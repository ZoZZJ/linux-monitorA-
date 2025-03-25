#include "InferenceProcessor.h"
#include <QDebug>

InferenceProcessor::InferenceProcessor(TensorRTClassifier* classifier, CircularQueue<QPixmap>* queue)
    : m_classifier(classifier), m_queue(queue), m_isProcessing(false)
{
}

void InferenceProcessor::startProcessing()
{
    if (m_isProcessing) return;  // 防止重复启动
    m_isProcessing = true;

    // 启动线程，进行推理处理
    m_processingThread = std::thread(&InferenceProcessor::process, this);
    m_processingThread.detach();  // 让线程在后台运行
}

void InferenceProcessor::stopProcessing()
{
    m_isProcessing = false;  // 设置为停止状态
    if (m_processingThread.joinable()) {
        m_processingThread.join();  // 等待线程结束
    }
}

bool InferenceProcessor::isProcessing() const
{
    return m_isProcessing;
}

void InferenceProcessor::process()
{
    while (m_isProcessing) {
        if (!m_queue->isEmpty()) {

            auto start = std::chrono::high_resolution_clock::now();
            int classIndex = m_classifier->predict(m_queue->dequeue());  // 进行推理
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;


            sendMessage("Inference time: " + QString::number(duration.count()) + " seconds");


            emit classificationResult(classIndex);  // 发射推理结果信号
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 短暂休眠，避免占用过多 CPU
    }
}
