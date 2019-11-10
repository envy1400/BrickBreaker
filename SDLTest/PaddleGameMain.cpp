// Author: Nick Vinyard
// Purpose: Creating a paddle and ball game

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "BrickBreaker/Paddle/Paddle.h"
#include "BrickBreaker/Ball/Ball.h"
#include "BrickBreaker/Graphics/LTexture.h"
#include "BrickBreaker/Config/SystemConfig.h"
#include "BrickBreaker\Bricks\Brick.h"
#include "BrickBreaker/Graphics/PG_Renderer.h"
#include "BrickBreaker\Levels\LevelArrays.h"
#include "BrickBreaker/Physics/CollisionChecker.h"
#include "BrickBreaker/Managers/LevelManager.h"
#include "BrickBreaker/App/MainMenu.h"
#include "BrickBreaker/App/PausedMenu.h"
#include "BrickBreaker/Managers/SoundManager/SoundManager.h"

using namespace BrickBreaker;

typedef enum {
	APP_MENU,
	APP_LOAD_LEVEL,
	APP_GAME_RUNNING,
	APP_DEATH_SCREEN,
	APP_LEVEL_COMPLETE,
	APP_GAME_COMPLETE,
	APP_GAME_PAUSED,
} eGameState;

// used to handle user input at menus
typedef enum {
	PAUSED_MENU,
	PAUSED_OPTIONS_MENU,
} ePausedMenus;

typedef enum {
	PAUSED_RESUME,
	PAUSED_OPTIONS,
	PAUSED_MAIN_MENU,
	PAUSED_QUIT,
} ePausedState;

typedef enum {
	PAUSED_OPTIONS_BACK,
} ePausedOptionsState;

static ePausedMenus pausedMenuState = PAUSED_MENU;
static ePausedState pausedState = PAUSED_RESUME;

// used when the game is paused
static uint8_t pausedSelectionIndex = 0;

// used when the game is paused and in the options menu
static uint8_t pausedOptionsSelectionIndex;

static bool IsKeyDown = false;
static uint8_t GameState = APP_MENU;

static Level *CurrentLevel;

static int GameLevel = 0;

// Local Functions
bool AppDeathScreenTasks(void);

bool LevelCompleteTasks(void);

bool GameCompleteTasks(void);

bool CheckForCheatCode(SDL_Event &e);

// Function Implementations

int main(int argc, char* args[])
{
	bool quit = false;
	SDL_Event e;
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
	{
		printf("Could not initialize SDL_Error: %s\n", SDL_GetError());
	}
	else
	{							
		if (InitPGRenderer())
		{

			SoundManagerInit();
			SM_LoadMedia();

			Paddle paddle;

			PG_AddPaddle(&paddle);

			Dot dot;

			PG_AddDot(&dot);

			while (!quit)
			{
				// TODO : move this to game running case
				// Something is wrong here. Why are we staying in this loop?
				/*while (SDL_PollEvent(&e) != 0)
				{*/
				SDL_PollEvent(&e);
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}				
				// }

				// switch on the game state

				switch (GameState)
				{
				default :
				case APP_MENU:

					if (AppMenuTasks())
					{
						GameState = APP_LOAD_LEVEL;
						
						dot.reset();

						paddle.reset();

						// reset level and bricks
						GameLevel = 0;
					}

					break;
				case APP_LOAD_LEVEL:

					if (!SM_IsMusicPlaying())
					{
						SM_PlayMusic();
					}					

					CurrentLevel = MasterLevelArray[GameLevel];					

					// Set the current level with managers
					LM_ResetLevel(*CurrentLevel);
					PG_SetLevel(*CurrentLevel);
					CC_SetLevel(*CurrentLevel);

					// Reset the ball
					dot.reset();

					GameState = APP_GAME_RUNNING;

					break;
				case APP_GAME_RUNNING:

					if (e.key.keysym.sym == SDLK_TAB)
					{
						// Pause the game
						GameState = APP_GAME_PAUSED;
						pausedMenuState = PAUSED_MENU;
					}

					paddle.handleEvent(e);					

					paddle.calcVel();

					paddle.move();


					// move each dot then check each dot for collision with paddle??					

					if (dot.move(paddle))
					{
						paddle.CollisionCount++;
					}								

					if (CC_CheckBallDie(&dot))
					{
						// go to menu game state
						GameState = APP_DEATH_SCREEN;
					}

					PG_RenderTasks();

					//if (e.key.keysym.sym == SDLK_TAB)
					//{
					//	// Pause the game


					//	continue;
					//}

					if (CurrentLevel->GetNumberOfBricksLeft() == 0 || CheckForCheatCode(e))
					{
						// Move to level complete
						GameState = APP_LEVEL_COMPLETE;
					}

					break;		
				case APP_LEVEL_COMPLETE :

					// Display level stats
					// Wait for user input
					if (LevelCompleteTasks())
					{

					}
				
					break;
				case APP_GAME_COMPLETE : 

					// Display game stats
					// Wait for user input
					if (GameCompleteTasks())
					{

					}
					break;
				case APP_DEATH_SCREEN :

					if (AppDeathScreenTasks())
					{
						dot.reset();

						paddle.reset();

						// reset level and bricks
						GameLevel = 0;

					}

					break;
				case APP_GAME_PAUSED :

					if (SM_IsMusicPlaying())
					{
						SM_PauseMusic();
					}

					switch (pausedMenuState)
					{
					case PAUSED_MENU:

						PG_RenderPausedMenu(pausedSelectionIndex);

						// Move the selector
						if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_SPACE))
						{
							IsKeyDown = true;
						}
						else if (e.type == SDL_KEYUP && e.key.repeat == 0 && IsKeyDown)
						{
							IsKeyDown = false;
							if (e.key.keysym.sym == SDLK_UP)
							{
								if (pausedSelectionIndex <= 0)
								{
									pausedSelectionIndex = 3;
								}
								else
								{
									pausedSelectionIndex--;
								}
							}
							else if (e.key.keysym.sym == SDLK_DOWN)
							{
								if (pausedSelectionIndex >= 3)
								{
									pausedSelectionIndex = 0;
								}
								else
								{
									pausedSelectionIndex++;
								}
							}

							if (e.key.keysym.sym == SDLK_SPACE)
							{
								switch (pausedSelectionIndex)
								{
								case PAUSED_RESUME:
									GameState = APP_GAME_RUNNING;
									SM_ResumeMusic();
									break;

								case PAUSED_OPTIONS:
									pausedMenuState = PAUSED_OPTIONS_MENU;
									break;

								case PAUSED_MAIN_MENU:
									SM_StopMusic();
									GameState = APP_MENU;
									break;

								case PAUSED_QUIT:
									quit = true;
									break;

								default:
									pausedSelectionIndex = 0;
									break;
								}
							}
						}
					
						break;

					case PAUSED_OPTIONS_MENU:

						PG_RenderPausedOptions(pausedOptionsSelectionIndex);
						// Move the selector
						if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_SPACE ))
						{
							IsKeyDown = true;
						}
						else if (e.type == SDL_KEYUP && e.key.repeat == 0 && IsKeyDown)
						{
							IsKeyDown = false;
							/*if (e.key.keysym.sym == SDLK_UP)
							{
								if (pausedSelectionIndex <= 0)
								{
									pausedSelectionIndex = 0;
								}
								else
								{
									pausedSelectionIndex--;
								}
							}
							else if (e.key.keysym.sym == SDLK_DOWN)
							{
								if (pausedSelectionIndex >= 0)
								{
									pausedSelectionIndex = 0;
								}
								else
								{
									pausedSelectionIndex++;
								}
							}*/
							if (e.key.keysym.sym == SDLK_SPACE)
							{
								switch (pausedOptionsSelectionIndex)
								{
								case PAUSED_OPTIONS_BACK:
									pausedMenuState = PAUSED_MENU;
									pausedOptionsSelectionIndex = PAUSED_OPTIONS_BACK;
									break;

								default:
									pausedOptionsSelectionIndex = 0;
									break;
								}
							}
						}					

						break;
					default:
						// do nothing
						break;
					}				
					break;
				} // switch(gameState)				
			}
		}		
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	SM_Close();

	return 0;
}

bool AppDeathScreenTasks(void)
{
	PG_RenderDeathScreen();

	SDL_Event deathScreenEvent;

	SDL_PollEvent(&deathScreenEvent);

	if (deathScreenEvent.type == SDL_KEYUP && deathScreenEvent.key.keysym.sym == SDLK_SPACE)
	{				
		GameState = APP_MENU;
		return true;
	}

	return false;
}

bool LevelCompleteTasks(void)
{
	PG_RenderLevelCompleteScreen();	

	SDL_Event levelCompleteEvent;

	SDL_PollEvent(&levelCompleteEvent);

	if (levelCompleteEvent.type == SDL_KEYUP && levelCompleteEvent.key.keysym.sym == SDLK_SPACE)
	{
		// Move to the next level or  game is complete
		if (GameLevel >= NUMBER_OF_LEVELS - 1)
		{
			// Game complete
			GameState = APP_GAME_COMPLETE;
		}
		else
		{
			// Increment level
			GameLevel++;
			GameState = APP_LOAD_LEVEL;
		}
		return true;
	}

	return false;
}

bool GameCompleteTasks(void)
{
	PG__RenderGameCompleteScreen();

	SDL_Event gameCompleteEvent;

	SDL_PollEvent(&gameCompleteEvent);

	if (gameCompleteEvent.type == SDL_KEYUP && gameCompleteEvent.key.keysym.sym == SDLK_SPACE)
	{
		// Reset the game
		GameLevel = 0;
		GameState = APP_MENU;
		return true;
	}
	return false;
}

bool CheckForCheatCode(SDL_Event& e)
{
	static bool XKeyDown, CKeyDown;	

	if (e.type == SDL_KEYDOWN)
	{
		int i = 0;
	}
	if (e.key.keysym.sym == SDLK_c && e.key.repeat == 0)
	{
		if (e.type == SDL_KEYDOWN)
		{
			CKeyDown = true;
		}
		else
		{
			CKeyDown = false;
		}
	}
	if (e.key.keysym.sym == SDLK_x)
	{
		if (e.type == SDL_KEYDOWN)
		{
			XKeyDown = true;
		}
		else
		{
			XKeyDown = false;
		}
	}

	if (XKeyDown && CKeyDown)
	{
		// reset they key states
		XKeyDown = false;
		CKeyDown = false;
		return true;
	}
	return false;
}