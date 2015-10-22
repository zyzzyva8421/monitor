#ifndef DLG_SERV_XINDIANJIAOZHUN_H
#define DLG_SERV_XINDIANJIAOZHUN_H

#include "ui_serv_xindianjiaozhun_dlg.h"

class CDlgServECGCorrect:public QDialog, public Ui_Dlg_serv_xindianjiaozhun
{
    Q_OBJECT
      public:
    CDlgServECGCorrect(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);

};

#endif // DLG_SERV_XINDIANJIAOZHUN_H
