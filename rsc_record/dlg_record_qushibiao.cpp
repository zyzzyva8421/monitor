#include "dlg_record_qushibiao.h"
#include <QKeyEvent>
#include "mainform.h"
#define MAX_DLG_HISQUSHIBIAO_COMB 1
#define MAX_DLG_HISQUSHIBIAO_BTN 7
enum{
    TREND_TABLE_BEATRATE = 0,
    TREND_TABLE_SPIRERATE = 1,
    TREND_TABLE_SPO2 = 2,
    TREND_TABLE_PULSERATE = 3,
    TREND_TABLE_TEMP1 = 4,
    TREND_TABLE_TEMP2 = 5,
    TREND_TABLE_NIBPSS = 6,
    TREND_TABLE_NIBPSZ = 7,
    TREND_TABLE_NIBPPJ = 8,
    TREND_TABLE_QIDAOSR = 9,
    TREND_TABLE_ETCO2 = 10,
    TREND_TABLE_FICO2 = 11,

};
#define TREND_CONTROL_BACK 0
#define TREND_CONTROL_BACK_FAST 1
#define TREND_CONTROL_BACK_END 2
#define TREND_CONTROL_FORWARD 3
#define TREND_CONTROL_FORWARD_FAST 4
#define TREND_CONTROL_FORWARD_END 5
/*#define  TREND_TABLE_BEATRATE  0
#define  TREND_TABLE_SPIRERATE  1
#define  TREND_TABLE_SPO2  2
#define  TREND_TABLE_PULSERATE  3
#define  TREND_TABLE_TEMP1  4
#define  TREND_TABLE_TEMP2  5
#define  TREND_TABLE_NIBPSS  6
#define  TREND_TABLE_NIBPSZ 7
#define  TREND_TABLE_NIBPPJ  8
#define  TREND_TABLE_QIDAOSR  9
#define  TREND_TABLE_ETCO2  10
#define  TREND_TABLE_FICO2  11*/
CDlgHisQushibiao::CDlgHisQushibiao(QWidget *parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    m_interval = 1;
    QComboBox *cmb[MAX_DLG_HISQUSHIBIAO_COMB] ={
        m_cmbb_interval
    };
    QPushButton *btn[MAX_DLG_HISQUSHIBIAO_BTN] = {
        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    QStringList items;

    items<<"1分钟"<<"2分钟"<<"3分钟"<<"4分钟"<<"5分钟"<<"10分钟"<<"15分钟"<<"30分钟"<<"60分钟";
    cmb[0]->addItems(items);
    //设置光标顺序
    setTabOrder(m_cmbb_interval,m_btn_back_end);
    setTabOrder(m_btn_back_end,m_btn_back_fast);
    setTabOrder(m_btn_back_fast,m_btn_back);
    setTabOrder(m_btn_back,m_btn_forwd);
    setTabOrder(m_btn_forwd,m_btn_forwd_fast);
    setTabOrder(m_btn_forwd_fast,m_btn_forwd_end);
    setTabOrder(m_btn_forwd_end,m_btn_return);
    setTabOrder(m_btn_return,m_cmbb_interval);
    m_cmbb_interval->setFocus();
    for(int i = 0;i<MAX_DLG_HISQUSHIBIAO_COMB;i++)
    {
        cmb[i]->installEventFilter(this);
    }
    for(int i=0;i<MAX_DLG_HISQUSHIBIAO_BTN;i++)
    {
        btn[i]->installEventFilter(this);
    }
    displayModel = new QStandardItemModel(this);
    displayModel->setItem(TREND_TABLE_BEATRATE,0,new QStandardItem("心率"));//
    displayModel->setItem(TREND_TABLE_SPIRERATE,0,new QStandardItem("呼吸率"));
    displayModel->setItem(TREND_TABLE_SPO2,0,new QStandardItem("血氧"));
    displayModel->setItem(TREND_TABLE_PULSERATE,0,new QStandardItem("脉率"));
    displayModel->setItem(TREND_TABLE_TEMP1,0,new QStandardItem("体温1"));
    displayModel->setItem(TREND_TABLE_TEMP2,0,new QStandardItem("体温2"));
    displayModel->setItem(TREND_TABLE_NIBPSS,0,new QStandardItem("收缩压"));
    displayModel->setItem(TREND_TABLE_NIBPSZ,0,new QStandardItem("舒张压"));
    displayModel->setItem(TREND_TABLE_NIBPPJ,0,new QStandardItem("平均压"));
    displayModel->setItem(TREND_TABLE_QIDAOSR,0,new QStandardItem("气道呼吸率"));
    displayModel->setItem(TREND_TABLE_ETCO2,0,new QStandardItem("EtCO2"));
    displayModel->setItem(TREND_TABLE_FICO2,0,new QStandardItem("FiCO2"));

    m_querytime = QDateTime::currentDateTime();//.addSecs(-540); //-10min
    int isec = m_querytime.time().second();
    m_querytime = m_querytime.addSecs(-isec);
    isec = m_querytime.time().second();
    QString stopdatetime = m_querytime.toString(Qt::TextDate);

    QString filter = "para_datetime <= '"+stopdatetime +"'";
    QSqlQuery q("select * from para_nibp where "+filter +" order by para_datetime desc limit 1 ;");

    QString stime = m_querytime.time().toString("hh:mm");
    QString sdate = m_querytime.date().toString("yyyy-MM-dd");
    displayModel->setHorizontalHeaderItem(0,new QStandardItem(sdate));
    displayModel->setHorizontalHeaderItem(1,new QStandardItem(stime));
    QDate cdate;
    QTime ctime;
/*
    int i = 1;
    QDateTime tmpdatetime[10];
    while (q.next())
    {

        QString vdate = q.value(NIBP_TABLE_VIEW_Date).toString();
        QString vtime = q.value(NIBP_TABLE_VIEW_Time).toString();
        QString vss = q.value(NIBP_TABLE_VIEW_SS).toString();
        QString vsz = q.value(NIBP_TABLE_VIEW_SZ).toString();
        QString vpj = q.value(NIBP_TABLE_VIEW_PJ).toString();

        displayModel->setItem( TREND_TABLE_NIBPSS, i, new QStandardItem(vss));
        displayModel->setItem(TREND_TABLE_NIBPSZ, i, new QStandardItem(vsz));
        displayModel->setItem(TREND_TABLE_NIBPPJ, i, new QStandardItem(vpj));
        bool bss = q.value(NIBP_TABLE_ALM1).toBool();
        bool bsz = q.value(NIBP_TABLE_ALM2).toBool();
        bool bpj = q.value(NIBP_TABLE_ALM3).toBool();
        QColor color("yellow");
        QBrush brs(color);

        if(bss)
        {
            displayModel->item(TREND_TABLE_NIBPSS, i)->setBackground(brs);
        }
        if(bsz)
        {
            displayModel->item(TREND_TABLE_NIBPSZ,i)->setBackground(brs);
        }
        if(bpj)
        {
            displayModel->item(TREND_TABLE_NIBPPJ, i)->setBackground(brs);
        }
        cdate = QDate::fromString(vdate,("yyyy-MM-dd"));
        ctime = QTime::fromString(vtime,("hh:mm:ss"));
        tmpdatetime[i].setDate(cdate);
        tmpdatetime[i].setTime(ctime);
        i++;
    }*/
    ///////////
    f_read_para();
    ///////////
    //display
    tv_para->setModel(displayModel );//tableModel
    tv_para->setSelectionMode(QAbstractItemView::SingleSelection);
    tv_para->setSelectionBehavior(QAbstractItemView::SelectRows);
    //tv_nibp->setColumnHidden(NIBP_TABLE_VIEW_Id,true); //id
    //tv_nibp->setColumnHidden(NIBP_TABLE_VIEW_PARAID,true); //para_id
    tv_para->setColumnHidden(NIBP_TABLE_DATETIME,true);
    tv_para->verticalHeader()->hide();
    //tv_nibp->resizeColumnsToContents();
    tv_para->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tv_para->setFocusPolicy(Qt::NoFocus);

    connect(m_cmbb_interval,SIGNAL(currentIndexChanged(int)),this,SLOT(do_interval_change(int)));


}
void CDlgHisQushibiao::do_interval_change(int idx)
{
    switch (idx) {
    case 0:
        m_interval = 1;
        break;
    case 1:
        m_interval = 2;
        break;
    case 2:
        m_interval = 3;
        break;
    case 3:
        m_interval = 4;
        break;
    case 4:
        m_interval = 5;
        break;
    case 5:
        m_interval = 10;
        break;
    case 6:
        m_interval = 15;
        break;
    case 7:
        m_interval = 30;
        break;
    case 8:
        m_interval = 60;
        break;
    default:
        break;
    }
    f_read_para();
}
void CDlgHisQushibiao::f_set_tableheader()
{

    displayModel->setItem(TREND_TABLE_BEATRATE,0,new QStandardItem("心率"));//
    displayModel->setItem(TREND_TABLE_SPIRERATE,0,new QStandardItem("呼吸率"));
    displayModel->setItem(TREND_TABLE_SPO2,0,new QStandardItem("血氧"));
    displayModel->setItem(TREND_TABLE_PULSERATE,0,new QStandardItem("脉率"));
    displayModel->setItem(TREND_TABLE_TEMP1,0,new QStandardItem("体温1"));
    displayModel->setItem(TREND_TABLE_TEMP2,0,new QStandardItem("体温2"));
    displayModel->setItem(TREND_TABLE_NIBPSS,0,new QStandardItem("收缩压"));
    displayModel->setItem(TREND_TABLE_NIBPSZ,0,new QStandardItem("舒张压"));
    displayModel->setItem(TREND_TABLE_NIBPPJ,0,new QStandardItem("平均压"));
    displayModel->setItem(TREND_TABLE_QIDAOSR,0,new QStandardItem("气道呼吸率"));
    displayModel->setItem(TREND_TABLE_ETCO2,0,new QStandardItem("EtCO2"));
    displayModel->setItem(TREND_TABLE_FICO2,0,new QStandardItem("FiCO2"));
}

void CDlgHisQushibiao::f_read_para(void)
{
    QDateTime pre = m_querytime;
    QDateTime after = m_querytime;
    int interval = m_interval*60;
    QString stime = m_querytime.time().toString("hh:mm");
    QString sdate = m_querytime.date().toString("yyyy-MM-dd");
    displayModel->removeColumns(1,5);
    for(int i = 0;i<5;i++)
    {
        int line = 5-i;
        pre = m_querytime.addSecs(-interval*i);
        after = pre.addSecs(-interval);
        QString pretime = pre.toString(Qt::TextDate);
        QString aftertime = after.toString(Qt::TextDate);
        stime = after.time().toString("hh:mm");
        displayModel->setHorizontalHeaderItem(0,new QStandardItem(after.date().toString("yyyy-MM-dd")));
        displayModel->setHorizontalHeaderItem(line,new QStandardItem(stime));

        {
            //nibp
            QString filter = "select * from para_nibp where para_datetime >= '"+aftertime+
                    "' and para_datetime < '"+pretime+"' limit 1";
            QSqlQuery q(filter);
            if(q.next())
            {

                QString vss = q.value(NIBP_TABLE_VIEW_SS).toString();
                QString vsz = q.value(NIBP_TABLE_VIEW_SZ).toString();
                QString vpj = q.value(NIBP_TABLE_VIEW_PJ).toString();
                displayModel->setItem( TREND_TABLE_NIBPSS, line, new QStandardItem(vss));
                displayModel->setItem(TREND_TABLE_NIBPSZ, line, new QStandardItem(vsz));
                displayModel->setItem(TREND_TABLE_NIBPPJ, line, new QStandardItem(vpj));
                bool bss = q.value(NIBP_TABLE_ALM1).toBool();
                bool bsz = q.value(NIBP_TABLE_ALM2).toBool();
                bool bpj = q.value(NIBP_TABLE_ALM3).toBool();
                QColor color("yellow");
                QBrush brs(color);

                if(bss)
                {
                    displayModel->item(TREND_TABLE_NIBPSS, line)->setBackground(brs);
                }
                if(bsz)
                {
                    displayModel->item(TREND_TABLE_NIBPSZ,line)->setBackground(brs);
                }
                if(bpj)
                {
                    displayModel->item(TREND_TABLE_NIBPPJ, line)->setBackground(brs);
                }

            }
            else
            {
                displayModel->setItem( TREND_TABLE_NIBPSS, line, new QStandardItem("---"));
                displayModel->setItem(TREND_TABLE_NIBPSZ, line, new QStandardItem("---"));
                displayModel->setItem(TREND_TABLE_NIBPPJ, line, new QStandardItem("---"));
            }
        }
        {
            //BEATRATE

            QString filter = "select * from para_beatrate where para_datetime >= '"+aftertime+
                    "' and para_datetime < '"+pretime+"' limit 1";
            QSqlQuery q(filter);
            if(q.next())
            {

                QString vss = q.value(BEATRATE_TABLE_VAL).toString();

                displayModel->setItem( TREND_TABLE_BEATRATE, line, new QStandardItem(vss));

                bool bss = q.value(BEATRATE_TABLE_ALM).toBool();

                QColor color("yellow");
                QBrush brs(color);

                if(bss)
                {
                    displayModel->item(TREND_TABLE_BEATRATE, line)->setBackground(brs);
                }

            }
            else
            {
                displayModel->setItem( TREND_TABLE_BEATRATE, line, new QStandardItem("---"));

            }
        }
        {
            //ecg breath

            QString filter = "select * from para_breathrate where para_datetime >= '"+aftertime+
                    "' and para_datetime < '"+pretime+"' limit 1";
            QSqlQuery q(filter);
            if(q.next())
            {

                QString vss = q.value(SPIRE_TABLE_VAL).toString();

                displayModel->setItem( TREND_TABLE_SPIRERATE, line, new QStandardItem(vss));

                bool bss = q.value(SPIRE_TABLE_ALM).toBool();

                QColor color("yellow");
                QBrush brs(color);

                if(bss)
                {
                    displayModel->item(TREND_TABLE_SPIRERATE, line)->setBackground(brs);
                }

            }
            else
            {
                displayModel->setItem( TREND_TABLE_SPIRERATE, line, new QStandardItem("---"));

            }
        }
        {
            //spo2
            QString filter = "select * from para_spo2 where para_datetime >= '"+aftertime+
                    "' and para_datetime < '"+pretime+"' limit 1";
            QSqlQuery q(filter);
            if(q.next())
            {
                QString vss;
                QString vsz;
                int spo = q.value(SPO2_TABLE_SPO).toInt();
                if(spo != -100)
                {
                     vss = QString::number(spo,10);
                     displayModel->setItem( TREND_TABLE_SPO2, line, new QStandardItem(vss));
                }
                else
                {
                    displayModel->setItem( TREND_TABLE_SPO2, line, new QStandardItem("---"));
                }
                int pr = q.value(SPO2_TABLE_PR).toInt();
                if(pr != -100)
                {
                    vsz = QString::number(pr,10);
                    displayModel->setItem(TREND_TABLE_PULSERATE, line, new QStandardItem(vsz));
                }else
                {
                    displayModel->setItem(TREND_TABLE_PULSERATE, line, new QStandardItem("---"));
                }
                //QString vss = q.value(SPO2_TABLE_SPO).toString();
                //QString vsz = q.value(SPO2_TABLE_PR).toString();

                bool bss = q.value(SPO2_TABLE_ALM1).toBool();
                bool bsz = q.value(SPO2_TABLE_ALM2).toBool();

                QColor color("yellow");
                QBrush brs(color);

                if(bss)
                {
                    displayModel->item(TREND_TABLE_SPO2, line)->setBackground(brs);
                }
                if(bsz)
                {
                    displayModel->item(TREND_TABLE_PULSERATE,line)->setBackground(brs);
                }


            }
            else
            {
                displayModel->setItem( TREND_TABLE_SPO2, line, new QStandardItem("---"));
                displayModel->setItem(TREND_TABLE_PULSERATE, line, new QStandardItem("---"));

            }
        }
        {
            //temperature
            QString filter = "select * from para_temperature where para_datetime >= '"+aftertime+
                    "' and para_datetime < '"+pretime+"' limit 1";
            QSqlQuery q(filter);
            if(q.next())
            {

                //QString vss = q.value(TEMP_TABLE_VAL1).toString();
                //QString vsz = q.value(TEMP_TABLE_VAL2).toString();
                QString vss;
                QString vsz;
                int temp1 = q.value(TEMP_TABLE_VAL1).toInt();
                int temp2 = q.value(TEMP_TABLE_VAL2).toInt();
                if(temp1 != -100)
                {

                    double tmp = temp1;
                    tmp  /=10;
                    vss = QString::number(tmp,'f',1);
                    displayModel->setItem( TREND_TABLE_TEMP1, line, new QStandardItem(vss));
                }
                else
                {
                    displayModel->setItem( TREND_TABLE_TEMP1, line, new QStandardItem("---"));
                }
                if(temp2 != -100)
                {
                    double tmp = temp2;
                    tmp  /=10;
                    vsz = QString::number(tmp,'f',1);
                    displayModel->setItem(TREND_TABLE_TEMP2, line, new QStandardItem(vsz));
                }
                else
                {
                     displayModel->setItem(TREND_TABLE_TEMP2, line, new QStandardItem("---"));
                }

                bool bss = q.value(TEMP_TABLE_ALM1).toBool();
                bool bsz = q.value(TEMP_TABLE_ALM2).toBool();

                QColor color("yellow");
                QBrush brs(color);

                if(bss)
                {
                    displayModel->item(TREND_TABLE_TEMP1, line)->setBackground(brs);
                }
                if(bsz)
                {
                    displayModel->item(TREND_TABLE_TEMP2,line)->setBackground(brs);
                }


            }
            else
            {
                displayModel->setItem( TREND_TABLE_TEMP1, line, new QStandardItem("---"));
                displayModel->setItem(TREND_TABLE_TEMP2, line, new QStandardItem("---"));

            }
        }
    }
}

bool CDlgHisQushibiao::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={

        m_cmbb_interval,
        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    int iTotalObj =  8;//11
    int iOkPos = iTotalObj -2;
    int iCancelPos = iTotalObj -1;
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
                if((iCursor>=0) &&(iCursor<1))
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
                if((iCursor>=0) &&(iCursor<1))
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
                if((iCursor>=0) &&(iCursor<1))
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
                    case 1:
                        slot_back_end();
                        break;
                    case 2:
                        slot_back_fast();
                        break;

                    case 3:
                        slot_back();
                        break;
                    case 4:
                        slot_forwd();
                        break;
                    case 5:
                        slot_forwd_fast();
                        break;
                    case 6:
                        slot_forwd_end();
                        break;
                    case 7:
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
void CDlgHisQushibiao::slot_back_end()
{
    int interval = -30;
    QDateTime now = QDateTime::currentDateTime();
    m_querytime = now.addDays(interval).addSecs(60*m_interval*5);
    f_read_para();
}
void CDlgHisQushibiao::slot_back_fast()
{
    int interval = -m_interval*60*5;
    QDateTime now = QDateTime::currentDateTime().addDays(-30).addSecs(60*m_interval*5);
    m_querytime = m_querytime.addSecs(interval);
    if(m_querytime< now)
    {
        m_querytime = now;
    }
    f_read_para();
}
void CDlgHisQushibiao::slot_back()
{
    int interval = -m_interval*60;
    QDateTime now = QDateTime::currentDateTime().addDays(-30).addSecs(60*m_interval*5);
    m_querytime = m_querytime.addSecs(interval);
    if(m_querytime < now)
    {
        m_querytime = now;
    }
    f_read_para();
}
void CDlgHisQushibiao::slot_forwd_end()
{

    m_querytime = QDateTime::currentDateTime();
    f_read_para();
}
void CDlgHisQushibiao::slot_forwd_fast()
{
    int interval = m_interval*60*5;
    QDateTime now = QDateTime::currentDateTime();

    m_querytime = m_querytime.addSecs(interval);
    if(m_querytime > now)
    {
        m_querytime = now;
    }
    f_read_para();
}
void CDlgHisQushibiao::slot_forwd()
{

    int interval = m_interval*60;
    QDateTime now = QDateTime::currentDateTime();

    m_querytime = m_querytime.addSecs(interval);
    if(m_querytime > now)
    {
        m_querytime = now;
    }
    f_read_para();
}
void CDlgHisQushibiao::slot_return()
{
    close();
}
