//
// Created by Akshay Patil on 6/19/21.
//

#include "trienode.h"

TrieNode::TrieNode() {
    children = map<char, TrieNode>();
    complete = false;
}
