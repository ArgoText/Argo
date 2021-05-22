#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scrollArea = new QScrollArea;
    editorView = new EditorView;
    scrollArea->setWidget(editorView);
    setWindowTitle("Argo");
}
