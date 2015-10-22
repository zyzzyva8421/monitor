#ifndef MENU_SET_H
#define MENU_SET_H
#include <QtGui>

class CMenuSet : public QMenu
 {
    Q_OBJECT
public:
    CMenuSet(QWidget *parnt );
    QAction *act_set[17];

private:
    QWidget *pMainForm;
private slots:
    void slot_do_set_color();
    void slot_do_set_alarm();
    void slot_do_set_record();
    void slot_do_set_screen_layout();
    void slot_do_set_time();
    void slot_do_set_others();
    void slot_do_set_ecg();
    void slot_do_set_spo();
    void slot_do_set_nibp();
    void slot_do_set_spire();
    void slot_do_set_temp();
    void slot_do_set_ibp();
    void slot_do_set_co2();
    void slot_do_set_eeg();
    void slot_do_set_mashen();
    void slot_do_set_default();
    void slot_do_set_return();
private:
     void keyPressEvent(QKeyEvent *e);
};

#endif // MENU_SET_H
