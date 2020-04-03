#include "VideoThread.h"
#include "MyFFmpeg.h"
#include "AudioPlay.h"
#include <list>
#include <QSemaphore>

using namespace std;

//static list<AVPacket> g_videos;
//static list<AVPacket> g_audios;
static int g_apts = -1;
const int BufferSize = 44100 * 10000;
int iCurrentRead = 0;
int iCurrentWrite = 0;
char buffer[BufferSize];
QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes;

VideoThread::VideoThread()
{

}


VideoThread::~VideoThread()
{

}

void VideoThread::run()
{
	char out[7680] = { 0 };
    int64_t start_time = 0;
    int64_t CurTime = 0;
    int64_t diff_time = 0;
    int64_t stop_time = 0;
    while (1)
	{
        msleep(10);
		//if (!MyFFmpeg::Get()->m_isPlay)
		//{
  //          //stop_time += 
		//	msleep(10);
		//	continue;
		//}

		//while (g_videos.size() > 0)
		//{
		//	AVPacket pack = g_videos.front();
  // //         if (pack.pts == 0)
  // //         {
  // //             start_time = MyFFmpeg::Get()->GetBaseTime();
  // //             stop_time = 0;
  // //         }
		//	int pts = MyFFmpeg::Get()->GetPts(&pack);

  // //         CurTime = MyFFmpeg::Get()->GetBaseTime();
  // //         diff_time = (CurTime - start_time - stop_time)/1000;
  // //         if (diff_time < pts)
  // //         {
  // //             break;
  // //         }
  // //         if (pts > g_apts)  //不注释这儿, 滑动可能会有问题
		//	//{
		//	//	break;
  // //         }
		//	
		//	MyFFmpeg::Get()->Decode(&pack);
		//	av_packet_unref(&pack);
		//	g_videos.pop_front();
		//}

  //      int free = AudioPlay::Get()->GetFree();

  //      //if (free < 7680)
  //      //{
  //      //    msleep(1);
  //      //    continue;
  //      //}


		////这时视频已经打开了
		//AVPacket pkt = MyFFmpeg::Get()->Read();  //读取视频帧
		//if (pkt.size <= 0)
		//{
		//	msleep(10);
  //          continue;
		//}

		//if (pkt.stream_index == MyFFmpeg::Get()->m_audioStream)
		//{
  //          //if (pkt.pts == 0)
  //          //{
  //          //    iCurrentRead = 0;
  //          //    iCurrentWrite = 0;
  //          //    usedBytes.release();
  //          //    freeBytes.release();
  //          //}
  //      if (free < 7680)
  //      {
  //          msleep(1);
  //          continue;
  //      }
		//	g_apts = MyFFmpeg::Get()->Decode(&pkt);
		//	av_packet_unref(&pkt);
		//	int len = MyFFmpeg::Get()->ToPCM(out);
		//	AudioPlay::Get()->Write(out, len);
		//	continue;
		//}

		//if (pkt.stream_index != MyFFmpeg::Get()->m_videoStream)
		//{
		//	av_packet_unref(&pkt);
		//	continue;
		//}

		//g_videos.push_back(pkt);
	}
}
