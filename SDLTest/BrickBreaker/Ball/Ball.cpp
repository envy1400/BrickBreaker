
#define BALL_CPP

#include "Ball.h"
#include "../Config/SystemConfig.h"

namespace BrickBreaker
{
#define DOT_RESET_POS_X		SCREEN_WIDTH/2
#define DOT_RESET_POS_Y		200
	bool ballCheckCollisionPaddle(SDL_Rect a, SDL_Rect b);

	Dot::Dot()
	{
		//Initialize the offsets
		mPosX = DOT_RESET_POS_X;
		mPosY = DOT_RESET_POS_Y;

		//Set collision box dimension
		mCollider.w = DOT_WIDTH;
		mCollider.h = DOT_HEIGHT;

		//Initialize the velocity
		mVelX = 3;
		mVelY = 3;		
	}

	void Dot::handleEvent(SDL_Event& e)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: mVelY -= DOT_VEL; break;
			case SDLK_DOWN: mVelY += DOT_VEL; break;
			case SDLK_LEFT: mVelX -= DOT_VEL; break;
			case SDLK_RIGHT: mVelX += DOT_VEL; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: mVelY += DOT_VEL; break;
			case SDLK_DOWN: mVelY -= DOT_VEL; break;
			case SDLK_LEFT: mVelX += DOT_VEL; break;
			case SDLK_RIGHT: mVelX -= DOT_VEL; break;
			}
		}
	}

	bool Dot::move(SDL_Rect& wall)
	{
		//Move the dot left or right
		mPosX += mVelX;
		mCollider.x = mPosX;

		bool hasCollided = ballCheckCollisionPaddle(mCollider, wall);	
		bool hasCollidedBrick;

		hasCollided |= CC_CheckBrickCollision(this);

		//If the dot collided or went too far to the left or right
		if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH) || hasCollided)
		{									
				//Move back
				mPosX -= mVelX;
				mCollider.x = mPosX;
				mVelX = -mVelX;		
		}

		//Move the dot up or down
		mPosY += mVelY;
		mCollider.y = mPosY;

		hasCollided = ballCheckCollisionPaddle(mCollider, wall);

		hasCollidedBrick = CC_CheckBrickCollision(this);

		//If the dot collided with the paddle
		if (hasCollided)
		{
			//Move back
			mPosY -= mVelY;
			mCollider.y = mPosY;
			// mVelY = -mVelY;
			
			// Calculate new angle
			int paddleCenter = wall.x + wall.w / 2;

			int paddleCenterLeft = paddleCenter - wall.w / 5 + 10;
			int paddleCenterRight = paddleCenter + wall.w / 5 - 10;

			int paddleLeft = paddleCenter - (wall.w / 10) - (wall.w / 5);
			int paddleRight = paddleCenter + (wall.w / 10) + (wall.w / 5);			

			int paddleEdgeLeft = wall.x;
			int paddleEdgeRight = wall.x + wall.w;

			int dotCenter = mCollider.x + mCollider.w / 2;			
			
			if (hasCollided)
			{
				// the dot has collided with the paddle										
				if (dotCenter > paddleRight && dotCenter < paddleEdgeRight)
				{		
					mVelX = 5;
					mVelY = -2;
				}
				else if (dotCenter < paddleLeft && dotCenter > paddleEdgeLeft)
				{
					mVelX = -5;
					mVelY = -2;
				}
				else if (dotCenter < paddleRight && dotCenter > paddleCenterRight)
				{
					mVelX = 3;
					mVelY = -3;
				}
				else if (dotCenter > paddleLeft && dotCenter < paddleCenterLeft)
				{
					mVelX = -3;
					mVelY = -3;
				}
				else if (dotCenter < paddleCenterRight && dotCenter > paddleCenterLeft)
				{
					mVelX = 0;
					mVelY = -3;
				}
				
			}					
		}

		// if the ball has collided with a brick or gone too far up
		if ((mPosY < 0) || hasCollidedBrick)
		{
			mPosY -= mVelY;
			mCollider.y = mPosY;
			mVelY = -mVelY;
		}

		return hasCollided;

	}

	bool ballCheckCollisionPaddle(SDL_Rect a, SDL_Rect b)
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

	void Dot::reset(void)
	{
		mPosX = DOT_RESET_POS_X;
		mPosY = DOT_RESET_POS_Y;
		mVelX = mVelY = 3;
	}

	void Dot::GetCoordinates(int *x, int *y)
	{
		*x = mPosX;
		*y = mPosY;
	}

} // namespace
