#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <cassert>
#include <cstdlib>
#include "lock.h"

namespace SDK
{
	template <class T> class SharedPtr
	{
		private:
			typedef SharedPtr<T> TNode;

		private:
			static Lock lock_;

		public:
			SharedPtr(T* p = NULL) :
				resource_(p),
				prev_(this),
				next_(this)
			{
			}

			SharedPtr(const SharedPtr<T>& rsh) :
				resource_(NULL),
				prev_(NULL),
				next_(NULL)
			{
				LockGuard l(lock_);
				this->Acquire(rsh);
			}

			~SharedPtr()
			{
				this->Release();
				if (!this->IsSingleNode())
				{
					LockGuard l(lock_);
					next_->prev_ = prev_;
					prev_->next_ = next_;
					prev_ = NULL;
					next_ = NULL;
					resource_ = NULL;
				}
			}

			SharedPtr<T>& operator=(const SharedPtr<T>& rsh)
			{
				if (this != &rsh)
				{
					LockGuard l(lock_);
					this->Release();
					this->Acquire(rsh);
				}

				return *this;
			}

			T& operator*() const
			{
				assert(NULL != resource_);
				return *resource_;
			}

			T* operator->() const
			{
				return resource_;
			}

#ifdef UNIT_TEST
		public:
#else
		private:
#endif
			bool IsSingleNode() const
			{
				return (this == prev_ && this == next_);
			}

			size_t Counter() const
			{
				const TNode* node = next_;
				size_t count = 1;
				while (this != node)
				{
					++count;
					node = node->next_;
				}

				return count;
			}

			void Acquire(const TNode& r)
			{
				resource_ = r.resource_;
				prev_ = &r;
				next_ = r.next_;
				next_->prev_ = this;
				r.next_ = this;
			}

			void Release()
			{
				if (this->IsSingleNode())
				{
					delete resource_;
					resource_ = NULL;
				}
			}

		private:
			T* resource_;
			mutable const TNode* prev_;
			mutable const TNode* next_;
	};

	template <class T> Lock SharedPtr<T>::lock_;
}

#endif // SHAREDPTR_H
