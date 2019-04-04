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

#include "subprocess.hpp"

using namespace std;

#define Trig  9
#define Echo  8

int flag =-1;  
int oldflag =-1;

char soundpath1[] ="DesiJourney.wav"; 
char soundpath2[] ="doublebass.wav";
char soundpath3[] ="MoodyLoop.wav";





void ultraInit(void)
{
	pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);
}

float disMeasure(void)
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


int main(void)
{
	
	float dis;
	
	wiringPiSetup();

	if(wiringPiSetup() == -1)
	{
		printf("setuo wiringPi failed !");
		return 1;
	}
	
	ultraInit();

	pid_t pid =-10;  
        //autofile();      
	char *soundpath;

	while(1)
	{
		dis = disMeasure();
		printf("distance = %0.2f cm\n",dis);

		if(dis>=10 && dis<20)
		{
			//soundpath =soundpath1;
			auto p=Popen({"omxplayer","-o","local","DesiJourney.wav"},output{PIPE},input{PIPE});
			flag =1;                
		}
		else if( dis>=20 && dis<30)
		{
			//soundpath =soundpath2;
			auto p=Popen({"omxplayer","-o","local","doublebass.wav"},output{PIPE},input{PIPE});
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
				pid =fork();
				if(pid==0)  
				{
					close(0);
					//printf(soundpath);
				        auto p=Popen({"omxplayer","-o","local",soundpath},output{PIPE},input{PIPE});
					//execlp("/usr/bin/omxplayer","omxplayer", "-o", "local", soundpath,NULL);
					perror("error");
					exit(0);
				}
			}
		}
		else
		{
			if(oldflag!=flag) 
			{
				oldflag =flag;
				kill(pid,9);
				//
				const char* msg = "q";
				p.send(msg, strlen(msg));
				auto res = p.communicate(nullptr, 0);
				std::cout << res.first.buf.data() << std::endl;
				//
				
				if(flag>0)
				{
					pid=fork();
					if(pid ==0)
					{
						close(0);
						//printf(soundpath);
						auto p=Popen({"omxplayer","-o","local",soundpath},output{PIPE},input{PIPE});
						//execlp("/usr/bin/omxplayer","omxplayer", "-o", "local", soundpath,NULL);
						perror("error");
						exit(0);
					}
				}
			}
		}
	
		delay(1000);
		
	}
	return 0;
}
