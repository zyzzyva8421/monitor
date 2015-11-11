#include "modu_anaes.h"
#include "mainform.h"
#include "modu_thread.h"

#define ANA_PARSE_STATE_IDDLE 0
#define ANA_PARSE_STATE_HEAD0 1
#define ANA_PARSE_STATE_HEAD1 2
#define ANA_PARSE_STATE_DATA 3
CAnaesDepModu::CAnaesDepModu(QWidget *parent)
{

    m_modu_cfg = new stAnaesDepModuCfg;
    m_modu_val = new stAnaesDepValue;

    f_setDefaultCfg();
    f_reset_value();
    //get ecg file config
    {
        QFile file((ANAESDEP_MODULE_CFG_DOC));
        if(file.open(QIODevice::ReadOnly))
        {
            stAnaesDepModuCfg tempCfg;
            QDataStream inout(&file);
            int magic;
            inout >> magic;
            if(magic == 0x12345678)
            {
                inout.readRawData((char *)&tempCfg,sizeof(stAnaesDepModuCfg));
            }
            memcpy(m_modu_cfg,&tempCfg,sizeof(stAnaesDepModuCfg));
            file.close();
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            QDataStream inout(&file);
            int magic = 0x12345678;
            inout<<magic;
            inout.writeRawData((char *)m_modu_cfg,sizeof(stAnaesDepModuCfg));
            file.close();
        }
    }
    m_port = new Posix_QextSerialPort(ANAESDEP_MODULE_DATA_PORT_NAME);
    m_port->open(QIODevice::ReadWrite);
    m_port->setBaudRate((BaudRateType)115200);
    m_port->setDataBits(DATA_8);
    m_port->setParity(PAR_NONE);
    m_port->setStopBits(STOP_1);
    m_port->setFlowControl(FLOW_OFF);
    m_port->setTimeout(10);
    m_port->flush();
}

void CAnaesDepModu::f_setDefaultCfg()
{
    m_modu_cfg->m_alarm_enable = true;
    m_modu_cfg->m_wave_amp = 0;
    m_modu_cfg->m_alarm_high = 100;
    m_modu_cfg->m_alarm_low = 60;
    m_modu_cfg->m_wave_speed = 0;
    m_modu_cfg-> m_panel_color = 4;
    m_modu_cfg-> m_wave_color = 4;
    m_modu_cfg-> m_module_enable;//true = module enable;
    m_modu_cfg->m_para_enable = true;
    m_modu_cfg->m_wave_enable = false;
    m_modu_cfg->m_module_enable = true;
    m_modu_cfg-> m_dara_src = 0;
}

void CAnaesDepModu::f_set_def_cfg()
{
    f_setDefaultCfg();
    QFile file(ANAESDEP_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_modu_cfg,sizeof(stAnaesDepModuCfg));
    file.close();
}

void CAnaesDepModu::f_set_cfg(stAnaesDepModuCfg cfg)
{
    memcpy(m_modu_cfg,&cfg,sizeof(stAnaesDepModuCfg));
    QFile file(ANAESDEP_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_modu_cfg,sizeof(stAnaesDepModuCfg));
    file.close();
}

void CAnaesDepModu::f_get_cfg( stAnaesDepModuCfg* cfg)
{
    memcpy(cfg,m_modu_cfg,sizeof(stAnaesDepModuCfg));
}
void CAnaesDepModu::f_reset_value()
{
    m_modu_val-> m_anaes_flg = 31;//1	31，代表麻醉深度
    m_modu_val->m_anaes_flg_1;//1	7
    for(int i = 0;i<100;i++)
    {
         m_modu_val->m_anaes_wave[i] = 0;//100	麻醉深度脑电波形，有符号，-128 to +128
    }

    m_modu_val->m_modu_state = 0xff;//1	模块状态：
                    /*Bit 0: 干扰
                    Bit 1: 电极脱落
                    Bit 2: 信号质量差
                    Bit 3: 阻抗高*/
    m_modu_val->m_black_imp_val = 0;//1	黑电极阻抗，数据范围0～11，0 = “<1”  11 = “>10”
    m_modu_val->m_white_imp_val = 0;//	1	白电极阻抗，数据范围0～11，0 = “<1”  11 = “>10”
    m_modu_val->m_csi_val = 0xff;//1	麻醉深度指数CSI，数据范围0～100, 255表示无效数据
    m_modu_val->m_bs_val = 0xff;//	爆发抑制BS，数据范围0～100, 255表示无效数据
    m_modu_val->m_sqi_val = 0xff;//1	信号质量SQI，数据范围0～100, 255表示无效数据
    m_modu_val->m_emg_val = 0xff;//1	肌电EMG，数据范围0～100, 255表示无效数据
    m_modu_val->m_bat_val = 0xff;//1	电池电压BAT，=20*电池电压，数据范围0～255
    for(int i = 0; i< 8;i++)
    {
        m_modu_val->m_reserv[i] = 0;//8	保留
    }

}
void CAnaesDepModu::f_read_data()
{
    if(m_modu_cfg->m_dara_src == ANAESDEP_MODULE_DATA_SRC_PORT)
    {
        QByteArray data =   m_port->readAll();

        /*data.clear();
        data.append(ecgdata,1024);*/

/*        data.clear();
        char ecg[9] = {0x05,0x80,0x88,0x80,0x88,0x80,0x88,0x80,0x9d};
        data.append(ecg,9);*/
        f_process_data(data);
        {
            QMutexLocker locker(&m_mutex_tcp);
            //m_modu_data_raw .append(data);
        }
        //emit signal_setpanels_value(pMainForm->TextLabel_bar_alarm_III,data.count());

        //QDataStream inout(&m_modu_data_file);
        //inout.writeRawData((char *)data.data(),data.count());
        //m_modu_data_file.flush();

    }
    else if(m_modu_cfg->m_dara_src == ANAESDEP_MODULE_DATA_SRC_FILE)
    {

    }
}

void CAnaesDepModu::f_process_data(QByteArray ana_data)
{


    //Read_Com_Data_AnaesDep.clear();//尾巴数据个数清零
    char * data = ana_data.data();
    char tmp = *data;
    char finishflg = 0;
    for(int i = 0;i<ana_data.count();i++)
    {
        tmp = *(data+i);
        switch(iParseState)
        {
            case ANA_PARSE_STATE_IDDLE:
            if(tmp == 0xff)
            {
                iParseState = ANA_PARSE_STATE_HEAD0;
            }

            break;
        case ANA_PARSE_STATE_HEAD0:
            if(tmp == 0x01)
            {
                iParseState = ANA_PARSE_STATE_HEAD1;
                cmdbuf[0] = 0x0ff;
                cmdbuf[1] = 0x01;
                cmdcount = 2;
            }
            else
            {
                iParseState = ANA_PARSE_STATE_IDDLE;
            }
            break;
        case ANA_PARSE_STATE_HEAD1:
            cmdbuf[cmdcount] = tmp;
            cmdcount++;
            cmdlen = tmp;
            iParseState = ANA_PARSE_STATE_DATA;
            break;
        case ANA_PARSE_STATE_DATA:
            cmdbuf[cmdcount] = tmp;
            cmdcount++;
            if(cmdcount >= (cmdlen+5))
            {
                //尾数校验和CRC校验
                if(cmdbuf[130] == 0xfe)
                {
                    //接收完一包数据，开始解析
                     finishflg = 1;
                }
                iParseState = ANA_PARSE_STATE_IDDLE;

            }
            break;
        default:
            break;
        }
    }
}
void CAnaesDepModu::f_parse_data()
{
    m_modu_val-> m_anaes_flg = 31;//1	31，代表麻醉深度
    m_modu_val->m_anaes_flg_1 = 17;//1	7
    for(int i = 0;i<100;i++)
    {
        m_modu_val->m_anaes_wave[i] = cmdbuf[28+i];//100	麻醉深度脑电波形，有符号，-128 to +128
        f_plot_ana_wave(m_modu_val->m_anaes_wave[i]);
    }

    m_modu_val->m_modu_state = 0xff;//1	模块状态：
                    /*Bit 0: 干扰
                    Bit 1: 电极脱落
                    Bit 2: 信号质量差
                    Bit 3: 阻抗高*/
    m_modu_val->m_black_imp_val = cmdbuf[17];//1	黑电极阻抗，数据范围0～11，0 = “<1”  11 = “>10”
    m_modu_val->m_white_imp_val = cmdbuf[18];//	1	白电极阻抗，数据范围0～11，0 = “<1”  11 = “>10”
    m_modu_val->m_csi_val = cmdbuf[14];//1	麻醉深度指数CSI，数据范围0～100, 255表示无效数据
    m_modu_val->m_bs_val = cmdbuf[15];//	爆发抑制BS，数据范围0～100, 255表示无效数据
    m_modu_val->m_sqi_val = cmdbuf[16];//1	信号质量SQI，数据范围0～100, 255表示无效数据
    m_modu_val->m_emg_val = cmdbuf[19];//1	肌电EMG，数据范围0～100, 255表示无效数据
    m_modu_val->m_bat_val = cmdbuf[20];//1	电池电压BAT，=20*电池电压，数据范围0～255
    for(int i = 0; i< 8;i++)
    {
        m_modu_val->m_reserv[i] = 0;//8	保留
    }
    QByteArray tcpdata;
    tcpdata.append((char *)&m_modu_val,131);

    //emit signal_para_tcp_data_ready(data,2);
}

void CAnaesDepModu::f_plot_ana_wave(int data)
{
    double y = 0;
    bool limit_flag = false;
    double dstep = 0;
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
            g_drawThread->f_draw_ana(m_modu_cfg->m_wave_indx,tempint,0);
            tempint.clear();
        }
        m_wave_last_pos = 0;
    }
    if(m_wave_pos >= (m_wave_last_pos +1))//plot 1 pix,do not plot if less than 1pix.如果小于1个像素，则不画
    {

        if(m_modu_cfg->m_wave_enable)
        {
            tempint.append(QPointF(x,y));
            //g_WavePlotter->setCurveData(m_modu_cfg->m_wave_indx, tempint,m_wave_pos);
            g_drawThread->f_draw_ana(m_modu_cfg->m_wave_indx, tempint,m_wave_pos);
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
    if(dstep)
    {
        if(m_modu_cfg->m_wave_enable)
        {
            tempint.append(QPointF(dstep,y));
            //g_WavePlotter->setCurveData(m_modu_cfg->m_wave_indx, tempint,m_wave_pos);
            g_drawThread->f_draw_ana(m_modu_cfg->m_wave_indx, tempint,m_wave_pos);
            tempint.clear();
        }
        m_wave_last_pos = m_wave_pos;
    }

}
