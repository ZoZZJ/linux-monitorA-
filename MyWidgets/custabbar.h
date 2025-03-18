#ifndef CUSTABBAR_H
#define CUSTABBAR_H

#include <QTabBar>
#include <QPaintEvent>

class CusTabBar : public QTabBar
{
    Q_OBJECT // 需要这个宏来启用信号与槽机制

public:
    CusTabBar();

    QSize tabSizeHint(int index) const override;

protected:
    void paintEvent(QPaintEvent *event) override; // 重绘tab文字和图片
};

#endif // CUSTABBAR_H
