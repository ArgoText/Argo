//
// Created by Akshay Patil on 6/19/21.
//

#include "trienode.h"

TrieNode::TrieNode() {
    children = unordered_map<char, TrieNode>();
    complete = false;
}
