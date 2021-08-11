#ifndef ARGO_EDITORVIEW_H
#define ARGO_EDITORVIEW_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include "buffer.h"
#include "trie.h"
#include "autocompleteView.h"
#include <set>


class EditorView : public QWidget {
    Q_OBJECT

public:
    EditorView(QWidget *parent = nullptr);
    ~EditorView();

    void updateFont(const QFont &font);

    static const int MAX_WORD_SIZE = 20;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void generateKeywords(char *fileName);

private:
    QFont displayFont;
    int count;
    Buffer *buffer;
    int charWidth;
    int lineHeight;
    AutocompleteView *autocompleteView;
    set<string> keywords;
    const int lineNumberWidth = 6;
    char currentWord[100];
};

#endif
