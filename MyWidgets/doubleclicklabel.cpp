#include "doubleclicklabel.h"

DoubleClickLabel::DoubleClickLabel(QWidget *parent)
    : QLabel(parent) {
}

void DoubleClickLabel::mouseDoubleClickEvent(QMouseEvent *event) {
    emit doubleClicked();  // 触发双击信号
    QLabel::mouseDoubleClickEvent(event);  // 调用父类的事件处理
}
