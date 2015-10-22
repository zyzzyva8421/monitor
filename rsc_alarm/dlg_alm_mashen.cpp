#include "dlg_alm_mashen.h"
#include "mainform.h"
#define DLG_ALM_MASHEN_COMBOBOX_NUM 1
#define DLG_ALM_MASHEN_SPB_NUM 2

CDlgAlmMashen::CDlgAlmMashen(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    QComboBox *cmb[DLG_ALM_MASHEN_COMBOBOX_NUM];
    cmb[0] = m_cmbb_mashen;

    QSpinBox * spb[DLG_ALM_MASHEN_SPB_NUM];
    spb[0] = m_spb_h;
    spb[1] = m_spb_l;


    //增加选择项
     QStringList items;
     items<<"关"<<"开";

    for(int i=0;i< DLG_ALM_MASHEN_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        cmb[i]->addItems(items);
        //设置光标顺序
        setTabOrder(cmb[i],spb[i*2]);
        setTabOrder(spb[i*2],spb[i*2+1]);

        if(i == (DLG_ALM_MASHEN_COMBOBOX_NUM-1))
            break;
        setTabOrder(spb[i*2+1],cmb[i+1]);
    }
    for(int i = 0;i<DLG_ALM_MASHEN_SPB_NUM;i++)
    {
        spb[i]->installEventFilter(this);
    }
     setTabOrder(spb[DLG_ALM_MASHEN_SPB_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();
    stAnaesDepModuCfg cfg;
    g_AnaesModule->f_get_cfg(&cfg);

    m_cmbb_mashen->setCurrentIndex(cfg.m_alarm_enable);
    m_spb_h->setValue(cfg.m_alarm_high);
    m_spb_l->setValue(cfg.m_alarm_low);
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgAlmMashen::do_ok_clicked()
{
    stAnaesDepModuCfg cfg;
    g_AnaesModule->f_get_cfg(&cfg);
    cfg.m_alarm_enable = m_cmbb_mashen->currentIndex();
    cfg.m_alarm_high = m_spb_h->value();
    cfg.m_alarm_low = m_spb_l->value();
    g_AnaesModule->f_set_cfg(cfg);
    close();
}
void CDlgAlmMashen::do_cancel_clicked()
{
    close();
}
bool CDlgAlmMashen::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_mashen
        ,m_spb_h
        ,m_spb_l

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

                if((iCursor == 1)||
                        (iCursor == 2)||
                        (iCursor == 4)||
                        (iCursor == 5)
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

                if((iCursor == 1)||
                        (iCursor == 2)||
                        (iCursor == 4)||
                        (iCursor == 5)
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
                else if((iCursor==0) ||(iCursor==3))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }
                else if((iCursor == 1)||
                (iCursor == 2)||
                (iCursor == 4)||
                (iCursor == 5)

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
