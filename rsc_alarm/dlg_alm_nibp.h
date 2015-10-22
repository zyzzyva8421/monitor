#ifndef DLG_ALM_NIBP_H
#define DLG_ALM_NIBP_H

#include "ui_alm_nibp_dlg.h"

class CDlgAlmNIBP:public QDialog, public Ui_Dlg_alm_nibp
{
    Q_OBJECT
      public:
    CDlgAlmNIBP(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_ALM_NIBP_H
