#ifndef MODU_IBP
#define MODU_IBP
#include <QtCore>
#include "../rsc_plot/waveplot.h"

#define IBP_MODULE_CFG_DOC "/home/data/config/ibp.dat"
typedef struct stIBPModuCfg_
{


    int m_wave_amp;
    bool m_alarm_enable;
    int m_alarm_high;
    int m_alarm_low;

    int m_chanel1_type;
    int m_chanel2_type;
    int m_wave_ruler_mode;
    int m_wave_filter_mode;
    int m_wave_speed;
    int m_modu_unit;
    int m_p1_type;
    int m_p2_type;
    double m_chanel1_ruler_high;
    double m_chanel1_ruler_low;
    double m_chanel2_ruler_high;
    double m_chanel2_ruler_low;
    int m_ibp1_panel_color;
    int m_ibp2_panel_color;
    int m_ibp1_wave_color;
    int m_ibp2_wave_color;
    bool m_ibp1_panel_enable;
    bool m_ibp2_panel_enable;
    bool m_ibp1_wave_enable;
    bool m_ibp2_wave_enable;
    QRect m_ibp1_wave_rec;
    QRect m_ibp2_wave_rec;
    int m_ibp1_wave_indx;
    int m_ibp2_wave_indx;
    bool m_alarm_ibp1_ss_en;
    bool m_alarm_ibp1_sz_en;
    bool m_alarm_ibp1_pj_en;
    int m_alarm_ibp1_ss_high;
    int m_alarm_ibp1_ss_low;
    int m_alarm_ibp1_sz_high;
    int m_alarm_ibp1_sz_low;
    int m_alarm_ibp1_pj_high;
    int m_alarm_ibp1_pj_low;
    bool m_alarm_ibp2_ss_en;
    bool m_alarm_ibp2_sz_en;
    bool m_alarm_ibp2_pj_en;
    int m_alarm_ibp2_ss_high;
    int m_alarm_ibp2_ss_low;
    int m_alarm_ibp2_sz_high;
    int m_alarm_ibp2_sz_low;
    int m_alarm_ibp2_pj_high;
    int m_alarm_ibp2_pj_low;
}stIBPModuCfg;
typedef struct stIBPValue_
{
    ///////////////////////////////////////////
   // 数据类型	长度（字节）	说明
    unsigned char	m_ibp_flg;//1	23，代表IBP
    unsigned char	m_ibp_flg_1;//1	4
    unsigned char	m_reserve0;//1
    unsigned char	m_ibp_wave[256];//256	2通道IBP波形，每通道长度为128字节
    unsigned char	m_ibp1_type;//1	通道1波形名称名称1-10：ART,PA,CVP,LAP,RAP,ICP,P1,P2,P3,P4
    short	m_ibp1_amp;//2	通道1波形放大系数
    short	m_flag;//2	0xaa55
    short	m_ibp1_baseline;//2	通道1波形基线
    unsigned char	m_ibp2_type;//1	通道2波形名称1-10：ART,PA,CVP,LAP,RAP,ICP,P1,P2,P3,P4
    short	m_ibp2_amp;//2	通道2波形放大系数
    short	m_flag_1;//2	0xaa55
    short	m_ibp2_baseline;//2	通道2波形基线
    short	m_ibp1_ss;//2	通道1收缩压
    short	m_ibp1_sz;//2	通道1舒张压
    short	m_ibp1_pj;//2	通道1平均压
    short	m_ibp2_ss;//2	通道2收缩压
    short	m_ibp2_sz;//2	通道2舒张压
    short	m_ibp2_pj;//2	通道2平均压

    short	m_alarm_ibp1_ss_high;//2	通道1收缩压报警上限
    short	m_alarm_ibp1_ss_low;//2	通道1收缩压报警上限
    short	m_alarm_ibp1_ss_level;//2	通道1收缩压报警级别，1～3分别对应高、中、低级报警
    short	m_alarm_ibp1_sz_high;//2	通道1舒张压报警上限
    short	m_alarm_ibp1_sz_low;//2	通道1舒张压报警上限
    short	m_alarm_ibp1_sz_level;//2	通道1舒张压报警级别，1～3分别对应高、中、低级报警
    short	m_alarm_ibp1_pj_high;//2	通道1平均压报警上限
    short	m_alarm_ibp1_pj_low;//2	通道1平均压报警上限
    short	m_alarm_ibp1_pj_level;//2	通道1平均压报警级别，1～3分别对应高、中、低级报警
    short	 m_alarm_ibp2_ss_high;//2	通道2收缩压报警上限
    short	m_alarm_ibp2_ss_low;//2	通道2收缩压报警上限
    short	m_alarm_ibp2_ss_level;//2	通道2收缩压报警级别，1～3分别对应高、中、低级报警
    short	m_alarm_ibp2_sz_high;//2	通道2舒张压报警上限
    short	m_alarm_ibp2_sz_low;//2	通道2舒张压报警上限
    short	m_alarm_ibp2_sz_level;//2	通道2舒张压报警级别，1～3分别对应高、中、低级报警
    short	m_alarm_ibp2_pj_high;//2	通道2平均压报警上限
    short	m_alarm_ibp2_pj_low;//2	通道2平均压报警上限
    short	m_alarm_ibp2_pj_level;//2	通道2平均压报警级别，1～3分别对应高、中、低级报警
    unsigned char	reserve1[4];//4	保留

}stIBPValue;

class CIBPModu:public QObject
{
    Q_OBJECT
public:
    CIBPModu(QWidget *parent);
    QWidget *pMainForm;
    void f_setDefaultCfg();
    void f_set_def_cfg();
    void f_reset_value();
    void f_set_cfg(stIBPModuCfg );
    void f_get_cfg( stIBPModuCfg*);
    void f_set_wave_color();
    void f_set_wave_layout();
private:
    void f_set_panel_display();
    stIBPModuCfg *m_modu_cfg;
    stIBPValue m_modu_value;
    WavePlotter *m_ibp1_wave_plot,
    *m_ibp2_wave_plot;
    WavePlotSettings * m_ibp1_wave_plot_setting,
    * m_ibp2_wave_plot_setting;
};

#endif // MODU_IBP

