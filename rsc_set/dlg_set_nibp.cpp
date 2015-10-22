
#include "dlg_set_nibp.h"
#include "mainform.h"
#include "../rsc_modu/modu_ecg.h"
#define DLG_SET_NIBP_COMBOBOX_NUM 3

CDlgSetNIBP::CDlgSetNIBP(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SET_NIBP_COMBOBOX_NUM];
    cmb[0] = m_cmbb_unit;
    cmb[1] =m_cmbb_celiangmoshi;
    cmb[2] =m_cmbb_interval;


    //增加选择项
     QStringList items;
     items<<"mmHg"<<"kPa";
    cmb[0]->addItems(items);
    items.clear();
    items<<"手动"<<"自动"<<"连续";
    cmb[1]->addItems(items);
    items.clear();
    items<<"1分钟"<<"2分钟"<<"3分钟"<<"4分钟"<<"5分钟"<<"10分钟"
           <<"15分钟"<<"30分钟"<<"60分钟"<<"90分钟"<<"120分钟"<<"180分钟"
             <<"240分钟"<<"480分钟";
    cmb[2]->addItems(items);

    for(int i=0;i< DLG_SET_NIBP_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_NIBP_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
     setTabOrder(cmb[DLG_SET_NIBP_COMBOBOX_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();

    CNibpModuleCfg cfg;
    g_EcgModule->f_get_nibp_cfg(&cfg);
    m_cmbb_unit->setCurrentIndex(cfg.m_nibp_unit);
    m_cmbb_celiangmoshi->setCurrentIndex(cfg.m_nibp_mesure_type);
    m_cmbb_interval->setCurrentIndex(cfg.m_nibp_interval);
    if(cfg.m_nibp_mesure_type == 0)
        m_cmbb_interval->setEnabled(false);
    else
        {
        m_cmbb_interval->setEnabled(true);
    }
    iCursor = 0;
    bCursorSta = false;
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
     connect(m_cmbb_celiangmoshi,SIGNAL(activated(int)),this,SLOT(do_model_index_changed(int)));

}
void CDlgSetNIBP::do_ok_clicked()
{
    CNibpModuleCfg cfg;
    g_EcgModule->f_get_nibp_cfg(&cfg);
    cfg.m_nibp_unit = m_cmbb_unit->currentIndex();
    cfg.m_nibp_mesure_type = m_cmbb_celiangmoshi->currentIndex();
    cfg.m_nibp_interval = m_cmbb_interval->currentIndex();
    g_EcgModule->f_set_nibp_cfg(cfg);
    close();
}
void CDlgSetNIBP::do_cancel_clicked()
{
    close();
}
void CDlgSetNIBP::do_model_index_changed(int idx)
{
    if(idx == 0)
        m_cmbb_interval->setEnabled(false);
    else
        {
        m_cmbb_interval->setEnabled(true);
    }
}
bool CDlgSetNIBP::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_unit
        ,m_cmbb_celiangmoshi
        ,m_cmbb_interval
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  5;//11
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
