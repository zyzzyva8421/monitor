
#include "dlg_set_ibp.h"
#include "rsc_modu/modu_ibp.h"
#include "mainform.h"

#define DLG_SET_IBP_COMBOBOX_NUM 8
#define DLG_SET_IBP_SPB_NUM 4

CDlgSetIBP::CDlgSetIBP(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    pMainForm = pMain;
    QComboBox *cmb[DLG_SET_IBP_COMBOBOX_NUM];
    cmb[0] = m_cmbb_chnl1;
    cmb[1] =m_cmbb_chnl2;
    cmb[2] =m_cmbb_biaochi;
    cmb[3] =m_cmbb_moshi;
    cmb[4] =m_cmbb_speed;
    cmb[5] =m_cmbb_unit;
    cmb[6] =m_cmbb_p1;
    cmb[7] =m_cmbb_p2;

    QDoubleSpinBox * spb[DLG_SET_IBP_SPB_NUM] ;
    spb[0] = m_spb_chnl1_high;
    spb[1] = m_spb_chnl1_low;
    spb[2] = m_spb_chnl2_high;
    spb[3] = m_spb_chnl2_low;
    //增加选择项
     QStringList items;
     items<<"主动脉压"<<"肺动脉压"<<"中心静脉压"<<"左房压"
            <<"右房压"<<"颅内压"<<"P1"<<"P2";
    cmb[0]->addItems(items);
    cmb[1]->addItems(items);
    items.clear();
    items<<"手动"<<"自动";
    cmb[2]->addItems(items);
    items.clear();
    items<<"平滑"<<"正常";
    cmb[3]->addItems(items);
    items.clear();
    items<<"12.5mm/s"<<"25mm/s";
    cmb[4]->addItems(items);
    items.clear();
    items<<"mmHg"<<"kPa"<<"%";
    cmb[5]->addItems(items);
    items.clear();
    items<<"S/D(M)"<<"平均压";
    cmb[6]->addItems(items);
    cmb[7]->addItems(items);

    for(int i=0;i< DLG_SET_IBP_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_IBP_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    setTabOrder(cmb[DLG_SET_IBP_COMBOBOX_NUM-1],spb[0]);
    for(int i=0;i<DLG_SET_IBP_SPB_NUM;i++)
    {
        spb[i]->installEventFilter(this);
        if(i == (DLG_SET_IBP_SPB_NUM-1))
            break;
        setTabOrder(spb[i],spb[i+1]);
    }
     setTabOrder(spb[DLG_SET_IBP_SPB_NUM-1],m_btn_ibp_jiaoling);
     setTabOrder(m_btn_ibp_jiaoling,m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
     cmb[0]->setFocus();
     stIBPModuCfg cfg;
     g_IBPModule1->f_get_cfg(&cfg);
     m_cmbb_chnl1->setCurrentIndex(cfg.m_chanel1_type);
     m_cmbb_chnl2->setCurrentIndex(cfg.m_chanel2_type);
     m_cmbb_biaochi->setCurrentIndex(cfg.m_wave_ruler_mode);
     m_cmbb_speed->setCurrentIndex(cfg.m_wave_filter_mode);
     m_cmbb_unit->setCurrentIndex(cfg.m_modu_unit);
     m_cmbb_p1->setCurrentIndex(cfg.m_p1_type);
     m_cmbb_p2->setCurrentIndex(cfg.m_p2_type);
     m_spb_chnl1_high->setValue(cfg.m_chanel1_ruler_high);
     m_spb_chnl1_low->setValue(cfg.m_chanel1_ruler_low);
     m_spb_chnl2_high->setValue(cfg.m_chanel2_ruler_high);
     m_spb_chnl2_low->setValue(cfg.m_chanel2_ruler_low);
     iCursor = 0;
     bCursorSta = false;
     m_btn_ibp_jiaoling->installEventFilter(this);
     m_btn_ok->installEventFilter(this);
     m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
     connect(m_btn_ibp_jiaoling,SIGNAL(clicked()),this,SLOT(do_correct()));
     connect(m_cmbb_chnl1,SIGNAL(currentIndexChanged(int)),this,SLOT(do_chanel1_changed(int)));
     connect(m_cmbb_chnl2,SIGNAL(currentIndexChanged(int)),this,SLOT(do_chanel2_changed(int)));
}
void CDlgSetIBP::do_ok_clicked()
{
    stIBPModuCfg cfg;
    g_IBPModule1->f_get_cfg(&cfg);
    cfg.m_chanel1_type = m_cmbb_chnl1->currentIndex();
    cfg.m_chanel2_type = m_cmbb_chnl2->currentIndex();
    cfg.m_wave_ruler_mode = m_cmbb_biaochi->currentIndex();
    cfg.m_wave_filter_mode = m_cmbb_speed->currentIndex();
    cfg.m_modu_unit = m_cmbb_unit->currentIndex();
    cfg.m_p1_type = m_cmbb_p1->currentIndex();
    cfg.m_p2_type = m_cmbb_p2->currentIndex();
    cfg.m_chanel1_ruler_high = m_spb_chnl1_high->value();
    cfg.m_chanel1_ruler_low = m_spb_chnl1_low->value();
    cfg.m_chanel2_ruler_high = m_spb_chnl2_high->value();
    cfg.m_chanel2_ruler_low = m_spb_chnl2_low->value();
    g_IBPModule1->f_set_cfg(cfg);
    close();

}
void CDlgSetIBP::do_cancel_clicked()
{
    close();
}
 void CDlgSetIBP::do_correct()
 {

 }
 void CDlgSetIBP::do_chanel1_changed(int indx1)
 {
     int indx2 = 0;
     if(m_cmbb_chnl2->currentIndex() == indx1)
     {
         if(indx1 == 0)
         {
             indx2 = 1;
         }
         else
         {
             indx2 = indx1-1;
         }
         m_cmbb_chnl2->setCurrentIndex(indx2);
     }
 }

 void CDlgSetIBP::do_chanel2_changed(int indx2)
 {
     int indx1 = 0;
     if(m_cmbb_chnl1->currentIndex() == indx2)
     {
         if(indx2 == 0)
         {
             indx1 = 1;
         }
         else
         {
             indx1 = indx2-1;
         }
         m_cmbb_chnl1->setCurrentIndex(indx1);
     }

 }
 bool CDlgSetIBP::eventFilter(QObject *o,QEvent *e)
 {
     QObject *obj[]={
         m_cmbb_chnl1
         ,m_cmbb_chnl2
         ,m_cmbb_biaochi
         ,m_cmbb_moshi
         ,m_cmbb_speed
         ,m_cmbb_unit
         ,m_cmbb_p1
         ,m_cmbb_p2
         ,m_spb_chnl1_high
         ,m_spb_chnl1_low
         , m_spb_chnl2_high
         , m_spb_chnl2_low
         ,m_btn_ibp_jiaoling
         ,m_btn_ok
         ,m_btn_cancel
     };
     int iTotalObj =  15;//11
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
                 if((iCursor>=0) &&(iCursor<iOkPos-1))
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

                 if((iCursor >= 8)&&(iCursor <=11))
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
                 if((iCursor>=0) &&(iCursor<(iOkPos-1)))
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
                 if((iCursor >= 8)&&(iCursor <=11))
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
                 else if(iCursor == iOkPos-1)
                 {
                     do_correct();
                 }
                 else if((iCursor>=0) &&(iCursor<8))
                 {
                     //btn[iCursor]->showPopup();

                     bCursorSta = false;
                     QComboBox *p = (QComboBox *)obj[iCursor];
                     p->showPopup();
                     //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                 }
                 else if((iCursor>=8) &&(iCursor<=11))
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
