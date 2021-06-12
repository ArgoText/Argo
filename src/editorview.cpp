#include <iostream>
#include <fstream>
#include <QPainter>
#include <QSize>
#include <QFontMetrics>
#include <QFileDialog>
#include <QTextStream>
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

    char *curr = buffer->getBufferStart();
    int line = 0;
    int col = 0;
    while (curr < buffer->getBufferEnd()) {

        if (curr == buffer->getPoint()) {
            painter.drawRect(width * (col) - 1, fontMetrics.height() * line, 1, fontMetrics.height());
        }

        if (curr < buffer->getGapStart() || curr >= buffer->getGapEnd()) {
            if (*curr == '\n') {
                line++;
                col = 0;
            } else {
                painter.drawText(width * col, fontMetrics.height() * (line + 1), QString(QChar(*curr)));
                col++;
            }
        }

        curr++;

    }
}


void EditorView::updateFont(const QFont &font) {
    displayFont.setFamily(font.family());
    update();
}

void EditorView::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        buffer->insertChar('\n');
    } else if (event->key() == Qt::Key_Right) {
        buffer->nextChar();
    } else if (event->key() == Qt::Key_Left) {
        buffer->previousChar();
    } else if (event->key() == Qt::Key_Backspace) {
        buffer->backspace();
    } else if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() == Qt::Key_O) {
            QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("Text Files (*.cpp)"));
            char ch;
            std::ifstream fin(fileName.toUtf8().constData(), std::ifstream::in);
            while (fin >> std::noskipws >> ch) {
                buffer->insertChar(ch);
            }
        } else if (event->key() == Qt::Key_S) {
            QString fileName = QFileDialog::getSaveFileName(this,
                                                            tr("Save file"), "",
                                                            tr("All Files (*)"));
            QFile file(fileName.toUtf8().constData());
            if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                QTextStream stream(&file);

                char *current = buffer->getBufferStart();

                while (current < buffer->getBufferEnd()) {
                    if (*current < 128 && *current != '\00') {
                        stream << *current;
                    }
                    current++;
                }

                file.close();
                //qDebug() << "Writing finished";
            }
        }
    } else if (event->key() >= 65 && event->key() <= 90 && !(event->modifiers() & Qt::ShiftModifier)) {
        buffer->insertChar(char(event->key() + 32));
    } else if (event->key() >= 32 && event->key() <= 126) {
        buffer->insertChar(char(event->key()));
    }
    update();
}