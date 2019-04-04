#ifndef MAINBUSI_H
#define MAINBUSI_H

#include "MeasureCtrl.h"
#include "SoundPlay.h"
#include "volume.h"

#define Trig  8//0
#define Echo  9//1

class MainBusiness
{
public:
	MainBusiness(void);
	~MainBusiness(void);

	void startGame();
	void InitData();
	void Setvolume(int m_vol);

private:
	MeasureCtrl m_MeasureCtrl;
	SoundPlay m_SoundPlay;
	volume m_volume;
	char* soundpath;
	void ultraInit(void);

};

#endif

