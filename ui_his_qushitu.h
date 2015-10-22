/********************************************************************************
** Form generated from reading UI file 'his_qushitu.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIS_QUSHITU_H
#define UI_HIS_QUSHITU_H

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

class Ui_widget
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *comboBox;
    QLabel *label_5;
    QComboBox *comboBox_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;

    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QString::fromUtf8("widget"));
        widget->resize(450, 337);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 71, 20));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 10, 68, 20));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 10, 71, 20));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 220, 50, 20));
        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(100, 220, 85, 27));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(240, 220, 71, 20));
        comboBox_3 = new QComboBox(widget);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(310, 220, 85, 27));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 260, 51, 27));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(90, 260, 51, 27));
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(150, 260, 51, 27));
        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(210, 260, 51, 27));
        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(270, 260, 51, 27));
        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(330, 260, 51, 27));
        pushButton_7 = new QPushButton(widget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(150, 300, 150, 30));

        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QWidget *widget)
    {
        widget->setWindowTitle(QApplication::translate("widget", "\350\266\213\345\212\277\345\233\276", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("widget", "\345\277\203\347\216\207", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("widget", "\346\227\245\346\234\237", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("widget", "\347\227\205\344\272\272\345\247\223\345\220\215", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("widget", "\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("widget", "\346\227\266\351\227\264\351\227\264\351\232\224", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("widget", "|<", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("widget", "<<", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("widget", "<", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("widget", ">", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("widget", ">>", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("widget", ">|", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("widget", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HIS_QUSHITU_H
