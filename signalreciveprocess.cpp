#include "SignalReciveProcess.h"
#include <QtDebug>
#include <QThread>
#include <QtMath>

SignalReciveProcess::SignalReciveProcess() {
    // 连接 TCP 的信号到数据接收槽
    connect(&atcp, &AeTCP::dataReceivedSignals, this, &SignalReciveProcess::onDataReceived);
}

void SignalReciveProcess::onDataReceived(double data) {
    receivedData.append(data);  // 将接收到的数据包添加到接收数组中

    // 如果接收到的数据包达到指定数量，则进行处理
    if (receivedData.size() >= batchSize) {
        processData();  // 处理数据
    }
}

void SignalReciveProcess::processData() {

    // 处理数据的示例（简单的平方处理作为示例）
    for (double value : receivedData) {
        processedData.append(qPow(value, 2)); // 处理逻辑可以根据需要修改
    }

    emit dataProcessedSignals(processedData); // 发出数据处理完成的信号

    // 清空接收到的数据以便下一轮接收
    receivedData.clear();
}
