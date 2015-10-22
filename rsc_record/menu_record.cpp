#include "menu_record.h"

#include "dlg_record_qushitu.h"
#include "dlg_record_qushibiao.h"
#include "dlg_record_alarm.h"
#include "dlg_record_nibp.h"
#include "dlg_record_boxing.h"
#include "rsc_plot/plotter.h"
//#include "rsc_plot/waveplot.h"
//#include "mainform.h"
CMenuRecord::CMenuRecord(QWidget *parent )
    :QMenu(parent)
{
    pMainForm = parent;
    //创建菜单项
    QString item = "趋势图";
    act_qushitu = new QAction(item,this);
    item = "趋势表";
    act_qushibiao= new QAction((item),this);
    item = "报警回顾";
    act_alarm= new QAction(item,this);
    item = "无创血压回顾";
    act_nibp= new QAction(item,this);
    item = "波形回顾";
    act_boxing= new QAction(item,this);
    item = "返回";
    act_return= new QAction(item,this);
     //添加菜单项
    addAction(act_qushitu);
    addAction(act_qushibiao);
    addSeparator();
    addAction(act_alarm);
    addAction(act_nibp);
    addAction(act_boxing);
    addSeparator();
    addAction(act_return);
    setFixedWidth(200);
    //设置格式
    this->setStyleSheet(tr("background-color: white;selection-background-color: blue;"));

    show();

    connect(act_qushitu,SIGNAL(triggered()),this,SLOT(slot_do_qushitu()));
    connect(act_qushibiao,SIGNAL(triggered()),this,SLOT(slot_do_qushibiao()));
    connect(act_alarm,SIGNAL(triggered()),this,SLOT(slot_do_alarm()));
    connect(act_nibp,SIGNAL(triggered()),this,SLOT(slot_do_nibp()));
    connect(act_boxing,SIGNAL(triggered()),this,SLOT(slot_do_boxing()));
    connect(act_return,SIGNAL(triggered()),this,SLOT(slot_do_back()));
}
void CMenuRecord::slot_do_qushitu(void)
{
    CDlgHisQushitu * dlg = new CDlgHisQushitu(this,pMainForm);
    dlg->show();
}
void CMenuRecord::slot_do_qushibiao()
{
    CDlgHisQushibiao *dlg = new CDlgHisQushibiao(this,pMainForm);
    dlg->show();
}
void CMenuRecord::slot_do_alarm()
{
    CDlgRecordAlarm * dlg = new CDlgRecordAlarm(this,pMainForm);
    dlg->show();
}
void CMenuRecord::slot_do_nibp()
{
    CDlgRecordNIBP *dlg = new CDlgRecordNIBP(this,pMainForm);
    dlg->show();
}
void CMenuRecord::slot_do_boxing()
{
   // CDlgRecordWave *dlg = new CDlgRecordWave(this);

    Plotter *plotter = new Plotter(this);

    int numPoints = 100;
    QVector<QPointF> points0;
    QVector<QPointF> points1;
    for (int x = 0; x < numPoints; ++x) {
        points0.append(QPointF(x, uint(qrand()) % 100));
        points1.append(QPointF(x, uint(qrand()) % 100));
    }
    plotter->setCurveData(0, points0);
    plotter->setCurveData(1, points1);

    PlotSettings settings;
    settings.minX = 0.0;
    settings.maxX = 100.0;
    settings.minY = 0.0;
    settings.maxY = 100.0;
    plotter->setPlotSettings(settings);

   plotter->show();
}
void CMenuRecord::slot_do_back()
{

}

void CMenuRecord::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {

    case 68:
    case Qt::Key_F9:
    case Qt::Key_F10:
    case Qt::Key_F11:
    case Qt::Key_F12:
    {
        //CMainForm *p = (CMainForm *)pMainForm;
        //p->f_process_key(event->key());
    }
        break;
    default:
        QMenu::keyPressEvent(event);
        break;
    }
    //QWidget::keyPressEvent(event);
}

