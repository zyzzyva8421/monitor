#include <QEvent>
#include "dlg_set_ecg.h"
#include "../mainform.h"
#define DLG_SET_ECG_COMBOBOX_NUM 13


CDlgSetECG::CDlgSetECG(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    QComboBox *cmb[DLG_SET_ECG_COMBOBOX_NUM];
    cmb[0] = m_cmbb_chnl1_daolian;
    cmb[1] =m_cmbb_chnl2_daolian;
    cmb[2] =m_cmbb_chnl3_daolian;
    cmb[3] =m_cmbb_amp;
    cmb[4] =m_cmbb_gongpinyizhi;
    cmb[5] =m_cmbb_daolianleixing;
    cmb[6] =m_cmbb_qiboqi;
    cmb[7] =m_cmbb_lvbomoshi;
    cmb[8] =m_cmbb_xintiaoyinliang;
    cmb[9] =m_cmbb_xinlvlaiyuan;
    cmb[10] =m_cmbb_boxingsudu;
    cmb[11] =m_cmbb_st;
    cmb[12] =m_cmbb_xinlvshichang;

    //增加选择项
     QStringList items;
     items.clear();
     items<<"I"<<"II"<<"III";
     cmb[0]->addItems(items);
     cmb[1]->addItems(items);
     cmb[2]->addItems(items);
     items.clear();
     items<<"x0.25"<<"x0.5"<<"x1"<<"x2";
     cmb[3]->addItems(items);
     items.clear();
      items<<"关"<<"开";
     cmb[4]->addItems(items);
     cmb[6]->addItems(items);
     cmb[11] ->addItems(items);
     cmb[12] ->addItems(items);
     items.clear();
      items<<"5导联"<<"3导联";
     cmb[5]->addItems(items);
     items.clear();
      items<<"诊断"<<"监护"<<"术中";
     cmb[7]->addItems(items);
     items.clear();
      items<<"0"<<"1"<<"2"<<"3";
     cmb[8]->addItems(items);
     items.clear();
      items<<"心电"<<"血氧"<<"自动";
     cmb[9]->addItems(items);
     items.clear();
      items<<"12.5mm/s"<<"25mm/s"<<"50mm/s";
     cmb[10]->addItems(items);

    for(int i=0;i< DLG_SET_ECG_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_ECG_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    setTabOrder(cmb[DLG_SET_ECG_COMBOBOX_NUM-1],m_btn_ok);
    setTabOrder(m_btn_ok,m_btn_cancel);
    setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();

    CEcgModuleCfg cfg;
    g_EcgModule->f_get_ecg_cfg(&cfg);

     m_cmbb_chnl1_daolian->setCurrentIndex(cfg.m_ecg_chanel1_lead);
     m_cmbb_chnl2_daolian->setCurrentIndex(cfg.m_ecg_chanel2_lead);
     m_cmbb_chnl3_daolian->setCurrentIndex(cfg.m_ecg_chanel3_lead);
     m_cmbb_amp->setCurrentIndex(cfg.m_ecg_amp);
     m_cmbb_gongpinyizhi->setCurrentIndex(cfg.m_ect_pwr_supression_enable);
     m_cmbb_daolianleixing->setCurrentIndex(cfg.m_ecg_lead_style);
     m_cmbb_qiboqi->setCurrentIndex(cfg.m_ecg_pacemaker_enable);
     m_cmbb_lvbomoshi->setCurrentIndex(cfg.m_ecg_filter_mod);
     m_cmbb_xintiaoyinliang->setCurrentIndex(cfg.m_ecg_pulse_vol);
     m_cmbb_xinlvlaiyuan->setCurrentIndex(cfg.m_ecg_beatrate_src);
     m_cmbb_boxingsudu->setCurrentIndex(cfg.m_ecg_wave_speed);
     m_cmbb_st->setCurrentIndex(cfg.m_ecg_st_enable);
     m_cmbb_xinlvshichang->setCurrentIndex(cfg.m_ecg_pvcs_enbale);
 /*
    m_cmbb_chnl1_daolian->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_chanel1_lead);
    m_cmbb_chnl2_daolian->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_chanel2_lead);
    m_cmbb_chnl3_daolian->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_chanel3_lead);
    m_cmbb_amp->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_amp);
    m_cmbb_gongpinyizhi->setCurrentIndex(g_EcgModule->m_module_cfg->m_ect_pwr_supression_enable);
    m_cmbb_daolianleixing->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_lead_style);
    m_cmbb_qiboqi->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_pacemaker_enable);
    m_cmbb_lvbomoshi->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_filter_mod);
    m_cmbb_xintiaoyinliang->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_pulse_vol);
    m_cmbb_xinlvlaiyuan->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_beatrate_src);
    m_cmbb_boxingsudu->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_wave_speed);
    m_cmbb_st->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_st_enable);
    m_cmbb_xinlvshichang->setCurrentIndex(g_EcgModule->m_module_cfg->m_ecg_pvcs_enbale);
*/
     m_btn_ok->installEventFilter(this);
     m_btn_cancel->installEventFilter(this);
    connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
    connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
    connect(m_cmbb_chnl1_daolian,SIGNAL(currentIndexChanged(int)),this,SLOT(do_ch1_changed(int)));
    connect(m_cmbb_chnl2_daolian,SIGNAL(currentIndexChanged(int)),this,SLOT(do_ch2_changed(int)));
    connect(m_cmbb_chnl3_daolian,SIGNAL(currentIndexChanged(int)),this,SLOT(do_ch3_changed(int)));

}
void CDlgSetECG::do_ch1_changed(int val)
{
    int temp1 = m_cmbb_chnl2_daolian->currentIndex();
    int temp2 = m_cmbb_chnl3_daolian->currentIndex();
    int temp = 0;
    for(int i = 0;i<3;i++)
    {
        if((i != temp1) &&(i!=temp2))
        {
            temp = i;
            break;
        }
    }
    if(val == temp1)
    {
        m_cmbb_chnl2_daolian->setCurrentIndex(temp);
    }
    else if(val == temp2)
    {
        m_cmbb_chnl3_daolian->setCurrentIndex(temp);
    }
}

void CDlgSetECG::do_ch2_changed(int val)
{
    int temp1 = m_cmbb_chnl1_daolian->currentIndex();
    int temp2 = m_cmbb_chnl3_daolian->currentIndex();
    int temp = 0;
    for(int i = 0;i<3;i++)
    {
        if((i != temp1) &&(i!=temp2))
        {
            temp = i;
            break;
        }
    }
    if(val == temp1)
    {
        m_cmbb_chnl1_daolian->setCurrentIndex(temp);
    }
    else if(val == temp2)
    {
        m_cmbb_chnl3_daolian->setCurrentIndex(temp);
    }
}

void CDlgSetECG::do_ch3_changed(int val)
{
    int temp1 = m_cmbb_chnl2_daolian->currentIndex();
    int temp2 = m_cmbb_chnl1_daolian->currentIndex();
    int temp = 0;
    for(int i = 0;i<3;i++)
    {
        if((i != temp1) &&(i!=temp2))
        {
            temp = i;
            break;
        }
    }
    if(val == temp1)
    {
        m_cmbb_chnl2_daolian->setCurrentIndex(temp);
    }
    else if(val == temp2)
    {
        m_cmbb_chnl1_daolian->setCurrentIndex(temp);
    }
}

void CDlgSetECG::do_ok_clicked()
{
    CEcgModuleCfg cfg;
    g_EcgModule->f_get_ecg_cfg(&cfg);
    cfg.m_ecg_chanel1_lead = m_cmbb_chnl1_daolian->currentIndex();
    cfg.m_ecg_chanel2_lead = m_cmbb_chnl2_daolian->currentIndex();
    cfg.m_ecg_chanel3_lead = m_cmbb_chnl3_daolian->currentIndex();
    cfg.m_ecg_amp = m_cmbb_amp->currentIndex();
    cfg.m_ect_pwr_supression_enable = m_cmbb_gongpinyizhi->currentIndex();
    cfg.m_ecg_lead_style = m_cmbb_daolianleixing->currentIndex();
    cfg.m_ecg_pacemaker_enable = m_cmbb_qiboqi->currentIndex();
    cfg.m_ecg_filter_mod = m_cmbb_lvbomoshi->currentIndex();
    cfg.m_ecg_pulse_vol = m_cmbb_xintiaoyinliang->currentIndex();
    cfg.m_ecg_beatrate_src = m_cmbb_xinlvlaiyuan->currentIndex();
    cfg.m_ecg_wave_speed = m_cmbb_boxingsudu->currentIndex();
    cfg.m_ecg_st_enable = m_cmbb_st->currentIndex();
    cfg.m_ecg_pvcs_enbale = m_cmbb_xinlvshichang->currentIndex();
    g_EcgModule->f_set_ecg_cfg(cfg);
    close();
}
void CDlgSetECG::do_cancel_clicked()
{
    close();
}

bool CDlgSetECG::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_chnl1_daolian
        ,m_cmbb_chnl2_daolian
        ,m_cmbb_chnl3_daolian
        ,m_cmbb_amp
        ,m_cmbb_gongpinyizhi
        ,m_cmbb_daolianleixing
        ,m_cmbb_qiboqi
        ,m_cmbb_lvbomoshi
        ,m_cmbb_xintiaoyinliang
        ,m_cmbb_xinlvlaiyuan
        ,m_cmbb_boxingsudu
        ,m_cmbb_st
        ,m_cmbb_xinlvshichang
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  15;//11
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
            {/*

                if((iCursor >= 7)&&(iCursor <=10))
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

                }*/
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
            {/*
                if((iCursor >= 7)&&(iCursor <=10))
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

                }*/

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
            {/*
                bCursorSta = false;
                if((iCursor >= 7)&&(iCursor <=10))
                {

                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    //p->setStyleSheet("background-color: rgb(255, 255, 255);");;
                }
                //obj[iCursor]->setStyleSheet("background-color: rgb(255, 255, 255);");
*/
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
