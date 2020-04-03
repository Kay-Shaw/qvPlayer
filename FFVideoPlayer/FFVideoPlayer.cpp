/*

������

*/

#include "FFVideoPlayer.h"
#include <QFileDialog>
#include "MyFFmpeg.h"
#include <QMessageBox>
#include "AudioPlay.h"
#include <string>
#include <iostream>
#include "VideoThread.h"
#include <QCursor>
#include "AboutDlg.h"
#include "NetStreamThread.h"
//#include "MyLog.h"
#include <QDesktopServices>
#include <stdio.h>
#include<fstream>
#include <QDragEnterEvent>
#include <QMimeData>


using namespace std;

//ȫ�־�̬����ֻ�ڸ�cpp�ļ�����Ч
static bool ispressSlider = false;

static bool g_isPlay = true;
static int g_fastPlay = 1;
int g_NetStream;
static const int EncryptionLen = 10;
FFVideoPlayer::FFVideoPlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    this->setAcceptDrops(true);

	m_Hour = 0;
	m_Min = 0;
	m_Second = 0;
	m_isMute = false;

    player = new QMediaPlayer(this);

	showMaximized(); //�����ʾ   
	setMinimumSize(QSize(800, 512)); //���ô�����С�ߴ�

	//LOG4CPLUS_INFO(MyLog::getInstance()->logger, "Program Start, init UI");
	initUI();

#ifdef _DEBUG
	setWindowTitle("FFVideoPlayer_D");
#else
	setWindowTitle("FFVideoPlayer");
#endif

	startTimer(40);
	allConnect();
}

void FFVideoPlayer::initUI()
{
	//MainWindow����ɫ
	setStyleSheet("background-color: rgb(53, 53, 53);");

	//�˵���ɫ
	ui.menuBar->setStyleSheet("background-color:rgb(53,53,53); border:1px solid gray; color:white; padding: 1px;");

	ui.label_Playtime->clear();
	ui.label_Playtime->setText("00:00:00/00:00:00");

	//������ť��ͼ
	setButtonBackImage(ui.btnPlayVideo, "./Resources/play.png");
	setButtonBackImage(ui.btnSetVolume, "./Resources/volume.png");
	setButtonBackImage(ui.btnFullScreen, "./Resources/fullscreen.png");
	setButtonBackImage(ui.btnCutImage, "./Resources/1xp.png");
    ui.btnFullScreen->hide();
}

void FFVideoPlayer::allConnect()
{
	connect(ui.btnPlayVideo, SIGNAL(clicked()), this, SLOT(slotPlay()));
	connect(ui.timeSlider, SIGNAL(sliderPressed()), this, SLOT(slotSliderPressed()));
	connect(ui.timeSlider, SIGNAL(sliderReleased()), this, SLOT(soltSliderReleased()));

	//�˵�
	connect(ui.action_OpenLocalFiles, SIGNAL(triggered()), this, SLOT(OpenLocalVideo()));
	connect(ui.action_OpenNetStream, SIGNAL(triggered()), this, SLOT(OpenNetStreamDlg()));
	connect(ui.action_About, SIGNAL(triggered()), this, SLOT(PopAboutDlg()));
	connect(ui.action_GetSourceCode, SIGNAL(triggered()), this, SLOT(GetSourceCode()));

	//��������
	connect(ui.sliderVolume, SIGNAL(sliderReleased()), this, SLOT(volumeAdjust()));
	connect(ui.btnSetVolume, SIGNAL(clicked()), this, SLOT(setMute()));

    //��������
    connect(ui.btnCutImage, SIGNAL(clicked()), this, SLOT(fastPlay()));

	connect(&m_NetDlg, SIGNAL(PushStream(QString)), this, SLOT(slotPushStream(QString)));
}
void FFVideoPlayer::PlayLocalVideo(QString filename)
{
    string videoPath = string((const char *)filename.toLocal8Bit()); //QStringתstring
    int n1 = videoPath.find_last_of('/');
    int n2 = videoPath.find_last_of('\0');
    string sname = videoPath.substr(n1 + 1, n2);
    QString qstr = QString(QString::fromLocal8Bit(sname.c_str())); //stringתQString
    this->setWindowTitle(qstr);
    if (!QFile::exists(filename)) {
        QMessageBox::information(this, "err", "file is not exist");
        return;
    }
    int nRet = 0;
    bool bIsEncryption = EncryptionCheck(filename.toLocal8Bit());
    if (bIsEncryption)
    {
        if (m_strLastFileName != videoPath)
        {
            QMessageBox::information(this, "msg", "file decryption, please wait 5s");
            if (!DecryptionFile(filename.toLocal8Bit()))
            {
                QMessageBox::information(this, "err", "decryption file failed,check disk");
                m_strLastFileName = "";
                return;
            }
            m_strLastFileName = videoPath;
        }
        //if (MyFFmpeg::Get()->IsPlaying())
        //{
        delete ui.openGLWidget;
        ui.openGLWidget = nullptr;
        MyFFmpeg::Get()->Stop();
        MyFFmpeg::Get()->m_nTotalPlayTime = 0;
        MyFFmpeg::Get()->m_nCurPlayTime = 0;

        ui.openGLWidget = new VideoWidget(ui.centralWidget);
        ui.openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        ui.openGLWidget->move(0, 0);
        ui.openGLWidget->resize(this->width(), this->height() - 82);
        ui.openGLWidget->setStyleSheet(QString::fromUtf8(""));
        ui.openGLWidget->show();
        //}

        nRet = MyFFmpeg::Get()->Play("cachefile", (void*)this->ui.openGLWidget->winId());

    }
    else
    {
        filename.replace("/", "\\");
        //if (MyFFmpeg::Get()->IsPlaying())
        //{
        delete ui.openGLWidget;
        ui.openGLWidget = nullptr;
        MyFFmpeg::Get()->Stop();
        MyFFmpeg::Get()->m_nTotalPlayTime = 0;
        MyFFmpeg::Get()->m_nCurPlayTime = 0;

        ui.openGLWidget = new VideoWidget(ui.centralWidget);
        ui.openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        ui.openGLWidget->move(0, 0);
        ui.openGLWidget->resize(this->width(), this->height() - 82);
        ui.openGLWidget->setStyleSheet(QString::fromUtf8(""));
        ui.openGLWidget->show();

        //}
        nRet = MyFFmpeg::Get()->Play(filename.toUtf8(), (void*)this->ui.openGLWidget->winId());
    }
    if (-1 == nRet)
    {
        QMessageBox::information(this, "err", "open file failed");
        return;
    }

    MyFFmpeg::Get()->SetVolume(50);
    this->ui.sliderVolume->setValue(50);

    g_isPlay = false;
    slotPlay();
    fastPlayReset();
}
void FFVideoPlayer::OpenLocalVideo()
{
	//LOG4CPLUS_INFO(MyLog::getInstance()->logger, "Open Local Video File");
	QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ����Ƶ�ļ�"));
	if (filename.isEmpty())
	{
		return;
	}

	string videoPath = string((const char *)filename.toLocal8Bit()); //QStringתstring
	int n1 = videoPath.find_last_of('/');
	int n2 = videoPath.find_last_of('\0');
	string sname = videoPath.substr(n1 + 1, n2);
	QString qstr = QString(QString::fromLocal8Bit(sname.c_str())); //stringתQString
	this->setWindowTitle(qstr);
    if (!QFile::exists(filename)) {
        QMessageBox::information(this, "err", "file is not exist");
        return ;
    }
    int nRet = 0;
    bool bIsEncryption = EncryptionCheck(filename.toLocal8Bit());
    if (bIsEncryption)
    {
        if (m_strLastFileName != videoPath)
        {
            QMessageBox::information(this, "msg", "file decryption, please wait 5s");
            if (!DecryptionFile(filename.toLocal8Bit()))
            {
                QMessageBox::information(this, "err", "decryption file failed,check disk");
                m_strLastFileName = "";
                return;
            }
            m_strLastFileName = videoPath;
        }
        //if (MyFFmpeg::Get()->IsPlaying())
        //{
            delete ui.openGLWidget;
            ui.openGLWidget = nullptr;
            MyFFmpeg::Get()->Stop();
            MyFFmpeg::Get()->m_nTotalPlayTime = 0;
            MyFFmpeg::Get()->m_nCurPlayTime = 0;

            ui.openGLWidget = new VideoWidget(ui.centralWidget);
            ui.openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
            ui.openGLWidget->move(0, 0);
            ui.openGLWidget->resize(this->width(), this->height() - 82);
            ui.openGLWidget->setStyleSheet(QString::fromUtf8(""));
            ui.openGLWidget->show();
        //}

        nRet = MyFFmpeg::Get()->Play("cachefile", (void*)this->ui.openGLWidget->winId());

    }
    else
    {
        filename.replace("/", "\\");
        //if (MyFFmpeg::Get()->IsPlaying())
        //{
            delete ui.openGLWidget;
            ui.openGLWidget = nullptr;
            MyFFmpeg::Get()->Stop();
            MyFFmpeg::Get()->m_nTotalPlayTime = 0;
            MyFFmpeg::Get()->m_nCurPlayTime = 0;

            ui.openGLWidget = new VideoWidget(ui.centralWidget);
            ui.openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
            ui.openGLWidget->move(0, 0);
            ui.openGLWidget->resize(this->width(), this->height() - 82);
            ui.openGLWidget->setStyleSheet(QString::fromUtf8(""));
            ui.openGLWidget->show();

        //}
        nRet = MyFFmpeg::Get()->Play(filename.toUtf8(), (void*)this->ui.openGLWidget->winId());
    }
    if (-1 == nRet)
    {
        QMessageBox::information(this, "err", "open file failed");
        return;
    }

    MyFFmpeg::Get()->SetVolume(50);
    this->ui.sliderVolume->setValue(50);

	g_isPlay = false;
	slotPlay();
    fastPlayReset();
}

/**
 * @brief ��ʱ���¼�
 * @param e
 */
void FFVideoPlayer::timerEvent(QTimerEvent *e)
{
    int seconds = MyFFmpeg::Get()->m_nTotalPlayTime;
    m_Hour = seconds / 3600;
    m_Min = (seconds - m_Hour * 3600) / 60;
    m_Second = seconds - m_Hour * 3600 - m_Min * 60;
	int playseconds = MyFFmpeg::Get()->m_nCurPlayTime;
	int hour = playseconds / 3600;
	int min = (playseconds - hour * 3600) / 60;
	int sec = playseconds - hour * 3600 - min * 60;
	char buf[1024] = { 0 };
	sprintf(buf, "%02d:%02d:%2d/%02d:%02d:%2d", hour, min, sec,m_Hour, m_Min, m_Second);
	this->ui.label_Playtime->setText(buf);  //��ǰ����ʱ��

	if (MyFFmpeg::Get()->m_nTotalPlayTime > 0)
	{
		float rate = MyFFmpeg::Get()->m_nCurPlayTime / (float(MyFFmpeg::Get()->m_nTotalPlayTime));

		//ֻ�а����ˣ��Ų���ʾ������
		if (!ispressSlider)
		{
            //int n1 = this->ui.timeSlider->value();
            //if (n1 <= rate)
            //{
                this->ui.timeSlider->setValue(rate * 1000); //������
           // }
		}

		//        if(ui.timeSlider->geometry().contains(this->mapFromGlobal(QCursor::pos())))
		//        {
		//            ui.timeSlider->show();
		//            ui.timeSlider->setValue(rate * 1000); //������
		//        }
		//        else
		//        {
		//            ui.timeSlider->hide();
		//        }
	}
}

/**
 * @brief ��Ӧ���������µ��ź�
 */
void FFVideoPlayer::slotSliderPressed()
{
	ispressSlider = true;
}

/**
 * @brief ��Ӧ����ɿ����������ź�
 */
void FFVideoPlayer::soltSliderReleased()
{
	ispressSlider = false;
	float pos = 0;
	pos = this->ui.timeSlider->value() / static_cast<float>(ui.timeSlider->maximum() + 1); //��0��ʼ�ģ������÷�ĸΪ0
	MyFFmpeg::Get()->SeekTo(pos);
}

/**
 * @brief ������Ƶ
 */
void FFVideoPlayer::slotPlay()
{
	g_isPlay = !g_isPlay;

	if (g_isPlay)
	{
        MyFFmpeg::Get()->Play();
		setButtonBackImage(ui.btnPlayVideo, "./Resources/stop.png");
	}
	else
	{
        MyFFmpeg::Get()->Pause();
		setButtonBackImage(ui.btnPlayVideo, "./Resources/play.png");
	}
}

void FFVideoPlayer::fastPlay()
{
    g_fastPlay++;
    g_fastPlay = g_fastPlay % 3;

    if (0 == g_fastPlay)
    {
        MyFFmpeg::Get()->fastPlay(0.5);
        setButtonBackImage(ui.btnCutImage, "./Resources/05xp.png");
    }
    else if (1 == g_fastPlay)
    {
        MyFFmpeg::Get()->fastPlay(1.0);
        setButtonBackImage(ui.btnCutImage, "./Resources/1xp.png");
    }
    else
    {
        MyFFmpeg::Get()->fastPlay(2.0);
        setButtonBackImage(ui.btnCutImage, "./Resources/2xp.png");
    }
}

void FFVideoPlayer::fastPlayReset()
{
    g_fastPlay = 1;
    setButtonBackImage(ui.btnCutImage, "./Resources/1xp.png");
}

/**
 * @brief ���ڹر�ʱ�Ĳ���
 * @param e
 */
void FFVideoPlayer::closeEvent(QCloseEvent * e)
{
	//�����߳�
	VideoThread::Get()->terminate();
}

//���ڴ�С�����仯ʱ�����ؼ���С��λ�ü���С������
void FFVideoPlayer::resizeEvent(QResizeEvent *e)
{
	if (isFullScreen())
	{
		ui.openGLWidget->move(0, 0);
		ui.openGLWidget->resize(this->width(), this->height());
	}
	else
	{
        if (ui.openGLWidget != nullptr)
        {
            ui.openGLWidget->move(0, 0);
            ui.openGLWidget->resize(this->width(), this->height() - 82);
        }
        if (ui.timeSlider != nullptr)
        {
            ui.timeSlider->move(0, this->height() - 80);
            ui.timeSlider->resize(this->width(), 20);
        }
		ui.label_Playtime->move(5, this->height() - 60);
		ui.btnPlayVideo->move(this->width() / 2 - 15, this->height() - 60);
		ui.btnSetVolume->move(this->width() * 4 / 5, this->height() - 60);
		ui.sliderVolume->move(this->width() * 4 / 5 + 31, this->height() - 60);
		ui.btnFullScreen->move(this->width() - 40, this->height() - 60);
		ui.btnCutImage->move(this->width() / 2 - 15 + 80, this->height() - 60);
	}
}
/**
 * @brief FFVideoPlayer::on_fullScreenBtn_clicked
 *        ȫ����ť
 */
void FFVideoPlayer::on_btnFullScreen_clicked()
{
    return;
	if (!isFullScreen())
	{
		fullShow();
	}
}

/**
 * @brief FFVideoPlayer::mouseDoubleClickEvent
 *        ���˫��
 */
void FFVideoPlayer::mouseDoubleClickEvent(QMouseEvent*)
{
    return;
	if (this->isFullScreen())
	{
		normalShow();
	}
	else
	{
		fullShow();
	}
}

/**
 * @brief ȫ��ʱ������ť����
 */
void FFVideoPlayer::fullShow()
{
	this->showFullScreen();
    //MyFFmpeg::Get()->SetFullscreen(true);
	ui.menuBar->hide();
	ui.timeSlider->hide();
	ui.label_Playtime->hide();
	ui.btnPlayVideo->hide();
	ui.btnSetVolume->hide();
	ui.sliderVolume->hide();
	ui.btnFullScreen->hide();
	ui.btnCutImage->hide();
}

/**
 * @brief ������ʾʱ�����ؼ�����ʾ
 */
void FFVideoPlayer::normalShow()
{

	this->showNormal();
    //MyFFmpeg::Get()->SetFullscreen(false);
	ui.menuBar->show();
	ui.timeSlider->show();
	ui.label_Playtime->show();
	ui.btnPlayVideo->show();
	ui.btnSetVolume->show();
	ui.sliderVolume->show();
	ui.btnFullScreen->show();
	ui.btnCutImage->show();
}

//�˵�--��������
void FFVideoPlayer::OpenNetStreamDlg()
{
	//NetStreamDlg nDlg;
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ����Ƶ�ļ�"));
    if (filename.isEmpty())
    {
        QMessageBox::information(this, "error", "open file failed");
        return;
    }
    if (!QFile::exists(filename)) {
        QMessageBox::information(this, "err", "file is not exist");
        return;
    }
    if (!EncryptionFile(filename.toLocal8Bit()))
    {
        QMessageBox::information(this, "error", "encryption file failed,check disk");
        return;
    }
    QMessageBox::information(this, "msg", "encryption success");
	//m_NetDlg.exec();
}

void FFVideoPlayer::PopAboutDlg()
{
	AboutDlg dlg;
	dlg.exec();
}

//��������
void FFVideoPlayer::volumeAdjust()
{
    int nVolume = ui.sliderVolume->value();
    MyFFmpeg::Get()->SetVolume(nVolume);
}

//��������
void FFVideoPlayer::setMute()
{
	m_isMute = !m_isMute;
	if (m_isMute)
	{
		//MyFFmpeg::Get()->m_VolumeRatio = 0;
        MyFFmpeg::Get()->SetVolume(0);
		setButtonBackImage(ui.btnSetVolume, "./Resources/mute.png");
	}
	else
	{
		//MyFFmpeg::Get()->m_VolumeRatio = 0.5;
         MyFFmpeg::Get()->SetVolume(50);
         ui.sliderVolume->setValue(50);
		setButtonBackImage(ui.btnSetVolume, "./Resources/volume.png");
	}
}

//���ð�ťͼ�꣬��ť��Ĭ�ϴ�С�� 30*30
void FFVideoPlayer::setButtonBackImage(QPushButton *button, QString image)
{  
	QPixmap pixmap(image);
	QPixmap fitpixmap = pixmap.scaled(30, 30).scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	button->setIcon(QIcon(fitpixmap));
	button->setIconSize(QSize(30, 30));
	button->setFlat(true);  //��ť͸��  
	button->setStyleSheet("border: 0px"); //�����߿�
}

void FFVideoPlayer::slotPushStream(QString address)
{
	//LOG4CPLUS_INFO(MyLog::getInstance()->logger, "Push Net Stream");
	g_NetStream = 1;

	setWindowTitle(address);
	NetStreamThread::getInstance()->startPlay(address);
}

bool FFVideoPlayer::DecryptionFile(const char* filename)
{
    char buf[5000];
    FILE* fileSrc = fopen(filename, "rb");
    if (NULL == fileSrc)
    {
        return false;
    }
    FILE* fileDst = fopen("cachefile", "wb+");
    if (NULL == fileDst)
    {
        return false;
    }
    long curpos, length;
    curpos = ftell(fileSrc);
    fseek(fileSrc, 0, SEEK_END);
    length = ftell(fileSrc);
    fseek(fileSrc, length - EncryptionLen, SEEK_SET);
    int nRead = fread(buf, 1, EncryptionLen, fileSrc);
    int nWrite = fwrite(buf, 1, nRead, fileDst);
    if (nWrite != nRead)
    {
        fclose(fileSrc);
        fclose(fileDst);
        return false;
    }
    fseek(fileSrc, EncryptionLen, SEEK_SET);
    do
    {
        nRead = fread(buf, 1, 4096, fileSrc);
        nWrite = fwrite(buf, 1, nRead, fileDst);
        if (nWrite != nRead)
        {
            fclose(fileSrc);
            fclose(fileDst);
            return false;
        }
    } while (nRead);

    fclose(fileSrc);
    fclose(fileDst);
    return true;
}

bool FFVideoPlayer::EncryptionCheck(const char* filename)
{
    char buf[EncryptionLen + 1] = {0};
    FILE* fileSrc = fopen(filename, "rb");
    if (NULL == fileSrc)
    {
        return false;
    }
    int nRead = fread(buf, 1, EncryptionLen, fileSrc);
    if (nRead != EncryptionLen)
    {
        fclose(fileSrc);
        return false;
    }
    std::string strRead = (std::string)buf;
    std::string strEncryption = "mp4boxbase";
    int nsize = strEncryption.length();
    if (strEncryption == strRead)
    {
        return true;
    }

    return false;
}

bool FFVideoPlayer::EncryptionFile(const char* filename)
{
    if (EncryptionCheck(filename))
    {
        return true;
    }
    char buf[EncryptionLen+1];
    ifstream fin(filename, ios::binary);
    fin.seekg(0, ios::beg);
    fin.read(buf, EncryptionLen);
    fin.close();
    ofstream fout(filename, ios::app);
    fout.write(buf, EncryptionLen);
    fout.close();

    fstream fs(filename, ios::binary | ios::out | ios::in);
    //��ת����ͷλ�ý���д�룬����д��
    fs.seekp(0, ios::beg);
    fs.write("mp4boxbase", EncryptionLen);
    fs.close();

    return true;
}

//��ȡԴ����
void FFVideoPlayer::GetSourceCode()
{
	//QDesktopServices::openUrl(QUrl(QString("https://github.com/")));
}

void FFVideoPlayer::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		QMenu menu;
		QAction *ac1 = menu.addAction(QString::fromLocal8Bit("�򿪱�����Ƶ"));
		QAction *ac2 = menu.addAction(QString::fromLocal8Bit("�鿴��Ƶ��Ϣ"));
		connect(ac1, SIGNAL(triggered()), this, SLOT(OpenLocalVideo()));
		menu.exec(QCursor::pos());
	}
}

void FFVideoPlayer::dragEnterEvent(QDragEnterEvent* e)
{
    //���Ϸ��¼�����ɸѡ
    if (true)
    {
        e->acceptProposedAction();	//���У����򲻻�ִ��dropEvent()����
    }
}
void FFVideoPlayer::dropEvent(QDropEvent* e)
{
    //��ȡ�ļ�·�� (QString)
    QList<QUrl> urls = e->mimeData()->urls();
    if (urls.isEmpty()) return;
    QString qStr = urls.first().toLocalFile();
    PlayLocalVideo(qStr);
}
