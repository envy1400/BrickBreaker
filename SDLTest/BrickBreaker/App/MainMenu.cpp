/*********************************
Filename	: MainMenu.cpp
Purpose		: Handles inputs on the main menu
Author		: Nick Vinyard
**/
#define MAIN_MENU_CPP

#include <SDL.h>
#include "../Graphics/PG_Renderer.h"

namespace BrickBreaker
{
	bool AppMenuTasks(void)
	{
		SDL_Event startGame;

		PG_RenderMenu();

		SDL_PollEvent(&startGame);

		if (startGame.type == SDL_KEYUP && startGame.key.keysym.sym == SDLK_SPACE)
		{
						
			return true;

		}
		return false;
	}
}
