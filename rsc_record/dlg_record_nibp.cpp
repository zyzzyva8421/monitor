#include "dlg_record_nibp.h"
#include <QKeyEvent>
#include "mainform.h"
#define MAX_DLG_NIBP_BTN 7
CDlgRecordNIBP::CDlgRecordNIBP(QWidget *parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;

    //设置光标顺序
    QPushButton *btn[MAX_DLG_NIBP_BTN] = {
        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    setTabOrder(m_btn_back_end,m_btn_back_fast);
    setTabOrder(m_btn_back_fast,m_btn_back);
    setTabOrder(m_btn_back,m_btn_forwd);
    setTabOrder(m_btn_forwd,m_btn_forwd_fast);
    setTabOrder(m_btn_forwd_fast,m_btn_forwd_end);
    setTabOrder(m_btn_forwd_end,m_btn_return);
    setTabOrder(m_btn_return,m_btn_back_end);
    m_btn_back_end->setFocus();
    for(int i=0;i<MAX_DLG_NIBP_BTN;i++)
    {
        btn[i]->installEventFilter(this);
    }
    tableModel = new QSqlTableModel(this);
    tableModel->setTable("para_nibp");
    tableModel->setSort(NIBP_TABLE_VIEW_Time,Qt::DescendingOrder);
    tableModel->setHeaderData(NIBP_TABLE_VIEW_Date,Qt::Horizontal,("日期"));
    tableModel->setHeaderData(NIBP_TABLE_VIEW_Time,Qt::Horizontal,("时间"));
    tableModel->setHeaderData(NIBP_TABLE_VIEW_SS,Qt::Horizontal,("收缩压"));
    tableModel->setHeaderData(NIBP_TABLE_VIEW_SZ,Qt::Horizontal,("舒张压"));
    tableModel->setHeaderData(NIBP_TABLE_VIEW_PJ,Qt::Horizontal,("平均压"));

    m_querytime = QDateTime::currentDateTime();//.addSecs(-540); //-10min
    QString stopdate = m_querytime.date().toString("yyyy-MM-dd");
    QString stoptime = m_querytime.time().toString("hh:mm::ss");
    QString stopdatetime = m_querytime.toString(Qt::TextDate);
    //QString filter = "para_date >= '" +stopdate + "'" + "and para_time >= '" + stoptime + "'";
    QString filter = "para_datetime <= '"+stopdatetime +"'";
    tableModel->setFilter(filter);
    tableModel->setFilter("limit 10");
    tableModel->select();
    int rowcount =  tableModel->rowCount();

    displayModel = new QStandardItemModel(this);
    f_set_table_header();
    //bool result =displayModel->insertRows(0,10);

    //if(rowcount >10)
    //{

    //    tableModel->removeRows(10,(rowcount-10));

    //}
    QSqlQuery q("select * from para_nibp where "+filter +" order by para_datetime desc limit 10 ;");
    QSqlRecord rec = q.record();

    int querycnt =  rec.count();
    int i = 0;
    QDateTime tmplastdatetime[10];
    QDate cdate ;
    QTime ctime;
    while (q.next())
    {

        QString vdate = q.value(NIBP_TABLE_VIEW_Date).toString();
        QString vtime = q.value(NIBP_TABLE_VIEW_Time).toString();
        QString vss = q.value(NIBP_TABLE_VIEW_SS).toString();
        QString vsz = q.value(NIBP_TABLE_VIEW_SZ).toString();
        QString vpj = q.value(NIBP_TABLE_VIEW_PJ).toString();
        displayModel->setItem(i, 0, new QStandardItem(vdate));
        displayModel->setItem(i, 1, new QStandardItem(vtime));
        displayModel->setItem(i, 2, new QStandardItem(vss));
        displayModel->setItem(i, 3, new QStandardItem(vsz));
        displayModel->setItem(i, 4, new QStandardItem(vpj));
        bool bss = q.value(NIBP_TABLE_ALM1).toBool();
        bool bsz = q.value(NIBP_TABLE_ALM2).toBool();
        bool bpj = q.value(NIBP_TABLE_ALM3).toBool();
        QColor color("yellow");
        QBrush brs(color);

        if(bss)
        {
            displayModel->item(i,2)->setBackground(brs);
        }
        if(bsz)
        {
            displayModel->item(i,3)->setBackground(brs);
        }
        if(bpj)
        {
            displayModel->item(i,4)->setBackground(brs);
        }
        cdate = QDate::fromString(vdate,("yyyy-MM-dd"));
        ctime = QTime::fromString(vtime,("hh:mm:ss"));
        tmplastdatetime[i].setDate(cdate);
        tmplastdatetime[i].setTime(ctime);
        i++;
    }

    if(i>1)
    {
        m_querytime = tmplastdatetime[0];
    }

    m_lasttime = tmplastdatetime[i-1];
/*

    int row = (rowcount>10)?10:rowcount;
    for(int i = 0; i<row;i++)
    {
        QSqlRecord record = tableModel->record(i);
        QString vdate = record.value(NIBP_TABLE_VIEW_Date).toString();
        QString vtime = record.value(NIBP_TABLE_VIEW_Time).toString();
        QString vss = record.value(NIBP_TABLE_VIEW_SS).toString();
        QString vsz = record.value(NIBP_TABLE_VIEW_SZ).toString();
        QString vpj = record.value(NIBP_TABLE_VIEW_PJ).toString();
        displayModel->setItem(i, 0, new QStandardItem(vdate));
        displayModel->setItem(i, 1, new QStandardItem(vtime));
        displayModel->setItem(i, 2, new QStandardItem(vss));
        displayModel->setItem(i, 3, new QStandardItem(vsz));
        displayModel->setItem(i, 4, new QStandardItem(vpj));
    }
*/
/*
    if(rowcount <10)
    {
        QDate cdate ;
        QTime ctime;
        int row = 0;
        QDateTime vdatetime ;
        for(int i = 0;i<10;i++)
        {
            vdatetime = m_querytime.addSecs((9-i)*60);//table list time
            if(row>=rowcount)
            {
                tableModel->insertRow(i);
            }
            QSqlRecord record = tableModel->record(row);
            cdate = QDate::fromString(record.value(NIBP_TABLE_VIEW_Date).toString(),tr("yyyy-MM-dd"));
            ctime = QTime::fromString(record.value(NIBP_TABLE_VIEW_Time).toString(),tr("hh:mm:ss"));
            //= QDateTime::fromString(nowdatetime,tr("yyyy-MM-ddhh:mm:ss"));
            QDateTime nowtime ; //record time
            nowtime.setDate(cdate);
            nowtime.setTime(ctime);
            if(nowtime == vdatetime)
            {
                row++;
            }
            else
            {
                QString vdate = vdatetime.date().toString("yyyy-MM-dd");
                QString vtime = vdatetime.time().toString("hh:mm:ss");
                tableModel->insertRow(i);
                tableModel->setData(tableModel->index(i,NIBP_TABLE_VIEW_Date),vdate);
                tableModel->setData(tableModel->index(i,NIBP_TABLE_VIEW_Time),vtime);
                tableModel->setData(tableModel->index(i,NIBP_TABLE_VIEW_SS),"---");
                tableModel->setData(tableModel->index(i,NIBP_TABLE_VIEW_SZ),"---");
                tableModel->setData(tableModel->index(i,NIBP_TABLE_VIEW_PJ),"---");
            }
        }



    }
*/
    tv_nibp->setModel(displayModel );//tableModel
    tv_nibp->setSelectionMode(QAbstractItemView::SingleSelection);
    tv_nibp->setSelectionBehavior(QAbstractItemView::SelectRows);
    //tv_nibp->setColumnHidden(NIBP_TABLE_VIEW_Id,true); //id
    //tv_nibp->setColumnHidden(NIBP_TABLE_VIEW_PARAID,true); //para_id
    tv_nibp->setColumnHidden(NIBP_TABLE_DATETIME,true);

    //tv_nibp->resizeColumnsToContents();
    tv_nibp->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tv_nibp->setFocusPolicy(Qt::NoFocus);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel(tableModel);

    //QSqlQueryModel model;
    //model.setQuery("SELECT * FROM para_nibp ");


}

bool CDlgRecordNIBP::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={

        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    int iTotalObj =  7;//11
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
                if((iCursor>=0) &&(iCursor<iTotalObj))
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
                if((iCursor>=0) &&(iCursor<iTotalObj))
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
                if((iCursor>=0) &&(iCursor<iTotalObj ))
                {
                    switch(iCursor)
                    {
                    case 0:
                        slot_back_end();
                        break;
                    case 1:
                        slot_back_fast();
                        break;

                    case 2:
                        slot_back();
                        break;
                    case 3:
                        slot_forwd();
                        break;
                    case 4:
                        slot_forwd_fast();
                        break;
                    case 5:
                        slot_forwd_end();
                        break;
                    case 6:
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
void CDlgRecordNIBP::f_set_table_header()
{

    displayModel->setHorizontalHeaderItem(0, new QStandardItem(("日期")));
    displayModel->setHorizontalHeaderItem(1, new QStandardItem(("时间")));
    displayModel->setHorizontalHeaderItem(2, new QStandardItem(("收缩压")));
    displayModel->setHorizontalHeaderItem(3, new QStandardItem(("舒张压")));
    displayModel->setHorizontalHeaderItem(4, new QStandardItem(("平均压")));

}
void CDlgRecordNIBP::f_set_table_rowname(int row)
{
    QStringList vlabel;// = QString("序号");
    vlabel<<"序号";
    //displayModel->setVerticalHeaderLabels(vlabel);
    for(int i = 0;i<row;i++)
    {
        QString bar = QString(" %1").arg(i);
        displayModel->setVerticalHeaderItem(i, new QStandardItem(bar));
    }
}

void CDlgRecordNIBP::f_set_table_style()
{
    int row = displayModel->rowCount();
    for(int i = 0;i<row;i++)
    {
        if(i%2)
        {
            QColor color("gray");
            QBrush brs(color);
            displayModel->item(i,0)->setBackground(brs);
            displayModel->item(i,1)->setBackground(brs);
            displayModel->item(i,2)->setBackground(brs);
            displayModel->item(i,3)->setBackground(brs);
            displayModel->item(i,4)->setBackground(brs);
        }
    }
}

void CDlgRecordNIBP::slot_back_end()
{
    displayModel->clear();
    f_set_table_header();
    displayModel->clear();
    f_set_table_header();
    QString stopdatetime = m_lasttime.toString(Qt::TextDate);
    QString filter = "para_datetime >= '"+stopdatetime +"' ";
    QSqlQuery q("select  * from para_nibp order by para_datetime asc limit 10 ;");

    int i = 0;
    QString vdate ;
    QString vtime;
    QString vss;
    QString vsz ;
    QString vpj ;
    QDateTime tmpdatetime[11];
    QDate cdate ;
    QTime ctime;
    while (q.next())
    {
        vdate = q.value(NIBP_TABLE_VIEW_Date).toString();
        vtime = q.value(NIBP_TABLE_VIEW_Time).toString();
        vss = q.value(NIBP_TABLE_VIEW_SS).toString();
        vsz = q.value(NIBP_TABLE_VIEW_SZ).toString();
        vpj = q.value(NIBP_TABLE_VIEW_PJ).toString();
        displayModel->setItem(10-i, 0, new QStandardItem(vdate));
        displayModel->setItem(10-i, 1, new QStandardItem(vtime));
        displayModel->setItem(10-i, 2, new QStandardItem(vss));
        displayModel->setItem(10-i, 3, new QStandardItem(vsz));
        displayModel->setItem(10-i, 4, new QStandardItem(vpj));
        bool bss = q.value(NIBP_TABLE_ALM1).toBool();
        bool bsz = q.value(NIBP_TABLE_ALM2).toBool();
        bool bpj = q.value(NIBP_TABLE_ALM3).toBool();
        QColor color("yellow");
        QBrush brs(color);

        if(bss)
        {
            displayModel->item(10-i,2)->setBackground(brs);
        }
        if(bsz)
        {
            displayModel->item(10-i,3)->setBackground(brs);
        }
        if(bpj)
        {
            displayModel->item(10-i,4)->setBackground(brs);
        }
        cdate = QDate::fromString(vdate,("yyyy-MM-dd"));
        ctime = QTime::fromString(vtime,("hh:mm:ss"));
        tmpdatetime[i].setDate(cdate);
        tmpdatetime[i].setTime(ctime);
        i++;
    }
    if(i>0)
    {
         m_querytime= tmpdatetime[i-1];
         m_lasttime = tmpdatetime[0];
    }

    if(i>10)
    {
        displayModel->removeRow(10);
        m_lasttime = tmpdatetime[1];


    }
    else
    {
        displayModel->removeRows(0,11-i);

    }
    int row = displayModel->rowCount();
    f_set_table_rowname(row);
    //f_set_table_style();
}
void CDlgRecordNIBP::slot_back_fast()
{

    displayModel->clear();
    f_set_table_header();

    QString stopdatetime = m_querytime.toString(Qt::TextDate);
    QString filter = "para_datetime <= '"+stopdatetime +"' ";
    QSqlQuery q("select * from para_nibp where "+filter +" order by para_datetime desc limit 20 ;");

    int i = 0;
    QString vdate ;
    QString vtime;
    QString vss;
    QString vsz ;
    QString vpj ;
    QDateTime tmpdatetime[20];
    QDate cdate ;
    QTime ctime;
    while (q.next())
    {
        vdate = q.value(NIBP_TABLE_VIEW_Date).toString();
        vtime = q.value(NIBP_TABLE_VIEW_Time).toString();
        vss = q.value(NIBP_TABLE_VIEW_SS).toString();
        vsz = q.value(NIBP_TABLE_VIEW_SZ).toString();
        vpj = q.value(NIBP_TABLE_VIEW_PJ).toString();
        displayModel->setItem(i, 0, new QStandardItem(vdate));
        displayModel->setItem(i, 1, new QStandardItem(vtime));
        displayModel->setItem(i, 2, new QStandardItem(vss));
        displayModel->setItem(i, 3, new QStandardItem(vsz));
        displayModel->setItem(i, 4, new QStandardItem(vpj));
        bool bss = q.value(NIBP_TABLE_ALM1).toBool();
        bool bsz = q.value(NIBP_TABLE_ALM2).toBool();
        bool bpj = q.value(NIBP_TABLE_ALM3).toBool();
        QColor color("yellow");
        QBrush brs(color);

        if(bss)
        {
            displayModel->item(i,2)->setBackground(brs);
        }
        if(bsz)
        {
            displayModel->item(i,3)->setBackground(brs);
        }
        if(bpj)
        {
            displayModel->item(i,4)->setBackground(brs);
        }
        cdate = QDate::fromString(vdate,("yyyy-MM-dd"));
        ctime = QTime::fromString(vtime,("hh:mm:ss"));
        tmpdatetime[i].setDate(cdate);
        tmpdatetime[i].setTime(ctime);
        i++;
    }

    if(i>0)
    {
        m_lasttime = tmpdatetime[i-1];
        m_querytime = tmpdatetime[0];
    }

    if(i>10)
    {
        displayModel->removeRows(i,20-i);
        displayModel->removeRows(0,i-10);
        m_querytime = tmpdatetime[i-10];

    }
    else
    {
        displayModel->removeRows(i,20-i);
    }
    int row = displayModel->rowCount();
    f_set_table_rowname(row);
    //f_set_table_style();
}
void CDlgRecordNIBP::slot_back()
{

    displayModel->clear();
    f_set_table_header();

    QString stopdatetime = m_querytime.toString(Qt::TextDate);
    QString filter = "para_datetime <= '"+stopdatetime +"' ";
    QSqlQuery q("select * from para_nibp where "+filter +" order by para_datetime desc limit 11 ;");

    int i = 0;
    QString vdate ;
    QString vtime;
    QString vss;
    QString vsz ;
    QString vpj ;
    QDateTime tmpdatetime[11];
    QDate cdate ;
    QTime ctime;
    while (q.next())
    {
        vdate = q.value(NIBP_TABLE_VIEW_Date).toString();
        vtime = q.value(NIBP_TABLE_VIEW_Time).toString();
        vss = q.value(NIBP_TABLE_VIEW_SS).toString();
        vsz = q.value(NIBP_TABLE_VIEW_SZ).toString();
        vpj = q.value(NIBP_TABLE_VIEW_PJ).toString();
        displayModel->setItem(i, 0, new QStandardItem(vdate));
        displayModel->setItem(i, 1, new QStandardItem(vtime));
        displayModel->setItem(i, 2, new QStandardItem(vss));
        displayModel->setItem(i, 3, new QStandardItem(vsz));
        displayModel->setItem(i, 4, new QStandardItem(vpj));
        bool bss = q.value(NIBP_TABLE_ALM1).toBool();
        bool bsz = q.value(NIBP_TABLE_ALM2).toBool();
        bool bpj = q.value(NIBP_TABLE_ALM3).toBool();
        QColor color("yellow");
        QBrush brs(color);

        if(bss)
        {
            displayModel->item(i,2)->setBackground(brs);
        }
        if(bsz)
        {
            displayModel->item(i,3)->setBackground(brs);
        }
        if(bpj)
        {
            displayModel->item(i,4)->setBackground(brs);
        }
        cdate = QDate::fromString(vdate,("yyyy-MM-dd"));
        ctime = QTime::fromString(vtime,("hh:mm:ss"));
        tmpdatetime[i].setDate(cdate);
        tmpdatetime[i].setTime(ctime);
        i++;
    }

    if(i>0)
    {
        m_lasttime = tmpdatetime[i-1];
        m_querytime = tmpdatetime[0];
    }

    if(i>10)
    {
        displayModel->removeRow(0);
        m_querytime = tmpdatetime[1];


    }
    else
    {
        displayModel->removeRows(i,11-i);
    }
    int row = displayModel->rowCount();
    f_set_table_rowname(row);
    //f_set_table_style();


}
void CDlgRecordNIBP::slot_forwd_end()
{
    displayModel->clear();
    f_set_table_header();

    QSqlQuery q("select * from para_nibp  order by para_datetime desc limit 10 ;");

    int i = 0;
    QString vdate ;
    QString vtime;
    QString vss;
    QString vsz ;
    QString vpj ;
    QDateTime tmpdatetime[11];
    QDate cdate ;
    QTime ctime;
    while (q.next())
    {
        vdate = q.value(NIBP_TABLE_VIEW_Date).toString();
        vtime = q.value(NIBP_TABLE_VIEW_Time).toString();
        vss = q.value(NIBP_TABLE_VIEW_SS).toString();
        vsz = q.value(NIBP_TABLE_VIEW_SZ).toString();
        vpj = q.value(NIBP_TABLE_VIEW_PJ).toString();
        displayModel->setItem(i, 0, new QStandardItem(vdate));
        displayModel->setItem(i, 1, new QStandardItem(vtime));
        displayModel->setItem(i, 2, new QStandardItem(vss));
        displayModel->setItem(i, 3, new QStandardItem(vsz));
        displayModel->setItem(i, 4, new QStandardItem(vpj));

        bool bss = q.value(NIBP_TABLE_ALM1).toBool();
        bool bsz = q.value(NIBP_TABLE_ALM2).toBool();
        bool bpj = q.value(NIBP_TABLE_ALM3).toBool();
        QColor color("yellow");
        QBrush brs(color);

        if(bss)
        {
            displayModel->item(i,2)->setBackground(brs);
        }
        if(bsz)
        {
            displayModel->item(i,3)->setBackground(brs);
        }
        if(bpj)
        {
            displayModel->item(i,4)->setBackground(brs);
        }
        cdate = QDate::fromString(vdate,("yyyy-MM-dd"));
        ctime = QTime::fromString(vtime,("hh:mm:ss"));
        tmpdatetime[i].setDate(cdate);
        tmpdatetime[i].setTime(ctime);
        i++;
    }

    if(i>0)
    {
        m_lasttime = tmpdatetime[i-1];
        m_querytime = tmpdatetime[0];
    }

    if(i>10)
    {
        displayModel->removeRow(0);
        m_querytime = tmpdatetime[1];

    }
    else
    {
        displayModel->removeRows(i,11-i);
    }
    int row = displayModel->rowCount();
    f_set_table_rowname(row);
    //f_set_table_style();
}
void CDlgRecordNIBP::slot_forwd_fast()
{

    displayModel->clear();
    f_set_table_header();
    QString stopdatetime = m_lasttime
            .toString(Qt::TextDate);
    QString filter = "para_datetime >= '"+stopdatetime +"' ";
    QSqlQuery q("select  * from para_nibp where "+filter +" order by para_datetime asc limit 20 ;");



    int i = 0;
    QString vdate ;
    QString vtime;
    QString vss;
    QString vsz ;
    QString vpj ;
    QDateTime tmpdatetime[20];
    QDate cdate ;
    QTime ctime;
    int pos = 20-1;
    while (q.next())
    {
        vdate = q.value(NIBP_TABLE_VIEW_Date).toString();
        vtime = q.value(NIBP_TABLE_VIEW_Time).toString();
        vss = q.value(NIBP_TABLE_VIEW_SS).toString();
        vsz = q.value(NIBP_TABLE_VIEW_SZ).toString();
        vpj = q.value(NIBP_TABLE_VIEW_PJ).toString();
        displayModel->setItem(pos-i, 0, new QStandardItem(vdate));
        displayModel->setItem(pos-i, 1, new QStandardItem(vtime));
        displayModel->setItem(pos-i, 2, new QStandardItem(vss));
        displayModel->setItem(pos-i, 3, new QStandardItem(vsz));
        displayModel->setItem(pos-i, 4, new QStandardItem(vpj));
        bool bss = q.value(NIBP_TABLE_ALM1).toBool();
        bool bsz = q.value(NIBP_TABLE_ALM2).toBool();
        bool bpj = q.value(NIBP_TABLE_ALM3).toBool();
        QColor color("yellow");
        QBrush brs(color);

        if(bss)
        {
            displayModel->item(pos-i,2)->setBackground(brs);
        }
        if(bsz)
        {
            displayModel->item(pos-i,3)->setBackground(brs);
        }
        if(bpj)
        {
            displayModel->item(pos-i,4)->setBackground(brs);
        }
        cdate = QDate::fromString(vdate,("yyyy-MM-dd"));
        ctime = QTime::fromString(vtime,("hh:mm:ss"));
        tmpdatetime[i].setDate(cdate);
        tmpdatetime[i].setTime(ctime);
        i++;
    }
    if(i>0)
    {
         m_querytime= tmpdatetime[i-1];
         m_lasttime = tmpdatetime[0];
    }
    if(i>10)
    {
        displayModel->removeRows(0,20-i);
        displayModel->removeRows(10,i-10);
        m_lasttime = tmpdatetime[i-10];
    }
    else
    {
        displayModel->removeRows(0,20-i);
    }
    int row = displayModel->rowCount();
    f_set_table_rowname(row);
    //f_set_table_style();
}
void CDlgRecordNIBP::slot_forwd()
{

    displayModel->clear();
    f_set_table_header();
    QString stopdatetime = m_lasttime.toString(Qt::TextDate);
    QString filter = "para_datetime >= '"+stopdatetime +"' ";
    QSqlQuery q("select  * from para_nibp where "+filter +" order by para_datetime asc limit 11 ;");



    int i = 0;
    QString vdate ;
    QString vtime;
    QString vss;
    QString vsz ;
    QString vpj ;
    QDateTime tmpdatetime[11];
    QDate cdate ;
    QTime ctime;
    while (q.next())
    {
        vdate = q.value(NIBP_TABLE_VIEW_Date).toString();
        vtime = q.value(NIBP_TABLE_VIEW_Time).toString();
        vss = q.value(NIBP_TABLE_VIEW_SS).toString();
        vsz = q.value(NIBP_TABLE_VIEW_SZ).toString();
        vpj = q.value(NIBP_TABLE_VIEW_PJ).toString();
        displayModel->setItem(10-i, 0, new QStandardItem(vdate));
        displayModel->setItem(10-i, 1, new QStandardItem(vtime));
        displayModel->setItem(10-i, 2, new QStandardItem(vss));
        displayModel->setItem(10-i, 3, new QStandardItem(vsz));
        displayModel->setItem(10-i, 4, new QStandardItem(vpj));
        bool bss = q.value(NIBP_TABLE_ALM1).toBool();
        bool bsz = q.value(NIBP_TABLE_ALM2).toBool();
        bool bpj = q.value(NIBP_TABLE_ALM3).toBool();
        QColor color("yellow");
        QBrush brs(color);

        if(bss)
        {
            displayModel->item(10-i,2)->setBackground(brs);
        }
        if(bsz)
        {
            displayModel->item(10-i,3)->setBackground(brs);
        }
        if(bpj)
        {
            displayModel->item(10-i,4)->setBackground(brs);
        }
        cdate = QDate::fromString(vdate,("yyyy-MM-dd"));
        ctime = QTime::fromString(vtime,("hh:mm:ss"));
        tmpdatetime[i].setDate(cdate);
        tmpdatetime[i].setTime(ctime);
        i++;
    }
    if(i>0)
    {
         m_querytime= tmpdatetime[i-1];
         m_lasttime = tmpdatetime[0];
    }

    if(i>10)
    {
        displayModel->removeRow(10);
        m_lasttime = tmpdatetime[1];


    }
    else
    {
        displayModel->removeRows(0,11-i);

    }
    int row = displayModel->rowCount();
    f_set_table_rowname(row);
    //f_set_table_style();

}
void CDlgRecordNIBP::slot_return()
{
    close();
}
