#include "mocktimer.h"

namespace SDK
{
	const TimerImpl* TestTimer::Impl() const
	{
		return impl_;
	}
}
