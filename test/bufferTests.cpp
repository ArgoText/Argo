#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/buffer.h"

void fillBufferToGap(Buffer *buffer, char fill) {
    int gapSize = buffer->getGapEnd() - buffer->getGapStart();
    for(int i = 0; i < gapSize; i++) {
        buffer->insertChar(fill);
    }
}

void fillBufferOverGap(Buffer *buffer, char fill) {
    int gapSize = buffer->getGapEnd() - buffer->getGapStart();
    for(int i = 0; i <= gapSize; i++) {
        buffer->insertChar(fill);
    }
}

TEST_CASE("new buffer") {
    Buffer buffer;
    CHECK(buffer.getBufferStart() != buffer.getBufferEnd());
}

TEST_CASE("buffer resize") {
    Buffer buffer;
    int gapSize = buffer.getGapEnd() - buffer.getGapStart();
    int bufferSize = buffer.getBufferEnd() - buffer.getBufferStart();
    SUBCASE("no resize") {
        fillBufferToGap(&buffer, 'a');
        CHECK(bufferSize == buffer.getBufferEnd() - buffer.getBufferStart());
    }
    SUBCASE("resize") {
        fillBufferOverGap(&buffer, 'a');
        CHECK(bufferSize < buffer.getBufferEnd() - buffer.getBufferStart());
    }
}

TEST_CASE("getChar()") {
    Buffer buffer;

    SUBCASE("first character") {
        buffer.insertChar('a');
        buffer.setPoint(buffer.getBufferStart());
        CHECK(buffer.getChar() == 'a');
    }

    SUBCASE("after gap") {
        fillBufferToGap(&buffer, 'a');
        buffer.insertChar('b');
        buffer.setPoint(buffer.getPoint() - 1);
        CHECK(buffer.getChar() == 'b');

    }
}

TEST_CASE("previousChar()") {
    Buffer buffer;

    SUBCASE("at start") {
        char *prev = buffer.getPoint();
        buffer.previousChar();
        CHECK(buffer.getPoint() == prev);
    }

    SUBCASE("first char") {
        buffer.insertChar('a');
        buffer.setPoint(buffer.getBufferStart());
        char *prev = buffer.getPoint();
        CHECK(buffer.previousChar() == 'a');
        CHECK(buffer.getPoint() == prev);
    }

    SUBCASE("at gap") {
        fillBufferToGap(&buffer, 'a');
        CHECK(buffer.getPoint() == buffer.getGapEnd());
        CHECK(buffer.previousChar() == 'a');
        CHECK(buffer.getPoint() == buffer.getGapStart() - 1);
    }

    SUBCASE("after gap") {
        fillBufferOverGap(&buffer, 'a');
        CHECK(buffer.getPoint() == buffer.getGapStart());
        CHECK(buffer.previousChar() == 'a');
    }
}

TEST_CASE("insertString()") {
    Buffer buffer;

    SUBCASE("short string") {
        buffer.insertString("Hello");
        CHECK(*buffer.getBufferStart() == 'H');
    }
}