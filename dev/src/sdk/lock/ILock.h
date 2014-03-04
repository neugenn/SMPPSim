#ifndef ILOCK_H_
#define ILOCK_H_

namespace SDK
{
	class ILock
	{
		public:
			ILock() {};
			virtual ~ILock() {};

		public:
			virtual bool Lock() = 0;
			virtual bool TryLock() = 0;
			virtual bool Unlock() = 0;

		private:
			ILock(const ILock&);
			ILock& operator=(const ILock&);
	};	
}

#endif // ILOCK_H_
