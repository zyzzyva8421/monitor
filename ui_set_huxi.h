/********************************************************************************
** Form generated from reading UI file 'set_huxi.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_HUXI_H
#define UI_SET_HUXI_H

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

class Ui_Form_set_huxi
{
public:
    QLabel *label_7;
    QLabel *label_4;
    QComboBox *comboBox_6;
    QComboBox *comboBox;
    QComboBox *comboBox_4;
    QLabel *label;
    QComboBox *comboBox_7;
    QLabel *label_8;
    QComboBox *comboBox_8;
    QLabel *label_9;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QWidget *Form_set_huxi)
    {
        if (Form_set_huxi->objectName().isEmpty())
            Form_set_huxi->setObjectName(QString::fromUtf8("Form_set_huxi"));
        Form_set_huxi->resize(300, 300);
        label_7 = new QLabel(Form_set_huxi);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 110, 71, 21));
        label_4 = new QLabel(Form_set_huxi);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 70, 71, 21));
        comboBox_6 = new QComboBox(Form_set_huxi);
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        comboBox_6->setGeometry(QRect(160, 100, 100, 30));
        comboBox_6->setMaxVisibleItems(3);
        comboBox = new QComboBox(Form_set_huxi);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(160, 20, 100, 30));
        comboBox->setMaxVisibleItems(8);
        comboBox_4 = new QComboBox(Form_set_huxi);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(160, 60, 100, 30));
        comboBox_4->setMaxVisibleItems(5);
        label = new QLabel(Form_set_huxi);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 71, 21));
        comboBox_7 = new QComboBox(Form_set_huxi);
        comboBox_7->setObjectName(QString::fromUtf8("comboBox_7"));
        comboBox_7->setGeometry(QRect(160, 140, 100, 30));
        comboBox_7->setMaxVisibleItems(2);
        label_8 = new QLabel(Form_set_huxi);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 150, 71, 21));
        comboBox_8 = new QComboBox(Form_set_huxi);
        comboBox_8->setObjectName(QString::fromUtf8("comboBox_8"));
        comboBox_8->setGeometry(QRect(160, 180, 100, 30));
        comboBox_8->setMaxVisibleItems(2);
        label_9 = new QLabel(Form_set_huxi);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 190, 71, 21));
        pushButton_2 = new QPushButton(Form_set_huxi);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 250, 99, 30));
        pushButton = new QPushButton(Form_set_huxi);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 250, 99, 30));

        retranslateUi(Form_set_huxi);

        QMetaObject::connectSlotsByName(Form_set_huxi);
    } // setupUi

    void retranslateUi(QWidget *Form_set_huxi)
    {
        Form_set_huxi->setWindowTitle(QApplication::translate("Form_set_huxi", "\345\221\274\345\220\270\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Form_set_huxi", "\346\263\242\345\275\242\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form_set_huxi", "\346\263\242\345\275\242\345\271\205\345\272\246", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_set_huxi", "\347\252\222\346\201\257\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Form_set_huxi", "\345\221\274\345\220\270\345\257\274\350\201\224", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Form_set_huxi", "\345\221\274\345\220\270\346\235\245\346\272\220", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_set_huxi", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_set_huxi", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_set_huxi: public Ui_Form_set_huxi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_HUXI_H
