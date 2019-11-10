/*********************************
Filename	: Brick.h
Purpose		: Defines the brick class
Author		: Nick Vinyard
**/
#ifndef LEVEL_ARRAYS_H
#define LEVEL_ARRAYS_H

#include <SDL.h>
#include "..\Bricks\Brick.h"
#include "Level.h"

namespace BrickBreaker
{
#define NUMBER_OF_LEVELS 2

	Brick Level1Array[5] = { Brick(50, 30, BRICK_COLOR_RED), Brick(100, 30, BRICK_COLOR_ORANGE), Brick(150, 30, BRICK_COLOR_YELLOW), Brick(200, 30, BRICK_COLOR_GREEN), 
		Brick(250, 30, BRICK_COLOR_BLUE) };

	Level level1(Level1Array, 5);	

	Brick Level2Array[10] = { Brick(50, 30, BRICK_COLOR_RED), Brick(100, 30, BRICK_COLOR_ORANGE), Brick(150, 30, BRICK_COLOR_YELLOW), Brick(200, 30, BRICK_COLOR_GREEN), 
		Brick(250, 30, BRICK_COLOR_BLUE), Brick(55, 40, BRICK_COLOR_PURPLE), Brick(105, 40, BRICK_COLOR_BLUE), Brick(155, 40, BRICK_COLOR_GREEN), Brick(205, 40, BRICK_COLOR_YELLOW), 
		Brick(255, 40, BRICK_COLOR_ORANGE) };

	Level level2(Level2Array, 10);	

	Level *MasterLevelArray[NUMBER_OF_LEVELS] = { &level1, &level2 };
} // namespace

#endif