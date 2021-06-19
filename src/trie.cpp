//
// Created by Akshay Patil on 6/19/21.
//

#include "trie.h"

Trie::Trie() {
    root = TrieNode();
}

TrieNode *Trie::search(TrieNode *curr, char key) {
    return curr->getChild(key);
}

TrieNode *Trie::search(char key) {
    return search(&root, key);
}

void Trie::insert(char *str) {
    TrieNode *curr = &root;
    while (*str) {
        if (!curr->getChild(*str)) {
            curr->addChild(*str);
        }
        curr = curr->getChild(*str);
        str += 1;
    }
    curr->setComplete(true);
}
