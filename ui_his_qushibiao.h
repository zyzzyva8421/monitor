/********************************************************************************
** Form generated from reading UI file 'his_qushibiao.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIS_QUSHIBIAO_H
#define UI_HIS_QUSHIBIAO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_His_qushibiao
{
public:
    QTableWidget *tableWidget;
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *pushButton_13;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_7;

    void setupUi(QWidget *His_qushibiao)
    {
        if (His_qushibiao->objectName().isEmpty())
            His_qushibiao->setObjectName(QString::fromUtf8("His_qushibiao"));
        His_qushibiao->resize(600, 458);
        tableWidget = new QTableWidget(His_qushibiao);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        if (tableWidget->rowCount() < 10)
            tableWidget->setRowCount(10);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(50, 20, 501, 301));
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setMidLineWidth(1);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setAutoScroll(false);
        tableWidget->setAutoScrollMargin(16);
        tableWidget->setRowCount(10);
        tableWidget->setColumnCount(6);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->verticalHeader()->setVisible(false);
        comboBox = new QComboBox(His_qushibiao);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(280, 330, 150, 35));
        label = new QLabel(His_qushibiao);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 335, 80, 31));
        label->setAlignment(Qt::AlignCenter);
        pushButton_13 = new QPushButton(His_qushibiao);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(420, 380, 51, 27));
        pushButton_11 = new QPushButton(His_qushibiao);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(180, 380, 51, 27));
        pushButton_12 = new QPushButton(His_qushibiao);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(300, 380, 51, 27));
        pushButton_8 = new QPushButton(His_qushibiao);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(240, 380, 51, 27));
        pushButton_9 = new QPushButton(His_qushibiao);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(120, 380, 51, 27));
        pushButton_10 = new QPushButton(His_qushibiao);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(360, 380, 51, 27));
        pushButton_7 = new QPushButton(His_qushibiao);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(220, 420, 150, 30));

        retranslateUi(His_qushibiao);

        QMetaObject::connectSlotsByName(His_qushibiao);
    } // setupUi

    void retranslateUi(QWidget *His_qushibiao)
    {
        His_qushibiao->setWindowTitle(QApplication::translate("His_qushibiao", "\350\266\213\345\212\277\350\241\250", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("His_qushibiao", "\346\227\266\351\227\264\351\227\264\351\232\224", 0, QApplication::UnicodeUTF8));
        pushButton_13->setText(QApplication::translate("His_qushibiao", ">|", 0, QApplication::UnicodeUTF8));
        pushButton_11->setText(QApplication::translate("His_qushibiao", "<<", 0, QApplication::UnicodeUTF8));
        pushButton_12->setText(QApplication::translate("His_qushibiao", ">", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("His_qushibiao", "<", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("His_qushibiao", "|<", 0, QApplication::UnicodeUTF8));
        pushButton_10->setText(QApplication::translate("His_qushibiao", ">>", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("His_qushibiao", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class His_qushibiao: public Ui_His_qushibiao {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HIS_QUSHIBIAO_H
