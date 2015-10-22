#ifndef DLG_SET_ALARM_H
#define DLG_SET_ALARM_H
#include "ui_set_alm_dlg.h"

class CDlgSetAlm:public QDialog, public Ui_Dlg_set_baojingshezhi
{
    Q_OBJECT
      public:
    CDlgSetAlm(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();

};

#endif // DLG_SET_ALARM_H
