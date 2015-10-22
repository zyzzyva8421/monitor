/********************************************************************************
** Form generated from reading UI file 'alm_spo_dlg.ui'
**
** Created: Tue Jun 9 17:08:54 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALM_SPO_DLG_H
#define UI_ALM_SPO_DLG_H

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

class Ui_Dlg_alm_spo
{
public:
    QLabel *label_5;
    QSpinBox *spinBox_2;
    QLabel *label_2;
    QSpinBox *spinBox;
    QLabel *label;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QLabel *label_3;
    QSpinBox *spinBox_3;
    QComboBox *comboBox_2;
    QLabel *label_4;
    QSpinBox *spinBox_4;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Dlg_alm_spo)
    {
        if (Dlg_alm_spo->objectName().isEmpty())
            Dlg_alm_spo->setObjectName(QString::fromUtf8("Dlg_alm_spo"));
        Dlg_alm_spo->resize(400, 169);
        label_5 = new QLabel(Dlg_alm_spo);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(280, 10, 71, 20));
        spinBox_2 = new QSpinBox(Dlg_alm_spo);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(270, 40, 91, 27));
        spinBox_2->setMaximum(100);
        spinBox_2->setValue(80);
        label_2 = new QLabel(Dlg_alm_spo);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 70, 51, 20));
        spinBox = new QSpinBox(Dlg_alm_spo);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(170, 40, 91, 27));
        spinBox->setMaximum(100);
        spinBox->setValue(90);
        label = new QLabel(Dlg_alm_spo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 51, 20));
        pushButton = new QPushButton(Dlg_alm_spo);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 120, 111, 30));
        comboBox = new QComboBox(Dlg_alm_spo);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(80, 40, 61, 27));
        comboBox->setMaxVisibleItems(2);
        label_3 = new QLabel(Dlg_alm_spo);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 10, 51, 20));
        spinBox_3 = new QSpinBox(Dlg_alm_spo);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(170, 70, 91, 27));
        spinBox_3->setMaximum(300);
        spinBox_3->setValue(100);
        comboBox_2 = new QComboBox(Dlg_alm_spo);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(80, 70, 61, 27));
        comboBox_2->setMaxVisibleItems(2);
        label_4 = new QLabel(Dlg_alm_spo);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 10, 71, 20));
        spinBox_4 = new QSpinBox(Dlg_alm_spo);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(270, 70, 91, 27));
        spinBox_4->setMaximum(300);
        spinBox_4->setValue(52);
        pushButton_2 = new QPushButton(Dlg_alm_spo);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 120, 121, 30));

        retranslateUi(Dlg_alm_spo);

        QMetaObject::connectSlotsByName(Dlg_alm_spo);
    } // setupUi

    void retranslateUi(QDialog *Dlg_alm_spo)
    {
        Dlg_alm_spo->setWindowTitle(QApplication::translate("Dlg_alm_spo", "\350\241\200\346\260\247\346\212\245\350\255\246\351\231\220\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dlg_alm_spo", "\346\212\245\350\255\246\344\275\216\351\231\220", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dlg_alm_spo", "\350\204\211\347\216\207", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dlg_alm_spo", "\350\241\200\346\260\247", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Dlg_alm_spo", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dlg_alm_spo", "\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dlg_alm_spo", "\346\212\245\350\255\246\351\253\230\351\231\220", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Dlg_alm_spo", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dlg_alm_spo: public Ui_Dlg_alm_spo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALM_SPO_DLG_H
