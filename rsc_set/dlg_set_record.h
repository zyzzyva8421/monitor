#ifndef DLG_SET_RECORD_H
#define DLG_SET_RECORD_H
#include "ui_set_jilushezhi_dlg.h"

class CDlgSetRecord:public QDialog,public Ui_Dlg_set_jilushezhi
{
    Q_OBJECT
public :
    CDlgSetRecord(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
    private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_SET_RECORD_H
