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

    {
        // 创建按钮组
            radioGroupDistance = new QButtonGroup(this);
            radioGroupVelocity = new QButtonGroup(this);
            radioGroupMode = new QButtonGroup(this);

            // 向按钮组中添加按钮，并设置ID
            radioGroupDistance->addButton(xyui->distance0, 0);
            radioGroupDistance->addButton(xyui->distance1, 1);
            radioGroupDistance->addButton(xyui->distance2, 2);
            radioGroupDistance->addButton(xyui->distance3, 3);

            radioGroupVelocity->addButton(xyui->vel0, 0);
            radioGroupVelocity->addButton(xyui->vel1, 1);
            radioGroupVelocity->addButton(xyui->vel2, 2);

            radioGroupMode->addButton(xyui->moveEndureBtn, 0);
            radioGroupMode->addButton(xyui->moveOnceBtn, 1);

    }


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


    xyui->moveEndureBtn->setChecked(true);
    xyui->moveOnceBtn->setChecked(false);
}

XyPlatform::~XyPlatform()
{
    delete xyui;
}



void XyPlatform::setupUI() {


}

void XyPlatform::setupConnections() {

    connect(xyui->EnableButton,&QPushButton::pressed,this,&XyPlatform::ChangePlatformEnabledStatus);



    connect(radioGroupVelocity, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, [this](QAbstractButton *button) {
        if (!button || !controller) {
            qDebug() << "错误：button 或 controller 为 nullptr!";
            return;
        }

        // 获取按钮的文本并转换为 float
        bool ok;
        float velocity = button->text().toFloat(&ok);
        if (!ok) {
            qDebug() << "按钮文本的值无效:" << button->text();
            return;
        }

        qDebug() << "设置速度:" << velocity;

        // 使用获取的速度值设置轴的速度
        controller->setAxisVelocity(0, velocity);
        controller->setAxisVelocity(1, velocity);
    });





//     QObject::connect(radioGroupMode, &QButtonGroup::buttonClicked, [this](QAbstractButton *button) {
//         controller->setAxisVelocity(0,button->text().toFloat());
//         controller->setAxisVelocity(1,button->text().toFloat());
//     });

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
    if(xyui->moveEndureBtn->isChecked()){

        std::cout << "axis "<<axis<<"is moving  "<<std::endl;
        if(movePositve) controller->MovePositive(axis);
        else  controller->MoveNegative(axis);
    }else{
        std::cout << "axis "<<axis<<"is moving at step mode "<<std::endl;
        QAbstractButton *checkedButton = radioGroupDistance->checkedButton(); // 获取选中的按钮
        if (checkedButton) {
             std::cout << "checkedButton exists "<<std::endl;
            if(movePositve) controller->MoveToRelativePos(axis,checkedButton->text().toFloat());
            else controller->MoveToRelativePos(axis,-checkedButton->text().toFloat());
        }

    }

}

void XyPlatform::handleMoveY(bool movePositve) {
     int axis = 1;
    if(xyui->moveEndureBtn->isChecked()){
        std::cout << "axis "<<axis<<"is moving"<<std::endl;
        if(!movePositve) controller->MovePositive(axis);
        else  controller->MoveNegative(axis);
    } else{
        QAbstractButton *checkedButton = radioGroupDistance->checkedButton(); // 获取选中的按钮
        if (checkedButton) {
            if(!movePositve) controller->MoveToRelativePos(axis,checkedButton->text().toFloat());
            else controller->MoveToRelativePos(axis,-checkedButton->text().toFloat());
        }

    }

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
