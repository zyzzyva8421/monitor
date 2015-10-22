
#include "menu_set.h"
#include "dlg_set_color.h"
#include "dlg_set_alarm.h"
#include "dlg_set_co2.h"
#include "dlg_set_ecg.h"
#include "dlg_set_eeg.h"
#include "dlg_set_ibp.h"
#include "dlg_set_mashen.h"
#include "dlg_set_nibp.h"
#include "dlg_set_others.h"
#include "dlg_set_record.h"
#include "dlg_set_screen_layout.h"
#include "dlg_set_spire.h"
#include "dlg_set_spo2.h"
#include "dlg_set_temp.h"
#include "dlg_set_time.h"
#include "mainform.h"
CMenuSet::CMenuSet(QWidget * parent):QMenu(parent)
 {
    pMainForm = parent;
    QString act_name_str[17]={" 颜色设置"," 报警设置"," 记录设置"," 屏幕布局"," 调整时间"," 其他设置"," 心电设置"," 血氧设置",
         " 无创血压设置"," 呼吸设置"," 体温设置"," 有创压设置"," CO₂设置"," 脑电设置"," 麻醉深度设置"," 取默认设置"," 返回"};
    for(int i=0;i<17;i++)
    {
        act_set[i] = new QAction( act_name_str[i],this);
        addAction(act_set[i]);
        if((i == 5)||(i == 14)||(i == 15))
            addSeparator();
    }
    setFixedWidth(200);
    //设置格式
    this->setStyleSheet(tr("background-color: white;selection-background-color: blue;"));

    show();

    connect( act_set[0],SIGNAL(triggered()),this,SLOT(slot_do_set_color()));
    connect( act_set[1],SIGNAL(triggered()),this,SLOT(slot_do_set_alarm()));
    connect( act_set[2],SIGNAL(triggered()),this,SLOT(slot_do_set_record()));
    connect( act_set[3],SIGNAL(triggered()),this,SLOT(slot_do_set_screen_layout()));
    connect( act_set[4],SIGNAL(triggered()),this,SLOT(slot_do_set_time()));
    connect( act_set[5],SIGNAL(triggered()),this,SLOT( slot_do_set_others()));
    connect( act_set[6],SIGNAL(triggered()),this,SLOT( slot_do_set_ecg()));
    connect( act_set[7],SIGNAL(triggered()),this,SLOT( slot_do_set_spo()));
    connect( act_set[8],SIGNAL(triggered()),this,SLOT( slot_do_set_nibp()));
    connect( act_set[9],SIGNAL(triggered()),this,SLOT( slot_do_set_spire()));
    connect( act_set[10],SIGNAL(triggered()),this,SLOT( slot_do_set_temp()));
    connect( act_set[11],SIGNAL(triggered()),this,SLOT( slot_do_set_ibp()));
    connect( act_set[12],SIGNAL(triggered()),this,SLOT( slot_do_set_co2()));
    connect( act_set[13],SIGNAL(triggered()),this,SLOT( slot_do_set_eeg()));
    connect( act_set[14],SIGNAL(triggered()),this,SLOT( slot_do_set_mashen()));
    connect( act_set[15],SIGNAL(triggered()),this,SLOT(slot_do_set_default()));
    connect( act_set[16],SIGNAL(triggered()),this,SLOT(slot_do_set_return()));
}
void CMenuSet::slot_do_set_color()
{
    CDlgSetColor *dlg = new CDlgSetColor(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_alarm()
{
    CDlgSetAlm *dlg = new CDlgSetAlm(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_record()
{
    CDlgSetRecord *dlg = new CDlgSetRecord(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_screen_layout()
{
    CDlgSetScreenLayout *dlg = new CDlgSetScreenLayout(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_time()
{
    CDlgSetTime *dlg = new CDlgSetTime(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_others()
{
    CDlgSetOthers *dlg = new CDlgSetOthers(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_ecg()
{
    CDlgSetECG *dlg = new CDlgSetECG(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_spo()
{
    CDlgSetSpo2 *dlg = new CDlgSetSpo2(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_nibp()
{
    CDlgSetNIBP *dlg = new CDlgSetNIBP(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_spire()
{
    CDlgSetSpire *dlg = new CDlgSetSpire(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_temp()
{
    CDlgSetTemp *dlg = new CDlgSetTemp(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_ibp()
{
    CDlgSetIBP *dlg = new CDlgSetIBP(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_co2()
{
    CDlgSetCO2 *dlg = new CDlgSetCO2(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_eeg()
{
    CDlgSetEEG *dlg = new CDlgSetEEG(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_mashen()
{
    CDlgSetMashen *dlg = new CDlgSetMashen(this,pMainForm);
    dlg->show();
}
void CMenuSet::slot_do_set_default()
{

}
void CMenuSet::slot_do_set_return()
{

}

void CMenuSet::keyPressEvent(QKeyEvent *event)
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
    }
    //QWidget::keyPressEvent(event);
}
