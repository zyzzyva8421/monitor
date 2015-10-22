#include "modu_record.h"

CRecordModu::CRecordModu(QWidget *parent)
{
    pMainForm = parent;
    m_modu_cfg = new stRecordCfg;
    f_setDefaultCfg();
    //get  file config
    {
        QFile file((RECORD_MODULE_CFG_DOC));
        if(file.open(QIODevice::ReadOnly))
        {
            stRecordCfg tempCfg;
            QDataStream inout(&file);
            int magic;
            inout >> magic;
            if(magic == 0x12345678)
            {
                inout.readRawData((char *)&tempCfg,sizeof(stRecordCfg));
            }
            memcpy(m_modu_cfg,&tempCfg,sizeof(stRecordCfg));
            file.close();
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            QDataStream inout(&file);
            int magic = 0x12345678;
            inout<<magic;
            inout.writeRawData((char *)m_modu_cfg,sizeof(stRecordCfg));
            file.close();
        }
    }
}
void CRecordModu::f_get_cfg(stRecordCfg *cfg)
{
    memcpy(cfg,m_modu_cfg,sizeof(stRecordCfg));

}

void CRecordModu::f_set_cfg(stRecordCfg cfg)
{
    memcpy(m_modu_cfg,&cfg,sizeof(stRecordCfg));
    QFile file(RECORD_MODULE_CFG_DOC);
    file.open(QIODevice::WriteOnly);
    QDataStream inout(&file);
    int magic = 0x12345678;
    inout<<magic;
    inout.writeRawData((char *)m_modu_cfg,sizeof(stRecordCfg));
    file.close();
}

void CRecordModu::f_set_def_cfg()
{
    f_setDefaultCfg();
    f_set_cfg(*m_modu_cfg);
}

void CRecordModu::f_setDefaultCfg()
{
    m_modu_cfg->m_wave_name[0] = 0;
    m_modu_cfg->m_wave_name[1] = 0;
    m_modu_cfg->m_wave_name[2] = 0;
    m_modu_cfg->m_grid_en = 1;
    m_modu_cfg->m_length = 0;
    m_modu_cfg->m_interval = 0;
    m_modu_cfg->m_speed = 1;
}
