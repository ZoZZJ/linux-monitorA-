#ifndef XYPLATFORMUI_H
#define XYPLATFORMUI_H
#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QCommandLinkButton>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "AxisManager/PlatformController.h"

namespace Ui {
class XyPlatform;
}

class XyPlatform : public QWidget
{
    Q_OBJECT

public:
    explicit XyPlatform(QWidget *parent = nullptr);
    ~XyPlatform();

private:

    Ui::XyPlatform *xyui;
    QButtonGroup *radioGroupMode;
    QButtonGroup *radioGroupDistance;
    QButtonGroup *radioGroupVelocity;

private:

    bool platformEnabled = false;
    PlatformController* controller; // 控制器实例
    int m_MoveType = 0; //0=步进 1=持续
    QTimer* KeepMovingTimer;       // 用于长按按钮触发移动

    void setupUI();          // 初始化UI
    void setupConnections(); // 绑定信号槽
    void enableAxis();
    void disableAxis();

private slots:

    void ChangePlatformEnabledStatus();
    void handleMoveX(bool movePositve);
    void handleMoveY(bool movePositve);
    void handleStop(int axisId);       // 停止移动
    void onAxisPositionUpdated(int axisId, float position);
     void onAxisVelocityUpdated(int axisId, float position);
     void onAxisAccelerationUpdated(int axisId, float position);
//    void updateStatus();     // 更新轴状态
//    void updatePosition();   // 更新轴位置
    void on_accPushButton_clicked();
    void on_VelocityPushButton_clicked();
    void onRadioButtonClicked(QAbstractButton *button);
    void on_QMoveEnableWidgetButton_clicked();
    void on_CommutButton_clicked();
};

#endif // XYPLATFORMUI_H
