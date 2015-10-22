#include "modu_eeg.h"
#include <QFile>
#include <QDataStream>
#include <QtCore>
#include <QObject>
#include "color.h"
#include "mainform.h"
#include "rsc_modu/modu_thread.h"
#define EEG_PARSE_STATE_IDDLE 0
#define EEG_PARSE_STATE_HEAD0 1
#define EEG_PARSE_STATE_HEAD1 2
#define EEG_PARSE_STATE_DATA 3

CEegModule::CEegModule(QWidget *parent)
{
    pMainForm = parent;
    m_eeg_cfg = new CEegModuleCfg;
    m_port = new Posix_QextSerialPort(EEG_MODULE_DATA_PORT_NAME,QextSerialBase::Polling);
    m_port->open(QIODevice::ReadWrite);
    m_port->setBaudRate((BaudRateType)115200);
    m_port->setDataBits(DATA_8);
    m_port->setParity(PAR_NONE);
    m_port->setStopBits(STOP_1);
    m_port->setFlowControl(FLOW_OFF);
    m_port->setTimeout(10);
    m_port->flush();
    m_eeg_wave_cnt = 0;
    iParseState = EEG_PARSE_STATE_IDDLE;
    iEegWavCnt=0;
    uiFrameCnt = 0;
    f_setDefaultCfg();

    //get ecg file config
    {
        QFile file((EEG_MODULE_CFG_DOC));
        if(file.open(QIODevice::ReadOnly))
        {
            CEegModuleCfg tempCfg;
            QDataStream inout(&file);
            int magic;
            inout >> magic;
            if(magic == 0x12345678)
            {
                inout.readRawData((char *)&tempCfg,sizeof(CEegModuleCfg));
            }
            memcpy(m_eeg_cfg,&tempCfg,sizeof(CEegModuleCfg));
            file.close();
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            QDataStream inout(&file);
            int magic = 0x12345678;
            inout<<magic;
            inout.writeRawData((char *)m_eeg_cfg,sizeof(CEegModuleCfg));
            file.close();
        }
    }
    /*
    for(int i =0;i<EEG_MODULE_WAVE_NUM;i++)
    {
        m_wave_plot[i] = new WavePlotter(parent);
        m_wave_plot_setting[i] = new WavePlotSettings();
        m_wave_plot_setting[i]->maxX = 4300;
        m_wave_plot_setting[i]->minX = 0;
        m_wave_plot_setting[i]->maxY = 0xff;
        m_wave_plot_setting[i]->minY = 0;
        m_wave_plot[i]->setPlotSettings(*m_wave_plot_setting[i]);
        m_wave_plot[i]->setGeometry(m_eeg_cfg->m_wave_rec[i]);//();
        m_wave_plot[i]->setWaveColor(0,GLB_COLOR(m_eeg_cfg->m_wave_color[i]));
        if(m_eeg_cfg->m_wave_plot_enable[i])
        {
            m_wave_plot[i]->show();
        }


    }
    m_wave_plot[0]->setWaveName("EEG1 ");
    m_wave_plot[1]->setWaveName("EEG2 ");
    m_wave_plot[2]->setWaveName("EEG3 ");
    m_wave_plot[3]->setWaveName("EEG4 ");
    m_wave_plot[4]->setWaveName("EEG5 ");
    m_wave_plot[5]->setWaveName("EEG6 ");
    m_wave_plot[6]->setWaveName("EEG7");
    m_wave_plot[7]->setWaveName("EEG8");
*/
    m_modu_data_file.setFileName("/home/data/eeg.dat");
    m_modu_data_file.open(QIODevice::ReadWrite);
    QDataStream inout(&m_modu_data_file);
    inout.readRawData(eegdata,1024);

}

 CEegModule::~CEegModule()
{

     delete m_eeg_cfg;
}
 void  CEegModule::f_set_eeg_wave_layout()
 {
     int iDisplay = f_get_wave_mode();

    QString name[8];
    switch (iDisplay) {
    case 0:
        name[0].append("FP1");
        name[1].append("Fp2");
        name[2].append("F3");
        name[3].append("F4");
        name[4].append("C3");
        name[5].append("C4");
        name[6].append("P3");
        name[7].append("P4");
        break;
    case 1:
        name[0].append("O1");
        name[1].append("O2");
        name[2].append("F7");
        name[3].append("F8");
        name[4].append("T3");
        name[5].append("T4");
        name[6].append("T5");
        name[7].append("T6");
        break;
    case 2:
        name[0].append("AF3");
        name[1].append("AF4");
        name[2].append("FC3");
        name[3].append("FC4");
        name[4].append("CP3");
        name[5].append("CP4");
        name[6].append("PO3");
        name[7].append("PO4");
        break;
    case 3:
        name[0].append("FT7");
        name[1].append("FT8");
        name[2].append("CP7");
        name[3].append("CP8");
        name[4].append("Fz");
        name[5].append("Cz");
        name[6].append("Pz");
        name[7].append("Oz");
        break;
    case 4:
        name[0].append("FP1");
        name[1].append("Fp2");
        name[2].append("肌电");
        name[3].append("左眼");
        name[4].append("右眼");
        name[5].append("呼吸1");
        name[6].append("鼾声");
        name[7].append("呼吸2");
        break;
    default:
        break;
    }


     for(int i=0;i<EEG_MODULE_WAVE_NUM;i++)
     {
         if(m_eeg_cfg->m_wave_plot_enable[i] == true)
         {
             g_WavePlotter->setWaveColor(m_eeg_cfg->m_wave_indx[i],
                                         GLB_COLOR(m_eeg_cfg->m_wave_color[i]));

         }
     }
     if(m_eeg_cfg->m_wave_plot_enable[0])
     {
         g_WavePlotter->setWaveName(m_eeg_cfg->m_wave_indx[0],name[0],
                 m_eeg_cfg->m_wave_rec[0].y(),m_eeg_cfg->m_wave_rec[0].height());
     }

     if(m_eeg_cfg->m_wave_plot_enable[1])
     g_WavePlotter->setWaveName(m_eeg_cfg->m_wave_indx[1],name[1],m_eeg_cfg->m_wave_rec[1].y(),m_eeg_cfg->m_wave_rec[1].height());
     if(m_eeg_cfg->m_wave_plot_enable[2])
     g_WavePlotter->setWaveName(m_eeg_cfg->m_wave_indx[2],name[2],m_eeg_cfg->m_wave_rec[2].y(),m_eeg_cfg->m_wave_rec[2].height());
     if(m_eeg_cfg->m_wave_plot_enable[3])
     g_WavePlotter->setWaveName(m_eeg_cfg->m_wave_indx[3],name[3],m_eeg_cfg->m_wave_rec[3].y(),m_eeg_cfg->m_wave_rec[3].height());
     if(m_eeg_cfg->m_wave_plot_enable[4])
     g_WavePlotter->setWaveName(m_eeg_cfg->m_wave_indx[4],name[4],m_eeg_cfg->m_wave_rec[4].y(),m_eeg_cfg->m_wave_rec[4].height());
     if(m_eeg_cfg->m_wave_plot_enable[5])
     g_WavePlotter->setWaveName(m_eeg_cfg->m_wave_indx[5],name[5],m_eeg_cfg->m_wave_rec[5].y(),m_eeg_cfg->m_wave_rec[5].height());
     if(m_eeg_cfg->m_wave_plot_enable[6])
     g_WavePlotter->setWaveName(m_eeg_cfg->m_wave_indx[6],name[6],m_eeg_cfg->m_wave_rec[6].y(),m_eeg_cfg->m_wave_rec[6].height());
     if(m_eeg_cfg->m_wave_plot_enable[7])
     g_WavePlotter->setWaveName(m_eeg_cfg->m_wave_indx[7],name[7],m_eeg_cfg->m_wave_rec[7].y(),m_eeg_cfg->m_wave_rec[7].height());



 }
void CEegModule::f_set_eeg_wave_color()
{
    for(int i=0;i<EEG_MODULE_WAVE_NUM;i++)
    {
        if(m_eeg_cfg->m_wave_plot_enable[i] == true)
        {
            g_WavePlotter->setWaveColor(m_eeg_cfg->m_wave_indx[i],
                                        GLB_COLOR(m_eeg_cfg->m_wave_color[i]));
        }
    }
}
void CEegModule::f_reset_value()
{
    m_eeg_val.m_eeg_flg = 30;//1	30，代表脑电
    m_eeg_val.m_eeg_flg_1 = 8;//1	8
    for(int i = 0;i<32;i++)
    {
        for(int j = 0;j<32;j++)
        {
            m_eeg_val.m_eeg_wave[i][j] = -127;//16×32	32 通道脑电波形，每通道长度为16字节。通道次序为： Fp1、F3、C3、P3、Fp2、F4、C4、P4、O1、F7、T3 、T5、O2、F8、T4、T6、AF3、FC3、CP3、PO3、AF4、FC4、CP4、PO4、FT7、CP7、Fz、Pz、FT8、CP8、Cz 、Oz（前十六个字节为第一通道数据，依次类推）
        }
    }

    //Int	4×32	32 通道脑电增益，单位0.01
    m_eeg_val.m_eeg_layout = 0;//1	屏幕布局，0～5 分别对应：标准界面、大字体界面、呼吸氧合图界面、血压趋势界面、趋势表界面、全屏多导界面
    for(int i = 0;i<32;i++)
    {
        m_eeg_val.m_reserve0[i] = 0;//32	保留
    }

    m_eeg_val.m_reserve1 = 0;//1	0
    m_eeg_val.m_reserve2 = 1;//1	1
}

void CEegModule::f_read_data()
{

    QByteArray data ;
    data = m_port->readAll();
    /*data.clear();
    char eeg[36] = {0x55,0xaa,0x0f,
                   0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
                   0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
                   0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
                   0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
                   0x0e
                  };

    data.append(eeg,36);*/
    /*data.clear();
    data.append(eegdata,1024);*/
    CMainForm *p= (CMainForm *)pMainForm;
    QString len = QString::number(data.count(),10);
    //p->TextLabel_bar_alarm_III->setText(len);
    if(data.count()>0)
    {
        p->TextLabel_bar_alarm_II->setText("eeg "+len);
        //QString val = QString::number(data[0],10);
        //p->TextLabel_bar_alarm_III->setText(val);
    }
    f_eeg_data_processing(data);
}

void CEegModule::f_parse_data()
{

}

void CEegModule::f_Enable(bool bEnable)
{

}

void CEegModule::f_isEnabled(bool *)
{

}

int  CEegModule::f_open_data_src()
{
    return 0;
}

void CEegModule::f_close_data_src()
{

}


void CEegModule::f_setDefaultCfg()
{
    if(!m_eeg_cfg)
        return;
    m_eeg_cfg->m_eeg_type = 0;
    m_eeg_cfg->m_eeg_display = 0;
    m_eeg_cfg->m_eeg_wave_sensitive = 0;
    m_eeg_cfg->m_eeg_wave_speed = 1;
    m_eeg_cfg->m_eeg_wave_filter = 1;
    m_eeg_cfg->m_eeg_time_const = 1;
    m_eeg_cfg->m_eeg_trap_en = true;
    m_eeg_cfg->m_eeg_spire_filter = 0;
    m_eeg_cfg->m_eeg_spire_time_const = 1;
    m_eeg_cfg->m_eeg_snore_time_const = 1;
    m_eeg_cfg->m_eeg_snore_trap_en = true; //脑电鼾声陷波,false = 关，true = 开

     m_eeg_cfg->m_eeg_coef = 1.4;  //脑电系数
     m_eeg_cfg->m_eeg_spire_coef =1.4 ; //脑电呼吸系数
     m_eeg_cfg->m_eeg_emg_coef = 1.4; //肌电系数
     m_eeg_cfg->m_eeg_eyemove_coef = 1.4; //眼动系数
     m_eeg_cfg->m_eeg_snore_coef = 1.4; //鼾声系数
     for(int i=0;i<EEG_MODULE_WAVE_NUM;i++)
     {
         m_eeg_cfg->m_wave_color[i] = GLB_COLOR_GREEN; // wave color
         m_eeg_cfg->m_wave_rec[i].setRect(0,50*i,730,48);
         m_eeg_cfg->m_wave_indx[i] = 0;
         m_eeg_cfg->m_wave_plot_enable[i] = true;
     }
}
void CEegModule::f_set_eeg_def_cfg()
{
    f_setDefaultCfg();

    QFile file(EEG_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_eeg_cfg,sizeof(CEegModuleCfg));
    file.close();
}

void CEegModule::f_set_eeg_cfg(CEegModuleCfg cfg)
{
    memcpy(m_eeg_cfg,&cfg,sizeof(CEegModuleCfg));
    QFile file(EEG_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_eeg_cfg,sizeof(CEegModuleCfg));
    file.close();

    f_set_eeg_wave_layout();
}

void CEegModule::f_get_eeg_cfg( CEegModuleCfg* cfg)
{
    memcpy(cfg,m_eeg_cfg,sizeof(CEegModuleCfg));
}

void CEegModule::f_plot_eeg_wave(char * data)
{
    double y[8] = {0};
    char tmp[8] = {0};
    short value = 0;
    bool limit_flag = false;
    QVector<QPointF> tempint;

    if(!m_eeg_cfg->m_wave_plot_enable[0])
        return;
    //V
    double x=0;

    if(m_eeg_cfg->m_eeg_wave_speed == 0) //15mm/s
    {
        x = 0.38884943182;//1*730/(500*17.6); // (730[pix]/220[mm])* 12.5[mm/s] / (500[Byte/s]) = pix/Byte
    }
    else if(m_eeg_cfg->m_eeg_wave_speed == 1) // 30mm/s
    {
        x = 0.7776988636;//1*730/(500*8.8);
    }
    else if(m_eeg_cfg->m_eeg_wave_speed == 2) // 60mm/s
    {
        x= 1.55539772727;//1*730/(500*4.4);
    }
    for(int i = 0;i<EEG_MODULE_WAVE_NUM;i++)
    {
        m_eeg_pos[i] +=x;
        if(m_eeg_pos[i]>= (WAVE_WIDGET_WIDTH_PIX-1))
        {
            m_eeg_pos[i] -= (WAVE_WIDGET_WIDTH_PIX-1);
            limit_flag = true;

        }
    }
    int iDisplay = f_get_wave_mode();
    if(iDisplay == 0)//1-8
    {
        for(int i = 0;i<8;i++)
        {
            value = tmp[i] = data[i];
            value += 0x7f;
            value = value>255?(255):(value);
            y[i] =m_eeg_cfg->m_wave_rec[i].height()+(m_eeg_cfg->m_wave_rec[i].height()>>1)
                                                                                       - (value)*m_eeg_cfg->m_wave_rec[i].height() / 256;
        }
    }
    else if(iDisplay == 1)//9-16
    {
        for(int i = 0;i<8;i++)
        {
            value = tmp[i] = data[i+8];
            value += 0x7f;
            value = value>255?(255):(value);
            y[i] =m_eeg_cfg->m_wave_rec[i].height()+(m_eeg_cfg->m_wave_rec[i].height()>>1)
                    - (value)*m_eeg_cfg->m_wave_rec[i].height() / 256;
        }
    }
    else if(iDisplay == 2)//17-24
    {
        for(int i = 0;i<8;i++)
        {
            value =  tmp[i] = data[i+16];
            value += 0x7f;
            value = value>255?(255):(value);
            y[i] =m_eeg_cfg->m_wave_rec[i].height()+(m_eeg_cfg->m_wave_rec[i].height()>>1)
                    - (value)*m_eeg_cfg->m_wave_rec[i].height() / 256;
        }
    }
    else if(iDisplay == 3)//17-24
    {
        for(int i = 0;i<8;i++)
        {
            value = tmp[i] = data[i+24];
            value += 0x7f;
            value = value>255?(255):(value);
            y[i] =m_eeg_cfg->m_wave_rec[i].height()+(m_eeg_cfg->m_wave_rec[i].height()>>1)
                    - (value)*m_eeg_cfg->m_wave_rec[i].height() / 256;
        }
    }
    else if(iDisplay == 4)
    {
        tmp[0] = data[0];
        tmp[1] = data[1];
        for(int i = 2;i<8;i++)
        {
            tmp[i] = data[i+17];
        }
        value = tmp[0];
        value += 0x7f;
        value = value>255?(255):(value);
        y[0] =m_eeg_cfg->m_wave_rec[0].height()+(m_eeg_cfg->m_wave_rec[0].height()>>1)
                - (value)*m_eeg_cfg->m_wave_rec[0].height() / 256;
        value = tmp[1];
        value += 0x7f;
        value = value>255?(255):(value);
        y[1] =m_eeg_cfg->m_wave_rec[1].height()+(m_eeg_cfg->m_wave_rec[1].height()>>1)
                - (value)*m_eeg_cfg->m_wave_rec[1].height() / 256;
        //emg
        tmp[2] *=m_eeg_cfg->m_eeg_emg_coef ;
        value = tmp[2];
        value += 0x7f;
        value = value>255?(255):(value);
        y[2] =m_eeg_cfg->m_wave_rec[2].height()+(m_eeg_cfg->m_wave_rec[2].height()>>1)
                - (value)*m_eeg_cfg->m_wave_rec[2].height() / 256;

        //left eye move
        tmp[3] *= m_eeg_cfg->m_eeg_eyemove_coef;
        value = tmp[3];
        value += 0x7f;
        value = value>255?(255):(value);
        y[3] =m_eeg_cfg->m_wave_rec[3].height()+(m_eeg_cfg->m_wave_rec[3].height()>>1)
                - (value)*m_eeg_cfg->m_wave_rec[3].height() / 256;

        //right eye move
        tmp[4] *= m_eeg_cfg->m_eeg_eyemove_coef;
        value = tmp[4];
        value += 0x7f;
        value = value>255?(255):(value);
        y[4] =m_eeg_cfg->m_wave_rec[4].height()+(m_eeg_cfg->m_wave_rec[4].height()>>1)
                - (value)*m_eeg_cfg->m_wave_rec[4].height() / 256;

        //spire1
        tmp[5]*=m_eeg_cfg->m_eeg_spire_coef;
        value = tmp[5];
        value += 0x7f;
        value = value>255?(255):(value);
        y[5] =m_eeg_cfg->m_wave_rec[5].height()+(m_eeg_cfg->m_wave_rec[5].height()>>1)
                - (value)*m_eeg_cfg->m_wave_rec[5].height() / 256;
        //snore
        tmp[6] *= m_eeg_cfg->m_eeg_snore_coef;
        value = tmp[6];
        value += 0x7f;
        value = value>255?(255):(value);
        y[6] =m_eeg_cfg->m_wave_rec[6].height()+(m_eeg_cfg->m_wave_rec[6].height()>>1)
                - (value)*m_eeg_cfg->m_wave_rec[6].height() / 256;
        //spire2
        tmp[7] *= m_eeg_cfg->m_eeg_spire_coef;
        value = tmp[7];
        value += 0x7f;
        value = value>255?(255):(value);
        y[7] =m_eeg_cfg->m_wave_rec[7].height()+(m_eeg_cfg->m_wave_rec[7].height()>>1)
                - (value)*m_eeg_cfg->m_wave_rec[7].height() / 256;
    }

    if(limit_flag == true)
    {
        for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
        {
            if(m_eeg_cfg->m_wave_plot_enable[i])
            {
                tempint.append(QPointF(x,y[i]));
                {
                    //QMutexLocker locker(&m_mutex_wave_ecg);
                    //m_ecg_data_to_draw[i].append(QPointF(m_ecg_pos[i],y[i]));
                    //
                }
                //g_WavePlotter->setCurveData(m_eeg_cfg->m_wave_indx[i], tempint,0);
                g_drawThread->f_draw_eeg(m_eeg_cfg->m_wave_indx[i], tempint,0);

                tempint.clear();
            }
            m_eeg_last_pos[i] = m_eeg_pos[i];
            //m_eeg_last_pos[i] = 0;

        }
    }
    if(m_eeg_pos[0] >= (m_eeg_last_pos[0] +1))//plot 1 pix,do not plot if less than 1pix.
    {


        for(int i=0;i<EEG_MODULE_WAVE_NUM;i++)
        {
            if(m_eeg_cfg->m_wave_plot_enable[i])
            {
                tempint.append(QPointF(x,y[i]));
                {
                    //QMutexLocker locker(&m_mutex_wave_ecg);
                    //m_ecg_data_to_draw[i].append(QPointF(m_ecg_pos[i],y[i]));
                    //m_eeg_last_pos[i] = m_eeg_pos[i];

                }
                //g_WavePlotter->setCurveData(m_eeg_cfg->m_wave_indx[i], tempint,m_eeg_pos[i]);
                g_drawThread->f_draw_eeg(m_eeg_cfg->m_wave_indx[i], tempint,m_eeg_pos[i]);
                tempint.clear();
            }
            m_eeg_last_pos[i] = m_eeg_pos[i];
        }
    }
}
int CEegModule::f_get_wave_mode()
{
    int iDisplay = 0;
    switch(m_eeg_cfg->m_eeg_type)
    {
    case 0:
           iDisplay = 0; // 1-8
        break;
    case 1:
        if(m_eeg_cfg->m_eeg_display == 1)
        {
            iDisplay = 4;
        }
        else
        {
            iDisplay = 0;
        }
        break;
    case 2:
        if(m_eeg_cfg->m_eeg_display == 1)
        {
            iDisplay = 1;
        }
        else
        {
            iDisplay = 0;
        }
        break;
    case 3:
        if(m_eeg_cfg->m_eeg_display == 1)
        {
            iDisplay = 1;
        }
        else if(m_eeg_cfg->m_eeg_display == 2)
        {
            iDisplay = 4;
        }
        else
        {
            iDisplay = 0;
        }
        break;
    case 4:
        if(m_eeg_cfg->m_eeg_display == 1)
        {
            iDisplay = 1;
        }
        else if(m_eeg_cfg->m_eeg_display == 2)
        {
            iDisplay = 2;
        }
        else if(m_eeg_cfg->m_eeg_display == 3)
        {
            iDisplay = 3;
        }
        else
        {
            iDisplay = 0;
        }
        break;
    default:
        break;
    }
    return iDisplay;
}

void CEegModule::f_eeg_data_processing(QByteArray eeg_data)
{
    char * data = eeg_data.data();
    for(int i = 0;i<eeg_data.count();i++)
    {
        unsigned char temp = data[i];
        switch(iParseState)
        {
        case EEG_PARSE_STATE_IDDLE:
            if(temp == 0x55)
            {
                iParseState = EEG_PARSE_STATE_HEAD0;
            }
            else
            {
                iParseState = EEG_PARSE_STATE_IDDLE;
            }

            break;
        case EEG_PARSE_STATE_HEAD0:
            if(temp == 0xaa)
            {
                iParseState = EEG_PARSE_STATE_HEAD1;
            }
            else
            {
                iParseState = EEG_PARSE_STATE_IDDLE;
            }
            break;
        case EEG_PARSE_STATE_HEAD1:
            if(temp == 0x0f)
            {
                 iParseState = EEG_PARSE_STATE_DATA;
                 uiSumchck = 0;//0x55+0xaa+0x0f;
            }
            else if(0x12==temp) // i+=7;
            {
            }
            else if(0x13==temp)//i+=15;
            {

            }
            else if(0x14==temp) //i+=14;
            {

            }
            else if(0x15==temp)//i+=10;
            {

            }
            else
            {
                iParseState = EEG_PARSE_STATE_IDDLE;
            }
            break;
        case EEG_PARSE_STATE_DATA:


            if((iEegWavCnt ==32))
            {


                iParseState = EEG_PARSE_STATE_IDDLE;
                if(((uiSumchck&0xff) == temp))
                {
                    g_EegModule->f_plot_eeg_wave((char *)m_eeg_val.m_eeg_wave[uiFrameCnt]);
                    //CMainForm *p= (CMainForm *)pMainForm;
                    //p->TextLabel_bar_alarm_III->setText("send plot data");
                    uiFrameCnt ++;
                    if(uiFrameCnt >=16)
                    {
                        uiFrameCnt = 0;
                        //emit signal_tcp_data_ready

                    }
                }
                uiSumchck = 0;
                iEegWavCnt = 0;
            }
            else
            {
                uiSumchck += temp;
                m_eeg_val.m_eeg_wave[uiFrameCnt][iEegWavCnt] = temp;
                iEegWavCnt ++;
            }
            break;
        default:
            break;
        }
    }


    /*
    if(num2>0)
    {
        static  int8_t data_record[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
        for(uchar z=0;z<32;z++)
        {
                DRAW_EEG_WAVE[z][iEegWavCnt]=-127;
        }

        char *buff=temp.data();
        char num3;
        static uint count_wave=0;
        uchar calculate_num=0,record_num=0;
        for(int i=0;i<num2;)
        {
            if((0x55==buff[i]))
            {
                if(0xaa==(uchar)(buff[i+1]))
                {
                    num3=0;
                    if(0x0f==buff[i+2])
                    {
                        for(unsigned int j=3;j<35;j++)
                            num3+=buff[i+j];
                        if((num3)==(buff[i+35]))
                        {

                            uchar EEG_Wave_TCP_i=0;
                            for(;EEG_Wave_TCP_i<shuimian_data;EEG_Wave_TCP_i++ )
                            {
                                static float  dat=0;
                                dat=((uchar)buff[(i+3)+EEG_Wave_TCP_i]-123)*eegseting_xishu[0];
                                data_record[EEG_Wave_TCP_i]=dat;
                                sub_filter_[EEG_Wave_TCP_i].HigtFilter(data_record +EEG_Wave_TCP_i);
                                sub_filter_[EEG_Wave_TCP_i].LowFilter(data_record+EEG_Wave_TCP_i);
                                if(Naodian_xianbo_set)
                                    sub_filter_[EEG_Wave_TCP_i].Notch_50Hz(data_record+EEG_Wave_TCP_i);
                            }
                            if(shuimian_flag)
                            {
                                {
                                    static float  dat=0;
                                    //1// //肌电
                                    dat=((uchar)buff[(i+3)+EEG_Wave_TCP_i]-123)*eegseting_xishu[1];
                                    data_record[EEG_Wave_TCP_i]=dat;
                                    EEG_Wave_TCP_i++;

                                    //2// //左眼
                                    dat=((uchar)buff[(i+3)+EEG_Wave_TCP_i]-123)*eegseting_xishu[2];
                                    data_record[EEG_Wave_TCP_i]=dat;
                                    EEG_Wave_TCP_i++;

                                    //3// //右眼
                                    dat=((uchar)buff[(i+3)+EEG_Wave_TCP_i]-123)*eegseting_xishu[3];
                                    data_record[EEG_Wave_TCP_i]=dat;
                                    EEG_Wave_TCP_i++;

                                    //4// //呼吸1
                                    dat=((uchar)buff[(i+3)+EEG_Wave_TCP_i]-123)*eegseting_xishu[4];
                                    data_record[EEG_Wave_TCP_i]=dat;
//                                    sub_filter_[EEG_Wave_TCP_i].HigtFilter(data_record+EEG_Wave_TCP_i);
//                                    sub_filter_[EEG_Wave_TCP_i].LowFilter(data_record+EEG_Wave_TCP_i);
//                                    if(Huxi_xianbo_set)
//                                        sub_filter_[EEG_Wave_TCP_i].Notch_50Hz(data_record+EEG_Wave_TCP_i);
                                    EEG_Wave_TCP_i++;

                                    //5// //鼾声
                                    dat=((uchar)buff[(i+3)+EEG_Wave_TCP_i]-123)*eegseting_xishu[5];
                                    data_record[EEG_Wave_TCP_i]=dat;
//                                    sub_filter_[EEG_Wave_TCP_i].HigtFilter(data_record+EEG_Wave_TCP_i);
//                                    if(Hansheng_xianbo_set)
//                                        sub_filter_[EEG_Wave_TCP_i].Notch_50Hz(data_record+EEG_Wave_TCP_i);
                                    EEG_Wave_TCP_i++;

                                    //1// //呼吸
                                    dat=((uchar)buff[(i+3)+EEG_Wave_TCP_i]-123)*eegseting_xishu[6];
                                    data_record[EEG_Wave_TCP_i]=dat;
//                                    sub_filter_[EEG_Wave_TCP_i].HigtFilter(data_record+EEG_Wave_TCP_i);
//                                    sub_filter_[EEG_Wave_TCP_i].LowFilter(data_record+EEG_Wave_TCP_i);
//                                    if(Huxi_xianbo_set)
//                                        sub_filter_[EEG_Wave_TCP_i].Notch_50Hz(data_record+EEG_Wave_TCP_i);

                                  }
                            }

                           // 滤波函数在此处调用


                            pthread_mutex_lock(&mutex_TCP_ByteArray);

                            for(uchar EEG_Wave_TCP_i=0;EEG_Wave_TCP_i<32;EEG_Wave_TCP_i++ )
                                ByteArray_EEG_Wave_TCP[EEG_Wave_TCP_i].append(data_record[EEG_Wave_TCP_i]);
                            pthread_mutex_unlock(&mutex_TCP_ByteArray);




                            {
                                if(count_wave%2)//1
                                {
                                    for(uchar z=0;z<32;z++)
                                    {
                                        if(DRAW_EEG_WAVE[z][iEegWavCnt]<data_record[z])
                                            DRAW_EEG_WAVE[z][iEegWavCnt]=data_record[z];
                                    }
                                    iEegWavCnt++;
                                }
                                else//0
                                {
                                    for(uchar z=0;z<32;z++)
                                    {
                                        DRAW_EEG_WAVE[z][iEegWavCnt]=data_record [z];
                                    }
                                    calculate_num++;
                                }
                            }

                            count_wave++;
                            i+=36;
//                            if(!(iEegWavCnt%40))
//                            SLEEP;
                        }
                        else if((num2-i)<=36)
                        {
                            EEG_breakpoint=num2-i;
                            EEG_breakpoint_buff= QByteArray::fromRawData(buff+i, EEG_breakpoint);
                            *(EEG_breakpoint_buff.data());
                            i+=36;
                        }
                        else i++;

                    }
                    else if(0x12==buff[i+2])
                        i+=7;
                    else if(0x13==buff[i+2])
                        i+=15;
                    else if(0x14==buff[i+2])
                        i+=14;
                    else if(0x15==buff[i+2])
                        i+=10;
                    else
                    {
                        if((num2-i)<=36)
                        {
                            EEG_breakpoint=num2-i;
                            EEG_breakpoint_buff= QByteArray::fromRawData(buff+i, EEG_breakpoint);
                            *(EEG_breakpoint_buff.data());
                            i+=36;
                        }
                        i++;
                    }
                }
                else if((num2-i)<=36)
                {
                    EEG_breakpoint=num2-i;
                    EEG_breakpoint_buff= QByteArray::fromRawData(buff+i, EEG_breakpoint);
                    *(EEG_breakpoint_buff.data());
                    i =num2;
                }
                else i++;

            }
            else
                i++;
        }
        if(count_wave%2)
        {
            count_wave=1;
        }
        else
            count_wave=0;
        for(uchar z=0;z<32;z++)
        {

                 data_record[z]=DRAW_EEG_WAVE[z][iEegWavCnt-1];
        }

     }
    else
    {
//        pthread_mutex_lock(&mutex_RECORD_ByteArray);
        //Record_Communication_interrupt=1;
//        pthread_mutex_unlock(&mutex_RECORD_ByteArray);
    }
    */
}
void CEegModule::EEG_WriteCom(char *  ,int  )
{

}
