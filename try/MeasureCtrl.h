#ifndef MEASURE_H
#define MEASURE_H


#define Trig  8//0
#define Echo  9//1

class MeasureCtrl
{
public:
	MeasureCtrl(void);
	~MeasureCtrl(void);

	char * GetplayPath(int &playflag);


private:
	int flag ;  
	int oldflag ;

	char *soundpath1; 
	char *soundpath2;
	char *soundpath3;

	float disMeasure(void);

};



#endif

