#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <qapplication.h>
#include <qtextcodec.h>
#include <qtextstream.h>
#include <qtranslator.h>
#include <qwidget.h>
#include <qnamespace.h>
#include <QtGui>
#include <QtCore/QTextCodec>
#include <QTranslator>
#include <QTextCodec>
#include <QFont>
#include <QStyle>
#include <QtGui>
#include <QtSql>
#include <cstdlib>
#include <QSound>
#include "rsc_modu/modu_gpio.h"
#include "mainform.h"
#include "rsc_warning/glb_warning.h"
#include "keyboard_context.h"
#include <QSound>
#define MONITOR_DATABASE_FILE "/home/data/database/monitor.dat"

int keyscan(void);
void createFakeData();
bool createConnection();
int main(int argc, char* argv[])
{

    //keyscan();
    QApplication::setStyle(new QCleanlooksStyle );
    QApplication app(argc, argv);

    KeyboardContext *ic = new KeyboardContext;
    app.setInputContext(ic);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb2312"));
    //Q_INIT_RESOURCE(findfile);
    app.setFont( QFont( "wenquanyi" , 12, 50 ) );
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    bool existingData = QFile::exists(MONITOR_DATABASE_FILE);
    if (createConnection())
    {
        if (!existingData)
                createFakeData();
    }

    QSound bells("/home/data/wav/heart.wav");
    //if(bells.isAvailable())
    {
        bells.play();
    }
    CMainForm form;
    form.show();
 //   form.f_set_big_font_layout();
 //   form.f_set_standard_layout();

/*
    QFile inputFile;
      inputFile.setFileName("/home/data/wav/heart.wav");
      inputFile.open(QIODevice::ReadOnly);

      QAudioFormat format;
      format.setFrequency(11025);
      format.setChannels(1);
      format.setSampleSize(8);
      format.setCodec("audio/pcm");
      format.setByteOrder(QAudioFormat::LittleEndian);
      format.setSampleType(QAudioFormat::UnSignedInt);
      QAudioOutput *audio = new QAudioOutput( format, 0);

      audio->start(&inputFile);
*/
      return app.exec();
}
void createFakeData()
{

    QSqlQuery query;
    query.exec("DROP TABLE warning_list");  //报警列表
    query.exec("DROP TABLE warning_type"); //报警类型
    query.exec("DROP TABLE para_list"); //参数列表
    query.exec("DROP TABLE para_beatrate"); //心率参数
    query.exec("DROP TABLE para_st"); //ST参数
    query.exec("DROP TABLE para_breathrate");//呼吸率参数
    query.exec("DROP TABLE para_spo2");//血氧参数
    query.exec("DROP TABLE para_pulserate");//脉率参数
    query.exec("DROP TABLE para_temperature");//体温参数
    query.exec("DROP TABLE para_nibp");//无创血压参数
    query.exec("DROP TABLE para_ibp1");//有创血压1参数
    query.exec("DROP TABLE para_ibp2");//有创血压1参数
    query.exec("DROP TABLE para_anaes");//麻醉参数



    //创建报警类型表
    query.exec("CREATE TABLE warning_type ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "warning_typeid INTEGER NOT NULL, "
               "warning_name VARCHAR(40) NOT NULL,"
               "warning_pri INTEGER NOT NULL)");



    //创建报警列表
    query.exec("CREATE TABLE warning_list ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "warning_time DATETIME NOT NULL,"
               "warning_value FLOAT(6,2) NOT NULL, "
               "warning_typeid INTEGER NOT NULL, "
                "para_id INTEGER NOT NULL, "
               "FOREIGN KEY (warning_typeid) REFERENCES warning_type)");
    //创建参数列表
    query.exec("CREATE TABLE para_list ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "warning_time DATETIME NOT NULL, "
               "para_name VARCHAR(40) NOT NULL, "
               "para_id INTEGER NOT NULL, "
               "warning_typeid INTEGER NOT NULL, "

               "FOREIGN KEY (warning_typeid) REFERENCES warning_type)");


    //创建心率参数值表
    query.exec("CREATE TABLE para_beatrate ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "para_id INTEGER NOT NULL, "
               "para_date DATE NOT NULL, "
               "para_time TIME NOT NULL, "

               "para_value INTEGER NOT NULL, "
               "para_datetime DATETIME NOT NULL, "
               "para_alm_flg INTEGER NOT NULL, "

               "FOREIGN KEY (para_id) REFERENCES para_list)");
    //创建ST参数值表
    query.exec("CREATE TABLE para_beatrate ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "para_id INTEGER NOT NULL, "
               "para_date DATE NOT NULL, "
               "para_time TIME NOT NULL, "

               "para_value1 INTEGER NOT NULL, "
               "para_value2 INTEGER NOT NULL, "
               "para_datetime DATETIME NOT NULL, "
               "para_alm_flg1 INTEGER NOT NULL, "
                "para_alm_flg2 INTEGER NOT NULL, "
               "FOREIGN KEY (para_id) REFERENCES para_list)");
    //创建呼吸参数值表
    query.exec("CREATE TABLE para_breathrate ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "para_id INTEGER NOT NULL, "
               "para_date DATE NOT NULL, "
               "para_time TIME NOT NULL, "

               "para_value FLOAT(6,2) NOT NULL, "
                "para_datetime DATETIME NOT NULL, "
               "para_alm_flg INTEGER NOT NULL, "

               "FOREIGN KEY (para_id) REFERENCES para_list)");
    //创建体温参数值表
    query.exec("CREATE TABLE para_temperature ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "para_id INTEGER NOT NULL, "
               "para_date DATE NOT NULL, "
               "para_time TIME NOT NULL, "

               "para_value1 FLOAT(6,2) NOT NULL, "
               "para_value2 FLOAT(6,2) NOT NULL, "
                "para_datetime DATETIME NOT NULL, "
               "para_alm_flg1 INTEGER NOT NULL, "
               "para_alm_flg2 INTEGER NOT NULL, "
               "FOREIGN KEY (para_id) REFERENCES para_list)");
    //创建血氧\脉率参数值表
    query.exec("CREATE TABLE para_spo2 ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "para_id INTEGER NOT NULL, "
               "para_date DATE NOT NULL, "
               "para_time TIME NOT NULL, "

               "para_value1 INTEGER NOT NULL, "
               "para_value2 INTEGER NOT NULL, "
                "para_datetime DATETIME NOT NULL, "
               "para_alm_flg1 INTEGER NOT NULL, "
               "para_alm_flg2 INTEGER NOT NULL, "
               "FOREIGN KEY (para_id) REFERENCES para_list)");
    //创建无创血压参数值表
    query.exec("CREATE TABLE para_nibp ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "para_id INTEGER NOT NULL, "
               "para_date DATE NOT NULL, "
               "para_time TIME NOT NULL, "
               "para_value1 INTEGER NOT NULL, "
               "para_value2 INTEGER NOT NULL, "
               "para_value3 INTEGER NOT NULL, "
               "para_datetime DATETIME NOT NULL, "
               "para_alm_flg1 INTEGER NOT NULL, "
               "para_alm_flg2 INTEGER NOT NULL, "
               "para_alm_flg3 INTEGER NOT NULL, "

               "FOREIGN KEY (para_id) REFERENCES para_list)");
    //创建有创血压参数值表
    query.exec("CREATE TABLE para_ibp1 ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "para_id INTEGER NOT NULL, "
               "para_date DATE NOT NULL, "
               "para_time TIME NOT NULL, "

               "para_value1 FLOAT(6,2) NOT NULL, "
               "para_value2 FLOAT(6,2) NOT NULL, "
               "para_value3 FLOAT(6,2) NOT NULL, "
                "para_datetime DATETIME NOT NULL, "
               "para_alm_flg1 INTEGER NOT NULL, "
               "para_alm_flg2 INTEGER NOT NULL, "
               "para_alm_flg3 INTEGER NOT NULL, "
               "FOREIGN KEY (para_id) REFERENCES para_list)");
    query.exec("CREATE TABLE para_ibp2 ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "para_id INTEGER NOT NULL, "
               "para_date DATE NOT NULL, "
               "para_time TIME NOT NULL, "

               "para_value1 FLOAT(6,2) NOT NULL, "
               "para_value2 FLOAT(6,2) NOT NULL, "
               "para_value3 FLOAT(6,2) NOT NULL, "
                "para_datetime DATETIME NOT NULL, "
               "para_alm_flg1 INTEGER NOT NULL, "
               "para_alm_flg2 INTEGER NOT NULL, "
               "para_alm_flg3 INTEGER NOT NULL, "
               "FOREIGN KEY (para_id) REFERENCES para_list)");
    //创建麻醉深度参数值表
    query.exec("CREATE TABLE para_anaes ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "para_id INTEGER NOT NULL, "
               "para_date DATE NOT NULL, "
               "para_time TIME NOT NULL, "

               "para_value1 INTEGER NOT NULL, "
                "para_datetime DATETIME NOT NULL, "
               "para_alm_flg1 INTEGER NOT NULL, "

               "FOREIGN KEY (para_id) REFERENCES para_list)");


    //插入warning类型列表
    query.prepare("INSERT INTO warning_type (warning_typeid, warning_name,warning_pri ) "
                  "VALUES (:warning_typeid, :warning_name, :warning_pri )");

/*
    for(int i = 0; i<G_WARN_MAX_COUNT;i++)
    {
        if(!g_WarningName[i].isEmpty())
        {
            query.bindValue(":warning_typeid",g_WarningCode[i]);
            query.bindValue(":warning_name",(g_WarningName[i]));
            query.bindValue(":warning_pri",g_WarningPri[i]);
            query.exec();
        }
    }*/
}
bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(MONITOR_DATABASE_FILE);
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
    return true;
}

