#ifndef FORM_PATIENT_INFO_H
#define FORM_PATIENT_INFO_H

#include <QtGui>
#include "ui_pmng_bingrenxinxi.h"

class CFormPatientInfo: public QDialog,public Ui_bingrenxinxi
{
    Q_OBJECT
public:
    CFormPatientInfo(QWidget *parent );

private slots:
    void on_ok_clicked();
};


#endif // FORM_PATIENT_INFO_H
