#include "dlg_set_color.h"

#define DLG_SET_COMBOBOX_NUM 24

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


CDlgSetColor::CDlgSetColor(QWidget *parent):QDialog(parent)
{
    setupUi(this);
    QComboBox *cmb[DLG_SET_COMBOBOX_NUM];
    cmb[0] = m_cmbb_beat_rate;
    cmb[1] = m_cmbb_beat_rate;
    cmb[2] = m_cmbb_spo2;
   cmb[3] = m_cmbb_spire_rate;
   cmb[4] =  m_cmbb_temp;
    cmb[5] = m_cmbb_nibp;
   cmb[6] =  m_cmbb_mashen;
   cmb[7] =  m_cmbb_ibp1;
   cmb[8] =  m_cmbb_ibp2;
    cmb[9] = m_cmbb_co2;
   cmb[10] =  m_cmbb_wav_eeg;
    cmb[11] = m_cmbb_wav_ecg1;
    cmb[12] = m_cmbb_wav_ecg2;
   cmb[13] =  m_cmbb_wav_ecg3;
   cmb[14] =  m_cmbb_wav_ecg4;
   cmb[15] =  m_cmbb_wav_ecg5;
   cmb[16] =  m_cmbb_wav_ecg6;
   cmb[17] =  m_cmbb_wav_ecg7;
   cmb[18] =  m_cmbb_wav_pulse;
   cmb[19] =  m_cmbb_wav_spr;
    cmb[20] = m_cmbb_wav_ibp1;
   cmb[21] =  m_cmbb_wav_ibp2;
   cmb[22] =  m_cmbb_wav_co2;
    cmb[23] = m_cmbb_wav_mashen;
    //设置颜色项
    QStringList color;
     color << "白" << "绿" << "红" << "蓝"<< "黄"<< "粉"<< "天蓝"<< "橙"<< "紫"<< "灰";
    for(int i=0;i<DLG_SET_COMBOBOX_NUM;i++)
    {
        cmb[i]->addItems(color);
        //设置光标顺序
        if(i == (DLG_SET_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    setTabOrder(cmb[DLG_SET_COMBOBOX_NUM-1],m_btn_ok);
    setTabOrder(m_btn_ok,m_btn_cancel);
    setTabOrder(m_btn_cancel,m_cmbb_beat_rate);
    cmb[0]->setFocus();

    connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
    connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));

}

void CDlgSetColor::do_ok_clicked()
{

}
void CDlgSetColor::do_cancel_clicked()
{

}
