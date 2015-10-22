#ifndef DLG_SET_NIBP_H
#define DLG_SET_NIBP_H
#include "ui_set_nibp_dlg.h"

class CDlgSetNIBP:public QDialog, public Ui_Dlg_set_nibp
{
    Q_OBJECT
      public:
    CDlgSetNIBP(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
    void do_model_index_changed(int );
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_SET_NIBP_H
