#include "dlg_serv_usr.h"
#include "rsc_modu/modu_net.h"
#include "mainform.h"
#include "rsc_modu/modu_ecg.h"
#include <QNetworkInterface>
#define DLG_SERV_USR_COMBOBOX_NUM 1
#define DLG_SERV_USR_SPB_NUM 24
CDlgServUsrCfg::CDlgServUsrCfg(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SERV_USR_COMBOBOX_NUM];
    cmb[0] = m_cmbb_record;
    QSpinBox *spb[DLG_SERV_USR_SPB_NUM];
    spb[0] =m_spb_ip1;
    spb[1] =m_spb_ip2;
    spb[2] =m_spb_ip3;
    spb[3] =m_spb_ip4;
    spb[4] =m_spb_gate1;
    spb[5] =m_spb_gate2;
    spb[6] =m_spb_gate3;
    spb[7] =m_spb_gate4;
    spb[8] =m_spb_serv1_1;
    spb[9] =m_spb_serv1_2;
    spb[10] =m_spb_serv1_3;
    spb[11] =m_spb_serv1_4;
    spb[12] =m_spb_serv2_1;
    spb[13] =m_spb_serv2_2;
    spb[14] =m_spb_serv2_3;
    spb[15] =m_spb_serv2_4;
    spb[16] =m_spb_serv3_1;
    spb[17] =m_spb_serv3_2;
    spb[18] =m_spb_serv3_3;
    spb[19] =m_spb_serv3_4;
    spb[20] =m_spb_net_num;
    spb[21] =m_spb_spo_correct;
    spb[22] =m_spb_nibp_correct;
    spb[23] =m_spb_ecg_ampli;

    //增加选择项
     QStringList items;
     items<<"关"<<"开";
    cmb[0]->addItems(items);

    for(int i=0; i<DLG_SERV_USR_SPB_NUM; i++)
     {
        spb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SERV_USR_SPB_NUM-1))
            break;
        setTabOrder(spb[i],spb[i+1]);
    }
    setTabOrder(spb[DLG_SERV_USR_SPB_NUM-1],m_spb_temp_correct);
    setTabOrder(m_spb_temp_correct,cmb[0]);
    for(int i=0;i< DLG_SERV_USR_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SERV_USR_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    m_spb_temp_correct->installEventFilter(this);
    setTabOrder(cmb[DLG_SERV_USR_COMBOBOX_NUM-1],m_btn_ok);
    setTabOrder(m_btn_ok,m_btn_cancel);
    setTabOrder(m_btn_cancel,spb[0]);
    spb[0]->setFocus();


    {
      QList<QHostAddress> AddressList = QNetworkInterface::allAddresses();
      QHostAddress result;
      foreach(QHostAddress address, AddressList){
          if(address.protocol() == QAbstractSocket::IPv4Protocol &&
             address != QHostAddress::Null &&
             address != QHostAddress::LocalHost){
              if (address.toString().contains("127.0.")){
                continue;
              }
              result = address;
              break;
          }
      }
      if(!result.isNull())
      {
          int ip = result.toIPv4Address();
          m_spb_ip1->setValue((ip&0xff000000)>>24);
          m_spb_ip2->setValue((ip&0xff0000)>>16);
          m_spb_ip3->setValue((ip&0xff00)>>8);
          m_spb_ip4->setValue((ip&0xff));
      }
    }
    f_set_display();
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
     connect(this,SIGNAL(signal_net_changed(int)),g_NetThread,SLOT(slot_net_changed(int)),Qt::QueuedConnection);
}
void CDlgServUsrCfg::do_ok_clicked()
{
    stNetModuleCfg cfg;
    //g_NetModule->f_get_cfg(&cfg);
    memcpy(&cfg,g_NetModule->m_modu_cfg,sizeof(stNetModuleCfg));
    int changeflg = 0;
    if((cfg.m_ip_0 != m_spb_ip1->value())
        ||(cfg.m_ip_1 !=m_spb_ip2->value())
            ||(cfg.m_ip_2!=m_spb_ip3->value())
            ||cfg.m_ip_3!=m_spb_ip4->value()
            )
    {
        changeflg |= 0x07;
    }
    cfg.m_ip_0 = m_spb_ip1->value();
    cfg.m_ip_1=m_spb_ip2->value();
    cfg.m_ip_2=m_spb_ip3->value();
    cfg.m_ip_3=m_spb_ip4->value();
    if(    (cfg.m_gate_0 !=m_spb_gate1->value())||
           (cfg.m_gate_1 !=m_spb_gate2->value())||
           (cfg.m_gate_2 !=m_spb_gate3->value())||
           (cfg.m_gate_3 !=m_spb_gate4->value()))
    {
        changeflg |= 0x07;
    }
    cfg.m_gate_0=m_spb_gate1->value();
    cfg.m_gate_1=m_spb_gate2->value();
    cfg.m_gate_2=m_spb_gate3->value();
    cfg.m_gate_3=m_spb_gate4->value();
    if(    (cfg.m_serv1_0!=m_spb_serv1_1->value())||
           (cfg.m_serv1_1!=m_spb_serv1_2->value())||
           (cfg.m_serv1_2!=m_spb_serv1_3->value())||
           (cfg.m_serv1_3!=m_spb_serv1_4->value()))
    {
        changeflg |= 0x01;
    }
    cfg.m_serv1_0=m_spb_serv1_1->value();
    cfg.m_serv1_1=m_spb_serv1_2->value();
    cfg.m_serv1_2=m_spb_serv1_3->value();
    cfg.m_serv1_3=m_spb_serv1_4->value();
    if(    (cfg.m_serv2_0!=m_spb_serv2_1->value())||
           (cfg.m_serv2_1!=m_spb_serv2_2->value())||
           (cfg.m_serv2_2!=m_spb_serv2_3->value())||
           (cfg.m_serv2_3!=m_spb_serv2_4->value()))
    {
        changeflg |= 0x02;
    }
    cfg.m_serv2_0=m_spb_serv2_1->value();
    cfg.m_serv2_1=m_spb_serv2_2->value();
    cfg.m_serv2_2=m_spb_serv2_3->value();
    cfg.m_serv2_3=m_spb_serv2_4->value();
    if((cfg.m_serv3_0!=m_spb_serv3_1->value())||
            (cfg.m_serv3_1!=m_spb_serv3_2->value())||
            (cfg.m_serv3_2!=m_spb_serv3_3->value())||
            (cfg.m_serv3_3!=m_spb_serv3_4->value()))
    {
        changeflg |= 0x04;
    }
    cfg.m_serv3_0=m_spb_serv3_1->value();
    cfg.m_serv3_1=m_spb_serv3_2->value();
    cfg.m_serv3_2=m_spb_serv3_3->value();
    cfg.m_serv3_3=m_spb_serv3_4->value();
    cfg.m_net_num=m_spb_net_num->value();
    cfg.m_port1_num = 510+cfg.m_ip_3;
    cfg.m_port2_num = 510+cfg.m_ip_3;
    cfg.m_port3_num = 510+cfg.m_ip_3;
    emit signal_net_changed(changeflg);
    g_NetModule->f_set_cfg(cfg);
    CEcgModuleCfg ecfg;
    g_EcgModule->f_get_ecg_cfg(&ecfg);
    ecfg.m_ecg_amp_usrcfg=m_spb_ecg_ampli->value();
    g_EcgModule->f_set_ecg_cfg(ecfg);
    CNibpModuleCfg ncfg;
    g_EcgModule->f_get_nibp_cfg(&ncfg);
    ncfg.m_nibp_correct=m_spb_nibp_correct->value();
    g_EcgModule->f_set_nibp_cfg(ncfg);
    CSpo2ModuleCfg scfg;
    g_EcgModule->f_get_spo2_cfg(&scfg);
    scfg.m_spo2_correct=m_spb_spo_correct->value();
    g_EcgModule->f_set_spo2_cfg(scfg);
    close();
}
void CDlgServUsrCfg::do_cancel_clicked()
{
    close();
}
void CDlgServUsrCfg::f_set_display()
{
    stNetModuleCfg cfg;
    //g_NetModule->f_get_cfg(&cfg);
    memcpy(&cfg,g_NetModule->m_modu_cfg,sizeof(stNetModuleCfg));
    //m_spb_ip1->setValue(cfg.m_ip_0);
    //m_spb_ip2->setValue(cfg.m_ip_1);
    //m_spb_ip3->setValue(cfg.m_ip_2);
    //m_spb_ip4->setValue(cfg.m_ip_3);
    m_spb_gate1->setValue(cfg.m_gate_0);
    m_spb_gate2->setValue(cfg.m_gate_1);
    m_spb_gate3->setValue(cfg.m_gate_2);
    m_spb_gate4->setValue(cfg.m_gate_3);
    m_spb_serv1_1->setValue(cfg.m_serv1_0);
    m_spb_serv1_2->setValue(cfg.m_serv1_1);
    m_spb_serv1_3->setValue(cfg.m_serv1_2);
    m_spb_serv1_4->setValue(cfg.m_serv1_3);
    m_spb_serv2_1->setValue(cfg.m_serv2_0);
    m_spb_serv2_2->setValue(cfg.m_serv2_1);
    m_spb_serv2_3->setValue(cfg.m_serv2_2);
    m_spb_serv2_4->setValue(cfg.m_serv2_3);
    m_spb_serv3_1->setValue(cfg.m_serv3_0);
    m_spb_serv3_2->setValue(cfg.m_serv3_1);
    m_spb_serv3_3->setValue(cfg.m_serv3_2);
    m_spb_serv3_4->setValue(cfg.m_serv3_3);
    m_spb_net_num->setValue(cfg.m_net_num);
    CEcgModuleCfg ecfg;
    g_EcgModule->f_get_ecg_cfg(&ecfg);
    m_spb_ecg_ampli->setValue(ecfg.m_ecg_amp_usrcfg);
    CNibpModuleCfg ncfg;
    g_EcgModule->f_get_nibp_cfg(&ncfg);
    m_spb_nibp_correct->setValue(ncfg.m_nibp_correct);
    CSpo2ModuleCfg scfg;
    g_EcgModule->f_get_spo2_cfg(&scfg);
    m_spb_spo_correct->setValue(scfg.m_spo2_correct);
}
bool CDlgServUsrCfg::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={

         m_spb_ip1
        ,m_spb_ip2
        ,m_spb_ip3
        ,m_spb_ip4
        ,m_spb_gate1
        ,m_spb_gate2
        ,m_spb_gate3
        ,m_spb_gate4
        ,m_spb_serv1_1
        ,m_spb_serv1_2
        ,m_spb_serv1_3
        ,m_spb_serv1_4
        ,m_spb_serv2_1
        ,m_spb_serv2_2
        ,m_spb_serv2_3
        ,m_spb_serv2_4
        ,m_spb_serv3_1
        ,m_spb_serv3_2
        ,m_spb_serv3_3
        ,m_spb_serv3_4
        ,m_spb_net_num
        ,m_spb_spo_correct
        ,m_spb_nibp_correct
        ,m_spb_ecg_ampli
        ,m_spb_temp_correct
        ,m_cmbb_record
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  28;//11
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
            {

                if((iCursor >= 0)&&(iCursor <iOkPos-1))
                {
                    if(iCursor == iOkPos-2)
                    {
                        QDoubleSpinBox *p = (QDoubleSpinBox *)(QSpinBox *)obj[iCursor];
                        if(p->value()!= p->minimum())
                        {
                            p->setValue(p->value()-1);
                        }
                        else
                        {
                            p->setValue(p->maximum());
                        }
                    }
                    else
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
                    }


                }

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
                if((iCursor>=0) &&(iCursor<(iOkPos)))
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
            {
                if((iCursor >= 0)&&(iCursor <iOkPos-1))
                {
                    if(iCursor == iOkPos -2)
                    {
                        QDoubleSpinBox *p = (QDoubleSpinBox *)obj[iCursor];
                        if(p->value()!= p->maximum())
                        {
                            p->setValue(p->value()+1);
                        }
                        else
                        {
                            p->setValue(p->minimum());
                        }
                    }
                    else
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
                    }


                }

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

                else if((iCursor== iOkPos-1))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }
                else if((iCursor>=0) &&(iCursor<iOkPos))
                {
                    bCursorSta = true;
                    QSpinBox *p = (QSpinBox *)obj[iCursor];

                }


            }
            else
            {
                bCursorSta = false;
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
