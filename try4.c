
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

#include <linux/input.h>
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

#define Trig1  9
#define Echo1  8
#define Trig2  2
#define Echo2  0
#define Trig3  13
#define Echo3  12
#define Trig4  11
#define Echo4  10


char soundpath1[] ="DesiJourney.wav"; 
char soundpath2[] ="doublebass.wav";
char soundpath3[] ="MoodyLoop.wav";




void ultraInit(void)
{
	pinMode(Echo2, INPUT);
	pinMode(Trig2, OUTPUT);
	pinMode(Echo1, INPUT);
	pinMode(Trig1, OUTPUT);
	pinMode(Echo3, INPUT);
	pinMode(Trig3, OUTPUT);
	pinMode(Echo4, INPUT);
	pinMode(Trig4, OUTPUT);
}

float disMeasure2(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float dis2;

	digitalWrite(Trig2, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig2, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig2, LOW);

	while(!(digitalRead(Echo2) == 1));
	gettimeofday(&tv1, NULL);

	while(!(digitalRead(Echo2) == 0));
	gettimeofday(&tv2, NULL);

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	dis2 = (float)(stop - start) / 1000000 * 34000 / 2;

	return dis2;
}

float disMeasure1(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float dis1;

	digitalWrite(Trig1, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig1, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig1, LOW);

	while(!(digitalRead(Echo1) == 1));
	gettimeofday(&tv1, NULL);

	while(!(digitalRead(Echo1) == 0));
	gettimeofday(&tv2, NULL);

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	dis1 = (float)(stop - start) / 1000000 * 34000 / 2;

	return dis1;
}

float disMeasure3(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float dis3;

	digitalWrite(Trig3, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig3, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig3, LOW);

	while(!(digitalRead(Echo3) == 1));
	gettimeofday(&tv1, NULL);

	while(!(digitalRead(Echo3) == 0));
	gettimeofday(&tv2, NULL);

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	dis3 = (float)(stop - start) / 1000000 * 34000 / 2;

	return dis3;
}

float disMeasure4(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float dis4;

	digitalWrite(Trig4, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig4, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig4, LOW);

	while(!(digitalRead(Echo4) == 1));
	gettimeofday(&tv1, NULL);

	while(!(digitalRead(Echo4) == 0));
	gettimeofday(&tv2, NULL);

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	dis4 = (float)(stop - start) / 1000000 * 34000 / 2;

	return dis4;
}

int main(void)
{

	float dis1,dis2,dis3,dis4;
	//float dis2;
	
	wiringPiSetup();

	if(wiringPiSetup() == -1)
	{
		printf("setuo wiringPi failed !");
		return 1;
	}
	
	ultraInit();


	while(1)
	{
		dis2 = disMeasure2();
		dis1 = disMeasure1();
		dis3 = disMeasure3();
		dis4 = disMeasure4();
		printf("distance4 = %0.2f cm\n",dis4);
		printf("distance3 = %0.2f cm\n",dis3);
		printf("distance2 = %0.2f cm\n",dis2);
		printf("distance1 = %0.2f cm\n",dis1);
		
	
		delay(1000);
		
	}
	return 0;
}
