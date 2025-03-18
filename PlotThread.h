#ifndef PLOTTHREAD_H
#define PLOTTHREAD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QVector>
#include <complex>
//#include <fftw3.h> // 引入 FFTW 库
#include "CircularQueue.h" // 引入 CircularQueue 的头文件

#include "SignalAcquisitionThread.h" // 添加这一行

class PlotThread  : public QThread {
    Q_OBJECT

public:
    explicit PlotThread(CircularQueue<float>& queue, std::vector<float>& processedData, QWidget *parent = nullptr);

    void run() override;

    void ProcessToggle(bool switch1);

    //void addSignalData(double signal);


signals:
    void plotReady(const QImage &image,const QImage &image2);
    void plotReadyone(const QImage &image);

    void AePlotMsgSignal(const QString &message);

public slots:
    void UpDateProcessedData(const std::vector<float>& mel);

private:
    bool ProcessOpened;
    QImage createProcessedImage();
    QImage createPlotImage();
    CircularQueue<float>& AeDataQueue;
    std::vector<float>& ProcessedAeData;
    QMutex m_mutex;
};

#endif // PLOTTHREAD_H
