#ifndef MODU_NETTHREAD
#define MODU_NETTHREAD
 #include <QLabel>
#include <QtCore>
#include <QThread>
#include <QtNetwork/QTcpSocket>
#include "modu_net.h"

typedef QAbstractSocket::SocketError typeSocketError;
typedef struct stNETDataHead
{
    //名称	长度（字节）	数据类型
    unsigned short m_pkg_len; //包长度	2
    unsigned char m_ip; //IP	1
    unsigned char m_pkg_id; //包类型ID	1
    unsigned short m_sumchk;//包头校验和	2


}stNETDataHead;
class CTcpConnection: public QObject
{
    Q_OBJECT
public:
    CTcpConnection(QWidget * parent);
private:
    QWidget *pMainForm;
public:
    void f_connect_to_server(int server);
    QTcpSocket *m_tcp_sokt1;
    QTcpSocket *m_tcp_sokt2;
    QTcpSocket *m_tcp_sokt3;


    void f_send_data(QByteArray);
    void f_read_data();
    void f_deal_error();
    void f_disconnect_server(int server);
signals:
    void signal_set_connection_pmp(bool);
private slots:
    void slot_connected_server1();
    void slot_disconnected_server1();
    void slot_data_ready_server1();
    void slot_error_server1();
    void slot_connected_server2();
    void slot_disconnected_server2();
    void slot_data_ready_server2();
    void slot_error_server2();
    void slot_connected_server3();
    void slot_disconnected_server3();
    void slot_data_ready_server3();
    void slot_error_server3();

    //数据存储
    void slot_store_beatrate(int value,bool,QDateTime);
    void slot_store_breath_ecg(int value,bool,QDateTime);
    void slot_store_spo2(int spo2,int pulserate,bool,bool,QDateTime);
    void slot_store_temp(int temp1,int temp2,bool,bool,QDateTime);
    void slot_store_nibp(int ss,int sz,int pj,bool,bool,bool,QDateTime);

    void slot_para_tcp_value_ready(QByteArray val,int iParaType);
};

class CNetThread : public QThread
{
    Q_OBJECT
public:
    CNetThread(QWidget *parent);
    static CNetThread &instance();
private:
    QWidget *pMainForm;
    //stNetModuleCfg *m_modu_cfg;
    //static CNetThread *p;
    CTcpConnection *m_connection;
    QTimer *m_timer;

public:
    void run();

private slots:
    void slot_time_out();
    void slot_net_changed(int );
};


#endif // MODU_NETTHREAD

