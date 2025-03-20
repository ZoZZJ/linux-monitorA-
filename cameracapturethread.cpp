#include "cameracapturethread.h"
#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include "GxViewer/GxViewer.h"

#ifdef _WIN32
#define PLATFORM_WINDOWS
#elif defined(__linux__)
#define PLATFORM_LINUX
#endif

using namespace cv;

CameraCaptureThread::CameraCaptureThread(CircularQueue<QPixmap>& queue, QObject *parent)
    : QThread(parent), m_queue(queue)
{
}

void CameraCaptureThread::run() {
#ifdef PLATFORM_WINDOWS
    VideoCapture cap(0); // 打开默认摄像头
    if (!cap.isOpened()) {
        qDebug() << "警告：相机开启失败";
        sendMessage("相机开启失败");
        return;
    }

    Mat frame;
    //线程任务：每50ms采集一次图形送入队列
    while (!isInterruptionRequested()) { // 检查是否请求中断
        cap.read(frame);
        if (frame.empty()) {
            qDebug() << "未检测到图像输入";
            continue;
        }
        // 转换 cv::Mat 到 QPixmap
        cv::cvtColor(frame, frame, COLOR_BGR2RGB); // 转换为 RGB 格式
        QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        QPixmap pixmap = QPixmap::fromImage(image);

        m_queue.enqueue(pixmap);
        QThread::msleep(35); // 控制采集速度
    }
    cap.release();   // 释放摄像头
    qDebug() << "相机已关闭";
    sendMessage("相机已关闭");
#else // PLATFORM_LINUX

    while (!isInterruptionRequested()) {
        QImage* image = CGxViewer::getInstance().GetShowImageFromAcquisionThread();

        if (!image) {
            QThread::msleep(50);  // 避免无效循环占用 CPU
            continue;
        }

        QPixmap pixmap = QPixmap::fromImage(*image); // 取消解引用空指针的风险

        m_queue.enqueue(pixmap);
        qDebug() << "Queue size:" << m_queue.size();

        delete image; // 释放内存，避免内存泄漏

        QThread::msleep(40);
    }


#endif
}

void CameraCaptureThread::sendMessage(const QString &message) {
    emit messageSignal(message); // 发送信号
}
