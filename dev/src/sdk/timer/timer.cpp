#include <cstddef>
#include "timer.h"
#include "TimerController.h"
#include <iostream>

namespace SDK
{
	Timer::Timer(TimerCallback* cbk /* = NULL */) : impl_(new SDK::TimerImpl(cbk))
	{
	}

	Timer::~Timer()
	{
		this->Stop();
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

		impl_->SetActive();
		impl_->SetTimeout(sec);
		TimerController::GetInstance().Add(impl_);
	}

	void Timer::Stop()
	{
		impl_->SetInactive();
	}

	/*
	void Timer::Reset()
	{
		impl_->Reset();
	}
	*/

	timer_id_t Timer::GetID() const
	{
		return impl_->GetID();
	}
}
