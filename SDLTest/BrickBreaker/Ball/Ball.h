
#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "../Paddle/Paddle.h"
#include "../Graphics/LTexture.h"
#include "../Bricks/Brick.h"

namespace BrickBreaker
{
	class Brick;

	class Dot
	{
	public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent(SDL_Event& e);

		//Moves the dot and checks collision
		bool move(SDL_Rect& wall);

		void reset(void);

		//Shows the dot on the screen
		void render();

		void GetCoordinates(int *x, int *y);

		friend class Paddle;

		friend void PG_RenderDot(Dot * dot);

		friend bool CC_CheckBallDie(Dot *ball);

		friend void PG_RemoveDot(Dot *dot);

		friend bool CC_CheckBallPaddleCollision(Dot &ball, Paddle &paddle);

		friend bool CC_CheckBrickCollision(Dot *ball);		

	private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//Dot's collision box
		SDL_Rect mCollider;

		// Dot ID
		int ID;
	};
}

#endif // #ifndef BALL_H
