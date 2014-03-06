#ifndef ICONDVAR_H_
#define ICONDVAR_H_

#include <cstdlib>

namespace SDK
{
	class ICondVar
	{
		public:
			ICondVar() {}
			virtual ~ICondVar() {}

		public:
			virtual bool Wait() = 0;
			virtual bool Wait(unsigned int sec, bool* timedOut = NULL) = 0;
			virtual bool Signal() = 0;

		private:
			virtual bool Init() = 0;

		private:
			ICondVar(const ICondVar&);
			ICondVar& operator=(const ICondVar&);
	};
}

#endif // ICONDVAR_H_
