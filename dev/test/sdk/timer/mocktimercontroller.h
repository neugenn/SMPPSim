#ifndef TESTTIMERCONTROLLER_H_
#define TESTTIMERCONTROLLER_H_

#include "TimerController.h"

namespace SDK
{
	class TestTimerController : public TimerController
	{
		private:
			TestTimerController() : TimerController() {}
		public:
			~TestTimerController() {}

		private:
			virtual bool Run();

		public:
			static void SetTestInstance();
			const TimerController::TQueue& TimerQueue();
	};
}

#endif // TESTTIMERCONTROLLER_H_
