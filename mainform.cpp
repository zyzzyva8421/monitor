#include <QtGui>
#include <QSound>
#include "mainform.h"
#include "rsc_pmng/menu_patient_mng.h"
#include "rsc_record/menu_record.h"
#include "rsc_set/menu_set.h"
#include "rsc_alarm/menu_alarm_limit.h"
#include "rsc_serve/menu_serve.h"
#include "rsc_warning/glb_warning.h"
#include "rsc_plot/waveplot.h"
#include "rsc_modu/modu_ecg.h"
#include "rsc_modu/layout.h"
#include "rsc_modu/modu_thread.h"
#include "rsc_modu/modu_ibp.h"
#include "rsc_modu/modu_anaes.h"
#include "rsc_modu/modu_eeg.h"
#include "rsc_modu/modu_netthread.h"
#include "rsc_modu/modu_net.h"
#include "rsc_modu/modu_database.h"
#include "rsc_modu/modu_co2.h"
#include "rsc_modu/modu_gpio.h"

int idxreg =  qRegisterMetaType< stWavedata>("stWavedata"); //注册元类型
CProcParaThread *procEcgThread;
CProcParaThread *procEegThread;
CEcgModule * g_EcgModule;
CLayoutModule *g_LayoutModule;
CIBPModu * g_IBPModule1;
CIBPModu * g_IBPModule2;
CAnaesDepModu *g_AnaesModule;
CEegModule *g_EegModule;
CNetThread *g_NetThread;
CNetModule *g_NetModule;
CDatabaseModule *g_DatabaseModule;
CCO2Modu *g_CO2Module;
WavePlotter *g_WavePlotter;
CKeyScanThread * g_KeyScanThread;
CPlayThread *g_PlayThread;
CDrawThread *g_drawThread;
CGPIOMODU *g_gpioModu;
int iStartdelay = 0;
CMainForm::CMainForm(QWidget* parent,Qt::WindowFlags f)
 :	QWidget(parent,f)
 {
    setupUi(this);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    m_freeze_flg = false;
    iCursor = 0;
    bCursorSta = false;
    //
    g_WarningCfg = new CGlbWarn();
    /*
     setTabOrder(m_btn_patnt_mng,m_btn_record);
     setTabOrder(m_btn_record,m_btn_set);
     setTabOrder(m_btn_set,m_btn_alarm);
     setTabOrder(m_btn_alarm,m_btn_serve);
     setTabOrder(m_btn_serve,m_btn_patnt_mng);
     */
     m_btn_patnt_mng->setFocus();
    //按钮事件处理

     m_btn_patnt_mng->installEventFilter(this);
     m_btn_record->installEventFilter(this);
     m_btn_set->installEventFilter(this);
     m_btn_alarm->installEventFilter(this);
     m_btn_serve->installEventFilter(this);
     connect(this,SIGNAL(signal_btn_clicked(QPushButton *)),this,SLOT(slot_btn_clicked(QPushButton*)));
   /*
    connect(m_btn_patnt_mng,SIGNAL(clicked()),this,SLOT(slot_btn_manage_clicked()));
    connect(m_btn_record,SIGNAL(clicked()),this,SLOT(slot_btn_record_clicked()));
    connect(m_btn_set,SIGNAL(clicked()),this,SLOT(slot_btn_set_clicked()));
    connect(m_btn_alarm,SIGNAL(clicked()),this,SLOT(slot_btn_alarm_clicked()));
    connect(m_btn_serve,SIGNAL(clicked()),this,SLOT(slot_btn_serve_clicked()));
*/
   /////////////////////////////////////////////////////////////////////////////////////
    g_gpioModu = new CGPIOMODU(this) ;
    //g_gpioModu->f_set_12v_en(false);
    g_PlayThread = new CPlayThread() ;

    sleep(1);

    g_EcgModule = new CEcgModule(this);
    g_IBPModule1 = new CIBPModu(this);
    g_AnaesModule = new CAnaesDepModu(this);
    g_EegModule = new CEegModule(this);
    g_CO2Module = new CCO2Modu(this);
    g_NetModule = new CNetModule(this);
    g_WavePlotter = new WavePlotter(this);
    g_LayoutModule = new CLayoutModule(this);
    g_DatabaseModule = new CDatabaseModule(this);
    g_drawThread = new CDrawThread(this);
    procEcgThread = new CProcParaThread(this,0); //ecg
    procEcgThread->start(QThread::NormalPriority);

   //procEegThread = new CProcParaThread(this,1); //eeg
   //procEegThread->start(QThread::NormalPriority);
    //g_gpioModu->f_set_12v_en(true);
   g_NetThread = new CNetThread(this);
   g_NetThread->start(QThread::LowPriority);
   g_KeyScanThread = new CKeyScanThread(this);
   g_KeyScanThread->start(QThread::LowPriority);
   connect(g_KeyScanThread,SIGNAL(signal_key_pressed(int)),this,SLOT(slot_key_pressed(int)));
    //procEcgThread.run();
   m_time_draw = new QTimer(this);
   m_time_draw->start(500);
   connect(m_time_draw,SIGNAL(timeout()),this,SLOT(slot_time_to_draw_wave()));

    f_set_all_panels_color();
    //QString value = QString::number(58,10);
    //TextLabel_XinLv_value->setText(value);
    //value.clear();
    //double v = 43.890;
    //value = QString::number(v,'f',1);
   // TextLabel_HuXiLvCo2_Co2_value_HuMo->setText(value);
    g_PlayThread->addPlay(G_WARN_T_CODE_STARTVOICE);


 }
CMainForm::~CMainForm()
{
    delete g_WarningCfg;
    delete g_LayoutModule;
}
void CMainForm::slot_btn_clicked(QPushButton * btn)
{
    if(btn == m_btn_patnt_mng)
    {
        slot_btn_manage_clicked();
    }
    else if(btn == m_btn_record)
    {
        slot_btn_record_clicked();
    }
    else if(btn == m_btn_set)
    {
        slot_btn_set_clicked();
    }
    else if(btn == m_btn_alarm)
    {
        slot_btn_alarm_clicked();
    }
    else if(btn == m_btn_serve)
    {
        slot_btn_serve_clicked();
    }
}

void CMainForm::slot_btn_manage_clicked(void)
{
    CFormPatinetMng *patient_mng_menu = new CFormPatinetMng(this);
    //setup menu position
    //patient_mng_menu->show();
    QPoint pos;
      pos.setX(0);
      pos.setY(-patient_mng_menu->sizeHint().height());
      patient_mng_menu->exec(this->m_btn_patnt_mng->mapToGlobal(pos));

}

void CMainForm::slot_btn_record_clicked()
{
    CMenuRecord * record_menu = new CMenuRecord(this);

    QPoint pos;
    pos.setX(0);
    pos.setY(-record_menu->sizeHint().height());
    record_menu->exec(this->m_btn_record->mapToGlobal(pos));
}
void CMainForm::slot_btn_set_clicked()
{
    CMenuSet * set_menu = new CMenuSet(this);

    QPoint pos;
    pos.setX(0);
    pos.setY(-set_menu->sizeHint().height());
    set_menu->exec(this->m_btn_set->mapToGlobal(pos));
}
void CMainForm::slot_btn_alarm_clicked()
{
    CMenuAlarmLimit * alarm_menu = new CMenuAlarmLimit(this);

    QPoint pos;
    pos.setX(0);
    pos.setY(-alarm_menu->sizeHint().height());
    alarm_menu->exec(this->m_btn_alarm->mapToGlobal(pos));
}
void CMainForm::slot_btn_serve_clicked()
{
    CMenuServe * serve_menu = new CMenuServe(this);

    QPoint pos;
    pos.setX(0);
    pos.setY(-serve_menu->sizeHint().height());
    serve_menu->exec(this->m_btn_serve->mapToGlobal(pos));
}
void CMainForm::slot_para_ecg_value_changed(stEcgValue val)
{

}

void CMainForm::slot_para_spo2_value_changed(stSpo2Value val)
{

}

void CMainForm::slot_para_nibp_value_changed( stNibpValue val)
{

}

void CMainForm::slot_para_temp_value_changed(stTempValue val)
{

}

void CMainForm::slot_para_spire_value_changed(stSpireValue val)
{

}
void CMainForm::slot_time_to_draw_wave()
{
    //date time
    QDateTime datatime = QDateTime::currentDateTime();
    QString datestring =  datatime.toString("yyyy-MM-dd");
    TextLabel_bar_date->setText(datestring);
    QString timestring = datatime.toString("hh:mm:ss");
    TextLabel_bar_time->setText(timestring);
    int numPoints = 5;
    QVector<QPointF> points0;
    QVector<QPointF> points1;
    QByteArray arydata;

    for (int x = 0; x < numPoints; ++x) {
        points0.append(QPointF(x, uint(qrand()) % 100));
        //points1.append(QPointF(x, uint(qrand()) % 100));
        //points0.append(QPointF(x, 10));
        arydata.append(60);
    }

    //g_EcgModule->f_plot_ecg_wave(points0);
    //g_EcgModule->f_plot_spo2_wave(arydata);
    //g_EcgModule->f_plot_spire_wave(points0);
   /* if(iStartdelay <=3)
    {
        iStartdelay ++;
    }

    if(iStartdelay == 3)
    {

    }*/

}
void CMainForm::slot_set_panels_color(QFrame *qf,int color)
{
    if((color<0)||(color>9))color = 0;

    QString stylesheet = "border-color: rgb(255, 255, 255); border-style:solid;border-width:1px;color:";
    stylesheet.append(g_ColorName[color]);
    stylesheet.append(";");

    qf->setStyleSheet(stylesheet);

}
int sindatatest[50] = {
    25,28,31,34,37,39,42,44,46,47
    ,48,49,49,49,49,48,47,46,44,42
    ,39,37,34,31,28,25,21,18,15,12
    ,10,7,5,3,2,1,0,0,0,0,1,2,3,5
    ,7,10,12,15,18,21,
};
int iTestcnt = 0;
void CMainForm::slot_paint_spo_wave(stWavedata data,double dfPos)
{
    QVector< QPointF > dat;
    dat = data;
    //g_EcgModule->f_plot_spo2_wave(data,dfPos);
    /*
    for(int i=0;i<3;i++)
    {
        g_EcgModule->f_plot_ecg_wave(sindatatest[iTestcnt]*100,
                                     sindatatest[iTestcnt]*100,
                                     sindatatest[iTestcnt]*100);
        iTestcnt++;

    }
    */
    /*
    double x = 0.33;
    double y = sindatatest[iTestcnt++];
    if(iTestcnt>=10)
        iTestcnt = 0;
    dat.clear();
    dat.append(QPointF(x,y));

    g_WavePlotter->setCurveDataAuto(8,dat);*/

/*
    QSound bells("/home/data/wav/heart.wav");
    if(bells.isAvailable())
        bells.play();*/
}
void CMainForm::f_set_all_panels_color()
{
    {
        CEcgModuleCfg cfg;
        g_EcgModule->f_get_ecg_cfg(&cfg);

        QString stylesheet = "border-color: rgb(255, 255, 255); border-style:solid;border-width:1px;color:";
        stylesheet.append(g_ColorName[cfg.m_panel_color]);
        stylesheet.append(";");
        frame_ECG->setStyleSheet(stylesheet);
    }
    {
        CSpo2ModuleCfg cfg;
        g_EcgModule->f_get_spo2_cfg(&cfg);

        QString stylesheet = "border-color: rgb(255, 255, 255); border-style:solid;border-width:1px;color:";
        stylesheet.append(g_ColorName[cfg.m_panel_color]);
        stylesheet.append(";");
        frame_spo2->setStyleSheet(stylesheet);

    }
    {
        CNibpModuleCfg cfg;
        g_EcgModule->f_get_nibp_cfg(&cfg);

        QString stylesheet = "border-color: rgb(255, 255, 255); border-style:solid;border-width:1px;color:";
        stylesheet.append(g_ColorName[cfg.m_panel_color]);
        stylesheet.append(";");
        frame_nibp->setStyleSheet(stylesheet);
    }
    {
        CTempModuleCfg cfg;
        g_EcgModule->f_get_temp_cfg(&cfg);

        QString stylesheet = "border-color: rgb(255, 255, 255); border-style:solid;border-width:1px;color:";
        stylesheet.append(g_ColorName[cfg.m_panel_color]);
        stylesheet.append(";");
        frame_temp->setStyleSheet(stylesheet);
    }
    {
        CSpireModuleCfg cfg;
        g_EcgModule->f_get_spire_cfg(&cfg);

        QString stylesheet = "border-color: rgb(255, 255, 255); border-style:solid;border-width:1px;color:";
        stylesheet.append(g_ColorName[cfg.m_panel_color]);
        stylesheet.append(";");
        frame_sp->setStyleSheet(stylesheet);
    }
    {
        stAnaesDepModuCfg cfg;
        g_AnaesModule->f_get_cfg(&cfg);
        QString stylesheet = "border-color: rgb(255, 255, 255); border-style:solid;border-width:1px;color:";
        stylesheet.append(g_ColorName[cfg.m_panel_color]);
        stylesheet.append(";");
        frame_mashen->setStyleSheet(stylesheet);
    }

}
void CMainForm::slot_setpanels_value(QLabel *p,double value,int prcs)
{
    QString val = QString::number(value,'f',prcs);
    p->setText(val);
}

void CMainForm::slot_setpanels_value(QLabel *p,int value)
{
    QString val = QString::number(value,10);
    p->setText(val);
}
void CMainForm::slot_setpanels_value(QLabel *p, QString val)
{
     p->setText(val);
}
void CMainForm::slot_setpanel_pixmap(QLabel *,int)
{

}

void CMainForm::slot_set_connection_pmp(  bool b)
{
    if(!b)
    {
        PixmapLabel_bar_tcpconnect ->setPixmap(QPixmap(QString::fromUtf8(":/image/qrc/Network_dis.png")));
    }
    else
    {
        PixmapLabel_bar_tcpconnect->setPixmap(QPixmap(QString::fromUtf8(":/image/qrc/Network_con.png")));
    }
}

bool CMainForm::eventFilter(QObject *o,QEvent *e)
{
    bool iflg = false;
    QPushButton *btn[5];
    btn[0] = m_btn_patnt_mng;
    btn[1] = m_btn_record;
    btn[2] = m_btn_set;
    btn[3] = m_btn_alarm;
    btn[4] = m_btn_serve;
    if(e->type() == QEvent::KeyPress)
    {
        QKeyEvent *event=(QKeyEvent *)e;
        switch (event->key()) {
         case Qt::Key_Up:
        case Qt::Key_Left:

           for(int i=0;i<5;i++)
            {
                if(btn[i] == o)
                {
                    if(i == 0)
                    {
                        btn[4]->setFocus();
                        iflg = true;
                        break;
                    }
                    else
                    {
                        btn[i-1]->setFocus();
                        iflg = true;
                        break;
                    }
                }
            }
            if(iflg == false)
            {
                btn[4]->setFocus();
            }
            return true;
            break;
        case Qt::Key_Down:
        case Qt::Key_Right:
            for(int i=0;i<5;i++)
            {
                if(btn[i] == o)
                {
                    if(i == 4)
                    {
                        btn[0]->setFocus();
                        iflg = true;
                        break;
                    }
                    else
                    {
                        btn[i+1]->setFocus();
                        iflg = true;
                        break;
                    }
                }
            }
            if(iflg == false)
            {
                btn[0]->setFocus();
            }
            return true;
            break;


        case Qt::Key_Return:
            for(int i = 0; i<5;i++)
            {
                if(btn[i] == o)
                {
                    emit(signal_btn_clicked((QPushButton*) o));
                    break;
                }
            }

        return true;
            break;
        default:
            f_process_key(event->key());
        }
    }
    else
    {
        return false;
    }
    return true;
}
void CMainForm::slot_key_pressed(int k)
{
    bool iflg = false;
    QPushButton *btn[5];
    btn[0] = m_btn_patnt_mng;
    btn[1] = m_btn_record;
    btn[2] = m_btn_set;
    btn[3] = m_btn_alarm;
    btn[4] = m_btn_serve;
    int iTotalObj = 5;
    switch (k) {
     case 9:

        if(iCursor == 0)
        {
            iCursor = iTotalObj-1;
        }
        else
        {
            iCursor -=1;
        }
        btn[iCursor]->setFocus();

        break;
    case 10:

        if(iCursor == iTotalObj-1)
        {
            iCursor = 0;
        }
        else
        {
            iCursor +=1;
        }
        btn[iCursor]->setFocus();

        break;

    case 6:

        emit(signal_btn_clicked(btn[iCursor]));
        break;

    default:
        f_process_key(k);
        break;
        //
    }
}




void CMainForm::keyPressEvent(QKeyEvent *event)
{
    QPushButton *btn[5];
    btn[0] = m_btn_patnt_mng;
    btn[1] = m_btn_record;
    btn[2] = m_btn_set;
    btn[3] = m_btn_alarm;
    btn[4] = m_btn_serve;

    switch (event->key()) {

    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Down:
    case Qt::Key_Up:
    case Qt::Key_Return:
        btn[0]->setFocus();
        break;

    default:
        QWidget::keyPressEvent(event);
    }
    //QWidget::keyPressEvent(event);
}

bool CMainForm::f_process_key(int key)
{
    switch(key)
    {
    case  68://silence
    {


        return true;
    }
    case (Qt::Key_F9)://pause
    {


        return true;
    }

    case(Qt::Key_F10)://freeze
    {
        if(m_freeze_flg)
        {
            m_freeze_flg = false;
        }
        else
        {
            m_freeze_flg = true;
        }
        g_WavePlotter->freezeScreen(m_freeze_flg);
        return true;
    }

    case(Qt::Key_F11)://nibp
    {

        g_EcgModule->f_do_nibp_measure();
        return true;
    }

    case(Qt::Key_F12)://print
    {

        return true;
    }
    default:
        //QWidget::keyPressEvent(event);
        return false;
    }
}
