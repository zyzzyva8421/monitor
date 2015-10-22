#ifndef SERV_USR_CONFIG_PARA_H
#define SERV_USR_CONFIG_PARA_H

#include "ui_serv__dlg.h"

class CDlgSetTime:public QDialog, public Ui_Dlg_set_time
{
    Q_OBJECT
      public:
    CDlgSetTime(QWidget *parent);
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();

};

#endif // SERV_USR_CONFIG_PARA_H
