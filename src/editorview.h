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
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    char translate(QKey *key);

private:
    QFont displayFont;
    int count;
    Buffer *buffer;
};
