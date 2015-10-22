/********************************************************************************
** Form generated from reading UI file 'alm_huxi.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALM_HUXI_H
#define UI_ALM_HUXI_H

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

class Ui_Form_alm_huxi
{
public:
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_4;
    QSpinBox *spinBox;
    QLabel *label;
    QSpinBox *spinBox_2;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Form_alm_huxi)
    {
        if (Form_alm_huxi->objectName().isEmpty())
            Form_alm_huxi->setObjectName(QString::fromUtf8("Form_alm_huxi"));
        Form_alm_huxi->resize(400, 139);
        label_3 = new QLabel(Form_alm_huxi);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 20, 51, 20));
        label_5 = new QLabel(Form_alm_huxi);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(280, 20, 71, 20));
        label_4 = new QLabel(Form_alm_huxi);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 20, 71, 20));
        spinBox = new QSpinBox(Form_alm_huxi);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(170, 50, 91, 27));
        spinBox->setMaximum(300);
        spinBox->setValue(90);
        label = new QLabel(Form_alm_huxi);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 50, 51, 20));
        spinBox_2 = new QSpinBox(Form_alm_huxi);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(270, 50, 91, 27));
        spinBox_2->setMaximum(300);
        spinBox_2->setValue(80);
        comboBox = new QComboBox(Form_alm_huxi);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(80, 50, 61, 27));
        comboBox->setMaxVisibleItems(2);
        pushButton = new QPushButton(Form_alm_huxi);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 90, 111, 30));
        pushButton_2 = new QPushButton(Form_alm_huxi);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 90, 121, 30));

        retranslateUi(Form_alm_huxi);

        QMetaObject::connectSlotsByName(Form_alm_huxi);
    } // setupUi

    void retranslateUi(QWidget *Form_alm_huxi)
    {
        Form_alm_huxi->setWindowTitle(QApplication::translate("Form_alm_huxi", "\345\221\274\345\220\270\346\212\245\350\255\246\351\231\220\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form_alm_huxi", "\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Form_alm_huxi", "\346\212\245\350\255\246\344\275\216\351\231\220", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form_alm_huxi", "\346\212\245\350\255\246\351\253\230\351\231\220", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_alm_huxi", "\345\221\274\345\220\270", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_alm_huxi", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_alm_huxi", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_alm_huxi: public Ui_Form_alm_huxi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALM_HUXI_H
