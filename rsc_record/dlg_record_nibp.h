#ifndef DLG_RECORD_NIBP_H
#define DLG_RECORD_NIBP_H
#include "ui_his_nibp_huigu_dlg.h"
#include <QDataWidgetMapper>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QDateTime>
#include <QStandardItemModel>
#include "rsc_modu/modu_database.h"
class CDlgRecordNIBP:public QDialog, public Ui_Dlg_record_nibp
{
    Q_OBJECT
 public:
     CDlgRecordNIBP(QWidget *parent,QWidget *pMain);
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
    QDateTime m_querytime;
    QDateTime m_lasttime;
    QSqlTableModel *tableModel;
    QStandardItemModel *displayModel;
    QDataWidgetMapper *mapper;

    void f_set_table_header();
    void f_set_table_style();
    void f_set_table_rowname(int row);
    bool eventFilter(QObject *o,QEvent *e);
};

#endif // DLG_RECORD_NIBP_H
