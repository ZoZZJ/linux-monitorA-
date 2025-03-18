#ifndef SIGNALRECIVEPROCESS_H
#define SIGNALRECIVEPROCESS_H

#include <QObject>
#include "AeTCP.h"
#include <QVector>

class SignalReciveProcess : public QObject {
    Q_OBJECT
public:
    SignalReciveProcess();

    void SignalProcess(QVector<double> dividedData);   // 开始处理数据

signals:
    void dataProcessedSignals(QVector<double> processedData); // 信号处理完毕信号

private slots:
    void onDataReceived(double data);  // 接收到数据的槽函数

private:
    AeTCP atcp;
    QVector<double> receivedData;  // 存储接收到的数据包
    QVector<double> processedData;// 存储处理完的数据包
    const int batchSize = 50;       // 每组数据的大小

    void processData();              // 处理数据的私有方法
};

#endif // SIGNALRECIVEPROCESS_H
