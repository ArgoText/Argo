//
// Created by Akshay Patil on 7/30/21.
//

#ifndef AR_AUTOCOMPLETEVIEW_H
#define AR_AUTOCOMPLETEVIEW_H

#include <QWidget>
#include "trie.h"

class AutocompleteView : public QWidget {
    Q_OBJECT

public:
    AutocompleteView(QWidget *parent = nullptr);
    ~AutocompleteView();
    void update(char key);

private:
    Trie *pTree;
    TrieNode *curr;
    char *prefix;
};


#endif //AR_AUTOCOMPLETEVIEW_H
