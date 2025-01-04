#include "src/deque_gb.h"
#include <iostream>

int main() {
    Gb gb;
    gb.move_cursor(3);
    gb.insert('X');
    gb.del();
    std::cout << gb.string_with_gap() << "\n";
    return 0;
}
