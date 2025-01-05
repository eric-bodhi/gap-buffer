#include <deque>
#include <string>
class Gb {
private:
    std::deque<char> left = {'h', 'e'};
    std::deque<char> right = {'l', 'l', 'o'};
    // cursor = end of left
    // moving cursor through index of full string with no gap (left + right)
    //
public:
    Gb(const std::string& string = "", const size_t& cursor = 0);

    void move_cursor(size_t index);
    void move_left();
    void move_right();
    void insert(const char c);
    void del();

    std::string string_with_gap();
    std::string to_string();
};
