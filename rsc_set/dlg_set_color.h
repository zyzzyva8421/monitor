#ifndef DLG_SET_COLOR_H
#define DLG_SET_COLOR_H
#include "ui_set_color_dlg.h"
#define DLG_SET_COMBOBOX_NUM 23

class CDlgSetColor:public QDialog,public Ui_Dlg_set_color
{
    Q_OBJECT
public :
    CDlgSetColor(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
     QWidget *pMainform;
    QComboBox *cmb[DLG_SET_COMBOBOX_NUM];
signals:
    void signal_set_panels_color(QFrame * ,int );

};

#endif // DLG_SET_COLOR_H
