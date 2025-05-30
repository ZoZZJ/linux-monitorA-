#include "control_interface.h"
#include "ui_control_interface.h"


//队列容量被初始化为100
control_interface::control_interface(QWidget *parent): QMainWindow(parent),
    MainUi(new Ui::control_interface),videoQueue(3),g_ProcessedAeData(3000),AeRxQueue(3000),
    PProvider(new ProbabilityProvider(this)),FControllerThread(new FuzzyController(PProvider,this))
{
    qRegisterMetaType<QPair<int, float>>("QPair<int, float>");
    qRegisterMetaType<Probabilities>("Probabilities");

    MainUi->setupUi(this);
    qDebug()<<"创建主界面。。。";
    //控件部分-------------------------------------------------------------------------------------------------------
    //控件部分-------------------------------------------------------------------------------------------------------

    MainUi->CameraToolButton->setDefaultAction(MainUi->CameraAction);
    MainUi->XYtoolButton->setDefaultAction(MainUi->actionXY);



    ImDockWidget = new ImageDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, ImDockWidget); // 将 Dock Widget 添加到右侧
    ImDockWidget->hide(); // 默认隐藏

    MainUi->MonitorTab->setCurrentIndex(0);
    MainUi->AeLabel->setScaledContents(true);//图像根据widget的大小缩放
    MainUi->AeProcessoLabel->setScaledContents(true);
    MainUi->Visonlabel->setScaledContents(true);
    MainUi->RealTImagelabel->setScaledContents(true);//图像根据widget的大小缩放

    connect(MainUi->Visonlabel, &DoubleClickLabel::doubleClicked, this, [=]() {
        MainUi->MonitorTab->setCurrentIndex(3);
    });


    connect(MainUi->MonitorTab, &QTabWidget::currentChanged, this, &control_interface::onTabChanged);


    connect(MainUi->AeLabel, &DoubleClickLabel::doubleClicked, this, &control_interface::OpenAeDock);
    connect(MainUi->AeLabel, &DoubleClickLabel::doubleClicked, this, &control_interface::OpenAeDock);

    connect(ImDockWidget, &ImageDockWidget::visibilityChanged, this, [this](bool visible) {

        DockOn = visible;
    });
    //滑动条
    connect(MainUi->ConfidenceSlider, &MySlider::valueChanged, MainUi->spinBox, &QSpinBox::setValue);
    connect(MainUi->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), MainUi->ConfidenceSlider, &MySlider::setValue);

    //Tab放在左侧：
    MainUi->MonitorTab->setTabPosition(QTabWidget::West);
    //线程部分----------------------------------------------------------------------------------------------------------------
    //线程部分----------------------------------------------------------------------------------------------------------------
    cameraThread = new CameraCaptureThread(videoQueue, this);
    //AeRxThread  = new SignalAcquisitionThread(AeRxQueue,this);
    AePlotThread = new PlotThread(AeRxQueue,g_ProcessedAeData,this);
    DataProThread = new DataProcessingThread(AeRxQueue,g_ProcessedAeData,this);

    udpServer = new UdpServer(8888, AeRxQueue); //udp接收声发射线程
    AeUdpReciveThread = new QThread;
    udpServer->moveToThread(AeUdpReciveThread);

    connect(this, &control_interface::udpStopSignal, udpServer, &UdpServer::stopUdp);

    connect(AeUdpReciveThread, &QThread::started, udpServer, &UdpServer::startConnect);


    //GX相机获取线程
    // 假设 mainWindow 是你的主窗口，cameraTab 是原来的 tab 页面

    int tabIndex = MainUi->MonitorTab->addTab(&CGxViewer::getInstance(), "");  // 添加单例对象
    MainUi->MonitorTab->setTabIcon(tabIndex,QIcon(":photos/camera.png"));

    int tabIndex2 = MainUi->MonitorTab->addTab(&XyPlatform::getInstance(), "");  // 添加单例对象
    MainUi->MonitorTab->setTabIcon(tabIndex2,QIcon(":photos/XYplatform.png"));

    connect(cameraThread, &CameraCaptureThread::messageSignal, this, &control_interface::addMessage);
    connect(cameraThread, &CameraCaptureThread::ImageSignal, this, &control_interface::LoadImageUI);

    connect(AePlotThread, &PlotThread::AePlotMsgSignal, this, &control_interface::addMessage);
    connect(DataProThread, &DataProcessingThread::messageSignal, this, &control_interface::addMessage);
    connect(udpServer, &UdpServer::messageSignal, this, &control_interface::addMessage);
    //connect(DataProThread, &DataProcessingThread::SendDataToPlot,AePlotThread, &PlotThread::UpDateProcessedData);//更新mel图ui显示

    connect(AePlotThread, &PlotThread::plotReady, this, &control_interface::updatePlot);
    connect(AePlotThread, &PlotThread::plotReadyone, this, &control_interface::updatePlotone);
    connect(this, &control_interface::ProcessToggling, AePlotThread, &PlotThread::ProcessToggle);
    connect(&m_VisionTimer, &QTimer::timeout, this,  &control_interface::onVisionTimerTimeout);




///控件部分
    MainUi->MsgTextEdit->setReadOnly(true);  // 设置为只读
    MainUi->MsgTextEdit->setWordWrapMode(QTextOption::WordWrap); // 自动换行
    //MainUi->MsgTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); // 设置滚动条
    MainUi->MsgTextEdit->setVerticalScrollBar(MainUi->MessageSlide);// 设置滚动条
    // 控制按钮
    //qDebug()<<"step2。。。";
    //启动视觉ui更新定时器
    m_VisionTimer.start(25);
   // qDebug() << "m_VisionTimer started? " << m_VisionTimer.isActive();


    setupInferenceProcessor();

}


control_interface::~control_interface()
{
    delete MainUi;
    if (cameraThread->isRunning()) {
        cameraThread->requestInterruption(); // 请求中断线程
        cameraThread->wait(); // 等待线程结束
    }
}

void control_interface::onVisionTimerTimeout()
{
    static int imageIndex = 1;  // 图片编号，从1开始
    static int missingCount = 0;  // 图片编号，从1开始
    if (!videoQueue.isEmpty()) {
        //更新为最近的一张图片
        QPixmap pixmap = videoQueue[videoQueue.size()-1];

        QSize labelSize = MainUi->Visonlabel->size();
        QPixmap scaledPixmap = pixmap.scaled(labelSize, Qt::KeepAspectRatioByExpanding);
        // 设置调整后的 Pixmap
        MainUi->Visonlabel->setPixmap(scaledPixmap);
    }
    QString imagePath = QString("/home/jetson/Monitor-Linux-monitor0306/VisionDataset/Left/%1.png").arg(imageIndex);
    if (QFile::exists(imagePath)) {
        QPixmap pixmap(imagePath);
        videoQueue.enqueue(pixmap);
        imageIndex++;  // 下一张图编号+1
        missingCount = 0;  // 重置连续未找到计数
    }
    else {
           missingCount++;    // 连续未找到计数加1

           if (missingCount >= 20) {
               imageIndex = 1;    // 超过20次未找到，重置索引
               missingCount = 0;  // 重置计数
           }
       }
}

//void control_interface::EnqueueOnePicture(){

//    QImage* image = viewer->GetShowImageFromAcquisionThread();

//    QPixmap pixmap = QPixmap::fromImage(*image);

//    videoQueue.enqueue(pixmap);
//}



//暂时弃用
void control_interface::LoadImageUI(QPixmap pixmap)
{
       //qDebug()<<"加载图形至ui......" ;
        MainUi->Visonlabel->setPixmap(pixmap);
        MainUi->RealTImagelabel->setPixmap(pixmap);
}

void control_interface::on_VideoButton_clicked()
{
    if (cameraOn) {
        // 停止线程
        if (cameraThread->isRunning()) {
            m_VisionTimer.stop();
            cameraThread->requestInterruption(); // 请求中断
            cameraThread->wait(); // 等待线程执行完

        }
        CGxViewer::getInstance().StopAcquisition_clicked_slot();
        //killTimer(Camera_timerId);

        MainUi->Visonlabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        MainUi->Visonlabel->setText("相机未开启");
        cameraOn = false; // 更新相机状态
    } else {
        // 如果线程已中断，直接复用现有线程
        if (!cameraThread->isRunning()) {

            cameraThread->start(); // 启动线程
            m_VisionTimer.start(50);
            //Camera_timerId = startTimer(60);
        }
        CGxViewer::getInstance().StartAcquisition_clicked_slot();
        MainUi->VideoButton->setText("关闭相机");
        cameraOn = true; // 更新相机状态
    }
}


void control_interface::on_AEButton_clicked()
{
    MainUi->MystatusBar->showMessage("按钮已点击！", 2000);
    if (AeON) {
        // 停止线程
        if (AeUdpReciveThread->isRunning()) {
            //udpServer->stopUdp();
            AeUdpReciveThread->quit(); // 请求退出
            AeUdpReciveThread->wait(); // 等待线程执行完
        }
        if (AePlotThread->isRunning()) {
            emit udpStopSignal();
            AePlotThread->requestInterruption(); // 请求中断

            AePlotThread->wait(); // 等待线程执行完
        }

        //killTimer(Camera_timerId);
        MainUi->AEButton->setText("接收声发射信号");
        MainUi->AeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        MainUi->AeLabel->setText("声发射未开启");
        AeON = false; // 更新相机状态
    } else {
        // 如果线程已中断，直接复用现有线程
        if (!AeUdpReciveThread->isRunning()) {

            AeUdpReciveThread->start(); // 启动线程
        }
        if (!AePlotThread->isRunning()) {

            AePlotThread->start(); // 启动线程
        }
        MainUi->AEButton->setText("关闭声发射接收");
        AeON = true; // 更新相机状态
    }
}

void control_interface::FullScreen(){

    this->showFullScreen();
}


void control_interface::addMessage(const QString &message) {

    QString time = QDateTime::currentDateTime().toString("hh:mm:ss"); // 时间戳 //yyyy-MM-dd
    MainUi->MsgTextEdit->append(time + " - " + message);  // 打印时间和消息到文本框

}

void control_interface::updatePlot(const QImage &image,const QImage &image2) {
    // 在UI上更新图片，比如用 QLabel 来展示
    MainUi->AeLabel->setPixmap(QPixmap::fromImage(image));
    MainUi->AeProcessoLabel->setPixmap(QPixmap::fromImage(image2));
}

void control_interface::updatePlotone(const QImage &image) {

    QPixmap pixmap = QPixmap::fromImage(image);

    QSize labelSize = MainUi->Visonlabel->size();

    QPixmap scaledPixmap = pixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    MainUi->Visonlabel->setPixmap(scaledPixmap);

    if (!DockOn) {
        MainUi->AeLabel->setPixmap(QPixmap::fromImage(image));
    } else {
        ImDockWidget->setImage(QPixmap::fromImage(image));
    }
}


void control_interface::openCameraProgram() {
    //QProcess::startDetached("path/to/your/program");


    qDebug()<<"打开相机设置中";
    addMessage("打开相机设置中");
}

void control_interface::on_FullScreenToggle_clicked()
{
//    if (IsFullScreen) {
//        qDebug() << "缩小";
//        MainUi->InferenceWidget->setWindowFlags(Qt::SubWindow);
//        MainUi->InferenceWidget->showNormal();
//        MainUi->RealTImagelabel->showNormal();
//        MainUi->RealTImagelabel->restoreGeometry(savedGeometry); // 恢复之前保存的窗口位置和大小
//    } else {
//        qDebug() << "最大化";
//        MainUi->InferenceWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
//        MainUi->InferenceWidget->showFullScreen();
//        savedGeometry = MainUi->RealTImagelabel->saveGeometry(); // 保存当前窗口的位置和大小
//        MainUi->RealTImagelabel->showFullScreen(); // 切换为全屏
//    }
//    IsFullScreen = !IsFullScreen;
//    // 立即调整 QLabel 大小
//    MainUi->RealTImagelabel->resize(MainUi->InferenceWidget->size());
}



void control_interface::on_MsgClrButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("确认清空"), tr("确定要清空消息吗？"),
                                  QMessageBox::Yes | QMessageBox::No);

    // 根据用户选择的按钮执行操作
    if (reply == QMessageBox::Yes) {
        MainUi->MsgTextEdit->clear(); // 清空消息
    }

}


void control_interface::on_ModelSelectButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择模型文件"), "", tr("模型文件 (*.engine)"));

    if (!filePath.isEmpty()) {

        QMessageBox::information(this, tr("选择的模型文件"), filePath);

        InferenceProcessor &processor = InferenceProcessor::getInstance();


        processor.setEnginePath(filePath.toStdString());
        MainUi->modelPathLineEdit->setText(filePath);
        processor.setEnginePath(filePath.toStdString());

    }
}


void control_interface::on_AEProcButton_clicked()
{

    MainUi->MystatusBar->showMessage("数据处理按钮已点击！", 2000);
    if (AeProcessON) {
        // 停止线程
        emit ProcessToggling(false);
        if (DataProThread->isRunning()) {
            DataProThread->requestInterruption(); // 请求中断
            DataProThread->wait(); // 等待线程执行完
        }

        MainUi->AEProcButton->setText("开启声发信号处理");
        MainUi->AeProcessoLabel ->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        MainUi->AeProcessoLabel->setText("声发射处理未开启");
        AeProcessON = false;
        //g_ProcessedAeData.clear();
        AeRxQueue.clear();
    } else {
        // 如果线程已中断，直接复用现有线程
        if (!DataProThread->isRunning()) {

            emit ProcessToggling(true);

            DataProThread->start(); // 启动线程

        }
        MainUi->AEProcButton->setText("关闭声发射信号处理");
        AeProcessON = true;
    }

}

void control_interface::onTabChanged(int index) {
    if (index == 3) {
        openCameraProgram(); // 调用相机的程序
    }
}

void control_interface::OpenAeDock(){
    ImDockWidget->show(); // 显示 Dock Widget
}

void control_interface::on_FileSaveAction_triggered()
{
    saveToFile();
}

void control_interface::saveToFile() {
    // 打开文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(this, "保存文件", "", "CSV文件 (*.csv)");
    if (fileName.isEmpty()) {
        return;  // 如果用户没有选择文件，则返回
    }

    // 打开文件进行写入
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法保存文件！");
        return;
    }

    // 创建一个 QTextStream 来写入文件，并指定 UTF-8 编码
    file.write("\xEF\xBB\xBF"); // 写入 BOM，确保文件被正确识别为 UTF-8 编码

    // 创建 QTextStream 并与文件关联
    QTextStream out(&file);
    out.setAutoDetectUnicode(true);  // 自动检测Unicode编码

    // 获取 QTableWidget 的行数和列数
    int rowCount = MainUi->InfereceTableWidget->rowCount();
    int columnCount = MainUi->InfereceTableWidget->columnCount();

    // 遍历表格中的每一行
    for (int row = 0; row < rowCount; ++row) {
        QStringList rowData;
        // 遍历每一列
        for (int col = 0; col < columnCount; ++col) {
            // 获取当前单元格的文本内容，若单元格为空，设置为 ""
            QString cellText = MainUi->InfereceTableWidget->item(row, col) ?
                                   MainUi->InfereceTableWidget->item(row, col)->text() : "";
            rowData.append(cellText);
        }
        // 将行数据按逗号连接，并写入到文件
        out << rowData.join(",") << "\n";
    }

    file.close();  // 关闭文件

    QMessageBox::information(this, "成功", "文件已成功保存！");
}


void control_interface::dealClsResult(const Probabilities& probs) {
    static int ShowImageCnt = 0;
    static int lastClassIndex = -1;
    ShowImageCnt++;
    //发给平台移动步长控制器dy
    PProvider->enqueueProbabilities(probs);

    int classIndex = 0;
    double maxProbs = probs.left;
    if (probs.none > maxProbs) {
        maxProbs = probs.none;
        classIndex = 1;
    }
    if (probs.right > maxProbs) {
        maxProbs = probs.right;
        classIndex = 2;
    }

    if(maxProbs<ConfidenceThreshold){
        return;
    }

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime newDateTime = currentDateTime.addMonths(-1);
    QString  currentTime = newDateTime.toString("MM-dd HH:mm:ss");
    // 解析分类结果

    QString classification;
    switch (classIndex) {
        case 0: classification = "左偏移"; break;
        case 1: classification = "未偏移"; break;
        case 2: classification = "右偏移"; break;
        default: classification = "未知"; break;
    }

    if (ShowImageCnt == 1) {
        ShowImageCnt = 0;
        //if(classIndex != lastClassIndex){
            lastClassIndex = classIndex;
            updateImageWithLabel(classification);  // 触发 UI 更新
       // }
    }

    int row =  MainUi-> InfereceTableWidget-> rowCount();
    MainUi->InfereceTableWidget->insertRow(row);  // 插入新的一行
    MainUi->InfereceTableWidget->setItem(row, 0, new QTableWidgetItem(currentTime));
    MainUi->InfereceTableWidget->setItem(row, 1, new QTableWidgetItem(classification));
    //MainUi->InfereceTableWidget->setItem(row, 2, new QTableWidgetItem(platformStrategy));
}

void control_interface::updateImageWithLabel(const QString &classification) {
    if (MainUi->Visonlabel->pixmap() == nullptr) return;

    QPixmap pixmap = *MainUi->Visonlabel->pixmap();
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font;
    font.setBold(true);
    font.setPointSize(16);
    painter.setFont(font);
    painter.setPen(Qt::red);

    int padding = 10;
    QRect textRect(padding, padding, pixmap.width() - 2 * padding, 40);
    painter.drawText(textRect, Qt::AlignRight | Qt::AlignTop, classification);

    painter.end();
    MainUi->RealTImagelabel->setPixmap(pixmap);

}


void control_interface::setupStatusBar() {
    // 创建三个标签，用于显示相机、声发射、平台的状态
    QLabel* cameraStatusLabel = new QLabel("相机状态: 连接正常");
    QLabel* aeStatusLabel = new QLabel("声发射状态: 传输正常");
    QLabel* platformStatusLabel = new QLabel("平台状态: 连接正常");

    // 将这三个标签添加到状态栏
    MainUi->MystatusBar->addWidget(cameraStatusLabel, 1);  // 1表示占用的空间比例
    MainUi->MystatusBar->addWidget(aeStatusLabel, 1);
    MainUi->MystatusBar->addWidget(platformStatusLabel, 1);
    //MainUi->MystatusBar->setGeometry();

    // 保存标签指针以便后续更新状态
    //m_cameraStatusLabel = cameraStatusLabel;
    // m_aeStatusLabel = aeStatusLabel;
    // m_platformStatusLabel = platformStatusLabel;
}

//xy重连s
void control_interface::on_XYtoolButton_triggered(QAction *arg1)
{

}

void control_interface::setupInferenceProcessor() {

    InferenceProcessor &processor = InferenceProcessor::getInstance();


    //processor.setEnginePath("/home/jetson/Model_pth/resnet18_model_fp16.engine");

    processor.setQueue(&videoQueue);

    connect(&processor, &InferenceProcessor::sendMessage, this, &control_interface::addMessage);
    connect(&processor, &InferenceProcessor::classificationResult, this, &control_interface::dealClsResult);
}




void control_interface::on_InferenceButton_clicked()
{
     InferenceProcessor &processor = InferenceProcessor::getInstance();
     if(!processor.getProcessingStatus()){
         processor.startProcessing();
          MainUi->InferenceButton->setText("停止推理");
     }else{
         processor.stopProcessing();
          MainUi->InferenceButton->setText("开始推理");
     }

}

void control_interface::on_XyPlatformButton_clicked()
{

    if (FControllerThread->GetRunningStatus()) {
        // 停止线程
        if (FControllerThread->isRunning()) {
            //m_VisionTimer.stop();
            FControllerThread->requestInterruption(); // 请求中断
            FControllerThread->wait(); // 等待线程执行完
        }
        FuzzyControllerOn = false; // 更新相机状态
        MainUi->XyPlatformButton->setText("开启平台运动");
    } else {
        // 如果线程已中断，直接复用现有线程
        if (!FControllerThread->isRunning()) {
            std::cout<<"1:"<<std::endl;
            FControllerThread->start(); // 启动线程

        }
        MainUi->XyPlatformButton->setText("停止平台运动");
        FuzzyControllerOn = true; //
    }
}
