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
	int Echo , Trig ;  //����������Ų���
	bool isInit_Echo ;  //�Ƿ��ʼ�������������
	bool isInit_mudis;
	bool isInit_spath;

	vector<float> musicDistence;  //���ֵ�ľ������䣬��һ�����뿪ʼ��������һ������ֹͣ���
	vector<string> soundpath;   //���������path
	

	//char *soundpath1; 
	//char *soundpath2;
	//char *soundpath3;

	float disMeasure(void);

};



#endif

