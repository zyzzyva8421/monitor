/********************************************************************************
** Form generated from reading UI file 'alm_ecg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALM_ECG_H
#define UI_ALM_ECG_H

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

class Ui_Form_alm_ecg
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QComboBox *comboBox;
    QComboBox *comboBox_2;

    void setupUi(QWidget *Form_alm_ecg)
    {
        if (Form_alm_ecg->objectName().isEmpty())
            Form_alm_ecg->setObjectName(QString::fromUtf8("Form_alm_ecg"));
        Form_alm_ecg->resize(400, 183);
        label = new QLabel(Form_alm_ecg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 50, 51, 20));
        label_2 = new QLabel(Form_alm_ecg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 80, 51, 20));
        label_3 = new QLabel(Form_alm_ecg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 20, 51, 20));
        label_4 = new QLabel(Form_alm_ecg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 20, 71, 20));
        label_5 = new QLabel(Form_alm_ecg);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(280, 20, 71, 20));
        pushButton_2 = new QPushButton(Form_alm_ecg);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 130, 121, 30));
        pushButton = new QPushButton(Form_alm_ecg);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 130, 111, 30));
        spinBox = new QSpinBox(Form_alm_ecg);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(170, 50, 91, 27));
        spinBox->setMaximum(300);
        spinBox_2 = new QSpinBox(Form_alm_ecg);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(270, 50, 91, 27));
        spinBox_2->setMaximum(300);
        spinBox_3 = new QSpinBox(Form_alm_ecg);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(170, 80, 91, 27));
        spinBox_3->setMaximum(300);
        spinBox_4 = new QSpinBox(Form_alm_ecg);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(270, 80, 91, 27));
        spinBox_4->setMaximum(300);
        comboBox = new QComboBox(Form_alm_ecg);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(80, 50, 61, 27));
        comboBox->setMaxVisibleItems(2);
        comboBox_2 = new QComboBox(Form_alm_ecg);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(80, 80, 61, 27));
        comboBox_2->setMaxVisibleItems(2);

        retranslateUi(Form_alm_ecg);

        QMetaObject::connectSlotsByName(Form_alm_ecg);
    } // setupUi

    void retranslateUi(QWidget *Form_alm_ecg)
    {
        Form_alm_ecg->setWindowTitle(QApplication::translate("Form_alm_ecg", "\345\277\203\347\224\265\346\212\245\350\255\246\351\231\220\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_alm_ecg", "\345\277\203\345\276\213", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form_alm_ecg", "ST\345\200\274", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form_alm_ecg", "\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form_alm_ecg", "\346\212\245\350\255\246\351\253\230\351\231\220", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Form_alm_ecg", "\346\212\245\350\255\246\344\275\216\351\231\220", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_alm_ecg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_alm_ecg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_alm_ecg: public Ui_Form_alm_ecg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALM_ECG_H
