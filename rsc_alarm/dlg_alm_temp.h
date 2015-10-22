#ifndef DLG_ALM_TEMP_H
#define DLG_ALM_TEMP_H

#include "ui_alm_temp_dlg.h"

class CDlgAlmTemp:public QDialog, public Ui_Dlg_alm_temp
{
    Q_OBJECT
      public:
    CDlgAlmTemp(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_ALM_TEMP_H
