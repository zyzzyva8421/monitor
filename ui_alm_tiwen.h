/********************************************************************************
** Form generated from reading UI file 'alm_tiwen.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALM_TIWEN_H
#define UI_ALM_TIWEN_H

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

class Ui_Form_alm_tiwen
{
public:
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLabel *label_5;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox;
    QLabel *label_4;
    QPushButton *pushButton;
    QLabel *label;
    QComboBox *comboBox;

    void setupUi(QWidget *Form_alm_tiwen)
    {
        if (Form_alm_tiwen->objectName().isEmpty())
            Form_alm_tiwen->setObjectName(QString::fromUtf8("Form_alm_tiwen"));
        Form_alm_tiwen->resize(400, 128);
        pushButton_2 = new QPushButton(Form_alm_tiwen);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 80, 121, 30));
        label_3 = new QLabel(Form_alm_tiwen);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 10, 51, 20));
        label_5 = new QLabel(Form_alm_tiwen);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(290, 10, 71, 20));
        spinBox_2 = new QSpinBox(Form_alm_tiwen);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(280, 40, 91, 27));
        spinBox_2->setMaximum(300);
        spinBox_2->setValue(80);
        spinBox = new QSpinBox(Form_alm_tiwen);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(180, 40, 91, 27));
        spinBox->setMaximum(300);
        spinBox->setValue(90);
        label_4 = new QLabel(Form_alm_tiwen);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(180, 10, 71, 20));
        pushButton = new QPushButton(Form_alm_tiwen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 80, 111, 30));
        label = new QLabel(Form_alm_tiwen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 40, 51, 20));
        comboBox = new QComboBox(Form_alm_tiwen);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(90, 40, 61, 27));
        comboBox->setMaxVisibleItems(2);

        retranslateUi(Form_alm_tiwen);

        QMetaObject::connectSlotsByName(Form_alm_tiwen);
    } // setupUi

    void retranslateUi(QWidget *Form_alm_tiwen)
    {
        Form_alm_tiwen->setWindowTitle(QApplication::translate("Form_alm_tiwen", "\344\275\223\346\270\251\346\212\245\350\255\246\351\231\220\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_alm_tiwen", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form_alm_tiwen", "\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Form_alm_tiwen", "\346\212\245\350\255\246\344\275\216\351\231\220", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form_alm_tiwen", "\346\212\245\350\255\246\351\253\230\351\231\220", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_alm_tiwen", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_alm_tiwen", "\344\275\223\346\270\251", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_alm_tiwen: public Ui_Form_alm_tiwen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALM_TIWEN_H
