#include <cstddef>
#include "timer.h"
#include "TimerController.h"

namespace SDK
{
	Timer::Timer(TimerCallback* cbk /* = NULL */) : impl_(new SDK::TimerImpl(cbk))
	{
	}

	Timer::~Timer()
	{
		if (impl_->IsDetached())
		{
			impl_->SetDefunct();
		}
		else
		{
			delete impl_;
			impl_ = NULL;
		}
	}

	bool Timer::IsRunning() const
	{
		return impl_->IsActive();
	}

	void Timer::Start(unsigned int sec)
	{
		if (this->IsRunning())
		{
			return;
		}

		if (!impl_->IsDetached())
		{
			impl_->SetDetached();
		}

		impl_->SetActive();
		impl_->SetTimeout(sec);
		TimerController::GetInstance().Add(impl_);
	}

	void Timer::Stop()
	{
		impl_->SetInactive();
	}
}
