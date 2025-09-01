/********************************************************************************
** Form generated from reading UI file 'FrameRateControl.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMERATECONTROL_H
#define UI_FRAMERATECONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CFrameRateControl
{
public:
    QGroupBox *FrameRate_Control;
    QDoubleSpinBox *AcquisitionFrameRateSpinBox;
    QLabel *AcquisitionFrameRateLabel;
    QLabel *AcquisitionFrameRateModeLabel;
    QComboBox *AcquisitionFrameRateMode;
    QPushButton *FrameRateControl_Close;

    void setupUi(QDialog *CFrameRateControl)
    {
        if (CFrameRateControl->objectName().isEmpty())
            CFrameRateControl->setObjectName(QString::fromUtf8("CFrameRateControl"));
        CFrameRateControl->resize(351, 145);
        FrameRate_Control = new QGroupBox(CFrameRateControl);
        FrameRate_Control->setObjectName(QString::fromUtf8("FrameRate_Control"));
        FrameRate_Control->setGeometry(QRect(10, 10, 331, 91));
        AcquisitionFrameRateSpinBox = new QDoubleSpinBox(FrameRate_Control);
        AcquisitionFrameRateSpinBox->setObjectName(QString::fromUtf8("AcquisitionFrameRateSpinBox"));
        AcquisitionFrameRateSpinBox->setGeometry(QRect(208, 55, 101, 24));
        AcquisitionFrameRateLabel = new QLabel(FrameRate_Control);
        AcquisitionFrameRateLabel->setObjectName(QString::fromUtf8("AcquisitionFrameRateLabel"));
        AcquisitionFrameRateLabel->setGeometry(QRect(18, 61, 171, 16));
        AcquisitionFrameRateModeLabel = new QLabel(FrameRate_Control);
        AcquisitionFrameRateModeLabel->setObjectName(QString::fromUtf8("AcquisitionFrameRateModeLabel"));
        AcquisitionFrameRateModeLabel->setGeometry(QRect(18, 25, 211, 16));
        AcquisitionFrameRateMode = new QComboBox(FrameRate_Control);
        AcquisitionFrameRateMode->setObjectName(QString::fromUtf8("AcquisitionFrameRateMode"));
        AcquisitionFrameRateMode->setGeometry(QRect(208, 20, 101, 24));
        FrameRateControl_Close = new QPushButton(CFrameRateControl);
        FrameRateControl_Close->setObjectName(QString::fromUtf8("FrameRateControl_Close"));
        FrameRateControl_Close->setGeometry(QRect(200, 110, 131, 25));
        FrameRateControl_Close->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        QWidget::setTabOrder(AcquisitionFrameRateMode, AcquisitionFrameRateSpinBox);
        QWidget::setTabOrder(AcquisitionFrameRateSpinBox, FrameRateControl_Close);

        retranslateUi(CFrameRateControl);

        QMetaObject::connectSlotsByName(CFrameRateControl);
    } // setupUi

    void retranslateUi(QDialog *CFrameRateControl)
    {
        CFrameRateControl->setWindowTitle(QApplication::translate("CFrameRateControl", "FrameRateControl", nullptr));
        FrameRate_Control->setTitle(QApplication::translate("CFrameRateControl", "FrameRate Control", nullptr));
        AcquisitionFrameRateLabel->setText(QApplication::translate("CFrameRateControl", "AcquisitionFrameRate", nullptr));
        AcquisitionFrameRateModeLabel->setText(QApplication::translate("CFrameRateControl", "AcquisitionFrameRateMode", nullptr));
        FrameRateControl_Close->setText(QApplication::translate("CFrameRateControl", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CFrameRateControl: public Ui_CFrameRateControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMERATECONTROL_H
