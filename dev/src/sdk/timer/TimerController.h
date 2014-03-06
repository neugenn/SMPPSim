#ifndef TIMER_CONTROLLER_H_
#define TIMER_CONTROLLER_H_

#include <queue>
#include <functional>
#include "lock.h"
#include "thread.h"
#include "condvar.h"
#include "timerimpl.h"

namespace SDK
{

	template<typename Type, typename Compare = std::greater<Type> >
	struct pless : public std::binary_function<Type*, Type*, bool>
	{
		bool operator()(const Type *x, const Type *y) const
		{
			return Compare()(*x, *y);
		}
	};

	class TimerController : public Thread
	{
		public:
			typedef std::priority_queue<TimerImpl*, std::vector<TimerImpl*>, pless<TimerImpl> > TQueue;
			static TimerController& GetInstance();

		protected:
			explicit TimerController();

		public:
			virtual ~TimerController();
			void Add(TimerImpl* t);

		private:
			virtual bool Run();

		protected:
			static TimerController* TheInstance;
			TQueue timers_;

		private:
			Lock queueLock_;
			CondVar queueReady_;
	};
}

#endif // TIMER_CONTROLLER_H_
