#include "timerimpl.h"

namespace SDK
{
	TimerImpl::TimerImpl(unsigned int sec) : id_(GenerateId()), delta_(sec), singleShot_(false), end_(time(NULL) + sec)
	{}

	TimerImpl::~TimerImpl()
	{
	}

	bool TimerImpl::Elapsed() const
	{
		return (time(NULL) >= end_);
	}

	void TimerImpl::Reset()
	{
		end_ = time(NULL) + delta_;
	}

	bool TimerImpl::IsSingleShot() const
	{
		return singleShot_;
	}

	void TimerImpl::EnableSingleShot()
	{
		singleShot_ = true;
	}

	timer_id_t TimerImpl::GetID() const
	{
		return id_;
	}

	timer_id_t TimerImpl::ID = 0;
	Lock TimerImpl::lock_;

	timer_id_t TimerImpl::GenerateId()
	{
		LockGuard l(TimerImpl::lock_);
		return ++ID;
	}

	bool operator==(const TimerImpl& lsh, const TimerImpl& rsh)
	{
		return (lsh.GetID() == rsh.GetID());
	}
}
