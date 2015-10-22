#include "dlg_set_others.h"
#include <QKeyEvent>
#include "mainform.h"
#define DLG_SET_OTHERS_COMBOBOX_NUM 3

CDlgSetOthers::CDlgSetOthers(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SET_OTHERS_COMBOBOX_NUM];
    cmb[0] = m_cmbb_light;
    cmb[1] =m_cmbb_warning_volume;
    cmb[2] =m_cmbb_smoth;


    //增加选择项
     QStringList items;
     items<<"1"<<"2"<<"3"<<"4";
     cmb[0]->addItems(items);
     cmb[1]->addItems(items);

     items.clear();
     items<<"关"<<"开";
    cmb[2]->addItems(items);
/*     items<<"关"<<"10s"<<"15s"<<"20s"
            <<"25s"<<"30s"<<"35s"<<"40s";
    cmb[0]->addItems(items);
    items.clear();
     items<<"x0.25"<<"x0.5"<<"x1"<<"x2"<<"x4";
     cmb[1]->addItems(items);
     items.clear();
      items<<"6.25mm/s"<<"12.5mm/s"<<"25mm/s";
      cmb[2]->addItems(items);
      items.clear();
      items<<"II"<<"I";
      cmb[3]->addItems(items);
      items.clear();
      items<<"ECG"<<"CO2";
      cmb[4]->addItems(items);*/

    for(int i=0;i< DLG_SET_OTHERS_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SET_OTHERS_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
     setTabOrder(cmb[DLG_SET_OTHERS_COMBOBOX_NUM-1],m_btn_ok);
     setTabOrder(m_btn_ok,m_btn_cancel);
     setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();

    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
     connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
     connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}
void CDlgSetOthers::do_ok_clicked()
{

    close();
}
void CDlgSetOthers::do_cancel_clicked()
{
    close();
}

bool CDlgSetOthers::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_light
        ,m_cmbb_warning_volume
        ,m_cmbb_smoth
        ,m_btn_ok
        ,m_btn_cancel
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
