#ifndef TIMERCALLBACK_H
#define TIMERCALLBACK_H

namespace SDK
{
	class TimerCallback
	{
		public:
			TimerCallback() {}
			virtual ~TimerCallback() {}

		public:
			virtual void Elapsed() = 0;
	};
}

#endif // TIMERCALLBACK_H
