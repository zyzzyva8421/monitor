#ifndef DLG_SET_CO2_H
#define DLG_SET_CO2_H

#include "ui_set_co2_dlg.h"

class CDlgSetCO2:public QDialog, public Ui_Dlg_set_co2
{
    Q_OBJECT
      public:
    CDlgSetCO2(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
    void slot_jiaoling();
};

#endif // DLG_SET_CO2_H
