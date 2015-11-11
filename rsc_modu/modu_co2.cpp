#include "modu_co2.h"
#include "mainform.h"
#include "modu_thread.h"
#define CO2_PARSE_STATE_IDDLE 0
#define CO2_PARSE_STATE_HEAD0 1
#define CO2_PARSE_STATE_HEAD1 2
#define CO2_PARSE_STATE_DATA 3

CCO2Modu::CCO2Modu(QWidget *parent)
{

    m_modu_cfg = new stCO2ModuCfg;

    f_setDefaultCfg();

    //get ecg file config
    {
        QFile file((CO2_MODULE_CFG_DOC));
        if(file.open(QIODevice::ReadOnly))
        {
            stCO2ModuCfg tempCfg;
            QDataStream inout(&file);
            int magic;
            inout >> magic;
            if(magic == 0x12345678)
            {
                inout.readRawData((char *)&tempCfg,sizeof(stCO2ModuCfg));
            }
            memcpy(m_modu_cfg,&tempCfg,sizeof(stCO2ModuCfg));
            file.close();
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            QDataStream inout(&file);
            int magic = 0x12345678;
            inout<<magic;
            inout.writeRawData((char *)m_modu_cfg,sizeof(stCO2ModuCfg));
            file.close();
        }
    }
    m_port = new Posix_QextSerialPort(CO2_MODULE_DATA_PORT_NAME);
    m_port->open(QIODevice::ReadWrite);
    m_port->setBaudRate((BaudRateType)115200);
    m_port->setDataBits(DATA_8);
    m_port->setParity(PAR_NONE);
    m_port->setStopBits(STOP_1);
    m_port->setFlowControl(FLOW_OFF);
    m_port->setTimeout(10);
    m_port->flush();

    iParseState = 0;
    for(int i = 0; i< CO2_MAX_DATA_BYTES;i++)
    {
        cmdbuf[i] = 0;
    }
    cmdcount = 0;
    cmdlen = 0;
}

void CCO2Modu::f_setDefaultCfg()
{
    m_modu_cfg->m_alarm_enable = true;
    m_modu_cfg->m_wave_amp = 0;
    m_modu_cfg->m_alarm_high = 100;
    m_modu_cfg->m_alarm_low = 60;
    m_modu_cfg->m_wave_speed = 0;


    m_modu_cfg->m_work_mode = 0;
    m_modu_cfg->m_ssphyxia_alarm = 1;
    m_modu_cfg->m_wave_amp = 0;
    m_modu_cfg->m_wave_speed = 1;
    m_modu_cfg->m_modu_unit = 0;
    m_modu_cfg->m_balance_air = 0;
    m_modu_cfg->m_wave_mode = 0;
    m_modu_cfg->m_co2_compens = 0;
    m_modu_cfg->m_anesthetic_val = 0;
    m_modu_cfg->m_temp_compens = 0;
    m_modu_cfg->m_air_pressure = 0;
    m_modu_cfg->m_correct_flg = false;
    m_modu_cfg->m_wave_enable = true;
    m_wave_pos = 0;
    m_wave_last_pos = 0;
    m_modu_cfg->m_alarm_breathrate_en = true;
    m_modu_cfg->m_alarm_breathrate_high = 60;
    m_modu_cfg->m_alarm_breathrate_low = 10;
    m_modu_cfg->m_alarm_humo_en = true;
    m_modu_cfg->m_alarm_humo_high = 60;
    m_modu_cfg->m_alarm_humo_low = 10;
    m_modu_cfg->m_alarm_xiru_en = true;
    m_modu_cfg->m_alarm_xiru_high = 60;
    m_modu_cfg->m_alarm_xiru_low = 0;
}
 void CCO2Modu::f_reset_value()
 {
     m_modu_val.m_co2_flg = 26;//1	26，代表CO2
     m_modu_val.m_co2_flg_1 = 5;//1	5
     m_modu_val.m_co2_flg_2 = 1;//1	1
     for(int i = 0;i< 256;i++)
     {
         m_modu_val.m_co2_wave[256];//256	CO2波形，长度为256字节
     }

     m_modu_val.m_Etco2_value = 0xff;//1	EtCO2参数数值
     m_modu_val.m_Fico2_value = 0xff;//2	FiCO2参数数值
     m_modu_val.m_spirerate_value = 0xff;//2	气道呼吸率
     m_modu_val.m_alarm_Etco2_high =m_modu_cfg->m_alarm_humo_high;//2	EtCO2报警上限
     m_modu_val.m_alarm_Etco2_low =m_modu_cfg->m_alarm_humo_low;//2	EtCO2报警上限
     m_modu_val.m_alarm_Etco2_level = 0;//2	EtCO2报警级别，1～3分别对应高、中、低级报警
     m_modu_val.m_alarm_Fico2_high = m_modu_cfg->m_alarm_xiru_high;//2	FiCO2报警上限
     m_modu_val.m_alarm_Fico2_low = m_modu_cfg->m_alarm_xiru_low;//2	FiCO2报警上限
     m_modu_val.m_alarm_Fico2_level = 0;//2	FiCO2报警级别，1～3分别对应高、中、低级报警
     m_modu_val.m_alarm_spirerate_high = m_modu_cfg->m_alarm_high;//2	气道呼吸率报警上限
     m_modu_val.m_alarm_spirerate_low = m_modu_cfg->m_alarm_low;//2	气道呼吸率报警上限
     m_modu_val.m_alarm_spirerate_level = 0;//2	气道呼吸率报警级别，1～3分别对应高、中、低级报警
     m_modu_val.m_air_press = 0;//2	大气压力，单位mmHg
     m_modu_val.reserve0[0] = 0;//2	保留
     m_modu_val.reserve0[1] = 0;
 }

void CCO2Modu::f_set_def_cfg()
{
    f_setDefaultCfg();
    QFile file(CO2_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_modu_cfg,sizeof(stCO2ModuCfg));
    file.close();
}

void CCO2Modu::f_set_cfg(stCO2ModuCfg cfg)
{
    memcpy(m_modu_cfg,&cfg,sizeof(stCO2ModuCfg));
    QFile file(CO2_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_modu_cfg,sizeof(stCO2ModuCfg));
    file.close();
}

void CCO2Modu::f_get_cfg( stCO2ModuCfg* cfg)
{
    memcpy(cfg,m_modu_cfg,sizeof(stCO2ModuCfg));
}
void CCO2Modu::f_set_wave_layout()
{
    if(m_modu_cfg->m_wave_enable == true)
    {
        g_WavePlotter->setWaveColor(m_modu_cfg->m_wave_indx,
                                    GLB_COLOR(m_modu_cfg->m_wave_color));
        g_WavePlotter->setWaveName(m_modu_cfg->m_wave_indx,"CO2",m_modu_cfg->m_wave_rec.y(),m_modu_cfg->m_wave_rec.height());
    }
    m_wave_last_pos = m_wave_pos = 0;
}

void CCO2Modu::f_plot_co2_wave(int data)
{
    double y = 0;
    bool limit_flag = false;
    double dstep  = 0;
    QVector<QPointF> tempint;

    y = m_modu_cfg->m_wave_rec.height()-data * m_modu_cfg->m_wave_rec.height() / 256; //

    //V
    double x=0;
    if(m_modu_cfg->m_wave_speed == 0) //12.5mm/s
    {
        x = 0.3181818;//1*730/(500*17.6); // (730[pix]/220[mm])* 12.5[mm/s] / (125[Byte/s]) = pix/Byte
    }
    else if(m_modu_cfg->m_wave_speed == 1) // 25mm/s
    {
        x = 0.66363636;//1*730/(125*8.8);
    }


    m_wave_pos +=x;
    if(m_wave_pos>= (WAVE_WIDGET_WIDTH_PIX-1))
    {
        m_wave_pos -= (WAVE_WIDGET_WIDTH_PIX-1);
        limit_flag = true;

    }

/*
    if(limit_flag == true)
    {
        if(m_modu_cfg->m_wave_enable)
        {
            tempint.append(QPointF(x,y));
            //QMutexLocker locker(&m_mutex_wave_spo2);
            //m_spo2_data_to_draw.append(QPointF(m_wave_pos,y));
            //g_WavePlotter->setCurveData(m_modu_cfg->m_wave_indx,tempint,0);
            g_drawThread->f_draw_co2(m_modu_cfg->m_wave_indx,tempint,0);
            tempint.clear();
        }
        m_wave_last_pos = 0;

    }
    if(m_wave_pos >= (m_wave_last_pos +1))//plot 1 pix,do not plot if less than 1pix.
    {

        if(m_modu_cfg->m_wave_enable)
        {
            tempint.append(QPointF(x,y));
            //g_WavePlotter->setCurveData(m_modu_cfg->m_wave_indx, tempint,m_wave_pos);
            g_drawThread->f_draw_co2(m_modu_cfg->m_wave_indx, tempint,m_wave_pos);
            tempint.clear();
        }
        m_wave_last_pos = m_wave_pos;

    }
    */
    if(m_wave_pos >= m_wave_last_pos)
    {
        dstep = m_wave_pos - m_wave_last_pos;
    }
    else
    {
        dstep = m_wave_pos + WAVE_WIDGET_WIDTH_PIX - m_wave_last_pos;
    }
    if(dstep >= 1)
    {
        if(m_modu_cfg->m_wave_enable)
        {
            tempint.append(QPointF(dstep,y));
            //g_WavePlotter->setCurveData(m_modu_cfg->m_wave_indx, tempint,m_wave_pos);
            g_drawThread->f_draw_co2(m_modu_cfg->m_wave_indx, tempint,m_wave_pos);
            tempint.clear();
        }
        m_wave_last_pos = m_wave_pos;
    }
}
void CCO2Modu::f_read_data()
{
    if(m_modu_cfg->m_dara_src == CO2_MODULE_DATA_SRC_PORT)
    {
        QByteArray data =   m_port->readAll();

        /*data.clear();
        data.append(ecgdata,1024);*/

/*        data.clear();
        char ecg[9] = {0x05,0x80,0x88,0x80,0x88,0x80,0x88,0x80,0x9d};
        data.append(ecg,9);*/
        f_proc_data(data);
        {
            QMutexLocker locker(&m_mutex_tcp);
            //m_modu_data_raw .append(data);
        }
        //emit signal_setpanels_value(pMainForm->TextLabel_bar_alarm_III,data.count());

        //QDataStream inout(&m_modu_data_file);
        //inout.writeRawData((char *)data.data(),data.count());
        //m_modu_data_file.flush();

    }
    else if(m_modu_cfg->m_dara_src == CO2_MODULE_DATA_SRC_FILE)
    {

    }
}

void CCO2Modu::f_proc_data(QByteArray co2data)
{
    char * data = co2data.data();
    char tmp = *data;
    char finishflg = 0;
    for(int i = 0;i<co2data.count();i++)
    {
        tmp = *(data+i);
        if((tmp & 0x80) != 0)//检测到数据包头
        {
            iParseState = CO2_PARSE_STATE_HEAD0; //收到数据头
            for(int j = 0;j<CO2_MAX_DATA_BYTES;j++)//命令数据缓存清零
            {
                cmdbuf[j] = 0;
            }
            cmdbuf[0] = tmp;//命令标识
            cmdcount =1; //计数
            continue; //跳出本次循环
        }
        switch(iParseState)
        {
        case CO2_PARSE_STATE_IDDLE:

        break;
        case CO2_PARSE_STATE_HEAD0:
            if((tmp<0) ||(tmp>0x7f)) //无效长度的数据包
            {
                iParseState = CO2_PARSE_STATE_IDDLE;
            }
            else
            {
                cmdlen = tmp;
                cmdbuf[cmdcount] = tmp;
                cmdcount++;
                iParseState = CO2_PARSE_STATE_HEAD1;
            }

        break;
        case CO2_PARSE_STATE_HEAD1:
            cmdbuf[cmdcount] = tmp;
            cmdcount ++;
            if(cmdcount >= (cmdlen+2))
            {
                //一包数据接受完
                if(IsChecksumValid(cmdbuf))
                {
                    //校验正确
                    finishflg = 1;
                }
            }

        break;
        case CO2_PARSE_STATE_DATA:

        break;
        default:
            break;

        }
        if(finishflg == 1)
        {
            switch(cmdbuf[0])
            {
            case 0x80:
                f_CO2DataProc_80();
                break;
            case 0x82:
                f_CO2DataProc_82();
                break;

            case 0x84:
                 f_CO2DataProc_84();
                break;
            case 0x90:
                 f_CO2DataProc_90();
                break;
            case 0xc8:
                 f_CO2DataProc_c8();
                break;
            case 0xc9:
                 f_CO2DataProc_c9();
                break;
            case 0xca:
                 f_CO2DataProc_ca();
                break;
            case 0xcb:
                 f_CO2DataProc_cb();
                break;
            case 0xcc:
                 f_CO2DataProc_cc();
                break;
            case 0xf8:
                 f_CO2DataProc_f8();
            default:
                break;
            }
        }
    }

}
void CCO2Modu::f_CO2DataProc_80(void)
{
    //co2 waveform
    int val =  ((((cmdbuf[3]*128)+cmdbuf[4])-1000) ) ;
    val /= 100;
    f_plot_co2_wave(val);
    //other parameters
    int value = 0;
    switch(cmdbuf[5])
    {

    case 1:
        //CO2模块状态/错误
        break;
    case 2:
        //呼末CO2值
        value = (cmdbuf[6]*128+cmdbuf[7])/10;
       m_modu_val.m_Etco2_value =  value ;
       if(m_modu_cfg->m_alarm_humo_en)
       {
           if(value > m_modu_cfg->m_alarm_humo_high)
           {
               //呼末CO2过高报警
           }
           else if(value < m_modu_cfg->m_alarm_humo_low)
           {
               //呼末CO2过低报警
           }
       }
        break;
    case 3:
        //呼吸率
        value = cmdbuf[6]*128+cmdbuf[7];
        m_modu_val.m_spirerate_value = value;
        if(m_modu_cfg->m_alarm_breathrate_en)
        {
            if(value > m_modu_cfg->m_alarm_breathrate_high)
            {
                //呼吸率过高报警
            }
            if(value < m_modu_cfg->m_alarm_breathrate_low)
            {
                //呼吸率过低报警
            }
        }

        break;
    case 4:
        //
        value = (cmdbuf[6]*128+cmdbuf[7])/10;
        m_modu_val.m_Fico2_value = value;
        if(m_modu_cfg->m_alarm_xiru_en)
        {
            if(value > m_modu_cfg->m_alarm_xiru_high)
            {
                //吸入CO2过高报警

            }
            else if(value <m_modu_cfg->m_alarm_xiru_low)
            {
                //吸入CO2过低报警
            }
        }
        break;
    case 5:
        //检测到呼吸
        break;
    case 7:
        //硬件错误代码
        break;
    default:
        break;
    }

}
void CCO2Modu::f_CO2DataProc_82(void)
{

}
void CCO2Modu::f_CO2DataProc_84(void)
{

}

void CCO2Modu::f_CO2DataProc_90(void)
{

}

void CCO2Modu::f_CO2DataProc_c8(void)
{

}

void CCO2Modu::f_CO2DataProc_c9(void)
{

}
void CCO2Modu::f_CO2DataProc_ca(void)
{

}

void CCO2Modu::f_CO2DataProc_cb(void)
{

}

void CCO2Modu::f_CO2DataProc_cc(void)
{

}

void CCO2Modu::f_CO2DataProc_f8(void)
{

}

void CCO2Modu::EtCO2_jiaoling()
{
    char bf[]={0x82,0x1,0x7d,0x82,0x1,0x7d,0x82,0x1,0x7d,0x82,0x1,0x7d,};
    {
        QByteArray btAry("");
        btAry= QByteArray::fromRawData(bf,sizeof(bf));
        *(btAry.data());
            (m_port)->write(btAry);
    }

}

void CCO2Modu::EtCO2_WriteCOM(char work,float wendu,int daqiya,char O2,char buchangqiti,
                           float mazuiji )
{
    wendu=wendu*10;
    mazuiji=mazuiji*10;
    int buff=wendu;
    char bf[30];
    bf[0]=0x84;bf[1]=0x3;bf[2]=0x1b;bf[3]=work;/*bf[4]=0x5e;*/
    AddChecksum(&bf[0]);

    bf[5]=0x84;bf[6]=0x04;bf[7]=0x04;bf[8]=(buff/128)&0x7f;bf[9]=(buff)&0x7f;
    AddChecksum(&bf[5]);

    bf[11]=0x84;bf[12]=0x04;bf[13]=0x01;bf[14]=(daqiya/128)&0x7f;bf[15]=(daqiya)&0x7f;
    AddChecksum(&bf[11]);

    buff=mazuiji;
    bf[17]=0x84;bf[18]=0x06;bf[19]=0x0b;bf[20]=O2;bf[21]=buchangqiti;
    bf[22]=(buff*10/128)&0x7f;bf[23]=(buff*10)&0x7f;
    AddChecksum(&bf[17]);

    bf[25]=0x80;bf[26 ]=0x2;bf[ 27]=0x0;bf[ 28]=0x7e;

    QByteArray btAry;
    btAry= QByteArray::fromRawData(bf,30);
    *(btAry.data());
    (m_port)->write(btAry);
}
void CCO2Modu::AddChecksum( char  buff[])//num==buff[1]+1;
{
    short num=buff[1]+1;
    char checksum;
    short i;
    checksum=0;
    for(i=0;i<num;i++)
        checksum=(char)(checksum+buff[i]);
    checksum=(char)((-checksum)&0x7e);
    buff[num]=checksum;
}

bool CCO2Modu::IsChecksumValid(char *lpBuf)//num==buff[1]+2;
{
    short num=lpBuf[1]+2;
    char checksum;
    checksum=*lpBuf;
    lpBuf++;
    num--;
    for(;num>0;num--)
    {
        if(((uchar)(*lpBuf))>=0x80)
            return 0;
        checksum=(char)(checksum+*lpBuf);
        lpBuf++;
    }
    checksum&=0x7e;
    if(checksum==0)
        return 1;
    else return 0;
}
