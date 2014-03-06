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
			~CondVar();

		public:
			bool Wait();
			bool Wait(unsigned int sec, bool* timedOut = NULL);
			bool Signal();

		private:
			CondVar(const CondVar&);
			CondVar& operator=(const CondVar&);

		private:
			ICondVar* impl_;
	};
}

#endif // CONDVAR_H
