/********************************************************************************
** Form generated from reading UI file 'alm_huxi_dlg.ui'
**
** Created: Tue Jun 9 17:08:54 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALM_HUXI_DLG_H
#define UI_ALM_HUXI_DLG_H

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

class Ui_Dlg_alm_huxi
{
public:
    QPushButton *pushButton_2;
    QSpinBox *spinBox_2;
    QComboBox *comboBox;
    QLabel *label_4;
    QSpinBox *spinBox;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_5;
    QPushButton *pushButton;

    void setupUi(QDialog *Dlg_alm_huxi)
    {
        if (Dlg_alm_huxi->objectName().isEmpty())
            Dlg_alm_huxi->setObjectName(QString::fromUtf8("Dlg_alm_huxi"));
        Dlg_alm_huxi->resize(400, 125);
        pushButton_2 = new QPushButton(Dlg_alm_huxi);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 80, 121, 30));
        spinBox_2 = new QSpinBox(Dlg_alm_huxi);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(270, 40, 91, 27));
        spinBox_2->setMaximum(300);
        spinBox_2->setValue(80);
        comboBox = new QComboBox(Dlg_alm_huxi);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(80, 40, 61, 27));
        comboBox->setMaxVisibleItems(2);
        label_4 = new QLabel(Dlg_alm_huxi);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 10, 71, 20));
        spinBox = new QSpinBox(Dlg_alm_huxi);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(170, 40, 91, 27));
        spinBox->setMaximum(300);
        spinBox->setValue(90);
        label_3 = new QLabel(Dlg_alm_huxi);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 10, 51, 20));
        label = new QLabel(Dlg_alm_huxi);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 51, 20));
        label_5 = new QLabel(Dlg_alm_huxi);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(280, 10, 71, 20));
        pushButton = new QPushButton(Dlg_alm_huxi);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 80, 111, 30));

        retranslateUi(Dlg_alm_huxi);

        QMetaObject::connectSlotsByName(Dlg_alm_huxi);
    } // setupUi

    void retranslateUi(QDialog *Dlg_alm_huxi)
    {
        Dlg_alm_huxi->setWindowTitle(QApplication::translate("Dlg_alm_huxi", "\345\221\274\345\220\270\346\212\245\350\255\246\351\231\220\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Dlg_alm_huxi", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dlg_alm_huxi", "\346\212\245\350\255\246\351\253\230\351\231\220", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dlg_alm_huxi", "\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dlg_alm_huxi", "\345\221\274\345\220\270", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dlg_alm_huxi", "\346\212\245\350\255\246\344\275\216\351\231\220", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Dlg_alm_huxi", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dlg_alm_huxi: public Ui_Dlg_alm_huxi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALM_HUXI_DLG_H
