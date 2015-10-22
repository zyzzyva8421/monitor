/********************************************************************************
** Form generated from reading UI file 'set_ecg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_ECG_H
#define UI_SET_ECG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_set_ecg
{
public:
    QComboBox *comboBox_10;
    QDoubleSpinBox *doubleSpinBox;
    QComboBox *comboBox_6;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_4;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_5;
    QComboBox *comboBox_4;
    QLabel *label_3;
    QComboBox *comboBox_8;
    QLabel *label_6;
    QComboBox *comboBox_2;
    QDoubleSpinBox *doubleSpinBox_3;
    QLabel *label_7;
    QLabel *label_11;
    QLabel *label_4;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QComboBox *comboBox_12;
    QLabel *label;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *pushButton_2;
    QLabel *label_8;
    QComboBox *comboBox_13;
    QLabel *label_14;
    QComboBox *comboBox_14;
    QLabel *label_15;
    QComboBox *comboBox_15;
    QLabel *label_16;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_5;
    QComboBox *comboBox_3;
    QLabel *label_17;
    QComboBox *comboBox_5;
    QLabel *label_18;

    void setupUi(QWidget *Form_set_ecg)
    {
        if (Form_set_ecg->objectName().isEmpty())
            Form_set_ecg->setObjectName(QString::fromUtf8("Form_set_ecg"));
        Form_set_ecg->resize(450, 389);
        comboBox_10 = new QComboBox(Form_set_ecg);
        comboBox_10->setObjectName(QString::fromUtf8("comboBox_10"));
        comboBox_10->setGeometry(QRect(110, 150, 100, 30));
        comboBox_10->setMaxVisibleItems(4);
        doubleSpinBox = new QDoubleSpinBox(Form_set_ecg);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(320, 120, 121, 30));
        doubleSpinBox->setMinimum(-999);
        doubleSpinBox->setMaximum(999.99);
        doubleSpinBox->setSingleStep(0.01);
        comboBox_6 = new QComboBox(Form_set_ecg);
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        comboBox_6->setGeometry(QRect(110, 80, 100, 30));
        comboBox_6->setMaxVisibleItems(15);
        label_13 = new QLabel(Form_set_ecg);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 195, 91, 20));
        doubleSpinBox_4 = new QDoubleSpinBox(Form_set_ecg);
        doubleSpinBox_4->setObjectName(QString::fromUtf8("doubleSpinBox_4"));
        doubleSpinBox_4->setGeometry(QRect(320, 225, 121, 30));
        doubleSpinBox_4->setMinimum(-999);
        doubleSpinBox_4->setMaximum(999);
        doubleSpinBox_4->setSingleStep(0.01);
        doubleSpinBox_2 = new QDoubleSpinBox(Form_set_ecg);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(320, 155, 121, 30));
        doubleSpinBox_2->setMinimum(-999);
        doubleSpinBox_2->setMaximum(999);
        doubleSpinBox_2->setSingleStep(0.01);
        label_5 = new QLabel(Form_set_ecg);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(220, 125, 75, 20));
        comboBox_4 = new QComboBox(Form_set_ecg);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(110, 45, 100, 30));
        comboBox_4->setMaxVisibleItems(7);
        label_3 = new QLabel(Form_set_ecg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(220, 15, 75, 20));
        comboBox_8 = new QComboBox(Form_set_ecg);
        comboBox_8->setObjectName(QString::fromUtf8("comboBox_8"));
        comboBox_8->setGeometry(QRect(110, 115, 100, 30));
        comboBox_8->setMaxVisibleItems(3);
        label_6 = new QLabel(Form_set_ecg);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(220, 160, 75, 20));
        comboBox_2 = new QComboBox(Form_set_ecg);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(320, 10, 120, 30));
        comboBox_2->setMaxVisibleItems(2);
        doubleSpinBox_3 = new QDoubleSpinBox(Form_set_ecg);
        doubleSpinBox_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));
        doubleSpinBox_3->setGeometry(QRect(320, 190, 121, 30));
        doubleSpinBox_3->setMinimum(-999);
        doubleSpinBox_3->setMaximum(999);
        doubleSpinBox_3->setSingleStep(0.01);
        label_7 = new QLabel(Form_set_ecg);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 90, 71, 20));
        label_11 = new QLabel(Form_set_ecg);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 160, 71, 20));
        label_4 = new QLabel(Form_set_ecg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 55, 71, 20));
        pushButton = new QPushButton(Form_set_ecg);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(90, 340, 111, 30));
        comboBox = new QComboBox(Form_set_ecg);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(110, 10, 100, 30));
        comboBox->setMaxVisibleItems(5);
        comboBox_12 = new QComboBox(Form_set_ecg);
        comboBox_12->setObjectName(QString::fromUtf8("comboBox_12"));
        comboBox_12->setGeometry(QRect(110, 185, 100, 30));
        comboBox_12->setMaxVisibleItems(4);
        label = new QLabel(Form_set_ecg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 71, 20));
        label_9 = new QLabel(Form_set_ecg);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 125, 71, 20));
        label_10 = new QLabel(Form_set_ecg);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(220, 230, 75, 20));
        pushButton_2 = new QPushButton(Form_set_ecg);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(260, 340, 121, 30));
        label_8 = new QLabel(Form_set_ecg);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(220, 195, 75, 20));
        comboBox_13 = new QComboBox(Form_set_ecg);
        comboBox_13->setObjectName(QString::fromUtf8("comboBox_13"));
        comboBox_13->setGeometry(QRect(110, 220, 100, 30));
        comboBox_13->setMaxVisibleItems(2);
        label_14 = new QLabel(Form_set_ecg);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 230, 71, 20));
        comboBox_14 = new QComboBox(Form_set_ecg);
        comboBox_14->setObjectName(QString::fromUtf8("comboBox_14"));
        comboBox_14->setGeometry(QRect(110, 255, 100, 30));
        comboBox_14->setMaxVisibleItems(4);
        label_15 = new QLabel(Form_set_ecg);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 265, 71, 20));
        comboBox_15 = new QComboBox(Form_set_ecg);
        comboBox_15->setObjectName(QString::fromUtf8("comboBox_15"));
        comboBox_15->setGeometry(QRect(110, 290, 100, 30));
        comboBox_15->setMaxVisibleItems(4);
        label_16 = new QLabel(Form_set_ecg);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 300, 91, 20));
        label_12 = new QLabel(Form_set_ecg);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(220, 265, 75, 20));
        doubleSpinBox_5 = new QDoubleSpinBox(Form_set_ecg);
        doubleSpinBox_5->setObjectName(QString::fromUtf8("doubleSpinBox_5"));
        doubleSpinBox_5->setGeometry(QRect(320, 260, 121, 30));
        doubleSpinBox_5->setMinimum(-999);
        doubleSpinBox_5->setMaximum(999);
        doubleSpinBox_5->setSingleStep(0.01);
        comboBox_3 = new QComboBox(Form_set_ecg);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(320, 45, 120, 30));
        comboBox_3->setMaxVisibleItems(2);
        label_17 = new QLabel(Form_set_ecg);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(220, 50, 91, 20));
        comboBox_5 = new QComboBox(Form_set_ecg);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(320, 80, 120, 30));
        comboBox_5->setMaxVisibleItems(2);
        label_18 = new QLabel(Form_set_ecg);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(220, 85, 75, 20));

        retranslateUi(Form_set_ecg);

        QMetaObject::connectSlotsByName(Form_set_ecg);
    } // setupUi

    void retranslateUi(QWidget *Form_set_ecg)
    {
        Form_set_ecg->setWindowTitle(QApplication::translate("Form_set_ecg", "\350\204\221\347\224\265\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("Form_set_ecg", "\350\204\221\347\224\265\346\227\266\351\227\264\345\270\270\346\225\260", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Form_set_ecg", "\350\204\221\347\224\265\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form_set_ecg", "\345\221\274\345\220\270\351\231\220\346\263\242", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Form_set_ecg", "\345\221\274\345\220\270\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Form_set_ecg", "\347\201\265  \346\225\217  \345\272\246", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Form_set_ecg", "\350\204\221\347\224\265\346\273\244\346\263\242", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form_set_ecg", "\346\263\242\345\275\242\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_set_ecg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_set_ecg", "\345\257\274\350\201\224\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Form_set_ecg", "\346\263\242\345\275\242\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Form_set_ecg", "\347\234\274\345\212\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_set_ecg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Form_set_ecg", "\350\202\214\347\224\265\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("Form_set_ecg", "\350\204\221\347\224\265\351\231\220\346\263\242", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("Form_set_ecg", "\345\221\274\345\220\270\346\273\244\346\263\242", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("Form_set_ecg", "\345\221\274\345\220\270\346\227\266\351\227\264\345\270\270\346\225\260", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Form_set_ecg", "\351\274\276\345\243\260\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("Form_set_ecg", "\351\274\276\345\243\260\346\227\266\351\227\264\345\270\270\346\225\260", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("Form_set_ecg", "\351\274\276\345\243\260\351\231\220\346\263\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_set_ecg: public Ui_Form_set_ecg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_ECG_H
