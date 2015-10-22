#include "dlg_alm_co2.h"
#include "mainform.h"
#define DLG_ALM_CO2_COMBOBOX_NUM 3
#define DLG_ALM_CO2_SPB_NUM 6

CDlgAlmCO2::CDlgAlmCO2(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    QComboBox *cmb[DLG_ALM_CO2_COMBOBOX_NUM];
    cmb[0] = m_cmbb_huxilv;
    cmb[1] =m_cmbb_hu;
    cmb[2] =m_cmbb_xi;
    QSpinBox * spb[DLG_ALM_CO2_SPB_NUM];
    spb[0] = m_spb_huxi_high;
    spb[1] = m_spb_huxi_low;
    spb[2] = m_spb_hu_high;
    spb[3] = m_spb_hu_low;
    spb[4] = m_spb_xi_high;
    spb[5] = m_spb_xi_low;

    //增加选择项
     QStringList items;
     items<<"关"<<"开";

    for(int i=0;i< DLG_ALM_CO2_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        cmb[i]->addItems(items);
        //设置光标顺序
        setTabOrder(cmb[i],spb[i*2]);
        setTabOrder(spb[i*2],spb[i*2+1]);

        if(i == (DLG_ALM_CO2_COMBOBOX_NUM-1))
            break;
        setTabOrder(spb[i*2+1],cmb[i+1]);
    }
     setTabOrder(spb[DLG_ALM_CO2_SPB_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();
    stCO2ModuCfg cfg;
    g_CO2Module->f_get_cfg(&cfg);
     m_cmbb_huxilv->setCurrentIndex(cfg.m_alarm_breathrate_en);
     m_spb_huxi_high->setValue(cfg.m_alarm_breathrate_high);
     m_spb_huxi_low->setValue(cfg.m_alarm_breathrate_low);
     m_cmbb_hu->setCurrentIndex(cfg.m_alarm_humo_en);
     m_spb_hu_high->setValue(cfg.m_alarm_humo_high);
     m_spb_hu_low->setValue(cfg.m_alarm_humo_low);
     m_cmbb_xi->setCurrentIndex(cfg.m_alarm_xiru_en);
     m_spb_xi_high->setValue(cfg.m_alarm_xiru_high);
     m_spb_xi_low->setValue(cfg.m_alarm_xiru_low);
     for(int i = 0; i<DLG_ALM_CO2_SPB_NUM;i++)
     {
         spb[i]->installEventFilter(this);
     }
     m_btn_ok->installEventFilter(this);
     m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgAlmCO2::do_ok_clicked()
{
    stCO2ModuCfg cfg;
    g_CO2Module->f_get_cfg(&cfg);
    cfg.m_alarm_breathrate_en = m_cmbb_huxilv->currentIndex();
    cfg.m_alarm_breathrate_high = m_spb_huxi_high->value();
    cfg.m_alarm_breathrate_low = m_spb_huxi_low->value();
    cfg.m_alarm_humo_en = m_cmbb_hu->currentIndex();
    cfg.m_alarm_humo_high = m_spb_hu_high->value();
    cfg.m_alarm_humo_low = m_spb_hu_low->value();
    cfg.m_alarm_xiru_en = m_cmbb_xi->currentIndex();
    cfg.m_alarm_xiru_high = m_spb_xi_high->value();
    cfg.m_alarm_xiru_low = m_spb_xi_low->value();
    g_CO2Module->f_set_cfg(cfg);
    close();
}
void CDlgAlmCO2::do_cancel_clicked()
{
    close();
}
bool CDlgAlmCO2::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
         m_cmbb_huxilv
        ,m_spb_huxi_high
        ,m_spb_huxi_low
        ,m_cmbb_hu
        ,m_spb_hu_high
        ,m_spb_hu_low
        ,m_cmbb_xi
        ,m_spb_xi_high
        ,m_spb_xi_low
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
                        (iCursor == 5)||
                        (iCursor == 2)||
                        (iCursor == 4)||
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
                        (iCursor == 5)||
                        (iCursor == 2)||
                        (iCursor == 4)||
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
                          (iCursor == 5)||
                          (iCursor == 2)||
                          (iCursor == 4)||
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
