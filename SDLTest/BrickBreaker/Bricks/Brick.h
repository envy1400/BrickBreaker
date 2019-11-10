/*********************************
	Filename	: Brick.h
	Purpose		: Defines the brick class
	Author		: Nick Vinyard
**/
#ifndef BRICK_H
#define BRICK_H

#include <SDL.h>
#include <vector>
#include "../Ball/Ball.h"
#include "../Levels/Level.h"
#include "../Helpers/CallbackHelper.h"
// #include "../Managers/LevelManager.h"

namespace BrickBreaker 
{	
	typedef enum {
		BRICK_COLOR_RED,
		BRICK_COLOR_BLUE,
		BRICK_COLOR_GREEN,
		BRICK_COLOR_YELLOW,
		BRICK_COLOR_ORANGE,
		BRICK_COLOR_PURPLE,
	} eBrickColor;

	class Dot;

	class Brick : public SDL_Rect
	{
	public :
		static const int BRICK_HEIGHT	= 10;
		static const int BRICK_WIDTH	= 50;		

		Brick(int PosX, int PosY, eBrickColor brickColor);

		SDL_Color GetColor(void);

		int GetXPosition(void);

		int GetYPosition(void);

		bool GetIsCollidable(void);

		bool GetIsVisible(void);

		void Break(void);

		void Reset(void);

		void RegisterBreakCallback(BrickBreakCallback BreakCallback, void * pArgs);

		// Friends
		friend bool CC_CheckBrickCollision(Dot *ball);

		friend void LM_ResetLevel(Level &level);

	private :		
		SDL_Color mColor;		

		bool IsVisible = false, IsCollidable = false;

		CallbackHelper_t SoundCallback;

		std::vector<CallbackHelper_t> BreakCallbacks;
	};
}

#endif