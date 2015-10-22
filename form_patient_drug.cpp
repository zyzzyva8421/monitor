#include "form_patient_drug.h"

CFormPatientDrug::CFormPatientDrug(QWidget *parent):QDialog(parent)
{
    setupUi(this);

    connect(m_btn_diding,SIGNAL(clicked()),this,SLOT(do_diding()));
    connect(m_btn_return,SIGNAL(clicked()),this,SLOT(close()));
}
void CFormPatientDrug::do_diding()
{

}
