#include "dlg_set_spo2.h"
#include "../rsc_modu/modu_ecg.h"
#include "mainform.h"
#define DLG_SET_SPO2_COMBOBOX_NUM 6

CDlgSetSpo2::CDlgSetSpo2(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SET_SPO2_COMBOBOX_NUM];
   cmb[0] = m_cmbb_maiboyinliang;
    cmb[1] =m_cmbb_lingmindu;
    cmb[2] =m_cmbb_boxingsudu;
    cmb[3] =m_cmbb_mailv;
    cmb[4] =m_cmbb_boxingmoshi;
    cmb[5] =m_cmbb_maiboyintiaozhi;

    //增加选择项
     QStringList items;
     items<<"0"<<"1"<<"2"<<"3";
    cmb[0]->addItems(items);
    items.clear();
    items<<"高"<<"中"<<"低";
    cmb[1]->addItems(items);
    items.clear();
    items<<"12.5mm/s"<<"25mm/s";
    cmb[2]->addItems(items);
    items.clear();
    items<<"关"<<"开";
    cmb[3]->addItems(items);
    items.clear();
    items<<"线条"<<"填充";
    cmb[4]->addItems(items);
    items.clear();
    items<<"关"<<"开";
    cmb[5]->addItems(items);
    for(int i=0;i< DLG_SET_SPO2_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_SPO2_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
     setTabOrder(cmb[DLG_SET_SPO2_COMBOBOX_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();

    CSpo2ModuleCfg cfg;
    g_EcgModule->f_get_spo2_cfg(&cfg);

    m_cmbb_maiboyinliang->setCurrentIndex(cfg.m_spo2_pulse_vol);
    m_cmbb_lingmindu->setCurrentIndex(cfg.m_spo2_sensitive);
    m_cmbb_boxingsudu->setCurrentIndex(cfg.m_spo2_wave_speed);
    m_cmbb_mailv->setCurrentIndex(cfg.m_spo2_pulse_enable);
    m_cmbb_boxingmoshi->setCurrentIndex(cfg.m_spo2_wave_type);
   m_cmbb_maiboyintiaozhi->setCurrentIndex(cfg.m_spo2_pulse_modulate);
   m_btn_ok->installEventFilter(this);
   m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgSetSpo2::do_ok_clicked()
{
    CSpo2ModuleCfg cfg;
    g_EcgModule->f_get_spo2_cfg(&cfg);
    cfg.m_spo2_pulse_vol= m_cmbb_maiboyinliang->currentIndex();
    cfg.m_spo2_sensitive = m_cmbb_lingmindu->currentIndex();
    cfg.m_spo2_wave_speed = m_cmbb_boxingsudu->currentIndex();
    cfg.m_spo2_pulse_enable = m_cmbb_mailv->currentIndex();
    cfg.m_spo2_wave_type = m_cmbb_boxingmoshi->currentIndex();
    cfg.m_spo2_pulse_modulate = m_cmbb_maiboyintiaozhi->currentIndex();

    g_EcgModule->f_set_spo2_cfg(cfg);

    close();

}
void CDlgSetSpo2::do_cancel_clicked()
{
    close();
}

bool CDlgSetSpo2::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_maiboyinliang
        ,m_cmbb_lingmindu
        ,m_cmbb_boxingsudu
        ,m_cmbb_mailv
        ,m_cmbb_boxingmoshi
        ,m_cmbb_maiboyintiaozhi
        ,m_btn_ok
        ,m_btn_cancel
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
