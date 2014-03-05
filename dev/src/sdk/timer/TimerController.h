#ifndef TIMER_CONTROLLER_H_
#define TIMER_CONTROLLER_H_

#include <vector>
#include "lock.h"
#include "thread.h"
#include "timerimpl.h"

namespace SDK
{
	class TimerImpl;

	class TimerController : public Thread
	{
		public:
			static TimerController& GetInstance();

		protected:
			explicit TimerController();

		public:
			virtual ~TimerController();

			bool Add(TimerImpl* t);
			void Remove(const TimerImpl* t);
			bool Manages(timer_id_t id);

		private:
			virtual bool Run();

		private:
			static TimerController* TheInstance;
			std::vector<TimerImpl*> timers_;
			Lock lock_;
	};
}

#endif // TIMER_CONTROLLER_H_
