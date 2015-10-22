#include "menu_patient_mng.h"
#include "form_patient_info.h"
#include "form_patient_drug.h"
#include "mainform.h"
CFormPatinetMng::CFormPatinetMng(QWidget *parent )
    :QMenu(parent)
{
    pMainForm = parent;
    //创建菜单项
    QString item = "病人信息";
    act_patnt_info = new QAction(item,this);
    item = "删除病人信息";
    act_patnt_del = new QAction(item,this);
    item = "药物计算";
    act_drug_sum = new QAction(item,this);
    item = "返回";
    act_back = new QAction(item,this);
    //添加菜单项
   // setObjectName(QString::fromUtf8("main"));
    addAction(act_patnt_info);
    addAction(act_patnt_del);
    addSeparator();
    addAction(act_drug_sum);
    addSeparator();
    addAction(act_back);
    setFixedWidth(200);
    //设置格式
    this->setStyleSheet(tr("background-color: white;selection-background-color: blue;"));

    show();

    connect(act_patnt_info,SIGNAL(triggered()),this,SLOT(do_patnt_info()));
    connect(act_patnt_del,SIGNAL(triggered()),this,SLOT(do_patnt_del()));
    connect(act_drug_sum,SIGNAL(triggered()),this,SLOT(do_drug_sum()));
    connect(act_back,SIGNAL(triggered()),this,SLOT(do_back()));

}
void CFormPatinetMng::do_patnt_info(void)
{
    CFormPatientInfo * form_patnt_info = new CFormPatientInfo(this,pMainForm);
    form_patnt_info->show();
}
void CFormPatinetMng::do_patnt_del()
{
    QMessageBox QuQueSheng;
    QuQueSheng.setStyleSheet(
                "QPushButton:focus"
                "{"
                "border-width:3px;"
                "border-style:solid;"
                "border-color:blue;"
                "border-radius:5px;"
                "background:#ffffff;"
                "}"
                );
    QuQueSheng.setGeometry((1024-260)/2,(768-170)/2,260,170);
    QuQueSheng.setWindowTitle("删除病人信息");
    QuQueSheng.setIcon(QMessageBox::Warning);
    QuQueSheng.setText("所有病人的历史数据\n将会被清除！\n您确定要执行该操作？");
    QuQueSheng.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

     if(QuQueSheng.exec() == QMessageBox::Yes)
    {
        QFile file("/home/data/patientseting.dat");
        file.remove();
        //BingRenGuanLi_BingRenXinXi_Get();
     }
}
void CFormPatinetMng::do_drug_sum()
{
    CFormPatientDrug * form_patnt_drug = new CFormPatientDrug(this,pMainForm);
    form_patnt_drug->show();
}
void CFormPatinetMng::do_back()
{

}

void CFormPatinetMng::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {

    case 68:
    case Qt::Key_F9:
    case Qt::Key_F10:
    case Qt::Key_F11:
    case Qt::Key_F12:
    {
        CMainForm *p = (CMainForm *)pMainForm;
        p->f_process_key(event->key());
    }
        break;
    default:
        QMenu::keyPressEvent(event);
        break;
    }
    //QWidget::keyPressEvent(event);
}

