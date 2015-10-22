#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <alsa/asoundlib.h>
#include "modu_play.h"
#include "rsc_warning/glb_warning.h"
struct WAV_HEADER
{
    char rld[4]; //riff ��־����
    int rLen; 
    char wld[4]; //��ʽ���ͣ�wave��
    char fld[4]; //"fmt"

    int fLen; //sizeof(wave format matex)
    
    short wFormatTag; //�����ʽ
    short wChannels; //������
    int nSamplesPersec ; //����Ƶ��
    int nAvgBitsPerSample;//WAVE�ļ�������С
    short wBlockAlign; //�����
    short wBitsPerSample; //WAVE�ļ�������С
    
    char dld[4]; //��data��
    int wSampleLength; //��Ƶ���ݵĴ�С

} wav_header;



void CPlayThread:: f_play_list(int itype)
{

    //if(argc!=2)
    {
       // printf("Usage:wav-player+wav file name\n");
      //  exit(1);
    }
    if(itype >255)//
    {
        return;
    }

    int nread;
    FILE *fp;
    QString filename = G_WARN_FILE_PATH+g_WarningFile[itype];
    QByteArray ba = filename.toLatin1();
    char *f = ba.data();
    fp=fopen((char *)f,"rb");
    if(fp==NULL)
    {
        //perror("open file failed:\n");
        //exit(1);
        return;
    }
    
    nread=fread(&wav_header,1,sizeof(wav_header),fp);
    //printf("nread=%d\n",nread);
    
    //printf("RIFF ��־%s\n",wav_header.rld);
    //printf("�ļ���СrLen��%d\n",wav_header.rLen);
    //printf("wld=%s\n",wav_header.wld);
    //printf("fld=%s\n",wav_header.fld);
    
   // printf("fLen=%d\n",wav_header.fLen);
    
    //printf("wFormatTag=%d\n",wav_header.wFormatTag);
    //printf("��������%d\n",wav_header.wChannels);
    //printf("����Ƶ�ʣ�%d\n",wav_header.nSamplesPersec);
    //printf("nAvgBitsPerSample=%d\n",wav_header.nAvgBitsPerSample);
    //printf("wBlockAlign=%d\n",wav_header.wBlockAlign);
    //printf("������λ����%d\n",wav_header.wBitsPerSample);
    
   // printf("data=%s\n",wav_header.dld);
    //printf("wSampleLength=%d\n",wav_header.wSampleLength);
    
    set_pcm_play(fp);

}

int CPlayThread::set_pcm_play(FILE *fp)
{
        int rc;
        int ret;
        int size;
        snd_pcm_t* handle; //PCI�豸���
        snd_pcm_hw_params_t* params;//Ӳ����Ϣ��PCM������
        unsigned int val;
        int dir=0;
        snd_pcm_uframes_t frames;
        char *buffer;
        int channels=wav_header.wChannels;
        int frequency=wav_header.nSamplesPersec;
        int bit=wav_header.wBitsPerSample;
        int datablock=wav_header.wBlockAlign;
        unsigned char ch[100]; //�����洢wav�ļ���ͷ��Ϣ
    
    
        
        rc=snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
        if(rc<0)
        {
                //perror("\nopen PCM device failed:");
                //exit(1);
        }


        snd_pcm_hw_params_alloca(&params); //����params�ṹ��
        if(rc<0)
        {
                //perror("\nsnd_pcm_hw_params_alloca:");
                exit(1);
        }
         rc=snd_pcm_hw_params_any(handle, params);//��ʼ��params
        if(rc<0)
        {
                //perror("\nsnd_pcm_hw_params_any:");
                //exit(1);
        }
        rc=snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED); //��ʼ������Ȩ��
        if(rc<0)
        {
                //perror("\nsed_pcm_hw_set_access:");
                //exit(1);

        }

        //����λ��
        switch(bit/8)
        {
        case 1:snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_U8);
                break ;
        case 2:snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
                break ;
        case 3:snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S24_LE);
                break ;

        }
        rc=snd_pcm_hw_params_set_channels(handle, params, channels); //��������,1��ʾ����>����2��ʾ������
        if(rc<0)
        {
               // perror("\nsnd_pcm_hw_params_set_channels:");
                //exit(1);
        }
        val = frequency;
        rc=snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir); //����>Ƶ��
        if(rc<0)
        {
                //perror("\nsnd_pcm_hw_params_set_rate_near:");
                //exit(1);
        }

        rc = snd_pcm_hw_params(handle, params);
        if(rc<0)
        {
        //perror("\nsnd_pcm_hw_params: ");
        //exit(1);
        }

        rc=snd_pcm_hw_params_get_period_size(params, &frames, &dir); /*��ȡ����
����*/
        if(rc<0)
        {
                perror("\nsnd_pcm_hw_params_get_period_size:");
                //exit(1);
        }

        size = frames * datablock; /*4 �������ݿ쳤��*/

        buffer =(char*)malloc(size);
    fseek(fp,58,SEEK_SET); //��λ������������

    while (1)
        {
                memset(buffer,0,sizeof(buffer));
                ret = fread(buffer, 1, size, fp);
                if(ret == 0)
                {
                        //printf("����д�����\n");
                        break;
                }
                 else if (ret != size)
                {
                 }
                // д��Ƶ���ݵ�PCM�豸 
        while(ret = snd_pcm_writei(handle, buffer, frames)<0)
           {
                 usleep(2000); 
                 if (ret == -EPIPE)
                {
                  /* EPIPE means underrun */
                  //fprintf(stderr, "underrun occurred\n");
                  //���Ӳ���������ã�ʹ�豸׼���� 
                  snd_pcm_prepare(handle);
                 }
                 else if (ret < 0)
                 {
                          fprintf(stderr,
                      "error from writei: %s\n",
                      snd_strerror(ret));
                 }
            }

    }
        //snd_pcm_drain(handle);
    msleep(40);
    snd_pcm_drop(handle);
    snd_pcm_close(handle);
    free(buffer);
    return 0;
}
CPlayThread::CPlayThread()
{
    start(QThread::HighPriority);
}
void CPlayThread::addPlay(int  itype)
{

    QMutexLocker locker(&mutex);
    m_playList.enqueue(itype);
    playAdded.wakeOne();
}
void CPlayThread::run()
{
    m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_timer_out()));
    int itype = 0;
    while(1)
    {
        {
            QMutexLocker locker(&mutex);

            if (m_playList.isEmpty())
                playAdded.wait(&mutex);
            itype = m_playList.dequeue();
            //if (transact == EndTransaction)
                //break;
        }

        emit playStarted(itype);

        f_play_list(itype);
        itype = 0;

        {
            QMutexLocker locker(&mutex);

            if (m_playList.isEmpty())
                emit allPlayDone();
        }
    }
    exec();
}
void CPlayThread::slot_timer_out()
{

}
