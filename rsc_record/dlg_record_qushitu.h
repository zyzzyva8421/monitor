#ifndef DLG_RECORD_QUSHITU_H
#define DLG_RECORD_QUSHITU_H
#include "ui_his_qushitu_dlg.h"
#include <QDateTime>
#include "rsc_plot/plotter.h"
class CDlgHisQushitu:public QDialog, public Ui_Dlg_his_qushitu
{
   Q_OBJECT
public:
    CDlgHisQushitu(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void slot_back_end();
    void slot_back_fast();
    void slot_back();
    void slot_forwd_end();
    void slot_forwd_fast();
    void slot_forwd();
    void slot_return();
    void do_interval_change(int);
    void do_para_change(int);
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
    void f_read_para(int paratype);
    QDateTime m_querytime;
    int m_interval;
    Plotter *m_plot;
    void f_read_beatrate();
    void f_read_st();
    void f_read_breathrate();
    void f_read_spo2();
    void f_read_pulserate();
    void f_read_temp();
    void f_set_interval();
};

#endif // DLG_RECORD_QUSHITU_H
