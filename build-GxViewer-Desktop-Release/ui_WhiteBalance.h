/********************************************************************************
** Form generated from reading UI file 'WhiteBalance.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHITEBALANCE_H
#define UI_WHITEBALANCE_H

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

class Ui_CWhiteBalance
{
public:
    QGroupBox *Balance_White;
    QComboBox *BalanceRatioSelector;
    QLabel *BalanceRatioSelectorLabel;
    QLabel *BalanceRatioLabel;
    QLabel *AWBROIHeightLabel;
    QSlider *AWBROIHeightSlider;
    QDoubleSpinBox *BalanceRatioSpin;
    QSpinBox *AWBROIHeightSpin;
    QLabel *AWBROIWidthLabel;
    QSpinBox *AWBROIWidthSpin;
    QSlider *AWBROIWidthSlider;
    QSpinBox *AWBROIOffsetYSpin;
    QSlider *AWBROIOffsetYSlider;
    QSlider *AWBROIOffsetXSlider;
    QSpinBox *AWBROIOffsetXSpin;
    QLabel *AWBROIOffsetXLabel;
    QLabel *AWBROIOffsetYLabel;
    QComboBox *WhiteBalanceAuto;
    QLabel *WhiteBalanceRatioLabel;
    QPushButton *WhiteBalance_Close;

    void setupUi(QDialog *CWhiteBalance)
    {
        if (CWhiteBalance->objectName().isEmpty())
            CWhiteBalance->setObjectName(QString::fromUtf8("CWhiteBalance"));
        CWhiteBalance->resize(351, 292);
        Balance_White = new QGroupBox(CWhiteBalance);
        Balance_White->setObjectName(QString::fromUtf8("Balance_White"));
        Balance_White->setGeometry(QRect(10, 12, 331, 241));
        BalanceRatioSelector = new QComboBox(Balance_White);
        BalanceRatioSelector->setObjectName(QString::fromUtf8("BalanceRatioSelector"));
        BalanceRatioSelector->setGeometry(QRect(180, 24, 131, 24));
        BalanceRatioSelector->setEditable(false);
        BalanceRatioSelectorLabel = new QLabel(Balance_White);
        BalanceRatioSelectorLabel->setObjectName(QString::fromUtf8("BalanceRatioSelectorLabel"));
        BalanceRatioSelectorLabel->setGeometry(QRect(20, 30, 141, 16));
        BalanceRatioLabel = new QLabel(Balance_White);
        BalanceRatioLabel->setObjectName(QString::fromUtf8("BalanceRatioLabel"));
        BalanceRatioLabel->setGeometry(QRect(20, 60, 121, 16));
        AWBROIHeightLabel = new QLabel(Balance_White);
        AWBROIHeightLabel->setObjectName(QString::fromUtf8("AWBROIHeightLabel"));
        AWBROIHeightLabel->setGeometry(QRect(20, 150, 151, 16));
        AWBROIHeightSlider = new QSlider(Balance_White);
        AWBROIHeightSlider->setObjectName(QString::fromUtf8("AWBROIHeightSlider"));
        AWBROIHeightSlider->setGeometry(QRect(180, 149, 60, 20));
        AWBROIHeightSlider->setInputMethodHints(Qt::ImhNone);
        AWBROIHeightSlider->setOrientation(Qt::Horizontal);
        AWBROIHeightSlider->setInvertedAppearance(false);
        AWBROIHeightSlider->setInvertedControls(false);
        AWBROIHeightSlider->setTickPosition(QSlider::NoTicks);
        BalanceRatioSpin = new QDoubleSpinBox(Balance_White);
        BalanceRatioSpin->setObjectName(QString::fromUtf8("BalanceRatioSpin"));
        BalanceRatioSpin->setGeometry(QRect(180, 54, 131, 24));
        AWBROIHeightSpin = new QSpinBox(Balance_White);
        AWBROIHeightSpin->setObjectName(QString::fromUtf8("AWBROIHeightSpin"));
        AWBROIHeightSpin->setGeometry(QRect(250, 144, 61, 24));
        AWBROIWidthLabel = new QLabel(Balance_White);
        AWBROIWidthLabel->setObjectName(QString::fromUtf8("AWBROIWidthLabel"));
        AWBROIWidthLabel->setGeometry(QRect(20, 120, 151, 16));
        AWBROIWidthSpin = new QSpinBox(Balance_White);
        AWBROIWidthSpin->setObjectName(QString::fromUtf8("AWBROIWidthSpin"));
        AWBROIWidthSpin->setGeometry(QRect(250, 114, 61, 24));
        AWBROIWidthSlider = new QSlider(Balance_White);
        AWBROIWidthSlider->setObjectName(QString::fromUtf8("AWBROIWidthSlider"));
        AWBROIWidthSlider->setGeometry(QRect(180, 119, 60, 20));
        AWBROIWidthSlider->setInputMethodHints(Qt::ImhNone);
        AWBROIWidthSlider->setOrientation(Qt::Horizontal);
        AWBROIWidthSlider->setInvertedAppearance(false);
        AWBROIWidthSlider->setInvertedControls(false);
        AWBROIWidthSlider->setTickPosition(QSlider::NoTicks);
        AWBROIOffsetYSpin = new QSpinBox(Balance_White);
        AWBROIOffsetYSpin->setObjectName(QString::fromUtf8("AWBROIOffsetYSpin"));
        AWBROIOffsetYSpin->setGeometry(QRect(250, 204, 61, 24));
        AWBROIOffsetYSlider = new QSlider(Balance_White);
        AWBROIOffsetYSlider->setObjectName(QString::fromUtf8("AWBROIOffsetYSlider"));
        AWBROIOffsetYSlider->setGeometry(QRect(180, 209, 60, 20));
        AWBROIOffsetYSlider->setInputMethodHints(Qt::ImhNone);
        AWBROIOffsetYSlider->setOrientation(Qt::Horizontal);
        AWBROIOffsetYSlider->setInvertedAppearance(false);
        AWBROIOffsetYSlider->setInvertedControls(false);
        AWBROIOffsetYSlider->setTickPosition(QSlider::NoTicks);
        AWBROIOffsetXSlider = new QSlider(Balance_White);
        AWBROIOffsetXSlider->setObjectName(QString::fromUtf8("AWBROIOffsetXSlider"));
        AWBROIOffsetXSlider->setGeometry(QRect(180, 179, 60, 20));
        AWBROIOffsetXSlider->setInputMethodHints(Qt::ImhNone);
        AWBROIOffsetXSlider->setOrientation(Qt::Horizontal);
        AWBROIOffsetXSlider->setInvertedAppearance(false);
        AWBROIOffsetXSlider->setInvertedControls(false);
        AWBROIOffsetXSlider->setTickPosition(QSlider::NoTicks);
        AWBROIOffsetXSpin = new QSpinBox(Balance_White);
        AWBROIOffsetXSpin->setObjectName(QString::fromUtf8("AWBROIOffsetXSpin"));
        AWBROIOffsetXSpin->setGeometry(QRect(250, 174, 61, 24));
        AWBROIOffsetXLabel = new QLabel(Balance_White);
        AWBROIOffsetXLabel->setObjectName(QString::fromUtf8("AWBROIOffsetXLabel"));
        AWBROIOffsetXLabel->setGeometry(QRect(20, 180, 151, 16));
        AWBROIOffsetYLabel = new QLabel(Balance_White);
        AWBROIOffsetYLabel->setObjectName(QString::fromUtf8("AWBROIOffsetYLabel"));
        AWBROIOffsetYLabel->setGeometry(QRect(20, 210, 151, 16));
        WhiteBalanceAuto = new QComboBox(Balance_White);
        WhiteBalanceAuto->setObjectName(QString::fromUtf8("WhiteBalanceAuto"));
        WhiteBalanceAuto->setGeometry(QRect(180, 84, 131, 24));
        WhiteBalanceAuto->setEditable(false);
        WhiteBalanceRatioLabel = new QLabel(Balance_White);
        WhiteBalanceRatioLabel->setObjectName(QString::fromUtf8("WhiteBalanceRatioLabel"));
        WhiteBalanceRatioLabel->setGeometry(QRect(20, 90, 141, 16));
        WhiteBalance_Close = new QPushButton(CWhiteBalance);
        WhiteBalance_Close->setObjectName(QString::fromUtf8("WhiteBalance_Close"));
        WhiteBalance_Close->setGeometry(QRect(200, 260, 131, 25));
        WhiteBalance_Close->setFocusPolicy(Qt::StrongFocus);
        QWidget::setTabOrder(BalanceRatioSelector, BalanceRatioSpin);
        QWidget::setTabOrder(BalanceRatioSpin, WhiteBalanceAuto);
        QWidget::setTabOrder(WhiteBalanceAuto, AWBROIWidthSlider);
        QWidget::setTabOrder(AWBROIWidthSlider, AWBROIWidthSpin);
        QWidget::setTabOrder(AWBROIWidthSpin, AWBROIHeightSlider);
        QWidget::setTabOrder(AWBROIHeightSlider, AWBROIHeightSpin);
        QWidget::setTabOrder(AWBROIHeightSpin, AWBROIOffsetXSlider);
        QWidget::setTabOrder(AWBROIOffsetXSlider, AWBROIOffsetXSpin);
        QWidget::setTabOrder(AWBROIOffsetXSpin, AWBROIOffsetYSlider);
        QWidget::setTabOrder(AWBROIOffsetYSlider, AWBROIOffsetYSpin);
        QWidget::setTabOrder(AWBROIOffsetYSpin, WhiteBalance_Close);

        retranslateUi(CWhiteBalance);

        QMetaObject::connectSlotsByName(CWhiteBalance);
    } // setupUi

    void retranslateUi(QDialog *CWhiteBalance)
    {
        CWhiteBalance->setWindowTitle(QApplication::translate("CWhiteBalance", "WhiteBalance", nullptr));
        Balance_White->setTitle(QApplication::translate("CWhiteBalance", "Balance White", nullptr));
        BalanceRatioSelectorLabel->setText(QApplication::translate("CWhiteBalance", "BalanceRatioSelector", nullptr));
        BalanceRatioLabel->setText(QApplication::translate("CWhiteBalance", "BalanceRatio", nullptr));
        AWBROIHeightLabel->setText(QApplication::translate("CWhiteBalance", "AWBROIHeight", nullptr));
        AWBROIWidthLabel->setText(QApplication::translate("CWhiteBalance", "AWBROIWidth", nullptr));
        AWBROIOffsetXLabel->setText(QApplication::translate("CWhiteBalance", "AWBROIOffsetX", nullptr));
        AWBROIOffsetYLabel->setText(QApplication::translate("CWhiteBalance", "AWBROIOffsetY", nullptr));
        WhiteBalanceRatioLabel->setText(QApplication::translate("CWhiteBalance", "WhiteBalanceAuto", nullptr));
        WhiteBalance_Close->setText(QApplication::translate("CWhiteBalance", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CWhiteBalance: public Ui_CWhiteBalance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHITEBALANCE_H
