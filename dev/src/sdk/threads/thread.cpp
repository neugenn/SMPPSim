#include "thread.h"
#include "posixthread.h"
#include <cassert>
#include <iostream>

namespace SDK
{
	Thread::Thread() : impl_(new PosixThread(*this))
	{
		assert(NULL != impl_);
	}

	Thread::~Thread()
	{
		if (NULL != impl_)
		{
			delete impl_;
			impl_ = NULL;
		}
	}

	bool Thread::Start() 
	{
		return impl_->Start();
	}

	void Thread::Stop()
	{
		return impl_->Stop();
	}

	bool Thread::IsRunning() const
	{
		return true;
	}

	bool Thread::Wait()
	{
		return impl_->Join();
	}
}
