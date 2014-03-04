#ifndef TIMER_CONTROLLER_H_
#define TIMER_CONTROLLER_H_

#include <vector>
#include <time.h>
#include "lock.h"
#include "thread.h"

namespace SDK
{
	class TimerImpl;
	typedef unsigned int timer_id_t;

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

	class TimerImpl
	{
		public:
			explicit TimerImpl(unsigned int sec);
			~TimerImpl();

			timer_id_t GetID() const;
			bool IsActive() const;
			bool Elapsed() const;
			void Register();
			void Unregister();
			void Reset();

		private:
			static timer_id_t GenerateId();
			static timer_id_t ID;
			static Lock lock_;

		private:
			const timer_id_t id_;
			const unsigned int delta_;
			time_t end_;
	};

	bool operator==(const TimerImpl& lsh, const TimerImpl& rsh);
}

#endif // TIMER_CONTROLLER_H_
