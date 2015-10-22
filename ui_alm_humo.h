/********************************************************************************
** Form generated from reading UI file 'alm_humo.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALM_HUMO_H
#define UI_ALM_HUMO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_alm_co2
{
public:
    QSpinBox *spinBox;
    QPushButton *pushButton_2;
    QComboBox *comboBox;
    QLabel *label;
    QSpinBox *spinBox_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton;
    QLabel *label_5;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QComboBox *comboBox_2;
    QLabel *label_2;
    QLabel *label_6;
    QComboBox *comboBox_3;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;

    void setupUi(QWidget *Form_alm_co2)
    {
        if (Form_alm_co2->objectName().isEmpty())
            Form_alm_co2->setObjectName(QString::fromUtf8("Form_alm_co2"));
        Form_alm_co2->resize(400, 200);
        spinBox = new QSpinBox(Form_alm_co2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(180, 50, 91, 27));
        spinBox->setMaximum(100);
        spinBox->setValue(90);
        pushButton_2 = new QPushButton(Form_alm_co2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 160, 121, 30));
        comboBox = new QComboBox(Form_alm_co2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(90, 50, 61, 27));
        comboBox->setMaxVisibleItems(2);
        label = new QLabel(Form_alm_co2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 50, 61, 20));
        spinBox_2 = new QSpinBox(Form_alm_co2);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(280, 50, 91, 27));
        spinBox_2->setMaximum(300);
        spinBox_2->setValue(80);
        label_3 = new QLabel(Form_alm_co2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 20, 51, 20));
        label_4 = new QLabel(Form_alm_co2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(190, 20, 71, 20));
        pushButton = new QPushButton(Form_alm_co2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 160, 111, 30));
        label_5 = new QLabel(Form_alm_co2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(290, 20, 71, 20));
        spinBox_3 = new QSpinBox(Form_alm_co2);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(280, 80, 91, 27));
        spinBox_3->setMaximum(300);
        spinBox_3->setValue(80);
        spinBox_4 = new QSpinBox(Form_alm_co2);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(180, 80, 91, 27));
        spinBox_4->setMaximum(100);
        spinBox_4->setValue(90);
        comboBox_2 = new QComboBox(Form_alm_co2);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(90, 80, 61, 27));
        comboBox_2->setMaxVisibleItems(2);
        label_2 = new QLabel(Form_alm_co2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 80, 61, 20));
        label_6 = new QLabel(Form_alm_co2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 110, 61, 20));
        comboBox_3 = new QComboBox(Form_alm_co2);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(90, 110, 61, 27));
        comboBox_3->setMaxVisibleItems(2);
        spinBox_5 = new QSpinBox(Form_alm_co2);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));
        spinBox_5->setGeometry(QRect(280, 110, 91, 27));
        spinBox_5->setMaximum(300);
        spinBox_5->setValue(80);
        spinBox_6 = new QSpinBox(Form_alm_co2);
        spinBox_6->setObjectName(QString::fromUtf8("spinBox_6"));
        spinBox_6->setGeometry(QRect(180, 110, 91, 27));
        spinBox_6->setMaximum(100);
        spinBox_6->setValue(90);

        retranslateUi(Form_alm_co2);

        QMetaObject::connectSlotsByName(Form_alm_co2);
    } // setupUi

    void retranslateUi(QWidget *Form_alm_co2)
    {
        Form_alm_co2->setWindowTitle(QApplication::translate("Form_alm_co2", "CO2\346\212\245\350\255\246\351\231\220\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_alm_co2", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_alm_co2", "\345\221\274\345\220\270\347\216\207", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form_alm_co2", "\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form_alm_co2", "\346\212\245\350\255\246\351\253\230\351\231\220", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_alm_co2", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Form_alm_co2", "\346\212\245\350\255\246\344\275\216\351\231\220", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form_alm_co2", "\345\221\274\346\234\253CO2", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Form_alm_co2", "\345\220\270\345\205\245CO2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_alm_co2: public Ui_Form_alm_co2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALM_HUMO_H
