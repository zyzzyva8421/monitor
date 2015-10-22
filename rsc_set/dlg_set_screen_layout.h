#ifndef DLG_SET_SCREEN_LAYOUT_H
#define DLG_SET_SCREEN_LAYOUT_H

#include "ui_set_pingmubuju_dlg.h"
#include "rsc_modu/modu_ecg.h"
#include "rsc_modu/layout.h"
#include "rsc_modu/color.h"
#include "rsc_modu/modu_ibp.h"
#include "rsc_modu/modu_anaes.h"
#include "rsc_modu/modu_net.h"
#include "rsc_modu/modu_netthread.h"
#include "rsc_modu/modu_eeg.h"
#include "rsc_modu/modu_database.h"
#include "rsc_modu/modu_co2.h"

#define DLG_SET_LAYOUT_COMBOBOX_NUM 2
#define DLG_SET_LAYOUT_CKB_NUM 23
class CDlgSetScreenLayout:public QDialog, public Ui_Dlg_set_pingmubuju
{
    Q_OBJECT
      public:
    CDlgSetScreenLayout(QWidget *parent,QWidget *pMain);
    QWidget * pMainForm;
private slots:
    void do_ok_clicked();
    void do_cancel_clicked();
    void do_layout_reset(int);
private:
    int iCursor;
    bool bCursorSta;
    bool eventFilter(QObject *o,QEvent *e);
private:
    QCheckBox * ckb[DLG_SET_LAYOUT_CKB_NUM];
    CEcgModuleCfg            m_ecg_cfg;
    CEegModuleCfg            m_eeg_cfg;
    stIBPModuCfg              m_ibp_cfg;
    stAnaesDepModuCfg   m_anaes_cfg;
    stCO2ModuCfg             m_co2_cfg;
    CTempModuleCfg         m_temp_cfg;
    CNibpModuleCfg          m_nibp_cfg;
    CSpireModuleCfg         m_spire_cfg;
    CSpo2ModuleCfg          m_spo2_cfg;

    void f_set_stand_layout();
    void f_set_bigfont_layout();
    void f_set_spirspo_layout();
    void f_set_nibpreview_layout();
    void f_set_trendtable_layout();
    void f_set_mashen_layout();
    void f_set_ecg_all_lead();

    void f_get_panel_beatrate();
    void f_get_panel_spo2();
    void f_get_panel_breathrate();
    void f_get_panel_nibp();
    void f_get_panel_temp();
    void f_get_panel_co2();
    void f_get_panel_anaes();
    void f_get_panel_ibp();

    void f_get_wave_eeg();
    void f_get_wave_ecg();
    void f_get_wave_spo2();
    void f_get_wave_spire();
    void f_get_wave_co2();
    void f_get_wave_anaes();
    void f_get_wave_ibp();
};


#endif // DLG_SET_SCREEN_LAYOUT_H
