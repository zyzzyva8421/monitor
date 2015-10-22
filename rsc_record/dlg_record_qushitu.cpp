#include "dlg_record_qushitu.h"
#include <QKeyEvent>
#include "mainform.h"
#include "rsc_plot/plotter.h"
#define MAX_DLG_HISQUSHITU_COMB 2
#define MAX_DLG_HISQUSHITU_BTN 7
CDlgHisQushitu::CDlgHisQushitu(QWidget *parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    m_querytime = QDateTime::currentDateTime();
    int sec = m_querytime.time().second();
    m_querytime = m_querytime.addSecs(-sec);
    QComboBox *cmb[MAX_DLG_HISQUSHITU_COMB] ={
        m_cmbb_para,
        m_cmbb_interval
    };
    QPushButton *btn[MAX_DLG_HISQUSHITU_BTN] = {
        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    QStringList list;
    list<<"心率"<<"ST"<<"呼吸率"<<"血氧"<<"脉率"<<"体温";
    m_cmbb_para->addItems(list);
    list.clear();
    list<<"1秒钟"<<"5秒钟"<<"1分钟"<<"5分钟"<<"10分钟";
    m_cmbb_interval->addItems(list);
    //设置光标顺序
    setTabOrder(m_cmbb_para,m_cmbb_interval);
    setTabOrder(m_cmbb_interval,m_btn_back_end);
    setTabOrder(m_btn_back_end,m_btn_back_fast);
    setTabOrder(m_btn_back_fast,m_btn_back);
    setTabOrder(m_btn_back,m_btn_forwd);
    setTabOrder(m_btn_forwd,m_btn_forwd_fast);
    setTabOrder(m_btn_forwd_fast,m_btn_forwd_end);
    setTabOrder(m_btn_forwd_end,m_btn_return);
    setTabOrder(m_btn_return,m_cmbb_para);
    for(int i =0;i<MAX_DLG_HISQUSHITU_COMB;i++)
    {
        cmb[i]->installEventFilter(this);
    }
    for(int i=0;i<MAX_DLG_HISQUSHITU_BTN;i++)
    {
        btn[i]->installEventFilter(this);
    }
    m_cmbb_para->setFocus();
    connect(m_cmbb_interval,SIGNAL(currentIndexChanged(int)),this,SLOT(do_interval_change(int)));
    connect(m_cmbb_para,SIGNAL(currentIndexChanged(int)),this,SLOT(do_para_change(int)));
    //plot
    m_plot = new Plotter(this);
    PlotSettings settings;
    settings.minX = 0.0;
    settings.maxX = 360.0;
    settings.minY = 0.0;
    settings.maxY = 100.0;
    QRect rect=QRect(0,30,width(),300);
    m_plot->setGeometry(rect);
    m_plot->setPlotSettings(settings);
    m_plot->show();

    //
    f_set_interval();
    f_read_para(m_cmbb_para->currentIndex());
}
void CDlgHisQushitu::do_interval_change(int )
{
    f_set_interval();
    int paratype = m_cmbb_para->currentIndex();
    f_read_para( paratype);
}
void CDlgHisQushitu::f_set_interval()
{
    int interval = m_cmbb_interval->currentIndex();
    switch (interval) {
    case 0:
        m_interval = 1;
        break;
    case 1:
        m_interval = 5;
        break;
    case 2:
        m_interval = 60;
        break;
    case 3:
        m_interval = 300;
        break;
    case 4:
        m_interval = 600;
        break;
    default:
        break;
    }
}

void CDlgHisQushitu::do_para_change(int paratype)
{

    f_read_para(paratype);
}

void CDlgHisQushitu::f_read_para(int paratype)
{

    m_plot->clearCurve(0);
    m_plot->clearCurve(1);
    switch (paratype) {
    case 0:
        f_read_beatrate();
        break;
    case 1:
        f_read_st();
        break;
    case 2:
        f_read_breathrate();
        break;
    case 3:
        f_read_spo2();
        break;
    case 4:
        f_read_pulserate();
        break;
    case 5:
        f_read_temp();
        break;

    default:
        break;
    }
}
void CDlgHisQushitu::f_read_beatrate()
{

    QDateTime pre = m_querytime;
    QDateTime after = m_querytime;
    int interval = m_interval*360; //interval

    QString stime = m_querytime.time().toString("hh:mm");
    QString sdate = m_querytime.date().toString("yyyy-MM-dd");
    int sec = m_querytime.time().second();
    pre = m_querytime.addSecs(-sec);
    after = pre.addSecs(-interval);
    QString pretime = pre.toString(Qt::TextDate);
    QString aftertime = after.toString(Qt::TextDate);
    QString filter = "select * from para_beatrate where para_datetime >= '"+aftertime+
            "' and para_datetime < '"+pretime+"' order by para_datetime asc";
    QSqlQuery q(filter);
    QVector<QPointF> points0;
    double x = 0;
    PlotSettings settings;
    settings.minX = 0.0;
    settings.maxX = 360.0;
    settings.minY = 0.0;
    settings.maxY = 180.0;
    m_plot->setPlotSettings(settings);
    while(q.next())
    {

        int  v = q.value(BEATRATE_TABLE_VAL).toInt();
        QString nowtime = q.value(BEATRATE_TABLE_DATETIME).toString();
        QDateTime now = QDateTime::fromString(nowtime,Qt::TextDate);
        int inter = after.secsTo(now);
        x = inter ;
        x  /= interval ;
        x *= 360;
        points0.append(QPointF(x, v));

        bool b = q.value(BEATRATE_TABLE_ALM).toBool();
        QColor color("yellow");
        QBrush brs(color);
        if(b)
        {

        }

    }

    m_plot->setXLabel(after,interval);
    m_plot->setCurveData(0,points0);
    label_para->setText("心率");
    label_date->setText(sdate);
}

void CDlgHisQushitu::f_read_st()
{
    QDateTime pre = m_querytime;
    QDateTime after = m_querytime;
    int interval = m_interval*360; //interval

    QString stime = m_querytime.time().toString("hh:mm");
    QString sdate = m_querytime.date().toString("yyyy-MM-dd");
    int sec = m_querytime.time().second();
    pre = m_querytime.addSecs(-sec);
    after = pre.addSecs(-interval);
    QString pretime = pre.toString(Qt::TextDate);
    QString aftertime = after.toString(Qt::TextDate);
    QString filter = "select * from para_beatrate where para_datetime >= '"+aftertime+
            "' and para_datetime < '"+pretime+"' order by para_datetime asc";
    QSqlQuery q(filter);
    m_plot->clearCurve(0);
    QVector<QPointF> points0;
    double x = 0;
    PlotSettings settings;
    settings.minX = 0.0;
    settings.maxX = 360.0;
    settings.minY = 0.0;
    settings.maxY = 180.0;
    m_plot->setPlotSettings(settings);
    while(q.next())
    {

        int  v = q.value(BEATRATE_TABLE_VAL).toInt();
        QString nowtime = q.value(BEATRATE_TABLE_DATETIME).toString();
        QDateTime now = QDateTime::fromString(nowtime,Qt::TextDate);
        int inter = after.secsTo(now);
        x = inter ;
        x  /= interval ;
        x *= 360;
        points0.append(QPointF(x, v));

        bool b = q.value(BEATRATE_TABLE_ALM).toBool();
        QColor color("yellow");
        QBrush brs(color);
        if(b)
        {

        }

    }

    m_plot->setXLabel(after,interval);
    m_plot->setCurveData(0,points0);
    label_para->setText("ST");
    label_date->setText(sdate);
}

void CDlgHisQushitu::f_read_breathrate()
{
    QDateTime pre = m_querytime;
    QDateTime after = m_querytime;
    int interval = m_interval*360; //interval

    QString stime = m_querytime.time().toString("hh:mm");
    QString sdate = m_querytime.date().toString("yyyy-MM-dd");
    int sec = m_querytime.time().second();
    pre = m_querytime.addSecs(-sec);
    after = pre.addSecs(-interval);
    QString pretime = pre.toString(Qt::TextDate);
    QString aftertime = after.toString(Qt::TextDate);
    QString filter = "select * from para_beatrate where para_datetime >= '"+aftertime+
            "' and para_datetime < '"+pretime+"' order by para_datetime asc";
    QSqlQuery q(filter);
    m_plot->clearCurve(0);
    QVector<QPointF> points0;
    double x = 0;
    PlotSettings settings;
    settings.minX = 0.0;
    settings.maxX = 360.0;
    settings.minY = 0.0;
    settings.maxY = 200.0;
    m_plot->setPlotSettings(settings);
    while(q.next())
    {

        int  v = q.value(SPIRE_TABLE_VAL).toInt();
        QString nowtime = q.value(SPIRE_TABLE_DATETIME).toString();
        QDateTime now = QDateTime::fromString(nowtime,Qt::TextDate);
        int inter = after.secsTo(now);
        x = inter ;
        x  /= interval ;
        x *= 360;
        points0.append(QPointF(x, v));

        bool b = q.value(SPIRE_TABLE_ALM).toBool();
        QColor color("yellow");
        QBrush brs(color);
        if(b)
        {

        }

    }

    m_plot->setXLabel(after,interval);
    m_plot->setCurveData(0,points0);
    label_para->setText("呼吸率");
    label_date->setText(sdate);
}

void CDlgHisQushitu::f_read_spo2()
{

    QDateTime pre = m_querytime;
    QDateTime after = m_querytime;
    int interval = m_interval*360; //interval

    QString stime = m_querytime.time().toString("hh:mm");
    QString sdate = m_querytime.date().toString("yyyy-MM-dd");
    int sec = m_querytime.time().second();
    pre = m_querytime.addSecs(-sec);
    after = pre.addSecs(-interval);
    QString pretime = pre.toString(Qt::TextDate);
    QString aftertime = after.toString(Qt::TextDate);
    QString filter = "select * from para_spo2 where para_datetime >= '"+aftertime+
            "' and para_datetime < '"+pretime+"' order by para_datetime asc";
    QSqlQuery q(filter);
    m_plot->clearCurve(0);
    QVector<QPointF> points0;
    double x = 0;
    PlotSettings settings;
    settings.minX = 0.0;
    settings.maxX = 360.0;
    settings.minY = 0.0;
    settings.maxY = 100.0;
    m_plot->setPlotSettings(settings);
    while(q.next())
    {

        int  v = q.value(SPO2_TABLE_SPO).toInt();
        if(v == -100)
        {
            continue;
        }
        QString nowtime = q.value(SPO2_TABLE_DATETIME).toString();
        QDateTime now = QDateTime::fromString(nowtime,Qt::TextDate);
        int inter = after.secsTo(now);
        x = inter ;
        x  /= interval ;
        x *= 360;
        points0.append(QPointF(x, v));

        bool b = q.value(SPO2_TABLE_ALM1).toBool();
        QColor color("yellow");
        QBrush brs(color);
        if(b)
        {

        }

    }

    m_plot->setXLabel(after,interval);
    m_plot->setCurveData(0,points0);
    label_para->setText("血氧");
    label_date->setText(sdate);
}

void CDlgHisQushitu::f_read_pulserate()
{

    QDateTime pre = m_querytime;
    QDateTime after = m_querytime;
    int interval = m_interval*360; //interval

    QString stime = m_querytime.time().toString("hh:mm");
    QString sdate = m_querytime.date().toString("yyyy-MM-dd");
    int sec = m_querytime.time().second();
    pre = m_querytime.addSecs(-sec);
    after = pre.addSecs(-interval);
    QString pretime = pre.toString(Qt::TextDate);
    QString aftertime = after.toString(Qt::TextDate);
    QString filter = "select * from para_spo2 where para_datetime >= '"+aftertime+
            "' and para_datetime < '"+pretime+"' order by para_datetime asc";
    QSqlQuery q(filter);
    m_plot->clearCurve(0);
    QVector<QPointF> points0;
    double x = 0;
    PlotSettings settings;
    settings.minX = 0.0;
    settings.maxX = 360.0;
    settings.minY = 0.0;
    settings.maxY = 200.0;
    m_plot->setPlotSettings(settings);
    while(q.next())
    {

        int  v = q.value(SPO2_TABLE_PR).toInt();
        if(v == -100)
        {
            continue;
        }
        QString nowtime = q.value(SPO2_TABLE_DATETIME).toString();
        QDateTime now = QDateTime::fromString(nowtime,Qt::TextDate);
        int inter = after.secsTo(now);
        x = inter ;
        x  /= interval ;
        x *= 360;
        points0.append(QPointF(x, v));

        bool b = q.value(SPO2_TABLE_ALM2).toBool();
        QColor color("yellow");
        QBrush brs(color);
        if(b)
        {

        }

    }

    m_plot->setXLabel(after,interval);
    m_plot->setCurveData(0,points0);
    label_para->setText("脉率");
    label_date->setText(sdate);
}

void CDlgHisQushitu::f_read_temp()
{

    QDateTime pre = m_querytime;
    QDateTime after = m_querytime;
    int interval = m_interval*360; //interval

    QString stime = m_querytime.time().toString("hh:mm");
    QString sdate = m_querytime.date().toString("yyyy-MM-dd");
    int sec = m_querytime.time().second();
    pre = m_querytime.addSecs(-sec);
    after = pre.addSecs(-interval);
    QString pretime = pre.toString(Qt::TextDate);
    QString aftertime = after.toString(Qt::TextDate);
    QString filter = "select * from para_temperature where para_datetime >= '"+aftertime+
            "' and para_datetime < '"+pretime+"' order by para_datetime asc";
    QSqlQuery q(filter);
    m_plot->clearCurve(0);
    QVector<QPointF> points0;
    QVector<QPointF> points1;
    double x = 0;
    PlotSettings settings;
    settings.minX = 0.0;
    settings.maxX = 360.0;
    settings.minY = 30.0;
    settings.maxY = 43.0;
    m_plot->setPlotSettings(settings);
    while(q.next())
    {

        int  v1 = q.value(TEMP_TABLE_VAL1).toInt();
        int  v2 = q.value(TEMP_TABLE_VAL2).toInt();

        QString nowtime = q.value(TEMP_TABLE_DATETIME).toString();
        QDateTime now = QDateTime::fromString(nowtime,Qt::TextDate);
        int inter = after.secsTo(now);
        x = inter ;
        x  /= interval ;
        x *= 360;
        if(v1 != -100)
        {
            double tmp = v1;
            tmp /= 10;
            points0.append(QPointF(x, tmp));

        }
        if(v2 != -100)
        {
            double tmp = v2;
            tmp /= 10;
            points1.append(QPointF(x, tmp));
            //label_name->setText(QString::number(v2,10));
        }


        bool b = q.value(TEMP_TABLE_ALM1).toBool();
        QColor color("yellow");
        QBrush brs(color);
        if(b)
        {

        }

    }

    m_plot->setXLabel(after,interval);
    m_plot->setCurveData(0,points0);
    m_plot->setCurveData(1,points1);
    label_para->setText("体温");
    label_date->setText(sdate);
}


bool CDlgHisQushitu::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_para,
        m_cmbb_interval,
        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    int iTotalObj =  9;//11
    //int iOkPos = iTotalObj -2;
    //int iCancelPos = iTotalObj -1;
    if(e->type() == QEvent::KeyPress)
    {

        QKeyEvent *event=(QKeyEvent *)e;
        switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_Left:
            if(bCursorSta == false)
            {
                if(iCursor == 0)
                {
                    iCursor = iTotalObj-1;
                }
                else
                {
                    iCursor -=1;
                }
                if((iCursor>=0) &&(iCursor<2))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setFocus();
                }
                else
                {
                    QPushButton *p = (QPushButton *)obj[iCursor];
                    p->setFocus();
                }

            }
            else
            {
            }

            return true;
            break;
        case Qt::Key_Down:
        case Qt::Key_Right:
            if(bCursorSta == false)
            {
                if(iCursor == iTotalObj-1)
                {
                    iCursor = 0;
                }
                else
                {
                    iCursor +=1;
                }
                if((iCursor>=0) &&(iCursor<2))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setFocus();
                }
                else
                {
                    QPushButton *p = (QPushButton *)obj[iCursor];
                    p->setFocus();
                }

            }
            else
            {

            }
            return true;
            break;
        case Qt::Key_Return:
            if(bCursorSta == false)
            {
                if((iCursor>=0) &&(iCursor<2))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }
                else
                {
                    switch(iCursor)
                    {
                    case 2:
                        slot_back_end();
                        break;
                    case 3:
                        slot_back_fast();
                        break;

                    case 4:
                        slot_back();
                        break;
                    case 5:
                        slot_forwd();
                        break;
                    case 6:
                        slot_forwd_fast();
                        break;
                    case 7:
                        slot_forwd_end();
                        break;
                    case 8:
                        slot_return();
                        break;
                    default:
                        break;
                    }
                }


            }
            else
            {
            }
            return true;
            break;
        default:
            CMainForm *p = (CMainForm *)pMainForm;
            p->f_process_key(event->key());
            return true;
            break;

        }
    }
    else
    {
        return false;
    }
}
void CDlgHisQushitu::slot_back_end()
{
    int interval = -30;
    QDateTime now = QDateTime::currentDateTime();
    m_querytime = now.addDays(interval).addSecs(m_interval*360);
    f_read_para(m_cmbb_para->currentIndex());
   // label_name->setText(m_querytime.time().toString("hh-mm:ss"));
}
void CDlgHisQushitu::slot_back_fast()
{
    int interval = -m_interval*360;
    QDateTime now = QDateTime::currentDateTime().addDays(-30).addSecs(m_interval*360);
    m_querytime = m_querytime.addSecs(interval);
    if(m_querytime< now)
    {
        m_querytime = now;
    }
    f_read_para(m_cmbb_para->currentIndex());
   // label_name->setText(m_querytime.time().toString("hh-mm:ss"));
}
void CDlgHisQushitu::slot_back()
{
    int interval = -m_interval*60;
    QDateTime now = QDateTime::currentDateTime().addDays(-30).addSecs(360*m_interval);
    m_querytime = m_querytime.addSecs(interval);
    if(m_querytime < now)
    {
        m_querytime = now;
    }
    f_read_para(m_cmbb_para->currentIndex());
    //label_name->setText(m_querytime.time().toString("hh-mm:ss"));
}
void CDlgHisQushitu::slot_forwd_end()
{

    m_querytime = QDateTime::currentDateTime();
    f_read_para(m_cmbb_para->currentIndex());
}
void CDlgHisQushitu::slot_forwd_fast()
{
    int interval = m_interval*360;
    QDateTime now = QDateTime::currentDateTime();

    m_querytime = m_querytime.addSecs(interval);
    if(m_querytime > now)
    {
        m_querytime = now;
    }
    f_read_para(m_cmbb_para->currentIndex());
    //label_name->setText(m_querytime.time().toString("hh-mm:ss"));
}
void CDlgHisQushitu::slot_forwd()
{

    int interval = m_interval*60;
    QDateTime now = QDateTime::currentDateTime();

    m_querytime = m_querytime.addSecs(interval);
    if(m_querytime > now)
    {
        m_querytime = now;
    }
    f_read_para(m_cmbb_para->currentIndex());
    //label_name->setText(m_querytime.time().toString("hh-mm:ss"));
}
void CDlgHisQushitu::slot_return()
{
    close();
}
