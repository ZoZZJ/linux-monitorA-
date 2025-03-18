#include "SignalAcquisitionThread.h"
#include <QDebug>



//暂时弃用了



SignalAcquisitionThread::SignalAcquisitionThread(CircularQueue<float>& AeRxQueue, QObject *parent)
    : QThread(parent), AeRxQueue(AeRxQueue) // 设定端口
{
    AeUdpSocket = new QUdpSocket(this);
}

void SignalAcquisitionThread::run() {
    //startServer(); // 启动 UDP 服务器

    while (!isInterruptionRequested()) {
        QThread::msleep(5); // 控制采集速度

        // 这里可以加入其他任务或处理
    }
}


void SignalAcquisitionThread::readPendingDatagrams() {
    while (AeUdpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(AeUdpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        AeUdpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        // 假设接收到的数据是 float 类型
        int numFloats = datagram.size() / sizeof(float);

        // 将数据解码并入队
        for (int i = 0; i < numFloats; ++i) {
            float* valuePtr = reinterpret_cast<float*>(datagram.data() + i * sizeof(float));
            AeRxQueue.enqueue(*valuePtr); // 将数据入队
            //qDebug() << "Received:" << *valuePtr;
        }

        sendMessage("Received data from UDP.");
    }
}

void SignalAcquisitionThread::sendMessage(const QString &message) {
    emit AeMessageSignal(message); // 发送信号
}
