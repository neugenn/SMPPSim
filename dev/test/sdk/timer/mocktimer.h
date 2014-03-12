#ifndef TESTTIMER_H_
#define TESTTIMER_H_

#include "timer.h"
#include "timerimpl.h"

namespace SDK
{
	namespace TEST
	{
		class Timer : public SDK::Timer
		{
			public:
				Timer(SDK::TimerCallback* c = NULL) : SDK::Timer(c) {}
				~Timer() {}

			public:
				SharedPtr<TimerImpl>& Impl();
		};
	}
}

#endif // TESTTIMER_H_
