#include "condvar.h"
#include "lock.h"
#include "condition.h"

namespace SDK
{
	CondVar::CondVar(Lock& l) : impl_(NULL)
	{
		impl_ = new POSIX::Condition(*l.impl_);
	}

	CondVar::~CondVar()
	{
		if (NULL != impl_)
		{
			delete impl_;
			impl_ = NULL;
		}
	}

	bool CondVar::Wait()
	{
		return impl_->Wait();
	}

	bool CondVar::Wait(unsigned int sec, bool* timedOut /* = NULL */)
	{
		return impl_->Wait(sec, timedOut);
	}

	bool CondVar::Signal()
	{
		return impl_->Signal();
	}
}

