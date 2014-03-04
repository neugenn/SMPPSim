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

	bool Timer::IsActive() const
	{
		return impl_->IsActive();
	}

	void Timer::Start()
	{
		impl_->Register();
	}

	void Timer::Stop()
	{
		impl_->Unregister();
	}
}
