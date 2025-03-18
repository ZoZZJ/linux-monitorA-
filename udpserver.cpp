#include "udpserver.h"
#include <QThread>
#include <QDebug>

UdpServer::UdpServer(int port, CircularQueue<float>& queue, QObject* parent)
    : QObject(parent), listenPort(port), dataQueue(queue) {
    AeUdpSocket = new QUdpSocket(this);
    //Isconnnected = false;
    connectionTimer = new QTimer(this);
    connect(connectionTimer, &QTimer::timeout, this, &UdpServer::attemptBind);
}

void UdpServer::startConnect() {
    connectionTimer->start(1000); // 每秒尝试绑定端口
    //qDebug() << "UDP server started. Attempting to bind to port:" << listenPort;
    emit messageSignal("等待客户端连接。。。");
}

void UdpServer::stopUdp() {
    AeUdpSocket->close(); // 关闭 socket
    qDebug() << "UDP server stopped.";
    emit messageSignal("udp停止。。。");
}

void UdpServer::attemptBind() {

    if (AeUdpSocket->bind(listenPort)) {
        connect(AeUdpSocket, &QUdpSocket::readyRead, this, &UdpServer::readPendingDatagrams);
        connectionTimer->stop(); // 成功绑定后停止定时器
        //qDebug() << "Successfully bound to port:" << listenPort;
         emit messageSignal("成功连上端口8888");
    } else {
        //qDebug() << "Failed to bind UDP socket. Retrying...";
        emit messageSignal("udpSocket绑定失败，正在重连");
    }

}


void UdpServer::readPendingDatagrams() {
    while (AeUdpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(AeUdpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        AeUdpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        //qDebug() << "Received:" << datagram;

        // 计算接收到的 float 数量
        int numFloats = datagram.size() / sizeof(float);

        // 将数据解码并入队
        for (int i = 0; i < numFloats; ++i) {
            float* valuePtr = reinterpret_cast<float*>(datagram.data() + i * sizeof(float));
            dataQueue.enqueue(*valuePtr); // 将数据入队
            //qDebug() << "Received:" << dataQueue[0];
            //qDebug() << "Received:" << *valuePtr;
        }
       // emit messageSignal("收到一个数据包");
    }
}
