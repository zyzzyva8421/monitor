#ifndef DLG_RECORD_BOXING_H
#define DLG_RECORD_BOXING_H
#include <QDockWidget>
#include "ui_his_boxing_dlg.h"
class CDlgRecordWave:public QDialog, public Ui_Dlg_record_boxing
{
    Q_OBJECT
 public:
    QDockWidget*	dockWidget;
     CDlgRecordWave(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
 private slots:
     void do_cancel_clicked();
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

#endif // DLG_RECORD_BOXING_H
