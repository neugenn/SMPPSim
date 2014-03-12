#ifndef CONDVAR_H
#define CONDVAR_H

#include <cstdlib>

namespace SDK
{
	class ICondVar;
	class Lock;

	class CondVar
	{
		public:
			CondVar(Lock& l);
			virtual ~CondVar();

		public:
			virtual bool Wait();
			virtual bool Wait(unsigned int sec, bool* timedOut = NULL);
			virtual bool Signal();

		private:
			CondVar(const CondVar&);
			CondVar& operator=(const CondVar&);

		private:
			ICondVar* impl_;
	};
}

#endif // CONDVAR_H
