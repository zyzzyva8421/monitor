#ifndef DLG_SERV_TIWENTANTOU_H
#define DLG_SERV_TIWENTANTOU_H

#include "ui_serv_tiwentantou_dlg.h"

class CDlgServTiwentantou:public QDialog, public Ui_Dlg_serv_tiwentantou
{
    Q_OBJECT
      public:
    CDlgServTiwentantou(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);

};

#endif // DLG_SERV_TIWENTANTOU_H
