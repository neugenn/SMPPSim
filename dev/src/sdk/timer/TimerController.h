#ifndef TIMER_CONTROLLER_H_
#define TIMER_CONTROLLER_H_

#include <queue>
#include <functional>
#include "lock.h"
#include "thread.h"
#include "condvar.h"
#include "timerimpl.h"
#include "sharedptr.h"

namespace SDK
{

	template<typename Type, typename Compare = std::greater<Type> >
	struct pless : public std::binary_function<Type, Type, bool>
	{
		bool operator()(Type x, Type y) const
		{
			return (*x > *y);
		}
	};

	class TimerController : public Thread
	{
		public:
			typedef std::priority_queue<SharedPtr<TimerImpl>, std::vector<SharedPtr<TimerImpl> >, pless<SharedPtr<TimerImpl> > > TQueue;
			static TimerController& GetInstance();

		protected:
			explicit TimerController();
			explicit TimerController(
					Lock* l,
					CondVar* c
					);

		public:
			virtual ~TimerController();
			void Add(SharedPtr<TimerImpl>& t);

		private:
			virtual bool Run();

		protected:
			bool RunEventLoop();

		protected:
			static TimerController* TheInstance;
			TQueue timers_;

		private:
			SharedPtr<Lock> queueLock_;
			SharedPtr<CondVar> queueReady_;
	};
}

#endif // TIMER_CONTROLLER_H_
