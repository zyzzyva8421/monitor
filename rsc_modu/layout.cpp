#include "layout.h"
#include "modu_ecg.h"
#include "modu_eeg.h"
#include "mainform.h"
CLayoutModule::CLayoutModule(QWidget *parent)
{
    pMainForm = parent;
    m_layout_cfg = new CLayoutCfg;
    f_layout_set_def_config();

    QFile file((LAYOUT_CFG_DOC));
    if(file.open(QIODevice::ReadOnly))
    {
        CLayoutCfg tempCfg;
        QDataStream inout(&file);
        int magic;
        inout >> magic;
        if(magic == 0x12345678)
        {
            inout.readRawData((char *)&tempCfg,sizeof(CLayoutCfg));
        }
        memcpy(m_layout_cfg,&tempCfg,sizeof(CLayoutCfg));
        file.close();
    }
    else
    {
        file.open(QIODevice::WriteOnly);
        QDataStream inout(&file);
        int magic = 0x12345678;
        inout<<magic;
        inout.writeRawData((char *)m_layout_cfg,sizeof(CLayoutCfg));
        file.close();
    }
    f_layout_hint( *m_layout_cfg);
}

void CLayoutModule::f_layout_get_config(CLayoutCfg *cfg)
{
    memcpy(cfg,m_layout_cfg,sizeof(CLayoutCfg));
}

void CLayoutModule::f_layout_set_config(CLayoutCfg cfg)
{
    memcpy(m_layout_cfg,&cfg,sizeof(CLayoutCfg));
    QFile file((LAYOUT_CFG_DOC));
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_layout_cfg,sizeof(CLayoutCfg));
    file.close();
    f_layout_hint( cfg);
}

void CLayoutModule::f_layout_set_def_config()
{
    m_layout_cfg->m_layout_type = LAYOUT_CFG_STANDER;
    m_layout_cfg->m_layout_trend_interval = 1;
    m_layout_cfg->m_layout_mashen_sens = 1;
}
void CLayoutModule::f_layout_hint(CLayoutCfg cfg)
{
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
}
void CLayoutModule::f_set_stand_layout()
{
    int iHLayout = 0;
    int index = 0;
    g_WavePlotter->clearScreen();
    {
        CEegModuleCfg cfg;
        g_EegModule->f_get_eeg_cfg(&cfg);

        for(int i = 0; i<EEG_MODULE_WAVE_NUM;i++)
        {
            if(cfg.m_wave_plot_enable[i] == true)
            {
                cfg.m_wave_rec[i] = QRect(0,iHLayout,WAVE_WIDGET_WIDTH_PIX,WAVE_WIDGET_HEIGHT_PIX);
                iHLayout +=WAVE_WIDGET_HEIGHT_PIX;
                cfg.m_wave_indx[i] = index++;
            }
        }
        g_EegModule->f_set_eeg_cfg(cfg);
        g_EegModule->f_set_eeg_wave_layout();
    }
    {
        CEcgModuleCfg cfg;
        g_EcgModule->f_get_ecg_cfg(&cfg);

        for(int i = 0; i<ECG_MODULE_WAVE_NUM;i++)
        {
            if(i>=3)
            {
                cfg.m_wave_plot_enable[i] = false;
            }
            if(cfg.m_wave_plot_enable[i] == true)
            {
                cfg.m_wave_rec[i] = QRect(0,iHLayout,WAVE_WIDGET_WIDTH_PIX,WAVE_WIDGET_HEIGHT_PIX);
                iHLayout +=WAVE_WIDGET_HEIGHT_PIX;
                cfg.m_wave_indx[i] = index++;
            }
        }
        g_EcgModule->f_set_ecg_cfg(cfg);
        g_EcgModule->f_set_ecg_wave_layout();
    }
    {
        stCO2ModuCfg cfg;
        g_CO2Module->f_get_cfg(&cfg);
        if(cfg.m_wave_enable == true)
        {
            cfg.m_wave_rec = QRect(0,iHLayout,WAVE_WIDGET_WIDTH_PIX,WAVE_WIDGET_HEIGHT_PIX);
            iHLayout +=WAVE_WIDGET_HEIGHT_PIX;
            cfg.m_wave_indx= index++;
            g_CO2Module->f_set_cfg(cfg);
            g_CO2Module->f_set_wave_layout();
        }

    }
    {
        CSpo2ModuleCfg cfg;
        g_EcgModule->f_get_spo2_cfg(&cfg);
        if(cfg.m_wave_enable == true)
        {
            cfg.m_wave_rec = QRect(0,
                                   iHLayout,
                                   WAVE_WIDGET_WIDTH_PIX,
                                   WAVE_WIDGET_HEIGHT_PIX-2);
             iHLayout +=WAVE_WIDGET_HEIGHT_PIX-2;
             cfg.m_wave_indx= index++;
           g_EcgModule->f_set_spo2_cfg(cfg);
           g_EcgModule->f_set_spo2_wave_layout();
        }

    }
    {
        CSpireModuleCfg cfg;
        g_EcgModule->f_get_spire_cfg(&cfg);
        if(cfg.m_wave_enable == true)
        {
            cfg.m_wave_rec = QRect(0,
                                   iHLayout,
                                   WAVE_WIDGET_WIDTH_PIX,
                                   WAVE_WIDGET_HEIGHT_PIX-2);
            iHLayout +=WAVE_WIDGET_HEIGHT_PIX-2;
            cfg.m_wave_indx= index++;
            g_EcgModule->f_set_spire_cfg(cfg);
            g_EcgModule->f_set_spire_wave_layout();
        }
    }

    {
        stIBPModuCfg cfg;
        g_IBPModule1->f_get_cfg(&cfg);
        cfg.m_ibp1_wave_enable = false;
        cfg.m_ibp2_wave_enable = false;
        g_IBPModule1->f_set_cfg(cfg);
        /*
        //if(cfg.m_wave_plot_enable[i] == true)
        {
            cfg.m_ibp1_wave_rec = QRect(0,iHLayout,WAVE_WIDGET_WIDTH_PIX,WAVE_WIDGET_HEIGHT_PIX);
            iHLayout +=WAVE_WIDGET_HEIGHT_PIX;
            cfg.m_ibp2_wave_rec = QRect(0,iHLayout,WAVE_WIDGET_WIDTH_PIX,WAVE_WIDGET_HEIGHT_PIX);
            iHLayout +=WAVE_WIDGET_HEIGHT_PIX;

            g_IBPModule1->f_set_cfg(cfg);
            g_IBPModule1->f_set_wave_layout();
        }*/
    }
    {
        stAnaesDepModuCfg cfg;
        g_AnaesModule->f_get_cfg(&cfg);
        cfg.m_wave_enable = false;
        g_AnaesModule->f_set_cfg(cfg);
    }
}

void CLayoutModule::f_set_bigfont_layout()
{

}

void CLayoutModule::f_set_spirspo_layout()
{

}

void CLayoutModule::f_set_nibpreview_layout()
{

}

void CLayoutModule::f_set_trendtable_layout()
{

}

void CLayoutModule::f_set_mashen_layout()
{

}

void CLayoutModule::f_set_ecg_all_lead()
{

}
