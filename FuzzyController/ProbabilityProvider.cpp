#include "ProbabilityProvider.h"
#include <iostream>
ProbabilityProvider::ProbabilityProvider(QObject* parent)
    : QObject(parent) {
}

bool ProbabilityProvider::getProbabilities(Probabilities& probs) {
    QMutexLocker locker(&mutex);
    if (probQueue.isEmpty()) {

        // 队列为空时返回默认均匀概率
        probs.left = 0.333;
        probs.none = 0.333;
        probs.right = 0.333;
        return false;
    }
    if (probQueue.isEmpty()) {
        return false;
    }
    // 取最新的概率
    probs = probQueue.last();
    return true;
}

void ProbabilityProvider::enqueueProbabilities(const Probabilities& probs) {
    QMutexLocker locker(&mutex);

    // 控制队列大小，防止无限增长
    if (probQueue.size() >= MAX_QUEUE_SIZE) {
        probQueue.dequeue();
    }
    probQueue.enqueue(probs);
    // 可以根据需要选择是否发送信号
    //std::cout<<"sucess to enqueue Probabilities:"<<std::endl;

    // emit probabilitiesUpdated(probs);
}

void ProbabilityProvider::clearProbabilities() {
    QMutexLocker locker(&mutex);
    probQueue.clear();
}
