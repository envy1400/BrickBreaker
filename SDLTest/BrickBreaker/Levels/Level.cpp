/*********************************
Filename	: Level.cpp
Purpose		: Implements the level class
Author		: Nick Vinyard
**/
#define LEVEL_CPP

#include "Level.h"

namespace BrickBreaker
{
	int Level::GetNumberOfBricksLeft(void)
	{
		return NumberOfBricksLeft;
	}

	Level::Level(Brick *levelBricks, int numOfBricks) : LevelBricks(levelBricks), NumberOfBricks(numOfBricks),NumberOfBricksLeft(numOfBricks)
	{		
	}
}