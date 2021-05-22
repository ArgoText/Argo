#include <QPainter>
#include "editorview.h"

EditorView::EditorView(QWidget *parent) : QWidget(parent) {
    //calculateSquareSize();
    setMouseTracking(true);
}

EditorView::~EditorView() {};

void EditorView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), QBrush(Qt::green));
}

void EditorView::updateFont(const QFont &font) {
    displayFont.setFamily(font.family());
    update();
}
