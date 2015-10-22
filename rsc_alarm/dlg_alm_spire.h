#ifndef DLG_ALM_SPIRE_H
#define DLG_ALM_SPIRE_H

#include "ui_alm_spire_dlg.h"

class CDlgAlmSpire:public QDialog, public Ui_Dlg_alm_spire
{
    Q_OBJECT
      public:
    CDlgAlmSpire(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_ALM_SPIRE_H
