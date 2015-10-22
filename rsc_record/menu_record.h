#ifndef MENU_RECORD_H
#define MENU_RECORD_H
#include <QtGui>

class CMenuRecord : public QMenu
 {
    Q_OBJECT
public:

    QAction *act_qushitu;
    QAction *act_qushibiao;
    QAction *act_alarm;
    QAction *act_nibp;
    QAction *act_boxing;
    QAction *act_return;

    CMenuRecord(QWidget *parnt );
    QWidget * pMainForm;
private slots:
    void slot_do_qushitu(void);
    void slot_do_qushibiao();
    void slot_do_alarm();
    void slot_do_nibp();
    void slot_do_boxing();
    void slot_do_back();
private:
     void keyPressEvent(QKeyEvent *e);
};

#endif // MENU_RECORD_H
