#include "modu_gpio.h"
#include "mainform.h"
#include "gpio.h"
CGPIOMODU::CGPIOMODU(QWidget * parent)
{
    pMainForm = (CMainForm *)parent;
    gpio_init();
    m_roll_last_stat  = 0;
    m_roo_new_stat = 0;

}
// en = 0 关闭电源，en = 1开启电源
void CGPIOMODU::f_set_12v_en(bool en)
{
    gpio_output(5,en);
}

void CGPIOMODU::f_set_warning_led(bool en)
{
    gpio_output(1,en);
    gpio_output(2,en);
    gpio_output(3,en);
}

void CGPIOMODU::f_set_system_led(bool en)
{
    gpio_output(0,en);
}
int CGPIOMODU::f_scan_key()
{
    int ret = -1;
    for( unsigned int i = 0;i<7;i++)
    {
        if(gpio_intput(i) == 0)
        {
            ret = i;
            ///QString key = "KEY %1";
            //pMainForm->TextLabel_bar_alarm_II->setText(key.arg(i));
            return ret;

        }
    }

    return ret;

}
int CGPIOMODU::f_scan_roll()
{
    int ret = -1;
    bool cw = 0;
    bool ccw = 0;
    QString key = "ROLL %1 ROOL %2 stat%3";
    cw = gpio_intput(KEY_NUM_CW);
    ccw = gpio_intput(KEY_NUM_CCW);

    if(cw != ccw )
    {

        if(cw != m_roll_last_stat)
        {
            pMainForm->TextLabel_bar_alarm_II->setText(key.arg(cw).arg(ccw).arg(m_roll_last_stat));
            if(cw != m_roo_new_stat)
            {
                m_roo_new_stat = cw;
                ret = KEY_NUM_UP;
            }
            else
            {
                ret = -1;
            }
        }
        else
        {
            pMainForm->TextLabel_bar_alarm_II->setText(key.arg(cw).arg(ccw).arg(m_roll_last_stat));
            if(ccw != m_roo_new_stat)
            {
                m_roo_new_stat = ccw;
                ret = KEY_NUM_DOWN;
            }
            else
            {
                ret = -1;
            }
        }
    }
    else
    {

        m_roo_new_stat = m_roll_last_stat = cw;
         ret = -1;
    }
    return ret;
}
