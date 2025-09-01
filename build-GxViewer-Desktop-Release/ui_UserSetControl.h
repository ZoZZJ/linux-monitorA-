/********************************************************************************
** Form generated from reading UI file 'UserSetControl.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERSETCONTROL_H
#define UI_USERSETCONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CUserSetControl
{
public:
    QGroupBox *UserSetControl;
    QComboBox *UserSetSelector;
    QLabel *UserSetSelectorLabel;
    QLabel *UserSetSaveLabel;
    QComboBox *UserSetDefault;
    QLabel *UserSetDefaultLabel;
    QLabel *UserSetLoadLabel;
    QPushButton *UserSetLoad;
    QPushButton *UserSetSave;
    QPushButton *UserSet_Close;

    void setupUi(QDialog *CUserSetControl)
    {
        if (CUserSetControl->objectName().isEmpty())
            CUserSetControl->setObjectName(QString::fromUtf8("CUserSetControl"));
        CUserSetControl->resize(351, 202);
        QIcon icon;
        icon.addFile(QString::fromUtf8("resources/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        CUserSetControl->setWindowIcon(icon);
        UserSetControl = new QGroupBox(CUserSetControl);
        UserSetControl->setObjectName(QString::fromUtf8("UserSetControl"));
        UserSetControl->setGeometry(QRect(10, 10, 331, 151));
        UserSetSelector = new QComboBox(UserSetControl);
        UserSetSelector->setObjectName(QString::fromUtf8("UserSetSelector"));
        UserSetSelector->setGeometry(QRect(180, 20, 131, 24));
        UserSetSelector->setEditable(false);
        UserSetSelectorLabel = new QLabel(UserSetControl);
        UserSetSelectorLabel->setObjectName(QString::fromUtf8("UserSetSelectorLabel"));
        UserSetSelectorLabel->setGeometry(QRect(20, 26, 141, 16));
        UserSetSaveLabel = new QLabel(UserSetControl);
        UserSetSaveLabel->setObjectName(QString::fromUtf8("UserSetSaveLabel"));
        UserSetSaveLabel->setGeometry(QRect(20, 86, 121, 16));
        UserSetDefault = new QComboBox(UserSetControl);
        UserSetDefault->setObjectName(QString::fromUtf8("UserSetDefault"));
        UserSetDefault->setGeometry(QRect(180, 110, 131, 24));
        UserSetDefault->setEditable(false);
        UserSetDefaultLabel = new QLabel(UserSetControl);
        UserSetDefaultLabel->setObjectName(QString::fromUtf8("UserSetDefaultLabel"));
        UserSetDefaultLabel->setGeometry(QRect(20, 116, 121, 16));
        UserSetLoadLabel = new QLabel(UserSetControl);
        UserSetLoadLabel->setObjectName(QString::fromUtf8("UserSetLoadLabel"));
        UserSetLoadLabel->setGeometry(QRect(20, 56, 121, 16));
        UserSetLoad = new QPushButton(UserSetControl);
        UserSetLoad->setObjectName(QString::fromUtf8("UserSetLoad"));
        UserSetLoad->setGeometry(QRect(180, 50, 131, 25));
        UserSetSave = new QPushButton(UserSetControl);
        UserSetSave->setObjectName(QString::fromUtf8("UserSetSave"));
        UserSetSave->setGeometry(QRect(180, 80, 131, 25));
        UserSet_Close = new QPushButton(CUserSetControl);
        UserSet_Close->setObjectName(QString::fromUtf8("UserSet_Close"));
        UserSet_Close->setGeometry(QRect(200, 170, 131, 25));
        QWidget::setTabOrder(UserSetSelector, UserSetLoad);
        QWidget::setTabOrder(UserSetLoad, UserSetSave);
        QWidget::setTabOrder(UserSetSave, UserSetDefault);
        QWidget::setTabOrder(UserSetDefault, UserSet_Close);

        retranslateUi(CUserSetControl);

        QMetaObject::connectSlotsByName(CUserSetControl);
    } // setupUi

    void retranslateUi(QDialog *CUserSetControl)
    {
        CUserSetControl->setWindowTitle(QApplication::translate("CUserSetControl", "UserSetControl", nullptr));
        UserSetControl->setTitle(QApplication::translate("CUserSetControl", "UserSetControl", nullptr));
        UserSetSelectorLabel->setText(QApplication::translate("CUserSetControl", "UserSetSelector", nullptr));
        UserSetSaveLabel->setText(QApplication::translate("CUserSetControl", "UserSetSave", nullptr));
        UserSetDefaultLabel->setText(QApplication::translate("CUserSetControl", "UserSetDefault", nullptr));
        UserSetLoadLabel->setText(QApplication::translate("CUserSetControl", "UserSetLoad", nullptr));
        UserSetLoad->setText(QApplication::translate("CUserSetControl", "UserSetLoad", nullptr));
        UserSetSave->setText(QApplication::translate("CUserSetControl", "UserSetSave", nullptr));
        UserSet_Close->setText(QApplication::translate("CUserSetControl", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CUserSetControl: public Ui_CUserSetControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERSETCONTROL_H
