/********************************************************************************
** Form generated from reading UI file 'set_tiwen_dlg.ui'
**
** Created: Tue Jun 9 17:08:54 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_TIWEN_DLG_H
#define UI_SET_TIWEN_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dlg_set_tiwen
{
public:
    QPushButton *pushButton_2;
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *Dlg_set_tiwen)
    {
        if (Dlg_set_tiwen->objectName().isEmpty())
            Dlg_set_tiwen->setObjectName(QString::fromUtf8("Dlg_set_tiwen"));
        Dlg_set_tiwen->resize(300, 124);
        pushButton_2 = new QPushButton(Dlg_set_tiwen);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 70, 99, 30));
        comboBox = new QComboBox(Dlg_set_tiwen);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(160, 20, 100, 30));
        comboBox->setMaxVisibleItems(2);
        label = new QLabel(Dlg_set_tiwen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 71, 21));
        pushButton = new QPushButton(Dlg_set_tiwen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 70, 99, 30));

        retranslateUi(Dlg_set_tiwen);

        QMetaObject::connectSlotsByName(Dlg_set_tiwen);
    } // setupUi

    void retranslateUi(QDialog *Dlg_set_tiwen)
    {
        Dlg_set_tiwen->setWindowTitle(QApplication::translate("Dlg_set_tiwen", "\344\275\223\346\270\251\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Dlg_set_tiwen", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dlg_set_tiwen", "\345\215\225         \344\275\215", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Dlg_set_tiwen", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dlg_set_tiwen: public Ui_Dlg_set_tiwen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_TIWEN_DLG_H
