
#include "dlg_set_spire.h"
#include "mainform.h"
#include "rsc_modu/modu_ecg.h"
#define DLG_SET_SPIRE_COMBOBOX_NUM 5

CDlgSetSpire::CDlgSetSpire(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SET_SPIRE_COMBOBOX_NUM];
    cmb[0] = m_cmbb_zhixibaojing;
    cmb[1] =m_cmbb_boxingfudu;
    cmb[2] =m_cmbb_boxingsudu;
    cmb[3] =m_cmbb_huxidaolian;
    cmb[4] =m_cmbb_huxilaiyuan;

    //增加选择项
     QStringList items;
     items<<"关"<<"10s"<<"15s"<<"20s"<<"30s"<<"35s"<<"40s";
    cmb[0]->addItems(items);
    items.clear();
    items<<"x0.25"<<"x0.5"<<"x1"<<"x2"<<"x4";
    cmb[1]->addItems(items);
    items.clear();
    items<<"6.25mm/s"<<"12.5mm/s"<<"25mm/s";
    cmb[2]->addItems(items);
    items.clear();
    items<<"II"<<"I";
    cmb[3]->addItems(items);
    items.clear();
    items<<"ECG"<<"CO2";
    cmb[4]->addItems(items);
    for(int i=0;i< DLG_SET_SPIRE_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_SPIRE_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
     setTabOrder(cmb[DLG_SET_SPIRE_COMBOBOX_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();
    CSpireModuleCfg cfg;
    g_EcgModule->f_get_spire_cfg(&cfg);
    m_cmbb_zhixibaojing->setCurrentIndex(cfg.m_spire_asp_alarm);
    m_cmbb_boxingfudu->setCurrentIndex(cfg.m_spire_wave_amp);
    m_cmbb_boxingsudu->setCurrentIndex(cfg.m_spire_wave_speed);
    m_cmbb_huxidaolian->setCurrentIndex(cfg.m_spire_lead);
    m_cmbb_huxilaiyuan->setCurrentIndex(cfg.m_spire_src);
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgSetSpire::do_ok_clicked()
{
    CSpireModuleCfg cfg;
    g_EcgModule->f_get_spire_cfg(&cfg);
    cfg.m_spire_asp_alarm = m_cmbb_zhixibaojing->currentIndex();
    cfg.m_spire_wave_amp = m_cmbb_boxingfudu->currentIndex();
    cfg.m_spire_wave_speed  = m_cmbb_boxingsudu->currentIndex();
    cfg.m_spire_lead    = m_cmbb_huxidaolian->currentIndex();
    cfg.m_spire_src     = m_cmbb_huxilaiyuan->currentIndex();
    g_EcgModule->f_set_spire_cfg(cfg);
    close();
}
void CDlgSetSpire::do_cancel_clicked()
{
    close();
}
bool CDlgSetSpire::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_zhixibaojing
        ,m_cmbb_boxingfudu
        ,m_cmbb_boxingsudu
        ,m_cmbb_huxidaolian
        ,m_cmbb_huxilaiyuan
        ,m_btn_ok
        ,m_btn_cancel
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
