#include "buffer.h"

Buffer::Buffer() {}

void Buffer::pointSet(unsigned int loc) {}

void Buffer::pointMove(unsigned int count) {}

char * Buffer::pointGet() {
    return point;
}

char Buffer::getChar() {
    return 'a';
}

char Buffer::nextChar() {
    return 'a';
}

char Buffer::previousChar() {
    return 'a';
}

void Buffer::putChar(char ch) {}

void Buffer::insertChar(char ch) {}

void Buffer::deleteChar() {}

void Buffer::printBuffer() {}
