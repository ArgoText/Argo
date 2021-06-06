#include <iostream>
#include <fstream>
#include <QPainter>
#include <QSize>
#include <QFontMetrics>
#include <QFileDialog>
#include <QColor>
#include "editorview.h"

EditorView::EditorView(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    buffer = new Buffer;
    displayFont = QFont("DejaVu Sans Mono");
    resize(2000, 20000);
    //displayFont = QFont("Monaco");
}

EditorView::~EditorView() {};

void EditorView::paintEvent(QPaintEvent *event) {

    resize(2000, 20000);

    QPainter painter(this);
    painter.fillRect(event->rect(), QBrush(QColor(10, 19, 27)));
    painter.setPen(QPen(QColor(255,255,255)));
    displayFont.setStyleHint(QFont::Monospace);
    painter.setFont(displayFont);
    QFontMetrics fontMetrics(displayFont);

    int width = fontMetrics.horizontalAdvance("A");
    QString a = QString(QChar('A'));

    int firstLineVisible = event->rect().top() / fontMetrics.height();
    int lastLineVisible = firstLineVisible + event->rect().height() / fontMetrics.height() + 1;

    int initialPoint = buffer->getRelativePoint();

    buffer->setPoint(0);


    // for(int line = firstLineVisible; line <= lastLineVisible; line++) {
//        for(int column = 0; column < 80; column++) {
//            painter.drawText(width * column, fontMetrics.height() * line, QString(QChar('A')));
//        }
        //painter.drawText(0, fontMetrics.height() * line, QString::number(line));
    int line = 1;
    while (buffer->getPoint() < buffer->getBufferEnd()) {    
        int col = 0;
        while (buffer->getChar() != '\n' && buffer->getPoint() < buffer->getBufferEnd()) {
            painter.drawText(width * col, fontMetrics.height() * line, QString(QChar(buffer->getChar())));
            if (buffer->getRelativePoint() == initialPoint - 1) {
                painter.drawRect(width * (col+1) - 1, fontMetrics.height() * (line-1), 1, fontMetrics.height());
            }
            buffer->movePoint(1);
            col++;
        }
        buffer->movePoint(1);
        line++;
    }
    buffer->setPoint(initialPoint);
}


void EditorView::updateFont(const QFont &font) {
    displayFont.setFamily(font.family());
    update();
}

void EditorView::keyPressEvent(QKeyEvent *event) {

    if (event->modifiers() & Qt::ShiftModifier) {
        if (event->key() != Qt::Key_Shift) {
            buffer->insertChar(char(event->key()));
        }
    } else if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() == Qt::Key_O) {
            QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("Text Files (*.cpp)"));
            char ch;
            std::ifstream fin(fileName.toUtf8().constData(), std::ifstream::in);
            while (fin >> std::noskipws >> ch) {
                buffer->insertChar(ch);
            }
        }
    } else {
        buffer->insertChar(char(event->key() + 32));
    }

    // if (event->key() >= 65 && event->key() <= 90) {
    //     if (event->modifiers() & Qt::ShiftModifier) {
    //         if (event->key() != Qt::Key_Shift) {
    //             buffer->insertChar(char(event->key()));
    //         }
    // }   else {
    //         buffer->insertChar(char(event->key() + 32));
    //     }
    // } else {
    //     buffer->insertChar(char(event->key()));
    // }
    update();
}