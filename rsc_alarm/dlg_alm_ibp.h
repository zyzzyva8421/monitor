#ifndef DLG_ALM_IBP_H
#define DLG_ALM_IBP_H

#include "ui_alm_ibp_dlg.h"

class CDlgAlmIBP:public QDialog, public Ui_Dlg_alm_ibp
{
    Q_OBJECT
      public:
    CDlgAlmIBP(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_ALM_IBP_H
