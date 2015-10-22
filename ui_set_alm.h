/********************************************************************************
** Form generated from reading UI file 'set_alm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_ALM_H
#define UI_SET_ALM_H

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

class Ui_Set_baojingshezhi
{
public:
    QLabel *label;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QLabel *label_4;
    QComboBox *comboBox_4;
    QLabel *label_5;
    QComboBox *comboBox_5;
    QLabel *label_6;
    QComboBox *comboBox_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Set_baojingshezhi)
    {
        if (Set_baojingshezhi->objectName().isEmpty())
            Set_baojingshezhi->setObjectName(QString::fromUtf8("Set_baojingshezhi"));
        Set_baojingshezhi->resize(300, 300);
        Set_baojingshezhi->setFocusPolicy(Qt::WheelFocus);
        label = new QLabel(Set_baojingshezhi);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 70, 20));
        comboBox = new QComboBox(Set_baojingshezhi);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(150, 15, 100, 30));
        comboBox_2 = new QComboBox(Set_baojingshezhi);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(150, 50, 100, 30));
        comboBox_2->setMaxVisibleItems(2);
        label_2 = new QLabel(Set_baojingshezhi);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 55, 70, 20));
        label_3 = new QLabel(Set_baojingshezhi);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 90, 70, 20));
        comboBox_3 = new QComboBox(Set_baojingshezhi);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(150, 85, 100, 30));
        comboBox_3->setMaxVisibleItems(2);
        label_4 = new QLabel(Set_baojingshezhi);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 125, 70, 20));
        comboBox_4 = new QComboBox(Set_baojingshezhi);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(150, 120, 100, 30));
        comboBox_4->setMaxVisibleItems(2);
        label_5 = new QLabel(Set_baojingshezhi);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 160, 70, 20));
        comboBox_5 = new QComboBox(Set_baojingshezhi);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(150, 155, 100, 30));
        comboBox_5->setMaxVisibleItems(2);
        label_6 = new QLabel(Set_baojingshezhi);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 195, 70, 20));
        comboBox_6 = new QComboBox(Set_baojingshezhi);
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        comboBox_6->setGeometry(QRect(150, 190, 100, 30));
        comboBox_6->setMaxVisibleItems(2);
        pushButton = new QPushButton(Set_baojingshezhi);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 260, 99, 27));
        pushButton_2 = new QPushButton(Set_baojingshezhi);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 260, 99, 27));

        retranslateUi(Set_baojingshezhi);

        QMetaObject::connectSlotsByName(Set_baojingshezhi);
    } // setupUi

    void retranslateUi(QWidget *Set_baojingshezhi)
    {
        Set_baojingshezhi->setWindowTitle(QApplication::translate("Set_baojingshezhi", "\346\212\245\350\255\246\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Set_baojingshezhi", "\346\212\245\350\255\246\351\237\263\351\207\217", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Set_baojingshezhi", "\346\232\202\345\201\234\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Set_baojingshezhi", "\351\227\252        \347\203\201", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Set_baojingshezhi", "\345\217\202\346\225\260\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Set_baojingshezhi", "\346\212\245\350\255\246\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Set_baojingshezhi", "\350\257\255\351\237\263\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Set_baojingshezhi", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Set_baojingshezhi", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Set_baojingshezhi: public Ui_Set_baojingshezhi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_ALM_H
