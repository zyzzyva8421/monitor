#include "modu_ecg.h"
#include <QFile>
#include <QDataStream>
#include <QtCore>
#include <QObject>
#include "rsc_modu/color.h"
#include "color.h"
#include "mainform.h"
#include "rsc_warning/glb_warning.h"
#include "rsc_modu/modu_thread.h"
#define ECG_CURVE_HEIGHT 50
#define SPIRE_CURVE_HEIGHT 48
#define SPO2_CURVE_HEIGHT 48
/*
CEcgModuleCfg::CEcgModuleCfg()
{


    m_module_enable = true;//true = module enable;
    for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
    {
        m_wave_color[i] = Qt::green; // wave color
    }
    m_panel_color = Qt::red;//para color
    m_ecg_wave_speed = 2; //6.25mm/s *N

    m_dara_src = ENUM_ECG_DATA_SRC_PORT; //where data from:file or serial port;

    m_data_src_file_name = ECG_MODULE_DATA_FILE_NAME;

    //port para
    m_serial_port_cfg.BaudRate = BAUD115200;
    m_serial_port_cfg.DataBits = DATA_8;
    m_serial_port_cfg.FlowControl = FLOW_OFF;
    m_serial_port_cfg.Parity = PAR_NONE;
    m_serial_port_cfg.StopBits = STOP_1;

    m_serial_port_num = 0; //searial port number
    m_serial_port_name = ECG_MODULE_DATA_PORT_NAME; //serial port name

    //alarm
    m_para_alarm_en = true; //true = para alarm enable flg enable
    m_tech_alarm_en  = true; // true = tech alarm enbale flag enable

    //wave
    m_wave_num = ECG_MODULE_WAVE_NUM; //module has n waves to draw;
     m_ecg_chanel1_lead = ECG_MODULE_LEAD_I;//通道导联
     m_ecg_chanel2_lead = ECG_MODULE_LEAD_II;
     m_ecg_chanel3_lead = ECG_MODULE_LEAD_III;
     m_ecg_amp = 0;
     m_ect_pwr_supression_enable = true;
     m_ecg_lead_style = ECG_MODULE_LEAD_MOD_5;
     m_ecg_pacemaker_enable = true;
     m_ecg_filter_mod = ECG_MODULE_FILTER_MOD_CARE;
     m_ecg_pulse_vol = 1;
     m_ecg_beatrate_src = ECG_MODULE_BEATRATE_SRC_ECG;
     m_ecg_wave_speed = 2; //6.25mm/s *(N+1)
     m_ecg_st_enable = true;
     m_ecg_pvcs_enbale = true;

}
*/


CEcgModule::CEcgModule( QWidget *parent)
{
    pMainForm = (CMainForm *)parent;
    iStoptest = 0;
    //config
    m_ecg_cfg = new CEcgModuleCfg();
    m_spo2_cfg = new CSpo2ModuleCfg;
    m_nibp_cfg = new CNibpModuleCfg;
    m_spire_cfg = new CSpireModuleCfg;
    m_temp_cfg = new CTempModuleCfg;
    m_ecg_wave_count = 0;
    m_spo2_wave_count = 0;
    m_spire_wave_count = 0;
    m_nibp_wave_count = 0;
    m_temp_wave_count = 0;
    //m_ecg_value.resize(981);
    m_spo2_value.resize(278);
    m_nibp_value.resize(37);
    m_temp_value.resize(48);
    m_spire_value.resize(0);
    m_ecg_backup_cnt = 0;
    m_spire_backup_cnt = 0;
    m_port = new Posix_QextSerialPort(ECG_MODULE_DATA_PORT_NAME);
    m_port->open(QIODevice::ReadWrite);
    m_port->setBaudRate((BaudRateType)115200);
    m_port->setDataBits(DATA_8);
    m_port->setParity(PAR_NONE);
    m_port->setStopBits(STOP_1);
    m_port->setFlowControl(FLOW_OFF);
    m_port->setTimeout(10);
    m_port->flush();


    f_setDefaultCfg();

    //get ecg file config
    {
        QFile file((ECG_MODULE_CFG_DOC));
        if(file.open(QIODevice::ReadOnly))
        {
            CEcgModuleCfg tempCfg;
            QDataStream inout(&file);
            int magic;
            inout >> magic;
            if(magic == 0x12345678)
            {
                inout.readRawData((char *)&tempCfg,sizeof(CEcgModuleCfg));
            }
            memcpy(m_ecg_cfg,&tempCfg,sizeof(CEcgModuleCfg));
            file.close();
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            QDataStream inout(&file);
            int magic = 0x12345678;
            inout<<magic;
            inout.writeRawData((char *)m_ecg_cfg,sizeof(CEcgModuleCfg));
            file.close();
        }
    }
    //get spo2 file config
    {
        QFile file((SPO2_MODULE_CFG_DOC));
        if(file.open(QIODevice::ReadOnly))
        {
            CSpo2ModuleCfg tempCfg;
            QDataStream inout(&file);
            int magic;
            inout >> magic;
            if(magic == 0x12345678)
            {
                inout.readRawData((char *)&tempCfg,sizeof(CSpo2ModuleCfg));
            }
            memcpy(m_spo2_cfg,&tempCfg,sizeof(CSpo2ModuleCfg));
            file.close();
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            QDataStream inout(&file);
            int magic = 0x12345678;
            inout<<magic;
            inout.writeRawData((char *)m_spo2_cfg,sizeof(CSpo2ModuleCfg));
            file.close();
        }
    }
    //获取nibp的设置文件
    {
        QFile file((NIBP_MODULE_CFG_DOC));
        if(file.open(QIODevice::ReadOnly))
        {
            CNibpModuleCfg tempCfg;
            QDataStream inout(&file);
            int magic;
            inout >> magic;
            if(magic == 0x12345678)
            {
                inout.readRawData((char *)&tempCfg,sizeof(CNibpModuleCfg));
            }
            memcpy(m_nibp_cfg,&tempCfg,sizeof(CNibpModuleCfg));
            file.close();
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            QDataStream inout(&file);
            int magic = 0x12345678;
            inout<<magic;
            inout.writeRawData((char *)m_nibp_cfg,sizeof(CNibpModuleCfg));
            file.close();
        }
    }
    //获取体温的设置文件
    {
        QFile file((TEMP_MODULE_CFG_DOC));
        if(file.open(QIODevice::ReadOnly))
        {
            CTempModuleCfg tempCfg;
            QDataStream inout(&file);
            int magic;
            inout >> magic;
            if(magic == 0x12345678)
            {
                inout.readRawData((char *)&tempCfg,sizeof(CTempModuleCfg));
            }
            memcpy(m_temp_cfg,&tempCfg,sizeof(CTempModuleCfg));
            file.close();
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            QDataStream inout(&file);
            int magic = 0x12345678;
            inout<<magic;
            inout.writeRawData((char *)m_temp_cfg,sizeof(CTempModuleCfg));
            file.close();
        }
    }
    //获取呼吸的设置文件
    {
        QFile file((SPIRE_MODULE_CFG_DOC));
        if(file.open(QIODevice::ReadOnly))
        {
            CSpireModuleCfg tempCfg;
            QDataStream inout(&file);
            int magic;
            inout >> magic;
            if(magic == 0x12345678)
            {
                inout.readRawData((char *)&tempCfg,sizeof(CSpireModuleCfg));
            }
            memcpy(m_spire_cfg,&tempCfg,sizeof(CSpireModuleCfg));
            file.close();
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            QDataStream inout(&file);
            int magic = 0x12345678;
            inout<<magic;
            inout.writeRawData((char *)m_spire_cfg,sizeof(CSpireModuleCfg));
            file.close();
        }
    }

    //open wave plotter
    m_spo2_data_to_draw.resize(1);
    m_spo_draw_pos = 0;
    m_ecg_data_to_draw.resize(ECG_MODULE_WAVE_NUM);
/*
    for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
    {
        m_wave_plot[i] = new WavePlotter(parent);        
        m_wave_plot_setting[i] = new WavePlotSettings();
        m_wave_plot_setting[i]->minX = 0.0;
        m_wave_plot_setting[i]->maxX = 500.0;
        m_wave_plot_setting[i]->minY = 0.0;
        m_wave_plot_setting[i]->maxY = 100.0;

        m_wave_plot[i]->setPlotSettings(*m_wave_plot_setting[i]);
        m_wave_plot[i]->setGeometry(m_ecg_cfg->m_wave_rec[i]);//();
        m_wave_plot[i]->setWaveColor(0,GLB_COLOR(m_ecg_cfg->m_wave_color[i]));
        if(m_ecg_cfg->m_wave_plot_enable[i])
        {
            m_wave_plot[i]->show();
        }

    }
    m_wave_plot[0]->setWaveName("ECG I");
    m_wave_plot[1]->setWaveName("ECG II");
    m_wave_plot[2]->setWaveName("ECG III");
    m_wave_plot[3]->setWaveName("ECG RA");
    m_wave_plot[4]->setWaveName("ECG LA");
    m_wave_plot[5]->setWaveName("ECG LL");
    m_wave_plot[6]->setWaveName("ECG V");

    m_spo2_wave_plot = new WavePlotter(parent);
    m_spo2_wave_plot_set= new WavePlotSettings();
    m_spo2_wave_plot->setWaveName(1,"血氧");
    m_spo2_wave_plot_set->minX = 0.0;
    m_spo2_wave_plot_set->maxX = 8200.0;
    m_spo2_wave_plot_set->minY = 0.0;
    m_spo2_wave_plot_set->maxY = 100.0;
    m_spo2_wave_plot->setPlotSettings(*m_spo2_wave_plot_set);
    //m_spo2_wave_plot->setGeometry(m_spo2_cfg->m_wave_rec);//();
    QRect rec=QRect(0,32,730,696);
    m_spo2_wave_plot->setGeometry(rec);
    m_spo2_wave_plot->setWaveColor(0,GLB_COLOR(m_spo2_cfg->m_wave_color));
    //m_spo2_wave_plot->setGeometry(0,32,730,690);
    if(m_spo2_cfg->m_wave_enable)
    {
        m_spo2_wave_plot->show();
    }


    m_spire_wave_plot = new WavePlotter(parent);
    m_spire_wave_plot_set = new WavePlotSettings();
    m_spire_wave_plot->setWaveName("呼吸波");
    m_spire_wave_plot_set->minX = 0.0;
    m_spire_wave_plot_set->maxX = 500.0;
    m_spire_wave_plot_set->minY = 0.0;
    m_spire_wave_plot_set->maxY = 100.0;
    m_spire_wave_plot->setPlotSettings(*m_spire_wave_plot_set);
    m_spire_wave_plot->setGeometry(m_spire_cfg->m_wave_rec);//();
    m_spire_wave_plot->setWaveColor(0,GLB_COLOR(m_spire_cfg->m_wave_color));
    if(m_spire_cfg->m_wave_enable)
    {
        m_spire_wave_plot->show();
    }
*/
    m_modu_data_file.setFileName("/home/ecg.dat");
    m_modu_data_file.open(QIODevice::ReadWrite);
    QDataStream inout(&m_modu_data_file);
    inout.readRawData(ecgdata,1024);

    f_reset_ecg_spire_value();
    f_reset_spo2_value();
    f_reset_nibp_value();
    f_reset_temp_record_value();
    connect(this,SIGNAL(signal_para_ecg_value_changed(stEcgValue )),parent, SLOT(slot_para_ecg_value_changed(stEcgValue)));

    connect(this,SIGNAL(signal_para_nibp_value_changed(stNibpValue) ),parent,SLOT(slot_para_nibp_value_changed(stNibpValue )));
    connect(this,SIGNAL(signal_para_spo2_value_changed(stSpo2Value )),parent,SLOT(slot_para_spo2_value_changed(stSpo2Value )));
    connect(this,SIGNAL(signal_para_temp_value_changed(stTempValue) ),parent,SLOT(slot_para_temp_value_changed(stTempValue )));
    connect(this,SIGNAL(signal_para_spire_value_changed(stSpireValue )),parent,SLOT(slot_para_spire_value_changed(stSpireValue )));

    connect(this,SIGNAL(signal_setpanels_value(QLabel *,double ,int )),parent, SLOT(slot_setpanels_value(QLabel *,double ,int )));
    connect(this,SIGNAL(signal_setpanels_value(QLabel *,int )),parent, SLOT( slot_setpanels_value(QLabel *,int )));
    connect(this,SIGNAL(signal_setpanels_value(QLabel *, QString)),parent, SLOT(slot_setpanels_value(QLabel *, QString )));

    plot_time = new QTimer(this);
    connect(plot_time,SIGNAL(timeout()),this,SLOT(slot_plot_all_waves()));
    plot_time->start(10);

}
CEcgModule::~CEcgModule()
{
    m_modu_data_file.close();
    delete m_ecg_cfg;


    delete m_spo2_cfg ;
   delete m_nibp_cfg ;
    delete m_spire_cfg ;
    delete m_temp_cfg;
    for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
    {
        delete m_wave_plot[i];
        delete m_wave_plot_setting[i];
    }

    delete m_spo2_wave_plot;
    delete m_spo2_wave_plot_set;


    delete m_spire_wave_plot;
    delete m_spire_wave_plot_set;


}
void CEcgModule::slot_plot_all_waves()
{
#define MAX_BYTE_PER_PROCES 10
    bool flg = false;
    int ch1[MAX_BYTE_PER_PROCES]={0};
    int ch2[MAX_BYTE_PER_PROCES] = {0};
    int ch3[MAX_BYTE_PER_PROCES] ={0};
    int len = 0;
    /*
    QVector<QPointF> tempint;
    for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
    {
        if(m_ecg_cfg->m_wave_plot_enable[i])
        {
            {
                QMutexLocker locker(&m_mutex_wave_ecg);
                int len = m_ecg_data_to_draw[i].count();
                if(len>5)
                {
                    for(int j = 0;j< 5;j++)
                    {
                        tempint.append(m_ecg_data_to_draw[i][j]);
                    }
                    m_ecg_data_to_draw[i].remove(0,5);
                    flg = true;
                     g_WavePlotter->setCurveData(m_ecg_cfg->m_wave_indx[i], tempint,tempint[4].x());
                }
            }
          }
            if(flg)
            {
                   //g_WavePlotter->setCurveData(m_ecg_cfg->m_wave_indx[i], tempint,m_ecg_last_pos[i]);
                   flg = false;
                   tempint.clear();
            }

        }*/
    /*
    {
        QMutexLocker locker(&m_mutex_wave_ecg);

         len = m_ecg_wave_data_1.count();
        if(len >=MAX_BYTE_PER_PROCES)
        {
            len = MAX_BYTE_PER_PROCES;
        }
        for (int i=0;i<len;i++)
        {
            ch1[i] = m_ecg_wave_data_1[i];
            ch2[i] = m_ecg_wave_data_2[i];
            ch3[i] = m_ecg_wave_data_3[i];
            flg = true;
        }
        m_ecg_wave_data_1.remove(0,len);
        m_ecg_wave_data_2.remove(0,len);
        m_ecg_wave_data_3.remove(0,len);
    }
    if(flg)
    {
        for(int i=0;i<len;i++)
        {
            f_plot_ecg_wave(ch1[i],ch2[i],ch3[i]);
        }
    flg = false;
    }
    {
        QMutexLocker locker(&m_mutex_wave_spo2);

         len = m_spo2_wave_data.count();
        if(len >=MAX_BYTE_PER_PROCES)
        {
            len = MAX_BYTE_PER_PROCES;
        }
        for (int i=0;i<len;i++)
        {
            ch1[i] = m_spo2_wave_data[i];
            emit signal_setpanels_value(pMainForm->TextLabel_bar_alarm_III,ch1[i]);
            flg = true;
        }
        m_spo2_wave_data.remove(0,len);
    }
    if(flg)
    {
        for(int i=0;i<len;i++)
        {
            f_plot_spo2_wave(ch1[i]);
        }
    flg = false;
    }
    {
        QMutexLocker locker(&m_mutex_wave_spire);

         len = m_spire_wave_data.count();
        if(len >=MAX_BYTE_PER_PROCES)
        {
            len = MAX_BYTE_PER_PROCES;
        }
        for (int i=0;i<len;i++)
        {
            ch1[i] = m_spire_wave_data[i];

            flg = true;
        }
        m_spire_wave_data.remove(0,len);
    }
    if(flg)
    {
        for(int i=0;i<len;i++)
        {
            f_plot_spire_wave(ch1[i]);
        }
    flg = false;
    }
    */
    {
        QMutexLocker locker(&m_mutex_wave_ecg);
    }
    {
        QMutexLocker locker(&m_mutex_wave_spo2);
    }
    {
        QMutexLocker locker(&m_mutex_wave_spire);
    }
}
void CEcgModule::f_reset_ecg_spire_value()
{
    m_ecg_val.m_ecg_flg = 20;//1	20，代表ECG
    m_ecg_val.m_ecg_flg_1 = 1;//1	0
    for(int i = 0; i< 3;i++)
    {
        for(int j = 0; j< 256;j++)
        {
             m_ecg_val.m_ecg_wave_data[i][j] = 0;//256×3	3通道ECG波形，每通道长度为256字节
        }
    }
   for(int i = 0; i< 128;i++)
   {
       m_ecg_val.m_spire_wave_data[i] = 0;//128	呼吸波形，长度为128字节
   }

    m_ecg_val.m_para_beat_rate = -100;//2	心率，-100代表无效值
    m_ecg_val.m_para_ecg_spr = -100;//2	呼吸率，-100代表无效值
    m_ecg_val.m_para_st1 = -100;//4	ST1，单位0.01mv，-100.00代表无效值
    m_ecg_val.m_para_st2 = -100;//4	ST2，单位0.01mv，-100.00代表无效值
    m_ecg_val.m_para_st3 = -100;//4	ST3，单位0.01mv，-100.00代表无效值
    m_ecg_val.m_para_pvcs = -100;//2	PVC，-100代表无效值
    m_ecg_val.m_ecg_name[0] = m_ecg_cfg->m_ecg_chanel1_lead;//3	3通道ECG 波形名称，1～8对应I、II、III、aVR、aVL、aVF、V、校准
    m_ecg_val.m_ecg_name[1] = m_ecg_cfg->m_ecg_chanel2_lead;
    m_ecg_val.m_ecg_name[2] = m_ecg_cfg->m_ecg_chanel3_lead;
    m_ecg_val.m_ecg_amp[0] = m_ecg_cfg->m_ecg_amp;//3	3通道ECG增益，1～4对应X0.25、X0.5、X1、X2
    m_ecg_val.m_layout_type = 0;//1	屏幕布局，0～5分别对应：标准界面、大字体界面、呼吸氧合图界面、血压趋势界面、趋势表界面、全屏多导界面
    m_ecg_val.m_ecg_pacemaker_enable;//1	高4位：起搏开关，0：关，1：开 低4位：陷波开关，0：关，1：开

    m_ecg_val.m_ecg_filter_mod = m_ecg_cfg->m_ecg_filter_mod;//1	滤波模式，1～3分别对应诊断、监护、手术模式
    m_ecg_val.m_spire_asp_alarm = m_spire_cfg->m_spire_asp_alarm;//1	呼吸窒息时间，0～6分别对应关、10秒、15秒、20秒、25秒、30秒、35秒、40秒、
    m_ecg_val.m_spire_amp = m_spire_cfg->m_spire_wave_amp;//1	呼吸增益，0～4分别对应×0.25、×0.5、×1、×2、×4
    m_ecg_val.m_ecg_beatrate_src = m_ecg_cfg->m_ecg_beatrate_src;//1	心率来源，0：ECG，1：SPO2，2：自动
    m_ecg_val.m_spire_asp_flag = 0;//1	呼吸窒息标志，0：无窒息，1：有窒息
    m_ecg_val.m_alarm_br_high = m_ecg_cfg->m_alarm_br_high;//2	心率报警上限
    m_ecg_val.m_alarm_br_low = m_ecg_cfg->m_alarm_br_low;//2	心率报警下限
    m_ecg_val.m_alarm_br_en = 1;//1	心率报警开关，1～3分别对应高、中、低级报警
    m_ecg_val.m_reserve0 = 0;//	保留
    m_ecg_val.m_alarm_spr_high = m_spire_cfg->m_alarm_high;//2	呼吸率报警上限
    m_ecg_val.m_alarm_spr_low = m_spire_cfg->m_alarm_low;//2	呼吸率报警下限
    m_ecg_val.m_spire_alarm_en = m_spire_cfg->m_alarm_en;//1	呼吸率报警开关，1～3分别对应高、中、低级报警
    m_ecg_val.m_reserve1 = 0;//	保留
    m_ecg_val.m_alarm_st1_high = m_ecg_cfg->m_alarm_st_high;//4	ST1报警上限，单位0.01mv
    m_ecg_val.m_alarm_st1_low = m_ecg_cfg->m_alarm_st_low;//4	ST1报警下限，单位0.01mv
    m_ecg_val.m_alarm_st1_level = 1;//2	ST1报警级别，1～3分别对应高、中、低级报警
    m_ecg_val.m_alarm_st2_high = m_ecg_cfg->m_alarm_st_high;//4	ST2报警上限，单位0.01mv
    m_ecg_val.m_alarm_st2_low = m_ecg_cfg->m_alarm_st_low;//4	ST2报警下限，单位0.01mv
    m_ecg_val.m_alarm_st2_level = 1;//2	ST2报警级别，1～3分别对应高、中、低级报警
    m_ecg_val.m_alarm_st3_high = m_ecg_cfg->m_alarm_st_high;//4	ST3报警上限，单位0.01mv
    m_ecg_val.m_alarm_st3_low = m_ecg_cfg->m_alarm_st_low;//4	ST3报警下限，单位0.01mv
    m_ecg_val.m_alarm_st3_level = 1;//2	ST3报警级别，1～3分别对应高、中、低级报警
    m_ecg_val.m_alarm_pvc_high = m_ecg_cfg->m_alarm_pvc_high;//2	PVC报警上限
    m_ecg_val.m_alarm_pvc_low = m_ecg_cfg->m_alarm_pvc_low;//2	PVC报警下限
    m_ecg_val.m_alarm_pvc_level;//2	PVC报警级别，1～3分别对应高、中、低级报警
    m_ecg_val.reserve2 = 0;//1	0X00
    m_ecg_val.reserve3 = 0x01;//1	0X01
    m_ecg_val.reserve4 = 0x0f;//1	0X0f
    m_ecg_val.reserve5 = 0xaa;//1	0XAA
///////////////////////////TCP data//////////////////////////////////
    //
    m_ecg_val. m_ecg_arr_type = 0; //心率失常类型
    m_ecg_val. m_ecg_arr_value = -100; //心率失常值
    m_ecg_val. m_para_R_inter = 0;

///////////////////////////TCP data//////////////////////////////////
    //
     m_ecg_arr_type = 0; //心率失常类型
    m_ecg_arr_value = -100; //心率失常值
    m_para_R_inter = 0;

    m_ecg_value[ECG_VAL_FLG_C] =20;//1	20，代表ECG
    m_ecg_value[ECG_VAL_FLG1_C] = 0;//1	0
    for(int i = 0;i<256*3;i++)
    {
        m_ecg_value[ECG_VAL_ECG_WAVE0_C+i] =0;//256×3	3通道ECG波形，每通道长度为256字节
    }
    for(int i = 0;i<128;i++)
    {
        m_ecg_value[ECG_VAL_SPIRE_WAVE_C+i] =0;//128	呼吸波形，长度为128字节
    }

    float vf = -100;
     short vs = -100;
     float *fv = &vf;
     short *sv = &vs;
    // v_100s[0] = v_100short&0xff;
     //v_100s[1] = (v_100short&0xff00)>>8;

    memcpy(m_ecg_value+ECG_VAL_BEATRATE_S,sv,2);//2	心率，-100代表无效值

    memcpy(m_ecg_value+ECG_VAL_SPRATE_S,sv,2);//2	呼吸率，-100代表无效值

    memcpy(m_ecg_value+ECG_VAL_ST1_F,fv,4);//4	ST1，单位0.01mv，-100.00代表无效值

    memcpy(m_ecg_value+ECG_VAL_ST2_F,fv,2);//4	ST2，单位0.01mv，-100.00代表无效值

    memcpy(m_ecg_value+ECG_VAL_ST3_F,fv,2);      //4	ST3，单位0.01mv，-100.00代表无效值

    memcpy(m_ecg_value+ECG_VAL_PVCS_S,sv,2);//2	PVC，-100代表无效值


    m_ecg_value[ECG_VAL_ECGNAME0_C] =m_ecg_cfg->m_ecg_chanel1_lead;//3	3通道ECG 波形名称，1～8对应I、II、III、aVR、aVL、aVF、V、校准
    m_ecg_value[ECG_VAL_AMP0_C] =m_ecg_cfg->m_ecg_amp;//3	3通道ECG增益，1～4对应X0.25、X0.5、X1、X2

    m_ecg_value[ECG_VAL_LAYOUT_C] =0;//1	屏幕布局，0～5分别对应：标准界面、大字体界面、呼吸氧合图界面、血压趋势界面、趋势表界面、全屏多导界面
    m_ecg_value[ECG_VAL_PACEMAKER_C] =0;//1	高4位：起搏开关，0：关，1：开 低4位：陷波开关，0：关，1：开
    m_ecg_value[ECG_VAL_FILTERMOD_C] =m_ecg_cfg->m_ecg_filter_mod;//1	滤波模式，1～3分别对应诊断、监护、手术模式
    m_ecg_value[ECG_VAL_ASPALARM_C] =m_spire_cfg->m_spire_asp_alarm;//1	呼吸窒息时间，0～6分别对应关、10秒、15秒、20秒、25秒、30秒、35秒、40秒
    m_ecg_value[ECG_VAL_SPIREAMP_C] =m_spire_cfg->m_spire_wave_amp;//1	呼吸增益，0～4分别对应×0.25、×0.5、×1、×2、×4
    m_ecg_value[ECG_VAL_BR_RSC_C] =m_ecg_cfg->m_ecg_beatrate_src;//1	心率来源，0：ECG，1：SPO2，2：自动
    m_ecg_value[ECG_VAL_ASPFLG_C] =0;//1	呼吸窒息标志，0：无窒息，1：有窒息

    memcpy(m_ecg_value+ECG_VAL_ALM_BR_H_S,&(m_ecg_cfg->m_alarm_br_high),2);//2	心率报警上限

    memcpy(m_ecg_value+ECG_VAL_ALM_BR_L_S,&(m_ecg_cfg->m_alarm_br_low),2);//2	心率报警下限

    m_ecg_value[ECG_VAL_ALM_BR_EN_C] =1;//1	心率报警开关，1～3分别对应高、中、低级报警
    m_ecg_value[ECG_VAL_RESERV0_C] =0;//	保留
    memcpy(m_ecg_value+ECG_VAL_ALM_SP_H_S,&(m_spire_cfg->m_alarm_high),2);//2	呼吸率报警上限

   memcpy( m_ecg_value+ECG_VAL_ALM_SP_L_S,&(m_spire_cfg->m_alarm_low),2);//2	呼吸率报警下限

    m_ecg_value[ECG_VAL_ALM_SP_EN_C] =m_spire_cfg->m_alarm_en;//1	呼吸率报警开关，1～3分别对应高、中、低级报警
    m_ecg_value[ECG_VAL_RESERV1_C] = 0;//	保留

    memcpy(m_ecg_value+ECG_VAL_ALM_ST1_H_F,&(m_ecg_cfg->m_alarm_st_high),sizeof(float)); //4	ST1报警上限，单位0.01mv

    memcpy(m_ecg_value+ECG_VAL_ALM_ST1_L_F,&(m_ecg_cfg->m_alarm_st_low),sizeof(float));//4	ST1报警下限，单位0.01mv
    m_ecg_value[ECG_VAL_ALM_ST1_LVL_S] = 1;//2	ST1报警级别，1～3分别对应高、中、低级报警

    memcpy(m_ecg_value+ECG_VAL_ALM_ST2_H_F,&(m_ecg_cfg->m_alarm_st_high),4);//4	ST2报警上限，单位0.01mv

    memcpy(m_ecg_value+ECG_VAL_ALM_ST2_L_F,&(m_ecg_cfg->m_alarm_st_low),4);//4	ST2报警下限，单位0.01mv

    m_ecg_value[ECG_VAL_ALM_ST2_LVL_S] =1;//2	ST2报警级别，1～3分别对应高、中、低级报警

    memcpy(m_ecg_value+ECG_VAL_ALM_ST3_H_F,&(m_ecg_cfg->m_alarm_st_high),4);//4	ST3报警上限，单位0.01mv

    memcpy(m_ecg_value+ECG_VAL_ALM_ST3_L_F,&(m_ecg_cfg->m_alarm_st_low),4);//4	ST3报警下限，单位0.01mv

    m_ecg_value[ECG_VAL_ALM_ST3_LVL_S] =1;//2	ST3报警级别，1～3分别对应高、中、低级报警

    memcpy(m_ecg_value+ECG_VAL_ALM_PVC_H_S,&(m_ecg_cfg->m_alarm_pvc_high),2);//2	PVC报警上限

    memcpy(m_ecg_value+ECG_VAL_ALM_PVC_L_S,&( m_ecg_cfg->m_alarm_pvc_low),2);//2	PVC报警下限

    m_ecg_value[ECG_VAL_ALM_PVC_LVL_S] =1;//2	PVC报警级别，1～3分别对应高、中、低级报警
    m_ecg_value[ECG_VAL_RESERV2_C] =0;//1	0X00
    m_ecg_value[ECG_VAL_RESERV3_C] =0x01;//1	0X01
    m_ecg_value[ECG_VAL_RESERV4_C] = 0x0f;//1	0X0f
    m_ecg_value[ECG_VAL_RESERV5_C] =0xaa;//1	0XAA
}

void CEcgModule::f_reset_spo2_value()
{
    m_spo2_val.m_spo2_flg = 21;//1	21，代表SPO2
    m_spo2_val.m_spo2_flg_1 = 1;//1	1
    for(int i = 0; i< 256;i++)
    {
        m_spo2_val.m_spo2_wave[i] = 0;//256	SPO2波形，长度为256字节
    }

    m_spo2_val.m_spo2_value = -100;//2	SpO2，-100代表无效值
    m_spo2_val.m_pulse_rate = -100;//2	脉率，-100代表无效值
    m_spo2_val.m_alarm_spo2_high = m_spo2_cfg->m_alarm_high;//2	SpO2报警上限
    m_spo2_val.m_alarm_spo2_low = m_spo2_cfg->m_alarm_low;//2	SpO2报警下限
    m_spo2_val.m_alarm_spo2_level = 1;//2	SpO2报警级别，1～3分别对应高、中、低级报警
    m_spo2_val.m_alarm_pulserate_high  = m_spo2_cfg->m_alarm_pulserate_high;//2	;//脉率报警上限
    m_spo2_val.m_alarm_pulserate_low = m_spo2_cfg->m_alarm_pulserate_low;//2	;//脉率报警下限
    m_spo2_val.m_alarm_pulserate_level = 1	;//脉率报警级别，1～3分别对应高、中、低级报警
    m_spo2_val.reserve0 = 0;//1	0
    m_spo2_val.reserve1 = 0;//1	0
    m_spo2_val.reserve2 = 1;//1	1
    m_spo2_val.reserve3 = m_spo2_cfg->m_spo2_sensitive;//1	灵敏度，0~2分别对应高、中、低
}

void CEcgModule::f_reset_nibp_value()
{
     m_nibp_val.m_nibp_flg = 22;//1	22，代表无创血压
    m_nibp_val.m_nibp_flg_1 = 1;//1	2
    m_nibp_val.m_nibp_year = 2015;//2	测量时间，年
    m_nibp_val.m_nibp_month = 1;//1	测量时间，月
    m_nibp_val.m_nibp_date = 1;//1	测量时间，日
    m_nibp_val.m_nibp_hour = 0;//1	测量时间，时
    m_nibp_val.m_nibp_min = 0;//1	测量时间，分
    m_nibp_val.m_nibp_sec = 0;//1	测量时间，秒
   m_nibp_val.m_para_nibp_ss = -100;//2	收缩压，单位mmHg
    m_nibp_val.m_para_nibp_sz = -100;//2	舒张压，单位mmHg
    m_nibp_val.m_para_nibp_pj = -100;//2	平均压，单位mmHg

    m_nibp_val.m_alarm_ss_high = m_nibp_cfg->m_alarm_ss_high;//2	收缩压报警上限，单位mmHg
    m_nibp_val.m_alarm_ss_low = m_nibp_cfg->m_alarm_ss_low;//2	收缩压报警下限，单位mmHg
    m_nibp_val.m_alarm_ss_level = 1;//2	收缩压报警级别，1～3分别对应高、中、低级报警
    m_nibp_val.m_alarm_sz_high = m_nibp_cfg->m_alarm_sz_high;//2	舒张压报警上限，单位mmHg
    m_nibp_val.m_alarm_sz_low = m_nibp_cfg->m_alarm_sz_low;//2	舒张压报警下限，单位mmHg
    m_nibp_val.m_alarm_sz_level = 1;//2	舒张压报警级别，1～3分别对应高、中、低级报警
    m_nibp_val.m_alarm_pj_high = m_nibp_cfg->m_alarm_pj_high;//2	平均压报警上限，单位mmHg
    m_nibp_val.m_alarm_pj_low = m_nibp_cfg->m_alarm_pj_low;//2	平均压报警下限，单位mmHg
    m_nibp_val.m_alarm_pj_level = 1;//2	平均压报警级别，1～3分别对应高、中、低级报警
    m_nibp_val.m_nibp_over_flg = 0;//1	无创血压测量结束标志，0：无创血压没有测量；0x55：无创血压测量结束
    m_nibp_val.m_reserve0 = 1;//1	1
    m_nibp_val.m_result_state = 0;//1	无创血压测量状态：
                                    /*
                                    0：等待状态
                                    1：手动测量中；
                                    2：自动测量中；
                                    3：连续测量中；
                                    4：校准中；
                                    5：漏气检测中；
                                    6：复位
                                    10：出错*/
    m_nibp_val.m_nibp_mode = 0;//	无创血压设置：
                                    /*高4位：无创血压测量模式，0：手动测量，1：自动测量；2：连续测量；
                                    低4位：自动测量周期
                                    0：1分钟
                                    1：2分钟
                                    2：3分钟
                                    3：4分钟
                                    4：5分钟
                                    5：10分钟
                                    6：15分钟
                                    7：30分钟
                                    8：60分钟
                                    9：90分钟
                                    10：120分钟
                                    11：180分钟
                                    12：240分钟
                                    13：480分钟*/
    /////////////////////////////////////////////////////////////
    m_nibp_val.m_para_nibp_xiudai = -100; //袖带压值
    m_nibp_val.m_para_pulse_rate = 0;
    //m_nibp_val.m_alarm_nibp_high = ;//报警上限
   // m_nibp_val.m_alarm_nibp_low;//报警下限
    //m_nibp_val.m_mesure_mod; //测量模式，手动，连续，
    //m_nibp_val.m_mesure_interval; //
    m_nibp_val.m_measure_stop_err = 0;
    m_nibp_val.m_state_err = 0;
}

void CEcgModule::f_reset_temp_record_value()
{
    m_temp_val.	m_temp_flg = 23;//1	23，代表体温
    m_temp_val.m_temp_flg_1 = 3;////1	3
    m_temp_val.m_para_temp1 = -100;//4	通道1体温值，单位：0.1℃
    m_temp_val.m_para_temp2 = -100;//4	通道2体温值，单位：0.1℃
    m_temp_val.m_para_temp_dif = -100;////4	温差体温值，单位：0.1℃
    m_temp_val.m_alarm_temp1_high = m_temp_cfg->m_alarm1_high;//4	通道1体温报警上限，单位：0.1℃
    m_temp_val.m_alarm_temp1_low = m_temp_cfg->m_alarm1_low;//4	通道1体温报警下限，单位：0.1℃
    m_temp_val.m_alarm_temp1_level = 1;//2	通道1体温报警级别，1～3分别对应高、中、低级报警
    m_temp_val.m_alarm_temp2_high = m_temp_cfg->m_alarm2_high;//4	通道2体温报警上限，单位：0.1℃
    m_temp_val.m_alarm_temp2_low = m_temp_cfg->m_alarm2_low;//4	通道2体温报警下限，单位：0.1℃
    m_temp_val.m_alarm_temp2_level = 1;//2	通道2体温报警级别，1～3分别对应高、中、低级报警
    m_temp_val.m_alarm_temp_dif_high = 100;//4	温差报警上限，单位：0.1℃
    m_temp_val.m_alarm_temp_dif_low = 35;//4	温差报警下限，单位：0.1℃
    m_temp_val.m_alarm_temp_dif_level = 1;//2	温差报警级别，1～3分别对应高、中、低级报警
    m_temp_val.reserve0 = 1;//1	1
    m_temp_val.m_record_wave_type = 0;//1	高4位：通道2记录波形
                    /*0：ECG1
                    1：ECG2
                    2：脉搏波
                    3：呼吸波
                    低4位：通道1记录波形，定义同上*/
    m_temp_val.m_record_mode = 0;//1	高4位：记录模式，0：8秒，1：连续
                    /*低4位：自动记录间隔
                    0：关闭
                    1：10分钟
                    2：20分钟
                    3：30分钟
                    4：40分钟
                    5：50分钟
                    6：60分钟
                    7：120分钟
                    8：180分钟
                    9：240分钟*/
    m_temp_val.m_record_speed = 0;//1	高4位：记录波形速度，2：25mm/s，3：50mm/s
                    //低4位：记录网格开关，0：关，1：开
}

void CEcgModule::f_plot_ecg_wave_pre(int,int,int)
{

}

void CEcgModule::f_plot_spo2_wave_pre(int)
{

}

void CEcgModule::f_plot_spire_wave_pre(int data)
{

}

void CEcgModule::f_plot_ecg_wave(int data1,int data2,int data3)
{

    double y[7] = {0};
    bool limit_flag = false;
    double dstep = 0;
    QVector<QPointF> tempint;
    if(m_ecg_cfg->m_ecg_chanel1_lead == ECG_MODULE_LEAD_II)
    {
        y[1] = m_ecg_cfg->m_wave_rec[0].height()-data1 * m_ecg_cfg->m_wave_rec[0].height() / 4096;
        y[0] = m_ecg_cfg->m_wave_rec[0].height()-data2 * m_ecg_cfg->m_wave_rec[0].height() / 4096;

    }
    else
    {
        y[0] = m_ecg_cfg->m_wave_rec[0].height()-data1 * m_ecg_cfg->m_wave_rec[0].height() / 4096;
        y[1] = m_ecg_cfg->m_wave_rec[0].height()-data2 * m_ecg_cfg->m_wave_rec[0].height() / 4096;
    }
    y[2] = y[1]-y[0]+m_ecg_cfg->m_wave_rec[0].height()/2;//III = II -1
    y[3] = m_ecg_cfg->m_wave_rec[0].height()-((y[0]+y[1])/2);//AVR=1/2 * (I + II)
    y[4] = m_ecg_cfg->m_wave_rec[0].height()-(y[0]-y[1]/2);//AVL=I - II/2
    y[5] = m_ecg_cfg->m_wave_rec[0].height()-(y[1] - y[0]/2);//AVF=II - I/2
    y[6] = m_ecg_cfg->m_wave_rec[0].height()-(data3 * m_ecg_cfg->m_wave_rec[0].height() / 4096); //v

    //V
    double x=0;

    if(m_ecg_cfg->m_ecg_wave_speed == 0) //12.5mm/s
    {
        x =g_PixPerByte_3_125mm;
    }
    else if(m_ecg_cfg->m_ecg_wave_speed == 1) // 25mm/s
    {
        x = g_PixPerByte_6_25mm;
    }
    else if(m_ecg_cfg->m_ecg_wave_speed == 2) // 50mm/s
    {
        x= g_PixPerByte_12_5mm;
    }
    for(int i = 0;i<ECG_MODULE_WAVE_NUM;i++)
    {
        m_ecg_pos[i] +=x;
        if(m_ecg_pos[i]>= (g_WaveWidgetWidthPix-1))
        {
            m_ecg_pos[i] -= (g_WaveWidgetWidthPix-1);
            limit_flag = true;

        }
    }
    /*
    if(limit_flag == true)
    {
        for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
        {
            if(m_ecg_cfg->m_wave_plot_enable[i])
            {
                tempint.append(QPointF(x,y[i]));
                {
                    //QMutexLocker locker(&m_mutex_wave_ecg);
                    //m_ecg_data_to_draw[i].append(QPointF(m_ecg_pos[i],y[i]));
                    //m_ecg_last_pos[i] = m_ecg_pos[i];
                }
                //g_WavePlotter->setCurveData(m_ecg_cfg->m_wave_indx[i], tempint,0);
                g_drawThread->f_draw_ecg(m_ecg_cfg->m_wave_indx[i], tempint,0);
                tempint.clear();
            }
            m_ecg_last_pos[i] = m_ecg_pos[i];
        }
    }

    if(m_ecg_pos[0] >= (m_ecg_last_pos[0] +1))//plot 1 pix,do not plot if less than 1pix.
    {

        //double x = m_ecg_pos[0] - m_ecg_last_pos[0];
        for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
        {
            if(m_ecg_cfg->m_wave_plot_enable[i])
            {

                tempint.append(QPointF(x,y[i]));
                {
                    //QMutexLocker locker(&m_mutex_wave_ecg);
                    //m_ecg_data_to_draw[i].append(QPointF(m_ecg_pos[i],y[i]));
                    ///m_ecg_last_pos[i] = m_ecg_pos[i];
                }
                //g_WavePlotter->setCurveData(m_ecg_cfg->m_wave_indx[i], tempint,m_ecg_pos[i]);
                g_drawThread->f_draw_ecg(m_ecg_cfg->m_wave_indx[i], tempint,m_ecg_pos[i]);
                tempint.clear();
            }
            m_ecg_last_pos[i] = m_ecg_pos[i];
        }
    }*/

    if(m_ecg_pos[0] >= (m_ecg_last_pos[0]))//plot 1 pix,do not plot if less than 1pix.
    {
        dstep = m_ecg_pos[0] - m_ecg_last_pos[0];
    }
    else
    {
        dstep = m_ecg_pos[0] +g_WaveWidgetWidthPix- m_ecg_last_pos[0];
    }
    if(dstep >=1)
    {
        //double x = m_ecg_pos[0] - m_ecg_last_pos[0];
        for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
        {
            if(m_ecg_cfg->m_wave_plot_enable[i])
            {

                tempint.append(QPointF(dstep,y[i]));
                {
                    //QMutexLocker locker(&m_mutex_wave_ecg);
                    //m_ecg_data_to_draw[i].append(QPointF(m_ecg_pos[i],y[i]));
                    ///m_ecg_last_pos[i] = m_ecg_pos[i];
                }
                //g_WavePlotter->setCurveData(m_ecg_cfg->m_wave_indx[i], tempint,m_ecg_pos[i]);
                g_drawThread->f_draw_ecg(m_ecg_cfg->m_wave_indx[i], tempint,m_ecg_pos[i]);
                tempint.clear();
            }
            m_ecg_last_pos[i] = m_ecg_pos[i];
        }
    }

}

void CEcgModule::f_read_data()
{
    if(m_ecg_cfg->m_dara_src == ECG_MODULE_DATA_SRC_PORT)
    {
        QByteArray data =   m_port->readAll();



        /*data.clear();
        data.append(ecgdata,1024);*/

/*        data.clear();
        char ecg[9] = {0x05,0x80,0x88,0x80,0x88,0x80,0x88,0x80,0x9d};
        data.append(ecg,9);*/
        f_parse_0803_com_data(data);
        {
            QMutexLocker locker(&m_mutex_tcp);
            //m_modu_data_raw .append(data);
        }
        //emit signal_setpanels_value(pMainForm->TextLabel_bar_alarm_III,data.count());

        //QDataStream inout(&m_modu_data_file);
        //inout.writeRawData((char *)data.data(),data.count());
        //m_modu_data_file.flush();

    }
    else if(m_ecg_cfg->m_dara_src == ECG_MODULE_DATA_SRC_FILE)
    {

    }
}
QByteArray CEcgModule::f_prepare_tcp_data(char *paradata,int type)
{
    /*
    {
        QMutexLocker locker(&m_mutex_tcp);
        data->append(m_modu_data_raw);
        m_modu_data_raw.clear();
    }*/
    QByteArray dat;
    if(type == 1)//ecg+spire
    {
        stEcgValue *val = (stEcgValue *)paradata;
        char tmp[981] = {0};

        tmp[ECG_VAL_FLG_C] =20;//1	20，代表ECG
        tmp[ECG_VAL_FLG1_C] = 0;//1	0

        memcpy(tmp+ECG_VAL_ECG_WAVE0_C,&(val->m_ecg_wave_data),768);

        memcpy(tmp+ECG_VAL_SPIRE_WAVE_C,&(val->m_spire_wave_data),128);

        memcpy(tmp+ECG_VAL_BEATRATE_S,&(val->m_para_beat_rate),2);//2	心率，-100代表无效值

        memcpy(tmp+ECG_VAL_SPRATE_S,&(val->m_para_ecg_spr),2);//2	呼吸率，-100代表无效值

        memcpy(tmp+ECG_VAL_ST1_F,&(val->m_para_st1),4);//4	ST1，单位0.01mv，-100.00代表无效值

        memcpy(tmp+ECG_VAL_ST2_F,&(val->m_para_st2),2);//4	ST2，单位0.01mv，-100.00代表无效值

        memcpy(tmp+ECG_VAL_ST3_F,&(val->m_para_st3),2);      //4	ST3，单位0.01mv，-100.00代表无效值

        memcpy(tmp+ECG_VAL_PVCS_S,&(val->m_para_pvcs),2);//2	PVC，-100代表无效值


        tmp[ECG_VAL_ECGNAME0_C] =m_ecg_cfg->m_ecg_chanel1_lead;//3	3通道ECG 波形名称，1～8对应I、II、III、aVR、aVL、aVF、V、校准
        tmp[ECG_VAL_AMP0_C] =m_ecg_cfg->m_ecg_amp;//3	3通道ECG增益，1～4对应X0.25、X0.5、X1、X2

        tmp[ECG_VAL_LAYOUT_C] =g_LayoutModule->m_layout_cfg->m_layout_type;//1	屏幕布局，0～5分别对应：标准界面、大字体界面、呼吸氧合图界面、血压趋势界面、趋势表界面、全屏多导界面
        tmp[ECG_VAL_PACEMAKER_C] =(m_ecg_cfg->m_ecg_pacemaker_enable<<4)||
                (m_ecg_cfg->m_ect_pwr_supression_enable);//1	高4位：起搏开关，0：关，1：开 低4位：陷波开关，0：关，1：开

        tmp[ECG_VAL_FILTERMOD_C] =m_ecg_cfg->m_ecg_filter_mod;//1	滤波模式，1～3分别对应诊断、监护、手术模式
        tmp[ECG_VAL_ASPALARM_C] =m_spire_cfg->m_spire_asp_alarm;//1	呼吸窒息时间，0～6分别对应关、10秒、15秒、20秒、25秒、30秒、35秒、40秒
        tmp[ECG_VAL_SPIREAMP_C] =m_spire_cfg->m_spire_wave_amp;//1	呼吸增益，0～4分别对应×0.25、×0.5、×1、×2、×4
        tmp[ECG_VAL_BR_RSC_C] =m_ecg_cfg->m_ecg_beatrate_src;//1	心率来源，0：ECG，1：SPO2，2：自动
        tmp[ECG_VAL_ASPFLG_C] =m_spire_val.m_alarm_asp;//1	呼吸窒息标志，0：无窒息，1：有窒息

        memcpy(m_ecg_value+ECG_VAL_ALM_BR_H_S,&(m_ecg_cfg->m_alarm_br_high),2);//2	心率报警上限

        memcpy(m_ecg_value+ECG_VAL_ALM_BR_L_S,&(m_ecg_cfg->m_alarm_br_low),2);//2	心率报警下限

        tmp[ECG_VAL_ALM_BR_EN_C] =1;//1	心率报警开关，1～3分别对应高、中、低级报警
        tmp[ECG_VAL_RESERV0_C] =0;//	保留
        memcpy(tmp+ECG_VAL_ALM_SP_H_S,&(m_spire_cfg->m_alarm_high),2);//2	呼吸率报警上限

       memcpy( tmp+ECG_VAL_ALM_SP_L_S,&(m_spire_cfg->m_alarm_low),2);//2	呼吸率报警下限

        tmp[ECG_VAL_ALM_SP_EN_C] =m_spire_cfg->m_alarm_en;//1	呼吸率报警开关，1～3分别对应高、中、低级报警
        tmp[ECG_VAL_RESERV1_C] = 0;//	保留

        memcpy(tmp+ECG_VAL_ALM_ST1_H_F,&(m_ecg_cfg->m_alarm_st_high),sizeof(float)); //4	ST1报警上限，单位0.01mv

        memcpy(tmp+ECG_VAL_ALM_ST1_L_F,&(m_ecg_cfg->m_alarm_st_low),sizeof(float));//4	ST1报警下限，单位0.01mv
        tmp[ECG_VAL_ALM_ST1_LVL_S] = 1;//2	ST1报警级别，1～3分别对应高、中、低级报警

        memcpy(tmp+ECG_VAL_ALM_ST2_H_F,&(m_ecg_cfg->m_alarm_st_high),4);//4	ST2报警上限，单位0.01mv

        memcpy(tmp+ECG_VAL_ALM_ST2_L_F,&(m_ecg_cfg->m_alarm_st_low),4);//4	ST2报警下限，单位0.01mv

        tmp[ECG_VAL_ALM_ST2_LVL_S] =1;//2	ST2报警级别，1～3分别对应高、中、低级报警

        memcpy(tmp+ECG_VAL_ALM_ST3_H_F,&(m_ecg_cfg->m_alarm_st_high),4);//4	ST3报警上限，单位0.01mv

        memcpy(tmp+ECG_VAL_ALM_ST3_L_F,&(m_ecg_cfg->m_alarm_st_low),4);//4	ST3报警下限，单位0.01mv

        tmp[ECG_VAL_ALM_ST3_LVL_S] =1;//2	ST3报警级别，1～3分别对应高、中、低级报警

        memcpy(tmp+ECG_VAL_ALM_PVC_H_S,&(val->m_alarm_pvc_high),2);//2	PVC报警上限

        memcpy(tmp+ECG_VAL_ALM_PVC_L_S,&( val->m_alarm_pvc_low),2);//2	PVC报警下限

        tmp[ECG_VAL_ALM_PVC_LVL_S] =1;//2	PVC报警级别，1～3分别对应高、中、低级报警
        tmp[ECG_VAL_RESERV2_C] =0;//1	0X00
        tmp[ECG_VAL_RESERV3_C] =0x01;//1	0X01
        tmp[ECG_VAL_RESERV4_C] = 0x0f;//1	0X0f
        tmp[ECG_VAL_RESERV5_C] =0xaa;//1	0XAA
        dat.append(tmp,981);
    }
    else if(type == 2)//spo2
    {


        stSpo2Value *val = (stSpo2Value *)paradata;
        char temp[278] = {0};
    temp[ SPO2_VAL_FLG_C] = 21;//1	21，代表SPO2
    temp[ SPO2_VAL_FLG1_C] = 1;
    memcpy(temp+SPO2_VAL_WAVE_C,val->m_spo2_wave,256);
    memcpy(temp+ SPO2_VAL_VALUE_S,&val->m_spo2_value,sizeof(short));
   memcpy( temp+ SPO2_VAL_PULSE_S,&val->m_pulse_rate,sizeof(short));
    memcpy(temp+ SPO2_VAL_ALM_H_S,&val->m_alarm_spo2_high,sizeof(short));
    memcpy(temp+ SPO2_VAL_ALM_L_S,&val->m_alarm_spo2_low,sizeof(short));
   memcpy( temp+ SPO2_VAL_ALM_LVL_S,&val->m_alarm_spo2_level,sizeof(short));
    memcpy(temp+SPO2_VAL_ALM_PULSE_H_S,&val->m_alarm_pulserate_high,sizeof(short));
    memcpy(temp+ SPO2_VAL_ALM_PULSE_L_S,&val->m_alarm_pulserate_low,sizeof(short));
    memcpy(temp+SPO2_VAL_ALM_PULSE_LVL_S,&val->m_alarm_pulserate_level ,sizeof(short));
    temp[ SPO2_VAL_RES0_C] = 0;
    temp[ SPO2_VAL_RES1_C] = 0;
    temp[ SPO2_VAL_RES2_C] = 1;
    temp[ SPO2_VAL_RES3_C] = m_spo2_cfg->m_spo2_sensitive;//
    dat.append(temp,278);
    }
    else if(type == 3)//nibp
    {
        stNibpValue *val = (stNibpValue *)paradata;
        char temp[48] = {0};
        temp[ NIBP_VAL_FLG_C] = 22;//1	22，代表无创血压
        temp[ NIBP_VAL_FLG1_C] = 2;//1	2
        memcpy(temp+ NIBP_VAL_YEAR_S,&(val->m_nibp_year),sizeof(short));
        temp[ NIBP_VAL_MONTH_C] = val->m_nibp_month;
        temp[ NIBP_VAL_DATE_C] = val->m_nibp_date;
        temp[ NIBP_VAL_HOUR_C] = val->m_nibp_hour;
        temp[ NIBP_VAL_MIN_C] = val->m_nibp_min;
        temp[ NIBP_VAL_SEC_C] = val->m_nibp_sec;
        memcpy(temp+ NIBP_VAL_SS_S, &(val->m_para_nibp_ss),sizeof(short));
        memcpy(temp+ NIBP_VAL_SZ_S,&(val->m_para_nibp_sz),sizeof(short));
        memcpy(temp+ NIBP_VAL_PJ_S,&(val->m_para_nibp_pj),sizeof(short));
        memcpy(temp+ NIBP_VAL_ALM_SS_H_S,&(val->m_alarm_ss_high),sizeof(short));
        memcpy(temp+ NIBP_VAL_ALM_SS_L_S,&(val->m_alarm_ss_low),sizeof(short));
        memcpy(temp+ NIBP_VAL_ALM_SS_LVL_S,&(val->m_alarm_ss_level),sizeof(short));
        memcpy(temp+ NIBP_VAL_ALM_SZ_H_S,&(val->m_alarm_sz_high),sizeof(short));
        memcpy(temp+ NIBP_VAL_ALM_SZ_L_S,&(val->m_alarm_sz_low),sizeof(short));
        memcpy(temp+ NIBP_VAL_ALM_SZ_LVL_S,&(val->m_alarm_sz_level),sizeof(short));
        memcpy(temp+ NIBP_VAL_ALM_PJ_H_S,&(val->m_alarm_pj_high),sizeof(short));
        memcpy(temp+ NIBP_VAL_ALM_PJ_L_S,&(val->m_alarm_pj_low),sizeof(short));
        memcpy(temp+ NIBP_VAL_ALM_PJ_LVL_S,&(val->m_alarm_pj_level),sizeof(short));
        temp[ NIBP_VAL_FINISH_FLG_C] = val->m_nibp_over_flg;
        temp[ NIBP_VAL_RES0_C] =1;
        temp[ NIBP_VAL_STAT_C] = val->m_result_state;

        temp[ NIBP_VAL_SET_C] = val->m_nibp_mode;
        dat.append(temp,48);
    }
    else if(type == 4)//temp +record
    {
        stTempValue *val = (stTempValue *)paradata;
        char temp[48] = {0};
    temp[ TEMP_VAL_FLG_C] =val->m_temp_flg;
    temp[ TEMP_VAL_FLG1_C] = val->m_temp_flg_1;
    memcpy(temp+TEMP_VAL_T1_F,&(val->m_para_temp1),sizeof(float));
     memcpy(temp+ TEMP_VAL_T2_F,&(val->m_para_temp2),sizeof(float));
     memcpy(temp+ TEMP_VAL_DIF_F,&(val->m_para_temp_dif),sizeof(float));
     memcpy(temp+ TEMP_VAL_ALM_T1_H_F,&(val->m_alarm_temp1_high),sizeof(float));
     memcpy(temp+ TEMP_VAL_ALM_T1_L_F,&(val->m_alarm_temp1_low),sizeof(float));
     memcpy(temp+ TEMP_VAL_ALM_T1_LVL_S,&(val->m_alarm_temp1_level),sizeof(short));
     memcpy(temp+ TEMP_VAL_ALM_T2_H_F,&(val->m_alarm_temp2_high),sizeof(float));
     memcpy(temp+ TEMP_VAL_ALM_T2_L_F,&(val->m_alarm_temp2_low),sizeof(float));
     memcpy(temp+ TEMP_VAL_ALM_T2_LVL_S,&(val->m_alarm_temp2_level),sizeof(short));
     memcpy(temp+ TEMP_VAL_ALM_DIF_H_F,&(val->m_alarm_temp_dif_high),sizeof(float));
    memcpy( temp+ TEMP_VAL_ALM_DIF_L_F,&(val->m_alarm_temp_dif_low ),sizeof(float));
     memcpy(temp+ TEMP_VAL_ALM_DIF_LVL_S,&(val->m_alarm_temp_dif_level),sizeof(short));
    temp[ TEMP_VAL_RES0_C] =val->reserve0;
    temp[ TEMP_VAL_RCDCH1_WAVETYPE_C] = val->m_record_wave_type;
    temp[ TEMP_VAL_RCDCH2_WAVETYPE_C] = val->m_record_mode;
    temp[ TEMP_VAL_RCD_SET_SPD_GRID_C] = val->m_record_speed;
    dat.append(temp,48);
    }
    return dat;
}

void CEcgModule::f_parse_data()
{

}

void CEcgModule::f_set_ecg_cfg(CEcgModuleCfg cfg)
{
    memcpy(m_ecg_cfg,&cfg,sizeof(cfg));
    QFile file(ECG_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_ecg_cfg,sizeof(CEcgModuleCfg));
    file.close();
    memcpy(m_ecg_value+ECG_VAL_ALM_BR_H_S,&m_ecg_cfg->m_alarm_br_high,sizeof(m_ecg_cfg->m_alarm_br_high));
    memcpy(m_ecg_value+ECG_VAL_ALM_BR_L_S,&m_ecg_cfg->m_alarm_br_low,sizeof(m_ecg_cfg->m_alarm_br_low));

    //m_ecg_val.m_alarm_br_high = m_ecg_cfg->m_alarm_br_high;
    //m_ecg_val.m_alarm_br_low = m_ecg_cfg->m_alarm_br_low;

}
void CEcgModule::f_setDefaultCfg()
{
    f_set_ecg_def_cfg();
    f_set_spo2_def_cfg();
    f_set_nibp_def_cfg();
    f_set_temp_def_cfg();
    f_set_spire_def_cfg();
}

void CEcgModule::f_get_ecg_cfg(CEcgModuleCfg *pCfg)
{

    memcpy(pCfg,m_ecg_cfg,sizeof(CEcgModuleCfg));
    /*
    pCfg->m_module_enable =  m_ecg_cfg->m_module_enable ;//true = module enable;
    for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
    {
       pCfg->m_wave_color[i] =  m_ecg_cfg->m_wave_color[i] ; // wave color
    }
    pCfg->m_panel_color = m_ecg_cfg->m_panel_color ;//para color
    pCfg->m_ecg_wave_speed=m_ecg_cfg->m_ecg_wave_speed ; //6.25mm/s *N

    pCfg->m_dara_src = m_ecg_cfg->m_dara_src ; //where data from:file or serial port;

    //pCfg->m_data_src_file_name = m_ecg_cfg->m_data_src_file_name;

    //port para
   pCfg->m_serial_port_cfg.BaudRate = m_ecg_cfg->m_serial_port_cfg.BaudRate ;
   pCfg->m_serial_port_cfg.DataBits = m_ecg_cfg->m_serial_port_cfg.DataBits ;
   pCfg->m_serial_port_cfg.FlowControl = m_ecg_cfg->m_serial_port_cfg.FlowControl ;
   pCfg->m_serial_port_cfg.Parity = m_ecg_cfg->m_serial_port_cfg.Parity ;
   pCfg->m_serial_port_cfg.StopBits = m_ecg_cfg->m_serial_port_cfg.StopBits ;

    pCfg->m_serial_port_num  = m_ecg_cfg->m_serial_port_num ; //searial port number
    //pCfg->m_serial_port_name = m_ecg_cfg->m_serial_port_name ; //serial port name

    //alarm
    pCfg->m_para_alarm_en = m_ecg_cfg->m_para_alarm_en ; //true = para alarm enable flg enable
    pCfg->m_tech_alarm_en = m_ecg_cfg->m_tech_alarm_en  ; // true = tech alarm enbale flag enable

    //wave
     pCfg->m_wave_num = m_ecg_cfg->m_wave_num ; //module has n waves to draw;
     pCfg->m_ecg_chanel1_lead = m_ecg_cfg->m_ecg_chanel1_lead ;//通道导联
     pCfg->m_ecg_chanel2_lead = m_ecg_cfg->m_ecg_chanel2_lead ;
     pCfg->m_ecg_chanel3_lead = m_ecg_cfg->m_ecg_chanel3_lead ;
     pCfg->m_ecg_amp = m_ecg_cfg->m_ecg_amp ;
     pCfg->m_ect_pwr_supression_enable = m_ecg_cfg->m_ect_pwr_supression_enable ;
     pCfg->m_ecg_lead_style = m_ecg_cfg->m_ecg_lead_style ;
     pCfg->m_ecg_pacemaker_enable = m_ecg_cfg->m_ecg_pacemaker_enable;
     pCfg->m_ecg_filter_mod = m_ecg_cfg->m_ecg_filter_mod ;
     pCfg->m_ecg_pulse_vol  = m_ecg_cfg->m_ecg_pulse_vol ;
     pCfg->m_ecg_beatrate_src = m_ecg_cfg->m_ecg_beatrate_src ;
     pCfg->m_ecg_wave_speed = m_ecg_cfg->m_ecg_wave_speed ; //6.25mm/s *(N+1)
     pCfg->m_ecg_st_enable = m_ecg_cfg->m_ecg_st_enable ;
     pCfg->m_ecg_pvcs_enbale = m_ecg_cfg->m_ecg_pvcs_enbale ;
    */
}

void CEcgModule::f_Enable(bool bEnable)
{
    m_ecg_cfg->m_module_enable = bEnable;
}

void CEcgModule::f_isEnabled(bool *bEnalbe)
{
    *bEnalbe = m_ecg_cfg->m_module_enable;
}
int  CEcgModule::f_open_data_src()
{
    if(m_ecg_cfg->m_dara_src == ECG_MODULE_DATA_SRC_PORT)
    {
        //open serial port
        //if(!m_ecg_cfg->m_serial_port_name.isEmpty()) //open serial port
        {
            m_port = new Posix_QextSerialPort(ECG_MODULE_DATA_PORT_NAME);
        }
        //else
        //{
        //    return -1;
        //}
    }
    else if(m_ecg_cfg->m_dara_src == ECG_MODULE_DATA_SRC_FILE)
    {
        //if(!m_ecg_cfg->m_data_src_file_name.isEmpty())
        {
            m_data_src_file = new QFile(ECG_MODULE_DATA_FILE_NAME);
            if(!m_data_src_file)
                return -1;
        }
        //else
        //{
        //    return -1;
        //}
    }
    return -1;
}

void CEcgModule::f_close_data_src()
{
     if(m_ecg_cfg->m_dara_src == ECG_MODULE_DATA_SRC_PORT)
     {
         m_port->close();
     }
     else if(m_ecg_cfg->m_dara_src == ECG_MODULE_DATA_SRC_FILE)
     {
         m_data_src_file->close();
     }

}
void CEcgModule::f_set_ecg_wave_color(int wavechanel, int colornum)
{
    if(wavechanel > ECG_MODULE_WAVE_NUM)return;
    g_WavePlotter->setWaveColor(m_ecg_cfg->m_wave_indx[wavechanel],
                                GLB_COLOR(colornum));

    m_ecg_cfg->m_wave_color[wavechanel] = colornum;
    f_set_ecg_cfg(*m_ecg_cfg);
}

void CEcgModule::f_set_ecg_def_cfg()
{
    m_ecg_cfg->m_module_enable = true;//true = module enable;
    for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
    {
        m_ecg_cfg->m_wave_color[i] = GLB_COLOR_RED; // wave color
        m_ecg_cfg->m_wave_rec[i].setRect(0,50*i+400,730,48);
        m_ecg_cfg->m_wave_plot_enable[i] = true;
        m_ecg_cfg->m_wave_indx[i] = 0;
        m_ecg_pos[i] = 0;
        m_ecg_last_pos[i] = 0; //
    }

    m_ecg_cfg->m_ecg_para_enable = true;
    m_ecg_cfg->m_panel_color = GLB_COLOR_RED;//para color
    m_ecg_cfg->m_ecg_wave_speed = 2; //6.25mm/s *N

    m_ecg_cfg->m_dara_src = ECG_MODULE_DATA_SRC_PORT; //where data from:file or serial port;

    //m_ecg_cfg->m_data_src_file_name = ECG_MODULE_DATA_FILE_NAME;

    //port para
   m_ecg_cfg->m_serial_port_cfg.BaudRate = BAUD115200;
   m_ecg_cfg->m_serial_port_cfg.DataBits = DATA_8;
   m_ecg_cfg->m_serial_port_cfg.FlowControl = FLOW_OFF;
   m_ecg_cfg->m_serial_port_cfg.Parity = PAR_NONE;
   m_ecg_cfg->m_serial_port_cfg.StopBits = STOP_1;

    m_ecg_cfg->m_serial_port_num = 0; //searial port number
    //m_ecg_cfg->m_serial_port_name = ECG_MODULE_DATA_PORT_NAME; //serial port name

    //alarm
    m_ecg_cfg->m_para_alarm_en = true; //true = para alarm enable flg enable
    m_ecg_cfg->m_tech_alarm_en  = true; // true = tech alarm enbale flag enable

    //wave
     m_ecg_cfg->m_wave_num = ECG_MODULE_WAVE_NUM; //module has n waves to draw;
     m_ecg_cfg->m_ecg_chanel1_lead = ECG_MODULE_LEAD_II;//通道导联
     m_ecg_cfg->m_ecg_chanel2_lead = ECG_MODULE_LEAD_I;
     m_ecg_cfg->m_ecg_chanel3_lead = ECG_MODULE_LEAD_III;
     m_ecg_cfg->m_ecg_amp = 0;
     m_ecg_cfg->m_ect_pwr_supression_enable = true;
     m_ecg_cfg->m_ecg_lead_style = ECG_MODULE_LEAD_MOD_5;
     m_ecg_cfg->m_ecg_pacemaker_enable = true;
     m_ecg_cfg->m_ecg_filter_mod = ECG_MODULE_FILTER_MOD_CARE;
     m_ecg_cfg->m_ecg_pulse_vol = 1;
     m_ecg_cfg->m_ecg_beatrate_src = ECG_MODULE_BEATRATE_SRC_ECG;
     m_ecg_cfg->m_ecg_wave_speed = 2; //6.25mm/s *(N+1)
     m_ecg_cfg->m_ecg_st_enable = true;
     m_ecg_cfg->m_ecg_pvcs_enbale = true;
     m_ecg_cfg->m_ecg_correct = true;
     m_ecg_cfg->m_patinet_info = 0;

     m_ecg_cfg->m_alarm_br_en  = false;

     //m_ecg_val.m_alarm_br_high = m_ecg_cfg->m_alarm_br_high = 90;
     //m_ecg_val.m_alarm_br_low = m_ecg_cfg->m_alarm_br_low = 40;
     memcpy(m_ecg_value+ECG_VAL_ALM_BR_H_S,&m_ecg_cfg->m_alarm_br_high,sizeof(m_ecg_cfg->m_alarm_br_high));
     memcpy(m_ecg_value+ECG_VAL_ALM_BR_L_S,&m_ecg_cfg->m_alarm_br_low,sizeof(m_ecg_cfg->m_alarm_br_low));

    m_ecg_cfg->m_alarm_st_en = false;
    m_ecg_cfg->m_alarm_st_high = 0;
    m_ecg_cfg->m_alarm_st_low = 0;
}

void CEcgModule::f_set_spo2_def_cfg()
{
    m_spo2_cfg->m_module_enable = true;
    m_spo2_cfg->m_spo2_pulse_vol = 0;
    m_spo2_cfg->m_spo2_sensitive = 0 ;
    m_spo2_cfg->m_spo2_wave_speed = 0;
    m_spo2_cfg->m_spo2_pulse_enable = 1;
    m_spo2_cfg->m_spo2_wave_type = 0;
    m_spo2_cfg->m_spo2_pulse_modulate = 0;
    m_spo2_cfg->m_wave_enable = true;
    m_spo2_cfg->m_wave_color = GLB_COLOR_SKYBLUE; // wave color
    m_spo2_cfg->m_panel_color = GLB_COLOR_SKYBLUE;
    m_spo2_cfg->m_wave_rec.setRect(0,32,730,696);
    m_spo2_cfg->m_wave_indx = 0;
    m_spo2_cfg->m_spo2_para_enable = true;

    m_spo2_cfg->m_alram_en = true;
    m_spo2_val.m_alarm_spo2_high = m_spo2_cfg->m_alarm_high = 100;
    m_spo2_val.m_alarm_spo2_low = m_spo2_cfg->m_alarm_low = 90;
    m_spo2_pos = 0;
    m_spo2_last_pos = 0;
}
void CEcgModule::f_set_spo2_wave_color(int color)
{
    g_WavePlotter->setWaveColor(m_spo2_cfg->m_wave_indx,GLB_COLOR(color));

    m_spo2_cfg->m_wave_color = color;
    f_set_spo2_cfg(*m_spo2_cfg);
}

void CEcgModule::f_set_spo2_cfg(CSpo2ModuleCfg cfg)
{
    memcpy(m_spo2_cfg,&cfg,sizeof(CSpo2ModuleCfg));
    QFile file((SPO2_MODULE_CFG_DOC));
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_spo2_cfg,sizeof(CSpo2ModuleCfg));
    file.close();
    m_spo2_val.m_alarm_spo2_high = m_spo2_cfg->m_alarm_high;
    m_spo2_val.m_alarm_spo2_low = m_spo2_cfg->m_alarm_low;
}
void CEcgModule::f_get_spo2_cfg(CSpo2ModuleCfg *cfg)
{
    memcpy(cfg,m_spo2_cfg,sizeof(CSpo2ModuleCfg));

}
void CEcgModule::f_plot_spire_wave(int data)
{

    double y = 0;
    bool limit_flag = false;
    double dstep = 0;
    QVector<QPointF> tempint;

    y = m_spire_cfg->m_wave_rec.height()-data * m_spire_cfg->m_wave_rec.height() / 256; //

    //V
    double x=0;
    if(m_spire_cfg->m_spire_wave_speed == 0) //6.25mm/s
    {
       x = g_PixPerByte_25mm;
    }
    else if(m_spire_cfg->m_spire_wave_speed == 1) // 12.5mm/s
    {
         x = 0.3181818;//1*730/(500*17.6); // (730[pix]/220[mm])* 12.5[mm/s] / (125[Byte/s]) = pix/Byte
    }
    else if(m_spire_cfg->m_spire_wave_speed == 2) // 25mm/s
    {
        x = 0.66363636;//1*730/(125*8.8);
    }

    m_spire_pos +=x;
    if(m_spire_pos>= (g_WaveWidgetWidthPix-1))
    {
        m_spire_pos -= (g_WaveWidgetWidthPix-1);
        limit_flag = true;

    }

/*
    if(limit_flag == true)
    {
        if(m_spire_cfg->m_wave_enable)
        {
            tempint.append(QPointF(x,y));
            //g_WavePlotter->setCurveData(m_spire_cfg->m_wave_indx,tempint,0);
            g_drawThread->f_draw_spire(m_spire_cfg->m_wave_indx,tempint,0);
            tempint.clear();

        }
        m_spire_last_pos = m_spire_pos;
        //m_spire_last_pos = 0;

    }
    if(m_spire_pos >= (m_spire_last_pos +1))//plot 1 pix,do not plot if less than 1pix.
    {

        if(m_spire_cfg->m_wave_enable)
        {
            tempint.append(QPointF(x,y));
            //QMutexLocker locker(&m_mutex_wave_spire);
            //m_spire_data_to_draw.append(QPointF(m_spire_pos,y));
           // g_WavePlotter->setCurveData(m_spire_cfg->m_wave_indx, tempint,m_spire_pos);
            g_drawThread->f_draw_spire(m_spire_cfg->m_wave_indx, tempint,m_spire_pos);
            tempint.clear();
        }
        m_spire_last_pos = m_spire_pos;

    }
 */
    if(m_spire_pos >= m_spire_last_pos)
    {
        dstep = m_spire_pos - m_spire_last_pos;
    }
    else
    {
        dstep = m_spire_pos + g_WaveWidgetWidthPix - m_spire_last_pos;
    }
    if(dstep >=1)
    {
        if(m_spire_cfg->m_wave_enable)
        {
            tempint.append(QPointF(dstep,y));
            //QMutexLocker locker(&m_mutex_wave_spire);
            //m_spire_data_to_draw.append(QPointF(m_spire_pos,y));
           // g_WavePlotter->setCurveData(m_spire_cfg->m_wave_indx, tempint,m_spire_pos);
            g_drawThread->f_draw_spire(m_spire_cfg->m_wave_indx, tempint,m_spire_pos);
            tempint.clear();
        }
        m_spire_last_pos = m_spire_pos;
    }


/*    for(int i=0; i<data.count();i++)
    {
        if(m_spo2_data_to_draw.size()<8200)
        {
            m_spo2_data_to_draw.append(QPointF(m_spo_draw_pos,data[i]));
        }
        else
        {
            m_spo2_data_to_draw[m_spo_draw_pos] = QPointF(m_spo_draw_pos,data[i]);
        }
        m_spo_draw_pos++;
        if(m_spo_draw_pos >=8200)
        {
            m_spo_draw_pos = 0;
        }
    }*/


  /*     for(int j=0;j<data.count();j++)
    {
     double dx = data[j].x() - m_spo2_wave_plot_set->minX;
        double dy = data[j].y() - m_spo2_wave_plot_set->minY;
        double x = 0 + (dx );
        double y = (50-1) - (dy * (50 - 1)
                                       / 100);
        if(y>(50-1)) //边界线
        {
            y = (50-1);
        }
        tempint.append(QPointF(x,y));
    }*/


    //
    /*
    QMap<int, QVector<QPointF> > datamap;
    for(int i = 0;i<16;i++)
    {
        for(int j=0;j<data.count();j++)
        {
            double x= data[j].x();
            double y = data[j].y();
            tempint.append(QPointF(x,y));
        }
        datamap[i] = tempint;
        g_WavePlotter->setCurveData(i, tempint,dfPos);

        tempint.clear();
    }*/
    //m_spo2_wave_plot->setCurveDatas(data.count(),datamap,dfPos);

/*
    m_spo2_wave_plot->setCurveData(0, tempint,dfPos);
    m_spo2_wave_plot->setCurveData(1, tempint,dfPos);
    m_spo2_wave_plot->setCurveData(2, tempint,dfPos);
    m_spo2_wave_plot->setCurveData(3, tempint,dfPos);
    m_spo2_wave_plot->setCurveData(4, tempint,dfPos);
    m_spo2_wave_plot->setCurveData(5, tempint,dfPos);
    */
/*
    if(iStoptest++ >=700)iStoptest = 0;
    if(m_spo2_cfg->m_wave_enable)
        m_spo2_wave_plot->setCurveData(0, data,iStoptest);*/
}
void CEcgModule::f_set_ecg_wave_layout()
{
    /*
    for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
    {
        if(m_ecg_cfg->m_wave_plot_enable[i] == true)
        {
            m_wave_plot[i]->setGeometry(m_ecg_cfg->m_wave_rec[i]);//();
        }
    }*/
    for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
    {
        if(m_ecg_cfg->m_wave_plot_enable[i] == true)
        {
            g_WavePlotter->setWaveColor(m_ecg_cfg->m_wave_indx[i],
                                        GLB_COLOR(m_ecg_cfg->m_wave_color[i]));

        }
        m_ecg_pos[i]=m_ecg_last_pos[i] = 0;
    }
    if(m_ecg_cfg->m_wave_plot_enable[0])
    {
        g_WavePlotter->setWaveName(m_ecg_cfg->m_wave_indx[0],"ECG I",
                m_ecg_cfg->m_wave_rec[0].y(),m_ecg_cfg->m_wave_rec[0].height());
    }

    if(m_ecg_cfg->m_wave_plot_enable[1])
    g_WavePlotter->setWaveName(m_ecg_cfg->m_wave_indx[1],"ECG II",m_ecg_cfg->m_wave_rec[1].y(),m_ecg_cfg->m_wave_rec[1].height());
    if(m_ecg_cfg->m_wave_plot_enable[2])
    g_WavePlotter->setWaveName(m_ecg_cfg->m_wave_indx[2],"ECG III",m_ecg_cfg->m_wave_rec[2].y(),m_ecg_cfg->m_wave_rec[2].height());
    if(m_ecg_cfg->m_wave_plot_enable[3])
    g_WavePlotter->setWaveName(m_ecg_cfg->m_wave_indx[3],"AVR",m_ecg_cfg->m_wave_rec[3].y(),m_ecg_cfg->m_wave_rec[3].height());
    if(m_ecg_cfg->m_wave_plot_enable[4])
    g_WavePlotter->setWaveName(m_ecg_cfg->m_wave_indx[4],"AVL",m_ecg_cfg->m_wave_rec[4].y(),m_ecg_cfg->m_wave_rec[4].height());
    if(m_ecg_cfg->m_wave_plot_enable[5])
    g_WavePlotter->setWaveName(m_ecg_cfg->m_wave_indx[5],"AVF",m_ecg_cfg->m_wave_rec[5].y(),m_ecg_cfg->m_wave_rec[5].height());
    if(m_ecg_cfg->m_wave_plot_enable[6])
    g_WavePlotter->setWaveName(m_ecg_cfg->m_wave_indx[6],"V",m_ecg_cfg->m_wave_rec[6].y(),m_ecg_cfg->m_wave_rec[6].height());

}

void CEcgModule::f_set_spo2_wave_layout()
{
    if(m_spo2_cfg->m_wave_enable == true)
    {
        g_WavePlotter->setWaveColor(m_spo2_cfg->m_wave_indx,
                                    GLB_COLOR(m_spo2_cfg->m_wave_color));
        g_WavePlotter->setWaveName(m_spo2_cfg->m_wave_indx,"血氧",m_spo2_cfg->m_wave_rec.y(),m_spo2_cfg->m_wave_rec.height());
    }
    m_spo2_pos = m_spo2_last_pos = 0;
}

void CEcgModule::f_set_spire_wave_layout()
{
    if(m_spire_cfg->m_wave_enable == true)
    {
        g_WavePlotter->setWaveColor(m_spire_cfg->m_wave_indx,
                                    GLB_COLOR(m_spire_cfg->m_wave_color));
        g_WavePlotter->setWaveName(m_spire_cfg->m_wave_indx,"呼吸",m_spire_cfg->m_wave_rec.y(),m_spire_cfg->m_wave_rec.height());
    }
    m_spire_pos = m_spire_last_pos = 0;
}

void CEcgModule::f_set_nibp_def_cfg()
{
    m_nibp_cfg->m_nibp_interval = 0;
    m_nibp_cfg->m_nibp_mesure_type = 0;
    m_nibp_cfg->m_nibp_interval = 0;
    m_nibp_cfg-> m_module_enable = true;//true = module enable;
    m_nibp_cfg-> m_nibp_para_enable = true;
    m_nibp_cfg-> m_panel_color = 4;//para color
    m_nibp_cfg->m_dara_src = CNibpModuleCfg::ENUM_ECG_DATA_SRC_PORT; //where data from:file or serial port;


    //PortSettings m_serial_port_cfg;
    m_nibp_cfg-> m_serial_port_num = 0; //searial port number

    //alarm
    m_nibp_cfg-> m_para_alarm_en = true; //true = para alarm enable flg enable
    m_nibp_cfg-> m_tech_alarm_en = true; // true = tech alarm enbale flag enable

    //wave
    m_nibp_cfg-> m_wave_num = 0; //module has n waves to draw;

    m_nibp_cfg->m_wave_rec = QRect(0,0,0,0);
    m_nibp_cfg-> m_nibp_unit = 0;
    m_nibp_cfg-> m_nibp_mesure_type = 0;
    m_nibp_cfg-> m_nibp_interval = 0;
    m_nibp_cfg-> m_nibp_correct = 0;

    m_nibp_cfg->m_alarm_pj_high = 110;
    m_nibp_cfg->m_alarm_pj_low = 60;
    m_nibp_cfg->m_alarm_ss_high = 160;
    m_nibp_cfg->m_alarm_ss_low = 90;
    m_nibp_cfg->m_alarm_sz_high = 90;
    m_nibp_cfg->m_alarm_sz_low = 50;
   // m_nibp_val.m_alarm_nibp_high = m_nibp_cfg->m_alarm_nibp_high;
  //  m_nibp_val.m_alarm_nibp_low = m_nibp_cfg->m_alarm_nibp_low;
}
void CEcgModule::f_set_nibp_cfg(CNibpModuleCfg cfg)
{
    memcpy(m_nibp_cfg,&cfg,sizeof(CNibpModuleCfg));
    QFile file((NIBP_MODULE_CFG_DOC));
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_nibp_cfg,sizeof(CNibpModuleCfg));
    file.close();
    //m_nibp_val.m_alarm_nibp_high = m_nibp_cfg->m_alarm_nibp_high;
   // m_nibp_val.m_alarm_nibp_low = m_nibp_cfg->m_alarm_nibp_low;
    if(m_nibp_cfg->m_nibp_unit == 0)
    {
        emit signal_setpanels_value(pMainForm->label_nibp_unit,"mmHg");
    }
    else
    {
        emit signal_setpanels_value(pMainForm->label_nibp_unit,"kPa");
    }

}
void CEcgModule::f_get_nibp_cfg(CNibpModuleCfg *cfg)
{
    memcpy(cfg,m_nibp_cfg,sizeof(CNibpModuleCfg));
}
void CEcgModule::f_do_nibp_measure()
{
    if(m_nibp_val.m_result_state == 0) //从等待状态开始测量
    {
        f_0803_com_send_cmd(0x55);
        pMainForm-> TextLabel_bar_alarm_II->setText("开始血压测量");
        m_nibp_val.m_result_state = 1; //手动测量开始
    }
    else//其他状态停止测量
    {
         pMainForm-> TextLabel_bar_alarm_II->setText("停止血压测量");
         f_0803_com_send_cmd(0x56);
         m_nibp_val.m_result_state = 0;
    }
}

void CEcgModule::f_set_temp_def_cfg()
{
    m_temp_cfg->m_temp_unit = 0;
    m_temp_cfg->m_alarm1_high = 39.0;
    m_temp_cfg->m_alarm1_low = 35.0;
    m_temp_cfg->m_alarm2_high = 39.0;
    m_temp_cfg->m_alarm2_low = 35.0;
    m_temp_cfg->m_wave_num = 0;
    m_temp_cfg->m_module_enable = true;//true = module enable;
    m_temp_cfg->m_temp_para_enable = true;
    m_temp_cfg->m_panel_color = 3;//para color

    m_temp_cfg->m_dara_src =CTempModuleCfg::ENUM_ECG_DATA_SRC_PORT; //where data from:file or serial port;


    //PortSettings m_serial_port_cfg;
    m_temp_cfg->m_serial_port_num=0; //searial port number


    //alarm
    m_temp_cfg->m_para_alarm_en=true; //true = para alarm enable flg enable
    m_temp_cfg->m_tech_alarm_en = true; // true = tech alarm enbale flag enable


    m_temp_cfg->m_wave_num = 0; //module has n waves to draw;

    m_temp_cfg->m_wave_rec = QRect(0,0,0,0) ;
    m_temp_cfg->m_temp_unit = 0;
    m_temp_cfg->m_temp_sensor = 0;

    m_temp_val.m_alarm_temp1_high = m_temp_cfg->m_alarm1_high;
    m_temp_val.m_alarm_temp1_low = m_temp_cfg->m_alarm1_low;
    m_temp_val.m_alarm_temp2_high = m_temp_cfg->m_alarm2_high;
    m_temp_val.m_alarm_temp2_low = m_temp_cfg->m_alarm2_low;
}
void CEcgModule::f_set_temp_cfg(CTempModuleCfg cfg )
{
    m_temp_cfg->m_temp_unit = cfg.m_temp_unit;
    QFile file((TEMP_MODULE_CFG_DOC));
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_temp_cfg,sizeof(CTempModuleCfg));
    file.close();
    m_temp_val.m_alarm_temp1_high = m_temp_cfg->m_alarm1_high;
    m_temp_val.m_alarm_temp1_low = m_temp_cfg->m_alarm1_low;
    m_temp_val.m_alarm_temp2_high = m_temp_cfg->m_alarm2_high;
    m_temp_val.m_alarm_temp2_low = m_temp_cfg->m_alarm2_low;
}
void CEcgModule::f_get_temp_cfg(CTempModuleCfg *cfg)
{
    cfg->m_temp_unit = m_temp_cfg->m_temp_unit;
    memcpy(cfg,m_temp_cfg,sizeof(CTempModuleCfg));
}

void CEcgModule::f_set_spire_def_cfg()
{
     m_spire_cfg->m_spire_asp_alarm = 2;
     m_spire_cfg->m_spire_wave_amp = 0;
     m_spire_cfg->m_spire_wave_speed = 0;
     m_spire_cfg->m_spire_lead = 1;
     m_spire_cfg->m_spire_src = 0;
     m_spire_cfg->m_wave_enable = true;
     m_spire_cfg->m_wave_color = GLB_COLOR_YELLOW; // wave color
     m_spire_cfg->m_panel_color = GLB_COLOR_YELLOW;
     m_spire_cfg->m_wave_rec.setRect(0,50*8+200,730,50);
     m_spire_cfg->m_wave_indx = 0;
     m_spire_cfg->m_spire_para_enable = true;

     m_spire_val.m_alarm_spr_high = m_spire_cfg->m_alarm_high;
     m_spire_val.m_alarm_spr_low = m_spire_cfg->m_alarm_low;

     m_spire_pos = 0;
     m_spire_last_pos = 0;
}
void CEcgModule::f_set_spire_cfg(CSpireModuleCfg cfg )
{
    memcpy(m_spire_cfg, &cfg,sizeof(CSpireModuleCfg));
    QFile file((SPIRE_MODULE_CFG_DOC));
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_spire_cfg,sizeof(CSpireModuleCfg));
    file.close();
    m_spire_val.m_alarm_spr_high = m_spire_cfg->m_alarm_high;
    m_spire_val.m_alarm_spr_low = m_spire_cfg->m_alarm_low;
}
void CEcgModule::f_get_spire_cfg(CSpireModuleCfg *cfg)
{
    memcpy(cfg,m_spire_cfg,sizeof(CSpireModuleCfg));

}
void CEcgModule::f_plot_spo2_wave(int data)
{
    double y = 0;
    bool limit_flag = false;
    double dstep = 0;
    QVector<QPointF> tempint;

    y = m_spo2_cfg->m_wave_rec.height()-data * m_spo2_cfg->m_wave_rec.height() / 256; //

    //V
    double x=0;
    if(m_spo2_cfg->m_spo2_wave_speed == 0) //12.5mm/s
    {
        x = 0.3181818;//1*730/(500*17.6); // (730[pix]/220[mm])* 12.5[mm/s] / (125[Byte/s]) = pix/Byte
    }
    else if(m_spo2_cfg->m_spo2_wave_speed == 1) // 25mm/s
    {
        x = 0.66363636;//1*730/(125*8.8);
    }


    m_spo2_pos +=x;
    if(m_spo2_pos>= (g_WaveWidgetWidthPix-1))
    {
        m_spo2_pos -= (g_WaveWidgetWidthPix-1);
        limit_flag = true;

    }

/*
    if(limit_flag == true)
    {
        if(m_spo2_cfg->m_wave_enable)
        {
            tempint.append(QPointF(x,y));
            //QMutexLocker locker(&m_mutex_wave_spo2);
            //m_spo2_data_to_draw.append(QPointF(m_spo2_pos,y));
            //g_WavePlotter->setCurveData(m_spo2_cfg->m_wave_indx,tempint,0);
            g_drawThread->f_draw_spo2(m_spo2_cfg->m_wave_indx,tempint,0);
            tempint.clear();
        }
        m_spo2_last_pos = 0;

    }
    if(m_spo2_pos >= (m_spo2_last_pos +1))//plot 1 pix,do not plot if less than 1pix.
    {

        if(m_spo2_cfg->m_wave_enable)
        {
            tempint.append(QPointF(x,y));
            //g_WavePlotter->setCurveData(m_spo2_cfg->m_wave_indx, tempint,m_spo2_pos);
            g_drawThread->f_draw_spo2(m_spo2_cfg->m_wave_indx, tempint,m_spo2_pos);
            tempint.clear();
        }
        m_spo2_last_pos = m_spo2_pos;

    }
    */
    if(m_spo2_pos >= m_spo2_last_pos)
    {
        dstep = m_spo2_pos - m_spo2_last_pos;
    }
    else
    {
        dstep = m_spo2_pos + g_WaveWidgetWidthPix - m_spo2_last_pos;
    }
    if(dstep >=1)
    {
        if(m_spo2_cfg->m_wave_enable)
        {
            tempint.append(QPointF(dstep,y));
            //g_WavePlotter->setCurveData(m_spo2_cfg->m_wave_indx, tempint,m_spo2_pos);
            g_drawThread->f_draw_spo2(m_spo2_cfg->m_wave_indx, tempint,m_spo2_pos);
            tempint.clear();
        }
        m_spo2_last_pos = m_spo2_pos;
    }
}
void CEcgModule::f_set_spire_wave_color(int color)
{
    g_WavePlotter->setWaveColor(m_spire_cfg->m_wave_indx,GLB_COLOR(color));

    m_spire_cfg->m_wave_color = color;
    f_set_spire_cfg(*m_spire_cfg);
}
void CEcgModule::f_store_beatrate(int value,bool flg)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_beatrate (para_id, para_value,para_time,para_alm_flg,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value, :para_time,:para_alm_flg,:para_date,:para_datetime )");

    query.bindValue(":para_id",DB_PARA_TYPE_BEATRATE);
    query.bindValue(":para_value",value);

    query.bindValue(":para_alm_flg",flg);


    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();


}

void CEcgModule::f_store_breath_ecg(int value,bool flg)
{/*
    QSqlQuery query;
    query.prepare("INSERT INTO para_breathrate (para_id, para_value,para_time,para_alm_flg,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value, :para_time,:para_alm_flg,:para_date,:para_datetime )");

    query.bindValue(":para_id",DB_PARA_TYPE_BREATHRATEECG);
    query.bindValue(":para_value",value);

    query.bindValue(":para_alm_flg",flg);


    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();*/
}

void CEcgModule::f_store_spo2(int spo2,int pulserate,bool flg1,bool flg2)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_spo2 (para_id, para_value1,para_value2,para_time,para_alm_flg1,para_alm_flg2,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value1, :para_value2,:para_time,:para_alm_flg1,:para_alm_flg2,:para_date,:para_datetime )");

    query.bindValue(":para_id",DB_PARA_TYPE_SPO2);
    query.bindValue(":para_value1",spo2);
    query.bindValue(":para_value2",pulserate);

    query.bindValue(":para_alm_flg1",flg1);
    query.bindValue(":para_alm_flg2",flg2);

    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}

void CEcgModule::f_store_temp(int temp1,int temp2,bool flg1,bool flg2)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_temperature (para_id, para_value1,para_value2,para_time,para_alm_flg1,para_alm_flg2,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value1, :para_value2,:para_time,:para_alm_flg1,:para_alm_flg2,:para_date,:para_datetime )");

    query.bindValue(":para_id",DB_PARA_TYPE_TEMP);
    query.bindValue(":para_value1",temp1);
    query.bindValue(":para_value2",temp2);

    query.bindValue(":para_alm_flg1",flg1);
    query.bindValue(":para_alm_flg2",flg2);
    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}

void CEcgModule::f_store_nibp(int ss,int sz,int pj,bool flg1,bool flg2,bool flg3)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_nibp (para_id, para_value1,para_value2,para_value3,para_date,para_time,para_datetime,para_alm_flg1,para_alm_flg2,para_alm_flg3 ) "
                  "VALUES (:para_id, :para_value1, :para_value2,:para_value3,:para_date,:para_time,:para_datetime,:para_alm_flg1,:para_alm_flg2,:para_alm_flg3 )");

    query.bindValue(":para_id",DB_PARA_TYPE_NIBP);
    query.bindValue(":para_value1",ss);
    query.bindValue(":para_value2",sz);
    query.bindValue(":para_value3",pj);



    query.bindValue(":para_alm_flg1",flg1);

    query.bindValue(":para_alm_flg2",flg2);

    query.bindValue(":para_alm_flg3",flg3);

    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}

void CEcgModule::f_parse_0803_com_data(QByteArray data)
{
    QByteArray temp=data;
    QByteArray qbSpo2Wav;
    QByteArray qbSireWav;

    int iEcgWavCnt = 0;
    int iSpireWavCnt = 0;
    int iSpo2WavCnt = 0;
    unsigned char ucComStat[2];//系统状态
    bool bSysTest[11];//系统自检结果
    unsigned char ucLeadStat[2];//心电导联连接和信号信息
    qint16 iBeatRate;
    qint16 HR_R;
    qint8 iPvc;
    int iArr_type;
    qint16 iArr_val;//心律失常
    static QByteArray BY_ECG_buff[3]={"","",""};
    qint16 iST1,iST2,iST3;
    bool bAPNEA;
    int iTempStat;
    qint16 iTempVal1;
    qint16 iTempVal2;
    bool bNibpStat; //NIBP star(true) stop(false) flag;
    int iNibpDP; //Diastolic blood pressure
    int iNibpSP; //Systolic pressure  收缩压
    int iNibpMP; //Mean pressure
    int iNibpPulseRate;
    int iNibpPatientInfo;;
    int iNibpStat;
    int iNibpInterval;
    int iNibpErr;
    int iNibpTime;
    qint16 iPulseRate;
    qint8 iSpo2Val;
    int iSpo2ttFlg;
    int iSpo2Stat;
    qint16 breath;

    if(temp.size()>0)//valid data
    {
        int iDataCnt=temp.size();

        for(int i=0;i<iDataCnt;i++)
        {
            if((temp[i] & 0x80) == 0)
            {
                m_para_data_type = temp[i];
                m_para_data_sumchk = 0;
                m_para_data_one_cnt = 0;
                for(int j=0;j<MAX_DATA_PER_CMD;j++)
                {
                    m_para_data_one_buf[j] = 0;
                }

            }
            else{                
            }
            m_para_data_one_buf[m_para_data_one_cnt] = temp[i];
            m_para_data_one_cnt++;
            switch(m_para_data_type)
            {
            case 0x05://心电波形

                if((m_para_data_one_cnt == 9)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[8] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1]; //
                    int ch1,ch2,ch3;
                    ch1 = ((((m_para_data_one_buf[2]&0x0f)<<8)+((m_para_data_one_buf[3]&0x7f)+((ucSign&0x02)<<6))));
                    ch2 = ((((m_para_data_one_buf[4]&0x0f)<<8)+((m_para_data_one_buf[5]&0x7f)+((ucSign&0x08)<<4))));
                    ch3 = ((((m_para_data_one_buf[6]&0x0f)<<8)+((m_para_data_one_buf[7]&0x7f)+((ucSign&0x20)<<2))));
                    //emit signal_setpanels_value(pMainForm->TextLabel_bar_alarm_II,ch1);
                    {
                        //QMutexLocker locker(&m_mutex_wave_ecg);
                        //m_ecg_wave_data_1.append(ch1);
                        //m_ecg_wave_data_2.append(ch2);
                        //m_ecg_wave_data_3.append(ch3);
                        bool bFlg = false;
                        f_plot_ecg_wave(ch1,ch2,ch3);
                        if(m_ecg_wave_count<500)
                        {
                            unsigned short cnt = m_ecg_wave_count*255/499;
                            m_ecg_val.m_ecg_wave_data[0][cnt] = ch1>>4;
                            m_ecg_val.m_ecg_wave_data[1][cnt] = ch2>>4;
                            m_ecg_val.m_ecg_wave_data[2][cnt] = ch3>>4;

                            m_ecg_value[ECG_VAL_ECG_WAVE0_C+(cnt)] = ch1>>4;
                            m_ecg_value[ECG_VAL_ECG_WAVE1_C+(cnt)] = ch2>>4;
                            m_ecg_value[ECG_VAL_ECG_WAVE2_C+(cnt)] = ch3>>4;

                             m_ecg_wave_count++;
                        }
                         if(m_ecg_wave_count >=500)
                         {
                             if(m_spire_wave_count >=125)
                             {
                                 m_ecg_wave_count =0;
                                 m_spire_wave_count = 0;
                                 QByteArray data;
                                 //data.append((char *)m_ecg_value,sizeof(m_ecg_value));
                                 data.append((char*)&m_ecg_val,sizeof(m_ecg_val));
                                 //data = m_ecg_value;
                                 emit signal_para_tcp_data_ready(data,1);
                                 unsigned short cnt;
                                 for(int i = 0;i<m_ecg_backup_cnt;i++)
                                 {
                                     cnt = i*255/499;
                                     m_ecg_val.m_ecg_wave_data[0][cnt] = m_ecg_backup_buf[0][i];
                                     m_ecg_val.m_ecg_wave_data[1][cnt] = m_ecg_backup_buf[1][i];
                                     m_ecg_val.m_ecg_wave_data[2][cnt] = m_ecg_backup_buf[2][i];
                                 }
                                 m_ecg_wave_count = m_ecg_backup_cnt;
                                 m_ecg_backup_cnt = 0;
                                 //
                                  unsigned short cnt1;
                                 for(int i = 0;i<m_spire_backup_cnt;i++)
                                 {
                                     cnt = i * 127/124;
                                     m_ecg_val.m_spire_wave_data[cnt] = m_spire_backup_buf[i];
                                     m_ecg_value[ECG_VAL_SPIRE_WAVE_C+cnt] = m_spire_backup_buf[i];
                                     if((i+1)<m_spire_backup_cnt)
                                     {
                                         cnt1 = (i+1) * 127/124;
                                         if((cnt1 - cnt)>1)
                                         {
                                             m_ecg_val.m_spire_wave_data[cnt+1] = m_spire_backup_buf[i];
                                         }
                                     }
                                 }
                                 m_spire_wave_count = m_spire_backup_cnt;
                                 m_spire_backup_cnt = 0;
                             }
                             else
                             {
                                 m_ecg_backup_buf[0][m_ecg_backup_cnt] = ch1>>4;
                                 m_ecg_backup_buf[1][m_ecg_backup_cnt] = ch2>>4;
                                 m_ecg_backup_buf[2][m_ecg_backup_cnt] = ch3>>4;
                                 m_ecg_backup_cnt++;
                                 m_ecg_backup_cnt %=256;
                             }
                         }

                    }
                    if((m_para_data_one_buf[1]& 0x40) !=0)
                    {

                    }
                    if((m_para_data_one_buf[1]& 0x20) !=0)
                    {
                        //QSound beat rate;
                    }
                }
                else
                {
                    m_para_data_sumchk+=temp[i];
                }
                break;
            case 0x10://
                //////////
                if((m_para_data_one_cnt == 4)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[3] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    int value = ((m_para_data_one_buf[2]&0x7f) +((ucSign&0x01)<<7));
                    qbSireWav[iSpireWavCnt]=value;
                    iSpireWavCnt++;
                    {
                        //QMutexLocker locker(&m_mutex_wave_spire);
                        //m_spire_wave_data.append(value);
                    }
                    f_plot_spire_wave(value);
                    if(m_spire_wave_count<125)
                    {
                        unsigned short cnt = m_spire_wave_count * 127/124;
                        m_ecg_val.m_spire_wave_data[cnt] = value;
                        m_ecg_value[ECG_VAL_SPIRE_WAVE_C+cnt] = value;
                        if(m_spire_wave_count+1<125)
                        {
                            unsigned short cnt1 = (m_spire_wave_count+1) * 127/124;
                            if(((cnt1 - cnt)>1))
                            {
                                m_ecg_val.m_spire_wave_data[cnt+1] = value;
                            }
                        }
                        m_spire_wave_count++;

                    }
                    if(m_spire_wave_count >= 125)
                    {

                        if(m_ecg_wave_count >=500)
                        {
                            m_ecg_wave_count =0;
                            m_spire_wave_count = 0;
                            QByteArray data;
                            //data.append((char *)m_ecg_value,sizeof(m_ecg_value));
                            data.append((char*)&m_ecg_val,sizeof(m_ecg_val));
                            //data = m_ecg_value;
                            emit signal_para_tcp_data_ready(data,1);
                            unsigned short cnt;
                             unsigned short cnt1;
                            for(int i = 0;i<m_spire_backup_cnt;i++)
                            {
                                cnt = i * 127/124;
                                m_ecg_val.m_spire_wave_data[cnt] = m_spire_backup_buf[i];
                                m_ecg_value[ECG_VAL_SPIRE_WAVE_C+cnt] = m_spire_backup_buf[i];
                                if((i+1)<m_spire_backup_cnt)
                                {
                                    cnt1 = (i+1) * 127/124;
                                    if((cnt1 - cnt)>1)
                                    {
                                        m_ecg_val.m_spire_wave_data[cnt+1] = m_spire_backup_buf[i];
                                    }
                                }
                            }
                            m_spire_wave_count = m_spire_backup_cnt;
                            m_spire_backup_cnt = 0;

                            for(int i = 0;i<m_ecg_backup_cnt;i++)
                            {
                                cnt = i*255/499;
                                m_ecg_val.m_ecg_wave_data[0][cnt] = m_ecg_backup_buf[0][i];
                                m_ecg_val.m_ecg_wave_data[1][cnt] = m_ecg_backup_buf[1][i];
                                m_ecg_val.m_ecg_wave_data[2][cnt] = m_ecg_backup_buf[2][i];
                            }
                            m_ecg_wave_count = m_ecg_backup_cnt;
                            m_ecg_backup_cnt = 0;
                        }
                        else
                        {
                            m_spire_backup_buf[m_spire_backup_cnt] = value;
                            m_spire_backup_cnt++;
                            m_spire_backup_cnt %=256;
                        }
                    }
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x16://
                //////////
                if((m_para_data_one_cnt == 5)
                &&( (m_para_data_sumchk & 0x7f) ==(m_para_data_one_buf[4] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    iSpo2Stat =(( ucSign &0x02)<<6)|(m_para_data_one_buf[3]&0x7f);
                    int wavevalue = ((((m_para_data_one_buf[2]&0x7f)+((ucSign&0x01)<<7))&0xff));

                    qbSpo2Wav[iSpo2WavCnt]= wavevalue;
                    iSpo2WavCnt++;
                    {
                        //QMutexLocker locker(&m_mutex_wave_spo2);
                        //m_spo2_wave_data.append(wavevalue);
                    }

                    m_spo2_val.m_state = iSpo2Stat;
                    if(m_spo2_val.m_state & (1<<7))
                    {
                        //warning finger drop

                    }
                    if(m_spo2_val.m_state & (1<<6))
                    {
                        //qsound pulse rate
                        if(m_spo2_cfg->m_spo2_pulse_vol >0)
                        {
                            g_PlayThread->addPlay(G_WARN_T_CODE_HEARTV);
                        }

                    }
                    if(m_spo2_val.m_state & (1<<5))
                    {
                        //searching pulse;
                    }
                    if(m_spo2_val.m_state & (1<<4))
                    {
                        //warning sensor drop
                    }
                    m_spo2_val.m_pulse_gram = m_spo2_val.m_state & 0x0f;

                    f_plot_spo2_wave(wavevalue);
                    m_spo2_val.m_spo2_wave[2*m_spo2_wave_count] = wavevalue>>1;//减半
                    m_spo2_val.m_spo2_wave[2*m_spo2_wave_count+1] = wavevalue>>1;//减半
                    if(m_spo2_wave_count >= 127)
                    {
                        QByteArray data;
                        data.append((char *)&m_spo2_val,278);
                        m_spo2_wave_count = 0;
                        emit signal_para_tcp_data_ready(data,2);
                    }
                    else
                    {
                        m_spo2_wave_count++;
                    }
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x20://
                //////////
                if((m_para_data_one_cnt == 7)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[6] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    int iTiePres = (((m_para_data_one_buf[2]&0x7f)+((ucSign&0x01)<<7))<<8)+
                            ((m_para_data_one_buf[3]&0x7f)+((ucSign&0x02)<<6));
                    m_nibp_val.m_para_nibp_xiudai = iTiePres;
                    QString str;
                    str.setNum(iTiePres);
                    emit signal_setpanels_value(pMainForm->TextLabel_WuChuangXueYa_xiudaiya_value,iTiePres);
                    //emit single_for_QLabel_set(TextLabel_WuChuangXueYa_xiudaiya_value,str,type_num);
                    m_nibp_val.m_measure_stop_err = m_para_data_one_buf[4]& 0x7f;
                    m_nibp_val.m_mesure_mod = m_para_data_one_buf[5] & 0x7f;

                    m_nibp_val.m_result_state = m_nibp_val.m_mesure_mod;

                    if(m_nibp_val.m_measure_stop_err ==1)
                    {
                        //stop nibp
                        f_0803_com_send_cmd(0x56);
                    }
                    QString mod;
                    if(m_nibp_val.m_mesure_mod == 0)
                    {
                        mod.append("手动");
                    }
                    else if(m_nibp_val.m_mesure_mod == 1)
                    {
                        mod.append("自动");
                    }
                    else if(m_nibp_val.m_mesure_mod == 2)
                    {
                        mod.append("STAT");
                    }
                    else if(m_nibp_val.m_mesure_mod == 3)
                    {
                        mod.append("校准");
                    }
                    else if(m_nibp_val.m_mesure_mod == 4)
                    {
                        mod.append("漏气检测");
                    }
                    emit signal_setpanels_value(pMainForm->TextLabel_WuChuangXueYa_ShouDong,mod);

                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x01://系统复位
                if(m_para_data_one_buf[1]==(char)0x81)
                {
                    f_0803_com_send_cmd(0x01);

                }
                //
                break;
            case 0x02://系统状态
                //////////
                if((m_para_data_one_cnt == 4)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[3] & 0x7f)))
                {

                    unsigned char ucSign = m_para_data_one_buf[1];
                    ucComStat[0]=(m_para_data_one_buf[2]&0x30)>>2;
                    ucComStat[1]=m_para_data_one_buf[2]&0x03;
                    if(ucComStat[0] == 0)
                    {

                    }
                    else if(ucComStat[0] == 1)
                    {
                        //warning 3.3v high
                    }
                    else if(ucComStat[0] == 2)
                    {
                        //warning 3.3v low
                    }
                    if(ucComStat[1] == 0){}
                    else if(ucComStat[1] == 1)
                    {
                        //warning 5v high
                    }
                    else if(ucComStat[1] == 2)
                    {
                        //warning 5v low
                    }
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x03://系统自检
                //////////
                if((m_para_data_one_cnt == 9)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[8] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    for (int x=0;x<10;x++)
                        bSysTest[x] = (m_para_data_one_buf[2+x/5] &(0x10 >> (x%5)))>>(4-x%5);
                    bSysTest[10] =(m_para_data_one_buf[4]&0x7f)+((ucSign&0x04)<<5);
                    if(bSysTest[0])
                    {
                        //warning watch dog
                    }
                    if(bSysTest[1])
                    {
                        //warning ad
                    }
                    if(bSysTest[2])
                    {
                        //warning RAM
                    }
                    if(bSysTest[3])
                    {
                        //warning ROM
                    }
                    if(bSysTest[4])
                    {
                        //warning CPU
                    }
                    if(bSysTest[5])
                    {
                        //warning NBP
                    }
                    if(bSysTest[6])
                    {
                        //warning SPO2
                    }
                    if(bSysTest[7])
                    {
                        //warning temp
                    }
                    if(bSysTest[8])
                    {
                        //warning resp
                    }
                    if(bSysTest[9])
                    {
                        //warning ecg
                    }
                    if(bSysTest[1])
                    {

                    }
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////
                break;
            case 0x04://命令应答
                //////////
                if((m_para_data_one_cnt == 9)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[8] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    if (m_para_data_one_buf[3]&0x7f)
                    {
                        if ((m_para_data_one_buf[2]&0x7f)>0x54 )
                        {
                            //FY0803_SendSetCommand(0x56);
                            //emit single_for_QLabel_set(TextLabel_WuChuangXueYa_xiudaiya,"",type_hide);
                            //emit single_for_QLabel_set(TextLabel_WuChuangXueYa_xiudaiya_value,"",type_hide);
                            //NIBP_Start_Stop=FALSE;
                        }
                    }
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////
//                else i++;
                break;
            case 0x06://心电导联
                //////////
                if((m_para_data_one_cnt == 5)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[4] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    ucLeadStat[0] = m_para_data_one_buf[2]&0x0f;
                    ucLeadStat[1] = m_para_data_one_buf[3]&0x03;
                    if(ucLeadStat[0] & 0x01)
                    {
                        //warning LL脱落
                    }
                    if(ucLeadStat[0] & 0x02)
                    {
                        //warning LA off
                    }
                    if(ucLeadStat[0] & 0x04)
                    {
                        //warning RA off
                    }
                    if(ucLeadStat[0] & 0x08)
                    {
                        //warning V off
                    }
                    if(ucLeadStat[1] & 0x01)
                    {
                        //warning ecg1过载
                    }
                    if(ucLeadStat[1] & 0x02)
                    {
                        //warning ecg2过载
                    }
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x07://心率
                //////////
                if((m_para_data_one_cnt == 7)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[6] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    iBeatRate=(((m_para_data_one_buf[2]&0x7f)+((ucSign&1)<<7))<<8)
                            +((m_para_data_one_buf[3]&0x7f)+((ucSign&2)<<6));
                    HR_R=(((m_para_data_one_buf[4]&0x7f)+((ucSign&4)<<5))<<8)
                            +((m_para_data_one_buf[5]&0x7f)+((ucSign&8)<<4));
                    //QString value = QString::number(iBeatRate,10);
                    //pMainForm->TextLabel_bar_alarm_II->setText(value);
                    bool almflg = false;
                    if((iBeatRate == -100) )
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_XinLv_value,"---");
                    }
                    else
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_XinLv_value,iBeatRate);

                        if((iBeatRate > m_ecg_cfg->m_alarm_br_high))
                        {
                                //warning beatrate high
                            almflg = true;
                         }
                         else if ((iBeatRate < m_ecg_cfg->m_alarm_br_low))
                        {
                            //warning beatrate low
                            almflg = true;
                        }
                        //存储到数据库
                        //f_store_beatrate(iBeatRate,almflg);
                        emit signal_store_beatrate(iBeatRate,almflg,QDateTime::currentDateTime());
                    }
                    m_ecg_value[ECG_VAL_BEATRATE_S]  = iBeatRate&0xff;
                    m_ecg_value[ECG_VAL_BEATRATE_S+1]  = (iBeatRate&0xff00)>>8;
                    m_ecg_val.m_para_beat_rate = iBeatRate;
                    m_ecg_val.m_para_R_inter = HR_R;


                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x09://iPvc
                //////////
                if((m_para_data_one_cnt == 4)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[3] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    iPvc=(char)((m_para_data_one_buf[2]&0x7f)+((ucSign&1)<<7));
                    if(iPvc == -100)
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_XinLv_QiBo_KaiGuan,"---");
                    }
                    else
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_XinLv_QiBo_KaiGuan,iPvc);
                    }
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x0a://=
                //////////
                if((m_para_data_one_cnt == 6)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[5] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    iArr_type=(m_para_data_one_buf[2]&0x7f)+((ucSign&1)<<7);
                    iArr_val=((((ucSign&0x02)<<6)+(m_para_data_one_buf[3]&0x7f))<<8)
                            +(((ucSign&0x04)<<5)+(m_para_data_one_buf[4]));
                    m_ecg_val.m_ecg_arr_type = iArr_type;
                    m_ecg_val.m_ecg_arr_value = iArr_val;
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x0b://
                //////////
                if((m_para_data_one_cnt == 9)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[8] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    iST1=(short)(((m_para_data_one_buf[2]&0x7f)+((ucSign&0x01)<<7))<<8)
                            +((m_para_data_one_buf[3]&0x7f)+((ucSign&0x02)<<6));
                    iST2=(short)(((m_para_data_one_buf[4]&0x7f)+((ucSign&0x04)<<5))<<8)
                            +((m_para_data_one_buf[5]&0x7f)+((ucSign&0x08)<<4));
                    iST3=(short)(((m_para_data_one_buf[6]&0x7f)+((ucSign&0x10)<<3))<<8)
                            +((m_para_data_one_buf[7]&0x7f)+((ucSign&0x20)<<2));
                    if(iST1 == -10000)
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_XinLv_STkaiguan1_Text,"---");
                    }
                    else
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_XinLv_STkaiguan1_Text,iST1);
                        //warning
                        if(iST1 > m_ecg_cfg->m_alarm_st_high)
                        {
                                //warning st1 high
                        }
                        else if(iST1 < m_ecg_cfg->m_alarm_st_high)
                        {
                            //warning st1 low
                        }
                    }
                    if(iST2 == -10000)
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_XinLv_STkaiguan2_Text,"---");
                    }
                    else
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_XinLv_STkaiguan2_Text,iST2);
                        if(iST2 > m_ecg_cfg->m_alarm_st_high)
                        {
                                //warning st2 high
                        }
                        else if(iST2 < m_ecg_cfg->m_alarm_st_high)
                        {
                            //warning st2 low
                        }
                    }
                    float fSt1,fSt2,fSt3;
                    fSt1 = iST1;
                    fSt2 = iST2;
                    fSt3 = iST3;
                    fSt1 /=100;
                    fSt2 /= 100;
                    fSt3 /= 100;
                    memcpy(m_ecg_value+ECG_VAL_ST1_F,&fSt1,sizeof(float));
                    memcpy(m_ecg_value+ECG_VAL_ST2_F,&fSt2,sizeof(float));
                    memcpy(m_ecg_value+ECG_VAL_ST3_F,&fSt3,sizeof(float));
                    m_ecg_val.m_para_st1 = fSt1;
                    m_ecg_val.m_para_st2 = fSt2;
                    m_ecg_val.m_para_st3 = fSt3;


                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;

            case 0x11://
                //////////
                if((m_para_data_one_cnt == 5)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[4] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    breath=(((m_para_data_one_buf[2]&0x7f)+((ucSign&0x01)<<7))<<8)
                            +((m_para_data_one_buf[3]&0x7f)+((ucSign&0x02)<<6));
                    bool almflg = false;
                    if(breath == -100)
                    {
                        emit (signal_setpanels_value(pMainForm->TextLabel_HuXiLv_value,"---"));
                    }
                    else
                    {


                        emit signal_setpanels_value(pMainForm->TextLabel_HuXiLv_value,breath);
                        if(m_spire_cfg->m_alarm_en)
                        {
                            if(breath > m_spire_cfg->m_alarm_high)
                            {
                                //warning 呼吸率高
                                almflg = true;
                            }
                            else if(breath < m_spire_cfg->m_alarm_low)
                            {
                                //warning 呼吸率低
                                almflg = true;
                            }
                        }
                        //存储到数据库
                        //f_store_breath_ecg(breath,almflg);
                        emit signal_store_breath_ecg(breath,almflg,QDateTime::currentDateTime());

                    }
                    memcpy(m_ecg_value+ECG_VAL_SPRATE_S,&breath,sizeof(breath)) ;
                    m_ecg_val.m_para_ecg_spr = breath;
                    //pMainForm->TextLabel_bar_alarm_II->setText(QString::number(breath,10));
                    //pMainForm->TextLabel_bar_alarm_III->setText(QString::number(m_ecg_val.m_para_ecg_spr,10));
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////
                break;
            case 0x12://
                //////////
                if((m_para_data_one_cnt == 9)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[8] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    if(m_para_data_one_buf[2]&0x7f)
                    {
                        bAPNEA=1;
                        //warning 窒息报警
                    }
                    else
                    {
                        bAPNEA=0;
                    }
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }

                break;
            case 0x15://
                //////////
                if((m_para_data_one_cnt == 8)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[7] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    iTempStat=m_para_data_one_buf[2]&0x03;
                    iTempVal1=((((ucSign&0x02)<<6)+(m_para_data_one_buf[3]&0x7f))<<8)
                            +(((ucSign&0x04)<<5)+(m_para_data_one_buf[4]&0x7f));
                    iTempVal2=((((ucSign&0x08)<<4)+(m_para_data_one_buf[5]&0x7f))<<8)
                            +(((ucSign&0x10)<<3)+(m_para_data_one_buf[6]&0x7f));
                    if(iTempStat & 0x01)
                    {
                        //warning 体温探头1脱落
                    }
                    if(iTempStat & 0x02)
                    {
                        //warning 2 off
                    }
                    bool bstoreflg = false;
                    bool alm1 = false;
                    bool alm2 = false;
                    if(iTempVal1 == -100)
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_TiWen_1_value_2,"---");
                    }
                    else
                   {
                        double temperature = iTempVal1;
                        temperature /=10;
                        if(temperature>m_temp_cfg->m_alarm1_high)
                        {
                            alm1 = true;
                        }
                        else if(temperature < m_temp_cfg->m_alarm1_low)
                        {
                            alm1 = true;
                        }
                        if(m_temp_cfg->m_temp_unit == 1)
                        {
                            temperature *= 1.8;
                            temperature +=32;
                        }

                        emit signal_setpanels_value(pMainForm->TextLabel_TiWen_1_value_2,temperature,1);
                         //存储到数据库
                        bstoreflg = true;
                    }
                    if(iTempVal2 == -100)
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_TiWen_2_value_2,"---");
                    }
                    else
                    {
                        double temperature = iTempVal2;
                        temperature /=10;
                        if(temperature > m_temp_cfg->m_alarm2_high)
                        {
                            alm2 = true;
                        }
                        else if(temperature < m_temp_cfg->m_alarm2_low)
                        {
                            alm2 = true;
                        }
                        if(m_temp_cfg->m_temp_unit == 1)
                        {
                            temperature *= 1.8;
                            temperature +=32;
                        }
                        emit signal_setpanels_value(pMainForm->TextLabel_TiWen_2_value_2,temperature,1);
                        bstoreflg = true;
                    }
                    if(bstoreflg)
                    {
                         //存储到数据库
                        //f_store_temp(iTempVal1,iTempVal2,alm1,alm2);
                        emit signal_store_temp(iTempVal1,iTempVal2,alm1,alm2,QDateTime::currentDateTime());
                    }
                    float fTmp1 = (float)iTempVal1;
                    float fTmp2 = (float)iTempVal2;
                    float fDifTmp = 0 ;
                    if(iTempVal1 > iTempVal2)
                    {
                        fDifTmp = iTempVal1 - iTempVal2;
                    }
                    else
                    {
                        fDifTmp = iTempVal2 - iTempVal1;
                    }
                    m_temp_val.m_para_temp1 = fTmp1;
                    m_temp_val.m_para_temp2 = fTmp2;
                    m_temp_val.m_para_temp_dif = fDifTmp;

                    QByteArray data;
                    data.append((char *)&m_temp_val,sizeof(stTempValue));
                    emit signal_para_tcp_data_ready(data,4);

                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x17://
                //////////
                if((m_para_data_one_cnt == 7)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[6] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    iPulseRate=((((ucSign&0x02)<<6)+(m_para_data_one_buf[3]&0x7f))<<8)
                            +(((ucSign&0x04)<<5)+(m_para_data_one_buf[4]&0x7f));
                    iSpo2Val=(m_para_data_one_buf[5]&0x7f)+((ucSign&0x08)<<4);
                    iSpo2ttFlg = (m_para_data_one_buf[2]>>6)&0x01;
                    m_spo2_val.m_spo2_value = iSpo2Val;
                    m_spo2_val.m_pulse_rate = iPulseRate;
                    m_spo2_val.m_para_info = iSpo2ttFlg;
                    bool bstoreflg = false;
                    bool bspoalmflg = false;
                    bool bpralmflg = false;
                    if(iSpo2Val == -100)
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_XueYang_value,"---");
                    }
                    else
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_XueYang_value,iSpo2Val);
                        if(iSpo2Val > m_spo2_cfg->m_alarm_high)
                        {
                            //warning spo2
                            bspoalmflg = true;
                        }
                        else if (iSpo2Val < m_spo2_cfg->m_alarm_low)
                        {
                            //warning spo2 low
                            bspoalmflg = true;
                        }
                        bstoreflg = true;
                    }
                    if(iPulseRate == -100)
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_MaiLv_value,"---");
                    }
                    else
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_MaiLv_value,iPulseRate);
                        if(iPulseRate > m_spo2_cfg->m_alarm_pulserate_high)
                        {
                            bpralmflg = true;
                        }
                        else if(iPulseRate < m_spo2_cfg->m_alarm_pulserate_low)
                        {
                            bpralmflg = true;
                        }
                        bstoreflg = true;
                    }
                    //存储到数据库
                    if(bstoreflg)
                    {
                        //f_store_spo2(iSpo2Val,iPulseRate,bspoalmflg,bpralmflg);
                        emit signal_store_spo2(iSpo2Val,iPulseRate,bspoalmflg,bpralmflg,QDateTime::currentDateTime());
                    }

                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x21://
                //////////
                if((m_para_data_one_cnt == 4)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[3] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    if ((m_para_data_one_buf[2] & 0x7f) < 3)
                    {
                        //FY0803_SendSetCommand(0x5B);
                        m_nibp_val.m_nibp_over_flg = 0x55;
                    }
                    bNibpStat= FALSE;
                    //emit single_for_QLabel_set(TextLabel_WuChuangXueYa_xiudaiya_value,"",type_hide);
                    //emit single_for_QLabel_set(TextLabel_WuChuangXueYa_xiudaiya,"",type_hide);
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x22://
                //////////
                if((m_para_data_one_cnt == 9)
                 &&( (m_para_data_sumchk & 0x7f) == (m_para_data_one_buf[8] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    iNibpStat = FALSE;
                    iNibpSP=(((m_para_data_one_buf[2]&0x7f)+((ucSign&0x01)<<7))<<8)
                            +((m_para_data_one_buf[3]&0x7f)+((ucSign&0x02)<<6));
                    iNibpDP=(((m_para_data_one_buf[4]&0x7f)+((ucSign&0x04)<<5))<<8)
                            +((m_para_data_one_buf[5]&0x7f)+((ucSign&0x08)<<4));
                    iNibpMP=(((m_para_data_one_buf[6]&0x7f)+((ucSign&0x10)<<3))<<8)
                            +((m_para_data_one_buf[7]&0x7f)+((ucSign&0x20)<<2));
                    m_nibp_val.m_para_nibp_ss = iNibpSP;
                    m_nibp_val.m_para_nibp_sz = iNibpDP;
                    m_nibp_val.m_para_nibp_pj = iNibpMP;

                    m_nibp_val.m_result_state = 0;
                    m_nibp_val.m_nibp_over_flg = 0x55;
                    bool bwarningflg1 = false;
                    bool bwarningflg2 = false;
                    bool bwarningflg3 = false;
                    if(iNibpSP == -100)
                    {
                        emit signal_setpanels_value(pMainForm->TextLabel_WuChuangXueYa_value_Gao_2,"---");
                    }
                    else
                    {
                         emit signal_setpanels_value(pMainForm->TextLabel_WuChuangXueYa_value_Gao_2,iNibpSP);
                        if((m_nibp_cfg->m_para_alarm_en) &&(m_nibp_cfg->m_alarm_ss_en))
                        {
                            if(iNibpSP > m_nibp_cfg->m_alarm_ss_high)
                            {
                                //warning nibp shousuo high
                                bwarningflg1 = true;
                            }
                            else if(iNibpSP < m_nibp_cfg->m_alarm_ss_low)
                            {
                                //warning nibp shousuo low
                                bwarningflg1 = true;
                            }
                        }
                    }
                    if(iNibpDP == -100)
                    {
                         emit signal_setpanels_value(pMainForm->TextLabel_WuChuangXueYa_value_Di,"---");
                    }
                    else
                    {
                         emit signal_setpanels_value(pMainForm->TextLabel_WuChuangXueYa_value_Di,iNibpDP);
                        if((m_nibp_cfg->m_para_alarm_en) &&(m_nibp_cfg->m_alarm_sz_en))
                        {
                            if(iNibpDP > m_nibp_cfg->m_alarm_sz_high)
                            {
                                //warning nibp shuzhang high
                                bwarningflg2 = true;
                            }
                            else if(iNibpDP < m_nibp_cfg->m_alarm_sz_low)
                            {
                                //warning nibp shuzhang low
                                bwarningflg2 = true;
                            }
                        }
                    }
                    if(iNibpMP == -100)
                    {
                         emit signal_setpanels_value(pMainForm->TextLabel_WuChuangXueYa_value_Pingjun,"---");
                    }
                    else
                    {
                         emit signal_setpanels_value(pMainForm->TextLabel_WuChuangXueYa_value_Pingjun,iNibpMP);
                        if((m_nibp_cfg->m_para_alarm_en) &&(m_nibp_cfg->m_alarm_pj_en))
                        {
                            if(iNibpMP > m_nibp_cfg->m_alarm_pj_high)
                            {
                                //warning nibp shuzhang high
                                bwarningflg3 = true;
                            }
                            else if(iNibpMP < m_nibp_cfg->m_alarm_pj_low)
                            {
                                //warning nibp shuzhang low
                                bwarningflg3 = true;
                            }
                        }
                    }
                     //存储到数据库
                    //f_store_nibp(iNibpSP,iNibpDP,iNibpMP,bwarningflg1,bwarningflg2,bwarningflg3);
                    emit signal_store_nibp(iNibpSP,iNibpDP,iNibpMP,bwarningflg1,bwarningflg2,bwarningflg3,QDateTime::currentDateTime());
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x23://
                //////////
                if((m_para_data_one_cnt == 5)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[4] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];
                    iNibpPulseRate= (((m_para_data_one_buf[2]&0x7f)+((ucSign&0x01)<<7))<<8)
                            +((m_para_data_one_buf[3]&0x7f)+((ucSign&0x02)<<6));
                    m_nibp_val.m_para_pulse_rate = iNibpPulseRate;
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////

                break;
            case 0x24://
                //////////
                if((m_para_data_one_cnt == 8)
                        &&( (m_para_data_sumchk & 0x7f) ==
                (m_para_data_one_buf[7] & 0x7f)))
                {
                    unsigned char ucSign = m_para_data_one_buf[1];

                    iNibpPatientInfo=m_para_data_one_buf[2]&0x30;
                    iNibpStat= m_para_data_one_buf[2]&0x0f;
                    iNibpInterval=m_para_data_one_buf[3]&0x7f;
                    iNibpErr=m_para_data_one_buf[4]&0x7f;
                    if (iNibpErr&0x0f)
                    {
                        //warning
                    }

                    iNibpTime = (((m_para_data_one_buf[5]&0x7f)+((ucSign&0x08)<<4))<<8)
                            +((m_para_data_one_buf[6]&0x7f)+((ucSign&0x10)<<3));

                    m_nibp_val.m_result_state = iNibpStat;
                    m_nibp_val.m_state_err = iNibpErr;
                    m_nibp_val.m_mesure_interval = iNibpTime;
                    //FY0803_SendSetCommand(0x56);
                }
                else
                {
                    m_para_data_sumchk += temp[i];
                }
                /////////////
                break;
            default:

            break;
            }

        }

    }
    else
    {

    }

}
/*********************************
名称：FY0803_SendSetCommand（）
作者：叶成磊
功能：串口数据识别之0803数据发送命令
输入参数：
********************************/

void CEcgModule::f_0803_com_send_cmd(char cmd_ID)
{
    switch (cmd_ID)
    {
        case 0x42://病人信息
                FY0803_SendCommand(cmd_ID,4,m_ecg_cfg->m_patinet_info,0,0,0);
                break;
        case 0x45://3/5导联//未处理
                FY0803_SendCommand(cmd_ID,4,m_ecg_cfg->m_ecg_lead_style,0,0,0);
                break;
        case 0x46://导联方式
                FY0803_SendCommand(cmd_ID,4,m_ecg_cfg->m_ecg_chanel1_lead/*+1*/,0,0,0);
                FY0803_SendCommand(cmd_ID,4,m_ecg_cfg->m_ecg_chanel3_lead/*+1*/+0x10,0,0,0);
                break;
        case 0x47://滤波方式
                FY0803_SendCommand(cmd_ID,4,m_ecg_cfg->m_ecg_filter_mod,0,0,0);
                break;
        case 0x48://心电增益
                FY0803_SendCommand(cmd_ID,4,m_ecg_cfg->m_ecg_amp,0,0,0);
                FY0803_SendCommand(cmd_ID,4,m_ecg_cfg->m_ecg_amp+0x10,0,0,0);
                break;
        case 0x49://1mv 校准开关
                FY0803_SendCommand(cmd_ID,4,m_ecg_cfg->m_ecg_correct,0,0,0);
                break;
        case 0x4a://工频抑制
                FY0803_SendCommand(cmd_ID,4,m_ecg_cfg->m_ect_pwr_supression_enable,0,0,0);
                break;
        case 0x4b://起博分析
                FY0803_SendCommand(cmd_ID,4,m_ecg_cfg->m_ecg_pacemaker_enable,0,0,0);
                break;
        case 0x50://呼吸增益
                FY0803_SendCommand(cmd_ID,4,m_spire_cfg->m_spire_wave_amp,0,0,0);
                break;
        case 0x52://窒息报警
                FY0803_SendCommand(cmd_ID,4,m_spire_cfg->m_spire_asp_alarm,0,0,0);
                break;
        case 0x53://体温探头
                FY0803_SendCommand(cmd_ID,4,m_temp_cfg->m_temp_sensor,0,0,0);
                break;
        case 0x54://SPO2 灵敏度
                FY0803_SendCommand(cmd_ID,4,m_spo2_cfg->m_spo2_sensitive,0,0,0);
                break;
        case 0x57://NBP手动/自动
                 if(m_nibp_cfg->m_nibp_mesure_type==0)
                        FY0803_SendCommand(cmd_ID,4,0,0,0,0);
                else
                        FY0803_SendCommand(cmd_ID,4,m_nibp_cfg->m_nibp_interval+1,0,0,0);
                break;
        case 0x5c://NBP设置初次充气压力
                if (m_ecg_cfg->m_patinet_info ==2 )
                        FY0803_SendCommand(cmd_ID,4,2,80,0,0);
                else if (m_ecg_cfg->m_patinet_info ==1 )
                        FY0803_SendCommand(cmd_ID,4,1,160,0,0);
                else
                        FY0803_SendCommand(cmd_ID,4,0,180,0,0);
                break;
        case 0x01:
    {
    }
            break;
        case 0x40:
        case 0x55://NIBP测量
        case 0x56://NIBP停止
        case 0x58://NIBP校准
        case 0x59://NIBP复位
        case 0x5a://NIBP漏气检测
                FY0803_SendCommand(cmd_ID,2,0,0,0,0);
                break;
    }
}

void CEcgModule::FY0803_SendCommand(char cmd_ID,char cmd_length,char canshu1,char canshu2,char canshu3,char canshu4)
{
        unsigned char cmd_canshu[4] = {canshu1,canshu2,canshu3,canshu4};
        char send_cmd[10] = {0};
        send_cmd[0] = cmd_ID;
        for (int i=2;i<cmd_length-1;i++)
        {
                send_cmd[1] += (cmd_canshu[i-2] & 0x80)>>(7-i);
                send_cmd[i] = (cmd_canshu[i-2] & 0x7f) ;
                send_cmd[cmd_length-1] += send_cmd[i];
        }
        for (int i=1;i<cmd_length;i++)
        {
                send_cmd[i] = send_cmd[i] | 0x80;

        }

        if (cmd_length-1 > 1)
            send_cmd[cmd_length-1] = (send_cmd[0]+send_cmd[1]+send_cmd[cmd_length-1])|0x80;
        else
            send_cmd[1] = send_cmd[0]|0x80;
        FY0803_WriteCom(send_cmd,cmd_length);
}


 /*********************************
 名称：FY0803_WriteCom（）
 作者：叶成磊
 功能：对0803板串口数据上传
 ********************************/
void CEcgModule::FY0803_WriteCom(char *bf,int _length)
{
    QByteArray btAry;
    btAry= QByteArray::fromRawData(bf,_length);
    *(btAry.data());
    m_port->write(btAry);
}
