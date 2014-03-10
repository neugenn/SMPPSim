#include "lock.h"
#include "mutex.h"

namespace SDK
{
	Lock::Lock() : impl_(new POSIX::Mutex) 
	{}

	Lock::~Lock() 
	{
		this->Release();
	}

	bool Lock::Acquire()
	{
		return impl_->Lock();
	}

	bool Lock::Release()
	{
		return impl_->Unlock();
	}

	LockGuard::LockGuard(Lock& l) : lock_(l)
	{
		lock_.Acquire();
	}

	LockGuard::~LockGuard()
	{
		lock_.Release();
	}
}
