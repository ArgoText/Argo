#include "buffer.h"

Buffer::Buffer() {}

void Buffer::setPoint(unsigned int loc) {}

void Buffer::movePoint(unsigned int count) {}

char * Buffer::getPoint() {
    return point;
}

int Buffer::getLine() {
    return -1;
}

int Buffer::getColumn() {
    return -1;
}

void Buffer::setColumn() {}

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

void Buffer::replaceChar(char ch) {}

void Buffer::searchForward(char ch) {}

void Buffer::searchForward(char *string) {}

void Buffer::searchBackward(char ch) {}

void Buffer::searchBackward(char *string) {}

void Buffer::printBuffer() {}
