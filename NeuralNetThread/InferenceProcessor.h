#ifndef INFERENCEPROCESSOR_H
#define INFERENCEPROCESSOR_H

#include <QObject>
#include <thread>
#include "TensorRTClassifier.h"
#include "CircularQueue.h"

class InferenceProcessor : public QObject
{
    Q_OBJECT

public:

    InferenceProcessor(TensorRTClassifier* classifier, CircularQueue<QPixmap>* queue);


    void startProcessing();


    void stopProcessing();


    bool isProcessing() const;



signals:

    void classificationResult(int classIndex);
    void sendMessage(const QString &message);


private:

    void process();

private:
    TensorRTClassifier* m_classifier;      // 推理分类器对象
    //后续优化性能的话换成cv：mat
    CircularQueue<QPixmap>* m_queue;       // 图像队列
    bool m_isProcessing;                   // 是否正在处理
    std::thread m_processingThread;        // 处理线程
};

#endif // INFERENCEPROCESSOR_H
