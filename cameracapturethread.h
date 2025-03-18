#ifndef CAMERACAPTURETHREAD_H
#define CAMERACAPTURETHREAD_H

#include <QThread>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include "CircularQueue.h"
//#include "GxViewer/AcquisitionThread.h"
//#include "GxViewer/GxViewer.h"


using namespace cv;

class CameraCaptureThread : public QThread
{
    Q_OBJECT

public:
    explicit CameraCaptureThread(CircularQueue<QPixmap>& queue, QObject *parent = nullptr);


protected:
    void run() override;

private:
    CircularQueue<QPixmap>& m_queue;
    void sendMessage(const QString &message);

signals:
    void messageSignal(const QString &message); // 声明信号
    void ImageSignal(QPixmap pixmap); // 声明信号
    //void OpenGxSignal();
    //void CloseGxSignal();
    //void EnqueuePictureSignals();
};


#endif // CAMERACAPTURETHREAD_H
