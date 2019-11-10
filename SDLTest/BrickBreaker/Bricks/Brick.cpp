/*********************************
Filename	: Brick.cpp
Purpose		: Implements the brick class
Author		: Nick Vinyard
**/
#define BRICK_CPP

#include "Brick.h"

namespace BrickBreaker
{
	Brick::Brick(int PosX, int PosY, eBrickColor brickColor)
	{
		x = PosX;
		y = PosY;
		w = BRICK_WIDTH;
		h = BRICK_HEIGHT;		
		IsCollidable = true;
		IsVisible = true;		
		
		mColor.a = 0xFF;
		switch (brickColor)
		{
		case BRICK_COLOR_RED:
		default:
			mColor.r = 0xFF;
			mColor.g = 0x00;
			mColor.b = 0x00;
			
			break;

		case BRICK_COLOR_ORANGE:
			mColor.r = 0xFF;
			mColor.g = 0xA5;
			mColor.b = 0x00;			

			break;

		case BRICK_COLOR_YELLOW:
			mColor.r = 0xF6;
			mColor.g = 0xFF;
			mColor.b = 0x33;

			break;

		case BRICK_COLOR_GREEN :
			mColor.r = 0x00;
			mColor.g = 0xFF;
			mColor.b = 0x00;

			break;

		case BRICK_COLOR_BLUE :
			mColor.r = 0x00;
			mColor.g = 0x00;
			mColor.b = 0xFF;

			break;

		case BRICK_COLOR_PURPLE:
			mColor.r = 0xEC;
			mColor.g = 0x33;
			mColor.b = 0xFF;

			break;
		}
	}

	SDL_Color Brick::GetColor(void)
	{
		return mColor;
	}

	int Brick::GetXPosition(void)
	{
		return x;
	}

	int Brick::GetYPosition(void)
	{
		return y;
	}

	bool Brick::GetIsCollidable(void)
	{
		return IsCollidable;
	}

	bool Brick::GetIsVisible(void)
	{
		return IsVisible;
	}

	void Brick::Break(void)
	{
		IsVisible = false;
		IsCollidable = false;

		if (SoundCallback.callback != NULL)
		{
			SoundCallback.callback(SoundCallback.pArgs);
		}
	}

	void Brick::Reset(void)
	{
		IsVisible = true;
		IsCollidable = true;
	}

	void Brick::RegisterBreakCallback(BrickBreakCallback BreakCallback, void * pArgs)
	{
		SoundCallback.callback = BreakCallback;
		SoundCallback.pArgs = pArgs;
	}

} // namespace