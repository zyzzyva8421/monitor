#ifndef MODU_ANSE
#define MODU_ANSE
#include <QtCore>

#define ANAESDEP_MODULE_CFG_DOC "/home/data/config/anaes.dat"
#define ANAESDEP_MODULE_DATA_CNT 131
#define ANAESDEP_MODULE_DATA_PORT_NAME "/dev/ttyUSB3"

#define ANAESDEP_MODULE_DATA_SRC_PORT 0
#define ANAESDEP_MODULE_DATA_SRC_FILE 1
#include "../rsc_plot/waveplot.h"
#include "../posix_qextserialport.h"
#include "qextserialbase.h"
typedef struct stAnaesDepModuCfg_
{
    int m_module_enable;//true = module enable;
    int m_dara_src;
    bool m_para_enable;

    int m_wave_amp;
    bool m_alarm_enable;
    int m_alarm_high;
    int m_alarm_low;


    QRect m_wave_rec;
    int m_wave_indx;
    int m_wave_color; // wave color
    int m_panel_color;//para color
    bool m_wave_enable;
    int m_wave_speed; //6.25mm/s *N //波形速度

}stAnaesDepModuCfg;
typedef struct stAnaesDepValue_
{

    ///////////////////TCP data////////////////////////////
    //数据类型	长度（字节）	说明
    unsigned char 	m_anaes_flg;//1	31，代表麻醉深度
    unsigned char 	m_anaes_flg_1;//1	7
    char  	m_anaes_wave[100];//100	麻醉深度脑电波形，有符号，-128 to +128
    unsigned char	m_modu_state;//1	模块状态：
                    /*Bit 0: 干扰
                    Bit 1: 电极脱落
                    Bit 2: 信号质量差
                    Bit 3: 阻抗高*/
    unsigned char 	m_black_imp_val;//1	黑电极阻抗，数据范围0～11，0 = “<1”  11 = “>10”
    unsigned char  m_white_imp_val;//	1	白电极阻抗，数据范围0～11，0 = “<1”  11 = “>10”
    unsigned char	m_csi_val;//1	麻醉深度指数CSI，数据范围0～100, 255表示无效数据
    unsigned char	m_bs_val;//	爆发抑制BS，数据范围0～100, 255表示无效数据
    unsigned char	m_sqi_val;//1	信号质量SQI，数据范围0～100, 255表示无效数据
    unsigned char	m_emg_val;//1	肌电EMG，数据范围0～100, 255表示无效数据
    unsigned char	m_bat_val;//1	电池电压BAT，=20*电池电压，数据范围0～255
    unsigned char	m_reserv[8];//8	保留
    ////////////////////////////////////////////////////

}stAnaesDepValue;

class CAnaesDepModu:QObject
{
    Q_OBJECT
public:
    CAnaesDepModu(QWidget *parent);
    void f_setDefaultCfg();
    void f_set_def_cfg();
    void f_set_cfg(stAnaesDepModuCfg );
    void f_get_cfg( stAnaesDepModuCfg*);
    void f_read_data();

    void f_process_data(QByteArray);
    void f_reset_value();
    void f_parse_data();
    void f_plot_ana_wave(int data);
    stAnaesDepValue *m_modu_val;
private:
    stAnaesDepModuCfg *m_modu_cfg;
    int m_wave_buf[ANAESDEP_MODULE_DATA_CNT];
    int m_wave_cnt;
    Posix_QextSerialPort *m_port;
    int iParseState;
    char cmdbuf[ANAESDEP_MODULE_DATA_CNT];
    int cmdcount;
    int cmdlen;
    double m_wave_pos;
    double m_wave_last_pos;
    QMutex m_mutex_wave;
    QMutex m_mutex_tcp;
signals:
    void signal_setpanels_value(QLabel *p,double value,int prcs);
    void signal_setpanels_value(QLabel *,int value);
    void signal_setpanels_value(QLabel *, QString);
    void signal_para_tcp_data_ready(QByteArray,int);

};


#endif // MODU_ANSE

