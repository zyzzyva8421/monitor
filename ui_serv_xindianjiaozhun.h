/********************************************************************************
** Form generated from reading UI file 'serv_xindianjiaozhun.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERV_XINDIANJIAOZHUN_H
#define UI_SERV_XINDIANJIAOZHUN_H

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

class Ui_Form_serv_xindianjiaozhun
{
public:
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QWidget *Form_serv_xindianjiaozhun)
    {
        if (Form_serv_xindianjiaozhun->objectName().isEmpty())
            Form_serv_xindianjiaozhun->setObjectName(QString::fromUtf8("Form_serv_xindianjiaozhun"));
        Form_serv_xindianjiaozhun->resize(300, 141);
        label_2 = new QLabel(Form_serv_xindianjiaozhun);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 35, 71, 20));
        comboBox = new QComboBox(Form_serv_xindianjiaozhun);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(120, 30, 100, 30));
        comboBox->setMaxVisibleItems(2);
        pushButton_2 = new QPushButton(Form_serv_xindianjiaozhun);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 90, 121, 30));
        pushButton = new QPushButton(Form_serv_xindianjiaozhun);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 90, 111, 30));

        retranslateUi(Form_serv_xindianjiaozhun);

        QMetaObject::connectSlotsByName(Form_serv_xindianjiaozhun);
    } // setupUi

    void retranslateUi(QWidget *Form_serv_xindianjiaozhun)
    {
        Form_serv_xindianjiaozhun->setWindowTitle(QApplication::translate("Form_serv_xindianjiaozhun", "\345\277\203\347\224\265\346\240\241\345\207\206", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form_serv_xindianjiaozhun", "\345\277\203\347\224\265\346\240\241\345\207\206", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_serv_xindianjiaozhun", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_serv_xindianjiaozhun", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_serv_xindianjiaozhun: public Ui_Form_serv_xindianjiaozhun {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERV_XINDIANJIAOZHUN_H
