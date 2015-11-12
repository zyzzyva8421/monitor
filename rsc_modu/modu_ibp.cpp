#include "modu_ibp.h"
#include "mainform.h"
#include <QtCore>
#include "rsc_modu/color.h"

QString qsIbpTypeLabel [8]= {"主动脉压",
                            "肺动脉压",
                            "中心静脉压",
                            "左房压",
                            "右房压",
                            "颅内压",
                            "P1",
                            "P2"
                           };
CIBPModu::CIBPModu(QWidget *parent)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    pMainForm = parent;
    m_modu_cfg = new stIBPModuCfg;
    //m_ibp1_wave_plot = new WavePlotter(pMainForm);
    //m_ibp2_wave_plot = new WavePlotter(pMainForm);
    m_ibp1_wave_plot_setting = new WavePlotSettings();
    m_ibp2_wave_plot_setting = new WavePlotSettings();
    f_setDefaultCfg();

    //get ecg file config
    {
        QFile file((IBP_MODULE_CFG_DOC));
        if(file.open(QIODevice::ReadOnly))
        {
            stIBPModuCfg tempCfg;
            QDataStream inout(&file);
            int magic;
            inout >> magic;
            if(magic == 0x12345678)
            {
                inout.readRawData((char *)&tempCfg,sizeof(stIBPModuCfg));
            }
            memcpy(m_modu_cfg,&tempCfg,sizeof(stIBPModuCfg));
            file.close();
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            QDataStream inout(&file);
            int magic = 0x12345678;
            inout<<magic;
            inout.writeRawData((char *)m_modu_cfg,sizeof(stIBPModuCfg));
            file.close();
        }
    }
/*
    m_ibp1_wave_plot->setWaveName((qsIbpTypeLabel[m_modu_cfg->m_chanel1_type]));
    m_ibp1_wave_plot_setting->minX = 0.0;
    m_ibp1_wave_plot_setting->maxX = 8200.0;
    m_ibp1_wave_plot_setting->minY = 0.0;
    m_ibp1_wave_plot_setting->maxY = 100.0;
    m_ibp1_wave_plot->setPlotSettings(*m_ibp1_wave_plot_setting);
    m_ibp1_wave_plot->setGeometry(m_modu_cfg->m_ibp1_wave_rec);//();
    m_ibp1_wave_plot->setWaveColor(0,GLB_COLOR(m_modu_cfg->m_ibp1_wave_color));
    if(m_modu_cfg->m_ibp1_wave_enable)
    {
        m_ibp1_wave_plot->show();
    }

    m_ibp2_wave_plot->setWaveName(qsIbpTypeLabel[m_modu_cfg->m_chanel2_type]);
    m_ibp2_wave_plot_setting->minX = 0.0;
    m_ibp2_wave_plot_setting->maxX = 8200.0;
    m_ibp2_wave_plot_setting->minY = 0.0;
    m_ibp2_wave_plot_setting->maxY = 100.0;
    m_ibp2_wave_plot->setPlotSettings(*m_ibp2_wave_plot_setting);
    m_ibp2_wave_plot->setGeometry(m_modu_cfg->m_ibp2_wave_rec);//();
    m_ibp2_wave_plot->setWaveColor(0,GLB_COLOR(m_modu_cfg->m_ibp2_wave_color));
    if(m_modu_cfg->m_ibp2_wave_enable)
    {
        m_ibp2_wave_plot->show();
    }
*/
}

void CIBPModu::f_setDefaultCfg()
{
    m_modu_cfg->m_alarm_enable = false;
    m_modu_cfg->m_wave_amp = 0;
    m_modu_cfg->m_alarm_high = 100;
    m_modu_cfg->m_alarm_low = 60;
    m_modu_cfg->m_wave_speed = 0;
    m_modu_cfg->m_chanel1_type = 0;
    m_modu_cfg->m_chanel2_type = 1;
    m_modu_cfg->m_wave_ruler_mode = 0;
    m_modu_cfg->m_wave_filter_mode = 1;
    m_modu_cfg->m_wave_speed = 1;
    m_modu_cfg->m_modu_unit = 0;
    m_modu_cfg->m_p1_type = 0;
    m_modu_cfg->m_p2_type = 0;
    m_modu_cfg->m_chanel1_ruler_high = 10;
    m_modu_cfg->m_chanel1_ruler_low = 0;
    m_modu_cfg->m_chanel2_ruler_high = 10;
    m_modu_cfg->m_chanel2_ruler_low = 0;
    m_modu_cfg->m_ibp1_wave_rec = QRect(0,STATUS_BAR_WIDGET_HEIGHT,
                                        g_WaveWidgetWidthPix,
                                        g_WaveWidgetHeightPix);
    m_modu_cfg->m_ibp1_wave_rec = QRect(0,STATUS_BAR_WIDGET_HEIGHT,
                                        g_WaveWidgetWidthPix,
                                        g_WaveWidgetHeightPix);
    m_modu_cfg->m_ibp1_wave_enable = false;
    m_modu_cfg->m_ibp2_wave_enable = false;
     m_modu_cfg->m_ibp1_wave_indx = 0;
     m_modu_cfg->m_ibp2_wave_indx = 0;
     m_modu_cfg->m_ibp1_panel_color = 5;
     m_modu_cfg->m_ibp2_panel_color = 5;
}
void CIBPModu::f_reset_value()
{
    m_modu_value.m_ibp_flg = 23;//1	23，代表IBP
    m_modu_value.m_ibp_flg_1 = 4;//1	4
    m_modu_value.m_reserve0 = 0;//1
    for(int i = 0; i<256;i++)
    {
        m_modu_value.m_ibp_wave[i] = 0;//256	2通道IBP波形，每通道长度为128字节
    }

    m_modu_value.m_ibp1_type = 1;//1	通道1波形名称名称1-10：ART,PA,CVP,LAP,RAP,ICP,P1,P2,P3,P4
    m_modu_value.m_ibp1_amp = 0;//2	通道1波形放大系数
    m_modu_value.m_flag = 0xaa55;//2	0xaa55
    m_modu_value.m_ibp1_baseline = 128;//2	通道1波形基线
    m_modu_value.m_ibp2_type = 2;//1	通道2波形名称1-10：ART,PA,CVP,LAP,RAP,ICP,P1,P2,P3,P4
    m_modu_value.m_ibp2_amp = 0;//2	通道2波形放大系数
    m_modu_value.m_flag_1 = 0xaa55;//2	0xaa55
    m_modu_value.m_ibp2_baseline = 128;//2	通道2波形基线
    m_modu_value.m_ibp1_ss = -100;//2	通道1收缩压
    m_modu_value.m_ibp1_sz = -100;//2	通道1舒张压
    m_modu_value.m_ibp1_pj = -100;//2	通道1平均压
    m_modu_value.m_ibp2_ss = -100;//2	通道2收缩压
    m_modu_value.m_ibp2_sz = -100;//2	通道2舒张压
    m_modu_value.m_ibp2_pj = -100;//2	通道2平均压

    m_modu_value.m_alarm_ibp1_ss_high = m_modu_cfg->m_alarm_ibp1_ss_high;//2	通道1收缩压报警上限
    m_modu_value.m_alarm_ibp1_ss_low = m_modu_cfg->m_alarm_ibp1_ss_low;//2	通道1收缩压报警上限
    m_modu_value.m_alarm_ibp1_ss_level = 1;//2	通道1收缩压报警级别，1～3分别对应高、中、低级报警
    m_modu_value.m_alarm_ibp1_sz_high = m_modu_cfg->m_alarm_ibp1_sz_high;//2	通道1舒张压报警上限
    m_modu_value.m_alarm_ibp1_sz_low = m_modu_cfg->m_alarm_ibp1_sz_low;//2	通道1舒张压报警上限
    m_modu_value.m_alarm_ibp1_sz_level = 1;//2	通道1舒张压报警级别，1～3分别对应高、中、低级报警
    m_modu_value.m_alarm_ibp1_pj_high = m_modu_cfg->m_alarm_ibp1_pj_high;//2	通道1平均压报警上限
    m_modu_value.m_alarm_ibp1_pj_low = m_modu_cfg->m_alarm_ibp1_pj_low;//2	通道1平均压报警上限
    m_modu_value.m_alarm_ibp1_pj_level = 1;//2	通道1平均压报警级别，1～3分别对应高、中、低级报警
    m_modu_value.m_alarm_ibp2_ss_high = m_modu_cfg->m_alarm_ibp2_ss_high;//2	通道2收缩压报警上限
    m_modu_value.m_alarm_ibp2_ss_low = m_modu_cfg->m_alarm_ibp2_ss_low;//2	通道2收缩压报警上限
    m_modu_value.m_alarm_ibp2_ss_level = 1;//2	通道2收缩压报警级别，1～3分别对应高、中、低级报警
    m_modu_value.m_alarm_ibp2_sz_high = m_modu_cfg->m_alarm_ibp2_sz_high;//2	通道2舒张压报警上限
    m_modu_value.m_alarm_ibp2_sz_low = m_modu_cfg->m_alarm_ibp2_sz_low;//2	通道2舒张压报警上限
    m_modu_value.m_alarm_ibp2_sz_level = 1;//2	通道2舒张压报警级别，1～3分别对应高、中、低级报警
    m_modu_value.m_alarm_ibp2_pj_high = m_modu_cfg->m_alarm_ibp2_pj_high;//2	通道2平均压报警上限
    m_modu_value.m_alarm_ibp2_pj_low = m_modu_cfg->m_alarm_ibp2_pj_low;//2	通道2平均压报警上限
    m_modu_value.m_alarm_ibp2_pj_level = 0;//2	通道2平均压报警级别，1～3分别对应高、中、低级报警
    for(int i = 0;i<4;i++)
    m_modu_value.reserve1[i] = 0;//4	保留

}

void CIBPModu::f_set_def_cfg()
{
    f_setDefaultCfg();
    QFile file(IBP_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_modu_cfg,sizeof(stIBPModuCfg));
    file.close();
}

void CIBPModu::f_set_cfg(stIBPModuCfg cfg)
{
    //set display
    if((m_modu_cfg->m_chanel1_type != cfg.m_chanel1_type)
        ||(m_modu_cfg->m_chanel2_type != cfg.m_chanel2_type))
    {
        f_set_panel_display();
    }
    memcpy(m_modu_cfg,&cfg,sizeof(stIBPModuCfg));
    QFile file(IBP_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_modu_cfg,sizeof(stIBPModuCfg));
    file.close();
}

void CIBPModu::f_get_cfg( stIBPModuCfg* cfg)
{
    memcpy(cfg,m_modu_cfg,sizeof(stIBPModuCfg));
}

void CIBPModu::f_set_panel_display()
{
    CMainForm *p = (CMainForm *)pMainForm;
    p->TextLabel_IBP1_Name->setText((qsIbpTypeLabel[m_modu_cfg->m_chanel1_type]));
    p->TextLabel_IBP2_Name->setText(qsIbpTypeLabel[m_modu_cfg->m_chanel2_type]);
}
void CIBPModu::f_set_wave_color()
{
    if(m_modu_cfg->m_ibp1_wave_enable)
    {
        g_WavePlotter->setWaveColor(m_modu_cfg->m_ibp1_wave_indx,
                                    GLB_COLOR(m_modu_cfg->m_ibp1_wave_color));
    }
    if(m_modu_cfg->m_ibp2_wave_enable)
    {
        g_WavePlotter->setWaveColor(m_modu_cfg->m_ibp2_wave_indx,
                                    GLB_COLOR(m_modu_cfg->m_ibp2_wave_color));
    }

}
void CIBPModu::f_set_wave_layout()
{
    /*
    m_ibp1_wave_plot->setGeometry(m_modu_cfg->m_ibp1_wave_rec);//();
    m_ibp2_wave_plot->setGeometry(m_modu_cfg->m_ibp2_wave_rec);//();
    if(m_modu_cfg->m_ibp1_wave_enable)
    {
        m_ibp1_wave_plot->show();
    }
    else
    {
        m_ibp1_wave_plot->hide();
    }
    if(m_modu_cfg->m_ibp2_wave_enable)
    {
        m_ibp2_wave_plot->show();
    }
    else
    {
        m_ibp2_wave_plot->hide();
    }
    */
}
