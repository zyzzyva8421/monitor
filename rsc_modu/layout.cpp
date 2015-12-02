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

void CLayoutModule::f_update_wave_num()
{
    g_WaveNumber = 0;
    CEegModuleCfg eeg_cfg;
    g_EegModule->f_get_eeg_cfg(&eeg_cfg);

    for(int i = 0; i<EEG_MODULE_WAVE_NUM;i++)
    {
        if(eeg_cfg.m_wave_plot_enable[i] == true)
        {
            g_WaveNumber++;
        }
    }


    CEcgModuleCfg ecg_cfg;
    g_EcgModule->f_get_ecg_cfg(&ecg_cfg);

    for(int i = 0; i<ECG_MODULE_WAVE_NUM-1;i++)
    {
        if(ecg_cfg.m_wave_plot_enable[i] == true)
        {
            g_WaveNumber++;
        }
    }

    stCO2ModuCfg co2_cfg;
    g_CO2Module->f_get_cfg(&co2_cfg);
    if(co2_cfg.m_wave_enable == true)
    {
        g_WaveNumber++;
    }

    CSpo2ModuleCfg spo2_cfg;
    g_EcgModule->f_get_spo2_cfg(&spo2_cfg);
    if(spo2_cfg.m_wave_enable == true)
    {
        g_WaveNumber++;
    }

    CSpireModuleCfg spire_cfg;
    g_EcgModule->f_get_spire_cfg(&spire_cfg);
    if(spire_cfg.m_wave_enable == true)
    {
        g_WaveNumber++;
    }

    stIBPModuCfg ibp_cfg;
    g_IBPModule1->f_get_cfg(&ibp_cfg);
    if (ibp_cfg.m_ibp1_wave_enable == true) g_WaveNumber++;
    if (ibp_cfg.m_ibp2_wave_enable == true) g_WaveNumber++;

    stAnaesDepModuCfg anaesdep_cfg;
    g_AnaesModule->f_get_cfg(&anaesdep_cfg);
    if (anaesdep_cfg.m_wave_enable == true) g_WaveNumber++;
    if (g_WaveNumber==0) g_WaveNumber=1;
}

bool CLayoutModule::f_set_stand_panel_layout(int &panelX)
{
    bool iHasPanel = false;
    int x = 0;
    stAnaesDepModuCfg anaesdep_cfg;
    g_AnaesModule->f_get_cfg(&anaesdep_cfg);
    if (anaesdep_cfg.m_para_enable) {
        iHasPanel = true;
        ((CMainForm*)pMainForm)->frame_mashen->setGeometry(QRect(730, 33, 292, 112));
         ((CMainForm*)pMainForm)->frame_mashen->show();
    } else {
        ((CMainForm*)pMainForm)->frame_mashen->hide();
        x += -112;
    }

    CEcgModuleCfg ecg_cfg;
    g_EcgModule->f_get_ecg_cfg(&ecg_cfg);
    if (ecg_cfg.m_ecg_para_enable) {
        iHasPanel = true;
         ((CMainForm*)pMainForm)->frame_ECG->setGeometry(QRect(730, 146+x, 292, 90));
         ((CMainForm*)pMainForm)->frame_ECG->show();
    } else {
        ((CMainForm*)pMainForm)->frame_ECG->hide();
        x += -90;
    }

    CSpo2ModuleCfg spo2_cfg;
    g_EcgModule->f_get_spo2_cfg(&spo2_cfg);
    if (spo2_cfg.m_spo2_para_enable) {
        iHasPanel = true;
        ((CMainForm*)pMainForm)->frame_spo2->setGeometry(QRect(730, 237+x, 292, 80));
         ((CMainForm*)pMainForm)->frame_spo2->show();
    } else {
         ((CMainForm*)pMainForm)->frame_spo2->hide();
        x += -80;
    }

    CNibpModuleCfg nibp_cfg;
    g_EcgModule->f_get_nibp_cfg(&nibp_cfg);
    if (nibp_cfg.m_nibp_para_enable) {
         iHasPanel = true;
          ((CMainForm*)pMainForm)->frame_nibp->setGeometry(QRect(730, 319+x, 292, 90));
          ((CMainForm*)pMainForm)->frame_nibp->show();
    } else {
        ((CMainForm*)pMainForm)->frame_nibp->hide();
        x += -90;
    }

    stIBPModuCfg ibp_cfg;
    g_IBPModule1->f_get_cfg(&ibp_cfg);
    if (ibp_cfg.m_ibp1_panel_enable) {
          iHasPanel = true;
          ((CMainForm*)pMainForm)->frame_ibp1->setGeometry(QRect(730, 410+x, 292, 80));
          ((CMainForm*)pMainForm)->frame_ibp1->show();
    } else {
        ((CMainForm*)pMainForm)->frame_ibp1->hide();
        x += -80;
    }
    if (ibp_cfg.m_ibp2_panel_enable) {
          iHasPanel = true;
          ((CMainForm*)pMainForm)->frame_ibp2->setGeometry(QRect(730, 492+x, 292, 80));
          ((CMainForm*)pMainForm)->frame_ibp2->show();
    } else {
        ((CMainForm*)pMainForm)->frame_ibp2->hide();
        x += -80;
    }

    CSpireModuleCfg spire_cfg;
    g_EcgModule->f_get_spire_cfg(&spire_cfg);
    if (spire_cfg.m_spire_para_enable) {
         iHasPanel = true;
         ((CMainForm*)pMainForm)->frame_sp->setGeometry(QRect(730, 573+x, 292, 80));
         ((CMainForm*)pMainForm)->frame_sp->show();
    } else {
         ((CMainForm*)pMainForm)->frame_sp->hide();
        x += -80;
    }

    CTempModuleCfg temp_cfg;
    g_EcgModule->f_get_temp_cfg(&temp_cfg);
    if (temp_cfg.m_temp_para_enable) {
        iHasPanel = true;
        ((CMainForm*)pMainForm)->frame_temp->setGeometry(QRect(730, 655+x, 292, 72));
        ((CMainForm*)pMainForm)->frame_temp->show();
    } else {
        ((CMainForm*)pMainForm)->frame_temp->hide();
       x += -72;
    }
    panelX = 730;
    return iHasPanel;
}

bool CLayoutModule::f_set_bigfont_panel_layout(int &panelX)
{
    bool iHasPanel = false;
    int x = 0;
    CEcgModuleCfg ecg_cfg;
    g_EcgModule->f_get_ecg_cfg(&ecg_cfg);
    if (ecg_cfg.m_ecg_para_enable) {
        iHasPanel = true;
         ((CMainForm*)pMainForm)->frame_ECG->setGeometry(QRect(590, 35, 430, 215));
         ((CMainForm*)pMainForm)->frame_ECG->show();
    } else {
        ((CMainForm*)pMainForm)->frame_ECG->hide();
        x += -215;
    }

    CSpireModuleCfg spire_cfg;
    g_EcgModule->f_get_spire_cfg(&spire_cfg);
    if (spire_cfg.m_spire_para_enable) {
         iHasPanel = true;
         ((CMainForm*)pMainForm)->frame_sp->setGeometry(QRect(590, 255+x, 430, 120));
         ((CMainForm*)pMainForm)->frame_sp->show();
    } else {
         ((CMainForm*)pMainForm)->frame_sp->hide();
        x += -120;
    }

    CSpo2ModuleCfg spo2_cfg;
    g_EcgModule->f_get_spo2_cfg(&spo2_cfg);
    if (spo2_cfg.m_spo2_para_enable) {
        iHasPanel = true;
        ((CMainForm*)pMainForm)->frame_spo2->setGeometry(QRect(590, 380+x, 430, 215));
         ((CMainForm*)pMainForm)->frame_spo2->show();
    } else {
         ((CMainForm*)pMainForm)->frame_spo2->hide();
        x += -215;
    }

    CTempModuleCfg temp_cfg;
    g_EcgModule->f_get_temp_cfg(&temp_cfg);
    if (temp_cfg.m_temp_para_enable) {
        iHasPanel = true;
        ((CMainForm*)pMainForm)-> frame_temp->setGeometry(QRect(590, 600+x, 430, 120));
        ((CMainForm*)pMainForm)->frame_temp->show();
    } else {
        ((CMainForm*)pMainForm)->frame_temp->hide();
       x += -120;
    }

    CNibpModuleCfg nibp_cfg;
    g_EcgModule->f_get_nibp_cfg(&nibp_cfg);
    if (nibp_cfg.m_nibp_para_enable) {
          ((CMainForm*)pMainForm)-> frame_nibp->setGeometry(QRect(5, 480, 580, 240));
          ((CMainForm*)pMainForm)->frame_nibp->show();
    } else {
        ((CMainForm*)pMainForm)->frame_nibp->hide();
    }
    panelX = 590;
    return iHasPanel;
}

bool CLayoutModule::f_set_ecg_panel_layout(int &panelX)
{
    bool iHasPanel = false;
    int x = 0;
    CEcgModuleCfg ecg_cfg;
    g_EcgModule->f_get_ecg_cfg(&ecg_cfg);
    if (ecg_cfg.m_ecg_para_enable) {
        iHasPanel = true;
         ((CMainForm*)pMainForm)->frame_ECG->setGeometry(QRect(660, 30, 360, 135));
         ((CMainForm*)pMainForm)->frame_ECG->show();
    } else {
        ((CMainForm*)pMainForm)->frame_ECG->hide();
        x += -140;
    }

    CNibpModuleCfg nibp_cfg;
    g_EcgModule->f_get_nibp_cfg(&nibp_cfg);
    if (nibp_cfg.m_nibp_para_enable) {
          ((CMainForm*)pMainForm)-> frame_nibp->setGeometry(QRect(660, 170+x, 360, 135));
          ((CMainForm*)pMainForm)->frame_nibp->show();
    } else {
        ((CMainForm*)pMainForm)->frame_nibp->hide();
        x += -140;
    }

    CSpo2ModuleCfg spo2_cfg;
    g_EcgModule->f_get_spo2_cfg(&spo2_cfg);
    if (spo2_cfg.m_spo2_para_enable) {
        iHasPanel = true;
        ((CMainForm*)pMainForm)->frame_spo2->setGeometry(QRect(660, 310+x, 360, 135));
         ((CMainForm*)pMainForm)->frame_spo2->show();
    } else {
         ((CMainForm*)pMainForm)->frame_spo2->hide();
        x += -140;
    }

    CSpireModuleCfg spire_cfg;
    g_EcgModule->f_get_spire_cfg(&spire_cfg);
    if (spire_cfg.m_spire_para_enable) {
         iHasPanel = true;
         ((CMainForm*)pMainForm)->frame_sp->setGeometry(QRect(660, 450+x, 360, 135));
         ((CMainForm*)pMainForm)->frame_sp->show();
    } else {
         ((CMainForm*)pMainForm)->frame_sp->hide();
        x += -140;
    }


    CTempModuleCfg temp_cfg;
    g_EcgModule->f_get_temp_cfg(&temp_cfg);
    if (temp_cfg.m_temp_para_enable) {
        iHasPanel = true;
        ((CMainForm*)pMainForm)-> frame_temp->setGeometry(QRect(660, 590+x, 360, 135));
        ((CMainForm*)pMainForm)->frame_temp->show();
    } else {
        ((CMainForm*)pMainForm)->frame_temp->hide();
       x += -140;
    }

    panelX = 660;
    return iHasPanel;
}

void CLayoutModule::f_layout_hint(CLayoutCfg cfg)
{
    f_update_wave_num();

    switch(cfg.m_layout_type)
    {
    case 0:
        f_set_stand_layout();
        ((CMainForm*)pMainForm)->f_set_standard_layout();
        break;
    case 1:
        f_set_bigfont_layout();
        ((CMainForm*)pMainForm)->f_set_big_font_layout();
        break;
    case 2:
        f_set_spirspo_layout();
        ((CMainForm*)pMainForm)->f_set_ecg_layout();
        break;
    case 3:
        f_set_nibpreview_layout();
        ((CMainForm*)pMainForm)->f_set_ecg_layout();
        break;
    case 4:
        f_set_trendtable_layout();
        ((CMainForm*)pMainForm)->f_set_ecg_layout();
        break;
    case 5:
        f_set_ecg_all_lead();
        ((CMainForm*)pMainForm)->f_set_ecg_layout();
        break;
    case 6:
        f_set_mashen_layout();
        ((CMainForm*)pMainForm)->f_set_ecg_layout();
        break;
    default:
        break;

    }
}

void CLayoutModule::f_set_wave_layout()
{
    g_WaveWidgetHeightPix = g_WaveWidgetAllHeightPix/g_WaveNumber;
    g_PixPerByte_3_125mm = g_WaveWidgetWidthPix/220.0*3.125/125.0;  //(730[pix]/220[mm])* 3.125[mm/s] / (125[Byte/s])
    g_PixPerByte_6_25mm = g_WaveWidgetWidthPix/220.0*6.25/125.0; //(730[pix]/220[mm])* 6.25[mm/s] / (125[Byte/s])
    g_PixPerByte_12_5mm =  g_WaveWidgetWidthPix/220.0*12.5/125.0;// (730[pix]/220[mm])* 12.5[mm/s] / (125[Byte/s])
    g_PixPerByte_25mm =  g_WaveWidgetWidthPix/220.0*25.0/125.0;//(730[pix]/220[mm])* 25[mm/s] / (125[Byte/s])
    g_PixPerByte_50mm =  g_WaveWidgetWidthPix/220.0*50.0/125.0;//(730[pix]/220[mm])* 50[mm/s] / (125[Byte/s])
    int iHLayout = 0;
    int index = 0;
    {
        CEegModuleCfg cfg;
        g_EegModule->f_get_eeg_cfg(&cfg);

        for(int i = 0; i<EEG_MODULE_WAVE_NUM;i++)
        {
            if(cfg.m_wave_plot_enable[i] == true)
            {
                cfg.m_wave_rec[i] = QRect(0,iHLayout,g_WaveWidgetWidthPix,g_WaveWidgetHeightPix);
                iHLayout +=g_WaveWidgetHeightPix;
                cfg.m_wave_indx[i] = index++;
            }
        }
        g_EegModule->f_set_eeg_cfg(cfg);
        g_EegModule->f_set_eeg_wave_layout();
    }
    {
        CEcgModuleCfg cfg;
        g_EcgModule->f_get_ecg_cfg(&cfg);

        for(int i = 0; i<ECG_MODULE_WAVE_NUM-1;i++)
        {
            if(cfg.m_wave_plot_enable[i] == true)
            {
                cfg.m_wave_rec[i] = QRect(0,iHLayout,g_WaveWidgetWidthPix,g_WaveWidgetHeightPix);
                iHLayout +=g_WaveWidgetHeightPix;
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
            cfg.m_wave_rec = QRect(0,iHLayout,g_WaveWidgetWidthPix,g_WaveWidgetHeightPix);
            iHLayout +=g_WaveWidgetHeightPix;
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
                                   g_WaveWidgetWidthPix,
                                   g_WaveWidgetHeightPix-2);
             iHLayout +=g_WaveWidgetHeightPix-2;
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
                                   g_WaveWidgetWidthPix,
                                   g_WaveWidgetHeightPix-2);
            iHLayout +=g_WaveWidgetHeightPix-2;
            cfg.m_wave_indx= index++;
            g_EcgModule->f_set_spire_cfg(cfg);
            g_EcgModule->f_set_spire_wave_layout();
        }
    }

    {
        stIBPModuCfg cfg;
        g_IBPModule1->f_get_cfg(&cfg);
        if (cfg.m_ibp1_wave_enable) {
            cfg.m_ibp1_wave_rec = QRect(0,iHLayout,g_WaveWidgetWidthPix-2,g_WaveWidgetHeightPix-2);
            iHLayout +=g_WaveWidgetHeightPix;
        }
        if (cfg.m_ibp2_wave_enable) {
            cfg.m_ibp2_wave_rec = QRect(0,iHLayout,g_WaveWidgetWidthPix-2,g_WaveWidgetHeightPix-2);
            iHLayout +=g_WaveWidgetHeightPix;
        }
        g_IBPModule1->f_set_cfg(cfg);
        g_IBPModule1->f_set_wave_layout();
    }
    {
        stAnaesDepModuCfg cfg;
        g_AnaesModule->f_get_cfg(&cfg);
        if (cfg.m_wave_enable) {
            cfg.m_wave_rec = QRect(0,iHLayout,g_WaveWidgetWidthPix-2,g_WaveWidgetHeightPix-2);
            iHLayout +=g_WaveWidgetHeightPix;
        }
        g_AnaesModule->f_set_cfg(cfg);
 //       g_AnaesModule->f_set_wave_layout();
    }
/*
    QRect ret(0,
              STATUS_BAR_WIDGET_HEIGHT,
              g_WaveWidgetWidthPix,
              g_WaveWidgetAllHeightPix);
    g_WavePlotter->setGeometry(ret);
    */
    g_WavePlotter->clearScreen();
}

void CLayoutModule::f_set_stand_layout()
{
    bool iHasPanel = false;
    int panelX = 0;
    iHasPanel = f_set_stand_panel_layout(panelX);
    g_WaveWidgetWidthPix =  (iHasPanel)?panelX:1022;
    g_WaveWidgetAllHeightPix =696;
    f_set_wave_layout();
}

void CLayoutModule::f_set_bigfont_layout()
{
    bool iHasPanel = false;
    int panelX = 0;
    iHasPanel = f_set_bigfont_panel_layout(panelX);
    CNibpModuleCfg nibp_cfg;
    g_EcgModule->f_get_nibp_cfg(&nibp_cfg);
    if (nibp_cfg.m_nibp_para_enable) {
        g_WaveWidgetAllHeightPix = 440;
    } else {
        g_WaveWidgetAllHeightPix = 696;
    }
    g_WaveWidgetWidthPix = (iHasPanel)?panelX:1022;
    f_set_wave_layout();
}

void CLayoutModule::f_set_spirspo_layout()
{
    f_set_wave_layout();
}

void CLayoutModule::f_set_nibpreview_layout()
{
     f_set_wave_layout();
}

void CLayoutModule::f_set_trendtable_layout()
{
     f_set_wave_layout();
}

void CLayoutModule::f_set_mashen_layout()
{
     f_set_wave_layout();
}

void CLayoutModule::f_set_ecg_all_lead()
{
    bool iHasPanel = false;
    int panelX = 0;
    iHasPanel = f_set_ecg_panel_layout(panelX);
    g_WaveWidgetWidthPix = (iHasPanel)?panelX:1022;
    g_WaveWidgetAllHeightPix =  696;
    f_set_wave_layout();
}
