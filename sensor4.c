
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

//}
#define Trig1  5
#define Echo1  4
#define Trig2  13
#define Echo2  12
#define Trig3  2
#define Echo3  0
#define Trig4  9
#define Echo4  8

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

float disMeasure1(void)
{
  struct timeval tv11;
  struct timeval tv12;
  long start1, stop1;
  float dis1;

  digitalWrite(Trig1, LOW);
  delayMicroseconds(2);

  digitalWrite(Trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig1, LOW);

  while(!(digitalRead(Echo1) == 1));
  gettimeofday(&tv11, NULL);

  while(!(digitalRead(Echo1) == 0));
  gettimeofday(&tv12, NULL);

  start1 = tv11.tv_sec * 1000000 + tv11.tv_usec;
  stop1  = tv12.tv_sec * 1000000 + tv12.tv_usec;

  dis1 = (float)(stop1 - start1) / 1000000 * 34000 / 2;

  return dis1;
}

float disMeasure2(void)
{
  struct timeval tv21;
  struct timeval tv22;
  long start2, stop2;
  float dis2;

  digitalWrite(Trig2, LOW);
  delayMicroseconds(2);

  digitalWrite(Trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig2, LOW);

  while(!(digitalRead(Echo2) == 1));
  gettimeofday(&tv21, NULL);

  while(!(digitalRead(Echo2) == 0));
  gettimeofday(&tv22, NULL);

  start2 = tv21.tv_sec * 1000000 + tv21.tv_usec;
  stop2  = tv22.tv_sec * 1000000 + tv22.tv_usec;

  dis2 = (float)(stop2 - start2) / 1000000 * 34000 / 2;

  return dis2;
}

float disMeasure3(void)
{
  struct timeval tv31;
  struct timeval tv32;
  long start3, stop3;
  float dis3;

  digitalWrite(Trig3, LOW);
  delayMicroseconds(2);

  digitalWrite(Trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig3, LOW);

  while(!(digitalRead(Echo3) == 1));
  gettimeofday(&tv31, NULL);

  while(!(digitalRead(Echo3) == 0));
  gettimeofday(&tv32, NULL);

  start3 = tv31.tv_sec * 1000000 + tv31.tv_usec;
  stop3  = tv32.tv_sec * 1000000 + tv32.tv_usec;

  dis3 = (float)(stop3 - start3) / 1000000 * 34000 / 2;

  return dis3;
}

float disMeasure4(void)
{
  struct timeval tv41;
  struct timeval tv42;
  long start4, stop4;
  float dis4;

  digitalWrite(Trig4, LOW);
  delayMicroseconds(2);

  digitalWrite(Trig4, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig4, LOW);

  while(!(digitalRead(Echo4) == 1));
  gettimeofday(&tv41, NULL);

  while(!(digitalRead(Echo4) == 0));
  gettimeofday(&tv42, NULL);

  start4 = tv41.tv_sec * 1000000 + tv41.tv_usec;
  stop4  = tv42.tv_sec * 1000000 + tv42.tv_usec;

  dis4 = (float)(stop4 - start4) / 1000000 * 34000 / 2;

  return dis4;
}

int main(void)
{
  float dis1, dis2, dis3 , dis4;
  wiringPiSetup();

  if(wiringPiSetup() == -1)
  {
    printf("setuo wiringPi failed !");
    return 1;
  }

  ultraInit();

  while(1)
  {
    dis1 = disMeasure1();
    dis2 = disMeasure2();
    dis3 = disMeasure3();
    dis4 = disMeasure4();
    printf("distance1 = %0.2f cm\n",dis1);
    printf("distance2 = %0.2f cm\n",dis2);
    printf("distance3 = %0.2f cm\n",dis3);
    printf("distance4 = %0.2f cm\n",dis4);
    
    delay(1000);
  }

  return 0;
}
