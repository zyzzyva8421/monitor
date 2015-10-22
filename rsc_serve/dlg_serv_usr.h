#ifndef DLG_SERV_USR_H
#define DLG_SERV_USR_H

#include "ui_serv_usr_dlg.h"

class CDlgServUsrCfg:public QDialog, public Ui_Dlg_serv_usr_set
{
    Q_OBJECT
public:
    CDlgServUsrCfg(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
    void f_set_display();
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
signals:
    void signal_net_changed(int);


};

#endif // DLG_SERV_USR_H
