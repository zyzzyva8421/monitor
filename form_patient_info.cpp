#include <QtGui>
#include"ui_pmng_patient_info.h"
#include "form_patient_info.h"

CFormPatientInfo::CFormPatientInfo(QWidget* parent) :QDialog(parent)
{
    setupUi(this);
    //this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    //
    setTabOrder(spinBox_chuanghao,comboBox_xingbie);
    setTabOrder(comboBox_xingbie,spinBox_shengao);
    setTabOrder(spinBox_shengao,comboBox_leixing);
    setTabOrder(comboBox_leixing,spinBox_tizhong);
    setTabOrder(spinBox_tizhong,comboBox_xuexing);
    setTabOrder(comboBox_xuexing,lineEdit_binglihao);
    setTabOrder(lineEdit_binglihao,lineEdit_bingrenxingming);
    setTabOrder(lineEdit_bingrenxingming,lineEdit_yishengxingming);
    setTabOrder(lineEdit_yishengxingming,spinBox_chusheng_nian);
    setTabOrder(spinBox_chusheng_nian,spinBox_chusheng_yue);
    setTabOrder(spinBox_chusheng_yue,spinBox_chusheng_ri);
    setTabOrder(spinBox_chusheng_ri,spinBox_ruyuan_nian);
    setTabOrder(spinBox_ruyuan_nian,spinBox_ruyuan_yue);
    setTabOrder(spinBox_ruyuan_yue,spinBox_ruyuan_ri);
    setTabOrder(spinBox_ruyuan_ri,m_btn_ok);
    setTabOrder(m_btn_ok,m_btn_cancel);
    setTabOrder(m_btn_cancel,spinBox_chuanghao);
    spinBox_chuanghao->setFocus();
    //
    comboBox_leixing->addItem(tr("成人"));
    comboBox_leixing->addItem(tr("婴儿"));
    comboBox_xingbie->addItem(tr("男"));
    comboBox_xingbie->addItem(tr("女"));
    //
    connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(accept()));
    connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(close()));
}
void CFormPatientInfo::on_ok_clicked()
{
    accept();
}
