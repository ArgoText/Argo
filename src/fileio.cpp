//
// Created by Akshay Patil on 6/5/21.
//

#include "fileio.h"

void fileio::open(Buffer* buffer) {
    char ch;
    std::fstream fin("file", std::fstream::in);
    while (fin >> std::noskipws >> ch) {
        buffer->insertChar(ch);
    }
}
