#include "mocktimercontroller.h"
#include <iostream>

namespace SDK
{
	bool TestTimerController::Run() 
	{
		return true;
	}

	const TimerController::TQueue& TestTimerController::TimerQueue()
	{
		return TimerController::timers_;
	}

	void TestTimerController::SetTestInstance()
	{
		if (NULL != TimerController::TheInstance)
		{
			delete TimerController::TheInstance;
		}	

		TimerController::TheInstance = new TestTimerController;
	}
}
