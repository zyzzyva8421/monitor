#include "dlg_set_eeg.h"
#include <QKeyEvent>
#include "rsc_modu/modu_eeg.h"
#include "mainform.h"
#define DLG_SET_EEG_COMBOBOX_NUM 12
#define DLG_SET_EEG_SPB_NUM 5
CDlgSetEEG::CDlgSetEEG(QWidget *parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    QComboBox *cmb[DLG_SET_EEG_COMBOBOX_NUM];
    cmb[0] = m_cmbb_daolianmoshi;
    cmb[1] =m_cmbb_boxingmoshi;
    cmb[2] =m_cmbb_lingmindu;
    cmb[3] =m_cmbb_boxingsudu;
    cmb[4] =m_cmbb_naodianlvbo;
    cmb[5] =m_cmbb_shijianchangshu;
    cmb[6] =m_cmbb_naodianxianbo;
    cmb[7] =m_cmbb_huxilvbo;
    cmb[8] =m_cmbb_huxichangshu;
    cmb[9] =m_cmbb_huxixianbo;
    cmb[10] =m_cmbb_hanshengchangshu;
    cmb[11] =m_cmbb_hanshengxianbo;

    QDoubleSpinBox *spb[DLG_SET_EEG_SPB_NUM];
    spb[0] = m_spb_naodianxishu;
    spb[1] = m_spb_huxixishu;
    spb[2] = m_spb_jidianxishu;
    spb[3] = m_spb_yandongxishu;
    spb[4] = m_spb_hanshengxishu;

    //增加选择项
     QStringList items;
     items.clear();items<<"脑电波8"
                       <<"脑电波8+睡眠"
                      <<"脑电波16"
                     <<"脑电波16+睡眠"
                    <<"脑电波32";
    cmb[0]->addItems(items);

   items.clear();
   items<<"15μv/cm"<<"25μv/cm"<<"30μv/cm"<<"35μv/cm"<<"40μv/cm"
       <<"50μv/cm"<<"70μv/cm"<<"80μv/cm"<<"100μv/cm"<<"120μv/cm"
      <<"150μv/cm"<<"200μv/cm"<<"300μv/cm"<<"400μv/cm"<<"500μv/cm";
    cmb[2]->addItems(items);
    items.clear();items<<"15mm/s"<<"30mm/s"<<"60mm/s";
    cmb[3]->addItems(items);
    items.clear();items<<"关"<<"15Hz"<<"30Hz"<<"40Hz";
    cmb[4]->addItems(items);
    items.clear();items<<"关"<<"0.1s"<<"0.2s"<<"0.3s";
    cmb[5]->addItems(items);
    items.clear();items<<"关"<<"开";
    cmb[6]->addItems(items);
    items.clear();items<<"关"<<"8Hz"<<"9Hz"<<"10Hz";
    cmb[7]->addItems(items);
    items.clear();items<<"关"<<"2s"<<"3s"<<"4s";
    cmb[8]->addItems(items);
    items.clear();items<<"关"<<"开";
    cmb[9]->addItems(items);
    items.clear();items<<"关"<<"0.1s"<<"0.2s"<<"0.3s";
    cmb[10]->addItems(items);
    items.clear();items<<"关"<<"开";
    cmb[11]->addItems(items);

    for(int i=0;i< DLG_SET_EEG_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_EEG_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
     setTabOrder(cmb[DLG_SET_EEG_COMBOBOX_NUM-1],spb[0]);
    for(int i=0; i<DLG_SET_EEG_SPB_NUM;i++)
     {
        spb[i]->installEventFilter(this);
         if(i == (DLG_SET_EEG_SPB_NUM-1))
             break;
         setTabOrder(spb[i],spb[i+1]);
     }
   // setTabOrder(spb[DLG_SET_EEG_SPB_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();

    CEegModuleCfg cfg;
    g_EegModule->f_get_eeg_cfg(&cfg);
    m_cmbb_daolianmoshi->setCurrentIndex(cfg.m_eeg_type);

    do_lead_changed(cfg.m_eeg_type);
    m_cmbb_boxingmoshi->setCurrentIndex(cfg.m_eeg_display);

    m_cmbb_lingmindu->setCurrentIndex(cfg.m_eeg_wave_sensitive);
    m_cmbb_boxingsudu->setCurrentIndex(cfg.m_eeg_wave_speed);
    m_cmbb_naodianlvbo->setCurrentIndex(cfg.m_eeg_wave_filter);
    m_cmbb_shijianchangshu->setCurrentIndex(cfg.m_eeg_time_const);
    m_cmbb_naodianxianbo->setCurrentIndex(cfg.m_eeg_trap_en);
    m_cmbb_huxilvbo->setCurrentIndex(cfg.m_eeg_spire_filter);
    m_cmbb_huxichangshu->setCurrentIndex(cfg.m_eeg_spire_time_const);
    m_cmbb_huxixianbo->setCurrentIndex(cfg.m_eeg_spire_trap_en);
    m_cmbb_hanshengchangshu->setCurrentIndex(cfg.m_eeg_snore_time_const);
    m_cmbb_hanshengxianbo->setCurrentIndex(cfg.m_eeg_snore_trap_en);

    m_spb_naodianxishu->setValue(cfg.m_eeg_coef);
    m_spb_huxixishu->setValue(cfg.m_eeg_spire_coef);
    m_spb_jidianxishu->setValue(cfg.m_eeg_emg_coef);
    m_spb_yandongxishu->setValue(cfg.m_eeg_eyemove_coef);
    m_spb_hanshengxishu->setValue(cfg.m_eeg_snore_coef);



    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
    connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
    connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
    connect(m_cmbb_daolianmoshi,SIGNAL(currentIndexChanged(int)),this,SLOT(do_lead_changed(int)));
}
void CDlgSetEEG::do_ok_clicked()
{
    CEegModuleCfg cfg;
    g_EegModule->f_get_eeg_cfg(&cfg);
    cfg.m_eeg_type =  m_cmbb_daolianmoshi->currentIndex();
    cfg.m_eeg_display =  m_cmbb_boxingmoshi->currentIndex();
    cfg.m_eeg_wave_sensitive =  m_cmbb_lingmindu->currentIndex();
    cfg.m_eeg_wave_speed =  m_cmbb_boxingsudu->currentIndex();
    cfg.m_eeg_wave_filter =  m_cmbb_naodianlvbo->currentIndex();
    cfg.m_eeg_time_const =  m_cmbb_shijianchangshu->currentIndex();
    cfg.m_eeg_trap_en =  m_cmbb_naodianxianbo->currentIndex();
    cfg.m_eeg_spire_filter =  m_cmbb_huxilvbo->currentIndex();
    cfg.m_eeg_spire_time_const =  m_cmbb_huxichangshu->currentIndex();
    cfg.m_eeg_spire_trap_en= m_cmbb_huxixianbo->currentIndex();
    cfg.m_eeg_snore_time_const =  m_cmbb_hanshengchangshu->currentIndex();
    cfg.m_eeg_snore_trap_en =  m_cmbb_hanshengxianbo->currentIndex();

    cfg.m_eeg_coef =  m_spb_naodianxishu->value();
    cfg.m_eeg_spire_coef =  m_spb_huxixishu->value();
    cfg.m_eeg_emg_coef =  m_spb_jidianxishu->value();
    cfg.m_eeg_eyemove_coef =  m_spb_yandongxishu->value();
    cfg.m_eeg_snore_coef =  m_spb_hanshengxishu->value();
    g_EegModule->f_set_eeg_cfg(cfg);
    close();
}
void CDlgSetEEG::do_cancel_clicked()
{
    close();
}
 void CDlgSetEEG::do_lead_changed(int idx)
 {
     QStringList items;
     m_cmbb_boxingmoshi->clear();
     items<<"脑电波1-8";
     switch(idx )
     {
      case 0:

         break;
     case 1:
         items<<"睡眠";
         break;
     case 2:
         items<<"脑电波9-16";
         break;
     case 3:
         items<<"脑电波9-16"<<"睡眠";
         break;
     case 4:
         items<<"脑电波9-16"<<"脑电波17-24"<<"脑电波25-32";
         break;
     default:
         break;
     }
    m_cmbb_boxingmoshi->addItems(items);
    //CEegModuleCfg cfg;
    //g_EegModule->f_get_eeg_cfg(&cfg);
    //m_cmbb_boxingmoshi->setCurrentIndex(cfg.m_eeg_display);
 }

bool CDlgSetEEG::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_daolianmoshi
        ,m_cmbb_boxingmoshi
        ,m_cmbb_lingmindu
        ,m_cmbb_boxingsudu
        ,m_cmbb_naodianlvbo
        ,m_cmbb_shijianchangshu
        ,m_cmbb_naodianxianbo
        ,m_cmbb_huxilvbo
        ,m_cmbb_huxichangshu
        ,m_cmbb_huxixianbo
        ,m_cmbb_hanshengchangshu
        ,m_cmbb_hanshengxianbo
        ,m_spb_naodianxishu
        ,m_spb_huxixishu
        ,m_spb_jidianxishu
        ,m_spb_yandongxishu
        ,m_spb_hanshengxishu
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  sizeof(obj)/4;//11
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

                if((iCursor >= 12)&&(iCursor <=16))
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
                if((iCursor >= 12)&&(iCursor <=16))
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
                else if((iCursor>=0) &&(iCursor<12))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }
                else if((iCursor>=12) &&(iCursor<=16))
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
            return true;
            break;

        }
    }
    else
    {
        return false;
    }
}
