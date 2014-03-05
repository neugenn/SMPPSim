#ifndef TIMER_H_
#define TIMER_H_

namespace SDK
{
	class TimerImpl;

	class Timer
	{
		public:
			Timer();
			~Timer();

		private:
			Timer(const Timer&);
			Timer& operator=(const Timer&);

		public:
			bool IsRunning() const;
			void Start(unsigned int sec = 10);
			void Stop();

		protected:
			TimerImpl* impl_;
	};
}

#endif //TIMER_H_
