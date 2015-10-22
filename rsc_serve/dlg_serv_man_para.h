#ifndef DLG_SERV_MAN_PARA_H
#define DLG_SERV_MAN_PARA_H

#include "ui_serv_man_config_para_dlg.h"

class CDlgServManCfgPara:public QDialog, public Ui_Dlg_serv_man_config_para
{
    Q_OBJECT
      public:
    CDlgServManCfgPara(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);

};

#endif // DLG_SERV_MAN_PARA_H
