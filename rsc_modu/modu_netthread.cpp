#include "modu_netthread.h"
#include <QtNetwork/QTcpSocket>
#include "mainform.h"
#include "rsc_modu/modu_net.h"

#define NET_CONNECT_STAT_IDLE 0
#define NET_CONNECT_STAT_CONNECTING 1
#define NET_CONNECT_STAT_CONNECTED 2
int m_serv1_connected_flg;
int m_serv2_connected_flg;
int m_serv3_connected_flg;
bool m_net_changed_flg1 = false;
bool m_net_changed_flg2 = false;
bool m_net_changed_flg3 = false;
bool m_net_changed_flg = false;
int keyscan(void);
int idxnetreg =  qRegisterMetaType< typeSocketError >("stQtsocketerror"); //注册元类型
CNetThread::CNetThread(QWidget *parent)
{
    pMainForm = parent;
   start();
}
void CNetThread::run()
{
    //m_tcp_sokt1->socketDescriptor();
    //socket1

    m_timer = new QTimer;

    //f_connect_to_server();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_time_out()),Qt::DirectConnection);

    m_connection = new CTcpConnection(pMainForm);
    m_connection->f_connect_to_server(0x0f);
    m_timer->start(20);

    //while(true)
    {

    }
   exec();
}
void CNetThread::slot_net_changed(int  flg)
{
    if(flg & 0x01)
    {
        m_net_changed_flg1 = true;

    }
    if(flg & 0x02)
    {
        m_net_changed_flg2 = true;

    }
    if(flg & 0x04)
    {
        m_net_changed_flg3 = true;

    }
    if( m_net_changed_flg1 ||
             m_net_changed_flg2||
             m_net_changed_flg3)
    {
        m_net_changed_flg = true;
    }

    if(m_net_changed_flg1)
    {
        m_connection->f_disconnect_server(0x01);
    }
    if(m_net_changed_flg2)
    {
        m_connection->f_disconnect_server(0x02);
    }
    if(m_net_changed_flg3)
    {
        m_connection->f_disconnect_server(0x04);
    }
}

CTcpConnection::CTcpConnection(QWidget *parent)
{
    pMainForm = parent;
    m_tcp_sokt1 = new QTcpSocket;
    m_tcp_sokt2 = new QTcpSocket;
    m_tcp_sokt3 = new QTcpSocket;
    connect(m_tcp_sokt1, SIGNAL(connected()), this, SLOT(slot_connected_server1()),Qt::DirectConnection);
    connect(m_tcp_sokt1, SIGNAL(disconnected()),
             this, SLOT(slot_disconnected_server1()),Qt::DirectConnection);
    connect(m_tcp_sokt1, SIGNAL(readyRead()),
             this, SLOT(slot_data_ready_server1()),Qt::DirectConnection);
    connect(m_tcp_sokt1, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(slot_error_server1()),Qt::DirectConnection);
     //socket 2
     connect(m_tcp_sokt2, SIGNAL(connected()), this, SLOT(slot_connected_server2()),Qt::DirectConnection);
     connect(m_tcp_sokt2, SIGNAL(disconnected()),
             this, SLOT(slot_disconnected_server2()),Qt::DirectConnection);
     connect(m_tcp_sokt2, SIGNAL(readyRead()),
             this, SLOT(slot_data_ready_server2()),Qt::DirectConnection);
     connect(m_tcp_sokt2, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(slot_error_server2()),Qt::DirectConnection);
     //socket3
     connect(m_tcp_sokt3, SIGNAL(connected()), this, SLOT(slot_connected_server3()),Qt::DirectConnection);
     connect(m_tcp_sokt3, SIGNAL(disconnected()),
             this, SLOT(slot_disconnected_server3()),Qt::DirectConnection);
     connect(m_tcp_sokt3, SIGNAL(readyRead()),
             this, SLOT(slot_data_ready_server3()),Qt::DirectConnection);
     connect(m_tcp_sokt3, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(slot_error_server3()),Qt::DirectConnection);
     connect(g_EcgModule,SIGNAL(signal_para_tcp_data_ready(QByteArray,int )),this, SLOT(slot_para_tcp_value_ready(QByteArray, int)));
     connect(this,SIGNAL(signal_set_connection_pmp(bool)),pMainForm,SLOT(slot_set_connection_pmp(bool)));

     connect(g_EcgModule,SIGNAL(signal_store_beatrate(int ,bool,QDateTime)),this,SLOT(slot_store_beatrate(int ,bool,QDateTime)));
     connect(g_EcgModule,SIGNAL( signal_store_breath_ecg(int ,bool,QDateTime)),this,SLOT( slot_store_breath_ecg(int ,bool,QDateTime)));
     connect(g_EcgModule,SIGNAL(signal_store_spo2(int ,int ,bool,bool,QDateTime)),this,SLOT(slot_store_spo2(int ,int ,bool,bool,QDateTime)));
     connect(g_EcgModule,SIGNAL(signal_store_temp(int ,int ,bool,bool,QDateTime)),this,SLOT(slot_store_temp(int ,int ,bool,bool,QDateTime)));
     connect(g_EcgModule,SIGNAL(signal_store_nibp(int ,int ,int ,bool,bool,bool,QDateTime)),this,SLOT(slot_store_nibp(int ,int ,int ,bool,bool,bool,QDateTime)));

}

void CTcpConnection::f_connect_to_server(int server)
{

    QString address ;
    int port;
    stNetModuleCfg cfg;
    //g_NetModule->f_get_cfg(&cfg);
    memcpy(&cfg,g_NetModule->m_modu_cfg,sizeof(stNetModuleCfg));
    if((m_serv1_connected_flg == NET_CONNECT_STAT_IDLE)
        &&(server & 0x01))
    {
        //socket1

        port =cfg.m_port1_num;// m_modu_cfg.m_port1_num;

        address=QString::number(cfg.m_serv1_0, 10)+"."
                +QString::number(cfg.m_serv1_1, 10)+"."
                +QString::number(cfg.m_serv1_2, 10)+"."
                +QString::number(cfg.m_serv1_3, 10);

        m_tcp_sokt1->connectToHost(address,port,QIODevice::ReadWrite);
        m_serv1_connected_flg = NET_CONNECT_STAT_CONNECTING;

    }
    //socket2
    if((m_serv2_connected_flg == NET_CONNECT_STAT_IDLE)
        &&(server & 0x02))
    {
        port = cfg.m_port2_num;//m_modu_cfg.m_port2_num;
        address.clear();
        address = QString::number(cfg.m_serv2_0, 10)+"."
                +QString::number(cfg.m_serv2_1, 10)+"."
                +QString::number(cfg.m_serv2_2, 10)+"."
                +QString::number(cfg.m_serv2_3, 10);
        m_tcp_sokt2->connectToHost(address,port);
        m_serv2_connected_flg = NET_CONNECT_STAT_CONNECTING;
    }
    //socket3

    if((m_serv3_connected_flg == NET_CONNECT_STAT_IDLE)
        && (server & 0x04))
    {
        port = cfg.m_port3_num;//m_modu_cfg.m_port3_num;
        address.clear();
        address = QString::number(cfg.m_serv3_0, 10)+"."
                +QString::number(cfg.m_serv3_1, 10)+"."
                +QString::number(cfg.m_serv3_2, 10)+"."
                +QString::number(cfg.m_serv3_3, 10);
        m_tcp_sokt3->connectToHost(address,port);
        m_serv3_connected_flg = NET_CONNECT_STAT_CONNECTING;
    }
}

void CTcpConnection::f_send_data(QByteArray data)
{
    if(m_serv1_connected_flg == NET_CONNECT_STAT_CONNECTED)
    {
        m_tcp_sokt1->write(data);
    }
    if(m_serv2_connected_flg == NET_CONNECT_STAT_CONNECTED)
    {
        m_tcp_sokt2->write(data);
    }
    if(m_serv3_connected_flg == NET_CONNECT_STAT_CONNECTED)
    {
        m_tcp_sokt3->write(data);
    }
}

void CTcpConnection::f_read_data()
{

}
void CTcpConnection::f_deal_error()
{

}
void CTcpConnection::slot_connected_server1()
{
    m_serv1_connected_flg = NET_CONNECT_STAT_CONNECTED;
    emit signal_set_connection_pmp(true);
}
void CTcpConnection::slot_disconnected_server1()
{
     m_serv1_connected_flg = NET_CONNECT_STAT_IDLE;
     if((!m_serv2_connected_flg)
         &&(!m_serv1_connected_flg)
             &&(!m_serv3_connected_flg))
     {
         emit signal_set_connection_pmp(false);
     }
     //f_connect_to_server();

}
void CTcpConnection::slot_data_ready_server1()
{

}
void CTcpConnection::slot_error_server1()
{
    m_serv1_connected_flg = NET_CONNECT_STAT_IDLE;
    //f_connect_to_server();
}
void CTcpConnection::slot_connected_server2()
{
    m_serv2_connected_flg = NET_CONNECT_STAT_CONNECTED;
    emit signal_set_connection_pmp(true);
}
void CTcpConnection::slot_disconnected_server2()
{

    m_serv2_connected_flg = NET_CONNECT_STAT_IDLE;
    if((!m_serv2_connected_flg)
        &&(!m_serv1_connected_flg)
            &&(!m_serv3_connected_flg))
    {
        emit signal_set_connection_pmp(false);
    }
     //f_connect_to_server();
}
void CTcpConnection::slot_data_ready_server2()
{

}
void CTcpConnection::slot_error_server2()
{
    m_serv2_connected_flg = NET_CONNECT_STAT_IDLE;
    //f_connect_to_server();
}
void CTcpConnection::slot_connected_server3()
{
    m_serv3_connected_flg = NET_CONNECT_STAT_CONNECTED;
    emit signal_set_connection_pmp(true);
}
void CTcpConnection::slot_disconnected_server3()
{
    m_serv3_connected_flg = NET_CONNECT_STAT_IDLE;
    if((!m_serv2_connected_flg)
        &&(!m_serv1_connected_flg)
            &&(!m_serv3_connected_flg))
    {
        emit signal_set_connection_pmp(false);
    }
    //f_connect_to_server();
}
void CTcpConnection::slot_data_ready_server3()
{

}
void CTcpConnection::slot_error_server3()
{
    m_serv3_connected_flg = false;
    //f_connect_to_server();
}
void CNetThread::slot_time_out()
{
    //QByteArray data;
    //g_EcgModule->f_prepare_tcp_data(&data);
    m_connection->f_connect_to_server(0x0f);

}
// 0-server1 1bit - server2 3bit -server3
void  CTcpConnection::f_disconnect_server( int server)
{
    if(m_serv1_connected_flg != NET_CONNECT_STAT_IDLE)
    {
        m_tcp_sokt1->close();
    }
    if(m_serv2_connected_flg != NET_CONNECT_STAT_IDLE)
    {
        m_tcp_sokt2->close();
    }
    if(m_serv3_connected_flg != NET_CONNECT_STAT_IDLE)
    {
        m_tcp_sokt3->close();
    }
}

void CTcpConnection::slot_para_tcp_value_ready(QByteArray val,int iParaType)
{
    QByteArray data;
    stNETDataHead head;

    stNetModuleCfg cfg;
    memcpy(&cfg,g_NetModule->m_modu_cfg,sizeof(stNetModuleCfg));
    head.m_ip = cfg.m_ip_3;
    int len = 0;
    switch(iParaType)
    {
    case 0x01: // ecg+spire
        head.m_pkg_id = 70;
        len =981;
        head.m_pkg_len = 6+ len;//

        break;
    case 0x02: //spo2
        head.m_pkg_id = 70;
        len = 278;
        head.m_pkg_len = 6+len;
        break;
    case 0x03: //nibp
        head.m_pkg_id = 70;
        len = 48;
        head.m_pkg_len =6+len;
        break;
    case 0x04: //temp +record
        head.m_pkg_id = 70;
        len = 48;
        head.m_pkg_len = 6+ len;
        break;
    case 0x05: //eeg
        head.m_pkg_id = 70;
        len = 677;
        head.m_pkg_len =6+len;
        break;
    case 0x06: //ibp
        head.m_pkg_id = 70;
        len = 325;
        head.m_pkg_len = 6+len;
        break;
    case 0x07: //co2
        head.m_pkg_id = 70;
        len = 286;
        head.m_pkg_len =6+len;
        break;
    case 0x08: //masimo
        head.m_pkg_id = 70;
        len = 118;
        head.m_pkg_len =6+len;
        break;
    case 0x09: // monitor started
        head.m_pkg_id = 60;
        len = 3;
        head.m_pkg_len = 6+len;
        break;
    case 0x0a: //patient info
        head.m_pkg_id = 62;
        len = 231;
        head.m_pkg_len = 6+len;
        break;
    case 0x0b: // monitor initiated
        head.m_pkg_id = 67;
        len = 0;
        head.m_pkg_len = 6+len;
        break;
    case 0x0c: //bed number
        head.m_pkg_id = 69;
        len = 2;
        head.m_pkg_len = 6+len;
        break;
    default: //invald
        return;
        break;
    }

    head.m_sumchk =head.m_ip;
     head.m_sumchk  += (head.m_pkg_len & 0xff);
     head.m_sumchk += (head.m_pkg_len & 0xff00)>>8;
     head.m_sumchk += head.m_pkg_id;
    //head.m_sumchk = ( head.m_sumchk>>16 )+( head.m_sumchk & 0xffff );

   // head.m_sumchk +=	( head.m_sumchk>>16 );
    head.m_sumchk = ~(head.m_sumchk & 0xffff);

    data.append((char *)&head,sizeof(head));

    if(len > val.count())
    {
            return;
    }
    QByteArray para ;
    if(iParaType <=4) //六参数模块
    {
        char *p = val.data();
        para= g_EcgModule->f_prepare_tcp_data(p,iParaType);
    }
    data.append(para,len);

    unsigned short sumcheck = 0;
    for(int i = 0;i<len;i++)
    {
        sumcheck +=para[i];
    }
    sumcheck = ~(sumcheck&0xffff);
    unsigned char sum[2] = {0};
    sum[0] = sumcheck &0xff;
    sum[1] = (sumcheck & 0xff00)>>8;
    data.append((char *)sum,2);

    f_send_data(data);
}
void CTcpConnection::slot_store_beatrate(int value,bool,QDateTime datetime)
{

}

void CTcpConnection::slot_store_breath_ecg(int value,bool,QDateTime datetime)
{

}

void CTcpConnection::slot_store_spo2(int spo2,int pulserate,bool flg1,bool flg2,QDateTime recordtime)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_spo2 (para_id, para_value1,para_value2,para_time,para_alm_flg1,para_alm_flg2,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value1, :para_value2,:para_time,:para_alm_flg1,:para_alm_flg2,:para_date,:para_datetime )");

    query.bindValue(":para_id",DB_PARA_TYPE_SPO2);
    query.bindValue(":para_value1",spo2);
    query.bindValue(":para_value2",pulserate);

    query.bindValue(":para_alm_flg1",flg1);
    query.bindValue(":para_alm_flg2",flg2);

    QDateTime time = recordtime;

    QString datetime = time.toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}

void CTcpConnection::slot_store_temp(int temp1,int temp2,bool,bool,QDateTime datetime)
{

}

void CTcpConnection::slot_store_nibp(int ss,int sz,int pj,bool flg1,bool flg2,bool flg3,QDateTime recordtime)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_nibp (para_id, para_value1,para_value2,para_value3,para_date,para_time,para_datetime,para_alm_flg1,para_alm_flg2,para_alm_flg3 ) "
                  "VALUES (:para_id, :para_value1, :para_value2,:para_value3,:para_date,:para_time,:para_datetime,:para_alm_flg1,:para_alm_flg2,:para_alm_flg3 )");

    query.bindValue(":para_id",DB_PARA_TYPE_NIBP);
    query.bindValue(":para_value1",ss);
    query.bindValue(":para_value2",sz);
    query.bindValue(":para_value3",pj);



    query.bindValue(":para_alm_flg1",flg1);

    query.bindValue(":para_alm_flg2",flg2);

    query.bindValue(":para_alm_flg3",flg3);

    QDateTime time = recordtime;

    QString datetime =  time.toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}
