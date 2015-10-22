#include <QKeyEvent>
#include "dlg_serv_xindianjiaozhun.h"
#include "mainform.h"
#define DLG_SERV_ECG_CORRECT_CMBB_NUM 1

CDlgServECGCorrect::CDlgServECGCorrect(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SERV_ECG_CORRECT_CMBB_NUM];
   cmb[0] = m_cmbb_jiaozhun;
  /*   cmb[1] =m_cmbb_pause_interval;
    cmb[2] =m_cmbb_corusecate;
    cmb[3] =m_cmbb_para_alarm;
    cmb[4] =m_cmbb_alarm_record;
    cmb[5] =m_cmbb_alarm_voice;
*/
    //增加选择项
     QStringList items;
     items<<"0"<<"1"<<"2"<<"3";
    cmb[0]->addItems(items);
    cmb[0]->installEventFilter(this);
    for(int i=0;i< DLG_SERV_ECG_CORRECT_CMBB_NUM;i++)
    {
        //设置光标顺序
        if(i == (DLG_SERV_ECG_CORRECT_CMBB_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
     setTabOrder(cmb[DLG_SERV_ECG_CORRECT_CMBB_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgServECGCorrect::do_ok_clicked()
{
    close();

}
void CDlgServECGCorrect::do_cancel_clicked()
{
    close();
}
bool CDlgServECGCorrect::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_jiaozhun
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  3;//11
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
