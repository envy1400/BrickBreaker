/*********************************
Filename	: SoundManager.cpp
Purpose		: This file handles sounds
Author		: Nick Vinyard
**/
#define SOUND_MANAGER_CPP

#include <SDL_Mixer.h>
#include <stdio.h>

namespace BrickBreaker
{
#define MUTE_VALUE 0

	// Local Variables
	Mix_Music *pBackgroundMusic = NULL;

	// Played when the paddle is hit
	Mix_Chunk *pPaddleHitChunk = NULL;

	// Played when a brick is broken
	Mix_Chunk *pBrickHitChunk = NULL;

	bool SoundManagerInit(void)
	{
		bool success = true;
		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		return success;
	}

	bool SM_LoadMedia(void)
	{
		bool success = true;

		//Load music
		pBackgroundMusic = Mix_LoadMUS("BrickBreaker/Assets/Music/Milky_Way_Original_Mix.mp3");
		if (pBackgroundMusic == NULL)
		{
			printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		//Load sound effects
		pPaddleHitChunk = Mix_LoadWAV("BrickBreaker/Assets/Sounds/paddlePunch.wav");
		if (pPaddleHitChunk == NULL)
		{
			printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		pBrickHitChunk = Mix_LoadWAV("BrickBreaker/Assets/Sounds/brickBreakSound.wav");
		if (pBrickHitChunk == NULL)
		{
			printf("Failed to laod brick sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		return success;
	}

	void SM_PlayMusic(void)
	{
		Mix_PlayMusic(pBackgroundMusic, -1);
	}

	void SM_ResumeMusic(void)
	{
		Mix_ResumeMusic();
	}

	void SM_PauseMusic(void)
	{
		Mix_PauseMusic();
	}

	void SM_StopMusic(void)
	{
		Mix_HaltMusic();
	}

	bool SM_IsMusicPlaying(void)
	{
		bool IsMusicPlaying = false;

		IsMusicPlaying = Mix_PlayingMusic();

		return IsMusicPlaying;
	}

	void SM_Close(void)
	{
		Mix_FreeMusic(pBackgroundMusic);
		Mix_FreeChunk(pPaddleHitChunk);
		Mix_FreeChunk(pBrickHitChunk);

		Mix_Quit();
	}

	void _SM_BrickBreakCallback(void * pArgs)
	{
		Mix_PlayChannel(-1, pBrickHitChunk, 0);
	}

	void SM_MuteMusic(void)
	{
		Mix_VolumeMusic(MUTE_VALUE);
	}
}