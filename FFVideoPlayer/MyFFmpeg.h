#ifndef VLCPLAYER_H
#define VLCPLAYER_H
#include"vlc/vlc.h"
#include <QObject>

class VlcPlayer : public QObject
{
    Q_OBJECT
public:

    explicit VlcPlayer(QObject *parent = 0);
    // 播放
    //int Play(QString filename, void* hwnd = nullptr);
    int Play(const char* filename, void* hwnd = nullptr);
    //去黑边
    void RemoveBlack();
    // 播放
    int Play();
    // 暂停
    void Pause();
    // 停止
    void Stop();
    // 音量设置为nVol
    void SetVolume(int nVol);
    //获取音量值
    int GetVolume();
    // 跳到指定位置nPos
    void SeekTo(float nPos);
    // 文件是否打开
    bool IsOpen();
    // 文件是否正在播放
    bool IsPlaying();
    // 是否暂停
    bool IsPause();
    // 获取文件当前播放的位置
    int GetPos();
    //获取总时长
    int64_t GetTime();
    // 获取播放时间
    int64_t GetPlayTime();
    // 设置播放时间
    void SetPlayTime(int64_t time);
    //获取播放状态
    int GetPlayState();
    void fastPlay(float fSpeed);
    //设置音轨
    bool setTrack(int trackIndex);
    //销毁
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
    libvlc_instance_t     *m_pVLC_Inst;                      // VLC实例
    libvlc_media_player_t *m_pVLC_Player;            // VLC播放器
    libvlc_event_manager_t *m_pVLC_eMg;           //VLC事件
};

class MyFFmpeg
{
public:
    //单例模式，对象的销毁用内部类实现，后续修改
    static VlcPlayer *Get()
    {
        static VlcPlayer ff;
        return &ff;
    }
};
#endif // VLCPLAYER_H
