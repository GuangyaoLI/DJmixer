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
#include <string>
#include<dirent.h>  
#include<sys/stat.h>   
#include<pthread.h>  
#include "MainBusiness.h"

using namespace std;


MainBusiness::MainBusiness(void)
{
	isInitData =false;
}


MainBusiness::~MainBusiness(void)
{
}

void MainBusiness::startGame()
{
	if(!isInitData)
	{
		throw string("void MainBusiness::startGame() ERROR; not isInitData！");
		return;
	}

	while (true)
	{
		bool start =false;
		int playflag1,playflag2, volumflag1, volumflag2;
		string soundpath1,soundpath2,volumpath1,volumpath2;

		soundpath1=m_MeasureCtrl_music1.GetplayPath(playflag1);
		soundpath2=m_MeasureCtrl_music2.GetplayPath(playflag2);
		volumpath1=m_MeasureCtrl_volume1.GetplayPath(volumflag1);
		volumpath2=m_MeasureCtrl_volume2.GetplayPath(volumflag2); 

		if(volumflag1==1 && strcmp(volumpath1.c_str(),volumepath_vec1[0].c_str()))  //关闭按钮
		{
			start=false;
			m_SoundPlay1.stopmusic();
			m_SoundPlay2.stopmusic();
			usleep(100*MS);
			continue; //不进行播放
		}
		else if(volumflag2==1 && strcmp(volumpath2.c_str(),volumepath_vec2[0].c_str())) //开启按钮
		{
			start=true;
		}
		
		if(start)
		{
			//第一种音频控制
			if(playflag1==1)
			{
				m_SoundPlay1.playmusic(soundpath1.c_str());
			}

			//第2种音频控制
			if(playflag2==1)
			{
				m_SoundPlay2.playmusic(soundpath2.c_str());
			}
			//第1种音量
			if(volumflag1==1)
			{
				m_SoundPlay1.sendMsg(volumpath1.c_str());
			}
			//第2种音量
			if(volumflag2==1)
			{
				m_SoundPlay2.sendMsg(volumpath2.c_str());
			}
		}
		usleep(100*MS);

	}
}


void MainBusiness::InitData()
{
	if(wiringPiSetup() == -1)
	{
		throw string("void MainBusiness::InitData();setuo wiringPi failed !");
		return ;
	}

	pinMode(Echo1, INPUT);
	pinMode(Trig1, OUTPUT);
	pinMode(Echo2, INPUT);
	pinMode(Trig2, OUTPUT);
	pinMode(Echo3, INPUT);
	pinMode(Trig3, OUTPUT);
	pinMode(Echo4, INPUT);
	pinMode(Trig4, OUTPUT);


	//初始化参数值
	soundpath_vec1.push_back("DesiJourney.wav");
	soundpath_vec1.push_back("doublebass.wav");
	soundpath_vec1.push_back("MoodyLoop.wav");  //第一个传感器分3段

	musicDistence_vec1.push_back(5);
	musicDistence_vec1.push_back(15);
	musicDistence_vec1.push_back(25);
	musicDistence_vec1.push_back(35);  //要求按从小到大，并多一个

	soundpath_vec2.push_back("TheEnd.mp3");
	soundpath_vec2.push_back("AroundWorld.mp3");
	soundpath_vec2.push_back("Decision.mp3");  //第一个传感器分3段

	musicDistence_vec2.push_back(5);
	musicDistence_vec2.push_back(15);
	musicDistence_vec2.push_back(25);
	musicDistence_vec2.push_back(35);  //要求按从小到大，并多一个


	volumepath_vec1.push_back("exit");
	volumepath_vec1.push_back("1");
	volumepath_vec1.push_back("2");
	volumepath_vec1.push_back("-");
	volumepath_vec1.push_back("+");

	volumeDistence_vec1.push_back(3);
	volumeDistence_vec1.push_back(5);
	volumeDistence_vec1.push_back(7);
	volumeDistence_vec1.push_back(9);
	volumeDistence_vec1.push_back(11);
	volumeDistence_vec1.push_back(13);

	volumepath_vec2.push_back("exit");
	volumepath_vec2.push_back("1");
	volumepath_vec2.push_back("2");
	volumepath_vec2.push_back("-");
	volumepath_vec2.push_back("+");

	volumeDistence_vec2.push_back(3);
	volumeDistence_vec2.push_back(5);
	volumeDistence_vec2.push_back(7);
	volumeDistence_vec2.push_back(9);
	volumeDistence_vec2.push_back(11);
	volumeDistence_vec2.push_back(13);

	///////////////////////////////////////////////////
	//初始化对象参数

	m_MeasureCtrl_music1.Ctrlname ="distance1";
	m_MeasureCtrl_music2.Ctrlname ="distance2";
	m_MeasureCtrl_volume1.Ctrlname ="distance3";
	m_MeasureCtrl_volume2.Ctrlname ="distance4";

	m_MeasureCtrl_music1.SetEcho_Trig(Echo1,Trig1);  //设置引脚
	m_MeasureCtrl_music2.SetEcho_Trig(Echo2,Trig2);
	m_MeasureCtrl_volume1.SetEcho_Trig(Echo3,Trig3);
	m_MeasureCtrl_volume2.SetEcho_Trig(Echo4,Trig4);

	m_MeasureCtrl_music1.SetmusicDistence(musicDistence_vec1);
	m_MeasureCtrl_music2.SetmusicDistence(musicDistence_vec2);
	m_MeasureCtrl_volume1.SetmusicDistence(volumeDistence_vec1);
	m_MeasureCtrl_volume2.SetmusicDistence(volumeDistence_vec2);

	m_MeasureCtrl_music1.Setsoundpath(soundpath_vec1);
	m_MeasureCtrl_music2.Setsoundpath(soundpath_vec2);
	m_MeasureCtrl_volume1.Setsoundpath(volumepath_vec1);
	m_MeasureCtrl_volume2.Setsoundpath(volumepath_vec2);  


	isInitData=true;
}

