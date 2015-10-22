#include "form_patient_drug.h"
#include <QKeyEvent>
#include "mainform.h"
CFormPatientDrug::CFormPatientDrug(QWidget *parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    //设置光标顺序
    setTabOrder(combb_yaowumingcheng,dspinb_tizhong);
    setTabOrder(dspinb_tizhong,dspinb_yaowuzongliang);
    setTabOrder(dspinb_yaowuzongliang,dspinb_yetirongji);
    setTabOrder(dspinb_yetirongji,dspinb_jiliang_min);
    setTabOrder(dspinb_jiliang_min,dspinb_jiliang_hr);
    setTabOrder(dspinb_jiliang_hr,dspinb_jiliang_k_min);
    setTabOrder(dspinb_jiliang_k_min,dspinb_jiliang_k_hr);
    setTabOrder(dspinb_jiliang_k_hr,dspinb_shuyesudu);
    setTabOrder(dspinb_shuyesudu,dspinb_disu);
    setTabOrder(dspinb_disu,dspinb_meiditiji);
    setTabOrder(dspinb_meiditiji,dspinb_shuyeshijian);
    setTabOrder(dspinb_shuyeshijian,m_btn_diding);
    setTabOrder(m_btn_diding,combb_yaowumingcheng);
    combb_yaowumingcheng->setFocus();
    QObject *obj[]={
        combb_yaowumingcheng,
        dspinb_tizhong,
        dspinb_yaowuzongliang,
        dspinb_yetirongji,
        dspinb_jiliang_min,
        dspinb_jiliang_hr,
        dspinb_jiliang_k_min,
        dspinb_jiliang_k_hr,
        dspinb_shuyesudu,
        dspinb_disu,
        dspinb_meiditiji,
        dspinb_shuyeshijian,
        m_btn_diding,
        m_btn_return
    };
    for(int i = 0;i<14;i++)
    {
        obj[i]->installEventFilter(this);
    }
    m_btn_diding->installEventFilter(this);
    m_btn_return->installEventFilter(this);
    connect(m_btn_diding,SIGNAL(clicked()),this,SLOT(do_diding()));
    connect(m_btn_return,SIGNAL(clicked()),this,SLOT(close()));
}
void CFormPatientDrug::do_diding()
{

}
bool CFormPatientDrug::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        combb_yaowumingcheng,
        dspinb_tizhong,
        dspinb_yaowuzongliang,
        dspinb_yetirongji,
        dspinb_jiliang_min,
        dspinb_jiliang_hr,
        dspinb_jiliang_k_min,
        dspinb_jiliang_k_hr,
        dspinb_shuyesudu,
        dspinb_disu,
        dspinb_meiditiji,
        dspinb_shuyeshijian,
        m_btn_diding,
        m_btn_return
    };
    int iTotalObj = 14;//11
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

                if((iCursor >= 1)&&(iCursor <=11))
                {
                    QDoubleSpinBox *p = (QDoubleSpinBox *)obj[iCursor];
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
                if((iCursor >= 1)&&(iCursor <=11))
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

            }
            return true;
            break;
        case Qt::Key_Return:
            if(bCursorSta == false)
            {
                if(iCursor == iOkPos)
                {
                    do_diding();
                }
                else if(iCursor == iCancelPos)
                {
                    close();
                }

                else if((iCursor>=0) &&(iCursor<1))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }
                else if((iCursor>=1) &&(iCursor<=11))
                {
                    bCursorSta = true;
                    QDoubleSpinBox *p = (QDoubleSpinBox *)obj[iCursor];

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
