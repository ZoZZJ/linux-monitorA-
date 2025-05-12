#ifndef INFERENCEPROCESSOR_H
#define INFERENCEPROCESSOR_H

#include <QObject>
#include <QThread>
#include <QString>
#include <opencv2/opencv.hpp>
#include "TensorRTClassifier.h"
#include "CircularQueue.h"

class InferenceProcessor : public QObject {
    Q_OBJECT

public:
    static InferenceProcessor& getInstance();  // 获取单例

    void setEnginePath(const std::string &path);  // 设置模型路径
    void setQueue(CircularQueue<QPixmap> *queue); // 设置队列指针
    void startProcessing();  // 开始处理
    void stopProcessing();   // 停止处理
    const bool getProcessingStatus(){return m_isProcessing;}

signals:
    void classificationResult(std::pair<int, float> classIndex_conf);
    void sendMessage(const QString &message); // 发送消息

private:
    explicit InferenceProcessor(QObject *parent = nullptr);
    ~InferenceProcessor();

    InferenceProcessor(const InferenceProcessor&) = delete;
    InferenceProcessor& operator=(const InferenceProcessor&) = delete;

    void process();  // 线程执行的主循环

    TensorRTClassifier *m_classifier;
    CircularQueue<QPixmap> *m_queue;
    std::atomic<bool> m_isProcessing;
    std::thread m_thread;
};

#endif // INFERENCEPROCESSOR_H
