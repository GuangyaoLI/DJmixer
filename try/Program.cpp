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
#include "iostream"

#include "MainBusiness.h"

using namespace std;


int main(void)
{
	MainBusiness m_MainBusiness;

	m_MainBusiness.InitData();
	int vol;
	char flag;
	cout<<******************************<<endl;
	cout<<"请设置声音大小（输入数字）："<<endl;
	cin>>vol;
	m_MainBusiness.Setvolume(vol);
	cout<<"输入字母'y'开始，其他结束"<<endl;
	cin>>flag;
	if(flag=='y')
	{
		m_MainBusiness.startGame();
	}

	retrun 0;
}
