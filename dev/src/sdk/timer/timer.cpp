#include <cstddef>
#include "timer.h"
#include "TimerController.h"

namespace SDK
{
	Timer::Timer(unsigned int sec) : impl_(new SDK::TimerImpl(sec))
	{
	}

	Timer::~Timer()
	{
		if (NULL != impl_)
		{
			delete impl_;
			impl_ = NULL;
		}
	}

	bool Timer::IsRunning() const
	{
		return false;
	}

	void Timer::Start()
	{
	}

	void Timer::Stop()
	{
	}
}
