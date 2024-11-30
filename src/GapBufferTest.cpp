#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <string>
#include <variant>

#include "gapbuffer.h"
/*
using namespace ::testing;

class GapBufferTest : public Test {
public:
};

TEST_F(GapBufferTest, DefaultConstructor) {
    auto gb = GapBuffer();

    EXPECT_EQ(gb.size(), 0);
    EXPECT_EQ(gb.capacity(), 32);
    EXPECT_EQ(gb.to_string(), "");
}

TEST_F(GapBufferTest, LengthConstructor) {
    auto gb = GapBuffer(64);

    EXPECT_EQ(gb.size(), 0);
    EXPECT_EQ(gb.capacity(), 64);
    EXPECT_EQ(gb.to_string(), "");
}

TEST_F(GapBufferTest, StringViewConstructor) {
    std::string s = "hello world";
    auto gb = GapBuffer(s);

    EXPECT_EQ(gb.size(), 11);
    EXPECT_EQ(gb.capacity(), 11 + 8);
    EXPECT_EQ(gb.to_string(), "hello world");
}

TEST_F(GapBufferTest, RangeConstructor) {
    std::vector<char> v1 = {'h', 'e', 'l', 'l', 'o'};
    auto gb1 = GapBuffer(v1.begin(), v1.end());

    EXPECT_EQ(gb1.size(), 5);
    EXPECT_EQ(gb1.capacity(), 5 + 8);
    EXPECT_EQ(gb1.to_string(), "hello");
}

TEST_F(GapBufferTest, CopyConstructor) {
    std::string_view s = "hello world";
    auto gb = GapBuffer(s);
    auto gb_copy = gb;

    EXPECT_EQ(gb_copy.size(), 11);
    EXPECT_EQ(gb_copy.capacity(), 11 + 8);
    EXPECT_EQ(gb_copy.to_string(), "hello world");
}

TEST_F(GapBufferTest, CopyAssignment) {
    std::string s = "hello world";
    auto gb = GapBuffer(s);
    auto gb_copy = gb;

    EXPECT_EQ(gb_copy.size(), 11);
    EXPECT_EQ(gb_copy.capacity(), 11 + 8);
    EXPECT_EQ(gb_copy.to_string(), "hello world");
}

TEST_F(GapBufferTest, MoveConstructor) {
    std::string s = "hello world";
    auto gb = GapBuffer(s);
    auto gb_move = std::move(gb);

    EXPECT_EQ(gb_move.size(), 11);
    EXPECT_EQ(gb_move.capacity(), 11 + 8);
    EXPECT_EQ(gb_move.to_string(), "hello world");
}

TEST_F(GapBufferTest, MoveAssignment) {
    std::string s = "hello world";
    auto gb = GapBuffer(s);
    auto gb_move = GapBuffer();
    gb_move = std::move(gb);

    EXPECT_EQ(gb_move.size(), 11);
    EXPECT_EQ(gb_move.capacity(), 11 + 8);
    EXPECT_EQ(gb_move.to_string(), "hello world");
}

TEST_F(GapBufferTest, At) {
    std::string s = "hello world";
    auto gb = GapBuffer(s);

    EXPECT_EQ(gb.at(0), 'h');
    EXPECT_EQ(gb.at(5), ' ');
    EXPECT_THROW(gb.at(21), std::out_of_range);
}

TEST_F(GapBufferTest, AtConst) {
    std::string s = "hello world";
    const auto gb = GapBuffer(s);

    EXPECT_EQ(gb.at(0), 'h');
    EXPECT_EQ(gb.at(5), ' ');
    EXPECT_THROW(gb.at(21), std::out_of_range);
}

TEST_F(GapBufferTest, ToStr) {
    std::string s = "hello world";
    auto gb = GapBuffer(s);
    EXPECT_EQ(gb.to_string(), s);

    gb.push_back('_');
    gb.push_back('_');
    gb.push_back('_');
    EXPECT_EQ(gb.to_string(), "hello world___");
}

TEST_F(GapBufferTest, Begin) {
    std::string s = "hello world";
    auto gb = GapBuffer(s);

    EXPECT_EQ(*gb.begin(), 'h');
    EXPECT_EQ(*(gb.begin() + 3), 'l');
}

TEST_F(GapBufferTest, End) {
    std::string s = "hello world";
    auto gb = GapBuffer(s);

    EXPECT_EQ(*(gb.end() - 9), 'd');
}

TEST_F(GapBufferTest, BeginConst) {
    std::string s = "hello world";
    const auto gb = GapBuffer(s);

    EXPECT_EQ(*gb.begin(), 'h');
    EXPECT_EQ(*(gb.begin() + 3), 'l');
}

TEST_F(GapBufferTest, EndConst) {
    std::string s = "hello world";
    const auto gb = GapBuffer(s);

    EXPECT_EQ(*(gb.end() - 9), 'd');
}

TEST_F(GapBufferTest, Cbegin) {
    std::string s = "hello world";
    const auto gb = GapBuffer(s);

    EXPECT_EQ(*gb.cbegin(), 'h');
    EXPECT_EQ(*(gb.cbegin() + 3), 'l');
}

TEST_F(GapBufferTest, Cend) {
    std::string s = "hello world";
    const auto gb = GapBuffer(s);

    EXPECT_EQ(*(gb.cend() - 9), 'd');
}

TEST_F(GapBufferTest, Rbegin) {
    std::string s = "hello world";
    auto gb = GapBuffer(s);

    EXPECT_EQ(*gb.rbegin(), 'd');
    EXPECT_EQ(*(gb.rbegin() + 3), 'o');
}

TEST_F(GapBufferTest, InsertChar) {
    auto gb = GapBuffer();
    gb.insert(gb.begin(), 'A');
    EXPECT_EQ(gb.size(), 1);
    EXPECT_EQ(gb.gapSize(), 32 - 1); // default is 32
    EXPECT_EQ(gb.at(0), 'A');
}

TEST_F(GapBufferTest, InsertStr) {
    auto gb = GapBuffer();
    std::string input = "ABC";
    gb.insert(gb.begin(), input);
    EXPECT_EQ(gb.size(), input.size());
    EXPECT_EQ(gb.gapSize(), 32 - input.size());

    size_t i = 0;
    for (const char& c : input) {
        EXPECT_EQ(gb.at(i++), c);
    }
}

TEST_F(GapBufferTest, EraseChar) {
    GapBuffer gb;
    gb.insert(gb.begin(), "ABC"); // Insert initial characters

    // Erase the first character ('A')
    gb.erase(gb.begin());

    EXPECT_EQ(gb.size(), 2);         // Size should be reduced to 2
    EXPECT_EQ(gb.gapSize(), 32 - 2); // Adjusted gap size
    EXPECT_EQ(gb.at(0), 'B');        // The new first character should be 'B'
    EXPECT_EQ(gb.at(1), 'C');        // The next character should still be 'C'
}

TEST_F(GapBufferTest, EraseStr) {
    GapBuffer gb;
    gb.insert(gb.begin(), "ABCDEFG"); // Insert initial characters

    // Erase characters from index 1 to 3 ('B', 'C', 'D')
    gb.erase(gb.begin() + 1, 3); // Erase 'BCD'

    EXPECT_EQ(gb.size(),
              4); // Remaining characters should be 'A', 'E', 'F', 'G'
    EXPECT_EQ(gb.gapSize(), 32 - 4); // Adjusted gap size
    EXPECT_EQ(gb.at(0), 'A');        // First character should be 'A'
    EXPECT_EQ(gb.at(1), 'E');        // Next character should be 'E'
    EXPECT_EQ(gb.at(2), 'F');        // Next character should be 'F'
    EXPECT_EQ(gb.at(3), 'G');        // Last character should be 'G'
}

TEST_F(GapBufferTest, charTest) {
    GapBuffer<char> gb;
    gb.insert(gb.begin(), 'a');

    gb.insert(gb.begin(), 't');
    gb.insert(gb.begin() + 1, 'h');
    gb.insert(gb.begin() + 2, 'i');
    gb.insert(gb.begin() + 3, 's');
    gb.insert(gb.begin() + 4, ' ');
    gb.insert(gb.begin() + 5, 'i');
    gb.insert(gb.begin() + 6, 's');
    gb.insert(gb.begin() + 7, 's');
    gb.insert(gb.begin() + 8, 's');

    EXPECT_EQ(gb.to_string(), "this isssa");
}
*/
class TextBufferTest : public ::testing::Test {
protected:
    // Simulating a TextBuffer using a variant for lines
    std::vector<std::variant<std::string, GapBuffer<char>>> buffer;
    size_t currentLineIdx = 0;

    TextBufferTest() {
        buffer.push_back("X");
        buffer.at(0) = GapBuffer<char>(std::get<std::string>(buffer.at(0)));
    }

    void switchLine(size_t newLineIdx) {
        if (currentLineIdx != newLineIdx) {
            // Convert current line to string
            if (std::holds_alternative<GapBuffer<char>>(
                    buffer.at(currentLineIdx))) {
                GapBuffer<char>& gbLine =
                    std::get<GapBuffer<char>>(buffer.at(currentLineIdx));
                buffer.at(currentLineIdx) = gbLine.to_string();
            }

            // Update current line index
            currentLineIdx = newLineIdx;

            // Convert new line to GapBuffer if it's a string
            if (std::holds_alternative<std::string>(
                    buffer.at(currentLineIdx))) {
                std::string lineString =
                    std::get<std::string>(buffer.at(currentLineIdx));
                buffer.at(currentLineIdx) = GapBuffer<char>(lineString);
            }
        }
    }

    void insertAt(size_t lineIdx, size_t col, char c) {
        switchLine(lineIdx);
        if (std::holds_alternative<GapBuffer<char>>(
                buffer.at(currentLineIdx))) {
            GapBuffer<char>& gbLine =
                std::get<GapBuffer<char>>(buffer.at(currentLineIdx));
            gbLine.insert(gbLine.begin() + col, c);
        } else {
            std::cout << std::to_string(lineIdx) << " " << std::to_string(col) << " " << "NOT GB\n";
        }
    }
};

TEST_F(TextBufferTest, GapReallocationTest) {
    switchLine(0);
    for (size_t i = 0; i < 100; ++i) {
        // Insert 'a', 'b', 'c' in a repeating pattern
        insertAt(0, i, "Abc"[i % 3]);
    }
    switchLine(0);
    const GapBuffer<char>& gbLine = std::get<GapBuffer<char>>(buffer.at(0));

    // Generate the expected string with the "abc" pattern repeated
    std::string expected;
    for (size_t i = 0; i < 100; ++i) {
        expected += "Abc"[i % 3];
    }

    EXPECT_EQ(gbLine.to_string(), expected);
}

/*

TEST_F(TextBufferTest, CursorRepositioningTest) {
    // Setup buffer with one line
    buffer.push_back(std::string("hello world"));

    // Insert characters in the middle
    switchLine(0);
    insertAt(0, 5, '!');
    insertAt(0, 6, '@');
    insertAt(0, 7, '#');

    // Check content after insertions
    const GapBuffer<char>& gbLine = std::get<GapBuffer<char>>(buffer.at(0));
    EXPECT_EQ(gbLine.to_string(), "hello!@# world");

    // Insert at the beginning
    insertAt(0, 0, '$');
    EXPECT_EQ(gbLine.to_string(), "$hello!@# world");

    // Insert at the end
    insertAt(0, gbLine.size(), '%');
    EXPECT_EQ(gbLine.to_string(), "$hello!@# world%");
}

TEST_F(TextBufferTest, LineSwitchingTest) {
    // Add multiple lines to the buffer
    buffer.push_back(std::string("first line"));
    buffer.push_back(std::string("second line"));
    buffer.push_back(std::string("third line"));

    // Switch between lines and edit
    switchLine(0);
    insertAt(0, 0, 'A');
    EXPECT_EQ(std::get<GapBuffer<char>>(buffer.at(0)).to_string(),
              "Afirst line");

    switchLine(1);
    insertAt(1, 6, 'B');
    EXPECT_EQ(std::get<GapBuffer<char>>(buffer.at(1)).to_string(),
              "seconBd line");

    switchLine(2);
    insertAt(2, 5, 'C');
    EXPECT_EQ(std::get<GapBuffer<char>>(buffer.at(2)).to_string(),
              "thirdC line");

    // Switch back to the first line
    switchLine(0);
    insertAt(0, 1, 'X');
    EXPECT_EQ(std::get<GapBuffer<char>>(buffer.at(0)).to_string(),
              "AXfirst line");
}
*/
