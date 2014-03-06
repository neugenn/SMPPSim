#include "timerimpl.h"

namespace SDK
{
	TimerImpl::TimerImpl(TimerCallback* cbk /* = NULL */) :
			active_(false),
			singleShot_(false),
			detached_(false),
			defunct_(false),
			end_(0),
			delta_(0),
			id_(GenerateId()),
			cbk_(cbk),
			propLock_()
	{}

	TimerImpl::~TimerImpl()
	{
	}

	time_t TimerImpl::SecUntilElapse() const
	{
		return end_ - time(NULL);
	}

	void TimerImpl::Reset()
	{
		end_ = time(NULL) + delta_;
	}

	bool TimerImpl::IsSingleShot() const
	{
//		LockGuard l(propLock_);
		return singleShot_;
	}

	void TimerImpl::EnableSingleShot()
	{
		LockGuard l(propLock_);
		singleShot_ = true;
	}

	bool TimerImpl::IsDetached() const
	{
//		LockGuard l(propLock_);
		return detached_;
	}

	void TimerImpl::SetDetached()
	{
		LockGuard l(propLock_);
		detached_ = true;
	}

	bool TimerImpl::IsDefunct() const
	{
//		LockGuard l(propLock_);
		return defunct_;
	}

	void TimerImpl::SetDefunct()
	{
		LockGuard l(propLock_);
		defunct_ = true;
	}

	bool TimerImpl::IsActive() const
	{
//		LockGuard l(propLock_);
		return active_;
	}

	void TimerImpl::SetActive()
	{
		LockGuard l(propLock_);
		active_ = true;
	}

	void TimerImpl::SetInactive()
	{
		LockGuard l(propLock_);
		active_ = false;
	}

	void TimerImpl::SetTimeout(unsigned int sec)
	{
		LockGuard l(propLock_);
		delta_ = sec;
		this->Reset();
	}

	TimerCallback* TimerImpl::GetCallback()
	{
		return cbk_;
	}

	timer_id_t TimerImpl::GetID() const
	{
		return id_;
	}

	timer_id_t TimerImpl::ID = 0;
	Lock TimerImpl::idLock_;

	timer_id_t TimerImpl::GenerateId()
	{
		LockGuard l(TimerImpl::idLock_);
		return ++ID;
	}

	bool operator==(const TimerImpl& lsh, const TimerImpl& rsh)
	{
		return (lsh.GetID() == rsh.GetID());
	}

	bool operator>(const TimerImpl& lsh, const TimerImpl& rsh)
	{
		return (lsh.SecUntilElapse() > rsh.SecUntilElapse());
	}
}
