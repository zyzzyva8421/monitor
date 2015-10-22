/********************************************************************************
** Form generated from reading UI file 'set_nibp.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_NIBP_H
#define UI_SET_NIBP_H

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

class Ui_Form_Set_nibp
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QComboBox *comboBox;
    QLabel *label;
    QComboBox *comboBox_4;
    QLabel *label_4;
    QComboBox *comboBox_6;
    QLabel *label_7;

    void setupUi(QWidget *Form_Set_nibp)
    {
        if (Form_Set_nibp->objectName().isEmpty())
            Form_Set_nibp->setObjectName(QString::fromUtf8("Form_Set_nibp"));
        Form_Set_nibp->resize(300, 211);
        pushButton = new QPushButton(Form_Set_nibp);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 160, 99, 30));
        pushButton_2 = new QPushButton(Form_Set_nibp);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 160, 99, 30));
        comboBox = new QComboBox(Form_Set_nibp);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(160, 20, 100, 30));
        comboBox->setMaxVisibleItems(2);
        label = new QLabel(Form_Set_nibp);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 71, 21));
        comboBox_4 = new QComboBox(Form_Set_nibp);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(160, 60, 100, 30));
        comboBox_4->setMaxVisibleItems(3);
        label_4 = new QLabel(Form_Set_nibp);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 70, 71, 21));
        comboBox_6 = new QComboBox(Form_Set_nibp);
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        comboBox_6->setGeometry(QRect(160, 100, 100, 30));
        comboBox_6->setMaxVisibleItems(14);
        label_7 = new QLabel(Form_Set_nibp);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 110, 71, 21));

        retranslateUi(Form_Set_nibp);

        QMetaObject::connectSlotsByName(Form_Set_nibp);
    } // setupUi

    void retranslateUi(QWidget *Form_Set_nibp)
    {
        Form_Set_nibp->setWindowTitle(QApplication::translate("Form_Set_nibp", "\346\227\240\345\210\233\350\241\200\345\216\213\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form_Set_nibp", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form_Set_nibp", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form_Set_nibp", "\345\215\225         \344\275\215", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form_Set_nibp", "\346\265\213\351\207\217\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Form_Set_nibp", "\351\227\264\351\232\224\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form_Set_nibp: public Ui_Form_Set_nibp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_NIBP_H
