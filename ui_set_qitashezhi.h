/********************************************************************************
** Form generated from reading UI file 'set_qitashezhi.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_QITASHEZHI_H
#define UI_SET_QITASHEZHI_H

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

class Ui_Set_qita
{
public:
    QComboBox *comboBox_2;
    QLabel *label_8;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QWidget *Set_qita)
    {
        if (Set_qita->objectName().isEmpty())
            Set_qita->setObjectName(QString::fromUtf8("Set_qita"));
        Set_qita->resize(300, 204);
        comboBox_2 = new QComboBox(Set_qita);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(150, 20, 100, 30));
        comboBox_2->setMaxVisibleItems(10);
        label_8 = new QLabel(Set_qita);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 25, 70, 20));
        label = new QLabel(Set_qita);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 65, 70, 20));
        comboBox = new QComboBox(Set_qita);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(150, 60, 100, 30));
        comboBox->setMaxVisibleItems(10);
        label_2 = new QLabel(Set_qita);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 105, 70, 20));
        comboBox_3 = new QComboBox(Set_qita);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(150, 100, 100, 30));
        comboBox_3->setMaxVisibleItems(2);
        pushButton_2 = new QPushButton(Set_qita);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 160, 99, 27));
        pushButton = new QPushButton(Set_qita);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 160, 99, 27));

        retranslateUi(Set_qita);

        QMetaObject::connectSlotsByName(Set_qita);
    } // setupUi

    void retranslateUi(QWidget *Set_qita)
    {
        Set_qita->setWindowTitle(QApplication::translate("Set_qita", "\345\205\266\344\273\226\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Set_qita", "\344\272\256\345\272\246", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Set_qita", "\346\212\245\350\255\246\351\237\263\351\207\217", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Set_qita", "\346\263\242\345\275\242\345\271\263\346\273\221", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Set_qita", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Set_qita", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Set_qita: public Ui_Set_qita {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_QITASHEZHI_H
