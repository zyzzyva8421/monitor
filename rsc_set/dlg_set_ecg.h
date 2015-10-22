#ifndef DLG_SET_ECG_H
#define DLG_SET_ECG_H
#include "ui_set_ecg_dlg.h"

class CDlgSetECG:public QDialog, public Ui_Dlg_set_ecg
{
    Q_OBJECT
      public:
    CDlgSetECG(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
    void do_ch1_changed(int);
    void do_ch2_changed(int);
    void do_ch3_changed(int);
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);

};

#endif // DLG_SET_ECG_H
