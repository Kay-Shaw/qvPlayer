/*

����FFmpeg����Ƶ������

��������
	Qt5.12.4 64λ
	FFmpeg4.2.1 Win64
	VS2017
	Win10-64
	unicode����

*/

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FFVideoPlayer.h"
#include <QMediaPlayer>
#include "NetStreamDlg.h"
#include <QWidget>
#include <QTimer>
#include<QTime>
#include <QMediaPlayer>    //����
#include<QWidget>
#include<QMediaPlaylist>       //�����б�
//#include <QVideoWidget>
#include<QVBoxLayout>
#include<QFileInfo>      //�ļ���
#include<QDial>       //����
#include<QMouseEvent>   //����¼�

#include<QListWidgetItem>  //�б��
#include<malloc.h>

class FFVideoPlayer : public QMainWindow
{
	Q_OBJECT

public:
	FFVideoPlayer(QWidget *parent = Q_NULLPTR);

	void timerEvent(QTimerEvent *e);
	void closeEvent(QCloseEvent * e);
	void resizeEvent(QResizeEvent *e);  //���ڷ����仯ʱ
	void mouseDoubleClickEvent(QMouseEvent*);  //˫��ȫ��
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
	void slotPlay(); //��������ͣ
	void slotSliderPressed();
	void soltSliderReleased();
	void on_btnFullScreen_clicked();
	void setMute();  //��������
    void fastPlay();
    void fastPlayReset();

	//�˵�
	void OpenLocalVideo();
    void PlayLocalVideo(QString filename);
	void OpenNetStreamDlg();
	void PopAboutDlg();
	void GetSourceCode();

	//��������
	void volumeAdjust();

	//������
	void slotPushStream(QString address);

    bool DecryptionFile(const char* filename);
    bool EncryptionCheck(const char* filename);
    bool EncryptionFile(const char* filename);

private:
	Ui::FFVideoPlayerClass ui;
	QMediaPlayer    *player;
    //QTimer *timer;
    //QVideoWidget *widget;   //��Ƶ���ſؼ�
    //QVBoxLayout *layout;     //��������
    //QTime time1;            //��ʼ��ֵ
    //QTime time2;            //�ı��ĳ�ʼ��ֵ
    //QDateTime time;

	//��Ƶ��ʱ��
	int m_Hour;
	int m_Min;
	int m_Second;
    std::string m_strLastFileName;

	NetStreamDlg m_NetDlg;
	bool m_isMute;   //�Ƿ���
};
