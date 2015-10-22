#ifndef MENU_ALARM_LIMIT_H
#define MENU_ALARM_LIMIT_H
#include <QtGui>

class CMenuAlarmLimit : public QMenu
 {
    Q_OBJECT
public:
    CMenuAlarmLimit(QWidget *parnt );
    QWidget * pMainForm;
    QAction *act_set[10];
    bool eventFilter(QObject *, QEvent *);
private slots:
    void slot_do_alm_ecg();
    void slot_do_alm_spo();
    void slot_do_alm_nibp();
    void slot_do_alm_spire();
    void slot_do_alm_temp();
    void slot_do_alm_mashen();
    void slot_do_alm_ibp();
    void slot_do_alm_co2();
    void slot_do_alm_default();
    void slot_do_alm_return();
private:
     void keyPressEvent(QKeyEvent *e);
 };


#endif // MENU_ALARM_LIMIT_H
