#ifndef MODU_GPIO_H
#define MODU_GPIO_H
#include <QtCore>
#include "gpio_lib.h"
#include "gpio.h"
#define KEY_NUM_KEY1 0
#define KEY_NUM_KEY2 1
#define KEY_NUM_KEY3 2
#define KEY_NUM_KEY4 3
#define KEY_NUM_KEY5 4
#define KEY_NUM_KEY6 5
#define KEY_NUM_COUNTER 6
#define KEY_NUM_CW 7
#define KEY_NUM_CCW 8
#define KEY_NUM_UP 9
#define KEY_NUM_DOWN 10

class CMainForm;
class CGPIOMODU: public QObject
{
    Q_OBJECT
public:
    CGPIOMODU(QWidget * parent);
    CMainForm *pMainForm;
    void f_set_12v_en(bool );
    void f_set_warning_led(bool);
    void f_set_system_led(bool);
    int f_scan_key();
    int f_scan_roll();
private:
    int m_roll_last_stat;
    int m_roo_new_stat;

};

#endif // MODU_GPIO_H
