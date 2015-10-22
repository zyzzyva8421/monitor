/********************************************************************************
** Form generated from reading UI file 'alm_tiwen_dlg.ui'
**
** Created: Tue Jun 9 17:08:54 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALM_TIWEN_DLG_H
#define UI_ALM_TIWEN_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dlg_alm_tiwen
{
public:
    QComboBox *comboBox;
    QSpinBox *spinBox_2;
    QLabel *label_5;
    QLabel *label_4;
    QPushButton *pushButton;
    QLabel *label_3;
    QSpinBox *spinBox;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QDialog *Dlg_alm_tiwen)
    {
        if (Dlg_alm_tiwen->objectName().isEmpty())
            Dlg_alm_tiwen->setObjectName(QString::fromUtf8("Dlg_alm_tiwen"));
        Dlg_alm_tiwen->resize(400, 131);
        comboBox = new QComboBox(Dlg_alm_tiwen);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(70, 40, 61, 27));
        comboBox->setMaxVisibleItems(2);
        spinBox_2 = new QSpinBox(Dlg_alm_tiwen);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(260, 40, 91, 27));
        spinBox_2->setMaximum(300);
        spinBox_2->setValue(80);
        label_5 = new QLabel(Dlg_alm_tiwen);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(270, 10, 71, 20));
        label_4 = new QLabel(Dlg_alm_tiwen);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 10, 71, 20));
        pushButton = new QPushButton(Dlg_alm_tiwen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 80, 111, 30));
        label_3 = new QLabel(Dlg_alm_tiwen);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 10, 51, 20));
        spinBox = new QSpinBox(Dlg_alm_tiwen);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(160, 40, 91, 27));
        spinBox->setMaximum(300);
        spinBox->setValue(90);
        pushButton_2 = new QPushButton(Dlg_alm_tiwen);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(210, 80, 121, 30));
        label = new QLabel(Dlg_alm_tiwen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 51, 20));

        retranslateUi(Dlg_alm_tiwen);

        QMetaObject::connectSlotsByName(Dlg_alm_tiwen);
    } // setupUi

    void retranslateUi(QDialog *Dlg_alm_tiwen)
    {
        Dlg_alm_tiwen->setWindowTitle(QApplication::translate("Dlg_alm_tiwen", "\344\275\223\346\270\251\346\212\245\350\255\246\351\231\220\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dlg_alm_tiwen", "\346\212\245\350\255\246\344\275\216\351\231\220", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dlg_alm_tiwen", "\346\212\245\350\255\246\351\253\230\351\231\220", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Dlg_alm_tiwen", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dlg_alm_tiwen", "\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Dlg_alm_tiwen", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dlg_alm_tiwen", "\344\275\223\346\270\251", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dlg_alm_tiwen: public Ui_Dlg_alm_tiwen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALM_TIWEN_DLG_H
