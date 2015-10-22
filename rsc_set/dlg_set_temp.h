#ifndef DLG_SET_TEMP_H
#define DLG_SET_TEMP_H

#include "ui_set_temp_dlg.h"

class CDlgSetTemp:public QDialog, public Ui_Dlg_set_temp
{
    Q_OBJECT
      public:
    CDlgSetTemp(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};


#endif // DLG_SET_TEMP_H
