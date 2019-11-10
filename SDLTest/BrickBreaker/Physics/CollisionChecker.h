
#ifndef COLLISION_CHECKER_H
#define COLLISION_CHECKER_H

#include "../Ball/Ball.h"
#include "..\Bricks\Brick.h"

namespace BrickBreaker
{

	bool CC_CheckBallDie(Dot *ball);

	bool CC_CheckBallPaddleCollision(Dot &ball, Paddle &paddle);

	bool CC_CheckBrickCollision(Dot *ball);

	void CC_SetLevel(Level &level);

	bool CC_CheckPaddleSideCollision(Dot &ball, SDL_Rect &wall);

}

#endif
