#include "dlg_record_boxing.h"
#include "../rsc_plot/plotter.h"
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <cmath>
#include <QSplitter>
#include <QKeyEvent>
//#include "mainform.h"
#define MAX_DLG_WAVE_COMB 0
#define MAX_DLG_WAVE_BTN 7
void readFlightCurves(Plotter *plotter, const QString &fileName)
{

    QVector<QPointF> data[6];
    double factX = 0.0013;
    double factY[6] = { 0.0008, 0.1, 0.2, 0.2, 0.1, 0.8 };
    double offsY[6] = { +500, -55, +309, +308, 0, 0 };
    int pos[6] = { 3, 6, 7, 8, 9, 10 };
    QFile file(fileName);
    double offsX = 0.0;

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList coords = line.split(' ',
                                            QString::SkipEmptyParts);
            if (coords.count() >= 6) {
                double x = factX * coords[0].toDouble();
                if (data[0].isEmpty())
                    offsX = x;
                for (int i = 0; i < 6; ++i) {
                    double y = coords[pos[i]].toDouble();
                    data[i].append(QPointF(x - offsX,
                                           factY[i] * (y - offsY[i])));
                }
            }
        }
    }

    plotter->setCurveData(0, data[0]);
    plotter->setCurveData(1, data[1]);
    plotter->setCurveData(2, data[2]);
    plotter->setCurveData(3, data[3]);
    plotter->setCurveData(4, data[4]);
    plotter->setCurveData(5, data[5]);

}

CDlgRecordWave::CDlgRecordWave(QWidget *parent,QWidget *pMain):QDialog(parent)
{
    setupUi(this);
    Plotter *plot = new Plotter(this);
    pMainForm = pMain;
    //设置光标顺序
    QPushButton *btn[MAX_DLG_WAVE_BTN] = {

        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    for(int i=0;i<MAX_DLG_WAVE_BTN;i++)
    {
        btn[i]->installEventFilter(this);
    }
    setTabOrder(m_btn_back_end,m_btn_back_fast);
    setTabOrder(m_btn_back_fast,m_btn_back);
    setTabOrder(m_btn_back,m_btn_forwd);
    setTabOrder(m_btn_forwd,m_btn_forwd_fast);
    setTabOrder(m_btn_forwd_fast,m_btn_forwd_end);
    setTabOrder(m_btn_forwd_end,m_btn_return);
    setTabOrder(m_btn_return,m_btn_back_end);
    m_btn_back_end->setFocus();

    connect(m_btn_return,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
}

void CDlgRecordWave::do_cancel_clicked()
{

    close();
}
bool CDlgRecordWave::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={

        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    int iTotalObj =  7;//11
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
                if((iCursor>=0) &&(iCursor<iTotalObj))
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
                if((iCursor>=0) &&(iCursor<iTotalObj))
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
                if((iCursor>=0) &&(iCursor<iTotalObj ))
                {
                    switch(iCursor)
                    {
                    case 0:
                        slot_back_end();
                        break;
                    case 1:
                        slot_back_fast();
                        break;

                    case 2:
                        slot_back();
                        break;
                    case 3:
                        slot_forwd_end();
                        break;
                    case 4:
                        slot_forwd_fast();
                        break;
                    case 5:
                        slot_forwd();
                        break;
                    case 6:
                        slot_return();
                        break;
                    default:
                        break;
                    }
                }


            }
            else
            {
            }
            return true;
            break;
        default:
            //CMainForm *p = (CMainForm *)pMainForm;
            //p->f_process_key(event->key());
            return true;
            break;

        }
    }
    else
    {
        return false;
    }
}

void CDlgRecordWave::slot_back_end()
{

}
void CDlgRecordWave::slot_back_fast()
{

}
void CDlgRecordWave::slot_back()
{

}
void CDlgRecordWave::slot_forwd_end()
{

}
void CDlgRecordWave::slot_forwd_fast()
{

}
void CDlgRecordWave::slot_forwd()
{

}
void CDlgRecordWave::slot_return()
{
    close();
}
