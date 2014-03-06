#ifndef TIMER_H_
#define TIMER_H_

#include <cstdlib>
#include "timercallback.h"

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

		protected:
			TimerImpl* impl_;
	};
}

#endif //TIMER_H_
