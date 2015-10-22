/********************************************************************************
** Form generated from reading UI file 'set_time.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_TIME_H
#define UI_SET_TIME_H

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

class Ui_Set_shijianshezhi
{
public:
    QLabel *label_7;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QPushButton *pushButton;
    QLabel *label_6;
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;

    void setupUi(QWidget *Set_shijianshezhi)
    {
        if (Set_shijianshezhi->objectName().isEmpty())
            Set_shijianshezhi->setObjectName(QString::fromUtf8("Set_shijianshezhi"));
        Set_shijianshezhi->resize(300, 320);
        label_7 = new QLabel(Set_shijianshezhi);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 235, 40, 20));
        label_2 = new QLabel(Set_shijianshezhi);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 60, 40, 20));
        label_5 = new QLabel(Set_shijianshezhi);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(60, 165, 40, 20));
        label_3 = new QLabel(Set_shijianshezhi);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 95, 40, 20));
        pushButton = new QPushButton(Set_shijianshezhi);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 280, 99, 27));
        label_6 = new QLabel(Set_shijianshezhi);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(60, 200, 40, 20));
        comboBox = new QComboBox(Set_shijianshezhi);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(150, 15, 100, 30));
        comboBox->setMaxVisibleItems(3);
        label = new QLabel(Set_shijianshezhi);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 70, 20));
        pushButton_2 = new QPushButton(Set_shijianshezhi);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 280, 99, 27));
        label_4 = new QLabel(Set_shijianshezhi);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 130, 40, 20));
        spinBox = new QSpinBox(Set_shijianshezhi);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(150, 55, 101, 30));
        spinBox->setMinimum(1900);
        spinBox->setMaximum(2200);
        spinBox->setValue(2015);
        spinBox_2 = new QSpinBox(Set_shijianshezhi);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(150, 90, 101, 30));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(12);
        spinBox_2->setValue(1);
        spinBox_3 = new QSpinBox(Set_shijianshezhi);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(150, 125, 101, 30));
        spinBox_3->setMinimum(1);
        spinBox_3->setMaximum(31);
        spinBox_4 = new QSpinBox(Set_shijianshezhi);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(150, 160, 101, 30));
        spinBox_4->setMaximum(59);
        spinBox_5 = new QSpinBox(Set_shijianshezhi);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));
        spinBox_5->setGeometry(QRect(150, 195, 101, 30));
        spinBox_5->setMaximum(59);
        spinBox_6 = new QSpinBox(Set_shijianshezhi);
        spinBox_6->setObjectName(QString::fromUtf8("spinBox_6"));
        spinBox_6->setGeometry(QRect(150, 230, 101, 30));
        spinBox_6->setMaximum(59);

        retranslateUi(Set_shijianshezhi);

        QMetaObject::connectSlotsByName(Set_shijianshezhi);
    } // setupUi

    void retranslateUi(QWidget *Set_shijianshezhi)
    {
        Set_shijianshezhi->setWindowTitle(QApplication::translate("Set_shijianshezhi", "\346\227\266\351\227\264\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Set_shijianshezhi", "\347\247\222", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Set_shijianshezhi", "\345\271\264", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Set_shijianshezhi", "\346\227\266", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Set_shijianshezhi", "\346\234\210", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Set_shijianshezhi", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Set_shijianshezhi", "\345\210\206", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Set_shijianshezhi", "\346\227\266\351\227\264\346\240\274\345\274\217", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Set_shijianshezhi", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Set_shijianshezhi", "\346\227\245", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Set_shijianshezhi: public Ui_Set_shijianshezhi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_TIME_H
