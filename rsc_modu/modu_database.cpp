#include <QtGui>
#include <QtSql>
#include <cstdlib>
#include "modu_database.h"
#include "../rsc_warning/glb_warning.h"
#include "rsc_modu/modu_ecg.h"



bool createConnection();
void createFakeData();

CDatabaseModule::CDatabaseModule(QWidget *parent)
{
    /*
    bool existingData = QFile::exists(MONITOR_DATABASE_FILE);
    if (createConnection())
    {
        if (!existingData)
                createFakeData();
    }*/
    f_store_warning(1,30);
    f_store_beatrate(50);
    f_store_breath_ecg(20);
    f_store_spo2(98,120);
    f_store_temp(35.0,36.0);
    f_store_nibp(120,80,90);
    f_store_ibp(1,110,81,91);
    f_store_ibp(2,122,82,92);
    f_store_anaes(76);

}
void CDatabaseModule::f_store_para_value(int iParaType, void *value)
{
    switch(iParaType)
    {

        case DB_PARA_TYPE_BEATRATE :
    {
        stEcgValue val;
        memcpy(&val,value,sizeof(stEcgValue));
        f_store_beatrate(val.m_para_beat_rate);
    }
        break;
        case DB_PARA_TYPE_BREATHRATEECG  :
    {
        stEcgValue val;
        memcpy(&val,value,sizeof(stEcgValue));
        f_store_breath_ecg( val.m_para_ecg_spr);
    }
        break;
        case DB_PARA_TYPE_SPO2     :

        case DB_PARA_TYPE_PULSERATE :
    {
        stSpo2Value val;
        memcpy(&val,value,sizeof(stSpo2Value));
        f_store_spo2(val.m_spo2_value,val.m_pulse_rate);
    }
        break;
        case DB_PARA_TYPE_TEMP  :
    {
        stTempValue val;
        memcpy(&val,value,sizeof(stTempValue));
        f_store_temp(val.m_para_temp1, val.m_para_temp2);
    }
        break;
        case DB_PARA_TYPE_NIBP    :
    {
        stNibpValue val;
        memcpy(&val,value,sizeof(stNibpValue));
        f_store_nibp(val.m_para_nibp_ss, val.m_para_nibp_sz, val.m_para_nibp_pj);
    }
        break;
        case DB_PARA_TYPE_IBP1  :
    {
        //f_store_ibp(int chanel,int ss,int sz,ing pj);
    }
        break;
        case DB_PARA_TYPE_IBP2   :
    {
        //f_store_ibp(int chanel,int ss,int sz,ing pj);
    }
        break;
        case DB_PARA_TYPE_ANAES  :
    {
        //f_store_anaes(int value);
    }
        break;
        default:

         break;
    }
}
void CDatabaseModule::f_store_beatrate(int value)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_beatrate (para_id, para_value,para_time,para_alm_flg,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value, :para_time,:para_alm_flg,:para_date,:para_datetime )");

    query.bindValue(":para_id",DB_PARA_TYPE_BEATRATE);
    query.bindValue(":para_value",value);
    bool flg = false;
    query.bindValue(":para_alm_flg",flg);


    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();


}

void CDatabaseModule::f_store_breath_ecg(int value)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_breathrate (para_id, para_value,para_time,para_alm_flg,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value, :para_time,:para_alm_flg,:para_date,:para_datetime )");

    query.bindValue(":para_id",DB_PARA_TYPE_BREATHRATEECG);
    query.bindValue(":para_value",value);
    bool flg = false;
    query.bindValue(":para_alm_flg",flg);


    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}

void CDatabaseModule::f_store_spo2(int spo2,int pulserate)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_spo2 (para_id, para_value1,para_value2,para_time,para_alm_flg1,para_alm_flg2,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value1, :para_value2,:para_time,:para_alm_flg1,:para_alm_flg2,:para_date,:para_datetime )");

    query.bindValue(":para_id",DB_PARA_TYPE_SPO2);
    query.bindValue(":para_value1",spo2);
    query.bindValue(":para_value2",pulserate);
    bool flg = false;
    query.bindValue(":para_alm_flg1",flg);
    query.bindValue(":para_alm_flg2",flg);

    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}

void CDatabaseModule::f_store_temp(int temp1,int temp2)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_temperature (para_id, para_value1,para_value2,para_time,para_alm_flg1,para_alm_flg2,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value1, :para_value2,:para_time,:para_alm_flg1,:para_alm_flg2,:para_date,:para_datetime )");

    query.bindValue(":para_id",DB_PARA_TYPE_TEMP);
    query.bindValue(":para_value1",temp1);
    query.bindValue(":para_value2",temp2);
    bool flg = false;
    query.bindValue(":para_alm_flg1",flg);
    query.bindValue(":para_alm_flg2",flg);
    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}

void CDatabaseModule::f_store_nibp(int ss,int sz,int pj)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_nibp (para_id, para_value1,para_value2,para_value3,para_date,para_time,para_datetime,para_alm_flg1,para_alm_flg2,para_alm_flg3 ) "
                  "VALUES (:para_id, :para_value1, :para_value2,:para_value3,:para_date,:para_time,:para_datetime,:para_alm_flg1,:para_alm_flg2,:para_alm_flg3 )");

    query.bindValue(":para_id",DB_PARA_TYPE_NIBP);
    query.bindValue(":para_value1",ss);
    query.bindValue(":para_value2",sz);
    query.bindValue(":para_value3",pj);

    bool warningflg = true;

    query.bindValue(":para_alm_flg1",warningflg);
    warningflg = false;
    query.bindValue(":para_alm_flg2",warningflg);
    warningflg = true;
    query.bindValue(":para_alm_flg3",warningflg);

    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}
void CDatabaseModule::f_store_ibp(int chanel,int ss,int sz,int pj)
{
    QSqlQuery query;
    if(chanel  == 1)
    {
    query.prepare("INSERT INTO para_ibp1 (para_id, para_value1,para_value2,para_value3,para_time,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value1, :para_value2,:para_value3,:para_time,:para_date,:para_datetime )");
       query.bindValue(":para_id",DB_PARA_TYPE_IBP1);
    }
    else if(chanel == 2)
    {
        query.prepare("INSERT INTO para_ibp2 (para_id, para_value1,para_value2,para_value3,para_time,para_alm_flg1,para_alm_flg2,para_alm_flg3 ) "
                      "VALUES (:para_id, :para_value1, :para_value2,:para_value3,:para_time,:para_alm_flg1,:para_alm_flg2,:para_alm_flg3 )");
       query.bindValue(":para_id",DB_PARA_TYPE_IBP2);
    }


    query.bindValue(":para_value1",ss);
    query.bindValue(":para_value2",sz);
    query.bindValue(":para_value3",pj);
    bool flg = false;
    query.bindValue(":para_alm_flg1",ss);
    query.bindValue(":para_alm_flg2",sz);
    query.bindValue(":para_alm_flg3",pj);
    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}
void CDatabaseModule::f_store_anaes(int value)
{
    QSqlQuery query;
    query.prepare("INSERT INTO para_anaes (para_id, para_value1,para_time,para_alm_flg1,para_date,para_datetime ) "
                  "VALUES (:para_id, :para_value1, :para_time,:para_alm_flg1,:para_date,:para_datetime )");

    query.bindValue(":para_id",DB_PARA_TYPE_ANAES);
    query.bindValue(":para_value1",value);

    QDateTime time = QDateTime::currentDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    QString sdate = time.toString("yyyy-MM-dd");
    QString stime = time.toString("hh:mm:ss");
    query.bindValue(":para_date",sdate);
    query.bindValue(":para_time",stime);
    query.bindValue(":para_datetime",datetime);
    query.exec();
}
void CDatabaseModule::f_store_warning(int iWarningType,double value)
{
    QSqlQuery query;
    query.prepare("INSERT INTO warning_list (warning_typeid, warning_value,warning_time ) "
                  "VALUES (:warning_typeid, :warning_value, :warning_time )");

    query.bindValue(":warning_typeid",iWarningType);
    query.bindValue(":warning_value",value);

    QDateTime time = QDateTime();

    QString datetime = time.currentDateTime().toString(Qt::TextDate);
    query.bindValue(":warning_time",datetime);
    query.exec();
}



