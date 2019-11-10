#ifndef LEVEL_H
#define LEVEL_H

namespace BrickBreaker 
{
	class Brick;

	class Dot;

	class Level
	{
	public :
		Level(Brick *levelBricks, int numOfBricks);
		int GetNumberOfBricksLeft(void);	
		Brick *LevelBricks;
		const int NumberOfBricks;
		friend bool CC_CheckBrickCollision(Dot *ball);
		friend void LM_ResetLevel(Level &level);
	private:
		int NumberOfBricksLeft;
	};
}

#endif // LEVEL_H
