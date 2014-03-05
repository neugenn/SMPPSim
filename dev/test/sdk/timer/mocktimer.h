#ifndef TESTTIMER_H_
#define TESTTIMER_H_

#include "timer.h"
#include "timerimpl.h"

namespace SDK
{
	class TestTimer : public Timer
	{
		public:
			TestTimer() : Timer() {}
			~TestTimer() {}

		public:
			const TimerImpl* Impl() const;
	};
}

#endif // TESTTIMER_H_
