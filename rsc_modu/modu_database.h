#ifndef MODU_DATABASE_H
#define MODU_DATABASE_H
#include <QtGui>
#include <QtCore/QTextCodec>
#include <QTranslator>
#include <QTextCodec>
#include <QFont>
#include <QStyle>
#include <QtSql>
#include <cstdlib>

#define DB_PARA_TYPE_BEATRATE                1
#define DB_PARA_TYPE_BREATHRATEECG      2
#define DB_PARA_TYPE_SPO2                           3
#define DB_PARA_TYPE_PULSERATE              4
#define DB_PARA_TYPE_TEMP                   5
#define DB_PARA_TYPE_NIBP                   6
#define DB_PARA_TYPE_IBP1                   7
#define DB_PARA_TYPE_IBP2                   8
#define DB_PARA_TYPE_ANAES                  9

//nibp
enum {
     NIBP_TABLE_VIEW_Id= 0,
     NIBP_TABLE_VIEW_PARAID= 1,
    NIBP_TABLE_VIEW_Date = 2,
    NIBP_TABLE_VIEW_Time = 3,
    NIBP_TABLE_VIEW_SS = 4,
    NIBP_TABLE_VIEW_SZ= 5,
    NIBP_TABLE_VIEW_PJ = 6,
    NIBP_TABLE_DATETIME = 7,
    NIBP_TABLE_ALM1 = 8,
    NIBP_TABLE_ALM2 = 9,
    NIBP_TABLE_ALM3 = 10

};
//BEAT RATE
enum{
    BEATRATE_TABLE_ID,
    BEATRATE_TABLE_PARAID,
    BEATRATE_TABLE_DATE,
    BEATRATE_TABLE_TIME,
    BEATRATE_TABLE_VAL,
    BEATRATE_TABLE_DATETIME,
    BEATRATE_TABLE_ALM
};
enum{
    SPIRE_TABLE_ID,
    SPIRE_TABLE_PARAID,
    SPIRE_TABLE_DATE,
    SPIRE_TABLE_TIME,
    SPIRE_TABLE_VAL,
    SPIRE_TABLE_DATETIME,
    SPIRE_TABLE_ALM,
};
//temp
enum{
    TEMP_TABLE_ID,
    TEMP_TABLE_PARAID,
    TEMP_TABLE_DATE,
    TEMP_TABLE_TIME,
    TEMP_TABLE_VAL1,
    TEMP_TABLE_VAL2,
    TEMP_TABLE_DATETIME,
    TEMP_TABLE_ALM1,
    TEMP_TABLE_ALM2,
};
//spo2
enum{
    SPO2_TABLE_ID,
    SPO2_TABLE_PARAID,
    SPO2_TABLE_DATE,
    SPO2_TABLE_TIME,
    SPO2_TABLE_SPO,
    SPO2_TABLE_PR,
    SPO2_TABLE_DATETIME,
    SPO2_TABLE_ALM1,
    SPO2_TABLE_ALM2,
};
enum{
    IBP_TABLE_ID,
    IBP_TABLE_PARAID,
    IBP_TABLE_DATE,
    IBP_TABLE_TIME,
    IBP_TABLE_SS,
    IBP_TABLE_SZ,
    IBP_TABLE_PJ,
    IBP_TABLE_DATETIME,
    IBP_TABLE_ALM1,
    IBP_TABLE_ALM2,
    IBP_TABLE_ALM3,
};
//anaes
enum{
    ANAES_TABLE_ID,
    ANAES_TABLE_PARAID,
    ANAES_TABLE_DATE,
    ANAES_TABLE_TIME,
    ANAES_TABLE_VAL1,
    ANAES_TABLE_DATETIME,
    ANAES_TABLE_ALM1,
};

class CDatabaseModule: public QObject
{
Q_OBJECT
public:
    CDatabaseModule(QWidget *parent);
public:
    void f_store_para_value(int iParaType, void *);
    void f_store_warning(int iWarningType,double value);
private:
    void f_store_beatrate(int value);
    void f_store_breath_ecg(int value);
    void f_store_spo2(int spo2,int pulserate);
    void f_store_temp(int temp1,int temp2);
    void f_store_nibp(int ss,int sz,int pj);
    void f_store_ibp(int chanel,int ss,int sz,int pj);
    void f_store_anaes(int value);
};

#endif // MODU_DATABASE_H
