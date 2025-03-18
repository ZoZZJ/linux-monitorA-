#ifndef DATAPROCESSINGTHREAD_H
#define DATAPROCESSINGTHREAD_H

#include <QThread>
#include <QMutex>
#include <QQueue>
#include <vector>
#include "CircularQueue.h" // 引入 CircularQueue 的头文件

class DataProcessingThread : public QThread {
    Q_OBJECT

public:
    DataProcessingThread(CircularQueue<float>& dataQueue,std::vector<float>& g_ProcessedAeData,QObject* parent = nullptr);
    void run() override;

signals:
    void dataProcessed(const std::vector<float>& wavelet, const std::vector<float>& mel, float rms);//处理三选一
    void SendDataToPlot(const std::vector<float>& mel);

    void messageSignal(const QString &message);

private:
    CircularQueue<float>& dataProcessQueue;
    std::vector<float>& ProcessedAeData;

    QMutex m_mutex;

    std::vector<float> waveletTransform(const std::vector<float>& data);
    std::vector<float> melFrequency(const std::vector<float>& data);
    float calculateRMS(const std::vector<float>& data);
};

#endif // DATAPROCESSINGTHREAD_H
