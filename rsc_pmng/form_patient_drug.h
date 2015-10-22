#ifndef FORM_PATIENT_DRUG_H
#define FORM_PATIENT_DRUG_H
#include "ui_pmng_patient_drug.h"

class CFormPatientDrug: public QDialog, public Ui_Dialog_patient_drug
{
    Q_OBJECT
    public:
    CFormPatientDrug(QWidget * parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_diding();
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
};


#endif // FORM_PATIENT_DRUG_H
