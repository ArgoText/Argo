#include <QWidget>
#include <QPaintEvent>


class EditorView : public QWidget {
    Q_OBJECT

public:
    EditorView(QWidget *parent = nullptr);
    ~EditorView();

    void updateFont(const QFont &font);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QFont displayFont;

};
