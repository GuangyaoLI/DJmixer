#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/soundcard.h>

#include "volume.h"
using namespace std;


volume::volume(void)
{
	g_oldvol = sys_volume_getvalue();
}


volume::~volume(void)
{
}

/* 静音 */
void volume::sys_volume_mute()
{
	g_oldvol = sys_volume_getvalue();

	sys_volume_setvalue(0);
}

void volume::sys_volume_resume()
{
	sys_volume_setvalue(g_oldvol);
}

/* 加大音量 */
void volume::sys_volume_up()
{
	int vol = sys_volume_getvalue();
	vol += 10;
	sys_volume_setvalue(vol);

}

/* 减少音量 */
void volume::sys_volume_down()
{
	int vol = sys_volume_getvalue();
	vol -= 10;
	sys_volume_setvalue(vol);
}

int volume::sys_volume_setvalue(int vol)
{
	int temp;
	int right, left;
	if(vol > 100){
		vol = 100;
	}
	else if(vol < 0){
		vol = 0;
	}

	right = left = vol;

	int mixerfd = open(MIXER_DEV, O_WRONLY);
	if(mixerfd < 0){
		perror("Error");
		return -1;
	}

	temp = (right << 8) | left;
	ioctl(mixerfd, MIXER_WRITE(SOUND_MIXER_VOLUME), &temp);

	close(mixerfd);

	return 0;
}

/* 获取音量值 */
int volume::sys_volume_getvalue()
{
	int vol;
	int left, right;
	int mixerfd = open(MIXER_DEV, O_RDONLY);
	if(mixerfd < 0){
		perror("Error");
		return -1;
	}

	ioctl(mixerfd, MIXER_READ(SOUND_MIXER_VOLUME), &vol);
	left = vol&0xff;
	right = vol>>8&0xff;

	close(mixerfd);

	return (left+right)/2;
}

void volume::Setvolume(int m_vol)
{
	sys_volume_setvalue(m_vol);
}

