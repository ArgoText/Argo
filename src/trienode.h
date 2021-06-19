//
// Created by Akshay Patil on 6/19/21.
//

#ifndef ARGO_TRIENODE_H
#define ARGO_TRIENODE_H

#include <unordered_map>

using namespace std;

class TrieNode {
private:
    unordered_map<char, TrieNode> children;
    bool complete;
public:
    TrieNode();

    void addChild(char key) { children[key] = TrieNode(); }
    TrieNode* getChild(char key) { return &children[key]; }
    unordered_map<char, TrieNode> getChildren() { return children; }
    bool isComplete() { return complete; }
    void setComplete(bool val) { complete = val; }
};


#endif //ARGO_TRIENODE_H
