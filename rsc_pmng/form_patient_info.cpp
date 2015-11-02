#include <QtGui>
#include"ui_pmng_patient_info.h"
#include "form_patient_info.h"
#include "mainform.h"
#include "keyboard_context.h"
CFormPatientInfo::CFormPatientInfo(QWidget* parent,QWidget *pMain) :QDialog(parent)
{
    setupUi(this);
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    //this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    //
    setTabOrder(spinBox_chuanghao,comboBox_xingbie);
    setTabOrder(comboBox_xingbie,spinBox_shengao);
    setTabOrder(spinBox_shengao,comboBox_leixing);
    setTabOrder(comboBox_leixing,spinBox_tizhong);
    setTabOrder(spinBox_tizhong,comboBox_xuexing);
    setTabOrder(comboBox_xuexing,lineEdit_binglihao);
    setTabOrder(lineEdit_binglihao,lineEdit_bingrenxingming);
    setTabOrder(lineEdit_bingrenxingming,lineEdit_yishengxingming);
    setTabOrder(lineEdit_yishengxingming,spinBox_chusheng_nian);
    setTabOrder(spinBox_chusheng_nian,spinBox_chusheng_yue);
    setTabOrder(spinBox_chusheng_yue,spinBox_chusheng_ri);
    setTabOrder(spinBox_chusheng_ri,spinBox_ruyuan_nian);
    setTabOrder(spinBox_ruyuan_nian,spinBox_ruyuan_yue);
    setTabOrder(spinBox_ruyuan_yue,spinBox_ruyuan_ri);
    setTabOrder(spinBox_ruyuan_ri,m_btn_ok);
    setTabOrder(m_btn_ok,m_btn_cancel);
    setTabOrder(m_btn_cancel,spinBox_chuanghao);
    spinBox_chuanghao->setFocus();
    //
    comboBox_leixing->addItem(("成人"));
    comboBox_leixing->addItem(("婴儿"));
    comboBox_xingbie->addItem(("男"));
    comboBox_xingbie->addItem(("女"));
    //
    QObject *obj[17] = {
        spinBox_chuanghao,
        comboBox_xingbie,
        spinBox_shengao,
        comboBox_leixing,
        spinBox_tizhong,
        comboBox_xuexing,
        lineEdit_binglihao,
        lineEdit_bingrenxingming,
        lineEdit_yishengxingming,
        spinBox_chusheng_nian,
        spinBox_chusheng_yue,
        spinBox_chusheng_ri,
        spinBox_ruyuan_nian,
        spinBox_ruyuan_yue,
        spinBox_ruyuan_ri,
        m_btn_ok,
        m_btn_cancel
    };
    for(int i = 0;i<17;i++)
    {
        obj[i]->installEventFilter(this);
    }
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
    connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(accept()));
    connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(close()));
}
void CFormPatientInfo::do_ok_clicked()
{
    close();
}
void CFormPatientInfo::do_cancel_clicked()
{
    close();
}
bool CFormPatientInfo::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        spinBox_chuanghao,
        comboBox_xingbie,
        spinBox_shengao,
        comboBox_leixing,
        spinBox_tizhong,
        comboBox_xuexing,
        lineEdit_binglihao,
        lineEdit_bingrenxingming,
        lineEdit_yishengxingming,
        spinBox_chusheng_nian,
        spinBox_chusheng_yue,
        spinBox_chusheng_ri,
        spinBox_ruyuan_nian,
        spinBox_ruyuan_yue,
        spinBox_ruyuan_ri,
        m_btn_ok,
        m_btn_cancel
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

                if(((iCursor >= 9)&&(iCursor <=14))||
                        (iCursor == 0)||
                        (iCursor == 2)||
                        (iCursor == 4))
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

                if(((iCursor >= 9)&&(iCursor <=14))||
                        (iCursor == 0)||
                        (iCursor == 2)||
                        (iCursor == 4))
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
                else if((iCursor==1) ||(iCursor==5)||(iCursor==3))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }
                else if(((iCursor >= 9)&&(iCursor <=14))||
                            (iCursor == 0)||
                            (iCursor == 2)||
                            (iCursor == 4))
                {
                    bCursorSta = true;
                    QSpinBox *p = (QSpinBox *)obj[iCursor];

                } else if (iCursor == 6 || iCursor == 7 || iCursor == 9) {
                    // line edit, popup the keyboard
                    ((KeyboardContext*)qApp->inputContext())->showKeyboard();
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
            return false;
            break;

        }
    }
    else
    {
        return false;
    }
}
