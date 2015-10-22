#include "modu_thread.h"
#include "modu_ecg.h"
#include "mainform.h"
#include "rsc_modu/modu_gpio.h"
int sindata[50] = {
    25,28,31,34,37,39,42,44,46,47
    ,48,49,49,49,49,48,47,46,44,42
    ,39,37,34,31,28,25,21,18,15,12
    ,10,7,5,3,2,1,0,0,0,0,1,2,3,5
    ,7,10,12,15,18,21,
};
int keyscan(void);
CProcParaThread::CProcParaThread(QWidget *parent,int para)
{
    pMainForm = parent;
    m_para_type = para;
    m_thread_stop = false;
    m_spo_draw_pos = 0;

    m_spo2_data_to_draw.resize(1);

    //
    for(int i=0;i<MAX_PORT_CNT;i++)
    {
        m_port[i] = NULL;
    }
    m_port[0] = g_EcgModule->m_port;

    m_com_data.resize(MAX_PORT_CNT);
    iTest = 0;
    iSimuSpo2Cnt = 0;
}

void CProcParaThread::run()
{
    QTimer *m_time = new QTimer();

    connect(m_time,SIGNAL(timeout()),this,SLOT(slot_time_to_draw()),Qt::DirectConnection);
    connect(this,SIGNAL(signal_draw_spo_wave(stWavedata,double)),
            pMainForm,SLOT(slot_paint_spo_wave(stWavedata,double)),
            Qt::QueuedConnection);
    m_time->start(20);
    //msleep(2000);
    g_gpioModu->f_set_12v_en(true);
/*
    if(m_para_type == 0)//ecg
    {
        while(true)
        {
            g_EcgModule->f_read_data();
            msleep(10);
        }
    }
    else if(m_para_type == 1) //eeg
    {
        while(true)
        {
            g_EegModule->f_read_data();
            msleep(10);
        }
    }
*/
    while(true)
    {
        g_EcgModule->f_read_data();
        g_EegModule->f_read_data();
        msleep(10);
    }
    //keyscan();

    this->exec();
}
void  CProcParaThread::slot_time_to_draw()
{
    int numPoints = 1;
    QVector<QPointF> points0;
    QVector<QPointF> points1;
    QByteArray arydata;

    for (int x = 0; x < numPoints; ++x) {
        points0.append(QPointF(x, uint(qrand()) % 100));
        //points1.append(QPointF(x, uint(qrand()) % 100));
        //points0.append(QPointF(x, 10));
        arydata.append(10);
    }

    QVector<QPointF> data;
    for(int i=10;i<arydata.count();i++)
    {
        m_spo_draw_pos++;
        if(m_spo_draw_pos >=730)
        {
            m_spo_draw_pos = 0;
        }
        double x = i;
        double y =sindata[(iTest++)%50]; //arydata[i];
        data.append(QPointF(x,y));
        if(iTest>1000)
        {
            iTest = 0;
        }
    }


/*
    for(int i=0; i<arydata.count();i++)
    {
        if(m_spo2_data_to_draw.size()<730)
        {
            m_spo2_data_to_draw.append(QPointF(m_spo_draw_pos,arydata[i]));
        }
        else
        {
            m_spo2_data_to_draw[m_spo_draw_pos] = QPointF(m_spo_draw_pos,arydata[i]);
        }
        m_spo_draw_pos++;
        if(m_spo_draw_pos >=730)
        {
            m_spo_draw_pos = 0;
        }
    }
    QVector<QPointF> data;
    for(int j=0; j<m_spo2_data_to_draw.size();j++)
    {
        double dx = m_spo2_data_to_draw[j].x() - 0;
        double dy = m_spo2_data_to_draw[j].y() - 0;
        double x = 0 + (dx *(730-1))/(730-1);//4100;
        double y = (50-1) - (dy * (50 - 1)
                                       / 100);
        if(y>(50-1)) //边界线
        {
            y = (50-1);
        }
        data.append(QPointF(x,y)) ;
    }
    */
    int realpos = m_spo_draw_pos* (730 - 1) / (730-1);
    //emit(signal_draw_spo_wave(data,realpos));
    double y =sindata[(iTest)%50]*80; //arydata[i];
    for(int i=0;i<3;i++)
    {
         //g_EcgModule->f_plot_ecg_wave(y,y,y);

    }
    (iTest++);
    if(iTest>1000)
    {
        iTest = 0;
    }


    //g_EcgModule->f_plot_spo2_wave(sindata[iSimuSpo2Cnt%50]*4);
   // g_EcgModule->f_plot_spire_wave(sindata[iSimuSpo2Cnt%50]*4);
    //g_CO2Module->f_plot_co2_wave(sindata[iSimuSpo2Cnt%50]*4);
    if(iSimuSpo2Cnt++ >1000)
    {
        iSimuSpo2Cnt = 0;
    }
     //g_EcgModule->f_read_data();

}

//
void CProcParaThread::f_read_com_data()
{
    for(int i =0;i<MAX_PORT_CNT;i++)
    {
        if(m_port[i])
        {
            m_com_data[i] = m_port[i]->readAll();
        }
    }
}

void CProcParaThread::f_parse_com_data()
{
    QByteArray tmp[MAX_PORT_CNT];
    for(int i = 0; i<MAX_PORT_CNT;i++)
    {
        tmp[i] = m_com_data[i];
        m_com_data[i].clear();
    }
    g_EcgModule->f_parse_0803_com_data(tmp[0]);
    f_parse_eeg_com_data(tmp[0]);
    f_parse_co2_com_data(tmp[0]);
    f_parse_masi_com_data(tmp[0]);
    f_parse_ibp_com_data(tmp[0]);

}


void CProcParaThread::f_parse_eeg_com_data(QByteArray data)
{

}

void CProcParaThread::f_parse_co2_com_data(QByteArray data)
{

}

void CProcParaThread::f_parse_masi_com_data(QByteArray data)
{

}

void CProcParaThread::f_parse_ibp_com_data(QByteArray data)
{

}
CKeyScanThread::CKeyScanThread(QWidget *parent)
{
    pMainForm = parent;
}
void CKeyScanThread::run()
{
    //keyscan();
    m_timer = new QTimer();
    int keypress = 0;
    CMainForm *pMain = (CMainForm *)pMainForm;
    while(1)
    {
        /*
        keypress = g_gpioModu->f_scan_key();
        if(keypress != -1)
        {
            msleep(100); //延时消抖
            if(keypress == g_gpioModu->f_scan_key())
            {
                emit signal_key_pressed(keypress);
                QString key = "KEY %1";
                pMain->TextLabel_bar_alarm_II->setText(key.arg(keypress));
            }
        }
        keypress = g_gpioModu->f_scan_roll();
        if(keypress != -1)
        {
            emit signal_key_pressed(keypress);
            QString key = "KEY %1";
            pMain->TextLabel_bar_alarm_III->setText(key.arg(keypress));
        }

        */
        g_gpioModu->f_set_12v_en(true);
        msleep(5);
    }

}
CDrawThread::CDrawThread(QWidget *parent)
{
    ecgwrite = 0;
    eegwrite = 0;
    spo2write = 0;
    spirewrite = 0;
    co2write = 0;
    ecgread = 0;
    eegread = 0;
    spo2read = 0;
    spireread = 0;
    co2read = 0;
    start();
}

void CDrawThread::f_draw_ecg(int waveindex, const QVector<QPointF> &data,int iStop)
{
    for(int i = 0;i<data.count();i++)
    {
        ecgdata[ecgwrite].setY( data[i].y());
        ecgdata[ecgwrite].setX(data[i].x());
        ecgindx[ecgwrite] = waveindex;
        ecgstop[ecgwrite] = iStop;
        ecgwrite++;
        ecgwrite %= DRAW_DATA_MAX;
    }


}

void CDrawThread::f_draw_eeg(int waveindex, const QVector<QPointF> &data,int iStop)
{
    for(int i = 0;i<data.count();i++)
    {
        eegdata[eegwrite].setX(data[i].x());
        eegdata[eegwrite].setY(data[i].y());
        eegindx[eegwrite] = waveindex;
        eegstop[eegwrite] = iStop;
        eegwrite++;
        eegwrite %= DRAW_DATA_MAX;
    }
}

void CDrawThread::f_draw_spo2(int waveindex, const QVector<QPointF> &data,int iStop)
{
    for(int i = 0;i<data.count();i++)
    {
        spo2data[spo2write].setX(data[i].x());
        spo2data[spo2write].setY(data[i].y());
        spo2indx[spo2write] = waveindex;
        spo2stop[spo2write] = iStop;
        spo2write++;
        spo2write %= DRAW_DATA_MAX;
    }
}

void CDrawThread::f_draw_spire(int waveindex, const QVector<QPointF> &data,int iStop)
{
    for(int i = 0;i<data.count();i++)
    {
        spiredata[spirewrite].setX( data[i].x());
        spiredata[spirewrite].setY( data[i].y());
        spireindx[spirewrite] = waveindex;
        spirestop[spirewrite] = iStop;
        spirewrite++;
        spirewrite %= DRAW_DATA_MAX;
    }
}

void CDrawThread::f_draw_co2(int waveindex, const QVector<QPointF> &data,int iStop)
{
    for(int i = 0;i<data.count();i++)
    {
        co2data[co2write].setX( data[i].x());
        co2data[co2write].setY(data[i].y());
        co2indx[co2write] = waveindex;
        co2stop[co2write] = iStop;
        co2write++;
        co2write %= DRAW_DATA_MAX;
    }
}
 void CDrawThread::f_store_data(int idx,QPointF *data,int istop,int writepos)
 {

 }
void CDrawThread::run()
{
    m_pos = 0;
    iTest = 0;
    QTimer *m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_timerout()));
    m_timer->start(5);
    while(1)
    {
        ///////////////////////////////////////////////////////////////////////
        /*
        QVector<QPointF> tempint;
        int realpos = m_pos* (730 - 1) / (730-1);
        double y =sindata[(iTest)%50]; //arydata[i];

        (iTest++);
        if(iTest>1000)
        {
            iTest = 0;
        }
        m_pos++;
        if(m_pos >=730)
        {
            m_pos = 0;
        }
        tempint.append(QPointF(1,y));
        for(int i=0;i<15;i++)
        {
            g_WavePlotter->setCurveData(i, tempint,m_pos);
        }
        */
///////////////////////////////////////////////////////////////////////////////

        int pwrite = ecgwrite;
        while(ecgread != pwrite)
        {
            QVector<QPointF> tempint;
            tempint.append(ecgdata[ecgread]);
            g_WavePlotter->setCurveData(ecgindx[ecgread], tempint,ecgstop[ecgread]);
            ecgread++;
            ecgread %= DRAW_DATA_MAX;
        }
        pwrite = spo2write;
        while(spo2read != pwrite)
        {
            QVector<QPointF> tempint;
            tempint.append(spo2data[spo2read]);
            g_WavePlotter->setCurveData(spo2indx[spo2read], tempint,spo2stop[spo2read]);
            spo2read++;
            spo2read %= DRAW_DATA_MAX;
        }
        pwrite = spirewrite;
        while(spireread != pwrite)
        {
            QVector<QPointF> tempint;
            tempint.append(spiredata[spireread]);
            g_WavePlotter->setCurveData(spireindx[spireread], tempint,spirestop[spireread]);
            spireread++;
            spireread %= DRAW_DATA_MAX;
        }
        pwrite = eegwrite;
        while(eegread != pwrite)
        {
            QVector<QPointF> tempint;
            tempint.append(eegdata[eegread]);
            g_WavePlotter->setCurveData(eegindx[eegread], tempint,eegstop[eegread]);
            eegread++;
            eegread %= DRAW_DATA_MAX;
        }
        pwrite = co2write;
        while(co2read != pwrite)
        {
            QVector<QPointF> tempint;
            tempint.append(co2data[co2read]);
            g_WavePlotter->setCurveData(co2indx[co2read], tempint,co2stop[co2read]);
            co2read++;
            co2read %= DRAW_DATA_MAX;
        }
        usleep(2);
    }
    this->exec();
}
void CDrawThread::slot_timerout(void)
{
    if(ecgread != ecgwrite)
    {
        QVector<QPointF> tempint;
        tempint.append(ecgdata[ecgread]);
        g_WavePlotter->setCurveData(ecgindx[ecgread], tempint,ecgstop[ecgread]);
        ecgread++;
        ecgread %= DRAW_DATA_MAX;
    }
    if(spo2read != spo2write)
    {
        QVector<QPointF> tempint;
        tempint.append(spo2data[spo2read]);
        g_WavePlotter->setCurveData(spo2indx[spo2read], tempint,spo2stop[spo2read]);
        spo2read++;
        spo2read %= DRAW_DATA_MAX;
    }
    if(spireread != spirewrite)
    {
        QVector<QPointF> tempint;
        tempint.append(spiredata[spireread]);
        g_WavePlotter->setCurveData(spireindx[spireread], tempint,spirestop[spireread]);
        spireread++;
        spireread %= DRAW_DATA_MAX;
    }
    if(eegread != eegwrite)
    {
        QVector<QPointF> tempint;
        tempint.append(eegdata[eegread]);
        g_WavePlotter->setCurveData(eegindx[eegread], tempint,eegstop[eegread]);
        eegread++;
        eegread %= DRAW_DATA_MAX;
    }
    if(co2read != co2write)
    {
        QVector<QPointF> tempint;
        tempint.append(co2data[co2read]);
        g_WavePlotter->setCurveData(co2indx[co2read], tempint,co2stop[co2read]);
        co2read++;
        co2read %= DRAW_DATA_MAX;
    }
}
