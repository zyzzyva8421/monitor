/********************************************************************************
** Form generated from reading UI file 'his_nibp_huigu.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIS_NIBP_HUIGU_H
#define UI_HIS_NIBP_HUIGU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xueyahuigu
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_7;

    void setupUi(QWidget *xueyahuigu)
    {
        if (xueyahuigu->objectName().isEmpty())
            xueyahuigu->setObjectName(QString::fromUtf8("xueyahuigu"));
        xueyahuigu->resize(507, 425);
        tableWidget = new QTableWidget(xueyahuigu);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        if (tableWidget->rowCount() < 10)
            tableWidget->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget->setItem(0, 0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget->setItem(0, 1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget->setItem(0, 2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget->setItem(0, 3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget->setItem(1, 0, __qtablewidgetitem4);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 507, 327));
        tableWidget->setLineWidth(1);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setAutoScroll(false);
        tableWidget->setRowCount(10);
        tableWidget->setColumnCount(4);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setMinimumSectionSize(30);
        tableWidget->verticalHeader()->setVisible(true);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);
        tableWidget->verticalHeader()->setHighlightSections(true);
        tableWidget->verticalHeader()->setMinimumSectionSize(30);
        pushButton_6 = new QPushButton(xueyahuigu);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(360, 340, 51, 27));
        pushButton_4 = new QPushButton(xueyahuigu);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(240, 340, 51, 27));
        pushButton_5 = new QPushButton(xueyahuigu);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(300, 340, 51, 27));
        pushButton = new QPushButton(xueyahuigu);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 340, 51, 27));
        pushButton_3 = new QPushButton(xueyahuigu);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(180, 340, 51, 27));
        pushButton_2 = new QPushButton(xueyahuigu);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(120, 340, 51, 27));
        pushButton_7 = new QPushButton(xueyahuigu);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(160, 380, 150, 30));

        retranslateUi(xueyahuigu);

        QMetaObject::connectSlotsByName(xueyahuigu);
    } // setupUi

    void retranslateUi(QWidget *xueyahuigu)
    {
        xueyahuigu->setWindowTitle(QApplication::translate("xueyahuigu", "\346\227\240\345\210\233\350\241\200\345\216\213\345\233\236\351\241\276", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = tableWidget->item(0, 0);
        ___qtablewidgetitem->setText(QApplication::translate("xueyahuigu", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->item(0, 1);
        ___qtablewidgetitem1->setText(QApplication::translate("xueyahuigu", "\346\224\266\347\274\251\345\216\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->item(0, 2);
        ___qtablewidgetitem2->setText(QApplication::translate("xueyahuigu", "\350\210\222\345\274\240\345\216\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(0, 3);
        ___qtablewidgetitem3->setText(QApplication::translate("xueyahuigu", "\345\271\263\345\235\207\345\216\213", 0, QApplication::UnicodeUTF8));
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton_6->setText(QApplication::translate("xueyahuigu", ">|", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("xueyahuigu", ">", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("xueyahuigu", ">>", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("xueyahuigu", "|<", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("xueyahuigu", "<", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("xueyahuigu", "<<", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("xueyahuigu", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class xueyahuigu: public Ui_xueyahuigu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HIS_NIBP_HUIGU_H
