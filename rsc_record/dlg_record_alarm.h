#ifndef DLG_RECORD_ALARM_H
#define DLG_RECORD_ALARM_H
#include "ui_his_alarm_dlg.h"

class CDlgRecordAlarm:public QDialog, public Ui_Dlg_record_alarm
{
    Q_OBJECT
 public:
     CDlgRecordAlarm(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
 private slots:
     void slot_back_end();
     void slot_back_fast();
     void slot_back();
     void slot_forwd_end();
     void slot_forwd_fast();
     void slot_forwd();
     void slot_return();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};


#endif // DLG_RECORD_ALARM_H
