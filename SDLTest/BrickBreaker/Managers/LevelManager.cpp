/*********************************
Filename	: LevelManager.cpp
Purpose		: Implements the level manager responsible
				for maintaining a level
Author		: Nick Vinyard
**/
#define LEVEL_MANAGER_CPP

#include "..\Levels\Level.h"
#include "LevelManager.h"
#include "SoundManager/SoundManager.h"

namespace BrickBreaker
{

	void LM_ResetLevel(Level &level)
	{
		level.NumberOfBricksLeft = level.NumberOfBricks;

		for (int i = 0; i < level.NumberOfBricks; i++)
		{
			level.LevelBricks[i].IsCollidable = true;
			level.LevelBricks[i].IsVisible = true;
			level.LevelBricks[i].RegisterBreakCallback(_SM_BrickBreakCallback, NULL);
		}
	}

} // namespace