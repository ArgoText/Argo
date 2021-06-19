#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scrollArea = new QScrollArea;
    editorView = new EditorView;
    scrollArea->setWidget(editorView);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(scrollArea);
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("Argo");
    setWindowState(Qt::WindowMaximized);


}
