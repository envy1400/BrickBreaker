/*********************************
Filename	: PausedMenu.cpp
Purpose		: Handles Inputs on the paused menu
Author		: Nick Vinyard
**/
#define PAUSED_MENU_CPP

#include <SDL.h>
#include "../Graphics/PG_Renderer.h"

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

static ePausedMenus pausedMenuState = PAUSED_MENU;
static ePausedState pausedState = PAUSED_RESUME;
static uint8_t pausedSelectionIndex = 0;
namespace BrickBreaker
{
	bool PausedMenuTasks(void)
	{
		SDL_Event pausedInput;

		PG_RenderPausedMenu(pausedSelectionIndex);

		SDL_PollEvent(&pausedInput);		

		switch (pausedMenuState)
		{
		case PAUSED_MENU :

			if (pausedInput.type == SDL_KEYUP && pausedInput.key.keysym.sym == SDLK_SPACE)
			{
				switch (pausedState)
				{
				case PAUSED_RESUME :
					return true;
					break;
				case PAUSED_OPTIONS :
					break;
				case PAUSED_MAIN_MENU :
					break;
				case PAUSED_QUIT : 
					break;
				default:
					pausedSelectionIndex = 0;
					break;
				}			
			}

			break;
		case PAUSED_OPTIONS_MENU :
			break;
		default:
			// do nothing
			break;
		}


		return false;
	}
}