#ifndef MODULE
#define MODULE

#include "../rsc_plot/waveplot.h"
#include "../posix_qextserialport.h"
#include "qextserialbase.h"



//data source selection
#define GEN_MODULE_DATA_SRC_PORT 0  //data from serial port
#define GEN_MODULE_DATA_SRC_FILE 1  //data from file


class CModuleCfgGen
{
public:
    CModuleCfgGen();
public:

    int m_module_enable;//true = module enable;
    QColor m_wave_color; // wave color
    QColor m_panel_color;//para color
    int m_wave_speed; //6.25mm/s *N

    int m_dara_src;

    QString m_data_src_file_name;

    PortSettings m_serial_port_cfg;
    int m_serial_port_num; //searial port number
    QString m_serial_port_name; //serial port name

    //alarm
    bool m_para_alarm_en; //true = para alarm enable flg enable
    bool m_tech_alarm_en; // true = tech alarm enbale flag enable
private:
    Posix_QextSerialPort *m_module_port;

};

class CModuleGen
{
public:
    CModuleGen(CModuleCfgGen,QWidget *);
    ~CModuleGen();
public:
    QWidget *parent;
    int m_wave_num;

public:
    void f_plot_wave();
    void f_read_data();
    void f_setCfg(CModuleCfgGen );
    void f_get_Cfg(CModuleCfgGen *);
    void f_Enable(bool bEnable);
    void f_isEnabled(bool *);

private:

};

#endif // MODULE

