#ifndef MODU_CO2
#define MODU_CO2
#include <QtCore>
#define CO2_MODULE_DATA_PORT_NAME "/dev/ttyUSB4"
#define CO2_MODULE_CFG_DOC "/home/data/config/co2.dat"
#define CO2_MODULE_DATA_SRC_PORT 0
#define CO2_MODULE_DATA_SRC_FILE 1
#include "../rsc_plot/waveplot.h"
#include "../posix_qextserialport.h"
#include "qextserialbase.h"
typedef struct stCO2ModuCfg_
{
    int m_module_enable;//true = module enable;
    bool m_para_enable;
    bool m_alarm_enable;
    int m_alarm_high;
    int m_alarm_low;

    int m_work_mode; //工作模式
    int m_ssphyxia_alarm; //窒息报警
    int m_wave_amp; //波形幅度

    int m_modu_unit; //单位
    int m_balance_air; //平衡气体
    int m_wave_mode;//波形模式
    double m_co2_compens; //氧气补偿
    double m_anesthetic_val; //麻醉剂剂量
    double m_temp_compens; //温度补偿
    double m_air_pressure; //大气压力
    bool m_correct_flg; //校准标志



    QRect m_wave_rec;
    int m_wave_indx;
    int m_wave_color; // wave color
    int m_panel_color;//para color
    bool m_wave_enable;
    int m_wave_speed; //6.25mm/s *N //波形速度

    enum Modu_src{ENUM_CO2_DATA_SRC_PORT,
                 ENUM_CO2_DATA_SRC_FILE} m_dara_src; //where data from:file or serial port;
    //PortSettings m_serial_port_cfg;
    int m_serial_port_num; //searial port number

    bool m_alarm_breathrate_en;
    int m_alarm_breathrate_high;
    int m_alarm_breathrate_low;
    bool m_alarm_humo_en;
    int m_alarm_humo_high;
    int m_alarm_humo_low;
    bool m_alarm_xiru_en;
    int m_alarm_xiru_high;
    int m_alarm_xiru_low;


}stCO2ModuCfg;
typedef struct stCO2Value_
{
    ////////////////////////////////////////////////
    //数据类型	长度（字节）	说明
    unsigned char	m_co2_flg;//1	26，代表CO2
    unsigned char	m_co2_flg_1;//1	5
    unsigned char	m_co2_flg_2;//1	1
    unsigned char	m_co2_wave[256];//256	CO2波形，长度为256字节
    short	m_Etco2_value;//1	EtCO2参数数值
    short	m_Fico2_value;//2	FiCO2参数数值
    short	m_spirerate_value;//2	气道呼吸率
    short	m_alarm_Etco2_high;//2	EtCO2报警上限
    short	m_alarm_Etco2_low;//2	EtCO2报警上限
    short	m_alarm_Etco2_level;//2	EtCO2报警级别，1～3分别对应高、中、低级报警
    short	m_alarm_Fico2_high;//2	FiCO2报警上限
    short	m_alarm_Fico2_low;//2	FiCO2报警上限
    short	m_alarm_Fico2_level;//2	FiCO2报警级别，1～3分别对应高、中、低级报警
    short	m_alarm_spirerate_high;//2	气道呼吸率报警上限
    short	m_alarm_spirerate_low;//2	气道呼吸率报警上限
    short	m_alarm_spirerate_level;//2	气道呼吸率报警级别，1～3分别对应高、中、低级报警
    short	m_air_press;//2	大气压力，单位mmHg
    unsigned char	reserve0[2];//2	保留

///////////////////////////////////////////
}stCO2Value;
#define CO2_MAX_DATA_BYTES 128
class CCO2Modu: public QObject
{
    Q_OBJECT
public:
    CCO2Modu(QWidget *parent);
    void f_setDefaultCfg();
    void f_set_def_cfg();
    void f_set_cfg(stCO2ModuCfg );
    void f_get_cfg( stCO2ModuCfg*);
    void f_set_wave_layout();
    void f_plot_co2_wave(int data);
    void f_reset_value();

    void f_read_data();
    void f_proc_data(QByteArray);
    void EtCO2_jiaoling();
    void EtCO2_WriteCOM(char work,float wendu,int daqiya,char O2,char buchangqiti,
                               float mazuiji );
    void AddChecksum( char  buff[]);
    bool IsChecksumValid(char *lpBuf);
    void f_CO2DataProc_80(void);
    void f_CO2DataProc_82(void);
    void f_CO2DataProc_84(void);
    void f_CO2DataProc_90(void);
    void f_CO2DataProc_c8(void);
    void f_CO2DataProc_c9(void);
    void f_CO2DataProc_ca(void);
    void f_CO2DataProc_cb(void);
    void f_CO2DataProc_cc(void);
    void f_CO2DataProc_f8(void);

private:
    stCO2ModuCfg *m_modu_cfg;
    stCO2Value m_modu_val;
    double m_wave_pos;
    double m_wave_last_pos;
     Posix_QextSerialPort *m_port;
     int iParseState;
     char cmdbuf[CO2_MAX_DATA_BYTES];
     int cmdcount;
     int cmdlen;

     QMutex m_mutex_wave;
     QMutex m_mutex_tcp;

};


#endif // MODU_CO2

