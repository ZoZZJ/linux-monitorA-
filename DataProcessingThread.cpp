#include "DataProcessingThread.h"
#include <cmath>
#include <QDebug>
//dataQueue=AeRxQueue
DataProcessingThread::DataProcessingThread(CircularQueue<float>& dataQueue,std::vector<float>& g_ProcessedAeData, QObject* parent)
    : QThread(parent), dataProcessQueue(dataQueue),ProcessedAeData(g_ProcessedAeData) {}

void DataProcessingThread::run() {

    while (!isInterruptionRequested()) {
        if (!dataProcessQueue.isEmpty()) {
            QMutexLocker locker(&m_mutex);
            int dataSize = dataProcessQueue.size();

            // 处理数据，确保不超过 ProcessedAeData 的大小
            for (int i = 0; i < std::min(dataSize, static_cast<int>(ProcessedAeData.size())); ++i) {
                float value = dataProcessQueue[i]; // 使用索引访问
                ProcessedAeData[i] = 2595 * log10(1 + (value / 700.0)); // 示例变换
                //ProcessedAeData[i] = value;//不处理供测试用
            }
           emit messageSignal("--Mel图绘制完毕--");

            //emit SendDataToPlot(mel);

            //emit dataProcessed(wavelet, mel, rms);
        }
        msleep(50);
    }
}

std::vector<float> DataProcessingThread::waveletTransform(const std::vector<float>& data) {
    // 示例：简单的 Haar 小波变换
    std::vector<float> result;
    int n = data.size();
    if (n < 2) return result;

    // 进行一次小波变换
    for (int i = 0; i < n / 2; ++i) {
        float average = (data[2 * i] + data[2 * i + 1]) / 2.0;
        float detail = (data[2 * i] - data[2 * i + 1]) / 2.0;
        result.push_back(average);
        result.push_back(detail);
    }
    return result;
}

std::vector<float> DataProcessingThread::melFrequency(const std::vector<float>& data) {
    // 梅尔频率计算
    std::vector<float> mel;
    int N = data.size();
    for (int i = 0; i < N; ++i) {
        mel.push_back(2595 * log10(1 + (data[i] / 700.0)));  // 示例公式
    }
    return mel;
}

float DataProcessingThread::calculateRMS(const std::vector<float>& data) {
    float sum = 0.0;
    for (float value : data) {
        sum += value * value;
    }
    return sqrt(sum / data.size());
}

