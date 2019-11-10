
#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>
#include "../Ball/Ball.h"
#include "../Graphics/LTexture.h"
#include <SDL_image.h>
#include "../Helpers/CallbackHelper.h"

namespace BrickBreaker
{	

	class Dot;

	class Paddle : public SDL_Rect {
	public:
		static const int PADDLE_HEIGHT = 10;
		static const int PADDLE_WIDTH = 100;

		static const int PADDLE_VEL = 10;

		int CollisionCount = 0;

		Paddle(void);

		void handleEvent(SDL_Event& e);

		void move(void);

		void leftKey(bool keyDown);

		void rightKey(bool keyDown);

		void calcVel(void);

		void hitBall(Dot& dot);		

		void reset(void);

		void RegisterHitCallback(BrickBreakCallback BreakCallback, void * pArgs);

	private:
		int mVelX;
		bool rightKeyDown = false, leftKeyDown = false;	
	};

}


#endif // #ifdef PADDLE_H
