#ifndef MUTEX_H_
#define MUTEX_H_

#include "ILock.h"
#include <pthread.h>

namespace SDK
{
	namespace POSIX
	{
		class Mutex : public ILock
		{
			public:
				Mutex();
				~Mutex();

			public:
				virtual bool Lock();
				virtual bool TryLock();
				virtual bool Unlock();
				pthread_mutex_t& Impl();

			private:
				pthread_mutexattr_t t_;
				pthread_mutex_t m_;
		};
	}
}

#endif // MUTEX_H_
