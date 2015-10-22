#include "dlg_serv_man_config.h"
#include "dlg_serv_man_para.h"
#include <QKeyEvent>
#include "mainform.h"
#define DLG_SERV_MAN_CFG_COMBOBOX_NUM 20

CDlgServManCfg::CDlgServManCfg(QWidget * parent,QWidget *pMain):QDialog(parent)
{
    iCursor = 0;
    bCursorSta = false;
    pMainForm = pMain;
    setupUi(this);
    QComboBox *cmb[DLG_SERV_MAN_CFG_COMBOBOX_NUM];
    cmb[0] = m_cmbb_lang;
    cmb[1] =m_cmbb_bianmaqi;
    cmb[2] =m_cmbb_tfp_val;
    cmb[3] =m_cmbb_pwr_board_val;
    cmb[4] =m_cmbb_yuyinbaojing;
    cmb[5] =m_cmbb_chuankou;
    cmb[6] = m_cmbb_boxingchangdu;
    cmb[7] =m_cmbb_yonghuxinxi;
    cmb[8] =m_cmbb_protocol;
    cmb[9] =m_cmbb_xinxi;
    cmb[10] =m_cmbb_qushihuigu;
    cmb[11] =m_cmbb_tiwentongdao;
    cmb[12] =m_cmbb_oem;
    cmb[13] =m_cmbb_ibp;
    cmb[14] =m_cmbb_kexuanmokuai;
    cmb[15] =m_cmbb_usb;
    cmb[16] = m_cmbb_chumoping;
    cmb[17] =m_cmbb_shuchu;
    cmb[18] =m_cmbb_jiluyi;
    cmb[19] =m_cmbb_spo2;

    //增加选择项
     QStringList items;
     items<<"中文"<<"English";
    cmb[0]->addItems(items);
    items.clear();
    items<<"GrayHill"<<"EC12E"<<"EC11E";
    cmb[1]->addItems(items);
    items.clear();
    items<<"4.3"<<"7"<<"9"<<"12"<<"15";
    cmb[2]->addItems(items);
    items.clear();
    items<<"1"<<"2";
    cmb[3]->addItems(items);
    items.clear();
    items<<"关"<<"开";
    cmb[4]->addItems(items);
    items.clear();
    items<<"记录仪"<<"CPT-CO2";
    cmb[5]->addItems(items);
    items.clear();
    items<<"1"<<"2"<<"4"<<"8"<<"10"<<"12"<<"20"<<"24";
    cmb[6]->addItems(items);
    items.clear();
    items<<"病人管理"<<"动物"<<"用户"<<"新生儿";
    cmb[7]->addItems(items);
    items.clear();
    items<<"FY0801"<<"8-bit"<<"FY0808";
    cmb[8]->addItems(items);
    items.clear();
    items<<"关"<<"开";
    cmb[9]->addItems(items);
    items.clear();
    items<<"72h"<<"120h"<<"240h"<<"36h"<<"720h"<<"1440h";
    cmb[10]->addItems(items);
    items.clear();
    items<<"2CH"<<"1CH";
    cmb[11]->addItems(items);
    items.clear();
    items<<"NCC";
    cmb[12]->addItems(items);
    items.clear();
    items<<"关"<<"开";
    cmb[13]->addItems(items);
    cmb[14]->addItems(items);
    cmb[15]->addItems(items);
    cmb[16]->addItems(items);
    cmb[17]->addItems(items);
    items.clear();
    items<<"UC50"<<"WG50";
    cmb[18]->addItems(items);
    items.clear();
    items<<"ADCOM"<<"MASIMO";
    cmb[19]->addItems(items);

    for(int i=0;i< DLG_SERV_MAN_CFG_COMBOBOX_NUM;i++)
    {
        cmb[i]->installEventFilter(this);
        //设置光标顺序
        if(i == (DLG_SERV_MAN_CFG_COMBOBOX_NUM-1))
            break;
        setTabOrder(cmb[i],cmb[i+1]);
    }
    setTabOrder(cmb[DLG_SERV_MAN_CFG_COMBOBOX_NUM-1],m_btn_para_switch);
    setTabOrder(m_btn_para_switch,m_btn_ok);
    setTabOrder(m_btn_ok,m_btn_cancel);
    setTabOrder(m_btn_cancel,cmb[0]);
    cmb[0]->setFocus();
    m_btn_para_switch->installEventFilter(this);
    m_btn_ok->installEventFilter(this);
    m_btn_cancel->installEventFilter(this);
    connect(m_btn_ok,SIGNAL(clicked()),this,SLOT(do_ok_clicked()));
    connect(m_btn_cancel,SIGNAL(clicked()),this,SLOT(do_cancel_clicked()));
    connect(m_btn_para_switch,SIGNAL(clicked()),this,SLOT(do_para_sw_clicked()));
}
void CDlgServManCfg::do_ok_clicked()
{

    close();
}
void CDlgServManCfg::do_cancel_clicked()
{
    close();
}
void CDlgServManCfg::do_para_sw_clicked()
{
    close();
    CDlgServManCfgPara *dlg = new CDlgServManCfgPara(this,pMainForm);
    dlg->show();

}
bool CDlgServManCfg::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
         m_cmbb_lang
        ,m_cmbb_bianmaqi
        ,m_cmbb_tfp_val
        ,m_cmbb_pwr_board_val
        ,m_cmbb_yuyinbaojing
        ,m_cmbb_chuankou
        ,m_cmbb_boxingchangdu
        ,m_cmbb_yonghuxinxi
        ,m_cmbb_protocol
        ,m_cmbb_xinxi
        ,m_cmbb_qushihuigu
        ,m_cmbb_tiwentongdao
        ,m_cmbb_oem
        ,m_cmbb_ibp
        ,m_cmbb_kexuanmokuai
        ,m_cmbb_usb
        ,m_cmbb_chumoping
        ,m_cmbb_shuchu
        ,m_cmbb_jiluyi
        ,m_cmbb_spo2
        ,m_btn_para_switch
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  23;//11
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
                else if(iCursor == iOkPos -1)
                {
                    do_para_sw_clicked();
                }
                else if((iCursor>=0) &&(iCursor<iOkPos-1))
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
