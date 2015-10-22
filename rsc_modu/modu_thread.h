#ifndef MODU_THREAD_H
#define MODU_THREAD_H
#include <QtCore>
#include <QThread>
#include <QVector>
#include "mainform.h"
#define MAX_PORT_CNT 8

class CProcParaThread:public QThread
{
Q_OBJECT
public:
    CProcParaThread(QWidget *parent,int para);
    bool m_thread_stop;
    int m_para_type;//0 == ecg ,1 == eeg
private:
    QWidget *pMainForm;
    int m_spo_draw_pos;
    int iTest;
    int iSimuSpo2Cnt;
    //QTimer *m_time;
     stWavedata m_spo2_data_to_draw;
     Posix_QextSerialPort *m_port[MAX_PORT_CNT];
     QVector< QByteArray > m_com_data;

protected:
    void  run();
signals:
    void signal_draw_spo_wave( stWavedata,double dfPos);

private slots:
     void  slot_time_to_draw();

private:
     void f_read_com_data();
     void f_parse_com_data();

     void f_parse_eeg_com_data(QByteArray data);
     void f_parse_co2_com_data(QByteArray data);
     void f_parse_masi_com_data(QByteArray data);
     void f_parse_ibp_com_data(QByteArray data);

};

class CKeyScanThread:public QThread
{
    Q_OBJECT
public:
    CKeyScanThread(QWidget *parent);
protected:
    void run();
private:
    QWidget *pMainForm;
    QTimer *m_timer;
signals:
    void signal_key_pressed(int);
};
#define DRAW_DATA_MAX 200
class CDrawThread:public QThread
{
Q_OBJECT
public:
    CDrawThread(QWidget *parent);
    void f_draw_ecg(int waveindex, const QVector<QPointF> &data,int iStop);
    void f_draw_eeg(int waveindex, const QVector<QPointF> &data,int iStop);
    void f_draw_spo2(int waveindex, const QVector<QPointF> &data,int iStop);
    void f_draw_spire(int waveindex, const QVector<QPointF> &data,int iStop);
    void f_draw_co2(int waveindex, const QVector<QPointF> &data,int iStop);
    void f_draw_ana(int waveindex, const QVector<QPointF> &data,int iStop);
    void f_store_data(int idx,QPointF *,int istop,int writepos);
    void f_draw_all();
    void run();



    int iTest;
    int m_pos;

private:
    QPointF ecgdata[DRAW_DATA_MAX];
    int ecgindx[DRAW_DATA_MAX];
    int ecgstop[DRAW_DATA_MAX];
    int ecgwrite;
    int ecgread;

    QPointF eegdata[DRAW_DATA_MAX];
    int eegindx[DRAW_DATA_MAX];
    int eegstop[DRAW_DATA_MAX];
    int eegwrite;
    int eegread;

    QPointF spo2data[DRAW_DATA_MAX];
    int spo2indx[DRAW_DATA_MAX];
    int spo2stop[DRAW_DATA_MAX];
    int spo2write;
    int spo2read;

    QPointF spiredata[DRAW_DATA_MAX];
    int spireindx[DRAW_DATA_MAX];
    int spirestop[DRAW_DATA_MAX];
    int spirewrite;
    int spireread;

    QPointF co2data[DRAW_DATA_MAX];
    int co2indx[DRAW_DATA_MAX];
    int co2stop[DRAW_DATA_MAX];
    int co2write;
    int co2read;

    QPointF anadata[DRAW_DATA_MAX];
    int anaindx[DRAW_DATA_MAX];
    int anastop[DRAW_DATA_MAX];
    int anawrite;
    int anaread;
private slots:
     void slot_timerout(void);
};


#endif // MODU_THREAD_H
