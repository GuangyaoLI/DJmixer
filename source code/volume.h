//声音控制类
//	SOUND_MIXER_VOLUME 主音量调节 
//	SOUND_MIXER_BASS 低音控制 
//	SOUND_MIXER_TREBLE 高音控制 
//	SOUND_MIXER_SYNTH FM合成器 
//	SOUND_MIXER_PCM 主D/A转换器 
//	SOUND_MIXER_SPEAKER PC喇叭 
//	SOUND_MIXER_LINE 音频线输入 
//	SOUND_MIXER_MIC 麦克风输入 
//	SOUND_MIXER_CD CD输入 
//	SOUND_MIXER_IMIX 回放音量 
//	SOUND_MIXER_ALTPCM 从D/A 转换器 
//	SOUND_MIXER_RECLEV 录音音量 
//	SOUND_MIXER_IGAIN 输入增益 
//	SOUND_MIXER_OGAIN 输出增益 
//	SOUND_MIXER_LINE1 声卡的第1输入 
//	SOUND_MIXER_LINE2 声卡的第2输入 
//	SOUND_MIXER_LINE3 声卡的第3输入

#ifndef SOME_HEADNAME_VOLUME
#define SOME_HEADNAME_VOLUME


#define MIXER_DEV "/dev/mixer"

class volume
{
public:
	volume(void);
	~volume(void);



	/* 静音 */
	void sys_volume_mute();
	/* 音量恢复 */
	void sys_volume_resume();
	/* 加大音量 */
	void sys_volume_up();
	/* 减少音量 */
	void sys_volume_down();

	void Setvolume(int m_vol);


private:
	int g_oldvol ;	//上一次音量

	/* 设置音量值 */
	int sys_volume_setvalue(int vol);
	/* 获取音量值 */
	int sys_volume_getvalue();


};


#endif 

