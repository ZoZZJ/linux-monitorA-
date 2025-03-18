#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <QPixmap>
#include <QVector>
#include <QMutex>
#include <QWaitCondition>
#include <stdexcept>

template <typename T>
class CircularQueue
{
public:
    explicit CircularQueue(int size) : m_size(size), m_front(0), m_rear(0), m_count(0) {
        m_data.resize(size);
    }

    void enqueue(const T &item) {
        QMutexLocker locker(&m_mutex);
        //QMutexLocker 是一个 RAII（资源获取即初始化）类，它会在创建时自动上锁指定的 QMutex，并在析构时自动解锁。这意味着你不需要手动解锁，因为 QMutexLocker 的生命周期结束时会自动执行解锁操作。
        if (m_count == m_size) {
            m_front = (m_front + 1) % m_size; // 如果队列满，覆盖最旧的元素
        } else {
            ++m_count;
        }
        m_data[m_rear] = item;
        m_rear = (m_rear + 1) % m_size;
        m_queueNotEmpty.wakeOne(); // 通知队列非空
    }

    T dequeue() {
        QMutexLocker locker(&m_mutex);
        while (isEmpty()) {
            m_queueNotEmpty.wait(&m_mutex);
        }
        T item = m_data[m_front];
        m_front = (m_front + 1) % m_size;
        --m_count;
        return item;
    }

    T front() const {
        QMutexLocker locker(&m_mutex);
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return m_data[m_front];
    }

    bool isEmpty() const {
        return m_count == 0;
    }

    bool isFull() const {
        return m_count == m_size;
    }

    int size() const {
        return m_count; // 返回当前元素数量，而不是容量
    }

    void clear() {
        m_front = 0;
        m_rear = 0;
        m_count = 0;
    }

    // 支持索引访问
    T& operator[](int index) {
        QMutexLocker locker(&m_mutex);
        if (index < 0 || index >= m_count) {
            throw std::out_of_range("Index is out of range");
        }
        // 计算实际索引
        int actualIndex = (m_front + index) % m_size;
        return m_data[actualIndex];
    }

    const T& operator[](int index) const {
        QMutexLocker locker(&m_mutex);
        if (index < 0 || index >= m_count) {
            throw std::out_of_range("Index is out of range");
        }
        // 计算实际索引
        int actualIndex = (m_front + index) % m_size;
        return m_data[actualIndex];
    }

private:
    QVector<T> m_data;
    int m_size;
    int m_front;
    int m_rear;
    int m_count;
    mutable QMutex m_mutex;
    QWaitCondition m_queueNotEmpty;
};

#endif // CIRCULARQUEUE_H
