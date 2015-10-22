
#include "dlg_set_temp.h"
#include "mainform.h"
#include "../rsc_modu/modu_ecg.h"

#define DLG_SET_TEMP_COMBOBOX_NUM 1

CDlgSetTemp::CDlgSetTemp(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SET_TEMP_COMBOBOX_NUM];
   cmb[0] = m_cmbb_unit;
/*     cmb[1] =m_cmbb_pause_interval;
    cmb[2] =m_cmbb_corusecate;
    cmb[3] =m_cmbb_para_alarm;
    cmb[4] =m_cmbb_alarm_record;
    cmb[5] =m_cmbb_alarm_voice;
*/
    //增加选择项
     QStringList items;
     items<<"℃"<<"F";
    cmb[0]->addItems(items);

    for(int i=0;i< DLG_SET_TEMP_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_TEMP_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
     setTabOrder(cmb[DLG_SET_TEMP_COMBOBOX_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);

    CTempModuleCfg cfg;
    g_EcgModule->f_get_temp_cfg(&cfg);
    m_cmbb_unit->setCurrentIndex(cfg.m_temp_unit);
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgSetTemp::do_ok_clicked()
{
    CTempModuleCfg cfg;
    g_EcgModule->f_get_temp_cfg(&cfg);
    cfg.m_temp_unit = m_cmbb_unit->currentIndex();
    g_EcgModule->f_set_temp_cfg(cfg);
    close();
}
void CDlgSetTemp::do_cancel_clicked()
{
    close();
}
bool CDlgSetTemp::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_unit
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
