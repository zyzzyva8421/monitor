/********************************************************************************
** Form generated from reading UI file 'set_spo2.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_SPO2_H
#define UI_SET_SPO2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Set_spo
{
public:
    QComboBox *comboBox_12;
    QComboBox *comboBox;
    QComboBox *comboBox_4;
    QLabel *label;
    QLabel *label_7;
    QComboBox *comboBox_8;
    QComboBox *comboBox_10;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_4;
    QComboBox *comboBox_6;
    QLabel *label_9;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QWidget *Form_Set_spo)
    {
        if (Form_Set_spo->objectName().isEmpty())
            Form_Set_spo->setObjectName(QString::fromUtf8("Form_Set_spo"));
        Form_Set_spo->resize(300, 300);
        comboBox_12 = new QComboBox(Form_Set_spo);
        comboBox_12->setObjectName(QString::fromUtf8("comboBox_12"));
        comboBox_12->setGeometry(QRect(150, 185, 100, 30));
        comboBox_12->setMaxVisibleItems(2);
        comboBox = new QComboBox(Form_Set_spo);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(150, 10, 100, 30));
        comboBox->setMaxVisibleItems(11);
        comboBox_4 = new QComboBox(Form_Set_spo);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(150, 45, 100, 30));
        comboBox_4->setMaxVisibleItems(3);
        label = new QLabel(Form_Set_spo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 71, 21));
        label_7 = new QLabel(Form_Set_spo);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 90, 71, 21));
        comboBox_8 = new QComboBox(Form_Set_spo);
        comboBox_8->setObjectName(QString::fromUtf8("comboBox_8"));
        comboBox_8->setGeometry(QRect(150, 115, 100, 30));
        comboBox_8->setMaxVisibleItems(2);
        comboBox_10 = new QComboBox(Form_Set_spo);
        comboBox_10->setObjectName(QString::fromUtf8("comboBox_10"));
        comboBox_10->setGeometry(QRect(150, 150, 100, 30));
        comboBox_10->setMaxVisibleItems(2);
        label_11 = new QLabel(Form_Set_spo);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 160, 71, 21));
        label_13 = new QLabel(Form_Set_spo);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 195, 81, 21));
        label_4 = new QLabel(Form_Set_spo);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 55, 71, 21));
        comboBox_6 = new QComboBox(Form_Set_spo);
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        comboBox_6->setGeometry(QRect(150, 80, 100, 30));
        comboBox_6->setMaxVisibleItems(2);
        label_9 = new QLabel(Form_Set_spo);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 125, 71, 21));
        pushButton_2 = new QPushButton(Form_Set_spo);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 240, 99, 30));
        pushButton = new QPushButton(Form_Set_spo);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 240, 99, 30));

        retranslateUi(Form_Set_spo);

        QMetaObject::connectSlotsByName(Form_Set_spo);
    } // setupUi

    void retranslateUi(QWidget *Form_Set_spo)
    {
        Form_Set_spo->setWindowTitle(QApplication::translate("Form_Set_spo", "\350\241\200\346\260\247\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_Set_spo", "\350\204\211\346\220\217\351\237\263\351\207\217", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Form_Set_spo", "\346\263\242\345\275\242\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Form_Set_spo", "\346\263\242\345\275\242\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("Form_Set_spo", "\350\204\211\346\220\217\351\237\263\350\260\203\345\210\266", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form_Set_spo", "\347\201\265\346\225\217\345\272\246", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Form_Set_spo", "\350\204\211\347\216\207", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_Set_spo", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_Set_spo", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_Set_spo: public Ui_Form_Set_spo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_SPO2_H
