#include "timerimpl.h"

namespace SDK
{
	TimerImpl::TimerImpl() :
			active_(false),
			singleShot_(false),
			detached_(false),
			defunct_(false),
			end_(0),
			delta_(0),
			id_(GenerateId())
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

	bool TimerImpl::IsDetached() const
	{
		return detached_;
	}

	void TimerImpl::SetDetached()
	{
		detached_ = true;
	}

	bool TimerImpl::IsDefunct() const
	{
		return defunct_;
	}

	void TimerImpl::SetDefunct()
	{
		defunct_ = true;
	}

	bool TimerImpl::IsActive() const
	{
		return active_;
	}

	void TimerImpl::SetActive()
	{
		active_ = true;
	}

	void TimerImpl::SetInactive()
	{
		active_ = false;
	}

	void TimerImpl::SetTimeout(unsigned int sec)
	{
		delta_ = sec;
		this->Reset();
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
