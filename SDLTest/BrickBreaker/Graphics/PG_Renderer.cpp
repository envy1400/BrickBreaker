#define PG_RENDERER_CPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include "LTexture.h"
#include "../Config/SystemConfig.h"
#include "../Paddle/Paddle.h"
#include "..\Bricks\Brick.h"
#include "../Timer/LTimer.h"

namespace BrickBreaker
{
#define MAX_DOTS 5
	// The window to render to
	static SDL_Window* pPG_Window = NULL;

	// the surface contained by the window
	static SDL_Surface* pPG_surface = NULL;

	//The window renderer
	static SDL_Renderer* pPG_Renderer = NULL;

	//Rendered texture
	static LTexture PG_TextTexture;

	//Globally used font
	static TTF_Font * pPG_Font = NULL;

	//Scene textures
	static LTexture PG_DotTexture;

	static Paddle * pPG_Paddle;

	static Dot* dotArray[MAX_DOTS];
	static int dotsAdded = 0;

	static Level * pCurrentLevel;

	//The frames per second timer
	static LTimer fpsTimer;

	//The frames per second cap timer
	static LTimer capTimer;

	void PG_RenderBrick(Brick * const &brick);

	bool InitPGRenderer()
	{
		pPG_Window = SDL_CreateWindow("Paddle Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (pPG_Window == NULL)
		{
			printf("Window is NULL : %s\n", SDL_GetError());
		}
		else
		{
			pPG_Renderer = SDL_CreateRenderer(pPG_Window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
			if (pPG_Renderer == NULL)
			{
				printf("Renderer error: %s\n", SDL_GetError());
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(pPG_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				}

				//Open the font
				pPG_Font = TTF_OpenFont("BrickBreaker/Assets/Fonts/Raleway-Regular.ttf", 28);
				if (pPG_Font == NULL)
				{
					printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
				}
				else
				{
					//Render text
					SDL_Color textColor = { 0, 0, 0 };		

					PG_DotTexture.Font = pPG_Font;
					PG_DotTexture.Renderer = pPG_Renderer;
					PG_TextTexture.Font = pPG_Font;
					PG_TextTexture.Renderer = pPG_Renderer;

					if (!PG_TextTexture.loadFromRenderedText("GO!", textColor))
					{
						printf("Failed to render text texture!\n");
					}
				}

				//Load press texture
				if (!PG_DotTexture.loadFromFile("BrickBreaker/Assets/Balls/dot.bmp"))
				{
					printf("Failed to load dot texture!\n");
					printf("SDL ERROR: %s\n", SDL_GetError());					
				}
			}
		}
		return true;
	}

	void PG_RenderPaddle(Paddle * paddle)
	{
		SDL_SetRenderDrawColor(pPG_Renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(pPG_Renderer, paddle);

		// render the count
		SDL_Color textColor = { 0, 0, 0 };

		std::stringstream sstream;
		sstream << paddle->CollisionCount;

		PG_TextTexture.loadFromRenderedText(sstream.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH - 50, 30);
	}

	void PG_RenderDot(Dot * dot)
	{
		PG_DotTexture.render(dot->mPosX, dot->mPosY);
	}

	void PG_RenderTasks(void)
	{
		capTimer.start();
		//Clear screen
		SDL_SetRenderDrawColor(pPG_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(pPG_Renderer);

		// Render bricks
		for (int j = 0; j < pCurrentLevel->NumberOfBricks; j++)
		{
			PG_RenderBrick((Brick*)&pCurrentLevel->LevelBricks[j]);						
		}

		//Render paddle
		PG_RenderPaddle(pPG_Paddle);

		for (int i = 0; i < dotsAdded; i++)
		{
			PG_RenderDot(dotArray[i]);
		}	

		//Update screen
		SDL_RenderPresent(pPG_Renderer);
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	void PG_AddPaddle(Paddle *paddle)
	{
		pPG_Paddle = paddle;
	}

	void PG_AddDot(Dot *dot)
	{
		if (dotsAdded < MAX_DOTS)
		{
			dotArray[dotsAdded++] = dot;
		}
	}	

	void PG_RemoveDot(Dot *dot)
	{
		for (int i = 0; i < dotsAdded; i++)
		{
			if (dotArray[i]->ID = dot->ID)
			{				
				
				// shift the remaining dots 
				for (int j = i; j < dotsAdded - i; j++)
				{
					dotArray[j] = dotArray[j + 1];
				}

				// Clear the last reference
				dotArray[dotsAdded - 1] = 0;

				dotsAdded--;
				break;
			}
		}
	}

	void PG_RenderMenu(void)
	{
		//Clear screen
		SDL_SetRenderDrawColor(pPG_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(pPG_Renderer);

		// render the count
		SDL_Color textColor = { 0, 0, 0 };

		std::stringstream sstream;
		sstream << "Press space to begin";

		PG_TextTexture.loadFromRenderedText(sstream.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH/2 - 100, 75);

		//Update screen
		SDL_RenderPresent(pPG_Renderer);
	}

	void PG_RenderDeathScreen(void)
	{
		//Clear screen
		SDL_SetRenderDrawColor(pPG_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(pPG_Renderer);

		// render the count
		SDL_Color textColor = { 0, 0, 0 };

		std::stringstream sstream;
		sstream << "WOW!";

		PG_TextTexture.loadFromRenderedText(sstream.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH / 2 - 100, 75);

		//Update screen
		SDL_RenderPresent(pPG_Renderer);
	}

	void PG_SetLevel(Level &level)
	{
		pCurrentLevel = &level;
	}

	void PG_RenderBrick(Brick * const &brick)
	{
		if (brick->GetIsVisible())
		{
			SDL_Color brickColor = brick->GetColor();
			SDL_SetRenderDrawColor(pPG_Renderer, brickColor.r, brickColor.g, brickColor.b, brickColor.a);
			SDL_RenderDrawRect(pPG_Renderer, brick);
		}					
	}

	void PG_RenderLevelCompleteScreen(void)
	{
		//Clear screen
		SDL_SetRenderDrawColor(pPG_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(pPG_Renderer);

		// render the count
		SDL_Color textColor = { 0, 0, 0 };

		std::stringstream sstream;
		sstream << "Level Complete. Press Spacebar";

		PG_TextTexture.loadFromRenderedText(sstream.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH / 2 - 200, 75);

		//Update screen
		SDL_RenderPresent(pPG_Renderer);
	}

	void PG__RenderGameCompleteScreen(void)
	{
		//Clear screen
		SDL_SetRenderDrawColor(pPG_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(pPG_Renderer);

		// render the count
		SDL_Color textColor = { 0, 0, 0 };

		std::stringstream sstream;
		sstream << "Game Complete. Press Spacebar";

		PG_TextTexture.loadFromRenderedText(sstream.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH / 2 - 100, 75);

		//Update screen
		SDL_RenderPresent(pPG_Renderer);
	}

	void PG_RenderPausedMenu(int selectedIndex)
	{		

		std::stringstream resumeString;
		std::stringstream optionsString;
		std::stringstream mainMenuString;
		std::stringstream quitToWindowsString;

		//Clear screen
		SDL_SetRenderDrawColor(pPG_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(pPG_Renderer);

		SDL_Rect selector;
		selector.h = 10;
		selector.w = 40;
		selector.x = SCREEN_WIDTH / 2 - 120;
		switch (selectedIndex)
		{
		case 0:
			selector.y = 160;
			break;
		case 1:
			selector.y = 185;
			break;
		case 2:
			selector.y = 210;
			break;
		case 3:
			selector.y = 235;
			break;
		default:
			selector.y = 160;
			break;
		}

		SDL_SetRenderDrawColor(pPG_Renderer, 0x9A, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(pPG_Renderer, &selector);

		// render the count
		SDL_Color textColor = { 0, 0, 0 };

		std::stringstream sstream;
		sstream << "Paused. Press Spacebar To Resume";

		PG_TextTexture.loadFromRenderedText(sstream.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH / 2 - 225, 75);

		resumeString << "Resume";

		PG_TextTexture.loadFromRenderedText(resumeString.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH / 2 - 60, 150);

		optionsString << "Options";

		PG_TextTexture.loadFromRenderedText(optionsString.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH / 2 - 60, 175);

		mainMenuString << "Main Menu";

		PG_TextTexture.loadFromRenderedText(mainMenuString.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH / 2 - 60, 200);

		quitToWindowsString << "Quit To Windows";

		PG_TextTexture.loadFromRenderedText(quitToWindowsString.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH / 2 - 60, 225);

		//Update screen
		SDL_RenderPresent(pPG_Renderer);
	}

	
	// Renders text and graphics for the options menu when
	// paused
	void PG_RenderPausedOptions(int selectedIndex)
	{
		std::stringstream backString;
		std::stringstream optionsString;
		std::stringstream mainMenuString;
		std::stringstream quitToWindowsString;

		//Clear screen
		SDL_SetRenderDrawColor(pPG_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(pPG_Renderer);

		SDL_Rect selector;
		selector.h = 10;
		selector.w = 40;
		selector.x = SCREEN_WIDTH / 2 - 120;
		switch (selectedIndex)
		{
		case 0:
			selector.y = 160;
			break;
		case 1:
			selector.y = 185;
			break;
		case 2:
			selector.y = 210;
			break;
		case 3:
			selector.y = 235;
			break;
		default:
			selector.y = 160;
			break;
		}

		SDL_SetRenderDrawColor(pPG_Renderer, 0x9A, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(pPG_Renderer, &selector);

		// render the count
		SDL_Color textColor = { 0, 0, 0 };

		std::stringstream sstream;
		sstream << "Options";

		PG_TextTexture.loadFromRenderedText(sstream.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH / 2 - 225, 75);

		backString << "Back";

		PG_TextTexture.loadFromRenderedText(sstream.str(), textColor);

		PG_TextTexture.render(SCREEN_WIDTH / 2 - 60, 150);

		//Update screen
		SDL_RenderPresent(pPG_Renderer);
	}
}