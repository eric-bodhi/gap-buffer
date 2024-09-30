import typing
import copy


class GapBuffer:
    def __init__(self, nBytes: int = 16, initString: str = ""):
        self.buffer = bytearray(nBytes)
        initStrEncoded = initString.encode("utf-8")
        self.buffer[: len(initString)] = initStrEncoded
        self.gapStart = len(initString)
        self.gapEnd = nBytes

        self.initSize = nBytes

    def printBuffer(self):
        strBuffer = self.buffer.decode("utf-8")
        print(
            "".join(strBuffer[: self.gapStart])
            + "["
            + " " * (self.gapEnd - self.gapStart)
            + "]"
            + "".join(strBuffer[self.gapEnd :])
        )
        print(self.gapStart, self.gapEnd, len(self.buffer))

    def shiftGap(self, position: int):
        if 0 > position or position > len(self.buffer):
            raise ValueError("Out of bounds")

        delta = position - self.gapStart

        # if position is to the right
        if delta > 0:
            self.buffer[self.gapStart : self.gapStart + delta] = self.buffer[
                self.gapEnd : self.gapEnd + delta
            ]

        # if position is to the left
        elif delta < 0:
            self.buffer[self.gapEnd + delta : self.gapEnd] = copy.deepcopy(
                self.buffer[self.gapStart + delta : self.gapStart]
            )

        self.gapStart = position
        self.gapEnd += delta

    def resize(self, amount: int):
        if amount < 0:
            raise ValueError("Out of bounds")

        reqBuffSize = len(self.buffer) - (self.gapEnd - self.gapStart) + amount
        newBuff = bytearray(reqBuffSize)

        newBuff[: self.gapStart] = self.buffer[: self.gapStart]
        # gap already made newBuff[self.gapStart:self.gapStart+amount]
        newBuff[self.gapStart + amount :] = self.buffer[self.gapEnd :]

        self.buffer = newBuff
        self.gapEnd = self.gapStart + amount
        self.initSize = amount

    def insertChar(self, position: int, char):
        if self.gapStart == self.gapEnd:
            self.resize(self.initSize * 2)

        self.shiftGap(position)
        self.buffer[self.gapStart] = char
        self.gapStart += 1

    def delete(self, position: int, count: int):
        self.shiftGap(position)
        self.gapEnd = min(self.gapEnd + count, len(self.buffer))


gb = GapBuffer(2)

# Insert examples
gb.insertChar(0, 65)
gb.printBuffer()
gb.insertChar(0, 66)
gb.printBuffer()  # Gap is empty
gb.insertChar(0, 67)  # Gap has to resize
gb.printBuffer()
gb.insertChar(0, 68)
gb.insertChar(0, 69)
gb.insertChar(0, 70)
gb.insertChar(0, 71)  # Gap has to resize again
gb.printBuffer()

print("--------")

# Delete examples
gb = GapBuffer(2)
gb.printBuffer()
gb.insertChar(0, 65)
gb.insertChar(0, 66)  # Gap empty
gb.printBuffer()
gb.delete(0, 1)  # GapStart moved left one (decrement) to delete
gb.printBuffer()
