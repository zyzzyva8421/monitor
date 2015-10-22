#ifndef MODU_NET
#define MODU_NET
#include <QtCore>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>

#define NET_MODULE_CFG_DOC "/home/data/config/net.dat"
typedef struct stNetModuleCfg_
{
    unsigned char m_ip_0,m_ip_1,m_ip_2,m_ip_3;
    unsigned char m_gate_0, m_gate_1, m_gate_2,m_gate_3;
    unsigned char m_serv1_0,m_serv1_1,m_serv1_2,m_serv1_3;
    unsigned char m_serv2_0,m_serv2_1,m_serv2_2,m_serv2_3;
    unsigned char m_serv3_0,m_serv3_1,m_serv3_2,m_serv3_3;
    int m_net_num;
    int m_port1_num,m_port2_num,m_port3_num;

    char m_wifi_ssid[25];
    char m_wifi_code[20];
    char m_wifi_code_type;
    unsigned char m_wifi_ip_0,m_wifi_ip_1,m_wifi_ip_2,m_wifi_ip_3;
}stNetModuleCfg;

class CNetModule:public QObject
{
    Q_OBJECT
public:
    CNetModule(QWidget *parent);
    stNetModuleCfg *m_modu_cfg;
    int *(TCP_bingrenxinxi[50]);
    int *(TCP_shishishuju_ECG[50]);
    int *(TCP_shishishuju_SPO2[50]);
    int *(TCP_shishishuju_xueya[50]);
    int *(TCP_shishishuju_temp[50]);
    int *(TCP_readcommand[50]);


public:
    void f_set_def_cfg();
    void f_set_cfg(stNetModuleCfg);
    void f_get_cfg(stNetModuleCfg *);


};

#endif // MODU_NET

