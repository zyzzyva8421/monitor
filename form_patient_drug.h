#ifndef FORM_PATIENT_DRUG_H
#define FORM_PATIENT_DRUG_H
#include "ui_pmng_patient_drug.h"

class CFormPatientDrug: public QDialog, public Ui_Dialog_patient_drug
{
    Q_OBJECT
    public:
    CFormPatientDrug(QWidget * parent);
private slots:
    void do_diding();
};


#endif // FORM_PATIENT_DRUG_H
