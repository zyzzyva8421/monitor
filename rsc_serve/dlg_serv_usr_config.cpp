#include "dlg_set_time.h"

#define DLG_SET_TIME_COMBOBOX_NUM 3

CDlgSetTime::CDlgSetTime(QWidget * parent):QDialog(parent)
{
    setupUi(this);
    QComboBox *cmb[DLG_SET_TIME_COMBOBOX_NUM];
   /* cmb[0] = m_cmbb_volume;
    cmb[1] =m_cmbb_pause_interval;
    cmb[2] =m_cmbb_corusecate;
    cmb[3] =m_cmbb_para_alarm;
    cmb[4] =m_cmbb_alarm_record;
    cmb[5] =m_cmbb_alarm_voice;
*/
    //增加选择项
     QStringList items;
     items<<"0"<<"1"<<"2"<<"3";
    cmb[0]->addItems(items);

    for(int i=0;i< DLG_SET_TIME_COMBOBOX_NUM;i++)
    {
        //设置光标顺序
        if(i == (DLG_SET_TIME_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
     setTabOrder(cmb[DLG_SET_TIME_COMBOBOX_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);

     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked),this,SLOT(do_cancel_clicked()));
}
void CDlgSetTime::do_ok_clicked()
{

}
void CDlgSetTime::do_cancel_clicked()
{

}

