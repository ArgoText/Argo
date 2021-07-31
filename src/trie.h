//
// Created by Akshay Patil on 6/19/21.
//

#ifndef ARGO_TRIE_H
#define ARGO_TRIE_H

#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include <cstring>
#include "trienode.h"

class Trie {
private:
    TrieNode root;

public:
    Trie();
    Trie(vector<char *> keyWords);
    Trie(char *fileName);

    TrieNode *search(TrieNode *curr, char key);
    void insert(char *str);
    TrieNode *search(char key);
    void possibleWords(char *prefix, TrieNode *subtree, vector<char *> *pw);

    TrieNode *getRoot() { return &root; }

    TrieNode *search(char *key);
};


#endif //ARGO_TRIE_H
