#ifndef DLG_RECORD_QUSHIBIAO_H
#define DLG_RECORD_QUSHIBIAO_H
#include "ui_his_qushibiao_dlg.h"
#include <QStandardItemModel>
#include <QDateTime>
#include "rsc_modu/modu_database.h"
class CDlgHisQushibiao:public QDialog, public Ui_Dlg_his_qushibiao
{
   Q_OBJECT
public:
    CDlgHisQushibiao(QWidget *parent,QWidget *pMain);
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
private:
    int iCursor;
    bool bCursorSta;
    QDateTime m_querytime;
    int m_interval;
    QStandardItemModel *displayModel;
    bool eventFilter(QObject *o,QEvent *e);
    void f_read_para(void);
    void f_set_tableheader();

};

#endif // DLG_RECORD_QUSHIBIAO_H
