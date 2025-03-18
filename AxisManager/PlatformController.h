#ifndef PLATFORMCONTROLLER_H
#define PLATFORMCONTROLLER_H
#include <QTimer>
#include <QObject>
#include <modbus.h>
#include <iostream>
class PlatformController : public QObject {
    Q_OBJECT

public:
    explicit PlatformController(const QString& ip, int port = 502, QObject* parent = nullptr);
    ~PlatformController();

    // 轴使能功能
    bool commutAxis(int axisId);
    bool enableAxis(int axisId);        // 使能指定轴
    bool disableAxis(int axisId);       // 禁用指定轴
    bool readAxisEnableState(int axisId); // 读取指定轴的使能状态

    bool MoveToAbsolutePos(int axisId, float Position);
    bool MoveToRelativePos(int axisId, float Position);

    bool HaltAxis(int axisId);

    bool SetCurrPosToZero(int axisId);
    bool StartProgramMove(int axisId) ;
    bool StopProgramMove(int axisId);
    bool PauseProgramMove(int axisId);
    // 速度设置
    bool setAxisVelocity(int axisId, float velocity); // 设置单轴速度
    bool setBothAxisVelocity(float velocity0, float velocity1); // 同时设置双轴速度
    bool getAxisVelocity(int axisId, float& velocity);

    bool MovePositive(int axisid, float velocity);

    bool MovePositive(int axisid);

    bool MoveNegative(int axisid, float velocity);

    bool MoveNegative(int axisid);


    // 反馈位置读取
    bool readAxisPosition(int axisId, float& position); // 读取单轴反馈位置
  //  bool readBothAxisPositions(float& position0, float& position1); // 同时读取双轴反馈位置



    //加速度设置
    bool setAxisAcceleration(int axisId, float Acceleration); // 设置单轴加速度
    bool getAxisAcceleration(int axisId, float& Acceleration);

    //bool setBothAxisAcceleration(float acc0, float acc1); // 同时设置双轴加速度

    bool tryAllCoils(int startAddress, int coilCount);


   // void moveTo(double x, double y);   // 移动到指定位置

    //void stop();                       // 停止运动

    // 定时器控制
    Q_INVOKABLE void startPolling();
    void stopPolling();

signals:
    void axisStateUpdated(int axisId, bool enabled); // 轴使能状态更新
    void axisPositionUpdated(int axisId, float position); // 轴位置更新
    void axisVelocityUpdated(int axisId, float Velocity);
    void axisAccelerationUpdated(int axisId, float Acceleration);
    void errorOccurred(const QString& error);  // 错误信号


private:
    modbus_t* modbusContext; // libmodbus 上下文
    QTimer* pollingTimer;   // 用于定时读取数据

    // 内部辅助方法
    bool writeSingleCoil(int address, bool value); // 写单个线圈
    bool readSingleCoil(int address, bool& value); // 读单个线圈
    bool writeMultipleRegisters(int address, const std::vector<uint16_t>& values); // 写多个寄存器

    bool writeFloatRegister(int address, float value);

    bool readFloatRegister(int address, float &value);

    bool readMultipleRegisters(int address, int count, std::vector<uint16_t>& values); // 读多个寄存器
    // 声明 writeMultipleCoils 函数
    bool writeMultipleCoils(int startAddress, const std::vector<uint8_t>& coils);
    void getPlatformStatus();
};

#endif // PLATFORMCONTROLLER_H
