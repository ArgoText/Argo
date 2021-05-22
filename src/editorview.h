#include <QWidget>
#include <QPaintEvent>


class EditorView : public QWidget{

public:
    EditorView(QWidget *parent = nullptr);
    ~EditorView();

    void updateFont(const QFont &font);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QFont displayFont;

};
