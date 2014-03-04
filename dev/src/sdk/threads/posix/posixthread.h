#ifndef POSIX_THREAD_H_
#define POSIX_THREAD_H_

#include "IThread.h"
#include <pthread.h>

namespace SDK
{
	class PosixThread : public IThread
	{
		public:
			PosixThread(Thread& tr);
			~PosixThread();

		public:
			virtual bool Start();
			virtual void Stop();
			virtual bool Join();

		private:
			pthread_t tid_;
	};
}

#endif
