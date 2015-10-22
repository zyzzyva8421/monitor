/********************************************************************************
** Form generated from reading UI file 'alm_humo_dlg.ui'
**
** Created: Tue Jun 9 17:08:54 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALM_HUMO_DLG_H
#define UI_ALM_HUMO_DLG_H

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

class Ui_Dlg_alm_humo
{
public:
    QSpinBox *spinBox_6;
    QPushButton *pushButton_2;
    QSpinBox *spinBox_5;
    QLabel *label;
    QSpinBox *spinBox;
    QComboBox *comboBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_4;
    QPushButton *pushButton;
    QComboBox *comboBox_2;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QComboBox *comboBox_3;
    QSpinBox *spinBox_3;
    QLabel *label_5;

    void setupUi(QDialog *Dlg_alm_humo)
    {
        if (Dlg_alm_humo->objectName().isEmpty())
            Dlg_alm_humo->setObjectName(QString::fromUtf8("Dlg_alm_humo"));
        Dlg_alm_humo->resize(400, 203);
        spinBox_6 = new QSpinBox(Dlg_alm_humo);
        spinBox_6->setObjectName(QString::fromUtf8("spinBox_6"));
        spinBox_6->setGeometry(QRect(180, 100, 91, 27));
        spinBox_6->setMaximum(100);
        spinBox_6->setValue(90);
        pushButton_2 = new QPushButton(Dlg_alm_humo);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 150, 121, 30));
        spinBox_5 = new QSpinBox(Dlg_alm_humo);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));
        spinBox_5->setGeometry(QRect(280, 100, 91, 27));
        spinBox_5->setMaximum(300);
        spinBox_5->setValue(80);
        label = new QLabel(Dlg_alm_humo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 61, 20));
        spinBox = new QSpinBox(Dlg_alm_humo);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(180, 40, 91, 27));
        spinBox->setMaximum(100);
        spinBox->setValue(90);
        comboBox = new QComboBox(Dlg_alm_humo);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(90, 40, 61, 27));
        comboBox->setMaxVisibleItems(2);
        spinBox_2 = new QSpinBox(Dlg_alm_humo);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(280, 40, 91, 27));
        spinBox_2->setMaximum(300);
        spinBox_2->setValue(80);
        spinBox_4 = new QSpinBox(Dlg_alm_humo);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(180, 70, 91, 27));
        spinBox_4->setMaximum(100);
        spinBox_4->setValue(90);
        pushButton = new QPushButton(Dlg_alm_humo);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 150, 111, 30));
        comboBox_2 = new QComboBox(Dlg_alm_humo);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(90, 70, 61, 27));
        comboBox_2->setMaxVisibleItems(2);
        label_6 = new QLabel(Dlg_alm_humo);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 100, 61, 20));
        label_3 = new QLabel(Dlg_alm_humo);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 10, 51, 20));
        label_2 = new QLabel(Dlg_alm_humo);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 70, 61, 20));
        label_4 = new QLabel(Dlg_alm_humo);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(190, 10, 71, 20));
        comboBox_3 = new QComboBox(Dlg_alm_humo);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(90, 100, 61, 27));
        comboBox_3->setMaxVisibleItems(2);
        spinBox_3 = new QSpinBox(Dlg_alm_humo);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(280, 70, 91, 27));
        spinBox_3->setMaximum(300);
        spinBox_3->setValue(80);
        label_5 = new QLabel(Dlg_alm_humo);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(290, 10, 71, 20));

        retranslateUi(Dlg_alm_humo);

        QMetaObject::connectSlotsByName(Dlg_alm_humo);
    } // setupUi

    void retranslateUi(QDialog *Dlg_alm_humo)
    {
        Dlg_alm_humo->setWindowTitle(QApplication::translate("Dlg_alm_humo", "CO2\346\212\245\350\255\246\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Dlg_alm_humo", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dlg_alm_humo", "\345\221\274\345\220\270\347\216\207", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Dlg_alm_humo", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Dlg_alm_humo", "\345\220\270\345\205\245CO2", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dlg_alm_humo", "\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dlg_alm_humo", "\345\221\274\346\234\253CO2", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dlg_alm_humo", "\346\212\245\350\255\246\351\253\230\351\231\220", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dlg_alm_humo", "\346\212\245\350\255\246\344\275\216\351\231\220", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dlg_alm_humo: public Ui_Dlg_alm_humo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALM_HUMO_DLG_H
