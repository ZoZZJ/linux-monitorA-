#include "offsetcorrect.h"
#include "ui_offsetcorrect.h"
#include <QDebug>

OffsetCorrect::OffsetCorrect(QWidget *parent)
    : QWidget(parent)
    , offui(new Ui::OffsetCorrectWidget)
{
    offui->setupUi(this);
    offui->RealTImagelabel_clf->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

OffsetCorrect::~OffsetCorrect()
{
    delete offui;
}

void OffsetCorrect::on_VideoButton_clicked()
{


}


void OffsetCorrect::on_FullScreenToggle_clf_clicked() {
    if (IsFullScreen) {
        qDebug() << "缩小";
        offui->ClassificationWidget->setWindowFlags(Qt::SubWindow);
        offui->ClassificationWidget->showNormal();
    } else {
        qDebug() << "最大化";
        offui->ClassificationWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        offui->ClassificationWidget->showFullScreen();
    }
    IsFullScreen = !IsFullScreen;
    // 立即调整 QLabel 大小
    offui->RealTImagelabel_clf->resize(offui->ClassificationWidget->size());
}
