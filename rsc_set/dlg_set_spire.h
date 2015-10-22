#ifndef DLG_SET_SPIRE_H
#define DLG_SET_SPIRE_H

#include "ui_set_spire_dlg.h"

class CDlgSetSpire:public QDialog, public Ui_Dlg_set_spire
{
    Q_OBJECT
      public:
    CDlgSetSpire(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};


#endif // DLG_SET_SPIRE_H
