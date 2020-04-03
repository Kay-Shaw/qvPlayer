#ifndef VLCPLAYER_H
#define VLCPLAYER_H
#include"vlc/vlc.h"
#include <QObject>

class VlcPlayer : public QObject
{
    Q_OBJECT
public:

    explicit VlcPlayer(QObject *parent = 0);
    // ����
    //int Play(QString filename, void* hwnd = nullptr);
    int Play(const char* filename, void* hwnd = nullptr);
    //ȥ�ڱ�
    void RemoveBlack();
    // ����
    int Play();
    // ��ͣ
    void Pause();
    // ֹͣ
    void Stop();
    // ��������ΪnVol
    void SetVolume(int nVol);
    //��ȡ����ֵ
    int GetVolume();
    // ����ָ��λ��nPos
    void SeekTo(float nPos);
    // �ļ��Ƿ��
    bool IsOpen();
    // �ļ��Ƿ����ڲ���
    bool IsPlaying();
    // �Ƿ���ͣ
    bool IsPause();
    // ��ȡ�ļ���ǰ���ŵ�λ��
    int GetPos();
    //��ȡ��ʱ��
    int64_t GetTime();
    // ��ȡ����ʱ��
    int64_t GetPlayTime();
    // ���ò���ʱ��
    void SetPlayTime(int64_t time);
    //��ȡ����״̬
    int GetPlayState();
    void fastPlay(float fSpeed);
    //��������
    bool setTrack(int trackIndex);
    //����
    void Release();
    void SetFullscreen(bool bFullscreen);
    int GetFullscreen();
public:
    int m_nTotalPlayTime;
    int m_nCurPlayTime;

signals:
    void playAllTime(int sec);
    void playCurrentTime(int sec);
public slots:

private:
    libvlc_instance_t     *m_pVLC_Inst;                      // VLCʵ��
    libvlc_media_player_t *m_pVLC_Player;            // VLC������
    libvlc_event_manager_t *m_pVLC_eMg;           //VLC�¼�
};

class MyFFmpeg
{
public:
    //����ģʽ��������������ڲ���ʵ�֣������޸�
    static VlcPlayer *Get()
    {
        static VlcPlayer ff;
        return &ff;
    }
};
#endif // VLCPLAYER_H
