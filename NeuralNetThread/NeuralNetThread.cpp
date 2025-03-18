#include "NeuralNetThread.h"
#include <QString>
#include <QMutexLocker>
#include <stdexcept> // for std::exception

NeuralNetThread::NeuralNetThread(CircularQueue<cv::Mat>* circularQueue, std::deque<cv::Mat>* deque, nvinfer1::IExecutionContext* context, QObject* parent)
    : QThread(parent),
    m_circularQueue(circularQueue),
    m_deque(deque),
    m_context(context),
    m_stopFlag(false) {}

NeuralNetThread::~NeuralNetThread() {
    stopThread();
}

void NeuralNetThread::stopThread() {
    QMutexLocker locker(&m_mutex);
    m_stopFlag = true;
    m_waitCondition.wakeAll();
}

void NeuralNetThread::run() {
    while (true) {
        cv::Mat image1, image2;

        // 检查是否需要停止线程
        {
            QMutexLocker locker(&m_mutex);
            if (m_stopFlag)
                break;
        }

        // 从循环队列提取数据
        if (!m_circularQueue->dequeue(image1)) {
            QMutexLocker locker(&m_mutex);
            m_waitCondition.wait(&m_mutex, 10); // 等待10ms，避免忙等
            continue;
        }

        // 从deque提取数据
        {
            QMutexLocker locker(&m_mutex);
            if (m_deque->empty()) {
                m_waitCondition.wait(&m_mutex, 10);
                continue;
            }
            image2 = m_deque->front();
            m_deque->pop_front();
        }

        // 图像处理和推理
        QString result;
        if (image1.empty() || image2.empty()) {
            emit inferenceCompleted("Invalid input data");
            continue;
        }

        try {
            result = runInference(image1, image2);
        } catch (const std::exception& e) {
            emit inferenceCompleted("Inference failed: " + QString::fromStdString(e.what()));
        }
    }
}

QString NeuralNetThread::runInference(const cv::Mat& image1, const cv::Mat& image2) {
    // 具体的推理实现代码
    return "Inference result";
}
