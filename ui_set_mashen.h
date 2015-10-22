/********************************************************************************
** Form generated from reading UI file 'set_mashen.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_MASHEN_H
#define UI_SET_MASHEN_H

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

class Ui_Form_set_mashen
{
public:
    QComboBox *comboBox_2;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QWidget *Form_set_mashen)
    {
        if (Form_set_mashen->objectName().isEmpty())
            Form_set_mashen->setObjectName(QString::fromUtf8("Form_set_mashen"));
        Form_set_mashen->resize(300, 206);
        comboBox_2 = new QComboBox(Form_set_mashen);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(120, 70, 120, 30));
        comboBox_2->setMaxVisibleItems(3);
        comboBox = new QComboBox(Form_set_mashen);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(120, 20, 121, 30));
        comboBox->setMaxVisibleItems(7);
        label = new QLabel(Form_set_mashen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 81, 20));
        label_3 = new QLabel(Form_set_mashen);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 80, 75, 20));
        pushButton_2 = new QPushButton(Form_set_mashen);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 140, 121, 30));
        pushButton = new QPushButton(Form_set_mashen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 140, 111, 30));

        retranslateUi(Form_set_mashen);

        QMetaObject::connectSlotsByName(Form_set_mashen);
    } // setupUi

    void retranslateUi(QWidget *Form_set_mashen)
    {
        Form_set_mashen->setWindowTitle(QApplication::translate("Form_set_mashen", "\351\272\273\351\206\211\346\267\261\345\272\246\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_set_mashen", "\350\204\221\347\224\265\346\263\242\345\271\205\345\272\246", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form_set_mashen", "\346\263\242\345\275\242\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_set_mashen", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_set_mashen", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_set_mashen: public Ui_Form_set_mashen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_MASHEN_H
