/********************************************************************************
** Form generated from reading UI file 'set_tiwen.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_TIWEN_H
#define UI_SET_TIWEN_H

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

class Ui_Form_set_tiwen
{
public:
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Form_set_tiwen)
    {
        if (Form_set_tiwen->objectName().isEmpty())
            Form_set_tiwen->setObjectName(QString::fromUtf8("Form_set_tiwen"));
        Form_set_tiwen->resize(300, 125);
        comboBox = new QComboBox(Form_set_tiwen);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(160, 20, 100, 30));
        comboBox->setMaxVisibleItems(2);
        label = new QLabel(Form_set_tiwen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 71, 21));
        pushButton = new QPushButton(Form_set_tiwen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 70, 99, 30));
        pushButton_2 = new QPushButton(Form_set_tiwen);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 70, 99, 30));

        retranslateUi(Form_set_tiwen);

        QMetaObject::connectSlotsByName(Form_set_tiwen);
    } // setupUi

    void retranslateUi(QWidget *Form_set_tiwen)
    {
        Form_set_tiwen->setWindowTitle(QApplication::translate("Form_set_tiwen", "\344\275\223\346\270\251\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_set_tiwen", "\345\215\225         \344\275\215", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_set_tiwen", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_set_tiwen", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_set_tiwen: public Ui_Form_set_tiwen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_TIWEN_H
