#include "dlg_record_alarm.h"
#include <QKeyEvent>
#define MAX_DLG_ALARM_COMB 1
#define MAX_DLG_ALARM_BTN 8
CDlgRecordAlarm::CDlgRecordAlarm(QWidget *parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    QComboBox *cmb[MAX_DLG_ALARM_COMB] ={
        m_btn_style
    };
    QPushButton *btn[MAX_DLG_ALARM_BTN] = {
        m_btn_record,
        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    //设置光标顺序
    setTabOrder(m_btn_style,m_btn_record);
    setTabOrder(m_btn_record,m_btn_back_end);
    setTabOrder(m_btn_back_end,m_btn_back_fast);
    setTabOrder(m_btn_back_fast,m_btn_back);
    setTabOrder(m_btn_back,m_btn_forwd);
    setTabOrder(m_btn_forwd,m_btn_forwd_fast);
    setTabOrder(m_btn_forwd_fast,m_btn_forwd_end);
    setTabOrder(m_btn_forwd_end,m_btn_return);
    setTabOrder(m_btn_return,m_btn_style);
    m_btn_style->setFocus();
    for(int i =0;i<MAX_DLG_ALARM_COMB;i++)
    {
        cmb[i]->installEventFilter(this);
    }
    for(int i=0;i<MAX_DLG_ALARM_BTN;i++)
    {
        btn[i]->installEventFilter(this);
    }
}

bool CDlgRecordAlarm::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={

        m_btn_style,
        m_btn_record,
        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    int iTotalObj = 9;//11
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
                        slot_forwd_end();
                        break;
                    case 6:
                        slot_forwd_fast();
                        break;
                    case 7:
                        slot_forwd();
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
            //CMainForm *p = (CMainForm *)pMainForm;
            //p->f_process_key(event->key());
            return true;
            break;

        }
    }
    else
    {
        return false;
    }
}
void CDlgRecordAlarm::slot_back_end()
{

}
void CDlgRecordAlarm::slot_back_fast()
{

}
void CDlgRecordAlarm::slot_back()
{

}
void CDlgRecordAlarm::slot_forwd_end()
{

}
void CDlgRecordAlarm::slot_forwd_fast()
{

}
void CDlgRecordAlarm::slot_forwd()
{

}
void CDlgRecordAlarm::slot_return()
{
    close();
}
