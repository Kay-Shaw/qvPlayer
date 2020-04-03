/*

基于FFmpeg的视频播放器

开发环境
	Qt5.12.4 64位
	FFmpeg4.2.1 Win64
	VS2017
	Win10-64
	unicode编码

*/

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FFVideoPlayer.h"
#include <QMediaPlayer>
#include "NetStreamDlg.h"
#include <QWidget>
#include <QTimer>
#include<QTime>
#include <QMediaPlayer>    //播放
#include<QWidget>
#include<QMediaPlaylist>       //播放列表
//#include <QVideoWidget>
#include<QVBoxLayout>
#include<QFileInfo>      //文件打开
#include<QDial>       //音量
#include<QMouseEvent>   //鼠标事件

#include<QListWidgetItem>  //列表框
#include<malloc.h>

class FFVideoPlayer : public QMainWindow
{
	Q_OBJECT

public:
	FFVideoPlayer(QWidget *parent = Q_NULLPTR);

	void timerEvent(QTimerEvent *e);
	void closeEvent(QCloseEvent * e);
	void resizeEvent(QResizeEvent *e);  //窗口发生变化时
	void mouseDoubleClickEvent(QMouseEvent*);  //双击全屏
	void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);

private:
	void fullShow();
	void normalShow();
	void initUI();
	void allConnect();
	void setButtonBackImage(QPushButton *button, QString image);

private slots:
	void slotPlay(); //播放与暂停
	void slotSliderPressed();
	void soltSliderReleased();
	void on_btnFullScreen_clicked();
	void setMute();  //静音设置
    void fastPlay();
    void fastPlayReset();

	//菜单
	void OpenLocalVideo();
    void PlayLocalVideo(QString filename);
	void OpenNetStreamDlg();
	void PopAboutDlg();
	void GetSourceCode();

	//音量调节
	void volumeAdjust();

	//网络流
	void slotPushStream(QString address);

    bool DecryptionFile(const char* filename);
    bool EncryptionCheck(const char* filename);
    bool EncryptionFile(const char* filename);

private:
	Ui::FFVideoPlayerClass ui;
	QMediaPlayer    *player;
    //QTimer *timer;
    //QVideoWidget *widget;   //视频播放控件
    //QVBoxLayout *layout;     //布局设置
    //QTime time1;            //初始话值
    //QTime time2;            //改变后的初始话值
    //QDateTime time;

	//视频总时间
	int m_Hour;
	int m_Min;
	int m_Second;
    std::string m_strLastFileName;

	NetStreamDlg m_NetDlg;
	bool m_isMute;   //是否静音
};
