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

    if (count % 2 == 0) {

    }
    painter.setPen(QPen(Qt::black));
    displayFont.setStyleHint(QFont::TypeWriter);
    painter.setFont(displayFont);
    QFontMetrics fontMetrics(displayFont);
//    painter.drawRect(0, 0, 10, 10);

    int width = fontMetrics.horizontalAdvance("A") + 1;


    QString a = QString(QChar('A'));

    int firstLineVisible = event->rect().top() / fontMetrics.height();
    int lastLineVisible = firstLineVisible + event->rect().height() / fontMetrics.height() + 1;

    for(int line = firstLineVisible; line <= lastLineVisible; line++) {
//        for(int column = 0; column < 80; column++) {
//            painter.drawText(width * column, fontMetrics.height() * line, QString(QChar('A')));
//        }
        painter.drawText(0, fontMetrics.height() * line, QString::number(line));
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
    return QSize(1000, 100000000000);
}
