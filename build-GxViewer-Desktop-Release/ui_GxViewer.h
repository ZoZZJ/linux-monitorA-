/********************************************************************************
** Form generated from reading UI file 'GxViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GXVIEWER_H
#define UI_GXVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CGxViewer
{
public:
    QVBoxLayout *verticalLayout_6;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *VendorName;
    QLabel *ModelName;
    QLabel *SerialNumber;
    QLabel *DeviceVersion;
    QLabel *ImageLabel;
    QHBoxLayout *horizontalLayout_6;
    QLabel *AcqFrameRateLabel;
    QLabel *ShowFrameRateLabel;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *Camera_Select;
    QVBoxLayout *verticalLayout_3;
    QPushButton *UpdateDeviceList;
    QComboBox *DeviceList;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *OpenDevice;
    QPushButton *CloseDevice;
    QGroupBox *Capture_Control;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *StartAcquisition;
    QPushButton *StopAcquisition;
    QHBoxLayout *horizontalLayout;
    QLabel *PixelFormatLabel;
    QComboBox *PixelFormat;
    QHBoxLayout *horizontalLayout_2;
    QLabel *TriggerModeLabel_;
    QComboBox *TriggerMode;
    QHBoxLayout *horizontalLayout_3;
    QLabel *TriggerSourceLabel;
    QComboBox *TriggerSource;
    QPushButton *TriggerSoftWare;
    QGroupBox *Other_Control;
    QVBoxLayout *verticalLayout;
    QPushButton *ROISettings;
    QPushButton *FrameRateControl;
    QPushButton *ExposureGain;
    QPushButton *WhiteBalance;
    QPushButton *ImageImprovement;
    QPushButton *UserSetControl;

    void setupUi(QWidget *CGxViewer)
    {
        if (CGxViewer->objectName().isEmpty())
            CGxViewer->setObjectName(QString::fromUtf8("CGxViewer"));
        CGxViewer->resize(1384, 810);
        verticalLayout_6 = new QVBoxLayout(CGxViewer);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        widget = new QWidget(CGxViewer);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        horizontalLayout_8 = new QHBoxLayout(widget);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        VendorName = new QLabel(widget);
        VendorName->setObjectName(QString::fromUtf8("VendorName"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(VendorName->sizePolicy().hasHeightForWidth());
        VendorName->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(8);
        VendorName->setFont(font);

        horizontalLayout_7->addWidget(VendorName);

        ModelName = new QLabel(widget);
        ModelName->setObjectName(QString::fromUtf8("ModelName"));
        ModelName->setFont(font);

        horizontalLayout_7->addWidget(ModelName);

        SerialNumber = new QLabel(widget);
        SerialNumber->setObjectName(QString::fromUtf8("SerialNumber"));
        SerialNumber->setMaximumSize(QSize(500, 16));
        SerialNumber->setFont(font);

        horizontalLayout_7->addWidget(SerialNumber);

        DeviceVersion = new QLabel(widget);
        DeviceVersion->setObjectName(QString::fromUtf8("DeviceVersion"));
        DeviceVersion->setFont(font);

        horizontalLayout_7->addWidget(DeviceVersion);


        verticalLayout_5->addLayout(horizontalLayout_7);

        ImageLabel = new QLabel(widget);
        ImageLabel->setObjectName(QString::fromUtf8("ImageLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ImageLabel->sizePolicy().hasHeightForWidth());
        ImageLabel->setSizePolicy(sizePolicy2);
        ImageLabel->setMinimumSize(QSize(1200, 700));
        ImageLabel->setMaximumSize(QSize(2400, 1600));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        QBrush brush3(QColor(170, 170, 170, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush4(QColor(255, 255, 220, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush5(QColor(0, 0, 0, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        QBrush brush6(QColor(0, 0, 0, 128));
        brush6.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush6);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush7(QColor(0, 0, 0, 128));
        brush7.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush7);
#endif
        ImageLabel->setPalette(palette);
        ImageLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_5->addWidget(ImageLabel);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        AcqFrameRateLabel = new QLabel(widget);
        AcqFrameRateLabel->setObjectName(QString::fromUtf8("AcqFrameRateLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(AcqFrameRateLabel->sizePolicy().hasHeightForWidth());
        AcqFrameRateLabel->setSizePolicy(sizePolicy3);
        AcqFrameRateLabel->setFont(font);

        horizontalLayout_6->addWidget(AcqFrameRateLabel);

        ShowFrameRateLabel = new QLabel(widget);
        ShowFrameRateLabel->setObjectName(QString::fromUtf8("ShowFrameRateLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(ShowFrameRateLabel->sizePolicy().hasHeightForWidth());
        ShowFrameRateLabel->setSizePolicy(sizePolicy4);
        ShowFrameRateLabel->setFont(font);

        horizontalLayout_6->addWidget(ShowFrameRateLabel);


        verticalLayout_5->addLayout(horizontalLayout_6);

        verticalLayout_5->setStretch(1, 1);

        horizontalLayout_8->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        Camera_Select = new QGroupBox(widget);
        Camera_Select->setObjectName(QString::fromUtf8("Camera_Select"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(Camera_Select->sizePolicy().hasHeightForWidth());
        Camera_Select->setSizePolicy(sizePolicy5);
        verticalLayout_3 = new QVBoxLayout(Camera_Select);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        UpdateDeviceList = new QPushButton(Camera_Select);
        UpdateDeviceList->setObjectName(QString::fromUtf8("UpdateDeviceList"));

        verticalLayout_3->addWidget(UpdateDeviceList);

        DeviceList = new QComboBox(Camera_Select);
        DeviceList->setObjectName(QString::fromUtf8("DeviceList"));
        DeviceList->setMouseTracking(false);

        verticalLayout_3->addWidget(DeviceList);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        OpenDevice = new QPushButton(Camera_Select);
        OpenDevice->setObjectName(QString::fromUtf8("OpenDevice"));

        horizontalLayout_5->addWidget(OpenDevice);

        CloseDevice = new QPushButton(Camera_Select);
        CloseDevice->setObjectName(QString::fromUtf8("CloseDevice"));

        horizontalLayout_5->addWidget(CloseDevice);


        verticalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout_4->addWidget(Camera_Select);

        Capture_Control = new QGroupBox(widget);
        Capture_Control->setObjectName(QString::fromUtf8("Capture_Control"));
        Capture_Control->setEnabled(true);
        sizePolicy5.setHeightForWidth(Capture_Control->sizePolicy().hasHeightForWidth());
        Capture_Control->setSizePolicy(sizePolicy5);
        verticalLayout_2 = new QVBoxLayout(Capture_Control);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        StartAcquisition = new QPushButton(Capture_Control);
        StartAcquisition->setObjectName(QString::fromUtf8("StartAcquisition"));

        horizontalLayout_4->addWidget(StartAcquisition);

        StopAcquisition = new QPushButton(Capture_Control);
        StopAcquisition->setObjectName(QString::fromUtf8("StopAcquisition"));

        horizontalLayout_4->addWidget(StopAcquisition);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        PixelFormatLabel = new QLabel(Capture_Control);
        PixelFormatLabel->setObjectName(QString::fromUtf8("PixelFormatLabel"));

        horizontalLayout->addWidget(PixelFormatLabel);

        PixelFormat = new QComboBox(Capture_Control);
        PixelFormat->setObjectName(QString::fromUtf8("PixelFormat"));
        PixelFormat->setEditable(false);

        horizontalLayout->addWidget(PixelFormat);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        TriggerModeLabel_ = new QLabel(Capture_Control);
        TriggerModeLabel_->setObjectName(QString::fromUtf8("TriggerModeLabel_"));

        horizontalLayout_2->addWidget(TriggerModeLabel_);

        TriggerMode = new QComboBox(Capture_Control);
        TriggerMode->setObjectName(QString::fromUtf8("TriggerMode"));

        horizontalLayout_2->addWidget(TriggerMode);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        TriggerSourceLabel = new QLabel(Capture_Control);
        TriggerSourceLabel->setObjectName(QString::fromUtf8("TriggerSourceLabel"));

        horizontalLayout_3->addWidget(TriggerSourceLabel);

        TriggerSource = new QComboBox(Capture_Control);
        TriggerSource->setObjectName(QString::fromUtf8("TriggerSource"));

        horizontalLayout_3->addWidget(TriggerSource);


        verticalLayout_2->addLayout(horizontalLayout_3);

        TriggerSoftWare = new QPushButton(Capture_Control);
        TriggerSoftWare->setObjectName(QString::fromUtf8("TriggerSoftWare"));

        verticalLayout_2->addWidget(TriggerSoftWare);


        verticalLayout_4->addWidget(Capture_Control);

        Other_Control = new QGroupBox(widget);
        Other_Control->setObjectName(QString::fromUtf8("Other_Control"));
        sizePolicy5.setHeightForWidth(Other_Control->sizePolicy().hasHeightForWidth());
        Other_Control->setSizePolicy(sizePolicy5);
        verticalLayout = new QVBoxLayout(Other_Control);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ROISettings = new QPushButton(Other_Control);
        ROISettings->setObjectName(QString::fromUtf8("ROISettings"));

        verticalLayout->addWidget(ROISettings);

        FrameRateControl = new QPushButton(Other_Control);
        FrameRateControl->setObjectName(QString::fromUtf8("FrameRateControl"));

        verticalLayout->addWidget(FrameRateControl);

        ExposureGain = new QPushButton(Other_Control);
        ExposureGain->setObjectName(QString::fromUtf8("ExposureGain"));
        ExposureGain->setEnabled(true);

        verticalLayout->addWidget(ExposureGain);

        WhiteBalance = new QPushButton(Other_Control);
        WhiteBalance->setObjectName(QString::fromUtf8("WhiteBalance"));
        WhiteBalance->setEnabled(true);

        verticalLayout->addWidget(WhiteBalance);

        ImageImprovement = new QPushButton(Other_Control);
        ImageImprovement->setObjectName(QString::fromUtf8("ImageImprovement"));

        verticalLayout->addWidget(ImageImprovement);

        UserSetControl = new QPushButton(Other_Control);
        UserSetControl->setObjectName(QString::fromUtf8("UserSetControl"));

        verticalLayout->addWidget(UserSetControl);


        verticalLayout_4->addWidget(Other_Control);


        horizontalLayout_8->addLayout(verticalLayout_4);

        horizontalLayout_8->setStretch(0, 4);
        horizontalLayout_8->setStretch(1, 1);

        verticalLayout_6->addWidget(widget);


        retranslateUi(CGxViewer);

        QMetaObject::connectSlotsByName(CGxViewer);
    } // setupUi

    void retranslateUi(QWidget *CGxViewer)
    {
        CGxViewer->setWindowTitle(QApplication::translate("CGxViewer", "Form", nullptr));
        VendorName->setText(QApplication::translate("CGxViewer", "<No Device Opened>", nullptr));
        ModelName->setText(QString());
        SerialNumber->setText(QString());
        DeviceVersion->setText(QString());
        ImageLabel->setText(QString());
        AcqFrameRateLabel->setText(QApplication::translate("CGxViewer", "Frame NUM: 0   Acq. FPS: 0.0      ", nullptr));
        ShowFrameRateLabel->setText(QApplication::translate("CGxViewer", "Disp. FPS:0.0   ", nullptr));
        Camera_Select->setTitle(QApplication::translate("CGxViewer", "Camera Select", nullptr));
        UpdateDeviceList->setText(QApplication::translate("CGxViewer", "\346\233\264\346\226\260\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        OpenDevice->setText(QApplication::translate("CGxViewer", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        CloseDevice->setText(QApplication::translate("CGxViewer", "\345\205\263\351\227\255\347\233\270\346\234\272", nullptr));
        Capture_Control->setTitle(QApplication::translate("CGxViewer", "\346\215\225\350\216\267\346\216\247\345\210\266", nullptr));
        StartAcquisition->setText(QApplication::translate("CGxViewer", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        StopAcquisition->setText(QApplication::translate("CGxViewer", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        PixelFormatLabel->setText(QApplication::translate("CGxViewer", "\344\275\215\345\233\276\346\240\274\345\274\217", nullptr));
        TriggerModeLabel_->setText(QApplication::translate("CGxViewer", "\350\247\246\345\217\221\346\250\241\345\274\217", nullptr));
        TriggerSourceLabel->setText(QApplication::translate("CGxViewer", "\350\247\246\345\217\221\347\261\273\345\236\213", nullptr));
        TriggerSoftWare->setText(QApplication::translate("CGxViewer", "\350\275\257\344\273\266\350\247\246\345\217\221", nullptr));
        Other_Control->setTitle(QApplication::translate("CGxViewer", "\345\205\266\344\273\226\346\216\247\345\210\266", nullptr));
        ROISettings->setText(QApplication::translate("CGxViewer", "ROI\350\256\276\345\256\232", nullptr));
        FrameRateControl->setText(QApplication::translate("CGxViewer", "\345\270\247\346\225\260\346\216\247\345\210\266", nullptr));
        ExposureGain->setText(QApplication::translate("CGxViewer", "Exposure && Gain", nullptr));
        WhiteBalance->setText(QApplication::translate("CGxViewer", "\347\231\275\345\271\263\350\241\241", nullptr));
        ImageImprovement->setText(QApplication::translate("CGxViewer", "\345\233\276\345\203\217\346\224\271\345\226\204", nullptr));
        UserSetControl->setText(QApplication::translate("CGxViewer", "\350\207\252\345\256\232\344\271\211\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CGxViewer: public Ui_CGxViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GXVIEWER_H
