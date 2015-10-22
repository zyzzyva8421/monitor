#include "dlg_set_time.h"
#include <QDateEdit>
#include <QKeyEvent>
#include "mainform.h"
#define DLG_SET_TIME_COMBOBOX_NUM 1
#define DLG_SET_TIME_SPB_NUM 6
void       adjustdate(int year,int  mon,int mday,int hour,int  min,int  sec );
CDlgSetTime::CDlgSetTime(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SET_TIME_COMBOBOX_NUM];
    cmb[0] = m_cmbb_style;
    QSpinBox *spb[DLG_SET_TIME_SPB_NUM];
    spb[0] = m_spb_year;
    spb[1] =  m_spb_month;
    spb[2] =  m_spb_date;
    spb[3] =  m_spb_hour;
    spb[4] =  m_spb_min;
    spb[5] =  m_spb_second;

    //增加选择项
     QStringList items;
     items<<"年/月/日"<<"日/月/年"<<"月/日/年";
    cmb[0]->addItems(items);

    for(int i=0;i< DLG_SET_TIME_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_TIME_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    setTabOrder(cmb[DLG_SET_TIME_COMBOBOX_NUM-1],spb[0]);
    for(int i=0;i< DLG_SET_TIME_SPB_NUM;i++)
    {
        spb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_TIME_SPB_NUM-1))
            break;
        setTabOrder(spb[i],spb[i+1]);
    }
     setTabOrder(spb[DLG_SET_TIME_SPB_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();
    QDateTime datetime;
     datetime = QDateTime::currentDateTime();
    int year = datetime.date().year();
    int month = datetime.date().month();
    int date  = datetime.date().day();
    int hour = datetime.time().hour();
    int min = datetime.time().minute();
    int sec = datetime.time().second();

    m_spb_year->setValue(year);
    m_spb_month->setValue(month);
    m_spb_date->setValue(date);
    m_spb_hour->setValue(hour);
    m_spb_min->setValue(min);
    m_spb_second->setValue(sec);

    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgSetTime::do_ok_clicked()
{
    int year = m_spb_year->value();
    int month = m_spb_month->value();
    int date = m_spb_date->value();
    int hour = m_spb_hour->value();
    int min = m_spb_min->value();
    int sec = m_spb_second->value();
    adjustdate(year,month,date,hour,min,sec);
    close();
}
void CDlgSetTime::do_cancel_clicked()
{
    close();
}
void       adjustdate(int       year,int       mon,int       mday,int       hour,int       min,int       sec       )
{
    time_t       t;
    struct           tm       nowtime       ;
    nowtime.tm_sec=sec;/*       Seconds.[0-60]       (1       leap       second)*/
    nowtime.tm_min=min;/*       Minutes.[0-59]       */
    nowtime.tm_hour=hour;/*       Hours.   [0-23]       */
    nowtime.tm_mday=mday;/*       Day.[1-31]       */
    nowtime.tm_mon=mon-1;/*       Month.   [0-11]       */
    nowtime.tm_year=year-1900       ;/*       Year-       1900.*/
    nowtime.tm_isdst=-1       ;/*       DST.[-1/0/1]*/
    t=mktime(&nowtime);
    stime(&t);
 }
bool CDlgSetTime::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_style
        , m_spb_year
        , m_spb_month
        ,  m_spb_date
        ,  m_spb_hour
        ,  m_spb_min
        ,  m_spb_second
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  9;//11
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
                if((iCursor>=0) &&(iCursor<iOkPos))
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

                if((iCursor >= 1)&&(iCursor <=6))
                {
                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    if(p->value()!= p->minimum())
                    {
                        p->setValue(p->value()-1);
                    }
                    else
                    {
                        p->setValue(p->maximum());
                    }

                }
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
                if((iCursor>=0) &&(iCursor<iOkPos))
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
                if((iCursor >= 1)&&(iCursor <=6))
                {
                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    if(p->value()!= p->maximum())
                    {
                        p->setValue(p->value()+1);
                    }
                    else
                    {
                        p->setValue(p->minimum());
                    }

                }

            }
            return true;
            break;
        case Qt::Key_Return:
            if(bCursorSta == false)
            {
                if(iCursor == iOkPos)
                {
                    do_ok_clicked();
                }
                else if(iCursor == iCancelPos)
                {
                    do_cancel_clicked();
                }
                else if((iCursor>=0) &&(iCursor<1))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }
                else if((iCursor>=1) &&(iCursor<=6))
                {
                    bCursorSta = true;
                    QSpinBox *p = (QSpinBox *)obj[iCursor];

                }


            }
            else
            {
                bCursorSta = false;
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
