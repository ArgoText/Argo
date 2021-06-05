#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include "editorview.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    EditorView *editorView;
    QScrollArea *scrollArea;
    QWidget *centralWidget;
    QVBoxLayout *centralLayout;
};
