#include "modu_net.h"
#include "mainform.h"
CNetModule::CNetModule(QWidget *parent)
{
    m_modu_cfg = new stNetModuleCfg;
    f_set_def_cfg();

    QFile file((NET_MODULE_CFG_DOC));
    if(file.open(QIODevice::ReadOnly))
    {
        stNetModuleCfg tempCfg;
        QDataStream inout(&file);
        int magic;
        inout >> magic;
        if(magic == 0x12345678)
        {
            inout.readRawData((char *)&tempCfg,sizeof(stNetModuleCfg));
        }
        memcpy(m_modu_cfg,&tempCfg,sizeof(stNetModuleCfg));
        file.close();
    }
    else
    {
        file.open(QIODevice::WriteOnly);
        QDataStream inout(&file);
        int magic = 0x12345678;
        inout<<magic;
        inout.writeRawData((char *)m_modu_cfg,sizeof(stNetModuleCfg));
        file.close();
    }
}

void CNetModule::f_set_def_cfg()
{
    m_modu_cfg->m_ip_0 = 192;
    m_modu_cfg->m_ip_1 = 168;
    m_modu_cfg->m_ip_2 = 10;
    m_modu_cfg->m_ip_3 = 2;
    m_modu_cfg->m_gate_0 = 192;
    m_modu_cfg->m_gate_1 = 168;
    m_modu_cfg->m_gate_2 = 10;
    m_modu_cfg->m_gate_3 = 1;
    m_modu_cfg->m_serv1_0 = 192;
    m_modu_cfg->m_serv1_1 = 168;
    m_modu_cfg->m_serv1_2 = 10;
    m_modu_cfg->m_serv1_3 = 100;
    m_modu_cfg->m_serv2_0 = 192;
    m_modu_cfg->m_serv2_1 = 168;
    m_modu_cfg->m_serv2_2 = 10;
    m_modu_cfg->m_serv2_3 = 231;
    m_modu_cfg->m_serv3_0 = 192;
    m_modu_cfg->m_serv3_1 = 168;
    m_modu_cfg->m_serv3_2 = 10;
    m_modu_cfg->m_serv3_3 = 230;

    m_modu_cfg->m_net_num = 20;
    m_modu_cfg->m_port1_num = 510+m_modu_cfg->m_ip_3;
    m_modu_cfg->m_port2_num = 510+m_modu_cfg->m_ip_3;
    m_modu_cfg->m_port3_num = 510+m_modu_cfg->m_ip_3;
    //m_modu_cfg->m_wifi_ssid[25] = "wireless";
    //m_modu_cfg->m_wifi_code[20] = "0123456789";
    m_modu_cfg->m_wifi_code_type = 0;
    m_modu_cfg->m_wifi_ip_0 = 192;
    m_modu_cfg->m_wifi_ip_1 = 168;
    m_modu_cfg->m_wifi_ip_2 = 10;
    m_modu_cfg->m_wifi_ip_3 = 11;
}

void CNetModule::f_set_cfg(stNetModuleCfg cfg)
{

    memcpy(m_modu_cfg,&cfg,sizeof(stNetModuleCfg));
    QFile file(NET_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_modu_cfg,sizeof(stNetModuleCfg));
    file.close();

    QFile netfile("/etc/network/interfaces");
    netfile.open(QIODevice::WriteOnly);
    QTextStream out(&netfile);
    out<<"# interfaces(5) file used by ifup(8) and ifdown(8)" << endl;
    out<<"auto lo"<<endl;
    out<<"iface lo inet loopback"<< endl;

    out<<"auto eth0"<< endl;

    out<<"iface eth0 inet static"<< endl;
    QString address=QString::number(m_modu_cfg->m_ip_0, 10)+"."
            +QString::number(m_modu_cfg->m_ip_1, 10)+"."
            +QString::number(m_modu_cfg->m_ip_2, 10)+"."
            +QString::number(m_modu_cfg->m_ip_3, 10);
    out<<"address  "<< address<< endl;

    address = QString::number(m_modu_cfg->m_gate_0, 10)+"."
            +QString::number(m_modu_cfg->m_gate_1, 10)+"."
            +QString::number(m_modu_cfg->m_gate_2, 10)+"."
            +QString::number(m_modu_cfg->m_gate_3, 10);
    out<<"gateway "<<address<< endl;

    out<<"netmask 255.255.255.0"<< endl;
    out<<endl;
   out<< "auto wlan0"<< endl;
    out<<"iface wlan0 inet dhcp"<< endl;
    out<<"wpa-ssid ncclink"<< endl;
    out<<"wpa-psk ncclink123"<< endl;
    file.close();
}

void CNetModule::f_get_cfg(stNetModuleCfg *cfg)
{
    memcpy(&cfg,m_modu_cfg,sizeof(stNetModuleCfg));
}
