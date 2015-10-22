#include "dlg_alm_spo2.h"
#include "mainform.h"
#define DLG_ALM_SPO2_COMBOBOX_NUM 2
#define DLG_ALM_SPO2_SPB_NUM 4

CDlgAlmSPO2::CDlgAlmSPO2(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    QComboBox *cmb[DLG_ALM_SPO2_COMBOBOX_NUM];
    cmb[0] = m_cmbb_spo;
    cmb[1] =m_cmbb_mailv;

    QSpinBox * spb[DLG_ALM_SPO2_SPB_NUM];
    spb[0] = m_spb_spo_h;
    spb[1] = m_spb_spo_l;
    spb[2] = m_spb_mailv_h;
    spb[3] = m_spb_mailv_l;


    //增加选择项
     QStringList items;
     items<<"关"<<"开";

    for(int i=0;i< DLG_ALM_SPO2_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        cmb[i]->addItems(items);
        //设置光标顺序
        setTabOrder(cmb[i],spb[i*2]);
        setTabOrder(spb[i*2],spb[i*2+1]);

        if(i == (DLG_ALM_SPO2_COMBOBOX_NUM-1))
            break;
        setTabOrder(spb[i*2+1],cmb[i+1]);
    }
    for(int i = 0;i<DLG_ALM_SPO2_SPB_NUM;i++)
    {
        spb[i]->installEventFilter(this);
    }
     setTabOrder(spb[DLG_ALM_SPO2_SPB_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();
    CSpo2ModuleCfg cfg;
    g_EcgModule->f_get_spo2_cfg(&cfg);
    m_spb_spo_h->setValue( cfg.m_alarm_high);
    m_spb_spo_l->setValue(cfg.m_alarm_low);
    m_spb_mailv_h->setValue (cfg.m_alarm_pulserate_high);
    m_spb_mailv_l->setValue(cfg.m_alarm_pulserate_low);
    m_cmbb_spo->setCurrentIndex(cfg.m_alram_en);
    m_cmbb_mailv->setCurrentIndex(cfg.m_alram_pulserate_en);
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgAlmSPO2::do_ok_clicked()
{
    CSpo2ModuleCfg cfg;
    g_EcgModule->f_get_spo2_cfg(&cfg);
    cfg.m_alarm_high = m_spb_spo_h->value();
    cfg.m_alarm_low = m_spb_spo_l->value();
    cfg.m_alarm_pulserate_high = m_spb_mailv_h->value();
    cfg.m_alarm_pulserate_low = m_spb_mailv_l->value();
    cfg.m_alram_en = m_cmbb_spo->currentIndex();
    cfg.m_alram_pulserate_en = m_cmbb_mailv->currentIndex();
    g_EcgModule->f_set_spo2_cfg(cfg);
    close();
}
void CDlgAlmSPO2::do_cancel_clicked()
{
    close();
}

bool CDlgAlmSPO2::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_spo
        ,m_spb_spo_h
        ,m_spb_spo_l
        ,m_cmbb_mailv
        ,m_spb_mailv_h
        ,m_spb_mailv_l

        ,m_btn_ok,
        m_btn_cancel
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

                if((iCursor == 1)||
                        (iCursor == 2)||
                        (iCursor == 4)||
                        (iCursor == 5)||
                        (iCursor == 7)||
                        (iCursor == 8)
                        )
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
                if((iCursor>=0) &&(iCursor<(iOkPos-1)))
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

                if((iCursor == 1)||
                        (iCursor == 2)||
                        (iCursor == 4)||
                        (iCursor == 5)||
                        (iCursor == 7)||
                        (iCursor == 8)
                        )
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
                else if((iCursor==0) ||(iCursor==3)||(iCursor==6))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }
                else if((iCursor == 1)||
                (iCursor == 2)||
                (iCursor == 4)||
                (iCursor == 5)||
                (iCursor == 7)||
                (iCursor == 8)
                )
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
