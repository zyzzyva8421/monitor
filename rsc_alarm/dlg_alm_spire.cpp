#include "dlg_alm_spire.h"
#include "mainform.h"
#define DLG_ALM_SPIRE_COMBOBOX_NUM 1
#define DLG_ALM_SPIRE_SPB_NUM 2

CDlgAlmSpire::CDlgAlmSpire(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    QComboBox *cmb[DLG_ALM_SPIRE_COMBOBOX_NUM];
    cmb[0] = m_cmbb_alm;

    QSpinBox * spb[DLG_ALM_SPIRE_SPB_NUM];
    spb[0] = m_spb_high;
    spb[1] = m_spb_low;


    //增加选择项
     QStringList items;
     items<<"关"<<"开";

    for(int i=0;i< DLG_ALM_SPIRE_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        cmb[i]->addItems(items);
        //设置光标顺序
        setTabOrder(cmb[i],spb[i*2]);
        setTabOrder(spb[i*2],spb[i*2+1]);

        if(i == (DLG_ALM_SPIRE_COMBOBOX_NUM-1))
            break;
        setTabOrder(spb[i*2+1],cmb[i+1]);
    }
    for(int i = 0;i<DLG_ALM_SPIRE_SPB_NUM;i++)
    {
        spb[i]->installEventFilter(this);
    }
     setTabOrder(spb[DLG_ALM_SPIRE_SPB_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();

    CSpireModuleCfg cfg;
    g_EcgModule->f_get_spire_cfg(&cfg);
   m_spb_high->setValue( cfg.m_alarm_high);
    m_spb_low->setValue(cfg.m_alarm_low);
    m_cmbb_alm->setCurrentIndex(cfg.m_alarm_en);
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgAlmSpire::do_ok_clicked()
{
    CSpireModuleCfg cfg;
    g_EcgModule->f_get_spire_cfg(&cfg);
    cfg.m_alarm_high =m_spb_high->value();
    cfg.m_alarm_low = m_spb_low->value();
    cfg.m_alarm_en = m_cmbb_alm->currentIndex();
    g_EcgModule->f_set_spire_cfg(cfg);
    close();
}
void CDlgAlmSpire::do_cancel_clicked()
{
    close();
}
bool CDlgAlmSpire::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_alm
        ,m_spb_high
        ,m_spb_low

        ,m_btn_ok,
        m_btn_cancel
    };
    int iTotalObj =  5;//11
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

                if((iCursor == 1)
                        )
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

                if((iCursor == 1)
                        )
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
                else if((iCursor==0) )
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }
                else if((iCursor == 1)
                )
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
