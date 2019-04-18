#ifndef MEASURE_H
#define MEASURE_H



#include <vector>
#include <string>
using namespace std;

class MeasureCtrl
{
public:
	MeasureCtrl(void);
	MeasureCtrl(int echo,int trig ,const char* name);
	~MeasureCtrl(void);


	const char* Ctrlname;

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
	

	float disMeasure(void);

};



#endif

