#include "dlg_alm_nibp.h"
#include "mainform.h"
#define DLG_ALM_NIBP_COMBOBOX_NUM 3
#define DLG_ALM_NIBP_SPB_NUM 6

CDlgAlmNIBP::CDlgAlmNIBP(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    QComboBox *cmb[DLG_ALM_NIBP_COMBOBOX_NUM];
    cmb[0] = m_cmbb_ss;
    cmb[1] =m_cmbb_sz;
    cmb[2] =m_cmbb_pj;
    QSpinBox * spb[DLG_ALM_NIBP_SPB_NUM];
    spb[0] = m_spb_ss_h;
    spb[1] = m_spb_ss_l;
    spb[2] = m_spb_sz_h;
    spb[3] = m_spb_sz_l;
    spb[4] = m_spb_pj_h;
    spb[5] = m_spb_pj_l;

    //增加选择项
     QStringList items;
     items<<"关"<<"开";

    for(int i=0;i< DLG_ALM_NIBP_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        cmb[i]->addItems(items);
        //设置光标顺序
        setTabOrder(cmb[i],spb[i*2]);
        setTabOrder(spb[i*2],spb[i*2+1]);

        if(i == (DLG_ALM_NIBP_COMBOBOX_NUM-1))
            break;
        setTabOrder(spb[i*2+1],cmb[i+1]);
    }
    for(int i = 0;i<DLG_ALM_NIBP_SPB_NUM;i++)
    {
        spb[i]->installEventFilter(this);
    }
     setTabOrder(spb[DLG_ALM_NIBP_SPB_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();
    CNibpModuleCfg cfg;
    g_EcgModule->f_get_nibp_cfg(&cfg);
    m_cmbb_ss->setCurrentIndex(cfg.m_alarm_ss_en);
    m_cmbb_sz->setCurrentIndex(cfg.m_alarm_sz_en);
    m_cmbb_pj->setCurrentIndex(cfg.m_alarm_pj_en);
    m_spb_ss_h->setValue(cfg.m_alarm_ss_high);
    m_spb_ss_l->setValue(cfg.m_alarm_ss_low);
    m_spb_sz_h->setValue(cfg.m_alarm_sz_high);
    m_spb_sz_l->setValue(cfg.m_alarm_sz_low);
    m_spb_pj_h->setValue(cfg.m_alarm_pj_high);
    m_spb_pj_l->setValue(cfg.m_alarm_pj_low);
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgAlmNIBP::do_ok_clicked()
{
    CNibpModuleCfg cfg;
    g_EcgModule->f_get_nibp_cfg(&cfg);
    cfg.m_alarm_ss_en = m_cmbb_ss->currentIndex();
    cfg.m_alarm_sz_en = m_cmbb_sz->currentIndex();
    cfg.m_alarm_pj_en = m_cmbb_pj->currentIndex();
    cfg.m_alarm_ss_high= m_spb_ss_h->value();
    cfg.m_alarm_ss_low= m_spb_ss_l->value();
    cfg.m_alarm_sz_high= m_spb_sz_h->value();
    cfg.m_alarm_sz_low= m_spb_sz_l->value();
    cfg.m_alarm_pj_high= m_spb_pj_h->value();
    cfg.m_alarm_pj_low= m_spb_pj_l->value();
    g_EcgModule->f_set_nibp_cfg(cfg);
    close();
}
void CDlgAlmNIBP::do_cancel_clicked()
{
    close();
}
bool CDlgAlmNIBP::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_ss
        ,m_spb_ss_h
        ,m_spb_ss_l
        ,m_cmbb_sz
        ,m_spb_sz_h
        ,m_spb_sz_l
        ,m_cmbb_pj
        ,m_spb_pj_h
        ,m_spb_pj_l
        ,m_btn_ok,
        m_btn_cancel
    };
    int iTotalObj =  11;//11
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
