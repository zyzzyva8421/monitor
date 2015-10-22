/********************************************************************************
** Form generated from reading UI file 'serv_tiwentantou.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERV_TIWENTANTOU_H
#define UI_SERV_TIWENTANTOU_H

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

class Ui_Form_serv_tiwentantou
{
public:
    QComboBox *comboBox;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Form_serv_tiwentantou)
    {
        if (Form_serv_tiwentantou->objectName().isEmpty())
            Form_serv_tiwentantou->setObjectName(QString::fromUtf8("Form_serv_tiwentantou"));
        Form_serv_tiwentantou->resize(300, 102);
        comboBox = new QComboBox(Form_serv_tiwentantou);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(130, 20, 100, 30));
        comboBox->setMaxVisibleItems(2);
        label_2 = new QLabel(Form_serv_tiwentantou);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 25, 101, 20));
        pushButton = new QPushButton(Form_serv_tiwentantou);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 60, 111, 30));
        pushButton_2 = new QPushButton(Form_serv_tiwentantou);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 60, 121, 30));

        retranslateUi(Form_serv_tiwentantou);

        QMetaObject::connectSlotsByName(Form_serv_tiwentantou);
    } // setupUi

    void retranslateUi(QWidget *Form_serv_tiwentantou)
    {
        Form_serv_tiwentantou->setWindowTitle(QApplication::translate("Form_serv_tiwentantou", "\344\275\223\346\270\251\346\216\242\345\244\264\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form_serv_tiwentantou", "\344\275\223\346\270\251\346\216\242\345\244\264\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_serv_tiwentantou", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_serv_tiwentantou", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_serv_tiwentantou: public Ui_Form_serv_tiwentantou {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERV_TIWENTANTOU_H
