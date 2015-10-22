 #include <QKeyEvent>
#include "dlg_set_alarm.h"
#include "main.h"
#include "mainform.h"
#define DLG_SET_ALARM_COMBOBOX_NUM 6
CDlgSetAlm::CDlgSetAlm(QWidget * parent,QWidget *pMain):QDialog(parent)
{
     iCursor = 0;
     bCursorSta = false;
     pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SET_ALARM_COMBOBOX_NUM];
    cmb[0] = m_cmbb_volume;
    cmb[1] =m_cmbb_pause_interval;
    cmb[2] =m_cmbb_corusecate;
    cmb[3] =m_cmbb_para_alarm;
    cmb[4] =m_cmbb_alarm_record;
    cmb[5] =m_cmbb_alarm_voice;

    //增加选择项
     QStringList items;
     items<<"0"<<"1"<<"2"<<"3";
    cmb[0]->addItems(items);
    items.clear();
    items<<"1分钟"<<"2分钟";
    cmb[1]->addItems(items);
    items.clear();
    items<<"栓锁"<<"非栓锁";
    cmb[3]->addItems(items);
    items.clear();
    items<<"开"<<"关";
    cmb[2]->addItems(items);
    cmb[4]->addItems(items);
    cmb[5]->addItems(items);

    for(int i=0;i< DLG_SET_ALARM_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_ALARM_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    m_btn_cancel->installEventFilter(this);
    m_btn_ok->installEventFilter(this);
     setTabOrder(cmb[DLG_SET_ALARM_COMBOBOX_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
     cmb[0]->setFocus();
     stWarnCfg cfg;
     g_WarningCfg->f_getConfig(&cfg);
     m_cmbb_volume->setCurrentIndex(cfg.m_warn_voice_volume);
     m_cmbb_pause_interval->setCurrentIndex(cfg.m_warn_pause_time);
     m_cmbb_corusecate->setCurrentIndex(cfg.m_warn_corusecate);
     m_cmbb_para_alarm->setCurrentIndex(cfg.m_warn_para_lock);
     m_cmbb_alarm_record->setCurrentIndex(cfg.m_warn_record_flg);
     m_cmbb_alarm_voice->setCurrentIndex(cfg.m_warn_voice_flg);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgSetAlm::do_ok_clicked()
{
    stWarnCfg stConfig;
    stConfig.m_warn_corusecate = m_cmbb_corusecate->currentIndex();
    stConfig.m_warn_para_lock = m_cmbb_para_alarm->currentIndex();
    stConfig.m_warn_pause_time = m_cmbb_pause_interval->currentIndex();
    stConfig.m_warn_record_flg = m_cmbb_alarm_record->currentIndex();
    stConfig.m_warn_voice_flg = m_cmbb_alarm_voice->currentIndex();
    stConfig.m_warn_voice_volume = m_cmbb_volume->currentIndex();
    g_WarningCfg->f_setConfig(stConfig);

    close();
}
void CDlgSetAlm::do_cancel_clicked()
{
   close();
}
#define MAX_ALARM_OBJ_CNT 8
#define ALARM_OK_NUM (MAX_ALARM_OBJ_CNT-2)
#define ALARM_CANCEL_NUM (MAX_ALARM_OBJ_CNT-1)
bool CDlgSetAlm::eventFilter(QObject *o,QEvent *e)
{
    QComboBox *btn[DLG_SET_ALARM_COMBOBOX_NUM];
    btn[0] = m_cmbb_volume;
    btn[1] =m_cmbb_pause_interval;
    btn[2] =m_cmbb_corusecate;
    btn[3] =m_cmbb_para_alarm;
    btn[4] =m_cmbb_alarm_record;
    btn[5] =m_cmbb_alarm_voice;
    if(e->type() == QEvent::KeyPress)
    {
        bool iflg = false;
        QKeyEvent *event=(QKeyEvent *)e;
        switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_Left:
            if(bCursorSta == false)
            {
                if((iCursor>0) &&(iCursor<6))
                {
                    btn[iCursor-1]->setFocus();
                }
                else if(iCursor == 0)
                {
                    m_btn_cancel->setFocus();
                }
                else if(iCursor == ALARM_OK_NUM)
                {
                    btn[5]->setFocus();
                }
                else if(iCursor == ALARM_CANCEL_NUM)
                {
                    m_btn_ok->setFocus();
                }
                iCursor--;
                if(iCursor < 0)
                {
                    iCursor = ALARM_OK_NUM;
                }
            }
            else
            {
                //bCursorSta = false;
                if((iCursor == ALARM_OK_NUM)||(iCursor == ALARM_CANCEL_NUM))
                {

                }
                else
                {
                    if( btn[iCursor]->currentIndex()==0)
                        btn[iCursor]->setCurrentIndex(btn[iCursor]->count()-1);
                    else
                        btn[iCursor]->setCurrentIndex(btn[iCursor]->currentIndex()-1);
                }
            }

            return true;
            break;
        case Qt::Key_Down:
        case Qt::Key_Right:
            if(bCursorSta == false)
            {
                if((iCursor>=0) &&(iCursor<(ALARM_OK_NUM-1)))
                {
                    btn[iCursor+1]->setFocus();
                }
                else if(iCursor == ALARM_OK_NUM-1)
                {
                    m_btn_ok->setFocus();
                }
                else if(iCursor == ALARM_OK_NUM)
                {
                    m_btn_cancel->setFocus();
                }
                else if(iCursor == ALARM_CANCEL_NUM)
                {
                    btn[0]->setFocus();

                }
                iCursor++;
                if(iCursor > ALARM_CANCEL_NUM)
                {
                    iCursor = 0;
                }
            }
            else
            {
                //bCursorSta = false;
                if(iCursor < ALARM_OK_NUM)
                {
                    if( btn[iCursor]->currentIndex()==btn[iCursor]->count()-1)
                        btn[iCursor]->setCurrentIndex(0);
                    else
                        btn[iCursor]->setCurrentIndex(btn[iCursor]->currentIndex()+1);
                }
            }
            return true;
            break;


        case Qt::Key_Return:

            if(bCursorSta == false)
            {
                if(iCursor == ALARM_OK_NUM)
                {
                    do_ok_clicked();
                }
                else if(iCursor == ALARM_CANCEL_NUM)
                {
                    do_cancel_clicked();
                }
                else if(iCursor<ALARM_OK_NUM)
                {
                    //btn[iCursor]->showPopup();
                    bCursorSta = true;
                    btn[iCursor]->setStyleSheet("background-color: rgb(35, 53, 234);");
                }
            }
            else
            {
                bCursorSta = false;
                btn[iCursor]->setStyleSheet("background-color: rgb(255, 255, 255);");
                if(iCursor < ALARM_OK_NUM)
                {
                    //iCursor++;
                    //btn[iCursor ]->setFocus();
                }
            }
        return true;
            break;

        default:
            CMainForm *p = (CMainForm *)pMainForm;
            p->f_process_key(event->key());
            //QWidget::keyPressEvent(event);
            return false;
        }
    }
    else
    {
        return false;
    }
    //return true;
}

