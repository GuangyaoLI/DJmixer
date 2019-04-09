#ifndef MEASURE_H
#define MEASURE_H


//#define Trig  8//0
//#define Echo  9//1
#include <vector>
#include <string.h>


class MeasureCtrl
{
public:
	MeasureCtrl(void);
	MeasureCtrl(int echo,int trig);
	~MeasureCtrl(void);

	string GetplayPath(int &playflag);
	bool SetEcho_Trig(int echo,int trig);
	bool SetmusicDistence(vector<float> & mudis);
	bool Setsoundpath(vector<string> & spath);

private:
	int flag ; 
	int oldflag ;
	int Echo , Trig ;  //输入输出引脚参数
	bool isInit_Echo ;  //是否初始化输入输出引脚
	bool isInit_mudis;
	bool isInit_spath;

	vector<float> musicDistence;  //输出值的距离区间，第一个距离开始输出，最后一个距离停止输出
	vector<string> soundpath;   //输出声音的path
	

	//char *soundpath1; 
	//char *soundpath2;
	//char *soundpath3;

	float disMeasure(void);

};



#endif

