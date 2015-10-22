#ifndef DLG_SET_SPO2_H
#define DLG_SET_SPO2_H
#include "ui_set_spo2_dlg.h"

class CDlgSetSpo2:public QDialog, public Ui_Dlg_set_spo2
{
    Q_OBJECT
      public:
    CDlgSetSpo2(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_SET_SPO2_H
