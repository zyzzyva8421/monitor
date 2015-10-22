#ifndef DLG_SET_MASHEN_H
#define DLG_SET_MASHEN_H

#include "ui_set_mashen_dlg.h"

class CDlgSetMashen:public QDialog, public Ui_Dlg_set_mashen
{
    Q_OBJECT
      public:
    CDlgSetMashen(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);

};

#endif // DLG_SET_MASHEN_H
