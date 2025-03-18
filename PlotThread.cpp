#include "PlotThread.h"
#include <QMutexLocker>
#include <QPainter>
#include <algorithm> // 引入 std::clamp
#include <QDebug>

PlotThread::PlotThread(CircularQueue<float>& queue, std::vector<float>& processedData, QWidget *parent)
    : QThread(parent), AeDataQueue(queue), ProcessedAeData(processedData),ProcessOpened(false) {}


void PlotThread::run() {
    while (!isInterruptionRequested()){

        QImage RawImage = createPlotImage();
        //QImage ProcessedImage ;

        if(ProcessOpened)
        {
            QImage ProcessedImage = createProcessedImage();
            emit plotReady(RawImage,ProcessedImage);
        }
        else emit plotReadyone(RawImage);

        msleep(20); // 控制更新频率为每 30ms 一次
    }
}

/*void PlotThread::addSignalData(double signal) {
    QMutexLocker locker(&m_mutex);
    // 可以在这里将信号数据添加到队列或进一步处理
}*/
void PlotThread::ProcessToggle(bool switch1){
    ProcessOpened = switch1;
    qDebug() << "ProcessOpened = ",ProcessOpened;
}


QImage PlotThread::createPlotImage() {
    //emit AePlotMsgSignal("正在画图呢---");
    // 创建图像，设定大小和格式
    QImage image(1200, 800, QImage::Format_RGB888);
    image.fill(Qt::white);  // 设置背景为白色
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿效果

    QMutexLocker locker(&m_mutex);
    int dataSize = AeDataQueue.size();
    if (dataSize < 2) return image; // 如果数据不足，直接返回空白图像

    double xScale = static_cast<double>(image.width() - 50) / dataSize;
    double yScale = static_cast<double>(image.height() - 50) / 2;  // Y 轴范围是 -1 到 1
    double amplification = 100.0; // 数据放大比例

    int margin = 40; // 边距
    int yAxisPosition = image.height() / 2; // Y 轴位置在中央
    int xAxisPosition = image.height() - margin; // X 轴位置

    // 绘制坐标轴
    painter.setPen(Qt::black);
    painter.drawLine(margin, yAxisPosition, image.width() - margin, yAxisPosition);  // Y轴
    painter.drawLine(margin, xAxisPosition, image.width() - margin, xAxisPosition);  // X轴

    // 标注X轴和Y轴的文字
    painter.setFont(QFont("Arial", 40)); // 增大标题字体大小
    painter.drawText(image.width() / 2 - 20, image.height() - 10, "Time (ms)");  // X轴标签
    painter.drawText(10, yAxisPosition + 50, "Amplitude");  // Y轴标签，稍微偏下

    // 设置标题

    painter.drawText(image.width() / 2 - 50, 100, "声发射数据");

    // 设置亮蓝色和线条宽度
    QColor brightBlue(0, 150, 255);
    QPen pen(brightBlue);
    pen.setWidth(4);
    painter.setPen(pen);

    // 开始绘制数据线条
    for (int i = 0; i < dataSize - 1; ++i) {
        int x1 = static_cast<int>(margin + i * xScale);
        int y1 = static_cast<int>(yAxisPosition - (AeDataQueue[i] * amplification * yScale));  // 调整Y坐标，确保负数在下面
        int x2 = static_cast<int>(margin + (i + 1) * xScale);
        int y2 = static_cast<int>(yAxisPosition - (AeDataQueue[i + 1] * amplification * yScale));  // 调整Y坐标，确保负数在下面

        // 限制 y1 和 y2 的值在有效范围内
        y1 = std::clamp(y1, 0, image.height() - 1);
        y2 = std::clamp(y2, 0, image.height() - 1);

        // 绘制从(x1, y1)到(x2, y2)的线条
        painter.drawLine(x1, y1, x2, y2);
    }


    return image;  // 返回最终绘制好的图像
}

QImage PlotThread::createProcessedImage() {
    // 创建图像，设定大小和格式
    QImage image(1200, 800, QImage::Format_RGB888);
    image.fill(Qt::white);  // 设置背景为白色
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿效果

    QMutexLocker locker(&m_mutex);
    int dataSize = ProcessedAeData.size();
    if (dataSize < 2) return image; // 如果数据不足，直接返回空白图像

    double xScale = static_cast<double>(image.width() - 50) / dataSize;
    double yScale = static_cast<double>(image.height() - 50) / 2;  // Y 轴范围是 -1 到 1
    double amplification = 100.0; // 数据放大比例

    int margin = 40; // 边距
    int yAxisPosition = image.height() / 2; // Y 轴位置在中央
    int xAxisPosition = image.height() - margin; // X 轴位置

    // 绘制坐标轴
    painter.setPen(Qt::black);
    painter.drawLine(margin, yAxisPosition, image.width() - margin, yAxisPosition);  // Y轴
    painter.drawLine(margin, xAxisPosition, image.width() - margin, xAxisPosition);  // X轴

    // 标注X轴和Y轴的文字
    painter.setFont(QFont("Arial", 40)); // 增大标题字体大小
    painter.drawText(image.width() / 2 - 20, image.height() - 10, "Time (ms)");  // X轴标签
    painter.drawText(10, yAxisPosition + 50, "Amplitude");  // Y轴标签，稍微偏下

    // 设置标题

    painter.drawText(image.width() / 2 - 50, 100, "Mel声发射数据");

    // 设置亮蓝色和线条宽度
    QColor brightBlue(0, 150, 255);
    QPen pen(brightBlue);
    pen.setWidth(4);
    painter.setPen(pen);

    // 开始绘制数据线条
    for (int i = 0; i < dataSize - 1; ++i) {
        int x1 = static_cast<int>(margin + i * xScale);
        int y1 = static_cast<int>(yAxisPosition - (ProcessedAeData[i] * amplification * yScale));  // 调整Y坐标，确保负数在下面
        int x2 = static_cast<int>(margin + (i + 1) * xScale);
        int y2 = static_cast<int>(yAxisPosition - (ProcessedAeData[i + 1] * amplification * yScale));  // 调整Y坐标，确保负数在下面

        // 限制 y1 和 y2 的值在有效范围内
        y1 = std::clamp(y1, 0, image.height() - 1);
        y2 = std::clamp(y2, 0, image.height() - 1);

        // 绘制从(x1, y1)到(x2, y2)的线条
        painter.drawLine(x1, y1, x2, y2);
    }


    return image;  // 返回最终绘制好的图像
}



void PlotThread::UpDateProcessedData(const std::vector<float>& mel){

    ProcessedAeData = mel;

}
