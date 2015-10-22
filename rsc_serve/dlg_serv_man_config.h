#ifndef DLG_SERV_MAN_CONFIG_H
#define DLG_SERV_MAN_CONFIG_H

#include "ui_serv_man_config_dlg.h"

class CDlgServManCfg:public QDialog, public Ui_Dlg_serv_man_config
{
    Q_OBJECT
      public:
    CDlgServManCfg(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
    void do_para_sw_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_SERV_MAN_CONFIG_H
