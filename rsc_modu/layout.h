#ifndef LAYOUT
#define LAYOUT


#include <QtCore>
#include <QFrame>

#define LAYOUT_CFG_STANDER 0
#define LAYOUT_CFG_BIG_FONT 1
#define LAYOUT_CFG_SPIRE_SPO2 2
#define LAYOUT_CFG_NIBP 3
#define LAYOUT_CFG_TREND_TABLE 4
#define LAYOUT_CFG_ALL_LEAD 5
#define LAYOUT_CFG_MASHEN 6
#define LAYOUT_CFG_DOC "/home/data/config/layout.dat"

typedef struct CLayoutCfg_
{
    int m_layout_type;
    int m_layout_trend_interval;
    int m_layout_mashen_sens;
}CLayoutCfg;


class CLayoutModule:public QObject
{
public:
    CLayoutModule(QWidget *parent);
    CLayoutCfg *m_layout_cfg;
private:
    QWidget *pMainForm;

public:
    void f_layout_get_config(CLayoutCfg *cfg);
    void f_layout_set_config(CLayoutCfg cfg);
    void f_layout_set_def_config();

private:
    void f_set_wave_layout();
    void f_layout_hint(CLayoutCfg cfg);
    void f_set_stand_layout();
    void f_set_bigfont_layout();
    void f_set_spirspo_layout();
    void f_set_nibpreview_layout();
    void f_set_trendtable_layout();
    void f_set_mashen_layout();
    void f_set_ecg_all_lead();

};

#endif // LAYOUT

