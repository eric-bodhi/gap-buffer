class GapBuffer:
    def __init__(self, initString="", gapSize=5):
        self.buffer = list(initString)
        self.start = 0
        self.end = self.start + gapSize
        self.make_gap(self.start, self.end)
        self.size = 5  # size of buffer for resizing

    def printBuffer(self):
        print("".join(self.buffer))
        print("start, end", self.start, self.end)
        print("Length", len(self.buffer), self.end - self.start)

    def insert(self, position, char):
        if position < 0 or position > len(self.buffer):
            raise ValueError("Out of bounds")

        if self.gap_size() <= 1:
            self.resize(self.size * 2)
        if self.start < position < self.end:  # is in gap
            self.buffer[self.start] = char
            self.start += 1

        else:
            self.move(position)
            self.buffer[self.start] = char
            self.start += 1

    def delete(self, position):
        if 0 > position or position >= len(self.buffer):
            raise ValueError("Out of bounds")

        self.move(position)
        self.buffer = self.buffer[: position + 1] + self.buffer[position + 1 :]

    def set_cursor(self, new_cursor):
        if 0 <= new_cursor <= len(self.buffer) - self.gap_size():
            self.move(new_cursor)

        else:
            raise ValueError("Out of bounds")

    def move(self, position):
        # Move gap left
        if position < self.start:
            while position < self.start:
                self.start -= 1
                self.end -= 1
                # Shift content from the left into the gap
                self.buffer[self.end] = self.buffer[self.start]
                self.buffer[self.start] = "_"

        # Move gap right
        elif position > self.start:
            while self.start < position:
                # Shift content from the right into the gap
                self.buffer[self.start] = self.buffer[self.end]
                self.buffer[self.end] = "_"
                self.start += 1
                self.end += 1

    def resize(self, count):
        newBuffer = ["_"] * count
        pre = self.buffer[: self.start]
        post = self.buffer[self.end :]

        self.buffer = pre + newBuffer + post
        self.end = self.start + count

    def make_gap(self, start, end):
        self.buffer = self.buffer[:start] + ["_"] * (end - start) + self.buffer[start:]

    def gap_size(self):
        return self.end - self.start


g = GapBuffer("This is the way out", 5)
g.printBuffer()
g.delete(6)
g.printBuffer()
