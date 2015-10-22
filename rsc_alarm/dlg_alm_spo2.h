#ifndef DLG_ALM_SPO2_H
#define DLG_ALM_SPO2_H
#include "ui_alm_spo2_dlg.h"

class CDlgAlmSPO2:public QDialog, public Ui_Dlg_alm_spo
{
    Q_OBJECT
      public:
    CDlgAlmSPO2(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_ALM_SPO2_H
