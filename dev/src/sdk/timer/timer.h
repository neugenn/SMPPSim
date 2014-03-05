#ifndef TIMER_H_
#define TIMER_H_

namespace SDK
{
	class TimerImpl;

	class Timer
	{
		public:
			explicit Timer(unsigned int sec);
			~Timer();

		private:
			Timer(const Timer&);
			Timer& operator=(const Timer&);

		public:
			bool IsRunning() const;
			void Start();
			void Stop();

		private:
			TimerImpl* impl_;
	};
}

#endif //TIMER_H_
