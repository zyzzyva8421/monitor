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

int g_WaveWidgetWidthPix = 730;
int g_WaveWidgetAllHeightPix = 696;
int g_WaveWidgetHeightPix = 50;
int g_WaveNumber = MAX_PLOT_CURVES;

double g_PixPerByte_3_125mm = 0.08295454; //(730[pix]/220[mm])* 3.125[mm/s] / (125[Byte/s])
double g_PixPerByte_6_25mm = 0.16590909; //(730[pix]/220[mm])* 6.25[mm/s] / (125[Byte/s])
double g_PixPerByte_12_5mm =  0.33181818;// (730[pix]/220[mm])* 12.5[mm/s] / (125[Byte/s])
double g_PixPerByte_25mm =  0.66363636;//(730[pix]/220[mm])* 25[mm/s] / (125[Byte/s])
double g_PixPerByte_50mm =  1.32727273;//(730[pix]/220[mm])* 50[mm/s] / (125[Byte/s])

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

void CMainForm::f_set_standard_layout()
{
    resize(1024, 768);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    QFont font;
    font.setFamily(QString::fromUtf8("WenQuanYi Micro Hei"));
    font.setPointSize(11);
    font.setBold(false);
    font.setWeight(50);
    setFont(font);
    setCursor(QCursor(Qt::ArrowCursor));
    setFocusPolicy(Qt::NoFocus);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setAcceptDrops(false);
    setWindowOpacity(1);
#ifndef QT_NO_ACCESSIBILITY
    setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY
    setLayoutDirection(Qt::LeftToRight);
    setAutoFillBackground(false);
    setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
    setLocale(QLocale(QLocale::Chinese, QLocale::China));

    // ECG Standard Layout
    //rame_ECG->setGeometry(QRect(730, 146, 292, 90));
    TextLabel_XinLv_ShangXian->show();
    TextLabel_XinLv_XiaXian->show();
    TextLabel_XinLv_STkaiguan1->show();
    TextLabel_XinLv_STkaiguan2->show();
    TextLabel_XinLv_STkaiguan1_Text->show();
    TextLabel_XinLv_STkaiguan2_Text->show();

    // Temprature Standdar Layout
    //frame_temp->setGeometry(QRect(730, 655, 292, 72));
    TextLabel_TiWen_SheShiDu->show();

    // IBP2 Standard Layout
    //frame_ibp2->setGeometry(QRect(730, 492, 292, 80));
    //frame_ibp2->show();

    // IBP1 Standard Layout
    //frame_ibp1->setGeometry(QRect(730, 410, 292, 80));
    //frame_ibp1->show();

    // NIBP Standard Layout
    //frame_nibp->setGeometry(QRect(730, 319, 292, 90));
    TextLabel_WuChuangXueYa_XiaXian->show();
    TextLabel_WuChuangXueYa_ShangXian->show();
    TextLabel_WuChuangXueYa_fenzhong->show();
    TextLabel_WuChuangXueYa_xiudaiya->show();
    TextLabel_WuChuangXueYa_xiudaiya_value->show();

    // Mashen Standard  Layout
    //frame_mashen->setGeometry(QRect(730, 33, 292, 112));
   // frame_mashen->show();

    // SPO2 Standard Layout
    //frame_spo2->setGeometry(QRect(730, 237, 292, 80));
    TextLabel_XueYang_XiaXian->show();
    TextLabel_XueYang_ShangXian->show();
    TextLabel_MaiLv_ShangXian->show();
    TextLabel_MaiLv_XiaXian->show();

    // SP Standard Layout
    //frame_sp->setGeometry(QRect(730, 573, 292, 80));
    TextLabel_HuXiLv_ShangXian->show();
    TextLabel_HuXiLv_XiaXian->show();
    TextLabel_HuXiLvCo2_Co2_ShangXian->show();
    TextLabel_HuXiLvCo2_Co2_XiaXian->show();

    // ECG Standard Layout
    QFont font1;
    font1.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    frame_ECG->setFont(font1);
    frame_ECG->setAutoFillBackground(false);
    frame_ECG->setStyleSheet(QString::fromUtf8("color:red;\n"
"border-color: rgb(255, 255, 255);\n"
"border-width:1px;\n"
"border-style:solid;"));
    frame_ECG->setFrameShape(QFrame::StyledPanel);
    frame_ECG->setFrameShadow(QFrame::Plain);
    TextLabel_XinLv->setGeometry(QRect(5, 5, 51, 30));
    QFont font2;
    font2.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font2.setPointSize(18);
    TextLabel_XinLv->setFont(font2);
    TextLabel_XinLv->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_ShangXian->setGeometry(QRect(20, 40, 32, 20));
    TextLabel_XinLv_ShangXian->setFont(font1);
    TextLabel_XinLv_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_XiaXian->setGeometry(QRect(20, 61, 32, 20));
    TextLabel_XinLv_XiaXian->setFont(font1);
    TextLabel_XinLv_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_bpm->setGeometry(QRect(90, 5, 50, 25));
    QFont font3;
    font3.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font3.setPointSize(16);
    TextLabel_XinLv_bpm->setFont(font3);
    TextLabel_XinLv_bpm->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_bpm->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_value->setGeometry(QRect(60, 31, 111, 57));
    QFont font4;
    font4.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font4.setPointSize(40);
    font4.setBold(true);
    font4.setWeight(75);
    TextLabel_XinLv_value->setFont(font4);
    TextLabel_XinLv_value->setLayoutDirection(Qt::RightToLeft);
    TextLabel_XinLv_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_value->setMidLineWidth(1);
    TextLabel_XinLv_value->setTextFormat(Qt::RichText);
    TextLabel_XinLv_value->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_QiBo->setGeometry(QRect(170, 57, 45, 26));
    QFont font5;
    font5.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font5.setPointSize(10);
    TextLabel_XinLv_QiBo->setFont(font5);
    TextLabel_XinLv_QiBo->setAutoFillBackground(false);
    TextLabel_XinLv_QiBo->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_QiBo->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_STkaiguan1->setGeometry(QRect(170, 5, 45, 25));
    TextLabel_XinLv_STkaiguan1->setFont(font5);
    TextLabel_XinLv_STkaiguan1->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_STkaiguan1->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_STkaiguan2->setGeometry(QRect(170, 31, 45, 25));
    TextLabel_XinLv_STkaiguan2->setFont(font5);
    TextLabel_XinLv_STkaiguan2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_STkaiguan2->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_QiBo_KaiGuan->setGeometry(QRect(230, 57, 50, 26));
    TextLabel_XinLv_QiBo_KaiGuan->setFont(font2);
    TextLabel_XinLv_QiBo_KaiGuan->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_QiBo_KaiGuan->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_STkaiguan1_Text->setGeometry(QRect(230, 5, 50, 25));
    TextLabel_XinLv_STkaiguan1_Text->setFont(font2);
    TextLabel_XinLv_STkaiguan1_Text->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_STkaiguan1_Text->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_STkaiguan2_Text->setGeometry(QRect(230, 31, 50, 25));
    TextLabel_XinLv_STkaiguan2_Text->setFont(font2);
    TextLabel_XinLv_STkaiguan2_Text->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_STkaiguan2_Text->setAlignment(Qt::AlignCenter);

    // Temprature Standdar Layout
    frame_temp->setFont(font1);
    frame_temp->setStyleSheet(QString::fromUtf8("color:rgb(255, 62, 14);border-color: rgb(255, 255, 255);border-style:solid;border-width:1px;\n"
""));
    frame_temp->setFrameShape(QFrame::StyledPanel);
    frame_temp->setFrameShadow(QFrame::Plain);
    TextLabel_TiWen_1->setGeometry(QRect(5, 5, 59, 30));
    TextLabel_TiWen_1->setFont(font2);
    TextLabel_TiWen_1->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_1->setFrameShape(QFrame::NoFrame);
    TextLabel_TiWen_1->setFrameShadow(QFrame::Raised);
    TextLabel_TiWen_1->setLineWidth(1);
    TextLabel_TiWen_1->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_1_ShangXian->setGeometry(QRect(15, 36, 32, 15));
    TextLabel_TiWen_1_ShangXian->setFont(font1);
    TextLabel_TiWen_1_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_1_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_1_XiaXian->setGeometry(QRect(15, 52, 32, 15));
    TextLabel_TiWen_1_XiaXian->setFont(font1);
    TextLabel_TiWen_1_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_1_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_2_XiaXian->setGeometry(QRect(161, 52, 32, 15));
    TextLabel_TiWen_2_XiaXian->setFont(font1);
    TextLabel_TiWen_2_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_2_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_2->setGeometry(QRect(146, 5, 59, 30));
    TextLabel_TiWen_2->setFont(font2);
    TextLabel_TiWen_2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_2->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_2_ShangXian->setGeometry(QRect(161, 32, 32, 15));
    TextLabel_TiWen_2_ShangXian->setFont(font1);
    TextLabel_TiWen_2_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_2_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_1_value_2->setGeometry(QRect(60, 32, 81, 35));
    QFont font6;
    font6.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font6.setPointSize(30);
    font6.setBold(true);
    font6.setWeight(75);
    TextLabel_TiWen_1_value_2->setFont(font6);
    TextLabel_TiWen_1_value_2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_1_value_2->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_SheShiDu->setGeometry(QRect(90, 10, 32, 21));
    QFont font7;
    font7.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font7.setPointSize(15);
    TextLabel_TiWen_SheShiDu->setFont(font7);
    TextLabel_TiWen_SheShiDu->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_SheShiDu->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_2_value_2->setGeometry(QRect(200, 32, 81, 35));
    TextLabel_TiWen_2_value_2->setFont(font6);
    TextLabel_TiWen_2_value_2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_2_value_2->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_SheShiDu2->setGeometry(QRect(230, 10, 32, 21));
    TextLabel_TiWen_SheShiDu2->setFont(font7);
    TextLabel_TiWen_SheShiDu2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_SheShiDu2->setAlignment(Qt::AlignCenter);

    // IBP2 Standard Layout
    frame_ibp2->setFont(font1);
    frame_ibp2->setStyleSheet(QString::fromUtf8("color:rgb(60, 102, 255);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width:1px;\n"
"border-style:solid;"));
    frame_ibp2->setFrameShape(QFrame::StyledPanel);
    frame_ibp2->setFrameShadow(QFrame::Plain);
    TextLabel_ZhongXinJingMaiYa_mmHg->setGeometry(QRect(220, 10, 70, 59));
    TextLabel_ZhongXinJingMaiYa_mmHg->setFont(font3);
    TextLabel_ZhongXinJingMaiYa_mmHg->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_ZhongXinJingMaiYa_mmHg->setAlignment(Qt::AlignCenter);
    TextLabel_IBP2_Name->setGeometry(QRect(5, 10, 121, 59));
    QFont font8;
    font8.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font8.setPointSize(17);
    TextLabel_IBP2_Name->setFont(font8);
    TextLabel_IBP2_Name->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_IBP2_Name->setAlignment(Qt::AlignCenter);
    TextLabel_ZhongXinJingMaiYa_value_unkown->setGeometry(QRect(130, 20, 91, 51));
    QFont font9;
    font9.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font9.setPointSize(31);
    font9.setBold(true);
    font9.setWeight(75);
    TextLabel_ZhongXinJingMaiYa_value_unkown->setFont(font9);
    TextLabel_ZhongXinJingMaiYa_value_unkown->setLayoutDirection(Qt::RightToLeft);
    TextLabel_ZhongXinJingMaiYa_value_unkown->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_ZhongXinJingMaiYa_value_unkown->setMidLineWidth(1);
    TextLabel_ZhongXinJingMaiYa_value_unkown->setTextFormat(Qt::RichText);
    TextLabel_ZhongXinJingMaiYa_value_unkown->setAlignment(Qt::AlignCenter);

    // IBP1 Standard Layout
    frame_ibp1->setFont(font1);
    frame_ibp1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 127);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width:1px;\n"
"border-style:solid;"));
    frame_ibp1->setFrameShape(QFrame::StyledPanel);
    frame_ibp1->setFrameShadow(QFrame::Plain);
    frame_ibp1->setLineWidth(1);
    TextLabel_IBP1_Name->setGeometry(QRect(5, 5, 95, 30));
    TextLabel_IBP1_Name->setFont(font2);
    TextLabel_IBP1_Name->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_IBP1_Name->setAlignment(Qt::AlignCenter);
    TextLabel_ZhuDongMaiYa_mmHg->setGeometry(QRect(210, 5, 70, 25));
    TextLabel_ZhuDongMaiYa_mmHg->setFont(font3);
    TextLabel_ZhuDongMaiYa_mmHg->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_ZhuDongMaiYa_mmHg->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    TextLabel_ZhuDongMaiYa_value_Di->setGeometry(QRect(200, 36, 90, 40));
    QFont font10;
    font10.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font10.setPointSize(31);
    TextLabel_ZhuDongMaiYa_value_Di->setFont(font10);
    TextLabel_ZhuDongMaiYa_value_Di->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_ZhuDongMaiYa_value_Di->setAlignment(Qt::AlignCenter);
    TextLabel_ZhuDongMaiYa_value_Gao->setGeometry(QRect(5, 36, 92, 40));
    TextLabel_ZhuDongMaiYa_value_Gao->setFont(font9);
    TextLabel_ZhuDongMaiYa_value_Gao->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_ZhuDongMaiYa_value_Gao->setAlignment(Qt::AlignCenter);
    TextLabel_ZhuDongMaiYa_value_unkown->setGeometry(QRect(132, 36, 61, 40));
    TextLabel_ZhuDongMaiYa_value_unkown->setFont(font10);
    TextLabel_ZhuDongMaiYa_value_unkown->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_ZhuDongMaiYa_value_unkown->setAlignment(Qt::AlignCenter);
    TextLabel_ZhuDongMaiYa_value_XieXian->setGeometry(QRect(120, 40, 21, 31));
    QFont font11;
    font11.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font11.setPointSize(14);
    TextLabel_ZhuDongMaiYa_value_XieXian->setFont(font11);
    TextLabel_ZhuDongMaiYa_value_XieXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_ZhuDongMaiYa_value_XieXian->setAlignment(Qt::AlignCenter);

    // NIBP Standard Layout
    frame_nibp->setFont(font1);
    frame_nibp->setAutoFillBackground(false);
    frame_nibp->setStyleSheet(QString::fromUtf8("color:rgb(0, 85, 255);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width:1px;\n"
"border-style:solid;\n"
"\n"
"\n"
""));
    frame_nibp->setFrameShape(QFrame::StyledPanel);
    frame_nibp->setFrameShadow(QFrame::Plain);
    TextLabel_WuChuangXueYa->setGeometry(QRect(5, 5, 95, 30));
    TextLabel_WuChuangXueYa->setFont(font2);
    TextLabel_WuChuangXueYa->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa->setAlignment(Qt::AlignCenter);
    label_nibp_unit->setGeometry(QRect(210, 5, 70, 25));
    label_nibp_unit->setFont(font3);
    label_nibp_unit->setStyleSheet(QString::fromUtf8("border-style:none;"));
    label_nibp_unit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    TextLabel_WuChuangXueYa_XiaXian->setGeometry(QRect(20, 50, 30, 18));
    TextLabel_WuChuangXueYa_XiaXian->setFont(font1);
    TextLabel_WuChuangXueYa_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_ShangXian->setGeometry(QRect(20, 31, 32, 18));
    TextLabel_WuChuangXueYa_ShangXian->setFont(font1);
    TextLabel_WuChuangXueYa_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_ShouDong->setGeometry(QRect(20, 69, 40, 15));
    TextLabel_WuChuangXueYa_ShouDong->setFont(font1);
    TextLabel_WuChuangXueYa_ShouDong->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_ShouDong->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_fenzhong->setGeometry(QRect(120, 69, 30, 15));
    TextLabel_WuChuangXueYa_fenzhong->setFont(font1);
    TextLabel_WuChuangXueYa_fenzhong->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_ZiDongJianGe->setGeometry(QRect(70, 72, 40, 10));
    QFont font12;
    font12.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font12.setPointSize(8);
    TextLabel_WuChuangXueYa_ZiDongJianGe->setFont(font12);
    TextLabel_WuChuangXueYa_ZiDongJianGe->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_ZiDongJianGe->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_value_Gao_2->setGeometry(QRect(70, 30, 69, 39));
    QFont font13;
    font13.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font13.setPointSize(25);
    font13.setBold(true);
    font13.setWeight(75);
    TextLabel_WuChuangXueYa_value_Gao_2->setFont(font13);
    TextLabel_WuChuangXueYa_value_Gao_2->setLayoutDirection(Qt::RightToLeft);
    TextLabel_WuChuangXueYa_value_Gao_2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_value_Gao_2->setMidLineWidth(1);
    TextLabel_WuChuangXueYa_value_Gao_2->setTextFormat(Qt::RichText);
    TextLabel_WuChuangXueYa_value_Gao_2->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_value_Pingjun->setGeometry(QRect(158, 30, 51, 39));
    TextLabel_WuChuangXueYa_value_Pingjun->setFont(font13);
    TextLabel_WuChuangXueYa_value_Pingjun->setLayoutDirection(Qt::RightToLeft);
    TextLabel_WuChuangXueYa_value_Pingjun->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_value_Pingjun->setMidLineWidth(1);
    TextLabel_WuChuangXueYa_value_Pingjun->setTextFormat(Qt::RichText);
    TextLabel_WuChuangXueYa_value_Pingjun->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_value_Di->setGeometry(QRect(210, 30, 69, 39));
    TextLabel_WuChuangXueYa_value_Di->setFont(font13);
    TextLabel_WuChuangXueYa_value_Di->setLayoutDirection(Qt::RightToLeft);
    TextLabel_WuChuangXueYa_value_Di->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_value_Di->setMidLineWidth(1);
    TextLabel_WuChuangXueYa_value_Di->setTextFormat(Qt::RichText);
    TextLabel_WuChuangXueYa_value_Di->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_xiudaiya->setGeometry(QRect(160, 70, 51, 16));
    TextLabel_WuChuangXueYa_xiudaiya->setFont(font1);
    TextLabel_WuChuangXueYa_xiudaiya->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_xiudaiya->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_xiudaiya_value->setGeometry(QRect(220, 70, 40, 16));
    QFont font14;
    font14.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font14.setPointSize(12);
    TextLabel_WuChuangXueYa_xiudaiya_value->setFont(font14);
    TextLabel_WuChuangXueYa_xiudaiya_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_xiudaiya_value->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_value_XieXian->setGeometry(QRect(140, 40, 21, 21));
    TextLabel_WuChuangXueYa_value_XieXian->setFont(font11);
    TextLabel_WuChuangXueYa_value_XieXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_value_XieXian->setAlignment(Qt::AlignCenter);

    // SPO2 Standard Layout
    frame_spo2->setFont(font1);
    frame_spo2->setAutoFillBackground(false);
    frame_spo2->setStyleSheet(QString::fromUtf8("color: rgb(85, 255, 0);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width:1px;\n"
"border-style:solid;"));
    frame_spo2->setFrameShape(QFrame::StyledPanel);
    frame_spo2->setFrameShadow(QFrame::Plain);
    TextLabel_MaiLv->setGeometry(QRect(230, 5, 55, 25));
    TextLabel_MaiLv->setFont(font3);
    TextLabel_MaiLv->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_MaiLv->setAlignment(Qt::AlignCenter);
    TextLabel_XueYang->setGeometry(QRect(5, 5, 51, 25));
    TextLabel_XueYang->setFont(font2);
    TextLabel_XueYang->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XueYang->setAlignment(Qt::AlignCenter);
    TextLabel_XueYang_BaiFenHao->setGeometry(QRect(130, 5, 21, 16));
    TextLabel_XueYang_BaiFenHao->setFont(font11);
    TextLabel_XueYang_BaiFenHao->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XueYang_XiaXian->setGeometry(QRect(20, 52, 32, 25));
    TextLabel_XueYang_XiaXian->setFont(font1);
    TextLabel_XueYang_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XueYang_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_XueYang_ShangXian->setGeometry(QRect(20, 31, 32, 20));
    TextLabel_XueYang_ShangXian->setFont(font1);
    TextLabel_XueYang_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XueYang_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_MaiLv_value->setParent(frame_spo2);
    TextLabel_MaiLv_value->show();
    TextLabel_MaiLv_value->setGeometry(QRect(230, 30, 50, 45));
    TextLabel_MaiLv_value->setFont(font2);
    TextLabel_MaiLv_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_MaiLv_value->setAlignment(Qt::AlignCenter);
    TextLabel_XueYang_value->setGeometry(QRect(79, 20, 121, 57));
    TextLabel_XueYang_value->setFont(font4);
    TextLabel_XueYang_value->setLayoutDirection(Qt::RightToLeft);
    TextLabel_XueYang_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XueYang_value->setMidLineWidth(1);
    TextLabel_XueYang_value->setTextFormat(Qt::RichText);
    TextLabel_XueYang_value->setAlignment(Qt::AlignCenter);
    TextLabel_MaiLv_ShangXian->setGeometry(QRect(200, 30, 32, 20));
    TextLabel_MaiLv_ShangXian->setFont(font1);
    TextLabel_MaiLv_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_MaiLv_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_MaiLv_XiaXian->setGeometry(QRect(200, 51, 32, 25));
    TextLabel_MaiLv_XiaXian->setFont(font1);
    TextLabel_MaiLv_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_MaiLv_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_XueYang_2->setParent(frame_spo2);
    TextLabel_XueYang_2->show();
    TextLabel_XueYang_2->setGeometry(QRect(170, 5, 51, 25));
    TextLabel_XueYang_2->setFont(font7);
    TextLabel_XueYang_2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XueYang_2->setAlignment(Qt::AlignCenter);

    // Mashen Standard  Layout
    frame_mashen->setFont(font1);
    frame_mashen->setAutoFillBackground(false);
    frame_mashen->setStyleSheet(QString::fromUtf8("color: purple;\n"
"border-color: rgb(255, 255, 255);\n"
"border-width:1px;\n"
"border-style:solid;\n"
""));
    frame_mashen->setFrameShape(QFrame::StyledPanel);
    frame_mashen->setFrameShadow(QFrame::Plain);
    TextLabel_AnaesDep_BaiDianJiDanWei->setGeometry(QRect(100, 90, 32, 20));
    TextLabel_AnaesDep_BaiDianJiDanWei->setFont(font1);
    TextLabel_AnaesDep_BaiDianJiDanWei->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_BaiDianJiDanWei->setAlignment(Qt::AlignCenter);
    TextLabel_AnaesDep_XiaXian->setGeometry(QRect(30, 50, 41, 20));
    TextLabel_AnaesDep_XiaXian->setFont(font1);
    TextLabel_AnaesDep_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_AnaesDep_HeiDianJiDanWei->setGeometry(QRect(246, 90, 32, 20));
    TextLabel_AnaesDep_HeiDianJiDanWei->setFont(font1);
    TextLabel_AnaesDep_HeiDianJiDanWei->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_HeiDianJiDanWei->setAlignment(Qt::AlignCenter);
    TextLabel_AnaesDep_XinHao->setGeometry(QRect(194, 70, 32, 20));
    TextLabel_AnaesDep_XinHao->setFont(font1);
    TextLabel_AnaesDep_XinHao->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_ShangXian->setGeometry(QRect(30, 30, 41, 20));
    TextLabel_AnaesDep_ShangXian->setFont(font1);
    TextLabel_AnaesDep_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_AnaesDep_BaiDianJi_value->setGeometry(QRect(60, 90, 40, 20));
    TextLabel_AnaesDep_BaiDianJi_value->setFont(font1);
    TextLabel_AnaesDep_BaiDianJi_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_BaiDianJi_value->setAlignment(Qt::AlignCenter);
    label_49->setGeometry(QRect(5, 10, 90, 20));
    QFont font17;
    font17.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font17.setPointSize(18);
    font17.setBold(false);
    font17.setItalic(false);
    font17.setWeight(50);
    label_49->setFont(font17);
    label_49->setStyleSheet(QString::fromUtf8("border-style:none;"));
    label_49->setFrameShape(QFrame::NoFrame);
    label_49->setFrameShadow(QFrame::Raised);
    label_49->setLineWidth(0);
    label_49->setAlignment(Qt::AlignCenter);
    label_49->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    TextLabel_AnaesDep_JiDian_value->setGeometry(QRect(147, 70, 40, 20));
    TextLabel_AnaesDep_JiDian_value->setFont(font1);
    TextLabel_AnaesDep_JiDian_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_JiDian_value->setAlignment(Qt::AlignCenter);
    TextLabel_AnaesDep_YiZhi_value->setGeometry(QRect(50, 70, 40, 20));
    TextLabel_AnaesDep_YiZhi_value->setFont(font1);
    TextLabel_AnaesDep_YiZhi_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_YiZhi_value->setAlignment(Qt::AlignCenter);
    TextLabel_AnaesDep_JiDian->setGeometry(QRect(97, 70, 32, 20));
    TextLabel_AnaesDep_JiDian->setFont(font1);
    TextLabel_AnaesDep_JiDian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_BaiDianJi->setGeometry(QRect(10, 90, 51, 20));
    TextLabel_AnaesDep_BaiDianJi->setFont(font1);
    TextLabel_AnaesDep_BaiDianJi->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_HeiDianJi_value->setGeometry(QRect(196, 90, 40, 20));
    TextLabel_AnaesDep_HeiDianJi_value->setFont(font1);
    TextLabel_AnaesDep_HeiDianJi_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_HeiDianJi_value->setAlignment(Qt::AlignCenter);
    TextLabel_AnaesDep_YiZhi->setGeometry(QRect(10, 70, 32, 20));
    TextLabel_AnaesDep_YiZhi->setFont(font1);
    TextLabel_AnaesDep_YiZhi->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_HeiDianJi->setGeometry(QRect(146, 90, 51, 20));
    TextLabel_AnaesDep_HeiDianJi->setFont(font1);
    TextLabel_AnaesDep_HeiDianJi->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_XinHao_value->setGeometry(QRect(234, 70, 40, 20));
    TextLabel_AnaesDep_XinHao_value->setFont(font1);
    TextLabel_AnaesDep_XinHao_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_XinHao_value->setAlignment(Qt::AlignCenter);
    label_68->setGeometry(QRect(238, 8, 51, 51));
    QFont font18;
    font18.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font18.setPointSize(29);
    font18.setItalic(false);
    label_68->setFont(font18);
    label_68->setStyleSheet(QString::fromUtf8("border-style:none;"));
    label_68->setAlignment(Qt::AlignCenter);
    TextLabel_AnaesDep_value->setGeometry(QRect(120, 10, 111, 57));
    TextLabel_AnaesDep_value->setFont(font4);
    TextLabel_AnaesDep_value->setLayoutDirection(Qt::RightToLeft);
    TextLabel_AnaesDep_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_AnaesDep_value->setMidLineWidth(1);
    TextLabel_AnaesDep_value->setTextFormat(Qt::RichText);
    TextLabel_AnaesDep_value->setAlignment(Qt::AlignCenter);
    verticalLayoutWidget->setGeometry(QRect(730, 30, 2, 2));
    verticalLayoutWidget->setFont(font1);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    // SP Standard Layout
    frame_sp->setFont(font1);
    frame_sp->setAutoFillBackground(false);
    frame_sp->setStyleSheet(QString::fromUtf8("color:rgb(255, 165, 10);\n"
"border-color: rgb(255, 255, 255);\n"
"border-style:solid;\n"
"border-width:1px;"));
    frame_sp->setFrameShape(QFrame::StyledPanel);
    frame_sp->setFrameShadow(QFrame::Plain);
    TextLabel_HuXiLv_ShangXian->setGeometry(QRect(15, 36, 30, 20));
    TextLabel_HuXiLv_ShangXian->setFont(font1);
    TextLabel_HuXiLv_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLv_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLv_value->setGeometry(QRect(42, 36, 71, 40));
    QFont font19;
    font19.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font19.setPointSize(26);
    font19.setBold(false);
    font19.setWeight(50);
    TextLabel_HuXiLv_value->setFont(font19);
    TextLabel_HuXiLv_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLv_value->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_XiaXian->setGeometry(QRect(110, 57, 30, 21));
    TextLabel_HuXiLvCo2_Co2_XiaXian->setFont(font1);
    TextLabel_HuXiLvCo2_Co2_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLv->setGeometry(QRect(5, 5, 71, 30));
    TextLabel_HuXiLv->setFont(font2);
    TextLabel_HuXiLv->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLv->setFrameShape(QFrame::NoFrame);
    TextLabel_HuXiLv->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_value_XiRu->setGeometry(QRect(141, 36, 60, 40));
    QFont font20;
    font20.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font20.setPointSize(15);
    font20.setBold(true);
    font20.setWeight(75);
    TextLabel_HuXiLvCo2_Co2_value_XiRu->setFont(font20);
    TextLabel_HuXiLvCo2_Co2_value_XiRu->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2_value_XiRu->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_ShangXian->setGeometry(QRect(110, 36, 30, 22));
    TextLabel_HuXiLvCo2_Co2_ShangXian->setFont(font1);
    TextLabel_HuXiLvCo2_Co2_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLv_XiaXian->setGeometry(QRect(15, 57, 30, 20));
    TextLabel_HuXiLv_XiaXian->setFont(font1);
    TextLabel_HuXiLv_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLv_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2->setGeometry(QRect(110, 5, 100, 29));
    TextLabel_HuXiLvCo2_Co2->setFont(font7);
    TextLabel_HuXiLvCo2_Co2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_mmHg->setGeometry(QRect(220, 5, 50, 30));
    TextLabel_HuXiLvCo2_Co2_mmHg->setFont(font2);
    TextLabel_HuXiLvCo2_Co2_mmHg->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2_mmHg->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_value_HuMo->setGeometry(QRect(210, 36, 79, 40));
    QFont font21;
    font21.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font21.setPointSize(24);
    font21.setBold(true);
    font21.setWeight(75);
    TextLabel_HuXiLvCo2_Co2_value_HuMo->setFont(font21);
    TextLabel_HuXiLvCo2_Co2_value_HuMo->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2_value_HuMo->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_value_XieXian->setGeometry(QRect(200, 40, 21, 31));
    TextLabel_HuXiLvCo2_Co2_value_XieXian->setFont(font11);
    TextLabel_HuXiLvCo2_Co2_value_XieXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2_value_XieXian->setAlignment(Qt::AlignCenter);

}

void CMainForm::f_set_big_font_layout()
{
    // ECG Big Font Layout
   // frame_ECG->setGeometry(QRect(590, 35, 430, 215));
    TextLabel_XinLv_ShangXian->hide();
    TextLabel_XinLv_XiaXian->hide();
    TextLabel_XinLv_STkaiguan1->hide();
    TextLabel_XinLv_STkaiguan2->hide();
    TextLabel_XinLv_STkaiguan1_Text->hide();
    TextLabel_XinLv_STkaiguan2_Text->hide();

    // Temparture Big Font Layout
    //frame_temp->setGeometry(QRect(590, 600, 430, 120));
    TextLabel_TiWen_SheShiDu->hide();

    // NIBP Standard Layout
    //frame_nibp->setGeometry(QRect(5, 480, 580, 240));
    TextLabel_WuChuangXueYa_XiaXian->hide();
    TextLabel_WuChuangXueYa_ShangXian->hide();
    TextLabel_WuChuangXueYa_fenzhong->hide();
    TextLabel_WuChuangXueYa_xiudaiya->hide();
    TextLabel_WuChuangXueYa_xiudaiya_value->hide();

    // SPO2 Big Font Layout
    //frame_spo2->setGeometry(QRect(590, 380, 430, 215));
    TextLabel_XueYang_XiaXian->hide();
    TextLabel_XueYang_ShangXian->hide();
    TextLabel_MaiLv_ShangXian->hide();
    TextLabel_MaiLv_XiaXian->hide();

    // SP Big Font Layout
     //frame_sp->setGeometry(QRect(590, 255, 430, 120));
     TextLabel_HuXiLv_ShangXian->hide();
     TextLabel_HuXiLv_XiaXian->hide();
     TextLabel_HuXiLvCo2_Co2_ShangXian->hide();
     TextLabel_HuXiLvCo2_Co2_XiaXian->hide();

     // IBP2 Standard Layout
     frame_ibp2->hide();

     // Mashen Standard  Layout
     frame_mashen->hide();

     // IBP1 Big Font Layout
     frame_ibp1->hide();

    // ECG Big Font Layout
    QFont font1;
    font1.setFamily(QString::fromUtf8("WenQuanYi Micro Hei"));
    frame_ECG->setFont(font1);
    frame_ECG->setAutoFillBackground(false);
    frame_ECG->setStyleSheet(QString::fromUtf8("color:red;\n"
"border-color: rgb(255, 255, 255);\n"
"border-width:1px;\n"
"border-style:solid;"));
    frame_ECG->setFrameShape(QFrame::StyledPanel);
    frame_ECG->setFrameShadow(QFrame::Plain);
    TextLabel_XinLv->setGeometry(QRect(5, 5, 40, 20));
    QFont font2;
    font2.setPointSize(14);
    TextLabel_XinLv->setFont(font2);
    TextLabel_XinLv->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_bpm->setGeometry(QRect(370, 5, 40, 20));
    TextLabel_XinLv_bpm->setFont(font2);
    TextLabel_XinLv_bpm->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_bpm->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_value->setGeometry(QRect(50, 40, 331, 141));
    QFont font3;
    font3.setPointSize(100);
    font3.setBold(true);
    font3.setWeight(75);
    TextLabel_XinLv_value->setFont(font3);
    TextLabel_XinLv_value->setLayoutDirection(Qt::RightToLeft);
    TextLabel_XinLv_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_value->setMidLineWidth(1);
    TextLabel_XinLv_value->setTextFormat(Qt::RichText);
    TextLabel_XinLv_value->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_QiBo->setGeometry(QRect(280, 5, 40, 20));
    QFont font4;
    font4.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font4.setPointSize(14);
    TextLabel_XinLv_QiBo->setFont(font4);
    TextLabel_XinLv_QiBo->setAutoFillBackground(false);
    TextLabel_XinLv_QiBo->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_QiBo->setAlignment(Qt::AlignCenter);
    TextLabel_XinLv_QiBo_KaiGuan->setGeometry(QRect(320, 5, 40, 20));
    TextLabel_XinLv_QiBo_KaiGuan->setFont(font4);
    TextLabel_XinLv_QiBo_KaiGuan->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XinLv_QiBo_KaiGuan->setAlignment(Qt::AlignCenter);

    // Temparture Big Font Layout
    frame_temp->setStyleSheet(QString::fromUtf8("color:rgb(255, 62, 14);\n"
"border-color: rgb(255, 255, 255);\n"
"border-style:solid;\n"
"border-width:1px;"));
    frame_temp->setFrameShape(QFrame::StyledPanel);
    frame_temp->setFrameShadow(QFrame::Plain);
    TextLabel_TiWen_1->setGeometry(QRect(5, 5, 59, 30));
    QFont font5;
    font5.setFamily(QString::fromUtf8("WenQuanYi Micro Hei Mono"));
    font5.setPointSize(14);
    TextLabel_TiWen_1->setFont(font5);
    TextLabel_TiWen_1->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_1->setFrameShape(QFrame::NoFrame);
    TextLabel_TiWen_1->setFrameShadow(QFrame::Raised);
    TextLabel_TiWen_1->setLineWidth(1);
    TextLabel_TiWen_1->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_1_ShangXian->setGeometry(QRect(15, 36, 32, 15));
    QFont font6;
    font6.setFamily(QString::fromUtf8("WenQuanYi Micro Hei Mono"));
    TextLabel_TiWen_1_ShangXian->setFont(font6);
    TextLabel_TiWen_1_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_1_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_1_XiaXian->setGeometry(QRect(15, 52, 32, 15));
    TextLabel_TiWen_1_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_1_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_2_XiaXian->setGeometry(QRect(210, 52, 32, 15));
    TextLabel_TiWen_2_XiaXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_2_XiaXian->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_2->setGeometry(QRect(200, 5, 59, 30));
    TextLabel_TiWen_2->setFont(font2);
    TextLabel_TiWen_2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_2->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_2_ShangXian->setGeometry(QRect(210, 32, 32, 15));
    TextLabel_TiWen_2_ShangXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_2_ShangXian->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_1_value_2->setGeometry(QRect(50, 40, 160, 60));
    QFont font7;
    font7.setPointSize(50);
    font7.setBold(true);
    font7.setWeight(75);
    TextLabel_TiWen_1_value_2->setFont(font7);
    TextLabel_TiWen_1_value_2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_1_value_2->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_2_value_2->setGeometry(QRect(250, 40, 160, 60));
    TextLabel_TiWen_2_value_2->setFont(font7);
    TextLabel_TiWen_2_value_2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_2_value_2->setAlignment(Qt::AlignCenter);
    TextLabel_TiWen_SheShiDu2->setGeometry(QRect(390, 10, 32, 21));
    TextLabel_TiWen_SheShiDu2->setFont(font2);
    TextLabel_TiWen_SheShiDu2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_TiWen_SheShiDu2->setAlignment(Qt::AlignCenter);

    // SPO2 Big Font Layout
    frame_spo2->setAutoFillBackground(false);
    frame_spo2->setStyleSheet(QString::fromUtf8("color: rgb(85, 255, 0);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width:1px;\n"
"border-style:solid;"));
    frame_spo2->setFrameShape(QFrame::StyledPanel);
    frame_spo2->setFrameShadow(QFrame::Plain);
    TextLabel_XueYang->setGeometry(QRect(5, 5, 51, 25));
    TextLabel_XueYang->setFont(font2);
    TextLabel_XueYang->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XueYang->setAlignment(Qt::AlignCenter);
    TextLabel_XueYang_BaiFenHao->setGeometry(QRect(400, 5, 21, 16));
    TextLabel_XueYang_BaiFenHao->setFont(font2);
    TextLabel_XueYang_BaiFenHao->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XueYang_value->setGeometry(QRect(60, 40, 311, 131));
    TextLabel_XueYang_value->setFont(font3);
    TextLabel_XueYang_value->setLayoutDirection(Qt::RightToLeft);
    TextLabel_XueYang_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XueYang_value->setMidLineWidth(1);
    TextLabel_XueYang_value->setTextFormat(Qt::RichText);
    TextLabel_XueYang_value->setAlignment(Qt::AlignCenter);

   // SP Big Font Layout
    frame_sp->setAutoFillBackground(false);
    frame_sp->setStyleSheet(QString::fromUtf8("color:rgb(255, 165, 10);\n"
"border-color: rgb(255, 255, 255);\n"
"border-style:solid;\n"
"border-width:1px;"));
    frame_sp->setFrameShape(QFrame::StyledPanel);
    frame_sp->setFrameShadow(QFrame::Plain);
    TextLabel_HuXiLv_value->setGeometry(QRect(10, 40, 181, 71));
    QFont font11;
    font11.setPointSize(50);
    font11.setBold(false);
    font11.setWeight(50);
    TextLabel_HuXiLv_value->setFont(font11);
    TextLabel_HuXiLv_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLv_value->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLv->setGeometry(QRect(5, 5, 71, 30));
    TextLabel_HuXiLv->setFont(font2);
    TextLabel_HuXiLv->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLv->setFrameShape(QFrame::NoFrame);
    TextLabel_HuXiLv->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_value_XiRu->setGeometry(QRect(200, 50, 101, 41));
    QFont font12;
    font12.setPointSize(25);
    font12.setBold(true);
    font12.setWeight(75);
    TextLabel_HuXiLvCo2_Co2_value_XiRu->setFont(font12);
    TextLabel_HuXiLvCo2_Co2_value_XiRu->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2_value_XiRu->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_value_XiRu->setGeometry(QRect(170, 50, 111, 41));
    TextLabel_HuXiLvCo2_Co2->setFont(font2);
    TextLabel_HuXiLvCo2_Co2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_mmHg->setGeometry(QRect(370, 5, 50, 30));
    TextLabel_HuXiLvCo2_Co2_mmHg->setFont(font2);
    TextLabel_HuXiLvCo2_Co2_mmHg->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2_mmHg->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_value_HuMo->setGeometry(QRect(320, 50, 101, 41));
    TextLabel_HuXiLvCo2_Co2_value_HuMo->setFont(font12);
    TextLabel_HuXiLvCo2_Co2_value_HuMo->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2_value_HuMo->setAlignment(Qt::AlignCenter);
    TextLabel_HuXiLvCo2_Co2_value_XieXian->setGeometry(QRect(290, 54, 21, 31));
    QFont font13;
    font13.setPointSize(25);
    TextLabel_HuXiLvCo2_Co2_value_XieXian->setFont(font13);
    TextLabel_HuXiLvCo2_Co2_value_XieXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_HuXiLvCo2_Co2_value_XieXian->setAlignment(Qt::AlignCenter);

    // NIBP Big Font Layout
    frame_nibp->setGeometry(QRect(5, 480, 580, 240));
    QFont font14;
    font14.setPointSize(11);
    font14.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    frame_nibp->setFont(font14);
    frame_nibp->setAutoFillBackground(false);
    frame_nibp->setStyleSheet(QString::fromUtf8("color:rgb(0, 85, 255);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width:1px;\n"
"border-style:solid;\n"
"\n"
"\n"
""));
    frame_nibp->setFrameShape(QFrame::StyledPanel);
    frame_nibp->setFrameShadow(QFrame::Plain);
    TextLabel_WuChuangXueYa->setGeometry(QRect(5, 5, 95, 30));
    TextLabel_WuChuangXueYa->setFont(font4);
    TextLabel_WuChuangXueYa->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa->setAlignment(Qt::AlignCenter);
    label_nibp_unit->setGeometry(QRect(500, 5, 70, 25));
    label_nibp_unit->setFont(font4);
    label_nibp_unit->setStyleSheet(QString::fromUtf8("border-style:none;"));
    label_nibp_unit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    TextLabel_WuChuangXueYa_ShouDong->setGeometry(QRect(190, 10, 40, 15));
    TextLabel_WuChuangXueYa_ShouDong->setFont(font14);
    TextLabel_WuChuangXueYa_ShouDong->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_ShouDong->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_ZiDongJianGe->setGeometry(QRect(90, 20, 40, 10));
    QFont font15;
    font15.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font15.setPointSize(8);
    TextLabel_WuChuangXueYa_ZiDongJianGe->setFont(font15);
    TextLabel_WuChuangXueYa_ZiDongJianGe->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_ZiDongJianGe->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_value_Gao_2->setGeometry(QRect(70, 80, 150, 100));
    QFont font16;
    font16.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font16.setPointSize(70);
    font16.setBold(true);
    font16.setWeight(75);
    TextLabel_WuChuangXueYa_value_Gao_2->setFont(font16);
    TextLabel_WuChuangXueYa_value_Gao_2->setLayoutDirection(Qt::RightToLeft);
    TextLabel_WuChuangXueYa_value_Gao_2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_value_Gao_2->setMidLineWidth(1);
    TextLabel_WuChuangXueYa_value_Gao_2->setTextFormat(Qt::RichText);
    TextLabel_WuChuangXueYa_value_Gao_2->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_value_Pingjun->setGeometry(QRect(300, 80, 150, 100));
    TextLabel_WuChuangXueYa_value_Pingjun->setFont(font16);
    TextLabel_WuChuangXueYa_value_Pingjun->setLayoutDirection(Qt::RightToLeft);
    TextLabel_WuChuangXueYa_value_Pingjun->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_value_Pingjun->setMidLineWidth(1);
    TextLabel_WuChuangXueYa_value_Pingjun->setTextFormat(Qt::RichText);
    TextLabel_WuChuangXueYa_value_Pingjun->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_value_Di->setGeometry(QRect(458, 160, 111, 61));
    QFont font17;
    font17.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font17.setPointSize(40);
    font17.setBold(true);
    font17.setWeight(75);
    TextLabel_WuChuangXueYa_value_Di->setFont(font17);
    TextLabel_WuChuangXueYa_value_Di->setLayoutDirection(Qt::RightToLeft);
    TextLabel_WuChuangXueYa_value_Di->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_value_Di->setMidLineWidth(1);
    TextLabel_WuChuangXueYa_value_Di->setTextFormat(Qt::RichText);
    TextLabel_WuChuangXueYa_value_Di->setAlignment(Qt::AlignCenter);
    TextLabel_WuChuangXueYa_value_XieXian->setGeometry(QRect(220, 110, 71, 61));
    QFont font18;
    font18.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font18.setPointSize(50);
    TextLabel_WuChuangXueYa_value_XieXian->setFont(font18);
    TextLabel_WuChuangXueYa_value_XieXian->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_WuChuangXueYa_value_XieXian->setAlignment(Qt::AlignCenter);
    TextLabel_MaiLv_value->setParent(frame_nibp);
    TextLabel_MaiLv_value->show();
    TextLabel_MaiLv_value->setGeometry(QRect(340, 190, 50, 45));
    QFont font19;
    font19.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font19.setPointSize(18);
    TextLabel_MaiLv_value->setFont(font19);
    TextLabel_MaiLv_value->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_MaiLv_value->setAlignment(Qt::AlignCenter);
    TextLabel_XueYang_2->setParent(frame_nibp);
    TextLabel_XueYang_2->show();
    TextLabel_XueYang_2->setGeometry(QRect(290, 200, 51, 25));
    QFont font20;
    font20.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
    font20.setPointSize(15);
    TextLabel_XueYang_2->setFont(font20);
    TextLabel_XueYang_2->setStyleSheet(QString::fromUtf8("border-style:none;"));
    TextLabel_XueYang_2->setAlignment(Qt::AlignCenter);
}
