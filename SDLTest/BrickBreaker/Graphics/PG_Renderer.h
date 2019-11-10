#ifndef PG_RENDERER_H
#define PG_RENDERER_H

#include "../Paddle/Paddle.h"
#include "../Ball/Ball.h"

namespace BrickBreaker
{

	bool InitPGRenderer();

	void PG_RenderPaddle(Paddle * paddle);

	void PG_RenderDot(Dot * dot);

	void PG_RenderTasks(void);

	void PG_AddDot(Dot *dot);

	void PG_AddPaddle(Paddle *paddle);

	void PG_RenderMenu(void);

	void PG_RenderDeathScreen(void);

	void PG_RenderLevelCompleteScreen(void);

	void PG__RenderGameCompleteScreen(void);

	void PG_SetLevel(Level &level);

	void PG_RenderBrick(Brick * const &brick);

	void PG_RenderPausedMenu(int selectedIndex);

	void PG_RenderPausedOptions(int selectedIndex);
}

#endif // PG_RENDERER_H
