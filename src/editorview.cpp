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
    autocompleteView = new AutocompleteView;
    displayFont = QFont("DejaVu Sans Mono");
    displayFont.setStyleHint(QFont::Monospace);
    QFontMetrics fontMetrics(displayFont);
    charWidth = fontMetrics.horizontalAdvance("A");
    lineHeight = fontMetrics.height();
    //resize(2000, 20000);
    //displayFont = QFont("Monaco");
}

EditorView::~EditorView() {};

void EditorView::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    painter.fillRect(event->rect(), QBrush(QColor(10, 19, 27)));
    painter.setPen(QPen(QColor(255,255,255)));
    painter.setFont(displayFont);

    char *curr = buffer->getBufferStart();
    int line = 0;
    int col = 0;

    int maxCol = 0;

    while (curr < buffer->getBufferEnd() && line * lineHeight < event->rect().bottom()) {

        if (curr == buffer->getPoint()) {
            painter.drawRect(charWidth * (col) - 1, lineHeight * line, 1, lineHeight);
        }

        if (curr < buffer->getGapStart() || curr >= buffer->getGapEnd()) {
            if (*curr == '\n') {
                if (col > maxCol) {
                    maxCol = col;
                }
                line++;
                col = 0;
            } else {
                if (lineHeight * (line + 10) >= event->rect().top() && lineHeight * (line - 10) <= event->rect().bottom() 
                && charWidth * col >= event->rect().left() && charWidth * col <= event->rect().right()) {
                    painter.drawText(charWidth * col, lineHeight * (line + 1), QString(QChar(*curr)));
                }
                col++;
            }
        }
        curr++;
    }

    //check where cursor is again in case it is at the end of the buffer
    if (curr == buffer->getPoint()) {
        painter.drawRect(charWidth * (col) - 1, lineHeight * line, 1, lineHeight);
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
        autocompleteView->update(char(127));
    } else if (event->key() == Qt::Key_Tab) {
        buffer->insertString("    ");
    } else if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() == Qt::Key_O) {
            QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("All Files (*)"));
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
            if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                QTextStream stream(&file);

                char *current = buffer->getBufferStart();

                while (current < buffer->getBufferEnd()) {
                    if ((current < buffer->getGapStart() || current >= buffer->getGapEnd()) && (*current < 128 && *current != '\00')) {
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
        autocompleteView->update(char(event->key() + 32));
    } else if (event->key() >= 32 && event->key() <= 127) {
        buffer->insertChar(char(event->key()));
        autocompleteView->update(char(event->key()));
    }
    update();
}