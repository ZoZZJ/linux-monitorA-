#ifndef CONTROL_INTERFACE_H
#define CONTROL_INTERFACE_H
#include "CircularQueue.h"
#include <QMainWindow>
//#include <opencv.hpp>
#include <QTimer>
//#include "SignalAcquisitionThread.h"
#include "cameracapturethread.h"
#include "PlotThread.h"
#include "DataProcessingThread.h"
#include "udpserver.h"
#include "MyWidgets/doubleclicklabel.h"
#include "GxViewer/GxViewer.h"
#include "GxViewer/AcquisitionThread.h"

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class control_interface; }
QT_END_NAMESPACE

class control_interface : public QMainWindow
{
    Q_OBJECT

public:
    control_interface(QWidget *parent = nullptr);
    ~control_interface();
    Ui::control_interface *MainUi;

  //  void timerEvent(QTimerEvent *e);//定时器事件
    void ReadCameraDataThread();
    void addMessage(const QString &message);
    void updatePlot(const QImage &image,const QImage &image2);
    void updatePlotone(const QImage &image);




private slots:
    void on_VideoButton_clicked();

    void on_AEButton_clicked();

    void LoadImageUI(QPixmap pixmap);

    void on_FullScreenToggle_clicked();

    void on_MsgClrButton_clicked();

    void on_ModelSelectButton_clicked();

    void on_AEProcButton_clicked();

    void onTabChanged(int index); //tab的页数改变了的话执行操作

    void openCameraProgram();

    void OpenAeDock();

    void on_FileSaveAction_triggered();

    void saveToFile();

    void InfereceMessage(QString currentTime,QString classification,QString platformStrategy);

    void onVisionTimerTimeout();

    //工业相机专用槽函数
   // void EnqueueOnePicture();


signals:
    void newFrameCaptured(const QImage &frame);
    void udpStopSignal();
    void ProcessToggling(bool switch1);


private:

    //void mouseDoubleClickEvent(QMouseEvent *event) override;
    //控件-----------------------------------------------------------------------------------------
    ImageDockWidget *ImDockWidget; // 自定义的 Dock Widget

    bool DockOn = false;
    void setupStatusBar();

    //WaveformUI *Aewave;



    //线程------------------------------------------------------------------------------------------
    //摄像头
    bool IsFullScreen = false;
    //VideoCapture cap;



    CircularQueue<QPixmap> videoQueue;
    std::vector<float> g_ProcessedAeData;
    CircularQueue<float> AeRxQueue;//声发射接收队列

    QByteArray savedGeometry;  // 保存的窗口位置和大小

    CameraCaptureThread *cameraThread;
    SignalAcquisitionThread *AeRxThread;//声发射接收线程
    DataProcessingThread *DataProThread;//声发射数据处理线程





    PlotThread *AePlotThread;//声发射绘图线程
    QThread* AeUdpReciveThread;//声发射udp接收线程
    UdpServer* udpServer;

    bool cameraOn = false;
    bool AeON = false;
    bool AeProcessON = false;
    //int Camera_timerId;

    //创建定时器
    QTimer m_VisionTimer;
    void FullScreen ();

};
#endif // CONTROL_INTERFACE_H
