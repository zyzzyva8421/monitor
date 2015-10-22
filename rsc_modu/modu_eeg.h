#ifndef MODU_EEG_H
#define MODU_EEG_H

#include "../rsc_plot/waveplot.h"
#include "../posix_qextserialport.h"
#include "qextserialbase.h"
#include "filter_one.h"
#define EEG_MODULE_WAVE_NUM 8
#define EEG_MODULE_CFG_DOC "/home/data/config/eeg.dat"
#define EEG_MODULE_DATA_PORT_NAME "/dev/ttyUSB2"

typedef struct CEegModuleCfg_
{
    int m_module_enable;//true = module enable;


    int m_wave_color[EEG_MODULE_WAVE_NUM]; // wave color
    bool m_wave_plot_enable[EEG_MODULE_WAVE_NUM]; //wave draw enable
    int m_panel_color;//para color


    enum Modu_src{ENUM_EEG_DATA_SRC_PORT,
                 ENUM_EEG_DATA_SRC_FILE} m_dara_src; //where data from:1file or 0serial port;

    //QString m_data_src_file_name;

    PortSettings m_serial_port_cfg;
    int m_serial_port_num; //searial port number
    //QString m_serial_port_name; //serial port name

    //alarm
    bool m_para_alarm_en; //true = para alarm enable flg enable
    bool m_tech_alarm_en; // true = tech alarm enbale flag enable

    //wave
    int m_wave_num; //module has n waves to draw;

    QRect m_wave_rec[EEG_MODULE_WAVE_NUM];
    int m_wave_indx[EEG_MODULE_WAVE_NUM];
    //设置参数

        //{ENUM_EEG_CHANEL_8,ENUM_EEG_CHANEL_8_SLEEP,
        //ENUM_EEG_CHANEL_16,ENUM_EEG_CHANEL_16_SLEEP,
        //   ENUM_EEG_CHANEL_32}
         int m_eeg_type; //EEG脑电模块的配置
        //enum{ENUM_EEG_1_8,
        //ENUM_EEG_9_16}
        int m_eeg_display;
        //enum{ENUM_EEG_SEN_15U, ENUM_EEG_SEN_25U,ENUM_EEG_SEN_30U,ENUM_EEG_SEN_35U,
        //ENUM_EEG_SEN_40U,ENUM_EEG_SEN_50U,ENUM_EEG_SEN_70U,ENUM_EEG_SEN_80U,
        //ENUM_EEG_SEN_100U,ENUM_EEG_SEN_120U,ENUM_EEG_SEN_150U, ENUM_EEG_SEN_200U,
        //ENUM_EEG_SEN_300U,ENUM_EEG_SEN_400U, ENUM_EEG_SEN_500U
    int m_eeg_wave_sensitive;
    //enum{
    //    ENUM_EEG_WAVE_SPEED_15MMPS,
    //    ENUM_EEG_WAVE_SPEED_30MMPS,
    //    ENUM_EEG_WAVE_SPEED_60MMPS
    //}
    int m_eeg_wave_speed;
    //enum{
    //    ENUM_EEG_FILTER_NO,
    //    ENUM_EEG_FILTER_15HZ,
    //    ENUM_EEG_FILTER_30HZ,
    //    ENUM_EEG_FILTER_40HZ
    //}
    int m_eeg_wave_filter;
    //enum{
    //    ENUM_EEG_TIME_CONST_NO,
    //    ENUM_EEG_TIME_CONST_0_1S,
    //    ENUM_EEG_TIME_CONST_0_2S,
    //    ENUM_EEG_TIME_CONST_0_3S
    //}
    int m_eeg_time_const;
    bool m_eeg_trap_en; //脑电陷波,false = 关，true = 开
    //enum{
    //    ENUM_EEG_SPIRE_FILTER_NO,
    //    ENUM_EEG_SPIRE_FILTER_8HZ,
    //    ENUM_EEG_SPIRE_FILTER_9HZ,
    //    ENUM_EEG_SPIRE_FILTER_10HZ
    //}
    int m_eeg_spire_filter;
    //enum{
    //    ENUM_EEG_SPIRE_TIME_CONST_NO,
    //    ENUM_EEG_SPIRE_TIME_CONST_2S,
     //   ENUM_EEG_SPIRE_TIME_CONST_3S,
    //    ENUM_EEG_SPIRE_TIME_CONST_4S
    //}
    int m_eeg_spire_time_const;
    bool m_eeg_spire_trap_en;//脑电呼吸陷波,false = 关，true = 开

    //enum{
    //    ENUM_EEG_SNORE_TIME_CONST_NO,
    //    ENUM_EEG_SNORE_TIME_CONST_1S,
    //    ENUM_EEG_SNORE_TIME_CONST_2S,
     //   ENUM_EEG_SNORE_TIME_CONST_3S
    //}
    int m_eeg_snore_time_const;

    bool m_eeg_snore_trap_en; //脑电鼾声陷波,false = 关，true = 开

    float m_eeg_coef;  //脑电系数
    float m_eeg_spire_coef; //脑电呼吸系数
    float m_eeg_emg_coef; //肌电系数
    float m_eeg_eyemove_coef; //眼动系数
    float m_eeg_snore_coef; //鼾声系数

}CEegModuleCfg;

typedef struct stEEGValue_
{
    //2.4.5.7	脑电数据（677字节）
    //数据类型	长度（字节）	说明
    unsigned char 	m_eeg_flg;//1	30，代表脑电
    unsigned char 	m_eeg_flg_1;//1	8
    unsigned char  	m_eeg_wave[16][32];//16×32	32 通道脑电波形，每通道长度为16字节。通道次序为： Fp1、F3、C3、P3、Fp2、F4、C4、P4、O1、F7、T3 、T5、O2、F8、T4、T6、AF3、FC3、CP3、PO3、AF4、FC4、CP4、PO4、FT7、CP7、Fz、Pz、FT8、CP8、Cz 、Oz（前十六个字节为第一通道数据，依次类推）
    //Int	4×32	32 通道脑电增益，单位0.01
    unsigned char 	m_eeg_layout;//1	屏幕布局，0～5 分别对应：标准界面、大字体界面、呼吸氧合图界面、血压趋势界面、趋势表界面、全屏多导界面
    unsigned char  	m_reserve0[32];//32	保留
    unsigned char	m_reserve1;//1	0
    unsigned char	m_reserve2;//1	1
}stEEGValue;

class CEegModule:public QObject
{
public:
    CEegModule(QWidget *parent);
    ~CEegModule();
public:
    void f_read_data();
    void f_parse_data();
    void f_Enable(bool bEnable);
    void f_isEnabled(bool *);
    int  f_open_data_src();
    void f_close_data_src();
    void f_reset_value();
    void f_set_eeg_def_cfg();
    void f_set_eeg_cfg(CEegModuleCfg );
    void f_get_eeg_cfg( CEegModuleCfg*);
    void f_plot_eeg_wave(char *);
    void f_eeg_data_processing(QByteArray eeg_data);
    int f_get_wave_mode();
    void EEG_WriteCom(char *  ,int  );
    void f_set_eeg_wave_layout();
    void f_set_eeg_wave_color();
private:
    QWidget *pMainForm;
    CEegModuleCfg *m_eeg_cfg;
    stEEGValue m_eeg_val;
    int m_eeg_wave_cnt;
    Posix_QextSerialPort *m_port;
    WavePlotter *m_wave_plot[EEG_MODULE_WAVE_NUM];

    QFile *m_data_src_file;
    int8_t DRAW_EEG_WAVE[32][760],*(p_DRAW_EEG_WAVE[8]);
    WavePlotSettings * m_wave_plot_setting[EEG_MODULE_WAVE_NUM];

    Filter_One subfilter[32];
    unsigned char iEegWavCnt;
    unsigned char uiFrameCnt;
    int iParseState;
    unsigned int uiSumchck;

    double m_eeg_pos[EEG_MODULE_WAVE_NUM];
    double m_eeg_last_pos[EEG_MODULE_WAVE_NUM];
    //模块数据存储文件
    QFile m_modu_data_file;
    char eegdata[1024] ;
    void f_setDefaultCfg();
};

#endif // MODU_EEG_H
