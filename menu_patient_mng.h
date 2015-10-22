#ifndef MENU_PATIENT_MNG_H
#define MENU_PATIENT_MNG_H

#include <QtGui>

class CFormPatinetMng : public QMenu
 {
    Q_OBJECT
public:
    QWidget *m_mainform;
    QAction *act_patnt_info;
    QAction *act_patnt_del;
    QAction *act_drug_sum;
    QAction *act_back;
    QPalette pal_backgrund,pal_foregrund;


    CFormPatinetMng(QWidget *parnt );
private slots:
    void do_patnt_info(void);
    void do_patnt_del();
    void do_drug_sum();
    void do_back();
};

#endif // MENU_PATIENT_MNG_H
