#include "InferenceProcessor.h"
#include <chrono>
#include <thread>
#include <iostream>
//使用前必须制定推理引擎地址以及队列指针
InferenceProcessor& InferenceProcessor::getInstance() {
    static InferenceProcessor instance;
    return instance;
}

InferenceProcessor::InferenceProcessor(QObject *parent)
    : QObject(parent), m_classifier(new TensorRTClassifier("/home/jetson/Model_pth/DirectionCNN_fp16.engine")), m_queue(nullptr), m_isProcessing(false) {

    m_classifier->testImage();
}

InferenceProcessor::~InferenceProcessor() {
    stopProcessing();
    if (m_classifier) {
        delete m_classifier;
        m_classifier = nullptr;
    }
}

void InferenceProcessor::setEnginePath(const std::string &path) {
    if (m_classifier) {
        delete m_classifier;
    }
    m_classifier = new TensorRTClassifier(path);
}

void InferenceProcessor::setQueue(CircularQueue<QPixmap> *queue) {
    m_queue = queue;
}

void InferenceProcessor::startProcessing() {
    if (!m_classifier || !m_queue) {
        emit sendMessage("Error: Classifier or queue not set.");
        return;
    }
    if (m_isProcessing) return;

    m_isProcessing = true;
    m_thread = std::thread(&InferenceProcessor::process, this);
}

void InferenceProcessor::stopProcessing() {
    m_isProcessing = false;
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void InferenceProcessor::process() {
    while (m_isProcessing) {
        if (m_queue && !m_queue->isEmpty()) {

            auto start = std::chrono::high_resolution_clock::now();
            std::pair<int, float> classIndex_confidence = m_classifier->predict(m_queue->dequeue());
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;

            emit classificationResult(classIndex_confidence);
            emit sendMessage(QString("Inference time: %1 seconds").arg(duration.count()));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
