#include <QtCore>
#include <QApplication>
#include <QWidget>
#include <iostream>

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    QWidget window;

    window.resize(250, 150);
    window.setWindowTitle("Simple GUI");
    window.show();

    return app.exec();
}