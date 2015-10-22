#ifndef DLG_SET_TIME_H
#define DLG_SET_TIME_H
#include "ui_set_time_dlg.h"

class CDlgSetTime:public QDialog, public Ui_Dlg_set_time
{
    Q_OBJECT
      public:
    CDlgSetTime(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_SET_TIME_H
