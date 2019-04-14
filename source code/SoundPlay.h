#ifndef PLAY_H
#define PLAY_H

typedef enum
{
	PLAY_STATUS_PLAY = 0x1,
	PLAY_STATUS_PAUSE,
	PLAY_STATUS_STOP,
	PLAY_STATUS_RESERV,
}PLAY_STATUS_S;

class SoundPlay
{
public:
	SoundPlay(void);
	~SoundPlay(void);


	int playmusic(const char *musicname);
	int pausemusic();
	int stopmusic();


private:
	PLAY_STATUS_S play_state;  //播放状态
	int child ;  //子进程号
	int beginplay(char *path);


};


#endif