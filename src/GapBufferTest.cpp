#include <gtest/gtest.h>
#include <string>

#include "gapbuffer.h"

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
