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

using namespace std;
#include "MeasureCtrl.h"


MeasureCtrl::MeasureCtrl(void)
{
	flag =-1;  
	oldflag =-1;

	soundpath1 ="/DJmixer/DesiJourney.wav"; 
	soundpath2 ="/DJmixer/doublebass.wav";
	soundpath3 ="/DJmixer/MoodyLoop.wav";

}


MeasureCtrl::~MeasureCtrl(void)
{
}



float MeasureCtrl::disMeasure(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float dis;

	digitalWrite(Trig, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig, LOW);

	while(!(digitalRead(Echo) == 1));
	gettimeofday(&tv1, NULL);

	while(!(digitalRead(Echo) == 0));
	gettimeofday(&tv2, NULL);

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	dis = (float)(stop - start) / 1000000 * 34000 / 2;

	return dis;
}

char * MeasureCtrl::GetplayPath(int &playflag)  //playflag 1 播放  0 什么都不做  -1  停止
{
	char *soundpath;
	float dis = disMeasure();
	printf("distance = %0.2f cm\n",dis);
	if(dis>=10 && dis<20)
	{
		soundpath =soundpath1;  
		flag =1;                
	}
	else if( dis>=20 && dis<30)
	{
		soundpath =soundpath2;
		flag =2;
	}
	else if( dis>=30 &&dis<40)
	{
		soundpath =soundpath3;
		flag =3;
	}
	else                    
	{
		soundpath =NULL;
		flag =0;
	}
	if(oldflag <=0)
	{
		oldflag=flag;
		if(flag>0)
		{
			playflag =1;
			return soundpath;
		}
		else
		{
			playflag =0;
			return NULL;
		}
	}
	else
	{
		if(oldflag!=flag) 
		{
			oldflag =flag;
			if(flag<=0)
			{
				playflag =-1;
			}
			else
			{
				playflag =1;
			}
			return soundpath;
		}
		else
		{
			playflag =0;
			return NULL;
		}
	}
}


