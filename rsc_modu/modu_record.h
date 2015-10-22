#ifndef MODU_RECORD
#define MODU_RECORD
#include <QtCore>
#define RECORD_MODULE_CFG_DOC "/home/data/config"
typedef struct stRecordCfg_{
    int m_wave_name[3];
    int m_grid_en;
    int m_length;
    int m_interval;
    int m_speed;
}stRecordCfg;
class CRecordModu:public QObject
{
public:
    CRecordModu(QWidget *parent);
    QWidget *pMainForm;
    stRecordCfg *m_modu_cfg;
    void f_get_cfg(stRecordCfg *cfg);
    void f_set_cfg(stRecordCfg cfg);
    void f_set_def_cfg();
    void f_setDefaultCfg();
};

#endif // MODU_RECORD

