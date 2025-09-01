/********************************************************************************
** Form generated from reading UI file 'ExposureGain.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPOSUREGAIN_H
#define UI_EXPOSUREGAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CExposureGain
{
public:
    QGroupBox *Exposure;
    QComboBox *ExposureAuto;
    QLabel *ExposureAutoLabel;
    QLabel *ExposureTimeLabel;
    QLabel *AutoExposureTimeMax;
    QDoubleSpinBox *ExposureTimeSpin;
    QDoubleSpinBox *AutoExposureTimeMaxSpin;
    QLabel *AutoExposureTimeMinLabel;
    QDoubleSpinBox *AutoExposureTimeMinSpin;
    QPushButton *AA_Close;
    QGroupBox *Gain;
    QComboBox *GainAuto;
    QLabel *GainAutoLabel;
    QLabel *GainLabel;
    QLabel *AutoGainMaxLabel;
    QDoubleSpinBox *GainSpin;
    QDoubleSpinBox *AutoGainMaxSpin;
    QLabel *AutoGainMinLabel;
    QDoubleSpinBox *AutoGainMinSpin;
    QGroupBox *AA_Param;
    QLabel *AAROIHeightLabel;
    QLabel *AAROIOffsetYLabel;
    QSlider *AAROIHeightSlider;
    QSlider *AAROIOffsetYSlider;
    QSpinBox *AAROIHeightSpin;
    QSpinBox *AAROIOffsetYSpin;
    QLabel *AAROIOffsetXLabel;
    QSpinBox *AAROIOffsetXSpin;
    QSlider *AAROIOffsetXSlider;
    QSpinBox *AAROIWidthSpin;
    QSlider *AAROIWidthSlider;
    QLabel *AAROIWidthLabel;
    QSpinBox *ExpectedGrayValueSpin;
    QLabel *ExpectedGrayValueLabel;
    QSlider *ExpectedGrayValueSlider;

    void setupUi(QDialog *CExposureGain)
    {
        if (CExposureGain->objectName().isEmpty())
            CExposureGain->setObjectName(QString::fromUtf8("CExposureGain"));
        CExposureGain->resize(351, 541);
        CExposureGain->setMouseTracking(false);
        CExposureGain->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        Exposure = new QGroupBox(CExposureGain);
        Exposure->setObjectName(QString::fromUtf8("Exposure"));
        Exposure->setGeometry(QRect(10, 10, 331, 151));
        ExposureAuto = new QComboBox(Exposure);
        ExposureAuto->setObjectName(QString::fromUtf8("ExposureAuto"));
        ExposureAuto->setGeometry(QRect(180, 24, 131, 24));
        ExposureAuto->setEditable(false);
        ExposureAutoLabel = new QLabel(Exposure);
        ExposureAutoLabel->setObjectName(QString::fromUtf8("ExposureAutoLabel"));
        ExposureAutoLabel->setGeometry(QRect(20, 30, 121, 16));
        ExposureTimeLabel = new QLabel(Exposure);
        ExposureTimeLabel->setObjectName(QString::fromUtf8("ExposureTimeLabel"));
        ExposureTimeLabel->setGeometry(QRect(20, 60, 121, 16));
        AutoExposureTimeMax = new QLabel(Exposure);
        AutoExposureTimeMax->setObjectName(QString::fromUtf8("AutoExposureTimeMax"));
        AutoExposureTimeMax->setGeometry(QRect(20, 120, 151, 16));
        ExposureTimeSpin = new QDoubleSpinBox(Exposure);
        ExposureTimeSpin->setObjectName(QString::fromUtf8("ExposureTimeSpin"));
        ExposureTimeSpin->setGeometry(QRect(180, 54, 131, 24));
        AutoExposureTimeMaxSpin = new QDoubleSpinBox(Exposure);
        AutoExposureTimeMaxSpin->setObjectName(QString::fromUtf8("AutoExposureTimeMaxSpin"));
        AutoExposureTimeMaxSpin->setGeometry(QRect(180, 114, 131, 24));
        AutoExposureTimeMinLabel = new QLabel(Exposure);
        AutoExposureTimeMinLabel->setObjectName(QString::fromUtf8("AutoExposureTimeMinLabel"));
        AutoExposureTimeMinLabel->setGeometry(QRect(20, 90, 151, 16));
        AutoExposureTimeMinSpin = new QDoubleSpinBox(Exposure);
        AutoExposureTimeMinSpin->setObjectName(QString::fromUtf8("AutoExposureTimeMinSpin"));
        AutoExposureTimeMinSpin->setGeometry(QRect(180, 84, 131, 24));
        AA_Close = new QPushButton(CExposureGain);
        AA_Close->setObjectName(QString::fromUtf8("AA_Close"));
        AA_Close->setGeometry(QRect(200, 508, 131, 25));
        Gain = new QGroupBox(CExposureGain);
        Gain->setObjectName(QString::fromUtf8("Gain"));
        Gain->setGeometry(QRect(10, 165, 331, 151));
        GainAuto = new QComboBox(Gain);
        GainAuto->setObjectName(QString::fromUtf8("GainAuto"));
        GainAuto->setGeometry(QRect(180, 24, 131, 24));
        GainAuto->setEditable(false);
        GainAutoLabel = new QLabel(Gain);
        GainAutoLabel->setObjectName(QString::fromUtf8("GainAutoLabel"));
        GainAutoLabel->setGeometry(QRect(20, 30, 121, 16));
        GainLabel = new QLabel(Gain);
        GainLabel->setObjectName(QString::fromUtf8("GainLabel"));
        GainLabel->setGeometry(QRect(20, 60, 121, 16));
        AutoGainMaxLabel = new QLabel(Gain);
        AutoGainMaxLabel->setObjectName(QString::fromUtf8("AutoGainMaxLabel"));
        AutoGainMaxLabel->setGeometry(QRect(20, 120, 151, 16));
        GainSpin = new QDoubleSpinBox(Gain);
        GainSpin->setObjectName(QString::fromUtf8("GainSpin"));
        GainSpin->setGeometry(QRect(180, 54, 131, 24));
        AutoGainMaxSpin = new QDoubleSpinBox(Gain);
        AutoGainMaxSpin->setObjectName(QString::fromUtf8("AutoGainMaxSpin"));
        AutoGainMaxSpin->setGeometry(QRect(180, 114, 131, 24));
        AutoGainMinLabel = new QLabel(Gain);
        AutoGainMinLabel->setObjectName(QString::fromUtf8("AutoGainMinLabel"));
        AutoGainMinLabel->setGeometry(QRect(20, 90, 151, 16));
        AutoGainMinSpin = new QDoubleSpinBox(Gain);
        AutoGainMinSpin->setObjectName(QString::fromUtf8("AutoGainMinSpin"));
        AutoGainMinSpin->setGeometry(QRect(180, 84, 131, 24));
        AA_Param = new QGroupBox(CExposureGain);
        AA_Param->setObjectName(QString::fromUtf8("AA_Param"));
        AA_Param->setGeometry(QRect(10, 320, 331, 181));
        AAROIHeightLabel = new QLabel(AA_Param);
        AAROIHeightLabel->setObjectName(QString::fromUtf8("AAROIHeightLabel"));
        AAROIHeightLabel->setGeometry(QRect(20, 56, 121, 16));
        AAROIOffsetYLabel = new QLabel(AA_Param);
        AAROIOffsetYLabel->setObjectName(QString::fromUtf8("AAROIOffsetYLabel"));
        AAROIOffsetYLabel->setGeometry(QRect(20, 116, 151, 16));
        AAROIHeightSlider = new QSlider(AA_Param);
        AAROIHeightSlider->setObjectName(QString::fromUtf8("AAROIHeightSlider"));
        AAROIHeightSlider->setGeometry(QRect(180, 55, 61, 20));
        AAROIHeightSlider->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        AAROIHeightSlider->setOrientation(Qt::Orientation::Horizontal);
        AAROIHeightSlider->setInvertedAppearance(false);
        AAROIHeightSlider->setInvertedControls(false);
        AAROIHeightSlider->setTickPosition(QSlider::TickPosition::NoTicks);
        AAROIOffsetYSlider = new QSlider(AA_Param);
        AAROIOffsetYSlider->setObjectName(QString::fromUtf8("AAROIOffsetYSlider"));
        AAROIOffsetYSlider->setGeometry(QRect(180, 115, 60, 20));
        AAROIOffsetYSlider->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        AAROIOffsetYSlider->setOrientation(Qt::Orientation::Horizontal);
        AAROIOffsetYSlider->setInvertedAppearance(false);
        AAROIOffsetYSlider->setInvertedControls(false);
        AAROIOffsetYSlider->setTickPosition(QSlider::TickPosition::NoTicks);
        AAROIHeightSpin = new QSpinBox(AA_Param);
        AAROIHeightSpin->setObjectName(QString::fromUtf8("AAROIHeightSpin"));
        AAROIHeightSpin->setGeometry(QRect(250, 50, 61, 24));
        AAROIOffsetYSpin = new QSpinBox(AA_Param);
        AAROIOffsetYSpin->setObjectName(QString::fromUtf8("AAROIOffsetYSpin"));
        AAROIOffsetYSpin->setGeometry(QRect(250, 110, 61, 24));
        AAROIOffsetXLabel = new QLabel(AA_Param);
        AAROIOffsetXLabel->setObjectName(QString::fromUtf8("AAROIOffsetXLabel"));
        AAROIOffsetXLabel->setGeometry(QRect(20, 86, 151, 16));
        AAROIOffsetXSpin = new QSpinBox(AA_Param);
        AAROIOffsetXSpin->setObjectName(QString::fromUtf8("AAROIOffsetXSpin"));
        AAROIOffsetXSpin->setGeometry(QRect(250, 80, 61, 24));
        AAROIOffsetXSlider = new QSlider(AA_Param);
        AAROIOffsetXSlider->setObjectName(QString::fromUtf8("AAROIOffsetXSlider"));
        AAROIOffsetXSlider->setGeometry(QRect(180, 85, 60, 20));
        AAROIOffsetXSlider->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        AAROIOffsetXSlider->setOrientation(Qt::Orientation::Horizontal);
        AAROIOffsetXSlider->setInvertedAppearance(false);
        AAROIOffsetXSlider->setInvertedControls(false);
        AAROIOffsetXSlider->setTickPosition(QSlider::TickPosition::NoTicks);
        AAROIWidthSpin = new QSpinBox(AA_Param);
        AAROIWidthSpin->setObjectName(QString::fromUtf8("AAROIWidthSpin"));
        AAROIWidthSpin->setGeometry(QRect(250, 21, 61, 24));
        AAROIWidthSpin->setFocusPolicy(Qt::FocusPolicy::WheelFocus);
        AAROIWidthSlider = new QSlider(AA_Param);
        AAROIWidthSlider->setObjectName(QString::fromUtf8("AAROIWidthSlider"));
        AAROIWidthSlider->setGeometry(QRect(180, 26, 61, 20));
        AAROIWidthSlider->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        AAROIWidthSlider->setOrientation(Qt::Orientation::Horizontal);
        AAROIWidthSlider->setInvertedAppearance(false);
        AAROIWidthSlider->setInvertedControls(false);
        AAROIWidthSlider->setTickPosition(QSlider::TickPosition::NoTicks);
        AAROIWidthLabel = new QLabel(AA_Param);
        AAROIWidthLabel->setObjectName(QString::fromUtf8("AAROIWidthLabel"));
        AAROIWidthLabel->setGeometry(QRect(20, 27, 121, 16));
        ExpectedGrayValueSpin = new QSpinBox(AA_Param);
        ExpectedGrayValueSpin->setObjectName(QString::fromUtf8("ExpectedGrayValueSpin"));
        ExpectedGrayValueSpin->setGeometry(QRect(250, 140, 61, 24));
        ExpectedGrayValueLabel = new QLabel(AA_Param);
        ExpectedGrayValueLabel->setObjectName(QString::fromUtf8("ExpectedGrayValueLabel"));
        ExpectedGrayValueLabel->setGeometry(QRect(20, 146, 151, 16));
        ExpectedGrayValueSlider = new QSlider(AA_Param);
        ExpectedGrayValueSlider->setObjectName(QString::fromUtf8("ExpectedGrayValueSlider"));
        ExpectedGrayValueSlider->setGeometry(QRect(180, 145, 60, 20));
        ExpectedGrayValueSlider->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        ExpectedGrayValueSlider->setOrientation(Qt::Orientation::Horizontal);
        ExpectedGrayValueSlider->setInvertedAppearance(false);
        ExpectedGrayValueSlider->setInvertedControls(false);
        ExpectedGrayValueSlider->setTickPosition(QSlider::TickPosition::NoTicks);
        QWidget::setTabOrder(ExposureAuto, ExposureTimeSpin);
        QWidget::setTabOrder(ExposureTimeSpin, AutoExposureTimeMinSpin);
        QWidget::setTabOrder(AutoExposureTimeMinSpin, AutoExposureTimeMaxSpin);
        QWidget::setTabOrder(AutoExposureTimeMaxSpin, GainAuto);
        QWidget::setTabOrder(GainAuto, GainSpin);
        QWidget::setTabOrder(GainSpin, AutoGainMinSpin);
        QWidget::setTabOrder(AutoGainMinSpin, AutoGainMaxSpin);
        QWidget::setTabOrder(AutoGainMaxSpin, AAROIWidthSlider);
        QWidget::setTabOrder(AAROIWidthSlider, AAROIWidthSpin);
        QWidget::setTabOrder(AAROIWidthSpin, AAROIHeightSlider);
        QWidget::setTabOrder(AAROIHeightSlider, AAROIHeightSpin);
        QWidget::setTabOrder(AAROIHeightSpin, AAROIOffsetXSlider);
        QWidget::setTabOrder(AAROIOffsetXSlider, AAROIOffsetXSpin);
        QWidget::setTabOrder(AAROIOffsetXSpin, AAROIOffsetYSlider);
        QWidget::setTabOrder(AAROIOffsetYSlider, AAROIOffsetYSpin);
        QWidget::setTabOrder(AAROIOffsetYSpin, ExpectedGrayValueSlider);
        QWidget::setTabOrder(ExpectedGrayValueSlider, ExpectedGrayValueSpin);
        QWidget::setTabOrder(ExpectedGrayValueSpin, AA_Close);

        retranslateUi(CExposureGain);

        QMetaObject::connectSlotsByName(CExposureGain);
    } // setupUi

    void retranslateUi(QDialog *CExposureGain)
    {
        CExposureGain->setWindowTitle(QApplication::translate("CExposureGain", "ExposureGain", nullptr));
        Exposure->setTitle(QApplication::translate("CExposureGain", "Exposure", nullptr));
        ExposureAutoLabel->setText(QApplication::translate("CExposureGain", "ExposureAuto", nullptr));
        ExposureTimeLabel->setText(QApplication::translate("CExposureGain", "ExposureTime(us)", nullptr));
        AutoExposureTimeMax->setText(QApplication::translate("CExposureGain", "AutoExposureTimeMax", nullptr));
#ifndef QT_NO_TOOLTIP
        ExposureTimeSpin->setToolTip(QApplication::translate("CExposureGain", "abcd", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        ExposureTimeSpin->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        AutoExposureTimeMinLabel->setText(QApplication::translate("CExposureGain", "AutoExposureTimeMin", nullptr));
        AA_Close->setText(QApplication::translate("CExposureGain", "Close", nullptr));
        Gain->setTitle(QApplication::translate("CExposureGain", "Gain", nullptr));
        GainAutoLabel->setText(QApplication::translate("CExposureGain", "GainAuto", nullptr));
        GainLabel->setText(QApplication::translate("CExposureGain", "Gain(dB)", nullptr));
        AutoGainMaxLabel->setText(QApplication::translate("CExposureGain", "AutoGainMax", nullptr));
        AutoGainMinLabel->setText(QApplication::translate("CExposureGain", "AutoGainMin", nullptr));
        AA_Param->setTitle(QApplication::translate("CExposureGain", "Auto Exposure && Auto Gain Param", nullptr));
        AAROIHeightLabel->setText(QApplication::translate("CExposureGain", "AAROIHeight", nullptr));
        AAROIOffsetYLabel->setText(QApplication::translate("CExposureGain", "AAROIOffsetY", nullptr));
        AAROIOffsetXLabel->setText(QApplication::translate("CExposureGain", "AAROIOffsetX", nullptr));
        AAROIWidthLabel->setText(QApplication::translate("CExposureGain", "AAROIWidth", nullptr));
        ExpectedGrayValueLabel->setText(QApplication::translate("CExposureGain", "ExpectedGrayValue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CExposureGain: public Ui_CExposureGain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPOSUREGAIN_H
