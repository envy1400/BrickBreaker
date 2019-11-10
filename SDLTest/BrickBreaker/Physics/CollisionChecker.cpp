#define COLLISION_CHECKER_C

#include "../Config/SystemConfig.h"
#include "CollisionChecker.h"

namespace BrickBreaker
{
	static Level *pCurrentLevel;

	bool CC_CheckBallDie(Dot *ball)
	{
		bool ballDied = false;
		if (ball->mPosY + ball->DOT_HEIGHT > SCREEN_HEIGHT)
		{
			// paddle has missed
			ballDied = true;
			ball->mVelX = 0;
			ball->mVelY = 0;			
		}
		return ballDied;
	}
	
	bool CC_CheckBallPaddleCollision(Dot &ball, Paddle &paddle)
	{
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;
		SDL_Rect ballRect = ball.mCollider;


		//Calculate the sides of rect A
		leftA = ballRect.x;
		rightA = ballRect.x + ballRect.w;
		topA = ballRect.y;
		bottomA = ballRect.y + ballRect.h;

		//Calculate the sides of rect B
		leftB = paddle.x;
		rightB = paddle.x + paddle.w;
		topB = paddle.y;
		bottomB = paddle.y + paddle.h;

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

	bool CC_CheckBrickCollision(Dot *ball)
	{
		Brick *checkingBrick;
		
		for (int i = 0; i < pCurrentLevel->NumberOfBricks; i++)
		{
			checkingBrick = &pCurrentLevel->LevelBricks[i];
			if (checkingBrick == NULL)
			{
				continue;
			}

			if (!checkingBrick->IsCollidable)
			{
				continue;
			}

			//The sides of the rectangles
			int leftA, leftB;
			int rightA, rightB;
			int topA, topB;
			int bottomA, bottomB;
			SDL_Rect ballRect = ball->mCollider;

			//Calculate the sides of rect A
			leftA = ballRect.x;
			rightA = ballRect.x + ballRect.w;
			topA = ballRect.y;
			bottomA = ballRect.y + ballRect.h;

			//Calculate the sides of rect B
			leftB = checkingBrick->x;
			rightB = checkingBrick->x + checkingBrick->w;
			topB = checkingBrick->y;
			bottomB = checkingBrick->y + checkingBrick->h;

			//If any of the sides from A are outside of B
			if (bottomA <= topB)
			{
				continue;
			}

			if (topA >= bottomB)
			{
				continue;
			}

			if (rightA <= leftB)
			{
				continue;
			}

			if (leftA >= rightB)
			{
				continue;
			}

			//If none of the sides from A are outside B		
			// checkingBrick->IsCollidable = false;
			// checkingBrick->IsVisible = false;
			checkingBrick->Break();
			pCurrentLevel->NumberOfBricksLeft--;

			return true;
		}		
		return false;
	}

	void CC_SetLevel(Level &level)
	{
		pCurrentLevel = &level;
	}

	bool CC_CheckPaddleSideCollision(Dot &ball, SDL_Rect &wall)
	{
		int ballX, ballY;

		ball.GetCoordinates(&ballX, &ballY);

		int ballLeftSide = ballX;
		int ballRightSide = ballX + ball.DOT_WIDTH;
		int wallLeftSide = wall.x;
		int wallRightSide = wall.x + wall.w;

		// if()
		return false;
	}
}