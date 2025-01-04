#include "deque_gb.h"
#include <deque>
#include <string>
#include <stdexcept>

void Gb::move_cursor(size_t index) {
    // if cursor in same position
    if (index == left.size()) {
        return;
    }

    if (index < left.size()) {
        while (left.size() != index) {
            move_left();
        }
    }

    else {
        while (left.size() != index) {
            move_right();
        }
    }
}

// (in)(de)crement cursor
void Gb::move_left() {
    if (left.size() == 0) {
        throw std::runtime_error("move left: out of range");
    }

    right.push_front(left.back());
    left.pop_back();
}

void Gb::move_right() {
    if (right.size() == 0) {
        throw std::runtime_error("move right: out of range");
    }

    left.push_back(right.front());
    right.pop_front();
}

void Gb::insert(const char c) {
    left.push_back(c);
}

void Gb::del() {
    left.pop_back();
}

std::string Gb::string_with_gap() {
    return std::string(left.begin(), left.end()) + " " + std::string(right.begin(), right.end());
}

std::string Gb::to_string() {
    return std::string(left.begin(), left.end()) + std::string(right.begin(), right.end());
}
