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
//			bool Add(TimerImpl* t);

		private:
			virtual bool Run();

		public:
			static void SetTestInstance();
//			static void DeleteTimerImpl(TimerImpl*& p);
//			const TimerController::TQueue& TimerQueue();
	};
}

#endif // TESTTIMERCONTROLLER_H_
