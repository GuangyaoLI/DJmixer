#ifndef MAINBUSI_H
#define MAINBUSI_H

#include "MeasureCtrl.h"
#include "SoundPlay.h"
#include "volume.h"


class MainBusiness
{
public:
	MainBusiness(void);
	~MainBusiness(void);

	void startGame();
	void InitData();
	void Setvolume(int m_vol);

private:
	MeasureCtrl m_MeasureCtrl_music1,m_MeasureCtrl_music2,m_MeasureCtrl_music3,m_MeasureCtrl_volume;
	SoundPlay m_SoundPlay1,m_SoundPlay2,m_SoundPlay3;
	volume m_volume;

	vector<string> soundpath_vec1 ,soundpath_vec2,soundpath_vec3, volumepath_vec;
	vector<float> musicDistence_vec1 ,musicDistence_vec2 ,musicDistence_vec3, volumeDistence_vec; 
	vector<int> volume_vec;

	bool isInitData;

};

#endif

