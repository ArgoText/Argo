#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include "buffer.h"


class EditorView : public QWidget {
    Q_OBJECT

public:
    EditorView(QWidget *parent = nullptr);
    ~EditorView();

    void updateFont(const QFont &font);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QFont displayFont;
    int count;
    Buffer *buffer;
};
