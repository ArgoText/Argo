//
// Created by Akshay Patil on 7/30/21.
//

#include "autocompleteView.h"

AutocompleteView::AutocompleteView(QWidget *parent) : QWidget(parent) {
    pTree = new Trie("../language/java.txt");
    curr = pTree->getRoot();
    prefix = "\0";
}

AutocompleteView::~AutocompleteView() {}

void AutocompleteView::update(char key) {
    if (key == 32) {
        curr = pTree->getRoot();
        prefix = "\0";
    } else if (key == 127) {
        char *n_prefix = new char[strlen(prefix)];
        strncpy(n_prefix, prefix, strlen(prefix) - 1);
        n_prefix[strlen(prefix) - 1] = '\0';
        prefix = n_prefix;
        curr = pTree->search(prefix);
    } else {
        curr = pTree->search(curr, key);
        char *n_prefix = new char[strlen(prefix) + 2];
        strncpy(n_prefix, prefix, strlen(prefix));
        n_prefix[strlen(prefix)] = key;
        n_prefix[strlen(prefix) + 1] = '\0';
        prefix = n_prefix;
    }
    vector<char *> pw = vector<char *>();
    pTree->possibleWords(prefix, curr, &pw);
    std::cout << pw.size() << "\n";
    for (char *c : pw) {
        std::cout << c << "\n";
    }
}