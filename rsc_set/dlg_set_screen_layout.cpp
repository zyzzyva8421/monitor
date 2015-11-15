#include "dlg_set_screen_layout.h"
#include "mainform.h"
#include "rsc_modu/modu_ecg.h"
#include "rsc_modu/layout.h"

CDlgSetScreenLayout::CDlgSetScreenLayout(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    QComboBox *cmb[DLG_SET_LAYOUT_COMBOBOX_NUM];
    cmb[0] = m_cmbb_layout;
    cmb[1] =m_cmbb_qushishijian;

    ckb[0] = m_ckb_xinlv;
    ckb[1] = m_ckb_xueyang;
    ckb[2] = m_ckb_huxilv;
    ckb[3] = m_ckb_tiwen;
    ckb[4] = m_ckb_nibp;
    ckb[5] = m_ckb_mshen;
    ckb[6] = m_ckb_ibp1;
    ckb[7] = m_ckb_ibp2;
    ckb[8] = m_ckb_co2;
    ckb[9] = m_ckb_wav_eeg;
    ckb[10] = m_ckb_wav_ecg1;
    ckb[11] = m_ckb_wav_ecg2;
    ckb[12] = m_ckb_wav_ecg3;
    ckb[13] = m_ckb_wav_ecg4;
    ckb[14] = m_ckb_wav_ecg5;
    ckb[15] = m_ckb_wav_ecg6;
    ckb[16] = m_ckb_wav_ecg7;
    ckb[17] = m_ckb_wav_maibo;
    ckb[18] = m_ckb_wav_huxi;
    ckb[19] = m_ckb_wav_ibp1;
    ckb[20] = m_ckb_wav_ibp2;
    ckb[21] = m_ckb_wav_co2;
    ckb[22] = m_ckb_wav_mashen;

    //增加选择项
     QStringList items;
     items<<"标准"<<"大字体"<<"呼吸氧合图"<<"无创血压回顾"<<"趋势表"
            <<"ECG全导联"<<"麻醉深度";
    cmb[0]->addItems(items);
    items.clear();
    items<<"1分钟"<<"3分钟"<<"5分钟"<<"7分钟"<<"10分钟"
           <<"15分钟"<<"20分钟"<<"30分钟"<<"40分钟"<<"50分钟"
             <<"60分钟";
      cmb[1]->addItems(items);

    for(int i=0;i< DLG_SET_LAYOUT_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_LAYOUT_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    setTabOrder(cmb[DLG_SET_LAYOUT_COMBOBOX_NUM-1],m_spb_mashen_fenbianlv);
    setTabOrder(m_spb_mashen_fenbianlv,ckb[0]);
    for(int i=0; i<DLG_SET_LAYOUT_CKB_NUM;i++)
    {
        ckb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_LAYOUT_CKB_NUM-1))
            break;
        setTabOrder(ckb[i],ckb[i+1]);
    }
     setTabOrder(ckb[DLG_SET_LAYOUT_CKB_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
     cmb[0]->setFocus();

    g_EcgModule->f_get_ecg_cfg(&m_ecg_cfg);
    g_EcgModule->f_get_nibp_cfg(&m_nibp_cfg);
    g_EcgModule->f_get_spire_cfg(&m_spire_cfg);
    g_EcgModule->f_get_spo2_cfg(&m_spo2_cfg);
    g_EcgModule->f_get_temp_cfg(&m_temp_cfg);
    g_EegModule->f_get_eeg_cfg(&m_eeg_cfg);
    g_CO2Module->f_get_cfg(&m_co2_cfg);
    g_IBPModule1->f_get_cfg(&m_ibp_cfg);
    g_AnaesModule->f_get_cfg(&m_anaes_cfg);

    CLayoutCfg cfg;
    g_LayoutModule->f_layout_get_config(&cfg);
    m_cmbb_layout->setCurrentIndex(cfg.m_layout_type);
    switch(cfg.m_layout_type)
    {
    case 0:
        f_set_stand_layout();
        break;
    case 1:
        f_set_bigfont_layout();
        break;
    case 2:
        f_set_spirspo_layout();
        break;
    case 3:
        f_set_nibpreview_layout();
        break;
    case 4:
        f_set_trendtable_layout();
        break;
    case 5:
        f_set_ecg_all_lead();
        break;
    case 6:
        f_set_mashen_layout();
        break;
    default:
        break;
    }
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);

     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
     connect(m_cmbb_layout,SIGNAL(currentIndexChanged(int)),this,SLOT(do_layout_reset(int)));
}
//确定更改
void CDlgSetScreenLayout::do_ok_clicked()
{
    bool bSetLayout = false;

    { //心率参数
        bool bChangeFlg = false;
        if((Qt::Checked == m_ckb_xinlv->checkState())
                &&(m_ecg_cfg.m_ecg_para_enable == false))
        {
            m_ecg_cfg.m_ecg_para_enable = true;
            bChangeFlg = true;
        }
        else if((Qt::Unchecked == m_ckb_xinlv->checkState())
                &&(m_ecg_cfg.m_ecg_para_enable == true))
        {
            m_ecg_cfg.m_ecg_para_enable = false;
             bChangeFlg = true;
        }
        //ECG波形
        for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
        {
            if((Qt::Checked == ckb[i+10]->checkState())
                    && (m_ecg_cfg.m_wave_plot_enable[i] == false))
            {
                m_ecg_cfg.m_wave_plot_enable[i] = true;
                bChangeFlg = true;
            }
            else if((Qt::Unchecked == ckb[i+10]->checkState())
                    && (m_ecg_cfg.m_wave_plot_enable[i] == true))
            {
                m_ecg_cfg.m_wave_plot_enable[i] = false;
                bChangeFlg = true;
            }

        }
        if(bChangeFlg == true)
        {
            g_EcgModule->f_set_ecg_cfg(m_ecg_cfg);
            bSetLayout = bChangeFlg;
        }

    }
    //血氧参数
    {
        bool bChangeFlg = false;

        if((Qt::Checked == m_ckb_xueyang->checkState())
                &&(m_spo2_cfg.m_spo2_para_enable == false))
        {
            m_spo2_cfg.m_spo2_para_enable = true;
            bChangeFlg = true;

        }
        else if ((Qt::Unchecked == m_ckb_xueyang->checkState())&&(m_spo2_cfg.m_spo2_para_enable == true))
        {
            m_spo2_cfg.m_spo2_para_enable = false;
            bChangeFlg = true;

        }

        if((Qt::Checked == m_ckb_wav_maibo->checkState())
                &&(m_spo2_cfg.m_wave_enable == false))
        {
            m_spo2_cfg.m_wave_enable = true;
            bChangeFlg = true;

        }
        else if ((Qt::Unchecked == m_ckb_wav_maibo->checkState())
                 &&(m_spo2_cfg.m_wave_enable == true))
        {
            m_spo2_cfg.m_wave_enable = false;
            bChangeFlg = true;

        }
        if(bChangeFlg == true)
        {
           g_EcgModule->f_set_spo2_cfg(m_spo2_cfg);
           bSetLayout = bChangeFlg;
        }

    }
    //呼吸率参数
    {
        bool bChangeFlg = false;

        if((Qt::Checked == m_ckb_huxilv->checkState())
                &&(m_spire_cfg.m_spire_para_enable == false))
        {
            m_spire_cfg.m_spire_para_enable = true;
            bChangeFlg = true;

        }
        else if ((Qt::Unchecked == m_ckb_huxilv->checkState())
                 &&(m_spire_cfg.m_spire_para_enable == true))
        {
            m_spire_cfg.m_spire_para_enable = false;
            bChangeFlg = true;

        }
        if(bChangeFlg == true)
        {
            g_EcgModule->f_set_spire_cfg(m_spire_cfg);
            bSetLayout = bChangeFlg;
        }
    }
    //体温参数
    {
        bool bChangeFlg = false;

        if((Qt::Checked == m_ckb_tiwen->checkState())
                &&(m_temp_cfg.m_temp_para_enable == false))
        {
            m_temp_cfg.m_temp_para_enable = true;
            bChangeFlg = true;

        }
        else if ((Qt::Unchecked == m_ckb_tiwen->checkState())
                 &&(m_temp_cfg.m_temp_para_enable == true))
        {
            m_temp_cfg.m_temp_para_enable = false;
            bChangeFlg = true;

        }
        if(bChangeFlg == true)
        {
           g_EcgModule->f_set_temp_cfg(m_temp_cfg);
           bSetLayout = bChangeFlg;
        }
    }
    //NIBP参数
    {
        bool bChangeFlg = false;

        if((Qt::Checked == m_ckb_nibp->checkState())
                &&(m_nibp_cfg.m_nibp_para_enable == false))
        {
            m_nibp_cfg.m_nibp_para_enable = true;
            bChangeFlg = true;

        }
        else if ((Qt::Unchecked == m_ckb_nibp->checkState())
                 &&(m_nibp_cfg.m_nibp_para_enable == true))
        {
            m_nibp_cfg.m_nibp_para_enable = false;
            bChangeFlg = true;

        }
        if(bChangeFlg == true)
        {
            g_EcgModule->f_set_nibp_cfg(m_nibp_cfg);
            bSetLayout = bChangeFlg;
        }
    }
    //eeg波形参数
    {
        bool bChangeFlg = false;

        if((Qt::Checked == m_ckb_wav_eeg->checkState())
                &&(m_eeg_cfg.m_wave_plot_enable[0] == false))
        {
            for(int i=0;i<EEG_MODULE_WAVE_NUM;i++)
            {
                m_eeg_cfg.m_wave_plot_enable[i] = true;
            }

            bChangeFlg = true;

        }
        else if ((Qt::Unchecked == m_ckb_wav_eeg->checkState())
                 &&(m_eeg_cfg.m_wave_plot_enable[0] == true))
        {
            for(int i=0;i<EEG_MODULE_WAVE_NUM;i++)
            {
                m_eeg_cfg.m_wave_plot_enable[i] = false;
            }
            bChangeFlg = true;
        }
        if(bChangeFlg == true)
        {
            g_EegModule->f_set_eeg_cfg(m_eeg_cfg);
            bSetLayout = bChangeFlg;
        }
    }
    { //ibp波形
        bool bChangeFlg = false;
        //panel
        if((Qt::Checked == m_ckb_ibp1->checkState())
                &&(m_ibp_cfg.m_ibp1_panel_enable == false))
        {
            m_ibp_cfg.m_ibp1_panel_enable = true;
            bChangeFlg = true;
        }
        else if ((Qt::Unchecked == m_ckb_ibp1->checkState())
                 &&(m_ibp_cfg.m_ibp1_panel_enable == true))
        {
            m_ibp_cfg.m_ibp1_panel_enable = false;
            bChangeFlg = true;
        }
        if((Qt::Checked == m_ckb_ibp2->checkState())
                &&(m_ibp_cfg.m_ibp2_panel_enable == false))
        {
            m_ibp_cfg.m_ibp2_panel_enable = true;
            bChangeFlg = true;
        }
        else if ((Qt::Unchecked == m_ckb_ibp2->checkState())
                 &&(m_ibp_cfg.m_ibp2_panel_enable == true))
        {
            m_ibp_cfg.m_ibp2_panel_enable = false;
            bChangeFlg = true;
        }
        //wave
        if((Qt::Checked == m_ckb_wav_ibp1->checkState())
                &&(m_ibp_cfg.m_ibp1_wave_enable == false))
        {
            m_ibp_cfg.m_ibp1_wave_enable = true;
            bChangeFlg = true;
        }
        else if ((Qt::Unchecked == m_ckb_wav_ibp1->checkState())
                 &&(m_ibp_cfg.m_ibp1_wave_enable == true))
        {
            m_ibp_cfg.m_ibp1_wave_enable = false;
            bChangeFlg = true;
        }
        if((Qt::Checked == m_ckb_wav_ibp2->checkState())
                &&(m_ibp_cfg.m_ibp2_wave_enable == false))
        {
            m_ibp_cfg.m_ibp2_wave_enable = true;
            bChangeFlg = true;
        }
        else if ((Qt::Unchecked == m_ckb_wav_ibp2->checkState())
                 &&(m_ibp_cfg.m_ibp2_wave_enable == true))
        {
            m_ibp_cfg.m_ibp2_wave_enable = false;
            bChangeFlg = true;
        }
        if(bChangeFlg == true)
        {
            g_IBPModule1->f_set_cfg(m_ibp_cfg);
            bSetLayout = bChangeFlg;
        }

    }
    //麻深参数
    {
        bool bChangeFlg = false;

        if((Qt::Checked == m_ckb_wav_mashen->checkState())
                &&(m_anaes_cfg.m_wave_enable == false))
        {
            m_anaes_cfg.m_wave_enable = true;
            bChangeFlg = true;

        }
        else if ((Qt::Unchecked == m_ckb_wav_mashen->checkState())
                 &&(m_anaes_cfg.m_wave_enable == true))
        {
            m_anaes_cfg.m_wave_enable = false;
            bChangeFlg = true;
        }
        if((Qt::Checked == m_ckb_mshen->checkState())
                &&(m_anaes_cfg.m_para_enable == false))
        {
            m_anaes_cfg.m_para_enable = true;
            bChangeFlg = true;

        }
        else if ((Qt::Unchecked == m_ckb_mshen->checkState())
                 &&(m_anaes_cfg.m_para_enable == true))
        {
            m_anaes_cfg.m_para_enable = false;
            bChangeFlg = true;
        }
        if(bChangeFlg == true)
        {
            g_AnaesModule ->f_set_cfg(m_anaes_cfg);
            bSetLayout = bChangeFlg;
        }
    }
    {//co2
        bool bChangeFlg = false;

        if((Qt::Checked == m_ckb_co2->checkState())
                &&(m_co2_cfg.m_para_enable == false))
        {
            m_co2_cfg.m_para_enable = true;
            bChangeFlg = true;

        }
        else if ((Qt::Unchecked == m_ckb_co2->checkState())&&(m_co2_cfg.m_para_enable == true))
        {
            m_co2_cfg.m_para_enable = false;
            bChangeFlg = true;

        }

        if((Qt::Checked == m_ckb_wav_co2->checkState())
                &&(m_co2_cfg.m_wave_enable == false))
        {
            m_co2_cfg.m_wave_enable = true;
            bChangeFlg = true;

        }
        else if ((Qt::Unchecked == m_ckb_wav_co2->checkState())
                 &&(m_co2_cfg.m_wave_enable == true))
        {
            m_co2_cfg.m_wave_enable = false;
            bChangeFlg = true;

        }
        if(bChangeFlg == true)
        {
            g_CO2Module->f_set_cfg(m_co2_cfg);
            bSetLayout = bChangeFlg;
        }

    }
    CLayoutCfg cfg;
    g_LayoutModule->f_layout_get_config(&cfg);
    cfg.m_layout_type = m_cmbb_layout->currentIndex();
    cfg.m_layout_trend_interval = m_cmbb_qushishijian->currentIndex();
    cfg.m_layout_mashen_sens = m_spb_mashen_fenbianlv->value();
    g_LayoutModule->f_layout_set_config(cfg);

    close();
}
void CDlgSetScreenLayout::do_cancel_clicked()
{
    close();
}
void CDlgSetScreenLayout::do_layout_reset(int idx)
{
    switch(idx)
    {
    case 0:
        f_set_stand_layout();
        break;
    case 1:
        f_set_bigfont_layout();
        break;
    case 2:
        f_set_spirspo_layout();
        break;
    case 3:
        f_set_nibpreview_layout();
        break;
    case 4:
        f_set_trendtable_layout();
        break;
    case 5:
        f_set_ecg_all_lead();
        break;
    case 6:
        f_set_mashen_layout();
        break;
    default:
        break;
    }
}

//设置标准屏幕配置
void CDlgSetScreenLayout::f_set_stand_layout()
{
    for(int i=0;i<DLG_SET_LAYOUT_CKB_NUM;i++)
    {
        ckb[i]->setEnabled(true);
    }

    m_ckb_xinlv->setChecked(m_ecg_cfg.m_ecg_para_enable);
    m_ckb_xueyang->setChecked(m_spo2_cfg.m_spo2_para_enable);
    m_ckb_huxilv->setChecked(m_spire_cfg.m_spire_para_enable);
    m_ckb_tiwen->setChecked(m_temp_cfg.m_temp_para_enable);
    m_ckb_nibp->setChecked(m_nibp_cfg.m_nibp_para_enable);
    m_ckb_mshen->setChecked(m_anaes_cfg.m_para_enable);
    m_ckb_ibp1->setChecked(m_ibp_cfg.m_ibp1_panel_enable);
    m_ckb_ibp2->setChecked(m_ibp_cfg.m_ibp1_panel_enable);
    m_ckb_co2->setChecked(m_co2_cfg.m_para_enable);
    m_ckb_wav_eeg->setChecked(m_eeg_cfg.m_wave_plot_enable[0]);
    m_ckb_wav_ecg1->setChecked(m_ecg_cfg.m_wave_plot_enable[0]);
    m_ckb_wav_ecg2->setChecked(m_ecg_cfg.m_wave_plot_enable[1]);
    m_ckb_wav_ecg3->setChecked(m_ecg_cfg.m_wave_plot_enable[2]);
    m_ckb_wav_ecg4->setChecked(m_ecg_cfg.m_wave_plot_enable[3]);
    m_ckb_wav_ecg5->setChecked(m_ecg_cfg.m_wave_plot_enable[4]);
    m_ckb_wav_ecg6->setChecked(m_ecg_cfg.m_wave_plot_enable[5]);
    m_ckb_wav_ecg7->setChecked(m_ecg_cfg.m_wave_plot_enable[6]);
    m_ckb_wav_maibo->setChecked(m_spo2_cfg.m_wave_enable);
    m_ckb_wav_huxi->setChecked(m_spire_cfg.m_wave_enable);
    m_ckb_wav_ibp1->setChecked(m_ibp_cfg.m_ibp1_wave_enable);
    m_ckb_wav_ibp2->setChecked(m_ibp_cfg.m_ibp2_wave_enable);
    m_ckb_wav_co2->setChecked(m_co2_cfg.m_wave_enable);
    m_ckb_wav_mashen->setChecked(m_anaes_cfg.m_wave_enable);
    //波形部分
    ckb[19]->setCheckState(Qt::Unchecked);
    ckb[19]->setEnabled(false);
    ckb[20]->setCheckState(Qt::Unchecked);
    ckb[20]->setEnabled(false);
    ckb[22]->setCheckState(Qt::Unchecked);
    ckb[22]->setEnabled(false);
        //心电波形

    for(int i=13;i<17;i++)
    {
        ckb[i]->setCheckState(Qt::Unchecked);
        ckb[i]->setEnabled(false);
    }
}
void CDlgSetScreenLayout::f_set_bigfont_layout()
{
    for(int i=0;i<DLG_SET_LAYOUT_CKB_NUM;i++)
    {
        ckb[i]->setEnabled(true);
    }

    m_ckb_xinlv->setChecked(m_ecg_cfg.m_ecg_para_enable);
    m_ckb_xueyang->setChecked(m_spo2_cfg.m_spo2_para_enable);
    m_ckb_huxilv->setChecked(m_spire_cfg.m_spire_para_enable);
    m_ckb_tiwen->setChecked(m_temp_cfg.m_temp_para_enable);
    m_ckb_nibp->setChecked(m_nibp_cfg.m_nibp_para_enable);
    m_ckb_mshen->setChecked(m_anaes_cfg.m_para_enable);
    m_ckb_ibp1->setChecked(m_ibp_cfg.m_ibp1_panel_enable);
    m_ckb_ibp2->setChecked(m_ibp_cfg.m_ibp1_panel_enable);
    m_ckb_co2->setChecked(m_co2_cfg.m_para_enable);
    m_ckb_wav_eeg->setChecked(m_eeg_cfg.m_wave_plot_enable[0]);
    m_ckb_wav_ecg1->setChecked(m_ecg_cfg.m_wave_plot_enable[0]);
    m_ckb_wav_ecg2->setChecked(m_ecg_cfg.m_wave_plot_enable[1]);
    m_ckb_wav_ecg3->setChecked(m_ecg_cfg.m_wave_plot_enable[2]);
    m_ckb_wav_ecg4->setChecked(m_ecg_cfg.m_wave_plot_enable[3]);
    m_ckb_wav_ecg5->setChecked(m_ecg_cfg.m_wave_plot_enable[4]);
    m_ckb_wav_ecg6->setChecked(m_ecg_cfg.m_wave_plot_enable[5]);
    m_ckb_wav_ecg7->setChecked(m_ecg_cfg.m_wave_plot_enable[6]);
    m_ckb_wav_maibo->setChecked(m_spo2_cfg.m_wave_enable);
    m_ckb_wav_huxi->setChecked(m_spire_cfg.m_wave_enable);
    m_ckb_wav_ibp1->setChecked(m_ibp_cfg.m_ibp1_wave_enable);
    m_ckb_wav_ibp2->setChecked(m_ibp_cfg.m_ibp2_wave_enable);
    m_ckb_wav_co2->setChecked(m_co2_cfg.m_wave_enable);
    m_ckb_wav_mashen->setChecked(m_anaes_cfg.m_wave_enable);
    //波形部分
    ckb[19]->setCheckState(Qt::Unchecked);
    ckb[19]->setEnabled(false);
    ckb[20]->setCheckState(Qt::Unchecked);
    ckb[20]->setEnabled(false);
    ckb[22]->setCheckState(Qt::Unchecked);
    ckb[22]->setEnabled(false);
        //心电波形

    for(int i=13;i<17;i++)
    {
        ckb[i]->setCheckState(Qt::Unchecked);
        ckb[i]->setEnabled(false);
    }
}
void CDlgSetScreenLayout::f_set_spirspo_layout()
{
    for(int i=0;i<DLG_SET_LAYOUT_CKB_NUM;i++)
    {
        ckb[i]->setEnabled(true);
    }
}
void CDlgSetScreenLayout::f_set_nibpreview_layout()
{
    for(int i=0;i<DLG_SET_LAYOUT_CKB_NUM;i++)
    {
        ckb[i]->setEnabled(true);
    }
}
void CDlgSetScreenLayout::f_set_trendtable_layout()
{
    for(int i=0;i<DLG_SET_LAYOUT_CKB_NUM;i++)
    {
        ckb[i]->setEnabled(true);
    }
}
void CDlgSetScreenLayout::f_set_mashen_layout()
{
    for(int i=0;i<DLG_SET_LAYOUT_CKB_NUM;i++)
    {
        ckb[i]->setEnabled(true);
    }
}
void CDlgSetScreenLayout::f_set_ecg_all_lead()
{
    for(int i=0;i<DLG_SET_LAYOUT_CKB_NUM;i++)
    {
        ckb[i]->setEnabled(true);
    }
}
void CDlgSetScreenLayout::f_get_panel_beatrate()
{
    //心率参数
    CEcgModuleCfg cfg;
    g_EcgModule->f_get_ecg_cfg(&cfg);

    if((cfg.m_ecg_para_enable == false))
    {
        ckb[0]->setChecked(false);
    }
    else
    {
        ckb[0]->setChecked(true);
    }
}

void CDlgSetScreenLayout::f_get_panel_spo2()
{
    //血氧参数
    CSpo2ModuleCfg cfg;
    g_EcgModule->f_get_spo2_cfg(&cfg);
    ckb[1]->setChecked(cfg.m_spo2_para_enable);

}

void CDlgSetScreenLayout::f_get_panel_breathrate()
{
    CSpireModuleCfg cfg;
    g_EcgModule->f_get_spire_cfg(&cfg);
    ckb[2]->setChecked(cfg.m_spire_para_enable);
}

void CDlgSetScreenLayout::f_get_panel_nibp()
{
    CNibpModuleCfg cfg;
    g_EcgModule->f_get_nibp_cfg(&cfg);
    ckb[4]->setChecked(cfg.m_nibp_para_enable);
}

void CDlgSetScreenLayout::f_get_panel_temp()
{
    CTempModuleCfg cfg;
    g_EcgModule->f_get_temp_cfg(&cfg);
    ckb[3]->setChecked(cfg.m_temp_para_enable);
}

void CDlgSetScreenLayout::f_get_panel_co2()
{
    stCO2ModuCfg cfg;
    g_CO2Module->f_get_cfg(&cfg);
    ckb[8]->setChecked(cfg.m_para_enable);
}
void CDlgSetScreenLayout::f_get_panel_anaes()
{
    stAnaesDepModuCfg cfg;
    g_AnaesModule->f_get_cfg(&cfg);
    ckb[5]->setChecked(cfg.m_para_enable);
}

void CDlgSetScreenLayout::f_get_panel_ibp()
{
    stIBPModuCfg cfg;
    g_IBPModule1->f_get_cfg(&cfg);
    ckb[6]->setChecked(cfg.m_ibp1_panel_enable);
    ckb[7]->setChecked(cfg.m_ibp2_panel_enable);
}
void  CDlgSetScreenLayout::f_get_wave_eeg()
{
    CEegModuleCfg cfg;
    g_EegModule->f_get_eeg_cfg(&cfg);
    ckb[9]->setChecked(cfg.m_wave_plot_enable[0]);
}
void  CDlgSetScreenLayout::f_get_wave_ecg()
{
    for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
    {
        CEcgModuleCfg cfg;
        g_EcgModule->f_get_ecg_cfg(&cfg);

        if(cfg.m_wave_plot_enable[i])
        {
            ckb[10+i]->setCheckState(Qt::Checked);
        }
        else
        {
            ckb[10+i]->setCheckState(Qt::Unchecked);
        }
    }
}
void  CDlgSetScreenLayout::f_get_wave_spo2()
{

}
void  CDlgSetScreenLayout::f_get_wave_spire()
{

}
void  CDlgSetScreenLayout::f_get_wave_co2()
{

}
void  CDlgSetScreenLayout::f_get_wave_anaes()
{

}
void  CDlgSetScreenLayout::f_get_wave_ibp()
{

}
bool CDlgSetScreenLayout::eventFilter(QObject *o,QEvent *e)
{

    QObject *obj[]={
    m_cmbb_layout
    ,m_cmbb_qushishijian

    ,m_ckb_xinlv
    ,m_ckb_xueyang
    ,m_ckb_huxilv
    ,m_ckb_tiwen
    ,m_ckb_nibp
    ,m_ckb_mshen
    ,m_ckb_ibp1
    ,m_ckb_ibp2
    ,m_ckb_co2
    ,m_ckb_wav_eeg
    , m_ckb_wav_ecg1
    , m_ckb_wav_ecg2
    ,m_ckb_wav_ecg3
    ,m_ckb_wav_ecg4
    , m_ckb_wav_ecg5
    ,m_ckb_wav_ecg6
    ,m_ckb_wav_ecg7
    ,m_ckb_wav_maibo
    ,m_ckb_wav_huxi
    ,m_ckb_wav_ibp1
    ,m_ckb_wav_ibp2
    ,m_ckb_wav_co2
    ,m_ckb_wav_mashen

    ,m_btn_ok
    ,m_btn_cancel
    };
    int iTotalObj =  27;//11
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
                if((iCursor>=2) &&(iCursor<iOkPos))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setStyleSheet("background-color: rgb(255, 255, 255,255);");
                }
                if(iCursor == 0)
                {
                    iCursor = iTotalObj-1;
                }
                else
                {
                    iCursor -=1;
                }
                if((iCursor>=0) &&(iCursor<2))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setFocus();
                }
                else if((iCursor>=2) &&(iCursor<iOkPos))
                {
                    QCheckBox *p = (QCheckBox *)obj[iCursor];
                    int i = 0;
                    for( i = iCursor;i>=2;i--)
                    {
                        if(p->isEnabled())
                        {
                            p->setFocus();
                            p->setStyleSheet("background-color: rgb(163, 229, 234);"
                                             "border-color:rgb(12,23,234);"
                                             "border-color:5 px;");
                            break;
                        }
                        else
                        {
                            iCursor--;
                            p->setStyleSheet("background-color: rgb(255, 255, 255,255);");
                            p = (QCheckBox *)obj[iCursor];
                        }
                    }
                    if(i == 1)
                    {
                        m_cmbb_qushishijian->setFocus();
                    }
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

                if((iCursor>=2) &&(iCursor<iOkPos))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setStyleSheet("background-color: rgb(255, 255, 255,255);");
                }
                if(iCursor == iTotalObj-1)
                {
                    iCursor = 0;
                }
                else
                {
                    iCursor +=1;
                }
                if((iCursor>=0) &&(iCursor<2))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setFocus();
                }
                else if((iCursor>=2) &&(iCursor<iOkPos))
                {
                    QCheckBox *p = (QCheckBox *)obj[iCursor];
                    int i = 0;
                    for( i = iCursor;i<iOkPos -1;i++)
                    {
                        if(p->isEnabled())
                        {
                            p->setFocus();
                            p->setStyleSheet("background-color: rgb(163, 229, 234);");
                            break;
                        }
                        else
                        {
                            iCursor++;
                            p->setStyleSheet("background-color: rgb(255, 255, 255,255);");
                            p = (QCheckBox *)obj[iCursor];
                        }
                    }
                    if(i == iOkPos)
                    {
                        m_btn_ok->setFocus();
                    }

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
                else if((iCursor>=0) &&(iCursor<2))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(163, 229, 234);");
                }
                else
                {
                    bCursorSta = false;
                    QCheckBox *p = (QCheckBox *)obj[iCursor];
                    p->setChecked(!p->checkState());
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
