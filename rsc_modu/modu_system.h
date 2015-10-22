#ifndef MODU_SYSTEM_H
#define MODU_SYSTEM_H
#include <QtCore>
typedef struct stSystemModu_
{
    //
    int m_bed_num; // 0~
    int m_patient_gender; //0=male,1 = female;
    int m_patient_height; //cm
    int m_patient_weight; //kg
    int m_patient_type;//0=成人，1=儿童，2=新生儿
    int m_patient_blood; //0=A,1=B,2=O,3=AB,4=NA
    char m_patient_case_num[128];
    char m_patient_name[128];
    char m_patient_DC_name[128];
    int m_patient_born_year;
    int m_patient_born_month;
    int m_patient_born_date;
    int m_patient_in_year;
    int m_patient_in_month;
    int m_patient_in_date;

}stSystemModu;

class CSystemModu:public QObject
{
    Q_OBJECT
public:
    CSystemModu(QWidget * parent);
    QWidget *pMainForm;


};

#endif // MODU_SYSTEM_H
