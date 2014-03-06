#ifndef CONDITION_H_
#define CONDITION_H_

#include "ICondVar.h"
#include <pthread.h>

namespace SDK
{
	class ILock;
	namespace POSIX
	{
		class Mutex;
		class Condition : public ICondVar
		{
			public:
				Condition(ILock& m);
				~Condition();

			public:
				virtual bool Wait();
				virtual bool Wait(unsigned int sec, bool* timedOut = NULL);
				virtual bool Signal();

			private:
				virtual bool Init();

			private:
				ILock& m_;
				pthread_cond_t cond_;
		};
	}
}

#endif // CONDITION_H_
