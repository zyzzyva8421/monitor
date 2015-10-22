#ifndef MODU_PLAY_H
#define MODU_PLAY_H
#include <QtCore>
class CPlayThread: public QThread
{
    Q_OBJECT
public:
    CPlayThread();

    void addPlay(int  itype);
    void f_play_list(int itype);
    QTimer *m_timer;
    int set_pcm_play(FILE *fp);

signals:
    void playStarted(int itype);
    void allPlayDone();

protected:
    void run();

private:
    int currentplay;
    QQueue<int > m_playList;
    QWaitCondition playAdded;
    QMutex mutex;
private slots:
    void slot_timer_out();

};

#endif // MODU_PLAY_H
