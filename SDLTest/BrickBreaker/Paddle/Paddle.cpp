

#define PADDLE_CPP

#include "Paddle.h"
#include <sstream>
#include "../Config/SystemConfig.h"

using namespace std;

namespace BrickBreaker
{
	class LTexture;

	bool checkCollision(SDL_Rect a, SDL_Rect b);

	Paddle::Paddle(void)
	{
		x = SCREEN_WIDTH/2;
		y = SCREEN_HEIGHT - 50;
		w = PADDLE_WIDTH;
		h = PADDLE_HEIGHT;
		mVelX = 0;		
	}

	void Paddle::hitBall(Dot& dot)
	{
		if (checkCollision(dot.mCollider, (SDL_Rect)*this))
		{
			// Increment paddle count
			CollisionCount++;
		}
	}

	void Paddle::handleEvent(SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				rightKey(true);
				break;
			case SDLK_LEFT:
				leftKey(true);
				break;
			default:
				break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				rightKey(false);
				break;
			case SDLK_LEFT:
				leftKey(false);
				break;
			default:
				break;
			}
		}
	}

	void Paddle::move(void)
	{
		x += mVelX;

		if ((x < 0) || (x + w > SCREEN_WIDTH))
		{
			x -= mVelX;
		}
	}

	void Paddle::leftKey(bool keyDown)
	{
		leftKeyDown = keyDown;
	}

	void Paddle::rightKey(bool keyDown)
	{
		rightKeyDown = keyDown;
	}

	void Paddle::calcVel(void)
	{
		if (rightKeyDown && leftKeyDown)
		{
			mVelX = 0;
		}
		else if (rightKeyDown && !leftKeyDown)
		{
			mVelX = 10;
		}
		else if (leftKeyDown && !rightKeyDown)
		{
			mVelX = -10;
		}
		else
		{
			mVelX = 0;
		}
	}

	void Paddle::reset(void)
	{
		CollisionCount = 0;
		mVelX = 0;
		rightKeyDown = leftKeyDown = false;
		x = SCREEN_WIDTH / 2;
	}

	bool checkCollision(SDL_Rect a, SDL_Rect b)
	{
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = a.x;
		rightA = a.x + a.w;
		topA = a.y;
		bottomA = a.y + a.h;

		//Calculate the sides of rect B
		leftB = b.x;
		rightB = b.x + b.w;
		topB = b.y;
		bottomB = b.y + b.h;

		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
	}

	void Paddle::RegisterHitCallback(BrickBreakCallback BreakCallback, void * pArgs)
	{

	}

}
