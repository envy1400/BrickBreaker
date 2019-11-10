/*********************************
	Filename	: SoundManager.h
	Purpose		: This file handles sounds
	Author		: Nick Vinyard
**/

#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

namespace BrickBreaker 
{
	bool SoundManagerInit(void);

	bool SM_LoadMedia(void);

	void SM_Close(void);

	void SM_PlayMusic(void);

	void SM_ResumeMusic(void);

	void SM_PauseMusic(void);

	void SM_StopMusic(void);

	bool SM_IsMusicPlaying(void);

	void _SM_BrickBreakCallback(void * pArgs);

	void SM_MuteMusic(void);

	// Should be a value between 0-100
	void SM_SetMusicVoluem(int volume);
}

#endif // SOUND_MANAGER_H