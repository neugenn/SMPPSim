#ifndef ITHREAD_H_
#define ITHREAD_H_

#include "thread.h"
#include <cstdlib>

namespace SDK
{
	class IThread
	{
		public:
			IThread(Thread& tr) : r_(tr) {}
			virtual ~IThread() {}

		public:
			virtual bool Start() = 0;
			virtual void Stop() = 0;
			virtual bool Join() = 0;

		private:
			IThread(const IThread&);
			IThread& operator=(const IThread&);

		protected:
			static void* ThreadStart(void* data)
			{
				if (NULL == data)
				{
					return (void*) (-1);
				}

				IThread* pt = static_cast<IThread*>(data);
				bool res = pt->r_.Run();

				if (res)
				{
					return (void*) (0);
				}

				return (void*) (-1);
			}

		private:
			Thread& r_;
	};
}

#endif // ITHREAD_H_
