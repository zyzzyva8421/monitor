#ifndef MOD_UECG
#define MOD_UECG
#include "../rsc_plot/waveplot.h"
#include "../posix_qextserialport.h"
#include "qextserialbase.h"
#include <QVector>
 #include <QMutex>

#define ECG_MODULE_WAVE_NUM 8 //
#define ECG_MODULE_DATA_PORT_NAME "/dev/ttyS1"
#define ECG_MODULE_DATA_FILE_NAME "/home/data/ecg.dat"
#define ECG_MODULE_DATA_SRC_PORT 0
#define ECG_MODULE_DATA_SRC_FILE 1
#define ECG_MODULE_FILTER_MOD_DIAGNOSE 0;
#define ECG_MODULE_FILTER_MOD_CARE 1;
#define ECG_MODULE_FILTER_MOD_OPERAT 2; //
#define ECG_MODULE_LEAD_I 0
#define ECG_MODULE_LEAD_II 1
#define ECG_MODULE_LEAD_III 2
#define ECG_MODULE_LEAD_MOD_5 0
#define ECG_MODULE_LEAD_MOD_3 1
#define ECG_MODULE_BEATRATE_SRC_ECG 0
#define ECG_MODULE_BEATRATE_SRC_SPO2 1
#define ECG_MODULE_BEATRATE_SRC_AUTO 2
#define ECG_MODULE_CFG_DOC "/home/data/config/ecg.dat"
#define NIBP_MODULE_CFG_DOC "/home/data/config/nibp.data"
#define SPO2_MODULE_CFG_DOC "/home/data/config/spo2.data"
#define SPIRE_MODULE_CFG_DOC "/home/data/config/spire.data"
#define TEMP_MODULE_CFG_DOC "/home/data/config/temp.data"

#define SPO_MODULE_WAVE_NUM 1
#define SPO_MODULE_DATA_FILE_NAME "/home/data/spo2.dat"
#define SPIRE_MODULE_WAVE_NUM 1
#define SPIRE_MODULE_DATA_FILE_NAME "/home/data/spire.dat"

#define MAX_DATA_PER_CMD 10

//心电网络数据对应的位置
#define ECG_VAL_FLG_C	0		//	20，代表ECG
#define ECG_VAL_FLG1_C	1		//	0
#define ECG_VAL_ECG_WAVE0_C 	2		//256*	3通道ECG波形，每通道长度为256字节
#define ECG_VAL_ECG_WAVE1_C 	258		//	3通道ECG波形，每通道长度为256字节
#define ECG_VAL_ECG_WAVE2_C 	514		//	3通道ECG波形，每通道长度为256字节
#define ECG_VAL_SPIRE_WAVE_C	770		//128	呼吸波形，长度为128字节
#define ECG_VAL_BEATRATE_S 	898		//2	心率，-100代表无效值
#define ECG_VAL_SPRATE_S	900		//2	呼吸率，-100代表无效值
#define ECG_VAL_ST1_F	902		//4	ST1，单位0.01mv，-100.00代表无效值
#define ECG_VAL_ST2_F	906		//4	ST2，单位0.01mv，-100.00代表无效值
#define ECG_VAL_ST3_F	910		//4	ST3，单位0.01mv，-100.00代表无效值
#define ECG_VAL_PVCS_S  	914		//2	PVC，-100代表无效值
#define ECG_VAL_ECGNAME0_C	916		//3	3通道ECG 波形名称，1～8对应I、II、III、aVR、aVL、aVF、V、校准
#define ECG_VAL_ECGNAME1_C	916
#define ECG_VAL_ECGNAME2_C	916
#define ECG_VAL_AMP0_C	919		//	屏幕布局，0～5分别对应：标准界面、大字体界面、呼吸氧合图界面、血压趋势界面、趋势表界面、全屏多导界面
#define ECG_VAL_AMP1_C	920    //3	3通道ECG增益，1～4对应X0.25、X0.5、X1、X2
#define ECG_VAL_AMP2_C	921
#define ECG_VAL_LAYOUT_C	922		//1	屏幕布局，0～5分别对应：标准界面、大字体界面、呼吸氧合图界面、血压趋势界面、趋势表界面、全屏多导界面
#define ECG_VAL_PACEMAKER_C	923		//1	高4位：起搏开关，0：关，1：开 低4位：陷波开关，0：关，1：开
#define ECG_VAL_FILTERMOD_C	924		//1	滤波模式，1～3分别对应诊断、监护、手术模式
#define ECG_VAL_ASPALARM_C	925		//1	呼吸窒息时间，0～6分别对应关、10秒、15秒、20秒、25秒、30秒、35秒、40秒、
#define ECG_VAL_SPIREAMP_C	926		//1	呼吸增益，0～4分别对应×0.25、×0.5、×1、×2、×4
#define ECG_VAL_BR_RSC_C 	927		//1	心率来源，0：ECG，1：SPO2，2：自动
#define ECG_VAL_ASPFLG_C	928		//1	呼吸窒息标志，0：无窒息，1：有窒息
#define ECG_VAL_ALM_BR_H_S	929		//2	心率报警上限
#define ECG_VAL_ALM_BR_L_S 	931		//2	心率报警下限
#define ECG_VAL_ALM_BR_EN_C	933		//1	心率报警开关，1～3分别对应高、中、低级报警
#define ECG_VAL_RESERV0_C	934		//	保留
#define ECG_VAL_ALM_SP_H_S	935		//2	呼吸率报警上限
#define ECG_VAL_ALM_SP_L_S 	937		//2	呼吸率报警下限
#define ECG_VAL_ALM_SP_EN_C	939		//1	呼吸率报警开关，1～3分别对应高、中、低级报警
#define ECG_VAL_RESERV1_C	940		//	保留
#define ECG_VAL_ALM_ST1_H_F	941		//4	ST1报警上限，单位0.01mv
#define ECG_VAL_ALM_ST1_L_F	945		//4	ST1报警下限，单位0.01mv
#define ECG_VAL_ALM_ST1_LVL_S	949		//2	ST1报警级别，1～3分别对应高、中、低级报警
#define ECG_VAL_ALM_ST2_H_F	951		//4	ST2报警上限，单位0.01mv
#define ECG_VAL_ALM_ST2_L_F	955		//4	ST2报警下限，单位0.01mv
#define ECG_VAL_ALM_ST2_LVL_S	959		//2	ST2报警级别，1～3分别对应高、中、低级报警
#define ECG_VAL_ALM_ST3_H_F	961		//4	ST3报警上限，单位0.01mv
#define ECG_VAL_ALM_ST3_L_F	965		//4	ST3报警下限，单位0.01mv
#define ECG_VAL_ALM_ST3_LVL_S	969		//2	ST3报警级别，1～3分别对应高、中、低级报警
#define ECG_VAL_ALM_PVC_H_S	971		//2	PVC报警上限
#define ECG_VAL_ALM_PVC_L_S	973		//2	PVC报警下限
#define ECG_VAL_ALM_PVC_LVL_S	975		//2	PVC报警级别，1～3分别对应高、中、低级报警
#define ECG_VAL_RESERV2_C	977		//	0X00
#define ECG_VAL_RESERV3_C	978		//	0X01
#define ECG_VAL_RESERV4_C	979		//	0X0f
#define ECG_VAL_RESERV5_C	980		//	0XAA
#define ECG_VAL_ARR_TYPE_C 981 //心率失常类型
#define ECG_VAL_ARR_VALUE_S  982 //心率失常值
#define ECG_VAL_R_INTER_S  983 //R波间期

//血氧网络数据对应的位置
#define SPO2_VAL_FLG_C	0	//	1	21，代表SPO2
#define SPO2_VAL_FLG1_C	1	//	1	1
#define SPO2_VAL_WAVE_C	2	//	256	SPO2波形，长度为256字节
#define SPO2_VAL_VALUE_S	258	//	2	SpO2，-100代表无效值
#define SPO2_VAL_PULSE_S	260	//	2	脉率，-100代表无效值
#define SPO2_VAL_ALM_H_S	262	//	2	SpO2报警上限
#define SPO2_VAL_ALM_L_S	264	//	2	SpO2报警下限
#define SPO2_VAL_ALM_LVL_S	266	//	2	SpO2报警级别，1～3分别对应高、中、低级报警
#define SPO2_VAL_ALM_PULSE_H_S	268	//	2	脉率报警上限
#define SPO2_VAL_ALM_PULSE_L_S	270	//	2	脉率报警下限
#define SPO2_VAL_ALM_PULSE_LVL_S	272	//	2	脉率报警级别，1～3分别对应高、中、低级报警
#define SPO2_VAL_RES0_C	274	//	1	0
#define SPO2_VAL_RES1_C	275	//	1	0
#define SPO2_VAL_RES2_C	276	//	1	1
#define SPO2_VAL_RES3_C	277	//	1	灵敏度，0~2分别对应高、中、低
//NIBP网络数据对应的位置
#define NIBP_VAL_FLG_C	0	//	1	22，代表无创血压
#define NIBP_VAL_FLG1_C	1	//	1	2
#define NIBP_VAL_YEAR_S	2	//	2	测量时间，年
#define NIBP_VAL_MONTH_C	4	//	1	测量时间，月
#define NIBP_VAL_DATE_C	5	//	1	测量时间，日
#define NIBP_VAL_HOUR_C	6	//	1	测量时间，时
#define NIBP_VAL_MIN_C	7	//	1	测量时间，分
#define NIBP_VAL_SEC_C	8	//	1	测量时间，秒
#define NIBP_VAL_SS_S	9	//	2	收缩压，单位mmHg
#define NIBP_VAL_SZ_S	11	//	2	舒张压，单位mmHg
#define NIBP_VAL_PJ_S	13	//	2	平均压，单位mmHg
#define NIBP_VAL_ALM_SS_H_S	15	//	2	收缩压报警上限，单位mmHg
#define NIBP_VAL_ALM_SS_L_S	17	//	2	收缩压报警下限，单位mmHg
#define NIBP_VAL_ALM_SS_LVL_S	19	//	2	收缩压报警级别，1～3分别对应高、中、低级报警
#define NIBP_VAL_ALM_SZ_H_S	21	//	2	舒张压报警上限，单位mmHg
#define NIBP_VAL_ALM_SZ_L_S	23	//	2	舒张压报警下限，单位mmHg
#define NIBP_VAL_ALM_SZ_LVL_S	25	//	2	舒张压报警级别，1～3分别对应高、中、低级报警
#define NIBP_VAL_ALM_PJ_H_S	27	//	2	平均压报警上限，单位mmHg
#define NIBP_VAL_ALM_PJ_L_S	29	//	2	平均压报警下限，单位mmHg
#define NIBP_VAL_ALM_PJ_LVL_S	31	//	2	平均压报警级别，1～3分别对应高、中、低级报警
#define NIBP_VAL_FINISH_FLG_C	33	//	1	无创血压测量结束标志，0：无创血压没有测量；0x55：无创血压测量结束
#define NIBP_VAL_RES0_C	34	//	1	1
#define NIBP_VAL_STAT_C	35	//	1	无创血压测量状态：
        //		0：等待状态
        //		1：手动测量中；
        //		2：自动测量中；
        //		3：连续测量中；
        //		4：校准中；
        //		5：漏气检测中；
        //		6：复位
        //		10：出错
#define NIBP_VAL_SET_C	37	//	1	无创血压设置：
        //		高4位：无创血压测量模式，0：手动测量，1：自动测量；2：连续测量；
        //		低4位：自动测量周期
        //		0：1分钟
        //		1：2分钟
        //		2：3分钟
        //		3：4分钟
        //		4：5分钟
        //		5：10分钟
        //		6：15分钟
        //		7：30分钟
        //		8：60分钟
        //		9：90分钟
        //		10：120分钟
        //		11：180分钟
        //		12：240分钟
        //		13：480分钟
//体温网络数据对应的位置
#define TEMP_VAL_FLG_C	0	//	1	23，代表体温
#define TEMP_VAL_FLG1_C	1	//	1	3
#define TEMP_VAL_T1_F	2	//	4	通道1体温值，单位：0.1℃
#define TEMP_VAL_T2_F	6	//	4	通道2体温值，单位：0.1℃
#define TEMP_VAL_DIF_F	10	//	4	温差体温值，单位：0.1℃
#define TEMP_VAL_ALM_T1_H_F	14	//	4	通道1体温报警上限，单位：0.1℃
#define TEMP_VAL_ALM_T1_L_F	18	//	4	通道1体温报警下限，单位：0.1℃
#define TEMP_VAL_ALM_T1_LVL_S	22	//	2	通道1体温报警级别，1～3分别对应高、中、低级报警
#define TEMP_VAL_ALM_T2_H_F	24	//	4	通道2体温报警上限，单位：0.1℃
#define TEMP_VAL_ALM_T2_L_F	28	//	4	通道2体温报警下限，单位：0.1℃
#define TEMP_VAL_ALM_T2_LVL_S	32	//	2	通道2体温报警级别，1～3分别对应高、中、低级报警
#define TEMP_VAL_ALM_DIF_H_F	34	//	4	温差报警上限，单位：0.1℃
#define TEMP_VAL_ALM_DIF_L_F	38	//	4	温差报警下限，单位：0.1℃
#define TEMP_VAL_ALM_DIF_LVL_S	42	//	2	温差报警级别，1～3分别对应高、中、低级报警
#define TEMP_VAL_RES0_C	44	//	1	1
#define TEMP_VAL_RCDCH1_WAVETYPE_C	45	//	1	高4位：通道2记录波形
        //		0：ECG1
        //		1：ECG2
        //		2：脉搏波
        //		3：呼吸波
        //		低4位：通道1记录波形，定义同上
#define TEMP_VAL_RCDCH2_WAVETYPE_C	46	//	1	高4位：记录模式，0：8秒，1：连续
        //		低4位：自动记录间隔
        //		0：关闭
        //		1：10分钟
        //		2：20分钟
        //		3：30分钟
        //		4：40分钟
        //		5：50分钟
        //		6：60分钟
        //		7：120分钟
        //		8：180分钟
        //		9：240分钟
#define TEMP_VAL_RCD_SET_SPD_GRID_C	47	//	1	高4位：记录波形速度，2：25mm/s，3：50mm/s
        //		低4位：记录网格开关，0：关，1：开

class CMainForm;
typedef struct CEcgModuleCfg_
{

    int m_module_enable;//true = module enable;
    bool m_ecg_para_enable;
    int m_wave_color[ECG_MODULE_WAVE_NUM]; // wave color
    bool m_wave_plot_enable[ECG_MODULE_WAVE_NUM]; //wave draw enable
    int m_panel_color;//para color


    int m_dara_src; //where data from:file or serial port;

    //QString m_data_src_file_name;

    PortSettings m_serial_port_cfg;
    int m_serial_port_num; //searial port number
    //QString m_serial_port_name; //serial port name

    //alarm
    bool m_para_alarm_en; //true = para alarm enable flg enable
    bool m_tech_alarm_en; // true = tech alarm enbale flag enable

    //wave
    int m_wave_num; //module has n waves to draw;

    //每个波形的Rrect。
    QRect m_wave_rec[ECG_MODULE_WAVE_NUM];
    int m_wave_indx[ECG_MODULE_WAVE_NUM] ;

    int m_ecg_chanel1_lead;//通道导联
    int m_ecg_chanel2_lead;
    int m_ecg_chanel3_lead;
    int m_ecg_amp; //=N,0.25*(N+1)
    int m_ect_pwr_supression_enable;
    int m_ecg_lead_style;
    int m_ecg_pacemaker_enable;
    int m_ecg_filter_mod;
    int m_ecg_pulse_vol;
    int m_ecg_beatrate_src;
    int m_ecg_wave_speed; //=N,6.25mm/s *(N+1)
    bool m_ecg_st_enable;
    bool m_ecg_pvcs_enbale;
    bool m_ecg_correct;
    double m_ecg_amp_usrcfg;

    int m_patinet_info;

    bool m_alarm_br_en;
    unsigned short m_alarm_br_high; //心率报警上限
    unsigned short m_alarm_br_low; //心率报警下限
    bool m_alarm_st_en;
    int m_alarm_st_high;
    int m_alarm_st_low;
    int m_alarm_pvc_high;
    int m_alarm_pvc_low;

}CEcgModuleCfg;
typedef struct CSpo2ModuleCfg_
{

    int m_module_enable;//true = module enable;
    bool m_spo2_para_enable;

    int m_wave_color; // wave color
    int m_panel_color;//para color
    bool m_wave_enable;
    int m_wave_speed; //6.25mm/s *N

    enum Modu_src{ENUM_ECG_DATA_SRC_PORT,
                 ENUM_ECG_DATA_SRC_FILE} m_dara_src; //where data from:file or serial port;
    //PortSettings m_serial_port_cfg;
    int m_serial_port_num; //searial port number
    //alarm
    bool m_para_alarm_en; //true = para alarm enable flg enable
    bool m_tech_alarm_en; // true = tech alarm enbale flag enable
    //wave
    int m_wave_num; //module has n waves to draw;

    QRect m_wave_rec;
    int m_wave_indx;

    int m_spo2_pulse_vol;
    int m_spo2_sensitive;
    int m_spo2_wave_speed;
    int m_spo2_pulse_enable;
    int m_spo2_wave_type;
    int m_spo2_pulse_modulate;
    bool m_alram_en;
    int m_alarm_high; //报警上限
    int m_alarm_low;//报警下限
    bool m_alram_pulserate_en;
    int m_alarm_pulserate_high;
    int m_alarm_pulserate_low;
    double m_spo2_correct;

}CSpo2ModuleCfg;
typedef struct CNibpModuleCfg_
{

    int m_module_enable;//true = module enable;
    bool m_nibp_para_enable;
    int m_panel_color;//para color

    enum Modu_src{ENUM_ECG_DATA_SRC_PORT,
                 ENUM_ECG_DATA_SRC_FILE} m_dara_src; //where data from:file or serial port;


    //PortSettings m_serial_port_cfg;
    int m_serial_port_num; //searial port number

    //alarm
    bool m_para_alarm_en; //true = para alarm enable flg enable
    bool m_tech_alarm_en; // true = tech alarm enbale flag enable
    bool m_alarm_ss_en; //true = para alarm enable flg enable
    bool m_alarm_sz_en; //true = para alarm enable flg enable
    bool m_alarm_pj_en; //true = para alarm enable flg enable
    int m_alarm_ss_high;//报警上限
    int m_alarm_ss_low;//报警下限
    int m_alarm_sz_high;//报警上限
    int m_alarm_sz_low;//报警下限
    int m_alarm_pj_high;//报警上限
    int m_alarm_pj_low;//报警下限
    //wave
    int m_wave_num; //module has n waves to draw;

    QRect m_wave_rec;
    int m_nibp_unit;
    int m_nibp_mesure_type;
    int m_nibp_interval;
    double m_nibp_correct;
}CNibpModuleCfg;
typedef struct CTempModuleCfg_
{
    int m_module_enable;//true = module enable;
    bool m_temp_para_enable;
    int m_panel_color;//para color

    enum Modu_src{ENUM_ECG_DATA_SRC_PORT,
                 ENUM_ECG_DATA_SRC_FILE} m_dara_src; //where data from:file or serial port;


    //PortSettings m_serial_port_cfg;
    int m_serial_port_num; //searial port number


    //alarm
    bool m_para_alarm_en; //true = para alarm enable flg enable
    bool m_tech_alarm_en; // true = tech alarm enbale flag enable

    //wave
    int m_wave_num; //module has n waves to draw;

    QRect m_wave_rec;
    int m_temp_unit;
    int m_temp_sensor;

    bool m_alarm1_en;
    float m_alarm1_high;
    float m_alarm1_low;
    bool m_alarm2_en;
    float m_alarm2_high;
    float m_alarm2_low;
}CTempModuleCfg;
typedef struct CSpireModuleCfg_
{

    int m_module_enable;//true = module enable;
    bool m_spire_para_enable;
    int m_wave_color; // wave color
    bool m_wave_enable;
    int m_panel_color;//para color

    int m_wave_speed; //6.25mm/s *N

    enum Modu_src{ENUM_ECG_DATA_SRC_PORT,
                 ENUM_ECG_DATA_SRC_FILE} m_dara_src; //where data from:file or serial port;


    int m_serial_port_num; //searial port number
    //alarm
    //bool m_para_alarm_en; //true = para alarm enable flg enable
    bool m_tech_alarm_en; // true = tech alarm enbale flag enable
    QRect m_wave_rec;
    int m_wave_indx;
    //wave
    int m_wave_num; //module has n waves to draw;

    int m_spire_asp_alarm;
    int m_spire_wave_amp;
    int m_spire_wave_speed;
    int m_spire_lead;
    int m_spire_src;
    bool m_alarm_en;
    int m_alarm_high;
    int m_alarm_low;
}CSpireModuleCfg;


typedef struct stEcgValue_
{
/////////////////////TCP data //////////////////////////////////
                    //length, value, meaning
    unsigned char	m_ecg_flg;//1	20，代表ECG
    unsigned char	m_ecg_flg_1;//1	0
    unsigned char	m_ecg_wave_data[3][256];//256×3	3通道ECG波形，每通道长度为256字节
    unsigned char	m_spire_wave_data[128];//128	呼吸波形，长度为128字节
    short	m_para_beat_rate;//2	心率，-100代表无效值
    short	m_para_ecg_spr;//2	呼吸率，-100代表无效值
    float	m_para_st1;//4	ST1，单位0.01mv，-100.00代表无效值
    float	m_para_st2;//4	ST2，单位0.01mv，-100.00代表无效值
    float	m_para_st3;//4	ST3，单位0.01mv，-100.00代表无效值
    short	m_para_pvcs;//2	PVC，-100代表无效值
    unsigned char	m_ecg_name[3];//3	3通道ECG 波形名称，1～8对应I、II、III、aVR、aVL、aVF、V、校准
    unsigned char	m_layout_type ;//1	屏幕布局，0～5分别对应：标准界面、大字体界面、呼吸氧合图界面、血压趋势界面、趋势表界面、全屏多导界面
    unsigned char	m_ecg_amp [3];//3	3通道ECG增益，1～4对应X0.25、X0.5、X1、X2
    unsigned char	m_ecg_pacemaker_enable;//1	高4位：起搏开关，0：关，1：开 低4位：陷波开关，0：关，1：开

    unsigned char	m_ecg_filter_mod;//1	滤波模式，1～3分别对应诊断、监护、手术模式
    unsigned char	m_spire_asp_alarm;//1	呼吸窒息时间，0～6分别对应关、10秒、15秒、20秒、25秒、30秒、35秒、40秒、
    unsigned char	m_spire_amp;//1	呼吸增益，0～4分别对应×0.25、×0.5、×1、×2、×4
    unsigned char	m_ecg_beatrate_src;//1	心率来源，0：ECG，1：SPO2，2：自动
    unsigned char	m_spire_asp_flag;//1	呼吸窒息标志，0：无窒息，1：有窒息
    unsigned short	m_alarm_br_high;//2	心率报警上限
    unsigned short	m_alarm_br_low;//2	心率报警下限
    unsigned char	m_alarm_br_en;//1	心率报警开关，1～3分别对应高、中、低级报警
    unsigned char	m_reserve0;//	保留
    unsigned short	m_alarm_spr_high;//2	呼吸率报警上限
    unsigned short	m_alarm_spr_low;//2	呼吸率报警下限
    unsigned char	m_spire_alarm_en;//1	呼吸率报警开关，1～3分别对应高、中、低级报警
    unsigned char	m_reserve1;//	保留
    float	 m_alarm_st1_high;//4	ST1报警上限，单位0.01mv
    float	 m_alarm_st1_low;//4	ST1报警下限，单位0.01mv
    unsigned short	m_alarm_st1_level;//2	ST1报警级别，1～3分别对应高、中、低级报警
    float	 m_alarm_st2_high;//4	ST2报警上限，单位0.01mv
    float	 m_alarm_st2_low;//4	ST2报警下限，单位0.01mv
    unsigned short	m_alarm_st2_level;//2	ST2报警级别，1～3分别对应高、中、低级报警
    float	m_alarm_st3_high;//4	ST3报警上限，单位0.01mv
    float	m_alarm_st3_low;//4	ST3报警下限，单位0.01mv
    unsigned short	m_alarm_st3_level;//2	ST3报警级别，1～3分别对应高、中、低级报警
    unsigned short	m_alarm_pvc_high;//2	PVC报警上限
    unsigned short	m_alarm_pvc_low;//2	PVC报警下限
    unsigned short	m_alarm_pvc_level;//2	PVC报警级别，1～3分别对应高、中、低级报警
    unsigned char	reserve2;//1	0X00
    unsigned char	reserve3;//1	0X01
    unsigned char	reserve4;//1	0X0f
    unsigned char	reserve5;//1	0XAA
///////////////////////////TCP data//////////////////////////////////
    //
    int m_ecg_arr_type; //心率失常类型
    int m_ecg_arr_value; //心率失常值
    int m_para_R_inter;
}stEcgValue;

typedef struct stSpo2Value_
{

    /////////////////////////TCP data//////////////////////////
    //数据类型	长度（字节）	说明
    unsigned char	m_spo2_flg;//1	21，代表SPO2
    unsigned char	m_spo2_flg_1;//1	1
    unsigned char	m_spo2_wave[256];//256	SPO2波形，长度为256字节
    short	m_spo2_value;//2	SpO2，-100代表无效值
    short	m_pulse_rate;//2	脉率，-100代表无效值
    short	m_alarm_spo2_high;//2	SpO2报警上限
    short	m_alarm_spo2_low;//2	SpO2报警下限
    short	m_alarm_spo2_level;//2	SpO2报警级别，1～3分别对应高、中、低级报警
    short	m_alarm_pulserate_high ;//2	;//脉率报警上限
    short	m_alarm_pulserate_low;//2	;//脉率报警下限
    short	m_alarm_pulserate_level	;//脉率报警级别，1～3分别对应高、中、低级报警
    unsigned char	reserve0;//1	0
    unsigned char	reserve1;//1	0
    unsigned char	reserve2;//1	1
    unsigned char	reserve3;//1	灵敏度，0~2分别对应高、中、低
    //////////////////////TCP data///////////////////////

    int m_state;
    int m_pulse_gram;
    int m_para_info;

}stSpo2Value;
typedef struct stNibpValue_
{

    ////////////////////////////////////////////////////////
    //数据类型	长度（字节）	说明
    unsigned char	m_nibp_flg;//1	22，代表无创血压
    unsigned char	m_nibp_flg_1;//1	2
    short	m_nibp_year;//2	测量时间，年
    unsigned char	m_nibp_month;//1	测量时间，月
    unsigned char	m_nibp_date;//1	测量时间，日
    unsigned char	m_nibp_hour;//1	测量时间，时
    unsigned char	m_nibp_min;//1	测量时间，分
    unsigned char	m_nibp_sec;//1	测量时间，秒
    short	m_para_nibp_ss;//2	收缩压，单位mmHg
    short	m_para_nibp_sz;//2	舒张压，单位mmHg
    short	m_para_nibp_pj;//2	平均压，单位mmHg

    short	m_alarm_ss_high;//2	收缩压报警上限，单位mmHg
    short	m_alarm_ss_low;//2	收缩压报警下限，单位mmHg
    short	m_alarm_ss_level;//2	收缩压报警级别，1～3分别对应高、中、低级报警
    short	m_alarm_sz_high;//2	舒张压报警上限，单位mmHg
    short	m_alarm_sz_low;//2	舒张压报警下限，单位mmHg
    short	m_alarm_sz_level;//2	舒张压报警级别，1～3分别对应高、中、低级报警
    short	m_alarm_pj_high;//2	平均压报警上限，单位mmHg
    short	m_alarm_pj_low;//2	平均压报警下限，单位mmHg
    short	m_alarm_pj_level;//2	平均压报警级别，1～3分别对应高、中、低级报警
    unsigned char	m_nibp_over_flg;//1	无创血压测量结束标志，0：无创血压没有测量；0x55：无创血压测量结束
    unsigned char	m_reserve0;//1	1
    unsigned char	m_result_state;//1	无创血压测量状态：
                                    /*
                                    0：等待状态
                                    1：手动测量中；
                                    2：自动测量中；
                                    3：连续测量中；
                                    4：校准中；
                                    5：漏气检测中；
                                    6：复位
                                    10：出错*/
    unsigned char	m_nibp_mode;//	无创血压设置：
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
    int m_para_nibp_xiudai; //袖带压值
    int m_para_pulse_rate;
    int m_alarm_nibp_high;//报警上限
    int m_alarm_nibp_low;//报警下限
    int m_mesure_mod; //测量模式，手动，连续，
    int m_mesure_interval; //
    int m_measure_stop_err;
    int m_state_err;

}stNibpValue;
typedef struct stSpireValue_
{
    int m_para_spr;
    int m_alarm_spr_high;
    int m_alarm_spr_low;
    int m_alarm_asp;
}stSpireValue;
typedef struct stTempValue_
{

    ///////////////////////////////////////////////
   // 数据类型	长度（字节）	说明
    unsigned char	m_temp_flg;//1	23，代表体温
    unsigned char	m_temp_flg_1;////1	3
    float	m_para_temp1;//4	通道1体温值，单位：0.1℃
    float	m_para_temp2;//4	通道2体温值，单位：0.1℃
    float	m_para_temp_dif;////4	温差体温值，单位：0.1℃
    float	m_alarm_temp1_high;//4	通道1体温报警上限，单位：0.1℃
    float	m_alarm_temp1_low;//4	通道1体温报警下限，单位：0.1℃
    short	m_alarm_temp1_level;//2	通道1体温报警级别，1～3分别对应高、中、低级报警
    float	m_alarm_temp2_high;//4	通道2体温报警上限，单位：0.1℃
    float	m_alarm_temp2_low;//4	通道2体温报警下限，单位：0.1℃
    short	m_alarm_temp2_level;//2	通道2体温报警级别，1～3分别对应高、中、低级报警
    float	m_alarm_temp_dif_high;//4	温差报警上限，单位：0.1℃
    float	m_alarm_temp_dif_low;//4	温差报警下限，单位：0.1℃
    short	m_alarm_temp_dif_level;//2	温差报警级别，1～3分别对应高、中、低级报警
    unsigned char	reserve0;//1	1
    unsigned char	m_record_wave_type;//1	高4位：通道2记录波形
                    /*0：ECG1
                    1：ECG2
                    2：脉搏波
                    3：呼吸波
                    低4位：通道1记录波形，定义同上*/
    unsigned char	m_record_mode;//1	高4位：记录模式，0：8秒，1：连续
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
    unsigned char	m_record_speed;//1	高4位：记录波形速度，2：25mm/s，3：50mm/s
                    //低4位：记录网格开关，0：关，1：开

    ///////////////////////////////////////////////
}stTempValue;

class CEcgModule:public QObject
{
    Q_OBJECT
public :
    CEcgModule(QWidget*parent);
    ~CEcgModule();
public:

    void f_read_data();
    void f_parse_data();
    QByteArray f_prepare_tcp_data( char *paradata,int type);

    void f_reset_ecg_spire_value();
    void f_reset_spo2_value();
    void f_reset_nibp_value();
    void f_reset_temp_record_value();
    void f_setDefaultCfg();
    void f_Enable(bool bEnable);
    void f_isEnabled(bool *);
    int  f_open_data_src();
    void f_close_data_src();

    void f_set_ecg_wave_color(int, int);
    void f_set_ecg_def_cfg();
    void f_set_ecg_cfg(CEcgModuleCfg );
    void f_get_ecg_cfg( CEcgModuleCfg*);
    void f_plot_ecg_wave(int ,int ,int);
    void f_set_ecg_wave_layout();
    void f_set_spo2_wave_layout();
    void f_set_spire_wave_layout();

    void f_set_spo2_def_cfg();
    void f_set_spo2_wave_color(int);
    void f_set_spo2_cfg(CSpo2ModuleCfg );
    void f_get_spo2_cfg(CSpo2ModuleCfg *);
    void f_plot_spo2_wave(int data );

    void f_set_nibp_def_cfg();
    void f_set_nibp_cfg(CNibpModuleCfg );
    void f_get_nibp_cfg(CNibpModuleCfg *);
    void f_do_nibp_measure();

    void f_set_temp_def_cfg();
    void f_set_temp_cfg(CTempModuleCfg );
    void f_get_temp_cfg(CTempModuleCfg *);

    void f_set_spire_def_cfg();
    void f_set_spire_cfg(CSpireModuleCfg );
    void f_get_spire_cfg(CSpireModuleCfg *);
    void f_plot_spire_wave(int data);
    void f_set_spire_wave_color(int);

    void f_parse_0803_com_data(QByteArray data);
    void f_0803_com_send_cmd(char cmd_ID);
    void FY0803_SendCommand(char cmd_ID,char cmd_length,
                            char canshu1,char canshu2,char canshu3,char canshu4);
    void FY0803_WriteCom(char *bf,int _length);
    void f_plot_ecg_wave_pre(int,int,int);
    void f_plot_spo2_wave_pre(int);
    void f_plot_spire_wave_pre(int data);
    //void f_set_panel_color();
    //数据库存储
    void f_store_beatrate(int value,bool);
    void f_store_breath_ecg(int value,bool);
    void f_store_spo2(int spo2,int pulserate,bool,bool);
    void f_store_temp(int temp1,int temp2,bool,bool);
    void f_store_nibp(int ss,int sz,int pj,bool,bool,bool);
private:
    CMainForm *pMainForm;
    CEcgModuleCfg *m_ecg_cfg;
    CSpo2ModuleCfg *m_spo2_cfg;
    CNibpModuleCfg *m_nibp_cfg;
    CTempModuleCfg *m_temp_cfg;
    CSpireModuleCfg *m_spire_cfg;


    WavePlotter *m_wave_plot[ECG_MODULE_WAVE_NUM],
    *m_spo2_wave_plot,
    *m_spire_wave_plot;
    WavePlotSettings * m_wave_plot_setting[ECG_MODULE_WAVE_NUM],
    *m_spo2_wave_plot_set,
    *m_spire_wave_plot_set;

    QFile *m_data_src_file;
    QByteArray m_modu_data_raw;

    QVector<int> m_ecg_wave_data_1;
    QVector<int> m_ecg_wave_data_2;
    QVector<int> m_ecg_wave_data_3;
    QVector<int> m_spo2_wave_data;
    QVector<int> m_spire_wave_data;

    QVector <QVector<QPointF> > m_ecg_data_to_draw; //存储画一个屏幕的数据
    QVector<int> m_ecg_data_pos; //新插入数据的位置
    QVector<QPointF> m_spo2_data_to_draw; //存储画一个屏幕的数据
    int m_spo_draw_pos; //新插入数据的位置
    QVector<QPointF> m_spire_data_to_draw; //存储画一个屏幕的数据
    int m_spire_draw_pos; //新插入数据的位置
    QTimer *plot_time; //绘图定时

    int iStoptest;
    double m_ecg_pos[ECG_MODULE_WAVE_NUM];
    double m_ecg_last_pos[ECG_MODULE_WAVE_NUM];
    double m_spo2_pos;
    double m_spo2_last_pos;
    double m_spire_pos;
    double m_spire_last_pos;

    //ecg parse state
   unsigned char m_para_data_one_buf[MAX_DATA_PER_CMD];
   int m_para_data_type;
   char m_para_data_sumchk;
   int m_para_data_one_cnt;

   //多线程保护
   QMutex m_mutex_wave_ecg;
   QMutex m_mutex_wave_spo2;
   QMutex m_mutex_wave_spire;
   QMutex m_mutex_tcp;


public:
    //PARAMETER
   char m_ecg_value[1000];
   stEcgValue m_ecg_val;
   char m_ecg_backup_buf[3][256];
   unsigned short m_ecg_backup_cnt;
   unsigned short m_ecg_wave_count;
   int m_ecg_arr_type; //心率失常类型
   int m_ecg_arr_value; //心率失常值
   int m_para_R_inter; //R波间期


   QByteArray m_nibp_value;
    stNibpValue m_nibp_val;
   unsigned char m_nibp_wave_count;
   QByteArray m_spo2_value;
    stSpo2Value m_spo2_val;
   unsigned char m_spo2_wave_count;
   QByteArray m_temp_value;
    stTempValue m_temp_val;
   unsigned char m_temp_wave_count;
   QByteArray m_spire_value;
    stSpireValue m_spire_val;
    unsigned char m_spire_wave_count;
    char m_spire_backup_buf[256];
    unsigned short m_spire_backup_cnt;

    QString m_port_name;
    QString m_data_src_file_name;
    Posix_QextSerialPort *m_port;

    //parameter unit
     enum Nibp_Unit{ENUM_NIBP_UINIT_MMHG,
                    ENUM_NIBP_UNIT_KPA} m_para_unit_nibp;
     enum Temp_Unit{ENUM_TEMP_UNIT_F,
                   ENUM_TEMP_UNIT_C} m_para_unit_temp;
    //data stream

     //模块数据存储文件
     QFile m_modu_data_file;
     char ecgdata[1024] ;
signals:
    void signal_para_ecg_value_changed(stEcgValue val);
    void signal_para_spo2_value_changed(stSpo2Value val);
    void signal_para_nibp_value_changed(stNibpValue  val);
    void signal_para_temp_value_changed(stTempValue val);
    void signal_para_spire_value_changed(stSpireValue val);
    void signal_setpanels_value(QLabel *p,double value,int prcs);
    void signal_setpanels_value(QLabel *,int value);
    void signal_setpanels_value(QLabel *, QString);
    void signal_para_tcp_data_ready(QByteArray,int);
    //数据存储
    void signal_store_beatrate(int value,bool,QDateTime);
    void signal_store_breath_ecg(int value,bool,QDateTime);
    void signal_store_spo2(int spo2,int pulserate,bool,bool,QDateTime);
    void signal_store_temp(int temp1,int temp2,bool,bool,QDateTime);
    void signal_store_nibp(int ss,int sz,int pj,bool,bool,bool,QDateTime);
private slots:
    void slot_plot_all_waves();
};

#endif // MOD_UECG

