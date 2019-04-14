//播放音乐类，实现音乐的播放，更新，同一时间只能播放一首音乐，只开通一个播放进程

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>

#include "SoundPlay.h"

using namespace std;


SoundPlay::SoundPlay(void)
{
	child=-1;
	play_state =PLAY_STATUS_STOP;  
}


SoundPlay::~SoundPlay(void)
{
}


int SoundPlay::beginplay(const char *path)
{
	child = fork();
	if(child < 0)
	{
		printf("fork failed...\n");
		return -1;
	}

	if(child == 0)
	{
		execl("./depend/player", "./depend/player", path, NULL);
	}
	return child;
}


/* 播放歌曲 */
int SoundPlay::playmusic(const char *musicname)
{

	if(NULL == musicname)
	{
		if(play_state == PLAY_STATUS_PAUSE)
		{
			kill(child, SIGCONT);//继续播放
			return 0;
		}
		return -1;
	}

	if(play_state != PLAY_STATUS_STOP)
	{
		stopmusic();
		usleep(200 * 1000);
	}

	play_state = PLAY_STATUS_PLAY;
	beginplay(musicname);

	return 0;
}


/* 暂停歌曲 */
int SoundPlay::pausemusic()
{
	if(child > 0 && play_state == PLAY_STATUS_PLAY)
	{
		play_state = PLAY_STATUS_PAUSE;
		kill(child, SIGSTOP);
		return 0;
	}
	return -1;
}

/* 停止播放歌曲  */
int SoundPlay::stopmusic()
{
	if(play_state != PLAY_STATUS_STOP)
	{
		play_state = PLAY_STATUS_STOP;
		kill(child,SIGKILL);

		child = -1;
		return 0;
	}
	return -1;
}
