#ifndef TIMER_H_
#define TIMER_H_

#include <cstdlib>
#include "timercallback.h"
#include "sharedptr.h"
#include "timerid.h"

namespace SDK
{
	class TimerImpl;
	class TimerCallback;

	class Timer
	{
		public:
			Timer(TimerCallback* cbk = NULL);
			~Timer();

		private:
			Timer(const Timer&);
			Timer& operator=(const Timer&);

		public:
			bool IsRunning() const;
			void Start(unsigned int sec);
			void Stop();
			void SetSingleShot();
			timer_id_t GetID() const;

		protected:
			SDK::SharedPtr<TimerImpl> impl_;
	};
}

#endif //TIMER_H_
