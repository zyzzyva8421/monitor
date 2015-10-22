/********************************************************************************
** Form generated from reading UI file 'alm_mashen.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALM_MASHEN_H
#define UI_ALM_MASHEN_H

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

class Ui_Form_alm_mashen
{
public:
    QComboBox *comboBox;
    QLabel *label_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpinBox *spinBox_2;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label;
    QSpinBox *spinBox;

    void setupUi(QWidget *Form_alm_mashen)
    {
        if (Form_alm_mashen->objectName().isEmpty())
            Form_alm_mashen->setObjectName(QString::fromUtf8("Form_alm_mashen"));
        Form_alm_mashen->resize(400, 122);
        comboBox = new QComboBox(Form_alm_mashen);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(90, 40, 61, 27));
        comboBox->setMaxVisibleItems(2);
        label_4 = new QLabel(Form_alm_mashen);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(180, 10, 71, 20));
        pushButton = new QPushButton(Form_alm_mashen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 80, 111, 30));
        pushButton_2 = new QPushButton(Form_alm_mashen);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 80, 121, 30));
        spinBox_2 = new QSpinBox(Form_alm_mashen);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(280, 40, 91, 27));
        spinBox_2->setMaximum(100);
        spinBox_2->setValue(80);
        label_5 = new QLabel(Form_alm_mashen);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(290, 10, 71, 20));
        label_3 = new QLabel(Form_alm_mashen);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 10, 51, 20));
        label = new QLabel(Form_alm_mashen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 61, 20));
        spinBox = new QSpinBox(Form_alm_mashen);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(180, 40, 91, 27));
        spinBox->setMaximum(100);
        spinBox->setValue(90);

        retranslateUi(Form_alm_mashen);

        QMetaObject::connectSlotsByName(Form_alm_mashen);
    } // setupUi

    void retranslateUi(QWidget *Form_alm_mashen)
    {
        Form_alm_mashen->setWindowTitle(QApplication::translate("Form_alm_mashen", "\351\272\273\351\206\211\346\267\261\345\272\246\346\212\245\350\255\246\351\231\220\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form_alm_mashen", "\346\212\245\350\255\246\351\253\230\351\231\220", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_alm_mashen", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_alm_mashen", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Form_alm_mashen", "\346\212\245\350\255\246\344\275\216\351\231\220", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form_alm_mashen", "\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_alm_mashen", "\351\272\273\351\206\211\346\267\261\345\272\246", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_alm_mashen: public Ui_Form_alm_mashen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALM_MASHEN_H
