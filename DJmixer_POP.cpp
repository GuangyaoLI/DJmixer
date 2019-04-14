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
using namespace subprocess;

#define Trig1  9
#define Echo1  8
#define Trig2  2
#define Echo2  0
#define Trig3  13
#define Echo3  12
#define Trig4  11
#define Echo4  10

int flag =-1;
int sub1 =0;
int sub2 =0;

char soundpath1[] ="DesiJourney.wav"; 
char soundpath2[] ="doublebass.wav";
char soundpath3[] ="MoodyLoop.wav";

char soundpath4[] ="TheEnd.mp3"; 
char soundpath5[] ="AroundWorld.mp3";
char soundpath6[] ="Decision.mp3";



void ultraInit(void)
{
	pinMode(Echo1, INPUT);
	pinMode(Trig1, OUTPUT);
	pinMode(Echo2, INPUT);
	pinMode(Trig2, OUTPUT);
	pinMode(Echo3, INPUT);
	pinMode(Trig3, OUTPUT);
	pinMode(Echo4, INPUT);
	pinMode(Trig4, OUTPUT);
}

float disMeasure(int Trig, int Echo)
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
	
	float dis1,dis2,dis3,dis4;
	
	wiringPiSetup();

	if(wiringPiSetup() == -1)
	{
		printf("setuo wiringPi failed !");
		return 1;
	}
	
	ultraInit();
	
	pid_t pid =-10;
     
	char *path1;
	char *path2;
	
	const char* msgq = "q";
	const char* msgh = "+";
	const char* msgl = "-";
	const char* msgs = "1";
	const char* msgf = "2";
	
	//////Initial music
	auto p=Popen({"omxplayer","-o","local","dingdong.mp3"},output{PIPE},input{PIPE});
	auto q=Popen({"omxplayer","-o","local","dingdong.mp3"},output{PIPE},input{PIPE});
	
	//dis1 = disMeasure(Trig1,Echo1);
	//cout << "distance1 = " << dis1 << " cm." << endl;
	//dis2 = disMeasure(Trig2,Echo2);
	//cout << "distance2 = " << dis2 << " cm." << endl;
	dis3 = disMeasure(Trig3,Echo3);
	cout << "distance3 = " << dis3 << " cm." << endl;
	dis4 = disMeasure(Trig4,Echo4);
	cout << "distance4 = " << dis4 << " cm." << endl;
	
	int start =0;
	
	if(dis3>=11 && dis3<13)   //off
	{
		start =0;
	}
	else if(dis4>=11 && dis4<13)  //on
	{
		start =1;
	}
	
	while(start)
	{
		/////////////////////////////////////////////////////////////////////////////////sound1
		if(p.poll()==0 && sub1==0)
		{
		sub1=1;
		pid=fork();
		if(pid==0)
		{
			close(0);
			while(1){
			dis1 = disMeasure(Trig1,Echo1);
			cout << "distance1 = " << dis1 << " cm." << endl;
			
			if(dis1>=10 && dis1<20)
			{
				path1 =soundpath1;
				auto p=Popen({"omxplayer","-o","local",path1},output{PIPE},input{PIPE});
				flag =1;	
				
				while(flag)
				{
					dis1 = disMeasure(Trig1,Echo1);
					cout << "distance1 = " << dis1 << " cm." << endl;
					dis3 = disMeasure(Trig3,Echo3);
					cout << "distance3 = " << dis3 << " cm." << endl;
					delay(1000);
					
					if(dis1>=20 && dis1<40)
					{
						//const char* msg = "q";
						p.send(msgq, strlen(msgq));
						auto res = p.communicate(nullptr, 0);
						std::cout << res.first.buf.data() << std::endl;
						flag =0;
					}
					if(dis3>=3 && dis3<5)
					{
						//const char* msg = "1";
						p.send(msgs, strlen(msgs));
					}
					else if(dis3>=5 && dis3<7)
					{
						//const char* msg = "2";
						p.send(msgf, strlen(msgf));
					}
					else if(dis3>=7 && dis3<9)
					{
						//const char* msg = "-";
						p.send(msgl, strlen(msgl));
					}
					else if(dis3>=9 && dis3<11)
					{
						//const char* msg = "+";
						p.send(msgh, strlen(msgh));
					}
				}
			}
		else if( dis1>=20 && dis1<30)
		{
				path1 =soundpath2;
				auto p=Popen({"omxplayer","-o","local",path1},output{PIPE},input{PIPE});
				flag =1;
			
				while(flag)
				{
					dis1 = disMeasure(Trig1,Echo1);
					cout << "distance1 = " << dis1 << " cm." << endl;
					dis3 = disMeasure(Trig3,Echo3);
					cout << "distance3 = " << dis3 << " cm." << endl;
					delay(1000);
					
					if((dis1>=10 && dis1<20)||(dis1>=30 && dis1<40))
					{
						//const char* msg = "q";
						p.send(msgq, strlen(msgq));
						auto res = p.communicate(nullptr, 0);
						std::cout << res.first.buf.data() << std::endl;
						flag =0;
					}
					if(dis3>=3 && dis3<5)
					{
						//const char* msg = "1";
						p.send(msgs, strlen(msgs));
					}
					else if(dis3>=5 && dis3<7)
					{
						//const char* msg = "2";
						p.send(msgf, strlen(msgf));
					}
					else if(dis3>=7 && dis3<9)
					{
						//const char* msg = "-";
						p.send(msgl, strlen(msgl));
					}
					else if(dis3>=9 && dis3<11)
					{
						//const char* msg = "+";
						p.send(msgh, strlen(msgh));
					}
				}

		}
		else if( dis1>=30 &&dis1<40)
		{
				path1 =soundpath3;
				auto p=Popen({"omxplayer","-o","local",path1},output{PIPE},input{PIPE});
				flag =1;

				while(flag)
				{
					dis1 = disMeasure(Trig1,Echo1);
					cout << "distance1 = " << dis1 << " cm." << endl;
					dis3 = disMeasure(Trig3,Echo3);
					cout << "distance3 = " << dis3 << " cm." << endl;
					delay(1000);
					
					if(dis1>=10 && dis1<30)
					{
						//const char* msg = "q";
						p.send(msgq, strlen(msgq));
						auto res = p.communicate(nullptr, 0);
						std::cout << res.first.buf.data() << std::endl;
						flag =0;
					}
					if(dis3>=3 && dis3<5)
					{
						//const char* msg = "1";
						p.send(msgs, strlen(msgs));
					}
					else if(dis3>=5 && dis3<7)
					{
						//const char* msg = "2";
						p.send(msgf, strlen(msgf));
					}
					else if(dis3>=7 && dis3<9)
					{
						//const char* msg = "-";
						p.send(msgl, strlen(msgl));
					}
					else if(dis3>=9 && dis3<11)
					{
						//const char* msg = "+";
						p.send(msgh, strlen(msgh));
					}
				}
		}delay(1000);}
		perror("error");
		exit(0);
		}
		}
		
		/////////////////////////////////////////////////////////////////////////////////sound2
		if(q.poll()==0 && sub2==0)
		{
			sub2=1;
			pid=fork();
			if(pid==0)
			{
				close(0);
				while(1){
				dis2 = disMeasure(Trig2,Echo2);
				cout << "distance2 = " << dis2 << " cm." << endl;
				
			if(dis2>=10 && dis2<20)
			{

				path2 =soundpath4;
				auto q=Popen({"omxplayer","-o","local",path2},output{PIPE},input{PIPE});
				flag =1;
			
				while(flag)
				{
					dis2 = disMeasure(Trig2,Echo2);
					cout << "distance2 = " << dis2 << " cm." << endl;
					dis4 = disMeasure(Trig4,Echo4);
					cout << "distance4 = " << dis4 << " cm." << endl;
					delay(1000);
					
					if(dis2>=20 && dis2<40)
					{
						//const char* msg = "q";
						q.send(msgq, strlen(msgq));
						auto res = q.communicate(nullptr, 0);
						//std::cout << res.first.buf.data() << std::endl;
						flag =0;
					}
					if(dis4>=3 && dis4<5)
					{
						//const char* msg = "1";
						q.send(msgs, strlen(msgs));
					}
					else if(dis4>=5 && dis4<7)
					{
						//const char* msg = "2";
						q.send(msgf, strlen(msgf));
					}
					else if(dis4>=7 && dis4<9)
					{
						//const char* msg = "-";
						q.send(msgl, strlen(msgl));
					}
					else if(dis4>=9 && dis4<11)
					{
						//const char* msg = "+";
						q.send(msgh, strlen(msgh));
					}
				}
		}
		else if( dis2>=20 && dis2<30)
		{
				path2 =soundpath5;
				auto q=Popen({"omxplayer","-o","local",path2},output{PIPE},input{PIPE});
				flag =1;
			
				while(flag)
				{
					dis2 = disMeasure(Trig2,Echo2);
					cout << "distance2 = " << dis2 << " cm." << endl;
					dis4 = disMeasure(Trig4,Echo4);
					cout << "distance4 = " << dis4 << " cm." << endl;
					delay(1000);
					
					if((dis2>=10 && dis2<20)||(dis2>=30 && dis2<40))
					{
						//const char* msg = "q";
						q.send(msgq, strlen(msgq));
						auto res = q.communicate(nullptr, 0);
						//std::cout << res.first.buf.data() << std::endl;
						flag =0;
					}
					if(dis4>=3 && dis4<5)
					{
						//const char* msg = "1";
						q.send(msgs, strlen(msgs));
					}
					else if(dis4>=5 && dis4<7)
					{
						//const char* msg = "2";
						q.send(msgf, strlen(msgf));
					}
					else if(dis4>=7 && dis4<9)
					{
						//const char* msg = "-";
						q.send(msgl, strlen(msgl));
					}
					else if(dis4>=9 && dis4<11)
					{
						//const char* msg = "+";
						q.send(msgh, strlen(msgh));
					}
				}
		}
		else if( dis2>=30 &&dis2<40)
		{
				path2 =soundpath6;
				auto q=Popen({"omxplayer","-o","local",path2},output{PIPE},input{PIPE});
				flag =1;
			
				while(flag)
				{
					dis2 = disMeasure(Trig2,Echo2);
					cout << "distance2 = " << dis2 << " cm." << endl;
					dis4 = disMeasure(Trig4,Echo4);
					cout << "distance4 = " << dis4 << " cm." << endl;
					delay(1000);
					
					if(dis2>=10 && dis2<30)
					{
						//const char* msg = "q";
						q.send(msgq, strlen(msgq));
						auto res = q.communicate(nullptr, 0);
						//std::cout << res.first.buf.data() << std::endl;
						flag =0;
					}
					if(dis4>=3 && dis4<5)
					{
						//const char* msg = "1";
						q.send(msgs, strlen(msgs));
					}
					else if(dis4>=5 && dis4<7)
					{
						//const char* msg = "2";
						q.send(msgf, strlen(msgf));
					}
					else if(dis4>=7 && dis4<9)
					{
						//const char* msg = "-";
						q.send(msgl, strlen(msgl));
					}
					else if(dis4>=9 && dis4<11)
					{
						//const char* msg = "+";
						q.send(msgh, strlen(msgh));
					}
				}
		}delay(1000);}
		perror("error");
		exit(0);
		}
		}
		
		if(dis3>=11 && dis3<13)   //off
		{
			start =0;
		}
		delay(1000);
	}
	return 0;
}
