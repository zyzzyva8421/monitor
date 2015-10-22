#ifndef DLG_ALM_ECG_H
#define DLG_ALM_ECG_H

#include "ui_alm_ecg_dlg.h"

class CDlgAlmECG:public QDialog, public Ui_Dlg_alm_ecg
{
    Q_OBJECT
      public:
    CDlgAlmECG(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_ALM_ECG_H
