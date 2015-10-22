#include "menu_serve.h"

#include "dlg_serv_man_config.h"
#include "dlg_serv_man_para.h"
#include "dlg_serv_tiwentantou.h"
#include "dlg_serv_usr.h"
#include "dlg_serv_xindianjiaozhun.h"
#include "mainform.h"
CMenuServe::CMenuServe(QWidget * parent):QMenu(parent)
 {
    pMainForm = parent;
    QString act_name_str[MENU_SERVE_ACT_COUNT]={" 心电校准",
                              " 体温探头类型",
                              " 血压漏气检测",
                              " 血压校准",
                              " 血压复位",
                              " 演示模式",
                              " 版本信息",
                              " 用户设置",
                              " 用户配置",
                              " 厂家维护",
                              " 返回" };
    for(int i=0;i<MENU_SERVE_ACT_COUNT;i++)
    {
        act_set[i] = new QAction( act_name_str[i],this);
        addAction(act_set[i]);
        if((i == 4)||(i==5)||(i==10)||(i==10))
        {
            addSeparator();
        }
    }

    setFixedWidth(200);
    //设置格式
    this->setStyleSheet(tr("background-color: white;selection-background-color: blue;"));

    show();

    connect( act_set[0],SIGNAL(triggered()),this,SLOT(slot_do_xindianjiaozhun()));
    connect( act_set[1],SIGNAL(triggered()),this,SLOT(slot_do_tiwentantou()));
    connect( act_set[2],SIGNAL(triggered()),this,SLOT(slot_do_louqijiance()));
    connect( act_set[3],SIGNAL(triggered()),this,SLOT(slot_do_xueyajiaozhun()));
    connect( act_set[4],SIGNAL(triggered()),this,SLOT(slot_do_xueyafuwei()));
    connect( act_set[5],SIGNAL(triggered()),this,SLOT( slot_do_yanshimoshi()));
    connect( act_set[6],SIGNAL(triggered()),this,SLOT( slot_do_banbenxinxi()));
    connect( act_set[7],SIGNAL(triggered()),this,SLOT( slot_do_yonghushezhi()));
    connect( act_set[8],SIGNAL(triggered()),this,SLOT( slot_do_yonghupeizhi()));
    connect( act_set[9],SIGNAL(triggered()),this,SLOT( slot_do_changjiaweihu()));
    connect( act_set[10],SIGNAL(triggered()),this,SLOT( slot_do_return()));

}
void CMenuServe::slot_do_xindianjiaozhun()
{
    CDlgServECGCorrect *dlg = new CDlgServECGCorrect(this,pMainForm);
    dlg->show();
}
void CMenuServe::slot_do_tiwentantou()
{
    CDlgServTiwentantou *dlg = new CDlgServTiwentantou(this,pMainForm);
    dlg->show();
}
void CMenuServe::slot_do_louqijiance()
{

}
void CMenuServe::slot_do_xueyajiaozhun()
{

}
void CMenuServe::slot_do_xueyafuwei()
{

}
void CMenuServe::slot_do_yanshimoshi()
{

}
void CMenuServe::slot_do_banbenxinxi()
{
    system ("pkill monitor ");
}
void CMenuServe::slot_do_yonghushezhi()
{
    CDlgServUsrCfg *dlg = new CDlgServUsrCfg(this,pMainForm);
    dlg->show();
}
void CMenuServe::slot_do_yonghupeizhi()
{

}
void CMenuServe::slot_do_changjiaweihu()
{
    CDlgServManCfg *dlg = new CDlgServManCfg(this,pMainForm);
    dlg->show();
}
void CMenuServe::slot_do_return()
{

}

void CMenuServe::keyPressEvent(QKeyEvent *event)
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

