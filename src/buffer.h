#ifndef ARGO_BUFFER_H
#define ARGO_BUFFER_H

class Buffer {

    char *point;
    char *bufferStart;
    char *bufferEnd;
    char *gapStart;
    char *gapEnd;
    int currLine;

    int initBuffer(unsigned int size);

    void expandBuffer(unsigned int size);

    void expandGap(unsigned int size);

public:

    static const int DEFAULT_GAP_SIZE = 20;

    Buffer(unsigned int size = DEFAULT_GAP_SIZE);

    ~Buffer();

    void moveGapToPoint();

    void copyBytes(char *destination, char *source, unsigned int length);

    void setPoint(char * loc);

    void setPointRelative(unsigned int loc);

    char * getPoint();

    int getPointRelative();

    int getLine();

    int getColumn();

    char * getBufferStart();

    char * getBufferEnd();

    char * getGapStart();

    char * getGapEnd();

    void setColumn(unsigned int column);

    char getChar();

    char nextChar();

    char previousChar();

    void putChar(char ch);

    void insertChar(char ch);

    void insertString(const char *string);

    void deleteChar();

    void backspace();

    void replaceChar(char ch);

    char * searchForward(char ch);

    void searchForward(char *string);

    char * searchBackward(char ch);

    void searchBackward(char *string);

    void printBuffer();

    bool atStart();
};

#endif

    

    

    
    
    
