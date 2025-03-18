#ifndef DOUBLECLICKLABEL_H
#define DOUBLECLICKLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QWidget>  // 确保包含这个头文件
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPixmap>

class DoubleClickLabel : public QLabel {
    Q_OBJECT

public:
    explicit DoubleClickLabel(QWidget *parent = nullptr);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void doubleClicked();  // 自定义信号

};


class ImageDockWidget : public QDockWidget {
    Q_OBJECT

public:
    ImageDockWidget(QWidget *parent = nullptr) : QDockWidget("Image Viewer", parent) {
        QLabel *imageLabel = new QLabel(this);
        imageLabel->setScaledContents(true);
        setWidget(imageLabel);
        resize(400, 300); // 设置初始大小
    }

    void setImage(const QPixmap &pixmap) {
        QLabel *imageLabel = qobject_cast<QLabel *>(widget());
        imageLabel->setPixmap(pixmap);
    }
};




#endif // DOUBLECLICKLABEL_H
