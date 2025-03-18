#ifndef SIGNALACQUISITIONTHREAD_H
#define SIGNALACQUISITIONTHREAD_H

#include <QThread>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <QUdpSocket>
#include <QTcpSocket>
#include "CircularQueue.h"

//暂时弃用了
class SignalAcquisitionThread : public QThread
{
    Q_OBJECT

public:
    explicit SignalAcquisitionThread(CircularQueue<float>& AeRxQueue, QObject *parent = nullptr);

     void startServer();//UDP



protected:
    void run() override;

private slots:
    void readPendingDatagrams();//UDP

private:
    CircularQueue<float>& AeRxQueue;
    void sendMessage(const QString &message);
    void receiveDataFromUSB();         // 从USB设备接收数据

    QUdpSocket *AeUdpSocket;
    //const quint16 port = 8888; // 监听端口

signals:
    void AeMessageSignal(const QString &message);
    void AeFinishSignal(QPixmap pixmap);
    void dataReady(); // 用于通知处理线程有新数据

};


#endif // SIGNALACQUISITIONTHREAD_H
