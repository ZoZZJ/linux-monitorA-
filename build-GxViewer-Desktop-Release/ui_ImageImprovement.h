/********************************************************************************
** Form generated from reading UI file 'ImageImprovement.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEIMPROVEMENT_H
#define UI_IMAGEIMPROVEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CImageImprovement
{
public:
    QGroupBox *ImageImprovement;
    QSpinBox *ContrastSpin;
    QSlider *ContrastSlider;
    QDoubleSpinBox *GammaSpin;
    QCheckBox *GammaCheckBox;
    QCheckBox *ContrastCheckBox;
    QCheckBox *ColorCorrect;
    QPushButton *ImageImprovement_Close;

    void setupUi(QDialog *CImageImprovement)
    {
        if (CImageImprovement->objectName().isEmpty())
            CImageImprovement->setObjectName(QString::fromUtf8("CImageImprovement"));
        CImageImprovement->resize(351, 172);
        ImageImprovement = new QGroupBox(CImageImprovement);
        ImageImprovement->setObjectName(QString::fromUtf8("ImageImprovement"));
        ImageImprovement->setGeometry(QRect(10, 10, 331, 121));
        ContrastSpin = new QSpinBox(ImageImprovement);
        ContrastSpin->setObjectName(QString::fromUtf8("ContrastSpin"));
        ContrastSpin->setGeometry(QRect(250, 80, 61, 24));
        ContrastSlider = new QSlider(ImageImprovement);
        ContrastSlider->setObjectName(QString::fromUtf8("ContrastSlider"));
        ContrastSlider->setGeometry(QRect(159, 85, 81, 20));
        ContrastSlider->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        ContrastSlider->setOrientation(Qt::Orientation::Horizontal);
        ContrastSlider->setInvertedAppearance(false);
        ContrastSlider->setInvertedControls(false);
        ContrastSlider->setTickPosition(QSlider::TickPosition::NoTicks);
        GammaSpin = new QDoubleSpinBox(ImageImprovement);
        GammaSpin->setObjectName(QString::fromUtf8("GammaSpin"));
        GammaSpin->setGeometry(QRect(160, 50, 151, 24));
        GammaSpin->setCorrectionMode(QAbstractSpinBox::CorrectionMode::CorrectToPreviousValue);
        GammaCheckBox = new QCheckBox(ImageImprovement);
        GammaCheckBox->setObjectName(QString::fromUtf8("GammaCheckBox"));
        GammaCheckBox->setGeometry(QRect(20, 53, 86, 20));
        ContrastCheckBox = new QCheckBox(ImageImprovement);
        ContrastCheckBox->setObjectName(QString::fromUtf8("ContrastCheckBox"));
        ContrastCheckBox->setGeometry(QRect(20, 83, 141, 20));
        ColorCorrect = new QCheckBox(ImageImprovement);
        ColorCorrect->setObjectName(QString::fromUtf8("ColorCorrect"));
        ColorCorrect->setGeometry(QRect(20, 23, 111, 20));
        ImageImprovement_Close = new QPushButton(CImageImprovement);
        ImageImprovement_Close->setObjectName(QString::fromUtf8("ImageImprovement_Close"));
        ImageImprovement_Close->setGeometry(QRect(200, 140, 131, 25));
        QWidget::setTabOrder(ColorCorrect, GammaCheckBox);
        QWidget::setTabOrder(GammaCheckBox, GammaSpin);
        QWidget::setTabOrder(GammaSpin, ContrastCheckBox);
        QWidget::setTabOrder(ContrastCheckBox, ContrastSlider);
        QWidget::setTabOrder(ContrastSlider, ContrastSpin);
        QWidget::setTabOrder(ContrastSpin, ImageImprovement_Close);

        retranslateUi(CImageImprovement);

        QMetaObject::connectSlotsByName(CImageImprovement);
    } // setupUi

    void retranslateUi(QDialog *CImageImprovement)
    {
        CImageImprovement->setWindowTitle(QApplication::translate("CImageImprovement", "Image Improvement", nullptr));
        ImageImprovement->setTitle(QApplication::translate("CImageImprovement", "Image Improvement", nullptr));
        GammaCheckBox->setText(QApplication::translate("CImageImprovement", "Gamma", nullptr));
        ContrastCheckBox->setText(QApplication::translate("CImageImprovement", "Contrast", nullptr));
        ColorCorrect->setText(QApplication::translate("CImageImprovement", "ColorCorrect", nullptr));
        ImageImprovement_Close->setText(QApplication::translate("CImageImprovement", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CImageImprovement: public Ui_CImageImprovement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEIMPROVEMENT_H
