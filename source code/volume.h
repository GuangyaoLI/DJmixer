//����������
//	SOUND_MIXER_VOLUME ���������� 
//	SOUND_MIXER_BASS �������� 
//	SOUND_MIXER_TREBLE �������� 
//	SOUND_MIXER_SYNTH FM�ϳ��� 
//	SOUND_MIXER_PCM ��D/Aת���� 
//	SOUND_MIXER_SPEAKER PC���� 
//	SOUND_MIXER_LINE ��Ƶ������ 
//	SOUND_MIXER_MIC ��˷����� 
//	SOUND_MIXER_CD CD���� 
//	SOUND_MIXER_IMIX �ط����� 
//	SOUND_MIXER_ALTPCM ��D/A ת���� 
//	SOUND_MIXER_RECLEV ¼������ 
//	SOUND_MIXER_IGAIN �������� 
//	SOUND_MIXER_OGAIN ������� 
//	SOUND_MIXER_LINE1 �����ĵ�1���� 
//	SOUND_MIXER_LINE2 �����ĵ�2���� 
//	SOUND_MIXER_LINE3 �����ĵ�3����

#ifndef SOME_HEADNAME_VOLUME
#define SOME_HEADNAME_VOLUME


#define MIXER_DEV "/dev/mixer"

class volume
{
public:
	volume(void);
	~volume(void);



	/* ���� */
	void sys_volume_mute();
	/* �����ָ� */
	void sys_volume_resume();
	/* �Ӵ����� */
	void sys_volume_up();
	/* �������� */
	void sys_volume_down();

	void Setvolume(int m_vol);


private:
	int g_oldvol ;	//��һ������

	/* ��������ֵ */
	int sys_volume_setvalue(int vol);
	/* ��ȡ����ֵ */
	int sys_volume_getvalue();


};


#endif 

