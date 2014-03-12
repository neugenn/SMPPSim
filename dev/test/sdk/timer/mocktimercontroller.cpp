#include "mocktimercontroller.h"
#include <iostream>

namespace SDK
{
	namespace TEST
	{
		TimerController::TimerController(Lock* pl, TEST::CondVar* pc) : 
			SDK::TimerController(pl, pc),
			cond_(pc)
		{
		}

		bool TimerController::Run() 
		{
			return true;
		}

		const SDK::TimerController::TQueue& TimerController::TimerQueue()
		{
			return SDK::TimerController::timers_;
		}

		TimerController* TimerController::GetTestInstance()
		{
			TEST::TimerController* controller = NULL;
			if (NULL == SDK::TimerController::TheInstance)
			{
				Lock* pl = new Lock();
				TEST::CondVar* pc = new TEST::CondVar(*pl);
				controller = new TimerController(pl, pc);
				SDK::TimerController::TheInstance = controller;
				pc = NULL;
				pl = NULL;
			}

			return controller;
		}

		void TimerController::ReleaseTestInstance(TimerController*& p)
		{
			p = NULL;

			if (NULL != SDK::TimerController::TheInstance)
			{
				delete SDK::TimerController::TheInstance;
				SDK::TimerController::TheInstance = NULL;
			}
		}

		bool TimerController::RunEventLoop()
		{
			return SDK::TimerController::RunEventLoop();
		}
	}
}

