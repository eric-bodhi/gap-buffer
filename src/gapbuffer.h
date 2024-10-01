#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

template <typename T>
concept Fundamental = std::is_fundamental_v<T>;

template <Fundamental T = char, class Allocator = std::allocator<T>>
class GapBuffer {
public:
    // STL Compatible Container types
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = std::allocator_traits<Allocator>::pointer;
    using const_pointer = std::allocator_traits<Allocator>::const_pointer;

private:
    // Iterator to abstract the gap
    template <typename PointerType>
    class GapIterator {
    public:
        // std::conditional<condition, typeIfTrue, typeIfFalse>
        static const bool is_const =
            std::is_const_v<std::remove_pointer_t<PointerType>>;
        using iterator_category = std::contiguous_iterator_tag;
        using gapbuffer_pointer =
            std::conditional<is_const, const GapBuffer*, GapBuffer*>::type;

        using value_type =
            std::conditional<is_const, const GapBuffer::value_type,
                             GapBuffer::value_type>::type;
        using element_type =
            std::conditional<is_const, const value_type, value_type>::type;

        using pointer = PointerType;
        using reference = value_type&;
        using difference_type = std::ptrdiff_t; // difference type of 2 iterators
        // difference between INDEXES NOT values

        gapbuffer_pointer gb;
        PointerType ptr;

        explicit GapIterator() = default;
        explicit GapIterator(gapbuffer_pointer self, PointerType input_ptr)
            : gb(self), ptr(input_ptr) {
        }

        GapIterator& operator++() {
            ptr += 1;
            if (ptr == gb->gapStart) {
                ptr = gb->gapEnd;
            }
        }

        GapIterator& operator++(int) {
            GapIterator tmp = *this;
            ++(*this);
            if (ptr == gb->gapStart) {
                ptr = gb->gapEnd;
            }
            return *this;
        }

        GapIterator operator--() {
            ptr -= 1;
            if (ptr == gb->gapEnd) {
                ptr = gb->gapStart - 1;
            }
        }

        GapIterator operator--(int) {
            GapIterator tmp = *this;
            --(*this);
            if (ptr == gb->gapEnd) {
                ptr = gb->gapStart - 1;
            }
            return tmp;
        }

        // provides functionality for it + value
        GapIterator operator+(const int val) {
            GapIterator tmp = *this;
            return tmp += val;
        }

        GapIterator operator+(const difference_type other) const {
            return GapBuffer(gb, ptr + other);
        }

        // provides functionality for value + it
        friend GapIterator operator+(const difference_type val, const GapIterator& other) {
            return other + val;
        }

        GapIterator operator-(const int val) {
            GapIterator tmp = *this;
            return tmp -= val;
        }

        // difference between iterators !! accounting for gap
        difference_type operator-(const GapIterator& other) const {
            // if both before gap
            if (ptr < gb->gabStart && other.ptr < gb->gapStart) {
                return ptr - other.ptr;
            }
            // if both after gap
            else if (ptr > gb->gapEnd && other.ptr > gb->gapEnd) {
                return ptr - other.ptr;
            }
            // if on opposite sides of gap
            // total distance WITHOUT the gap
            else {
                return (gb->gapStart - other.ptr) + (ptr - gb->gapEnd);
            }
        }

        GapIterator operator-(const difference_type other) const {
            return GapIterator(gb, ptr - other);
        }

        friend GapIterator operator-(const difference_type value, const GapIterator& other) {
            return other - value;
        }

        GapIterator& operator+=(difference_type val) {
            ptr += val;
            return *this;
        }

        GapIterator& operator-=(difference_type val) {
            ptr -= val;
            return *this;
        }

        auto operator<=>(const GapIterator&) const = default;

        reference operator*() { return *ptr; }
        PointerType operator->() const { return &operator*(); }
    };

    // Iterator member types
    using iterator = GapIterator<pointer>;
    using const_iterator = GapIterator<const_pointer>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    // raw pointer over
    pointer bufferStart = nullptr;
    pointer gapStart = nullptr;
    pointer gapEnd = nullptr;
    pointer bufferEnd = nullptr;
};
