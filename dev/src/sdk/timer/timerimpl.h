#ifndef TIMERIMPL_H
#define TIMERIMPL_H

#include "lock.h"
#include <time.h>

namespace SDK
{
	typedef unsigned int timer_id_t;

	class TimerImpl
	{
		public:
			explicit TimerImpl(unsigned int sec = 0);
			~TimerImpl();

			timer_id_t GetID() const;

			bool IsSingleShot() const;
			void EnableSingleShot();
			bool Elapsed() const;
			void Reset();

		private:
			static timer_id_t GenerateId();
			static timer_id_t ID;
			static Lock lock_;

		private:
			const timer_id_t id_;
			const unsigned int delta_;
			bool singleShot_;
			time_t end_;
	};

	bool operator==(const TimerImpl& lsh, const TimerImpl& rsh);
}

#endif // TIMERIMPL_H
