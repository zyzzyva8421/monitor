/********************************************************************************
** Form generated from reading UI file 'set_wifi.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_WIFI_H
#define UI_SET_WIFI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_serv_wifi
{
public:
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QComboBox *comboBox_3;

    void setupUi(QWidget *Form_serv_wifi)
    {
        if (Form_serv_wifi->objectName().isEmpty())
            Form_serv_wifi->setObjectName(QString::fromUtf8("Form_serv_wifi"));
        Form_serv_wifi->resize(450, 254);
        label = new QLabel(Form_serv_wifi);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 65, 101, 20));
        label_2 = new QLabel(Form_serv_wifi);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 105, 68, 20));
        comboBox = new QComboBox(Form_serv_wifi);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(120, 100, 111, 27));
        label_3 = new QLabel(Form_serv_wifi);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 145, 71, 20));
        lineEdit_2 = new QLineEdit(Form_serv_wifi);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 140, 211, 27));
        label_4 = new QLabel(Form_serv_wifi);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 25, 91, 20));
        comboBox_2 = new QComboBox(Form_serv_wifi);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(120, 20, 111, 27));
        pushButton = new QPushButton(Form_serv_wifi);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(70, 200, 111, 30));
        pushButton_2 = new QPushButton(Form_serv_wifi);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 200, 121, 30));
        comboBox_3 = new QComboBox(Form_serv_wifi);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(120, 60, 211, 27));

        retranslateUi(Form_serv_wifi);

        QMetaObject::connectSlotsByName(Form_serv_wifi);
    } // setupUi

    void retranslateUi(QWidget *Form_serv_wifi)
    {
        Form_serv_wifi->setWindowTitle(QApplication::translate("Form_serv_wifi", "\346\227\240\347\272\277\347\275\221\347\273\234\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_serv_wifi", "\347\275\221\347\273\234\345\220\215\347\247\260 SSID", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form_serv_wifi", "\345\212\240\345\257\206\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form_serv_wifi", "\347\275\221\347\273\234\345\257\206\351\222\245", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form_serv_wifi", "\346\227\240\347\272\277\347\275\221\347\273\234\345\274\200\345\205\263", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_serv_wifi", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_serv_wifi", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_serv_wifi: public Ui_Form_serv_wifi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_WIFI_H
