#include "dlg_set_record.h"
#include <QKeyEvent>
#include "mainform.h"
#define DLG_SET_RECORD_COMBOBOX_NUM 7

CDlgSetRecord::CDlgSetRecord(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SET_RECORD_COMBOBOX_NUM];
    cmb[0] = m_cmbb_wave1;
    cmb[1] =m_cmbb_wave2;
    cmb[2] =m_cmbb_wave3;
    cmb[3] =m_cmbb_grid;
    cmb[4] =m_cmbb_lengh;
    cmb[5] =m_cmbb_interval;
    cmb[6] =m_cmbb_speed;

    //增加选择项
     QStringList items;
     items<<"0"<<"1"<<"2"<<"3";
    cmb[0]->addItems(items);

    for(int i=0;i< DLG_SET_RECORD_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_RECORD_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
     setTabOrder(cmb[DLG_SET_RECORD_COMBOBOX_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
     m_btn_ok->installEventFilter(this);
     m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgSetRecord::do_ok_clicked()
{

    close();
}
void CDlgSetRecord::do_cancel_clicked()
{

    close();
}
bool CDlgSetRecord::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_wave1
        ,m_cmbb_wave2
        ,m_cmbb_wave3
        ,m_cmbb_grid
        ,m_cmbb_lengh
        ,m_cmbb_interval
        ,m_cmbb_speed
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
                else if((iCursor>=0) &&(iCursor<iOkPos))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
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
