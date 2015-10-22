#ifndef FORM_PATIENT_INFO_H
#define FORM_PATIENT_INFO_H

#include <QtGui>
#include "ui_pmng_bingrenxinxi.h"

class CFormPatientInfo: public QDialog,public Ui_bingrenxinxi
{
    Q_OBJECT
public:
    CFormPatientInfo(QWidget *parent ,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};


#endif // FORM_PATIENT_INFO_H
