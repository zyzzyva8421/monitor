#ifndef DLG_ALM_CO2_H
#define DLG_ALM_CO2_H

#include "ui_alm_co2_dlg.h"

class CDlgAlmCO2:public QDialog, public Ui_Dlg_alm_co2
{
    Q_OBJECT
      public:
    CDlgAlmCO2(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_ALM_CO2_H
