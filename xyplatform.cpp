#include "xyplatform.h"
#include "ui_xyplatformUI.h"
#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QImageReader>
#include <QGridLayout>
#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QButtonGroup>

XyPlatform::XyPlatform(QWidget *parent)
    : QWidget(parent), xyui(new Ui::XyPlatform)
{
    xyui->setupUi(this);

    controller = new PlatformController("10.0.0.100", 502, NULL);
    KeepMovingTimer = new QTimer(this);

    QThread* controllerThread = new QThread(this);

       // 将控制器移动到新线程
    controller->moveToThread(controllerThread);

       // 启动线程
    controllerThread->start();

    QMetaObject::invokeMethod(controller, "startPolling");

    setupConnections();
    connect(controllerThread, &QThread::finished, controller, &PlatformController::deleteLater);
    connect(controllerThread, &QThread::finished, controllerThread, &QThread::deleteLater);


    enableAxis();
    float velocity0 = 0.0f;
    float velocity1 = 0.0f;

   // controller->setBothAxisVelocity(0,0);

        // 获取第0轴的速度
        if (controller->getAxisVelocity(0, velocity0)) {
            qDebug() << "Axis 0 Velocity:" << velocity0;
        } else {
            qDebug() << "Failed to get Axis 0 Velocity";
        }

        // 获取第1轴的速度
        if (controller->getAxisVelocity(1, velocity1)) {
            qDebug() << "Axis 1 Velocity:" << velocity1;
        } else {
            qDebug() << "Failed to get Axis 1 Velocity";
        }

        float pos0 = 0.0f;
        float pos1 = 0.0f;

       controller->readAxisPosition(0,pos0);
       controller->readAxisPosition(1,pos1);

        qDebug() <<"Axis 1 pos: " << pos0;

        qDebug() <<"Axis 1 pos: " << pos1;

}

XyPlatform::~XyPlatform()
{
    delete xyui;
}



void XyPlatform::setupUI() {


}

void XyPlatform::setupConnections() {

    connect(xyui->EnableButton,&QPushButton::pressed,this,&XyPlatform::ChangePlatformEnabledStatus);


    // 长按移动
    connect(xyui->UpButton, &QPushButton::pressed, [=]() {  handleMoveY(1); });
    connect(xyui->DownButton, &QPushButton::pressed, [=]() {  handleMoveY(0); });
    connect(xyui->LeftButton, &QPushButton::pressed, [=]() { handleMoveX(0); });
    connect(xyui->RightButton, &QPushButton::pressed, [=]() {  handleMoveX(1); });

    // 松开按钮停止
    connect(xyui->UpButton, &QPushButton::released, this, [this]() { handleStop(1); });
    connect(xyui->DownButton, &QPushButton::released, this, [this]() { handleStop(1); });
    connect(xyui->LeftButton, &QPushButton::released, this,[this]() { handleStop(0); });
    connect(xyui->RightButton, &QPushButton::released, this, [this]() { handleStop(0); });

    // 定时更新状态和位置
    connect(controller, &PlatformController::axisStateUpdated, this, [=](int axisId, bool enabled) {
        if (axisId == 0) {
            //axis0Status->setText(QString("Axis 0: %1").arg(enabled ? "Enabled" : "Disabled"));
        } else {
            //axis1Status->setText(QString("Axis 1: %1").arg(enabled ? "Enabled" : "Disabled"));
        }
    });

    connect(controller, &PlatformController::axisPositionUpdated, this, &XyPlatform::onAxisPositionUpdated);
    connect(controller, &PlatformController::axisAccelerationUpdated, this, &XyPlatform::onAxisAccelerationUpdated);
    connect(controller, &PlatformController::axisVelocityUpdated, this, &XyPlatform::onAxisVelocityUpdated);

}


void XyPlatform::handleMoveX(bool movePositve) {
    int axis = 0;
     std::cout << "axis "<<axis<<"is moving  "<<std::endl;
    if(movePositve) controller->MovePositive(axis);
    else  controller->MoveNegative(axis);
}

void XyPlatform::handleMoveY(bool movePositve) {
    int axis = 1;
    std::cout << "axis "<<axis<<"is moving"<<std::endl;
    if(!movePositve) controller->MovePositive(axis);
    else  controller->MoveNegative(axis);
}


void XyPlatform::handleStop(int axisId) {
     std::cout << "axis stop moving"<<std::endl;
    //KeepMovingTimer->stop();
     controller->HaltAxis(axisId);
}

void XyPlatform::enableAxis(){

    int ret = controller->enableAxis(0);
     std::cout << "axis 0 "<<"ennable  "<<ret<<std::endl;
    int ret2 = controller->enableAxis(1);
     std::cout << "axis 1"<<"ennable  "<<ret2<<std::endl;
     if(ret&&ret2) platformEnabled = true;
     else platformEnabled  = false;
     xyui->EnableButton->setText( platformEnabled ? "失能":"使能");
}


void XyPlatform::disableAxis(){

    int ret = controller->disableAxis(0);
     std::cout << "axis 0 "<<"disable  "<<ret<<std::endl;
    int ret2 = controller->disableAxis(1);
     std::cout << "axis 1"<<"disable  "<<ret2<<std::endl;
     if(ret&&ret2) platformEnabled = false;
     else platformEnabled  = true;
     xyui->EnableButton->setText( platformEnabled ? "失能":"使能");
}

void XyPlatform::onAxisPositionUpdated(int axisId, float position) {
    if (axisId == 0) {
        // 更新 X 轴坐标
        xyui->XlcdNumber->display(position);
    } else if (axisId == 1) {
        // 更新 Y 轴坐标
        xyui->YlcdNumber->display(position);
    }
}

void XyPlatform::onAxisVelocityUpdated(int axisId, float Velocity) {
    if (axisId == 0) {
        // 更新 X 轴坐标
        xyui->CurrXVelEdit->setText(QString::number(Velocity));
    } else if (axisId == 1) {
        // 更新 Y 轴坐标
        xyui->CurrYVelEdit->setText(QString::number(Velocity));
    }
}

void XyPlatform::onAxisAccelerationUpdated(int axisId, float Acceleration) {
    if (axisId == 0) {
        // 更新 X 轴坐标
        xyui->CurrXAccEdit->setText(QString::number(Acceleration));
    } else if (axisId == 1) {
        // 更新 Y 轴坐标
        xyui->CurrYAccEdit->setText(QString::number(Acceleration));
    }
}

void XyPlatform::on_accPushButton_clicked()
{
    controller->setAxisAcceleration(xyui->AccAxisChooseBox->value(), static_cast<float>(xyui->AccSpinBox->value()));
}


void XyPlatform::on_VelocityPushButton_clicked()
{
     controller->setAxisVelocity(xyui->VelAxisChooseBox->value(), static_cast<float>(xyui->VelocitySpinBox->value()));
}

void XyPlatform::on_QMoveEnableWidgetButton_clicked()
{
    float postion0 =  xyui->TargetYposEdit->text().toFloat();
    float postion1 = xyui->TargetXposEdit->text().toFloat();
    controller->MoveToAbsolutePos(0,postion0);
    controller->MoveToAbsolutePos(1,postion1);
}


void XyPlatform::onRadioButtonClicked(QAbstractButton *button)
{
    float num = button->text().toFloat();
    xyui->VelAxisChooseBox->setValue(num);

    controller->setAxisVelocity(0,num);
    controller->setAxisVelocity(1,num);
}


void XyPlatform::ChangePlatformEnabledStatus(){

    platformEnabled ?  disableAxis():enableAxis();

}




void XyPlatform::on_CommutButton_clicked()
{
    if(controller->commutAxis(0)&&controller->commutAxis(1)) xyui->CommutButton->setEnabled(false);
}
