class Buffer {

    char *point;
    char *buffer;
    char *gapStart;
    char *gapEnd;

    int initBuffer(unsigned int size);

    void expandBuffer(unsigned int size);

    void expandGap(unsigned int size);

public:

    static const int DEFAULT_GAP_SIZE = 20;

    Buffer();

    void pointSet(unsigned int loc);

    void pointMove(unsigned int count);

    char * pointGet();

    char getChar();

    char nextChar();

    char previousChar();

    void putChar(char ch);

    void insertChar(char ch);

    void deleteChar();

    void printBuffer();

};

    

    

    
    
    
