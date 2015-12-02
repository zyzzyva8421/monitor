#include "dlg_set_color.h"
#include "rsc_modu/color.h"
#include "rsc_modu/modu_ecg.h"
#include "rsc_modu/modu_eeg.h"
#include "mainform.h"


QColor g_Color[10] = {Qt::white,
                      Qt::green,
                      Qt::red,
                      Qt::blue, //蓝色
                      Qt::yellow, //黄色
                      QColor(239,155,160), //粉色
                      QColor(0,124,195), //天蓝色
                      QColor(255,97,0),  //橙色
                      QColor(255,0,255), //紫色
                      Qt::gray //灰色
                     };

QString g_ColorName[10] =
{
    "white",
    "green",
    "red",
    "blue",
    "yellow",
    "rgb(239, 155, 160)",
    "rgb(0, 124, 195)",
    "rgb(255, 97, 0)",
    "rgb(255, 0, 255)",
    "gray"
};

CDlgSetColor::CDlgSetColor(QWidget *parent,QWidget *pMain):QDialog(parent)
{
    pMainform = pMain;
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = parent;
    cmb[0] = m_cmbb_beat_rate;
    cmb[1] = m_cmbb_spo2;
    cmb[2] = m_cmbb_spire_rate;
    cmb[3] =  m_cmbb_temp;
    cmb[4] = m_cmbb_nibp;
    cmb[5] =  m_cmbb_mashen;
    cmb[6] =  m_cmbb_ibp1;
    cmb[7] =  m_cmbb_ibp2;
    cmb[8] = m_cmbb_co2;
    cmb[9] =  m_cmbb_wav_eeg;
    cmb[10] = m_cmbb_wav_ecg1;
    cmb[11] = m_cmbb_wav_ecg2;
    cmb[12] =  m_cmbb_wav_ecg3;
    cmb[13] =  m_cmbb_wav_ecg4;
    cmb[14] =  m_cmbb_wav_ecg5;
    cmb[15] =  m_cmbb_wav_ecg6;
    cmb[16] =  m_cmbb_wav_ecg7;
    cmb[17] =  m_cmbb_wav_pulse;
    cmb[18] =  m_cmbb_wav_spr;
    cmb[19] = m_cmbb_wav_ibp1;
    cmb[20] =  m_cmbb_wav_ibp2;
    cmb[21] =  m_cmbb_wav_co2;
    cmb[22] = m_cmbb_wav_mashen;
    //设置颜色项
    QStringList color;
     color << "白" << "绿" << "红" << "蓝"<< "黄"<< "粉"<< "天蓝"<< "橙"<< "紫"<< "灰";
    for(int i=0;i<DLG_SET_COMBOBOX_NUM;i++)
    {
        cmb[i]->addItems(color);
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    setTabOrder(cmb[DLG_SET_COMBOBOX_NUM-1],m_btn_ok);
    setTabOrder(m_btn_ok,m_btn_cancel);
    setTabOrder(m_btn_cancel,m_cmbb_beat_rate);
    cmb[0]->setFocus();

    {
        CEcgModuleCfg cfg;
        g_EcgModule->f_get_ecg_cfg(&cfg);
        //ecg wave color
        for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
        {
            cmb[i+10]->setCurrentIndex(cfg.m_wave_color[i]);
        }
        cmb[0]->setCurrentIndex(cfg.m_panel_color);
    }
    {
        CSpo2ModuleCfg cfg;
        g_EcgModule->f_get_spo2_cfg(&cfg);
        cmb[1]->setCurrentIndex(cfg.m_panel_color);
        cmb[17]->setCurrentIndex(cfg.m_wave_color);
    }
    {
        CNibpModuleCfg cfg;
        g_EcgModule->f_get_nibp_cfg(&cfg);
        cmb[4]->setCurrentIndex(cfg.m_panel_color);
    }
    {
        CTempModuleCfg cfg;
        g_EcgModule->f_get_temp_cfg(&cfg);
        cmb[3]->setCurrentIndex(cfg.m_panel_color);
    }
    {
        CSpireModuleCfg cfg;
        g_EcgModule->f_get_spire_cfg(&cfg);
        cmb[2]->setCurrentIndex(cfg.m_panel_color);
        cmb[18]->setCurrentIndex(cfg.m_wave_color);
    }
    {
        CEegModuleCfg cfg;
        g_EegModule->f_get_eeg_cfg(&cfg);
        cmb[9]->setCurrentIndex(cfg.m_wave_color[0]);
    }
    {
        stIBPModuCfg cfg;
        g_IBPModule1->f_get_cfg(&cfg);
        cmb[6]->setCurrentIndex(cfg.m_ibp1_panel_color);
        cmb[7]->setCurrentIndex(cfg.m_ibp2_panel_color);
        cmb[19]->setCurrentIndex(cfg.m_ibp1_wave_color);
        cmb[20]->setCurrentIndex(cfg.m_ibp2_wave_color);
    }
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
    connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
    connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
    connect(this,SIGNAL(signal_set_panels_color(QFrame* ,int )),pMainform,SLOT(slot_set_panels_color(QFrame* ,int )));
}

void CDlgSetColor::do_ok_clicked()
{
    CMainForm * p = (CMainForm *)pMainform;
    {
        bool bChangeFlg = false;
        CEcgModuleCfg cfg;
        g_EcgModule->f_get_ecg_cfg(&cfg);
        //ecg wave color
        for(int i=0;i<ECG_MODULE_WAVE_NUM;i++)
        {
            if(cmb[i+10]->currentIndex() != cfg.m_wave_color[i])
            {
                bChangeFlg = true;
                cfg.m_wave_color[i] = cmb[i+10]->currentIndex();
                g_EcgModule->f_set_ecg_wave_color(i,cfg.m_wave_color[i]); //read write file too much
            }

        }
        if(cmb[0]->currentIndex() != cfg.m_panel_color)
        {
            cfg.m_panel_color = cmb[0]->currentIndex();
            bChangeFlg = true;
            emit(signal_set_panels_color(p->frame_ECG ,cfg.m_panel_color ));

        }
        if(bChangeFlg == true)
        {
            g_EcgModule->f_set_ecg_cfg(cfg);
        }
    }
    {
        CSpo2ModuleCfg cfg;
        g_EcgModule->f_get_spo2_cfg(&cfg);
        if((cmb[1]->currentIndex() !=cfg.m_panel_color)
            ||(cmb[17]->currentIndex() != cfg.m_wave_color))
        {
            cfg.m_panel_color = cmb[1]->currentIndex();
            cfg.m_wave_color = cmb[17]->currentIndex() ;
            g_EcgModule->f_set_spo2_wave_color(cfg.m_wave_color);
            emit(signal_set_panels_color(p->frame_spo2 ,cfg.m_panel_color ));
            g_EcgModule->f_set_spo2_cfg(cfg);

        }
    }
    {
        CNibpModuleCfg cfg;
        g_EcgModule->f_get_nibp_cfg(&cfg);
        if(cmb[4]->currentIndex() != cfg.m_panel_color)
        {
             cfg.m_panel_color = cmb[4]->currentIndex();
             emit(signal_set_panels_color(p->frame_nibp ,cfg.m_panel_color ));
            g_EcgModule->f_set_nibp_cfg(cfg);
        }

    }
    {
        CTempModuleCfg cfg;
        g_EcgModule->f_get_temp_cfg(&cfg);
        if(cmb[3]->currentIndex() != cfg.m_panel_color)
        {
            cfg.m_panel_color = cmb[3]->currentIndex();
            emit(signal_set_panels_color(p->frame_temp ,cfg.m_panel_color ));
            g_EcgModule->f_set_temp_cfg(cfg);
        }
    }
    {
        CSpireModuleCfg cfg;
        g_EcgModule->f_get_spire_cfg(&cfg);
        if((cmb[2]->currentIndex() !=cfg.m_panel_color)||
        (cmb[18]->currentIndex() !=cfg.m_wave_color))
        {
            cfg.m_panel_color = cmb[2]->currentIndex();
            cfg.m_wave_color = cmb[18]->currentIndex();
            emit(signal_set_panels_color(p->frame_sp ,cfg.m_panel_color ));
            g_EcgModule->f_set_spire_wave_color(cfg.m_wave_color);
            g_EcgModule->f_set_spire_cfg(cfg);
        }
    }
    {
        CEegModuleCfg cfg;
        g_EegModule->f_get_eeg_cfg(&cfg);
        for(int i=0;i<EEG_MODULE_WAVE_NUM;i++)
        {
            cfg.m_wave_color[i] = cmb[9]->currentIndex();
        }
        g_EegModule->f_set_eeg_cfg(cfg);
        g_EegModule->f_set_eeg_wave_color();
    }
    {
        stAnaesDepModuCfg cfg;
        g_AnaesModule->f_get_cfg(&cfg);
        cfg.m_panel_color = cmb[5]->currentIndex();
        cfg.m_wave_color = cmb[22]->currentIndex();
        g_AnaesModule->f_set_cfg(cfg);
        emit(signal_set_panels_color(p->frame_mashen ,cfg.m_panel_color ));
    }
    {
        stIBPModuCfg cfg;
        g_IBPModule1->f_get_cfg(&cfg);
        cfg.m_ibp1_panel_color = cmb[6]->currentIndex();
        cfg.m_ibp2_panel_color = cmb[7]->currentIndex();
        cfg.m_ibp1_wave_color = cmb[19]->currentIndex();
        cfg.m_ibp2_wave_color = cmb[20]->currentIndex();
        g_IBPModule1->f_set_cfg(cfg);
        emit(signal_set_panels_color(p->frame_ibp1,cfg.m_ibp1_panel_color));
        emit(signal_set_panels_color(p->frame_ibp2,cfg.m_ibp2_panel_color));
        g_IBPModule1->f_set_wave_color();
    }
    {
        stCO2ModuCfg cfg;
        g_CO2Module->f_get_cfg(&cfg);
        cfg.m_panel_color = cmb[8]->currentIndex();
        cfg.m_wave_color = cmb[21]->currentIndex();
        g_CO2Module->f_set_cfg(cfg);
        g_CO2Module->f_set_wave_layout();
        //emit(signal_set_panels_color(p->frame_co2 ,cfg.m_panel_color ));
    }
    close();
}
void CDlgSetColor::do_cancel_clicked()
{

    close();
}
bool CDlgSetColor::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_beat_rate
        ,m_cmbb_spo2
        ,m_cmbb_spire_rate
        ,m_cmbb_temp
        ,m_cmbb_nibp
        ,m_cmbb_mashen
        ,m_cmbb_ibp1
        ,m_cmbb_ibp2
        ,m_cmbb_co2
        ,m_cmbb_wav_eeg
        ,m_cmbb_wav_ecg1
        ,m_cmbb_wav_ecg2
        ,m_cmbb_wav_ecg3
        ,m_cmbb_wav_ecg4
        ,m_cmbb_wav_ecg5
        ,m_cmbb_wav_ecg6
        ,m_cmbb_wav_ecg7
        ,m_cmbb_wav_pulse
        ,m_cmbb_wav_spr
        ,m_cmbb_wav_ibp1
        ,m_cmbb_wav_ibp2
        ,m_cmbb_wav_co2
        ,m_cmbb_wav_mashen
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  25;//
    int iOkPos = iTotalObj -2;
    int iCancelPos = iTotalObj -1;
    if(e->type() == QEvent::KeyPress)
    {

        QKeyEvent *event=(QKeyEvent *)e;
        switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_Left:
            if(bCursorSta == false)
            {
                if(iCursor == 0)
                {
                    iCursor = iTotalObj-1;
                }
                else
                {
                    iCursor -=1;
                }
                if((iCursor>=0) &&(iCursor<iOkPos))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setFocus();
                }
                else
                {
                    QPushButton *p = (QPushButton *)obj[iCursor];
                    p->setFocus();
                }

            }
            else
            {/*

                if((iCursor >= 7)&&(iCursor <=10))
                {
                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    if(p->value()!= p->minimum())
                    {
                        p->setValue(p->value()-1);
                    }
                    else
                    {
                        p->setValue(p->maximum());
                    }

                }*/
            }

            return true;
            break;
        case Qt::Key_Down:
        case Qt::Key_Right:
            if(bCursorSta == false)
            {
                if(iCursor == iTotalObj-1)
                {
                    iCursor = 0;
                }
                else
                {
                    iCursor +=1;
                }
                if((iCursor>=0) &&(iCursor<iOkPos))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setFocus();
                }

                else
                {
                    QPushButton *p = (QPushButton *)obj[iCursor];
                    p->setFocus();
                }

            }
            else
            {/*
                if((iCursor >= 7)&&(iCursor <=10))
                {
                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    if(p->value()!= p->maximum())
                    {
                        p->setValue(p->value()+1);
                    }
                    else
                    {
                        p->setValue(p->minimum());
                    }

                }*/

            }
            return true;
            break;
        case Qt::Key_Return:
            if(bCursorSta == false)
            {
                if(iCursor == iOkPos)
                {
                    do_ok_clicked();
                }
                else if(iCursor == iCancelPos)
                {
                    do_cancel_clicked();
                }
                else if((iCursor>=0) &&(iCursor<iOkPos))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }


            }
            else
            {/*
                bCursorSta = false;
                if((iCursor >= 7)&&(iCursor <=10))
                {

                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    //p->setStyleSheet("background-color: rgb(255, 255, 255);");;
                }
                //obj[iCursor]->setStyleSheet("background-color: rgb(255, 255, 255);");
*/
            }
            return true;
            break;
        default:
            CMainForm *p = (CMainForm *)pMainForm;
            p->f_process_key(event->key());
            return true;
            break;

        }
    }
    else
    {
        return false;
    }
}
