/********************************************************************************
** Form generated from reading UI file 'Roi.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROI_H
#define UI_ROI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CRoi
{
public:
    QGroupBox *ROISettings;
    QSpinBox *OffsetXSpin;
    QSlider *HeightSlider;
    QLabel *OffsetXLabel;
    QLabel *HeightLabel;
    QSpinBox *HeightSpin;
    QSpinBox *OffsetYSpin;
    QLabel *WidthLabel;
    QSlider *WidthSlider;
    QSpinBox *WidthSpin;
    QLabel *OffsetYLabel;
    QSlider *OffsetYSlider;
    QSlider *OffsetXSlider;
    QPushButton *ROISettingClose;

    void setupUi(QDialog *CRoi)
    {
        if (CRoi->objectName().isEmpty())
            CRoi->setObjectName(QString::fromUtf8("CRoi"));
        CRoi->resize(351, 214);
        ROISettings = new QGroupBox(CRoi);
        ROISettings->setObjectName(QString::fromUtf8("ROISettings"));
        ROISettings->setGeometry(QRect(10, 10, 331, 161));
        OffsetXSpin = new QSpinBox(ROISettings);
        OffsetXSpin->setObjectName(QString::fromUtf8("OffsetXSpin"));
        OffsetXSpin->setGeometry(QRect(250, 88, 61, 24));
        HeightSlider = new QSlider(ROISettings);
        HeightSlider->setObjectName(QString::fromUtf8("HeightSlider"));
        HeightSlider->setGeometry(QRect(109, 58, 131, 20));
        HeightSlider->setInputMethodHints(Qt::ImhNone);
        HeightSlider->setOrientation(Qt::Horizontal);
        HeightSlider->setInvertedAppearance(false);
        HeightSlider->setInvertedControls(false);
        HeightSlider->setTickPosition(QSlider::NoTicks);
        OffsetXLabel = new QLabel(ROISettings);
        OffsetXLabel->setObjectName(QString::fromUtf8("OffsetXLabel"));
        OffsetXLabel->setGeometry(QRect(20, 94, 91, 16));
        HeightLabel = new QLabel(ROISettings);
        HeightLabel->setObjectName(QString::fromUtf8("HeightLabel"));
        HeightLabel->setGeometry(QRect(20, 59, 91, 16));
        HeightSpin = new QSpinBox(ROISettings);
        HeightSpin->setObjectName(QString::fromUtf8("HeightSpin"));
        HeightSpin->setGeometry(QRect(250, 53, 61, 24));
        OffsetYSpin = new QSpinBox(ROISettings);
        OffsetYSpin->setObjectName(QString::fromUtf8("OffsetYSpin"));
        OffsetYSpin->setGeometry(QRect(250, 123, 61, 24));
        WidthLabel = new QLabel(ROISettings);
        WidthLabel->setObjectName(QString::fromUtf8("WidthLabel"));
        WidthLabel->setGeometry(QRect(20, 24, 91, 16));
        WidthSlider = new QSlider(ROISettings);
        WidthSlider->setObjectName(QString::fromUtf8("WidthSlider"));
        WidthSlider->setGeometry(QRect(110, 23, 131, 20));
        WidthSlider->setInputMethodHints(Qt::ImhNone);
        WidthSlider->setSingleStep(4);
        WidthSlider->setOrientation(Qt::Horizontal);
        WidthSlider->setInvertedAppearance(false);
        WidthSlider->setInvertedControls(false);
        WidthSlider->setTickPosition(QSlider::NoTicks);
        WidthSpin = new QSpinBox(ROISettings);
        WidthSpin->setObjectName(QString::fromUtf8("WidthSpin"));
        WidthSpin->setGeometry(QRect(250, 18, 61, 24));
        OffsetYLabel = new QLabel(ROISettings);
        OffsetYLabel->setObjectName(QString::fromUtf8("OffsetYLabel"));
        OffsetYLabel->setGeometry(QRect(20, 129, 91, 16));
        OffsetYSlider = new QSlider(ROISettings);
        OffsetYSlider->setObjectName(QString::fromUtf8("OffsetYSlider"));
        OffsetYSlider->setGeometry(QRect(109, 128, 131, 20));
        OffsetYSlider->setInputMethodHints(Qt::ImhNone);
        OffsetYSlider->setOrientation(Qt::Horizontal);
        OffsetYSlider->setInvertedAppearance(false);
        OffsetYSlider->setInvertedControls(false);
        OffsetYSlider->setTickPosition(QSlider::NoTicks);
        OffsetXSlider = new QSlider(ROISettings);
        OffsetXSlider->setObjectName(QString::fromUtf8("OffsetXSlider"));
        OffsetXSlider->setGeometry(QRect(110, 93, 131, 20));
        OffsetXSlider->setInputMethodHints(Qt::ImhNone);
        OffsetXSlider->setSingleStep(4);
        OffsetXSlider->setOrientation(Qt::Horizontal);
        OffsetXSlider->setInvertedAppearance(false);
        OffsetXSlider->setInvertedControls(false);
        OffsetXSlider->setTickPosition(QSlider::NoTicks);
        ROISettingClose = new QPushButton(CRoi);
        ROISettingClose->setObjectName(QString::fromUtf8("ROISettingClose"));
        ROISettingClose->setGeometry(QRect(200, 180, 131, 25));
        QWidget::setTabOrder(WidthSlider, WidthSpin);
        QWidget::setTabOrder(WidthSpin, HeightSlider);
        QWidget::setTabOrder(HeightSlider, HeightSpin);
        QWidget::setTabOrder(HeightSpin, OffsetXSlider);
        QWidget::setTabOrder(OffsetXSlider, OffsetXSpin);
        QWidget::setTabOrder(OffsetXSpin, OffsetYSlider);
        QWidget::setTabOrder(OffsetYSlider, OffsetYSpin);
        QWidget::setTabOrder(OffsetYSpin, ROISettingClose);

        retranslateUi(CRoi);

        QMetaObject::connectSlotsByName(CRoi);
    } // setupUi

    void retranslateUi(QDialog *CRoi)
    {
        CRoi->setWindowTitle(QApplication::translate("CRoi", "ROISettings", nullptr));
        ROISettings->setTitle(QApplication::translate("CRoi", "ROI Settings", nullptr));
        OffsetXLabel->setText(QApplication::translate("CRoi", "OffsetX", nullptr));
        HeightLabel->setText(QApplication::translate("CRoi", "Height", nullptr));
        WidthLabel->setText(QApplication::translate("CRoi", "Width", nullptr));
        OffsetYLabel->setText(QApplication::translate("CRoi", "OffsetY", nullptr));
        ROISettingClose->setText(QApplication::translate("CRoi", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CRoi: public Ui_CRoi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROI_H
