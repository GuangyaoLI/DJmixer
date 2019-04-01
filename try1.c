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


using namespace std;

#define Trig  9//0
#define Echo  8//1
#define FIFO    "fifo"  

int fd;    
int my_lock=0;//发送命令标志位   

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

void send_cmd(char *cmd)//通过有名管道向mplayer发送命令   
{   
	if((write(fd,cmd,strlen(cmd)))!=strlen(cmd))   
	{   
		perror("write cmd");   
	}   
}   

void *disMeasure_pthread()   
{   
	float dis=0; 
	char *soundpath;
	while(1)   
	{   
		dis = disMeasure();
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
				my_lock=0;
				send_cmd(soundpath);
			}
		}
		else
		{
			if(oldflag!=flag) 
			{
				oldflag =flag;
				if(flag>0)
				{
					my_lock=0;
					send_cmd(soundpath);
				}
				if(flag==0)
				{
					if(my_lock==0)
					{
						my_lock=1;
						send_cmd("pause\n"); 
					}
				}
			} 
		}
	}   
	return NULL;   
}   


int main(void)
{
	wiringPiSetup();

	if(wiringPiSetup() == -1)
	{
		printf("setuo wiringPi failed !");
		return 1;
	}

	ultraInit();

	pid_t pid;  
	unlink(FIFO);//如果管道存在，先删除   
	if(mkfifo("fifo",IPC_CREAT|0x744)==-1)//创建有名管道   
	{   
		perror("mkfifo");   
		exit(1);   
	}   
	if((pid=fork())==-1)   
	{   
		perror("fork");   
		exit(1);   
	}   
	else if(pid==0)//在子进程中播放歌曲   
	{   
		char song[SONG_CHNUM];     
		execlp("./mplayer","","-ac","mad","-slave","-quiet","-input","file=fifo",song,NULL);

	}   
	else if(pid>0)   
	{          
	pthread_t tid_disMeasure;   
	usleep(500*MS);//等待让歌曲播放之后在获取信息   
	if((fd=open(FIFO,O_RDWR))==-1)   
	{   
		perror("open");   
		exit(1);   
	}   
	pthread_create(&tid_disMeasure,NULL,disMeasure_pthread,NULL);//创建检测线程   

	pthread_join(tid_disMeasure,NULL); //等待子线程  
}
