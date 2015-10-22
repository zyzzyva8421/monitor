#ifndef MENU_SERVE_H
#define MENU_SERVE_H
#include <QtGui>

#define MENU_SERVE_ACT_COUNT 11

class CMenuServe : public QMenu
 {
    Q_OBJECT
public:
    CMenuServe(QWidget *parnt );
    QWidget * pMainForm;
    QAction *act_set[MENU_SERVE_ACT_COUNT];


private slots:
    void  slot_do_xindianjiaozhun();
    void slot_do_tiwentantou();
    void slot_do_louqijiance();
    void slot_do_xueyajiaozhun();
    void slot_do_xueyafuwei();
    void slot_do_yanshimoshi();
    void slot_do_banbenxinxi();
    void slot_do_yonghushezhi();
    void slot_do_yonghupeizhi();
    void slot_do_changjiaweihu();
    void slot_do_return();
private:
    int iCursor;
    bool bCursorSta;

     void keyPressEvent(QKeyEvent *e);
};


#endif // MENU_SERVE_H
