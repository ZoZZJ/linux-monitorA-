QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
RC_ICONS = icon1_nlH_1.ico

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#arm64 的编译宏
contains(QMAKE_HOST.arch, aarch64){
#aarch64 是编译器类型，如果不是这个编译器， 可以把.arch 替换成对应的类型
#arm 64平台


    LIBS +=  -L/home/jetson/Monitor-Linux-monitor/libmodbus/lib -lmodbus
    LIBS += -L/usr/lib/aarch64-linux-gnu -lnvinfer
    LIBS += -L/usr/lib/ -lgxiapi \
             -L/usr/local/cuda/lib64 -lcudart \
             -L/usr/lib/aarch64-linux-gnu -lnvinfer \
             -lcublas -lcudnn \
             -L/usr/lib/aarch64-linux-gnu -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

    INCLUDEPATH += /usr/local/cuda/include \
                   /usr/include/opencv4 \
                   /usr/include/opencv4/opencv2 \
                   /usr/include \
                   /home/jetson/Monitor-Linux-monitor/libmodbus/include/modbus \
                   GxViewer/include/ \
                   /usr/include/aarch64-linux-gnu \
                   /usr/include/eigen3 \
                   /usr/local/include/onnxruntime \
                   /usr/local/include/protobuf \
                   /usr/include/jsoncpp



message(": arm-64")
message("编译目标平台: $$QMAKE_HOST.arch")
}else{
message("编译目标平台: x86")
message("编译目标平台类型: $$QMAKE_HOST.arch")

win32{
    LIBS +=C:\opencv452\x64\mingw\lib\libopencv*
    LIBS +=E:\Qt\documents\monitor_app\libmodbus\lib\release\modbus.lib
    LIBS +=E:\Qt\documents\monitor_app\libmodbus\lib\release\modbus.dll
    INCLUDEPATH +=C:\opencv452\include
    INCLUDEPATH += C:\opencv452\include\opencv2
    INCLUDEPATH +=E:\Qt\documents\monitor_app\libmodbus\include
    }

    #linux平台opencv seetaface环境
unix{
    LIBS += -L/home/yahboom/OPENCV_OPT/opencv4-pc/lib -lopencv_world
    INCLUDEPATH += /home/yahboom/OPENCV_OPT/opencv4-pc/include/opencv4
    INCLUDEPATH += /home/yahboom/OPENCV_OPT/opencv4-pc/include/opencv4/opencv2
    INCLUDEPATH += /home/yahboom/OPENCV_OPT/opencv4-pc/include
    }


}



SOURCES += \
    AxisManager/JPMASManager.cpp \
    AxisManager/PlatformController.cpp \
    GxViewer/AcquisitionThread.cpp \
    GxViewer/Common.cpp \
    GxViewer/ExposureGain.cpp \
    GxViewer/Fps.cpp \
    GxViewer/FrameRateControl.cpp \
    GxViewer/GxViewer.cpp \
    GxViewer/ImageImprovement.cpp \
    GxViewer/Roi.cpp \
    GxViewer/UserSetControl.cpp \
    GxViewer/WhiteBalance.cpp \
    DataProcessingThread.cpp \
    MyWidgets/custabbar.cpp \
    MyWidgets/doubleclicklabel.cpp \
    MyWidgets/myslider.cpp \
    NeuralNetThread/InferenceProcessor.cpp \
    NeuralNetThread/TensorRTClassifier.cpp \
    PlotThread.cpp \
    cameracapturethread.cpp \
    main.cpp \
    control_interface.cpp \
    udpserver.cpp \
    xyplatform.cpp

HEADERS += \
    AxisManager/JPMASManager.h \
    AxisManager/PlatformController.h \
    CircularQueue.h \
    GxViewer/AcquisitionThread.h \
    GxViewer/Common.h \
    GxViewer/ExposureGain.h \
    GxViewer/Fps.h \
    GxViewer/FrameRateControl.h \
    GxViewer/GxViewer.h \
    GxViewer/ImageImprovement.h \
    GxViewer/Roi.h \
    GxViewer/UserSetControl.h \
    GxViewer/WhiteBalance.h \
    GxViewer/include/DxImageProc.h \
    GxViewer/include/GxIAPI.h \
    DataProcessingThread.h \
    MyWidgets/custabbar.h \
    MyWidgets/doubleclicklabel.h \
    MyWidgets/myslider.h \
    NeuralNetThread/InferenceProcessor.h \
    NeuralNetThread/TensorRTClassifier.h \
    PlotThread.h \
    cameracapturethread.h \
    control_interface.h \
    inferthread.h \
    udpserver.h \
    xyplatform.h

FORMS += \
    GxViewer/ExposureGain.ui \
    GxViewer/FrameRateControl.ui \
    GxViewer/GxViewer.ui \
    GxViewer/ImageImprovement.ui \
    GxViewer/Roi.ui \
    GxViewer/UserSetControl.ui \
    GxViewer/WhiteBalance.ui \
    ui/control_interface.ui \
    ui/xyplatformUI.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    photoSource/minus.png

RESOURCES += \
    resources.qrc \

#SUBDIRS += \
#    GxViewer/GxViewer.pro

