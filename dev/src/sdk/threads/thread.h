#ifndef THREAD_H_
#define THREAD_H_

namespace SDK
{
	class IThread;

	class Thread
	{
		public:
			Thread();
			virtual ~Thread();
		
		private:
			Thread(const IThread&);
			Thread& operator=(const IThread&);

		public:
			bool Start();
			void Stop();
			bool Wait();
			bool IsRunning() const;

		private:
			virtual bool Run() = 0;

		private:
			friend class IThread;
			IThread* impl_;
	};
}

#endif // THREAD_H_
