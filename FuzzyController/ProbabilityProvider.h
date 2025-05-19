#ifndef PROBABILITYPROVIDER_H
#define PROBABILITYPROVIDER_H

#include <QObject>
#include <QMutex>
#include <QQueue>
#include "NeuralNetThread/Probabilities.h"

class ProbabilityProvider : public QObject {
    Q_OBJECT
public:
    explicit ProbabilityProvider(QObject* parent = nullptr);
    ~ProbabilityProvider() override = default;

    // 获取最新的概率值，成功返回true，否则返回false且给出默认均匀概率
    bool getProbabilities(Probabilities& probs);

    // 入队一个概率结构体，限制队列最大长度防止内存暴涨
    void enqueueProbabilities(const Probabilities& probs);

public slots:
    // 清空队列中的所有概率数据
    void clearProbabilities();

signals:
    // 概率更新信号，传递结构体
    void probabilitiesUpdated(const Probabilities& probs);

private:
    QMutex mutex;                        // 保护队列的互斥锁
    QQueue<Probabilities> probQueue;    // 存储概率的队列
    static constexpr int MAX_QUEUE_SIZE = 1000;  // 最大队列长度
};

#endif // PROBABILITYPROVIDER_H
