#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

class GapBuffer {
private:
    std::vector<char> buff;
    std::vector<char>::iterator gapStart, gapEnd;
    std::size_t initSize;

    std::size_t itToIndex(const std::vector<char>::iterator& it) {
        return std::distance(buff.begin(), it);
    }

public:
    GapBuffer(const std::size_t nBytes, std::string_view initString)
        : buff(nBytes), initSize(nBytes) {
        std::copy(initString.begin(), initString.end(), buff.begin());

        gapStart = buff.begin() + initString.size();
        gapEnd = buff.end();
    }

    void printBuffer() {
        std::string beforeGap(buff.begin(), gapStart);
        std::string afterGap(gapEnd, buff.end());

        std::string gap{};
        for (std::size_t i = 0; i < gapEnd - gapStart; i++) {
            gap.push_back('_');
        }

        std::cout << beforeGap << "[" << gap << "]" << afterGap << "\n";
        std::cout << itToIndex(gapStart) << ", " << itToIndex(gapEnd) << "\n";
    }

    void shiftGap(const std::size_t& position) {
        // shifting inside gap is UB
        if (position < 0 || position > buff.size() ||
            (itToIndex(gapStart) <= position &&
             position <= itToIndex(gapEnd))) {
            throw std::out_of_range("Index out of bounds");
        }

        // no shift required if already there
        else if (position == itToIndex(gapStart)) {
            std::cerr << "No shift == \n";
            return;
        }

        const int delta = position - *gapStart;
        for (std::size_t i = 0; i < delta; ++i) {
            *(gapStart + i) = *(gapEnd + i);
        }

        gapStart += position;
        gapEnd += delta;
    }

    void resize(const std::size_t& amount) {
        if (amount < initSize) {
            std::cerr << "Cannot resize to smaller size than " << initSize
                      << "\n";
        }

        std::cerr << "Gap before " << itToIndex(gapStart) << ", "
                  << itToIndex(gapEnd) << "\n";
        const std::size_t requiredBuffSize =
            buff.size() - (itToIndex(gapEnd) - itToIndex(gapStart)) + amount;
        std::vector<char> newBuff(requiredBuffSize);

        std::copy(buff.begin(), gapStart, newBuff.begin());
        std::copy(gapEnd, buff.end(),
                  newBuff.begin() + itToIndex(gapEnd) + amount);

        // for (int i = 0; i < buff.size(); i++) {
        //     std::cout << i << ", " << buff[i] << "\n";
        // }
        std::copy(newBuff.begin(), newBuff.end(), buff.begin());
        // for (int i = 0; i < buff.size(); i++) {
        //     std::cout << i << ", " << buff[i] << "\n";
        // }

        gapStart = buff.begin() + itToIndex(gapStart);
        gapEnd = gapStart + amount;
        initSize = amount;
        std::cerr << "Gap after " << itToIndex(gapStart) << ", "
                  << itToIndex(gapEnd) << "\n";
    }

    void insertChar(const std::size_t& position, const char& c) {
        if (gapStart == gapEnd) {
            resize(initSize * 2);
        }

        shiftGap(position);
        *gapStart = c;
        gapStart++;
    }

    void remove(const std::size_t& position, const std::size_t& count = 1) {
        shiftGap(position);
        gapEnd = std::min(gapEnd + count, buff.begin() + buff.size());
    }
};
