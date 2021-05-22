#include <iostream>
#include <QPainter>
#include <QSize>
#include <QFontMetrics>
#include "editorview.h"

EditorView::EditorView(QWidget *parent) : QWidget(parent) {
    //calculateSquareSize();
    setMouseTracking(true);
}

EditorView::~EditorView() {};

void EditorView::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    painter.fillRect(event->rect(), QBrush(Qt::white));
    painter.setPen(QPen(Qt::black));
    displayFont.setStyleHint(QFont::TypeWriter);
    painter.setFont(displayFont);
    QFontMetrics fontMetrics(displayFont);
//    painter.drawRect(0, 0, 10, 10);

    int width = fontMetrics.horizontalAdvance("A") + 1;


    QString a = QString(QChar('A'));

    for(int line = 0; line < 50; line++) {
        for(int column = 0; column < 80; column++) {
            painter.drawText(width * column, fontMetrics.height() * line, QString(QChar('A')));
        }
    }
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
