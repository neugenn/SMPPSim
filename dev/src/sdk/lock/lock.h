#ifndef LOCK_H_
#define LOCK_H_

#include <memory>

namespace SDK
{
	class ILock;

	class Lock
	{
		public:
			Lock();
			~Lock();

		private:
			Lock(const Lock&);
			Lock& operator=(const Lock&);

		public:
			bool Acquire();
			bool Release();

		private:
			std::auto_ptr<ILock> impl_;
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
