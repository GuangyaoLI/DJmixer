//���������࣬ʵ�����ֵĲ��ţ����£�ͬһʱ��ֻ�ܲ���һ�����֣�ֻ��ͨһ�����Ž���

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


/* ���Ÿ��� */
int SoundPlay::playmusic(const char *musicname)
{

	if(NULL == musicname)
	{
		if(play_state == PLAY_STATUS_PAUSE)
		{
			kill(child, SIGCONT);//��������
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


/* ��ͣ���� */
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

/* ֹͣ���Ÿ���  */
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
