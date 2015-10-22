#ifndef DLG_SET_OTHERS_H
#define DLG_SET_OTHERS_H
#include "ui_set_qitashezhi_dlg.h"

class CDlgSetOthers:public QDialog, public Ui_Dlg_set_others
{
    Q_OBJECT
      public:
    CDlgSetOthers(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_SET_OTHERS_H
