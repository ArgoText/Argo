#include <iostream>
#include <QPainter>
#include <QSize>
#include <QFontMetrics>
#include "editorview.h"

EditorView::EditorView(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    buffer = new Buffer;
}

EditorView::~EditorView() {};

void EditorView::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    painter.fillRect(event->rect(), QBrush(Qt::white));
    painter.setPen(QPen(Qt::black));
    displayFont.setStyleHint(QFont::TypeWriter);
    painter.setFont(displayFont);
    QFontMetrics fontMetrics(displayFont);

    int width = fontMetrics.horizontalAdvance("A") + 1;
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
        while (buffer->getChar() != Qt::Key_Enter && buffer->getPoint() < buffer->getBufferEnd()) {
            painter.drawText(width * col, fontMetrics.height() * line, QString(QChar(buffer->getChar())));
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

/*
 * initial size of the editor widget
 */
QSize EditorView::sizeHint() const {
    return QSize(1000, 10000);
}

void EditorView::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers() & Qt::ShiftModifier) {
        if (event->key() != Qt::Key_Shift) {
            buffer->insertChar(char(event->key()));
        }
    } else if (event->modifiers() & Qt::CtrlModifier) {
        if (event->key() != Qt::Key_O) {
            QStringList fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("Text Files (*.txt)"));
            char ch;
            fstream fin(f, fstream::in);
            while (fin >> noskipws >> ch) {
                buffer->insertChar(ch);
            }
        }
    } else {
        buffer->insertChar(char(event->key() + 32));
    }
    update();
}