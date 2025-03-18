#ifndef NEURAL_NET_THREAD_H
#define NEURAL_NET_THREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <deque>
#include <opencv2/opencv.hpp>
//#include <NvInfer.h>
#include "CircularQueue.h"  // 循环队列的头文件

class NeuralNetThread : public QThread {
    Q_OBJECT

public:
    NeuralNetThread(CircularQueue<cv::Mat>* circularQueue, std::deque<cv::Mat>* deque, nvinfer1::IExecutionContext* context, QObject* parent = nullptr);
    ~NeuralNetThread() override;

    void stopThread();

signals:
    void inferenceCompleted(const QString& result); // 推理完成信号

protected:
    void run() override;

private:
    QString runInference(const cv::Mat& image1, const cv::Mat& image2);

    CircularQueue<cv::Mat>* m_circularQueue;
    std::deque<cv::Mat>* m_deque;
    nvinfer1::IExecutionContext* m_context;
    QMutex m_mutex;
    QWaitCondition m_waitCondition;
    bool m_stopFlag;
};

#endif // NEURAL_NET_THREAD_H
