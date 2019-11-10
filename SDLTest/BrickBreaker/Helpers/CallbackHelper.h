/*********************************
	Filename	: CallbackHelper.h
	Purpose		: This file defines a callback struct for re
					registering callbacks
	Author		: Nick Vinyard
**/

#ifndef CALLBACK_HELPER_H
#define CALLBACK_HELPER_H

namespace BrickBreaker
{
	typedef void(*BrickBreakCallback)(void *pArgs);

	typedef struct CallbackHelper_t CallbackHelper_t;
	struct CallbackHelper_t 
	{
		BrickBreakCallback callback;
		void * pArgs;
	};
}

#endif // CALLBACK_HELPER_H