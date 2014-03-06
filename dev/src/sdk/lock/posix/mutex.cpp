#include "mutex.h"
#include <iostream>

namespace SDK
{
	namespace POSIX
	{
		Mutex::Mutex() : ILock(), t_(), m_()
		{
			/*
			pthread_mutexattr_init(&t_);
			pthread_mutexattr_settype(&t_, PTHREAD_MUTEX_RECURSIVE);
			*/
			pthread_mutex_init(&m_, NULL);
		}

		Mutex::~Mutex() 
		{
			pthread_mutex_destroy(&m_);
			pthread_mutexattr_destroy(&t_);
		}

		bool Mutex::Lock()
		{
			int r = pthread_mutex_lock(&m_);
			return (0 == r);
		}

		bool Mutex::TryLock()
		{
			int r = pthread_mutex_trylock(&m_);
			return (0 == r);
		}

		bool Mutex::Unlock()
		{
			int r = pthread_mutex_unlock(&m_);
			return (0 == r);
		}

		pthread_mutex_t& Mutex::Impl()
		{
			return m_;
		}
	}
}
