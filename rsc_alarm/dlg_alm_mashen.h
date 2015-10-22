#ifndef DLG_ALM_MASHEN_H
#define DLG_ALM_MASHEN_H

#include "ui_alm_mashen_dlg.h"

class CDlgAlmMashen:public QDialog, public Ui_Dlg_alm_mashen
{
    Q_OBJECT
      public:
    CDlgAlmMashen(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_ALM_MASHEN_H
