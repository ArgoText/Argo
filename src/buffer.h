class Buffer {

    char *point;
    char *buffer;
    char *gapStart;
    char *gapEnd;
    int curLine;

    int initBuffer(unsigned int size);

    void expandBuffer(unsigned int size);

    void expandGap(unsigned int size);

public:

    static const int DEFAULT_GAP_SIZE = 20;

    Buffer();

    void setPoint(unsigned int loc);

    void movePoint(unsigned int count);

    char * getPoint();

    int getLine();

    int getColumn();

    void setColumn();

    char getChar();

    char nextChar();

    char previousChar();

    void putChar(char ch);

    void insertChar(char ch);

    void deleteChar();

    void replaceChar(char ch);

    void searchForward(char ch);

    void searchForward(char *string);

    void searchBackward(char ch);

    void searchBackward(char *string);

    void printBuffer();

};

    

    

    
    
    
