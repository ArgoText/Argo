#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scrollArea = new QScrollArea;
    QVBoxLayout *scrollLayout = new QVBoxLayout;
    scrollLayout->setSizeConstraint(QLayout::SetMinimumSize);
    editorView = new EditorView;
    scrollLayout->addWidget(editorView);
    scrollArea->setLayout(scrollLayout);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(scrollArea);
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("Argo");
    setWindowState(Qt::WindowMaximized);
}
