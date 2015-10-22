#ifndef DLG_SET_EEG_H
#define DLG_SET_EEG_H

#include "ui_set_eeg_dlg.h"

class CDlgSetEEG:public QDialog, public Ui_Dlg_set_eeg
{
    Q_OBJECT
      public:
    CDlgSetEEG(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
    void do_lead_changed(int idx);
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_SET_EEG_H
