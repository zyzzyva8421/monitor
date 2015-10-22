#include "menu_alarm_limit.h"

#include "dlg_alm_co2.h"
#include "dlg_alm_ecg.h"
#include "dlg_alm_ibp.h"
#include "dlg_alm_mashen.h"
#include "dlg_alm_nibp.h"
#include "dlg_alm_spire.h"
#include "dlg_alm_temp.h"
#include "dlg_alm_spo2.h"
#include "mainform.h"
CMenuAlarmLimit::CMenuAlarmLimit(QWidget *parent):QMenu(parent)
{
    pMainForm = parent;
    QString act_name_str[10]={" 心电报警限设置",
                              " 血氧报警限设置",
                              " 血压报警限设置",
                              " 呼吸报警限设置",
                              " 体温报警限设置",
                              " 麻深报警限设置",
                              " 有创压报警限",
                              " CO₂报警限",
                              " 取缺省报警限",
                              " 返回"};
    for(int i=0;i<10;i++)
    {
        act_set[i] = new QAction( act_name_str[i],this);
        addAction(act_set[i]);
    }
    setFixedWidth(200);
    //设置格式
    this->setStyleSheet(tr("background-color: white;selection-background-color: blue;"));

    show();

    connect( act_set[0],SIGNAL(triggered()),this,SLOT(slot_do_alm_ecg()));
    connect( act_set[1],SIGNAL(triggered()),this,SLOT(slot_do_alm_spo()));
    connect( act_set[2],SIGNAL(triggered()),this,SLOT(slot_do_alm_nibp()));
    connect( act_set[3],SIGNAL(triggered()),this,SLOT(slot_do_alm_spire()));
    connect( act_set[4],SIGNAL(triggered()),this,SLOT(slot_do_alm_temp()));
    connect( act_set[5],SIGNAL(triggered()),this,SLOT( slot_do_alm_mashen()));
    connect( act_set[6],SIGNAL(triggered()),this,SLOT( slot_do_alm_ibp()));
    connect( act_set[7],SIGNAL(triggered()),this,SLOT( slot_do_alm_co2()));
    connect( act_set[8],SIGNAL(triggered()),this,SLOT( slot_do_alm_default()));
    connect( act_set[9],SIGNAL(triggered()),this,SLOT( slot_do_alm_return()));

}

void CMenuAlarmLimit::slot_do_alm_ecg()
{
    CDlgAlmECG *dlg = new CDlgAlmECG(this,pMainForm);
    dlg->show();
}
void CMenuAlarmLimit::slot_do_alm_spo()
{
    CDlgAlmSPO2 *dlg = new CDlgAlmSPO2(this,pMainForm);
    dlg->show();
}
void CMenuAlarmLimit::slot_do_alm_nibp()
{
    CDlgAlmNIBP *dlg = new CDlgAlmNIBP(this,pMainForm);
    dlg->show();
}
void CMenuAlarmLimit::slot_do_alm_spire()
{
    CDlgAlmSpire *dlg = new CDlgAlmSpire(this,pMainForm);
    dlg->show();
}
void CMenuAlarmLimit::slot_do_alm_temp()
{
    CDlgAlmTemp *dlg = new CDlgAlmTemp(this,pMainForm);
    dlg->show();
}
void CMenuAlarmLimit::slot_do_alm_mashen()
{
    CDlgAlmMashen *dlg = new CDlgAlmMashen(this,pMainForm);
    dlg->show();
}
void CMenuAlarmLimit::slot_do_alm_ibp()
{
    CDlgAlmIBP *dlg = new CDlgAlmIBP(this,pMainForm);
    dlg->show();
}
void CMenuAlarmLimit::slot_do_alm_co2()
{
    CDlgAlmCO2 *dlg = new CDlgAlmCO2(this,pMainForm);
    dlg->show();
}
void CMenuAlarmLimit::slot_do_alm_default()
{

}
void CMenuAlarmLimit::slot_do_alm_return()
{

}
bool CMenuAlarmLimit::eventFilter(QObject *, QEvent *)
{

}

void CMenuAlarmLimit::keyPressEvent(QKeyEvent *event)
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

