#include "dlg_set_mashen.h"
#include "rsc_modu/modu_anaes.h"
#include "mainform.h"
#define DLG_SET_MASHEN_COMBOBOX_NUM 2

CDlgSetMashen::CDlgSetMashen(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    pMainForm = pMain;
    QComboBox *cmb[DLG_SET_MASHEN_COMBOBOX_NUM];
    cmb[0] = m_cmbb_ap;
    cmb[1] =m_cmbb_speed;


    //增加选择项
     QStringList items;
     items<<"±10μv"<<"±20μv"<<"±40μv"
         <<"±80μv"<<"±100μv"<<"±150μv"<<"±200μv";
    cmb[0]->addItems(items);
    items.clear();
    items<<"6.25mm/s"<<"12.5mm/s"<<"25mm/s";
    cmb[1]->addItems(items);

    for(int i=0;i< DLG_SET_MASHEN_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_MASHEN_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    setTabOrder(cmb[DLG_SET_MASHEN_COMBOBOX_NUM-1],m_btn_ok);
    setTabOrder(m_btn_ok,m_btn_cancel);
    setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();
    stAnaesDepModuCfg cfg;
    g_AnaesModule->f_get_cfg(&cfg);
    m_cmbb_ap->setCurrentIndex(cfg.m_wave_amp);
    m_cmbb_speed->setCurrentIndex(cfg.m_wave_speed);
    iCursor = 0;
    bCursorSta = false;
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgSetMashen::do_ok_clicked()
{
    stAnaesDepModuCfg cfg;
    g_AnaesModule->f_get_cfg(&cfg);
    cfg.m_wave_amp = m_cmbb_ap->currentIndex();
    cfg.m_wave_speed = m_cmbb_speed->currentIndex();
    g_AnaesModule->f_set_cfg(cfg);
    close();
}
void CDlgSetMashen::do_cancel_clicked()
{
    close();
}
bool CDlgSetMashen::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
         m_cmbb_ap
        ,m_cmbb_speed
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  4;//11
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
            {
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

