#include <iostream>
#include "buffer.h"

Buffer::Buffer(unsigned int size) {
    bufferStart = (char *) malloc(size);

    point = bufferStart;
    gapStart = bufferStart;

    gapEnd = bufferStart + size;
    bufferEnd = gapEnd;
}

Buffer::~Buffer() {
    if (bufferStart) {
        free(bufferStart);
    }
}

/*
 * Expand buffer to new size + default gap size
 */
void Buffer::expandBuffer(unsigned int size) {
    char *originalBuffer = bufferStart;
    int newBufferSize = (bufferEnd - bufferStart) + size + DEFAULT_GAP_SIZE;
    bufferStart =  (char *) realloc(bufferStart, newBufferSize);

    point += bufferStart - originalBuffer;
    bufferEnd += bufferStart - originalBuffer;
    gapStart += bufferStart - originalBuffer;
    gapEnd += bufferStart - originalBuffer;
}
/*
 * Expand the size of the gap to default + size
 */
void Buffer::expandGap(unsigned int size) {
    if (size > gapEnd - gapStart) {
        size += DEFAULT_GAP_SIZE;
        expandBuffer(size);
        copyBytes(gapEnd + size, gapEnd, bufferEnd - gapEnd);

        gapEnd += size;
        bufferEnd += size;
    }
}

/*
 * Moves the position of gapStart to the point
 */
void Buffer::moveGapToPoint() {

    if (point == gapStart) {
        return;
    }

    if (point == gapEnd) {
        point = gapStart;
    }

    if(point < gapStart) {
        copyBytes(point + (gapEnd - gapStart), point, gapStart - point);
        gapEnd -= (gapStart - point);
        gapStart = point;
    } else {
        copyBytes(gapStart, gapEnd, point - gapEnd);
        gapStart += point - gapEnd;
        gapEnd = point;
        point = gapStart;
    }
}

void Buffer::copyBytes(char *destination, char *source, unsigned int length) {

    if ((destination == source) ||  (length == 0)) {
        return;
    }
    if (source > destination) {

        if (source + length >= bufferEnd) {
            return;
        }

        for (; length > 0; length--) {
            *(destination++) = *(source++);
        }

    } else {
        source += length;
        destination += length;

        for (; length > 0; length--) {
            *(--destination) = *(--source);
        }
    }
}


void Buffer::setPoint(char * loc) {
    point = loc;
}

void Buffer::setPointRelative(unsigned int loc) {
    point = bufferStart + loc;
    if (point > gapStart) {
        point += gapEnd - gapStart;
    }
}


char * Buffer::getPoint() {
    return point;
}

int Buffer::getPointRelative() {
    if (point > gapStart) {
        return (point - (gapEnd - gapStart)) - bufferStart;
    } else {
        return point - bufferStart;
    }
    
}

int Buffer::getLine() {
    return currLine;
}

int Buffer::getColumn() {
    char *startLine = searchBackward('\n');
    return point - startLine;
}

char * Buffer::getBufferStart() {
    return bufferStart;
}

char * Buffer::getBufferEnd() {
    return bufferEnd;
}

char * Buffer::getGapStart() {
    return gapStart;
}

char * Buffer::getGapEnd() {
    return gapEnd;
}

void Buffer::setColumn(unsigned int column) {
    char *startLine = searchBackward('\n');
    point = startLine + column;
}

/*
 * Gets the char at the current point
 */
char Buffer::getChar() {
    if (point == gapStart) {
        point = gapEnd;
    }
    return *point;
}

/*
 * Gets the char right after the current point
 */
char Buffer::nextChar() {
    if (point == gapStart) {
        point = gapEnd + 1;
        return *point;
    } else if (point == bufferEnd) {
        return *gapEnd;
    } else {
        return *(++point);
    }
}

/*
 * Gets the char right before the current point
 */
char Buffer::previousChar() {
    if (point == gapEnd) {
        point = gapStart - 1;
        return *point;
    } else if (point == bufferStart) {
        return *bufferStart;
    } else {
        return *(--point);
    }
}

/*
 *
 */
void Buffer::insertChar(char ch) {
    if (point != gapStart) {
        moveGapToPoint();
    }

    if (gapStart == gapEnd) {
        expandGap(1);
    }

    *(gapStart++) = ch;

    point++;

}

void Buffer::insertString(const char *string) {
    while (*string) {
        insertChar(*string);
        string++;
    }
}

/*
 * Deletes the character at the current point
 */
void Buffer::deleteChar() {
    if (point != gapStart) {
        moveGapToPoint();
    }
    gapEnd++;
}

bool Buffer::atStart() {
    return point == bufferStart;
}

void Buffer::backspace() {
    previousChar();
    deleteChar();
}

/*
 * Replaces the char at the current point
 */
void Buffer::replaceChar(char ch) {
    if (point == gapStart) {
        point = gapEnd;
    }
    *point = ch;
}

/*
 * Searches for a character starting at the current point until the end of the buffer
 */
char * Buffer::searchForward(char ch) {
    char *curr = point;
    while (curr < bufferEnd) {
        curr++;
    }
    return curr;
}

/*
 * Searches for a string starting at the current point until the end of the buffer
 */
void Buffer::searchForward(char *string) {

}

/*
 * Searches for a character starting at the current point until the start of the buffer
 */
char * Buffer::searchBackward(char ch) {
    char *curr = point;
    while (*curr != ch && curr >= bufferStart) {
        curr--;
    }
    return curr;
}

/*
 * Searches for a string starting at the current point until the start of the buffer
 */
void Buffer::searchBackward(char *string) {

}

/*
 * Prints out the buffer in its entirety
 */
void Buffer::printBuffer() {
    char *curr = bufferStart;
    while (curr < bufferEnd) {
        if (curr >= gapStart && curr < gapEnd) {
            std::cout << "_";
        } else if (*curr != '\0') {
            std::cout << *curr;
        }
        curr++;
    }
    std::cout << (point - bufferStart) <<'\n';
}