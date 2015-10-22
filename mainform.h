#ifndef MAINFORM_H
#define MAINFORM_H


#include "ui_mainform.h"


#include "rsc_modu/layout.h"
#include "rsc_modu/color.h"
#include "rsc_modu/modu_ibp.h"
#include "rsc_modu/modu_anaes.h"
#include "rsc_modu/modu_net.h"
#include "rsc_modu/modu_netthread.h"
#include "rsc_modu/modu_eeg.h"
#include "rsc_modu/modu_database.h"
#include "rsc_modu/modu_co2.h"
#include "rsc_modu/modu_ecg.h"
#include "rsc_modu/modu_play.h"

class CEegModule;
class CEcgModule;
class CLayoutModule;
class CCO2Modu;
class CIBPModu;
class CAnaesDepModu;
class CNetModule;
class CNetThread;
class CDatabaseModule;
class CDrawThread ;
class CGPIOMODU;
typedef QVector<QPointF> stWavedata;

#define WAVE_WIDGET_WIDTH_PIX 730
#define WAVE_WIDGET_ALL_HEIGHT_PIX 696
#define WAVE_WIDGET_WIDTH_LEN 220
#define WAVE_WIDGET_HEIGHT_PIX 50
#define STATUS_BAR_WIDGET_HEIGHT 32
class CMainForm :	public QWidget,public Ui_MonitorForm
{
    Q_OBJECT
public:
    CMainForm(QWidget* = 0,Qt::WindowFlags f = 0 );
    ~CMainForm();
private:
    /*******串口定义*******/
#define BaudRate115200    19

#define BaudRate57600    17

#define BaudRate19200     14

#define UART_PORTS_TOTAL 5
#define INVALID_PORT_NO 0xff
    //各参数板对应的串口队列中的位置，初始化为0xff
    char m_Port_Num_FY0803;
    char m_Port_Num_EEG;
    char m_Port_Num_CO2;
    char m_Port_Num_AnaesDep;

 ///////////////////////////////////////////////////// 生理参数/////////////////////////////////////
    //过量值
#define over 999

    QTimer *m_time_read_com,*m_time_draw/*,*time_Tcp*/;
signals:
    void signal_btn_clicked(QPushButton *);
private slots:
            void slot_btn_manage_clicked(void);
            void slot_btn_record_clicked();
            void slot_btn_set_clicked();
            void slot_btn_alarm_clicked();
            void slot_btn_serve_clicked();
            void slot_para_ecg_value_changed(stEcgValue val);
            void slot_para_spo2_value_changed(stSpo2Value val);
            void slot_para_nibp_value_changed(stNibpValue val);
            void slot_para_temp_value_changed(stTempValue val);
            void slot_para_spire_value_changed(stSpireValue val);
            void slot_time_to_draw_wave();
            void slot_set_panels_color(QFrame *qf,int color);
            void slot_paint_spo_wave(stWavedata,double dfPos);
            void slot_setpanels_value(QLabel *p,double value,int prcs);
            void slot_setpanels_value(QLabel *,int value);
            void slot_setpanels_value(QLabel *, QString);
            void slot_setpanel_pixmap(QLabel *,int);
            void slot_set_connection_pmp(bool);
            void slot_btn_clicked(QPushButton *);
            void slot_key_pressed(int);
public:
        void f_set_all_panels_color();
        bool f_process_key(int key);
protected:
        bool eventFilter(QObject *o,QEvent *e);
        void keyPressEvent(QKeyEvent *e);
private:
        bool m_freeze_flg;
        int iCursor;
        bool bCursorSta;
};


extern CEcgModule * g_EcgModule;
extern CLayoutModule *g_LayoutModule;
extern CIBPModu * g_IBPModule1;
extern CIBPModu * g_IBPModule2;
extern CAnaesDepModu *g_AnaesModule;
extern CNetThread *g_NetThread;
extern CNetModule *g_NetModule;
extern CEegModule *g_EegModule;
extern CDatabaseModule *g_DatabaseModule;
extern CCO2Modu *g_CO2Module;
extern WavePlotter *g_WavePlotter;
extern CPlayThread *g_PlayThread;
extern CDrawThread *g_drawThread;
extern CGPIOMODU *g_gpioModu;
#endif // MAINFORM_H
