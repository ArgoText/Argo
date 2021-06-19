//
// Created by Akshay Patil on 6/5/21.
//

#include "fileio.h"

void fileio::open(Buffer* buffer) {
    char ch;
    fstream fin("file", fstream::in);
    while (fin >> noskipwas >> ch) {
        buffer->insertChar(ch)
    }
}
