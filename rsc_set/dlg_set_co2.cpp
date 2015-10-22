#include "dlg_set_co2.h"
#include "mainform.h"
#define DLG_SET_CO2_COMBOBOX_NUM 7
#define DLG_SET_CO2_SPB_NUM 4
CDlgSetCO2::CDlgSetCO2(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    QComboBox *cmb[DLG_SET_CO2_COMBOBOX_NUM];
    cmb[0] = m_cmbb_model;
    cmb[1] =m_cmbb_alarm;
    cmb[2] =m_cmbb_ampli;
    cmb[3] =m_cmbb_speed;
    cmb[4] =m_cmbb_unit;
    cmb[5] =m_cmbb_gas;
    cmb[6] =m_cmbb_wave_model;

    QDoubleSpinBox * spb[DLG_SET_CO2_SPB_NUM];
    spb[0] = m_spb_o2;
    spb[1] = m_spb_mazuiji;
    spb[2] = m_spb_wendubuchang;
    spb[3] = m_spb_daqiyali;

    //增加选择项
     QStringList items;

     items<<"待命"<<"运行";
    cmb[0]->addItems(items);
    items.clear();
    items<<"关"<<"10s"<<"15s"<<"20s"<<"30s"<<"35s"<<"40s";
    cmb[1]->addItems(items);
    items.clear();
    items<<"4.0kPa"<<"5.3kPa"<<"6.7kPa"<<"8.0kPa"<<"9.3kPa"<<
           "10.7kPa"<<"12.0kPa"<<"13.3kPa"<<"14.7kPa"<<"16.0kPa"<<
           "17.3kPa"<<"18.7kPa"<<"20.0kPa";
    cmb[2]->addItems(items);
   items.clear();
   items<<"6.25mm/s"<<"12.5"<<"25";
    cmb[3]->addItems(items);
   items.clear();
   items<<"mmHg"<<"kPa"<<"%";
    cmb[4]->addItems(items);
   items.clear();
   items<<"空气"<<"N2O"<<"氦气";
    cmb[5]->addItems(items);
    items.clear();
    items<<"线条"<<"填充";
    cmb[6]->addItems(items);


    for(int i=0;i< DLG_SET_CO2_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_CO2_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    setTabOrder(cmb[DLG_SET_CO2_COMBOBOX_NUM-1],spb[0]);
    for(int i = 0; i<DLG_SET_CO2_SPB_NUM;i++)
    {
        spb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_CO2_SPB_NUM-1))
            break;
        setTabOrder(spb[i],spb[i+1]);
    }
     setTabOrder(spb[DLG_SET_CO2_SPB_NUM-1],m_spb_jiaoling);
     setTabOrder(m_spb_jiaoling,m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
     cmb[0]->setFocus();
     stCO2ModuCfg cfg;
     g_CO2Module->f_get_cfg(&cfg);
    m_cmbb_model->setCurrentIndex(cfg.m_work_mode); //工作模式
    m_cmbb_alarm->setCurrentIndex(cfg.m_ssphyxia_alarm);; //窒息报警
    m_cmbb_ampli->setCurrentIndex(cfg.m_wave_amp);; //波形幅度
    m_cmbb_unit->setCurrentIndex(cfg.m_modu_unit); //单位
    m_cmbb_gas->setCurrentIndex(cfg.m_balance_air);; //平衡气体
    m_cmbb_wave_model->setCurrentIndex( cfg.m_wave_mode );;//波形模式
    m_spb_o2->setValue(cfg. m_co2_compens);; //氧气补偿
    m_spb_mazuiji->setValue( cfg.m_anesthetic_val); //麻醉剂剂量
    m_spb_wendubuchang->setValue( cfg.m_temp_compens); //温度补偿
    m_spb_daqiyali->setValue(cfg.m_air_pressure);; //大气压力
    m_cmbb_speed->setCurrentIndex(cfg.m_wave_speed); //6.25mm/s *N //波形速度

    m_spb_jiaoling->installEventFilter(this);
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_spb_jiaoling,SIGNAL(clicked()),this,SLOT(slot_jiaoling()));
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgSetCO2::do_ok_clicked()
{
    stCO2ModuCfg cfg;
    g_CO2Module->f_get_cfg(&cfg);
     cfg.m_work_mode = m_cmbb_model->currentIndex(); //工作模式
     cfg.m_ssphyxia_alarm = m_cmbb_alarm->currentIndex();; //窒息报警
     cfg.m_wave_amp = m_cmbb_ampli->currentIndex();; //波形幅度

     cfg.m_modu_unit = m_cmbb_unit->currentIndex(); //单位
     cfg.m_balance_air = m_cmbb_gas->currentIndex();; //平衡气体
     cfg.m_wave_mode = m_cmbb_wave_model->currentIndex();;//波形模式
     cfg. m_co2_compens = m_spb_o2->value();; //氧气补偿
     cfg.m_anesthetic_val = m_spb_mazuiji->value(); //麻醉剂剂量
     cfg.m_temp_compens =  m_spb_wendubuchang->value(); //温度补偿
     cfg.m_air_pressure  =  m_spb_daqiyali->value();; //大气压力

     cfg.m_wave_speed = m_cmbb_speed->currentIndex(); //6.25mm/s *N //波形速度

    g_CO2Module->f_set_cfg(cfg);
    close();
}
void CDlgSetCO2::do_cancel_clicked()
{
    close();
}
void CDlgSetCO2::slot_jiaoling()
{
    stCO2ModuCfg cfg;
    g_CO2Module->f_get_cfg(&cfg);
    cfg.m_correct_flg; //校准标志
    g_CO2Module->f_set_cfg(cfg);

}
bool CDlgSetCO2::eventFilter(QObject *o,QEvent *e)
{

    QObject *obj[]={
        m_cmbb_model,
        m_cmbb_alarm,
        m_cmbb_ampli,
        m_cmbb_speed,
        m_cmbb_unit,
        m_cmbb_gas,
        m_cmbb_wave_model,
        m_spb_o2,
        m_spb_mazuiji,
        m_spb_wendubuchang,
        m_spb_daqiyali,
        m_spb_jiaoling,
        m_btn_ok,
        m_btn_cancel
    };
    int iTotalObj =  14;//
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
                if((iCursor>=0) &&(iCursor<=6))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setFocus();
                }
                else if((iCursor >= 7)&&(iCursor <=10))
                {
                    QSpinBox *p = (QSpinBox *)obj[iCursor];
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
                if((iCursor == iOkPos)||
                    (iCursor == iCancelPos)||
                (iCursor == iOkPos -1)) //correct btn
                {

                }
                else if((iCursor>=0) &&(iCursor<=6))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    if( p->currentIndex()==0)
                        p->setCurrentIndex(p->count()-1);
                    else
                        p->setCurrentIndex(p->currentIndex()-1);
                }
                else if((iCursor >= 7)&&(iCursor <=10))
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
                if((iCursor>=0) &&(iCursor<=6))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setFocus();
                }
                else if((iCursor >= 7)&&(iCursor <=10))
                {
                    QSpinBox *p = (QSpinBox *)obj[iCursor];
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
                if((iCursor == iOkPos)||
                    (iCursor == iCancelPos)||
                (iCursor == iOkPos -1)) //correct btn
                {

                }
                else if((iCursor>=0) &&(iCursor<=6))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    if( p->currentIndex()==p->count()-1)
                        p->setCurrentIndex(0);
                    else
                        p->setCurrentIndex(p->currentIndex()+1);
                }
                else if((iCursor >= 7)&&(iCursor <=10))
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
                else if(iCursor == iOkPos -1)
                {
                    slot_jiaoling();
                }
                else if((iCursor>=0) &&(iCursor<=6))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }
                else if((iCursor >= 7)&&(iCursor <=10))
                {
                    bCursorSta = true;
                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");;
                }

            }
            else
            {
                bCursorSta = false;
                if((iCursor>=0) &&(iCursor<=6))
                {
                    //btn[iCursor]->showPopup();


                    QComboBox *p = (QComboBox *)obj[iCursor];
                    //p->setStyleSheet("background-color: rgb(255, 255, 255);");
                }
                else if((iCursor >= 7)&&(iCursor <=10))
                {

                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    //p->setStyleSheet("background-color: rgb(255, 255, 255);");;
                }
                //obj[iCursor]->setStyleSheet("background-color: rgb(255, 255, 255);");

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
    return true;
}
