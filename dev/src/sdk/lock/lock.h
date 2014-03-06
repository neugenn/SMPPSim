#ifndef LOCK_H_
#define LOCK_H_

namespace SDK
{
	class ILock;

	class Lock
	{
		public:
			Lock();
			~Lock();

		public:
			bool Acquire();
			bool Release();

		private:
			ILock* impl_;
			friend class CondVar;
	};

	class LockGuard
	{
		public:
			LockGuard(Lock& lr);
			~LockGuard();

		private:
			LockGuard(const LockGuard&);
			LockGuard& operator=(const LockGuard&);

		private:
			Lock& lock_;
	};
}

#endif // LOCK_H_
