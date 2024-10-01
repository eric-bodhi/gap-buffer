#include "gap-buffer.hpp"

int main() {
    GapBuffer gb(3, "A");
    gb.printBuffer();
    gb.insertChar(0, 'B');
    // gb.insertChar(0, 'C');
    gb.printBuffer();
    // gb.insertChar(0, 'D');
    // ISSUE WITH SHIFTGAP
    gb.printBuffer();
    return 0;
}
