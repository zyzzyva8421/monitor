#include "dlg_serv_man_para.h"
#include <QKeyEvent>
#include "mainform.h"
#define DLG_SERV_MAN_CFG_PARA_COMBOBOX_NUM 15

CDlgServManCfgPara::CDlgServManCfgPara(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SERV_MAN_CFG_PARA_COMBOBOX_NUM];
    cmb[0] = m_cmbb_xindian;
    cmb[1] =m_cmbb_xueyang;
    cmb[2] =m_cmbb_huxi;
    cmb[3] =m_cmbb_tiwen;
    cmb[4] =m_cmbb_nibp;
    cmb[5] =m_cmbb_mashen;
    cmb[6] =m_cmbb_ibp1;
    cmb[7] =m_cmbb_ibp2;
    cmb[8] = m_cmbb_co2;
    cmb[9] =m_cmbb_qushi;
    cmb[10] =m_cmbb_baojinghuigu;
    cmb[11] =m_cmbb_boxinghuigu;
    cmb[12] =m_cmbb_jiemian;
    cmb[13] =m_cmbb_yaowujisuan;
    cmb[14] = m_cmbb_daolianleixing;

    //增加选择项
     QStringList items;
     items<<"关"<<"开";
    for(int i=0;i< DLG_SERV_MAN_CFG_PARA_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
         cmb[i]->addItems(items);
        //设置光标顺序
        if(i == (DLG_SERV_MAN_CFG_PARA_COMBOBOX_NUM-1))
        {
            items.clear();
            items<<"3导联"<<"5导联";
            cmb[i]->addItems(items);
            break;
        }
        setTabOrder(cmb[i],cmb[i+1]);
    }
     setTabOrder(cmb[DLG_SERV_MAN_CFG_PARA_COMBOBOX_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgServManCfgPara::do_ok_clicked()
{

    close();
}
void CDlgServManCfgPara::do_cancel_clicked()
{
    close();
}
bool CDlgServManCfgPara::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
         m_cmbb_xindian
        ,m_cmbb_xueyang
        ,m_cmbb_huxi
        ,m_cmbb_tiwen
        ,m_cmbb_nibp
        ,m_cmbb_mashen
        ,m_cmbb_ibp1
        ,m_cmbb_ibp2
        ,m_cmbb_co2
        ,m_cmbb_qushi
        ,m_cmbb_baojinghuigu
        ,m_cmbb_boxinghuigu
        ,m_cmbb_jiemian
        ,m_cmbb_yaowujisuan
        ,m_cmbb_daolianleixing
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  17;//11
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
