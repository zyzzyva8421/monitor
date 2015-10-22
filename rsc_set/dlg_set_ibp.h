#ifndef DLG_SET_IBP_H
#define DLG_SET_IBP_H

#include "ui_set_ibp_dlg.h"

class CDlgSetIBP:public QDialog, public Ui_Dlg_set_ibp
{
    Q_OBJECT
public:
   CDlgSetIBP(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
   void do_ok_clicked();
   void do_cancel_clicked();
   void do_correct();
   void do_chanel1_changed(int);
   void do_chanel2_changed(int);
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_SET_IBP_H
