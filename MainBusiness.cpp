#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>

#include<string.h>  
#include<dirent.h>    
#include<sys/stat.h>   
#include<pthread.h>  
#include "MainBusiness.h"

using namespace std;


MainBusiness::MainBusiness(void)
{
}


MainBusiness::~MainBusiness(void)
{
}

void MainBusiness::startGame()
{
	while (true)
	{
		int playflag=0;
		soundpath =m_MeasureCtrl.GetplayPath(playflag);
		if(playflag==1)
		{
			m_SoundPlay.playmusic(soundpath);
		}
		else if(playflag==-1)
		{
			m_SoundPlay.stopmusic();
		}
	}
}


void MainBusiness::InitData()
{
	if(wiringPiSetup() == -1)
	{
		printf("setuo wiringPi failed !");
		return ;
	}
	ultraInit();
}

void MainBusiness::ultraInit(void)
{
	pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);
}

void MainBusiness::Setvolume(int m_vol)
{
	m_volume.Setvolume(m_vol);
}
