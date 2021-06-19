//
// Created by Akshay Patil on 6/19/21.
//

#ifndef ARGO_TRIE_H
#define ARGO_TRIE_H

#include "trienode.h"

class Trie {
private:
    TrieNode root;

public:
    Trie();

    TrieNode *search(TrieNode *curr, char key);
    void insert(char *str);
    TrieNode *search(char key);
};


#endif //ARGO_TRIE_H
