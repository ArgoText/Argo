#include <QMainWindow>
#include <QScrollArea>
#include "editorview.h"

class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget *parent = nullptr);

private:
    EditorView *editorView;
    QScrollArea *scrollArea;
};
