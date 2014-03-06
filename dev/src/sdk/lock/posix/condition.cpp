#include "condition.h"
#include "mutex.h"
#include <sys/time.h>
#include <errno.h>

namespace SDK
{
	namespace POSIX
	{
		Condition::Condition(ILock& m) : m_(m), cond_()
		{
			this->Init();
		}

		Condition::~Condition()
		{
			pthread_cond_destroy(&cond_);
		}

		bool Condition::Init()
		{
			int res = pthread_cond_init(&cond_, NULL);
			return (0 == res);
		}

		bool Condition::Wait()
		{
			Mutex& p = dynamic_cast<Mutex&>(m_);
			int r = pthread_cond_wait(&cond_, &(p.Impl()));
			return (0 == r);
		}

		bool Condition::Wait(unsigned int sec, bool* timedOut /* = NULL */)
		{
			timeval now;
			gettimeofday(&now, NULL);

			struct timespec time;
			time.tv_sec = now.tv_sec + sec;
			time.tv_nsec = now.tv_usec * 1000;

			Mutex& p = dynamic_cast<Mutex&>(m_);
			int r = pthread_cond_timedwait(&cond_, &(p.Impl()), &time);
			if (NULL != timedOut)
			{
				*timedOut = (ETIMEDOUT == r) ? true : false;
			}

			return (0 == r || ETIMEDOUT == r);
		}

		bool Condition::Signal()
		{
			int r = pthread_cond_signal(&cond_);
			return (0 == r);
		}
	}
}
