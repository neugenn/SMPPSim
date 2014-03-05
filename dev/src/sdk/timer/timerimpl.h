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
			explicit TimerImpl();
			~TimerImpl();

			timer_id_t GetID() const;

			bool IsSingleShot() const;
			void EnableSingleShot();
			bool IsDetached() const;
			void SetDetached();
			bool IsDefunct() const;
			void SetDefunct();
			bool IsActive() const;
			void SetActive();
			void SetInactive();
			void SetTimeout(unsigned int sec);

			bool Elapsed() const;
			void Reset();

		private:
			TimerImpl(const TimerImpl&);
			TimerImpl& operator=(const TimerImpl&);

		private:
			static timer_id_t GenerateId();
			static timer_id_t ID;
			static Lock lock_;

		private:
			bool active_;
			bool singleShot_;
			bool detached_;
			bool defunct_;
			time_t end_;
			unsigned int delta_;
			const timer_id_t id_;
	};

	bool operator==(const TimerImpl& lsh, const TimerImpl& rsh);
}

#endif // TIMERIMPL_H
