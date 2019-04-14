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
	isInitData =false;
}


MainBusiness::~MainBusiness(void)
{
}

void MainBusiness::startGame()
{
	if(!isInitData)
	{
		throw string("void MainBusiness::startGame() ERROR; 没有isInitData！");
		return;
	}

	while (true)
	{
		int playflag1,playflag2, playflag3, volumflag;
		string soundpath1,soundpath2,soundpath3,volumpath;

		soundpath1=m_MeasureCtrl_music1.GetplayPath(playflag1);
		soundpath2=m_MeasureCtrl_music2.GetplayPath(playflag2);
		soundpath3=m_MeasureCtrl_music3.GetplayPath(playflag3);
		volumpath=m_MeasureCtrl_volume.GetplayPath(volumflag); 

		//音量控制
		if(volumflag==-1)
		{
			m_SoundPlay1.stopmusic();
			m_SoundPlay2.stopmusic();
			m_SoundPlay3.stopmusic();
			Setvolume(0);
			usleep(200*MS);
			continue; //不进行播放
		}
		else if(volumflag == 0)
		{
			if(strcmp(volumpath.c_str(),""))
			{
				m_SoundPlay1.stopmusic();
				m_SoundPlay2.stopmusic();
				m_SoundPlay3.stopmusic();
				Setvolume(0);
				usleep(200*MS);
				continue; //不进行播放
			}
		}
		else if(volumflag==1)
		{
			for(int i=0;i<volumepath_vec.size();i++)
			{
				if(strcmp(volumpath.c_str(),volumepath_vec[i].c_str()))
				{
					Setvolume(volume_vec[i]);
					break;
				}
			}
		}
		 //第一种音频控制
		if(playflag1==1)
		{
			m_SoundPlay1.playmusic(soundpath1.c_str());
		}
		else if(playflag1==-1)
		{
			m_SoundPlay1.stopmusic();
		}

		//第2种音频控制
		if(playflag2==1)
		{
			m_SoundPlay2.playmusic(soundpath2.c_str());
		}
		else if(playflag2==-1)
		{
			m_SoundPlay2.stopmusic();
		}

		//第3种音频控制
		if(playflag3==1)
		{
			m_SoundPlay3.playmusic(soundpath3.c_str());
		}
		else if(playflag3==-1)
		{
			m_SoundPlay3.stopmusic();
		}
		usleep(200*MS);

	}
}


void MainBusiness::InitData()
{
	if(wiringPiSetup() == -1)
	{
		throw string("void MainBusiness::InitData();setuo wiringPi failed !");
		return ;
	}


	//初始化参数值
	soundpath_vec1.push_back("/DJmixer/DesiJourney.wav");
	soundpath_vec1.push_back("/DJmixer/doublebass.wav");
	soundpath_vec1.push_back("/DJmixer/MoodyLoop.wav");  //第一个传感器分3段

	musicDistence_vec1.push_back(10);
	musicDistence_vec1.push_back(20);
	musicDistence_vec1.push_back(30);
	musicDistence_vec1.push_back(40);  //要求按从小到大，并多一个

	soundpath_vec2.push_back("/DJmixer/22.wav");
	soundpath_vec2.push_back("/DJmixer/222.wav");
	soundpath_vec2.push_back("/DJmixer/2222.wav");  //第一个传感器分3段

	musicDistence_vec2.push_back(15);
	musicDistence_vec2.push_back(25);
	musicDistence_vec2.push_back(35);
	musicDistence_vec2.push_back(50);  //要求按从小到大，并多一个


	soundpath_vec3.push_back("/DJmixer/333.wav");
	soundpath_vec3.push_back("/DJmixer/3333.wav");  //第一个传感器分2段


	musicDistence_vec3.push_back(18);
	musicDistence_vec3.push_back(36);
	musicDistence_vec3.push_back(54);  //要求按从小到大，并多一个


	volumepath_vec.push_back("40");  //这个的值可以任意设置，不相同就行
	volumepath_vec.push_back("80");

	volume_vec.push_back(40);
	volume_vec.push_back(80);

	volumeDistence_vec.push_back(10);
	volumeDistence_vec.push_back(35);
	volumeDistence_vec.push_back(50);

	///////////////////////////////////////////////////
	//初始化对象参数
	m_MeasureCtrl_music1.SetEcho_Trig(8,9);  //设置引脚
	m_MeasureCtrl_music2.SetEcho_Trig(4,5);
	m_MeasureCtrl_music3.SetEcho_Trig(1,2);
	m_MeasureCtrl_volume.SetEcho_Trig(3,6);

	m_MeasureCtrl_music1.SetmusicDistence(musicDistence_vec1);
	m_MeasureCtrl_music2.SetmusicDistence(musicDistence_vec2);
	m_MeasureCtrl_music3.SetmusicDistence(musicDistence_vec3);
	m_MeasureCtrl_volume.SetmusicDistence(volumeDistence_vec);

	m_MeasureCtrl_music1.Setsoundpath(soundpath_vec1);
	m_MeasureCtrl_music2.Setsoundpath(soundpath_vec2);
	m_MeasureCtrl_music3.Setsoundpath(soundpath_vec3);
	m_MeasureCtrl_volume.Setsoundpath(volumepath_vec);  


	isInitData=true;
}


void MainBusiness::Setvolume(int m_vol)
{
	m_volume.Setvolume(m_vol);
}
