#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include "CircularQueue.h"
#include <QTimer>

class UdpServer : public QObject {
    Q_OBJECT


public:
    UdpServer(int port, CircularQueue<float>& queue, QObject* parent = nullptr);
    void startConnect(); // 启动UDP监听
    void stopUdp();
signals:
    void messageSignal(const QString &message);

private slots:
    void readPendingDatagrams();
    void attemptBind();

private:
    QUdpSocket* AeUdpSocket;
    CircularQueue<float>& dataQueue;
    int listenPort;
    QTimer* connectionTimer;      // 连接尝试定时器
    //bool Isconnnected;
};

#endif // UDPSERVER_H
