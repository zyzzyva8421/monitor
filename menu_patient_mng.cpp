#include "menu_patient_mng.h"
#include "form_patient_info.h"
#include "form_patient_drug.h"

CFormPatinetMng::CFormPatinetMng(QWidget *parent )
    :QMenu(parent)
{


    act_patnt_info = new QAction(tr("1"),this);

    act_patnt_del = new QAction(tr("2"),this);

    act_drug_sum = new QAction(("3"),this);
    act_drug_sum->setText(tr("药物计算"));
    act_back = new QAction(tr("4"),this);

    setObjectName(QString::fromUtf8("main"));
    addAction(act_patnt_info);
    addAction(act_patnt_del);
    addSeparator();
    addAction(act_drug_sum);
    addSeparator();
    addAction(act_back);
    setFixedWidth(200);
    setStyleSheet(tr("background-color:white;"));
/*
    pal_backgrund.setColor(QPalette::Foreground, Qt::white );
    pal_backgrund.setColor(QPalette::Background,Qt::white);

    pal_foregrund.setColor( QPalette::Foreground, Qt::white );
    pal_foregrund.setColor( QPalette::Background, Qt::blue );
    this->setAutoFillBackground(true);
    this->setPalette(pal_backgrund);
*/
    show();

    connect(act_patnt_info,SIGNAL(triggered()),this,SLOT(do_patnt_info()));
    connect(act_patnt_del,SIGNAL(triggered()),this,SLOT(do_patnt_del()));
    connect(act_drug_sum,SIGNAL(triggered()),this,SLOT(do_drug_sum()));
    connect(act_back,SIGNAL(triggered()),this,SLOT(do_back()));

}
void CFormPatinetMng::do_patnt_info(void)
{
    CFormPatientInfo * form_patnt_info = new CFormPatientInfo(this);
    form_patnt_info->show();
}
void CFormPatinetMng::do_patnt_del()
{

}
void CFormPatinetMng::do_drug_sum()
{
    CFormPatientDrug * form_patnt_drug = new CFormPatientDrug(this);
    form_patnt_drug->show();
}
void CFormPatinetMng::do_back()
{

}
