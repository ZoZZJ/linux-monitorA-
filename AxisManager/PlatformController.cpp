#include "PlatformController.h"
#include <QDebug>

PlatformController::PlatformController(const QString& ip, int port, QObject* parent)
    : QObject(parent), modbusContext(nullptr), pollingTimer(new QTimer(this)) {
    // 初始化 Modbus TCP 连接
    modbusContext = modbus_new_tcp(ip.toStdString().c_str(), port);
    if (!modbusContext) {
        qCritical() << "Failed to create Modbus context!";
        return;
    }
//从机地址
    modbus_set_slave(modbusContext, 1);

    if (modbus_set_response_timeout(modbusContext, 1, 0) == -1) {
            qDebug() << "Failed to set response timeout!";
            modbus_free(modbusContext);  // 释放资源
            return;
        }

    if (modbus_connect(modbusContext) == -1) {
        qCritical() << "Failed to connect to Modbus server:" << modbus_strerror(errno);
        modbus_free(modbusContext);
        modbusContext = nullptr;
        return;
    }else{
        qDebug()<<"\n 已经成功连接！\n";
    }

    // 定时器连接槽
    connect(pollingTimer, &QTimer::timeout, this, &PlatformController::getPlatformStatus);
}

//单轴使能（0 或 1轴）
PlatformController::~PlatformController() {
    if (modbusContext) {
        modbus_close(modbusContext);
        modbus_free(modbusContext);
    }
}

bool PlatformController::commutAxis(int axisId) {
    int address = (axisId == 0) ? 9632 : 9633; // 轴对应的地址
    return writeSingleCoil(address, true); // 上升沿触发
}

bool PlatformController::enableAxis(int axisId) {
    int address = (axisId == 0) ? 9600 : 9601; // 轴对应的地址
    return writeSingleCoil(address, true); // 上升沿触发
}

bool PlatformController::disableAxis(int axisId) {
    int address = (axisId == 0) ? 9616 : 9617; // 轴对应的地址
    return writeSingleCoil(address, true);
}

bool PlatformController::readAxisEnableState(int axisId) {
    int address = (axisId == 0) ? 1025 : 1057; // 轴对应的地址
    bool value;
    return readSingleCoil(address, value);
}

bool PlatformController::HaltAxis(int axisId) {
    int address = (axisId == 0) ? 9680 : 9681;
    return writeSingleCoil(address, true);
}

bool PlatformController::SetCurrPosToZero(int axisId) {
    int address = (axisId == 0) ? 9713 : 9714;
    return writeSingleCoil(address, true);
}

bool PlatformController::StartProgramMove(int axisId) {
    int address = (axisId == 0) ? 9729 : 9630;
    return writeSingleCoil(address, true);
}

bool PlatformController::StopProgramMove(int axisId) {
    int address = (axisId == 0) ? 9745 : 9746;
    return writeSingleCoil(address, true);
}

bool PlatformController::PauseProgramMove(int axisId) {
    int address = (axisId == 0) ? 9745 : 9746;
    return writeSingleCoil(address, true);
}

bool PlatformController::setAxisAcceleration(int axisId, float Acceleration){
    int address = (axisId == 0) ? 0000 : 0002; // 轴对应的地址   也可能是1440


    return writeFloatRegister(address, Acceleration);
}


//单轴反馈加速度
bool PlatformController::getAxisAcceleration(int axisId, float& Acceleration) {
    int address = (axisId == 0) ? 0000 : 0002; // 轴对应的地址 //
    if (readFloatRegister(address, Acceleration)) {
        return true;
    }
    return false;
}

//单轴速度
bool PlatformController::setAxisVelocity(int axisId, float velocity) {

    int address = (axisId == 0) ? 4416 : 4418; // 轴对应的地址

    return writeFloatRegister(address, velocity);
}

////双轴速度
//bool PlatformController::setBothAxisVelocity(float velocity0, float velocity1) {
//    const int address = 4416; // 起始地址
//    std::vector<uint16_t> values = {
//        static_cast<uint16_t>(velocity0), 0, // 0轴速度
//        static_cast<uint16_t>(velocity1), 0  // 1轴速度
//    };
//    return writeFloatRegister(address, Acceleration);
//}

//单轴速度
bool PlatformController::getAxisVelocity(int axisId, float& velocity) {
    int address = (axisId == 0) ? 4416 : 4418; // 轴对应的地址   也可能是1664
    if (readFloatRegister(address, velocity)) {
        return true;
    }
    return false;
}



bool PlatformController:: MovePositive(int axisId, float velocity){

    setAxisVelocity(axisId,velocity);
    int address = (axisId == 0) ? 9808 : 9809;
    return writeSingleCoil(address, true);
}


bool PlatformController:: MovePositive(int axisId){

    int address = (axisId == 0) ? 9808 : 9809;
    return writeSingleCoil(address, true);
}

bool PlatformController:: MoveNegative(int axisId, float velocity){

    setAxisVelocity(axisId,velocity);
    int address = (axisId == 0) ? 9824 : 9825;
    return writeSingleCoil(address, true);
}

bool PlatformController:: MoveNegative(int axisId){

    int address = (axisId == 0) ? 9824 : 9825;
    return writeSingleCoil(address, true);
}

//移动到绝对位置
bool PlatformController::MoveToAbsolutePos(int axisId, float Position) {

    int address0 = (axisId == 0) ? 9800 : 9802; // 轴对应的地址

     int ret = writeFloatRegister(address0, Position);

     if(ret) {
         int address1 = (axisId == 0) ? 9840 : 9842; // 轴对应的地址
         return writeFloatRegister(address1, Position);
     }
     return false;
}


//移动到相对位置
bool PlatformController::MoveToRelativePos(int axisId, float Position) {

    int address = (axisId == 0) ? 9832 : 9834; // 轴对应的地址
    int ret = writeFloatRegister(address, Position);

    if(ret) {
        int address1 = (axisId == 0) ? 9872 : 9844; // 轴对应的地址
        return writeFloatRegister(address1, Position);
    }
    return false;
}




//单轴反馈位置
bool PlatformController::readAxisPosition(int axisId, float& position) {
    int address = (axisId == 0) ? 1632 : 1634; // 轴对应的地址 //
    if (readFloatRegister(address, position)) {
        return true;
    }
    return false;
}

//双轴反馈位置

//bool PlatformController::readBothAxisPositions(float& position0, float& position1) {
//    int address = 1632; // 起始地址
//    std::vector<uint16_t> values;
//    if (readMultipleRegisters(address, 4, values)) {
//        position0 = static_cast<float>((values[1] << 16) | values[0]);
//        position1 = static_cast<float>((values[3] << 16) | values[2]);
//        return true;
//    }
//    return false;
//}





//5. 定时器循环控制
void PlatformController::startPolling() {
    if (!pollingTimer->isActive()) {
        pollingTimer->start(100); // 每 1 秒循环读取
    }
}

void PlatformController::stopPolling() {
    if (pollingTimer->isActive()) {
        pollingTimer->stop();
    }
}
//6. 底层读写函数

#include <QDebug>

bool PlatformController::writeSingleCoil(int address, bool value) {
    int result = modbus_write_bit(modbusContext, address, value);
    if (result == 1) {
        return true;
    } else {
        qDebug() << "写入失败: Address =" << address
                 << ", 错误信息 =" << modbus_strerror(errno);
        return false;
    }
}

//读单个线圈
bool PlatformController::readSingleCoil(int address, bool& value) {
    uint8_t data;
    int result = modbus_read_bits(modbusContext, address, 1, &data);
    if (result == 1) {
        value = (data != 0);
        return true;
    }
    return false;
}


//写多个寄存器
bool PlatformController::writeMultipleRegisters(int address, const std::vector<uint16_t>& values) {
    return modbus_write_registers(modbusContext, address, values.size(), values.data()) == values.size();
}

bool PlatformController::writeFloatRegister(int address, float value) {
    uint16_t regValues[2];

    // 将 float 转换成 32-bit 整数
    uint32_t intValue;
    memcpy(&intValue, &value, sizeof(float));

    // 拆分成低 16-bit 和高 16-bit（低字节在前）
    regValues[0] = intValue & 0xFFFF;          // 低 16 位
    regValues[1] = (intValue >> 16) & 0xFFFF;  // 高 16 位

    // 写入两个 16-bit 的寄存器
    if (modbus_write_registers(modbusContext, address, 2, regValues) != 2) {
        std::cerr << "Modbus 写入失败: " << modbus_strerror(errno) << std::endl;
        return false;
    }

    return true;
}


bool PlatformController::readFloatRegister(int address, float &value) {
    uint16_t registers[2]; // 读取两个16位寄存器
    int rc = modbus_read_registers(modbusContext, address, 2, registers);

    if (rc == -1) {
        std::cerr << "读取失败: " << modbus_strerror(errno) << std::endl;
        return false;
    }

    // CD AB 格式（低字在前，高字在后）
    uint32_t rawData = (static_cast<uint32_t>(registers[1]) << 16) | registers[0];

    // 转换成 float
    value = *reinterpret_cast<float*>(&rawData);
    return true;
}

//读多个寄存器
bool PlatformController::readMultipleRegisters(int address, int count, std::vector<uint16_t>& values) {
    values.resize(count);
    return modbus_read_registers(modbusContext, address, count, values.data()) == count;
}
void PlatformController::getPlatformStatus(){
    float posX, posY,velX,velY,accX,accY;
    // 读取 X 轴位置
    if (readAxisPosition(0, posX)) {
        emit axisPositionUpdated(0, posX); // 发送 X 轴位置信号
    } else {
        qWarning() << "Failed to read X axis position!";
    }

    // 读取 Y 轴位置
    if (readAxisPosition(1, posY)) {
        emit axisPositionUpdated(1, posY); // 发送 Y 轴位置信号
    } else {
        qWarning() << "Failed to read Y axis position!";
    }

    if (getAxisVelocity(0, velX)) {
        emit axisVelocityUpdated(0, velX); // 发送 X 轴位置信号
    } else {
        qWarning() << "Failed to read X axis Velocity!";
    }
    if (getAxisVelocity(1, velY)) {
        emit axisVelocityUpdated(1, velY); // 发送 Y 轴位置信号
    } else {
        qWarning() << "Failed to read Y axis Velocity!";
    }

    if (getAxisAcceleration(0, accX)) {
        emit axisAccelerationUpdated(0, accX); // 发送 X 轴位置信号
    } else {
        qWarning() << "Failed to read X axis Acceleration!";
    }

    if (getAxisAcceleration(1, accY)) {
        emit axisAccelerationUpdated(1, accY); // 发送 Y 轴位置信号
    } else {
        qWarning() << "Failed to read Y axis Acceleration!";
    }
}

bool PlatformController::tryAllCoils(int startAddress, int coilCount) {
    uint8_t data; // 用于保存单个线圈的状态

    for (int i = 0; i < coilCount; ++i) {
        int address = startAddress + i;  // 计算当前线圈的地址
        int result = modbus_read_bits(modbusContext, address, 1, &data);  // 读取当前线圈状态

        if (result == -1) {
            std::cerr << "Error reading coil at address " << address << ": " << modbus_strerror(errno) << std::endl;
        }else{
            std::cout << "sucess"<< std::endl;
        }
    }

    return true;
}



