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

TrieNode *Trie::search(char *key) {
    TrieNode *curr = &this->root;
    while (curr && *key) {
        curr = search(curr, *key);
        key++;
    }
    return curr == nullptr ? nullptr : curr;
}

void Trie::insert(char *str) {
    TrieNode *curr = &root;
    while (*str && *str != ' ') {
        if (!curr->getChild(*str)) {
            curr->addChild(*str);
        }
        curr = curr->getChild(*str);
        str++;
    }
    curr->setComplete(true);
}

void Trie::possibleWords(char *prefix, TrieNode *subtree, vector<char *> *pw) {
    if (!subtree->getChildren().empty()) {
        for (auto i : subtree->getChildren()) {
            int len1 = std::strlen(prefix);
            const char c = i.first;


            char *new_prefix = new char[len1 + 2];
            std::strncpy(new_prefix, prefix, len1);
            new_prefix[len1] = c;
            new_prefix[len1 + 1] = '\0';
            possibleWords(new_prefix, &i.second, pw);
        }
    }
    if (subtree->isComplete()) {
        pw->push_back(prefix);
    }
}

Trie::Trie(vector<char *> keyWords) {
    for (char *keyWord : keyWords) {
        insert(keyWord);
    }
}

Trie::Trie(char *fileName) {
    fstream myfile(fileName, std::ios::in | std::ios::out);
    string s;
    while (getline(myfile, s)) {
        char keyWord[s.length()];
        strcpy(keyWord, s.c_str());
        insert(keyWord);
    }
    myfile.close();
}




