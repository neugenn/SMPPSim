#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <cassert>

namespace SDK
{
	template <class T> class SharedPtr
	{
		private:
			typedef SharedPtr<T>* TNodePtr;

		public:
			SharedPtr(T* p) :
				resource_(p),
				prev_(NULL),
				next_(NULL)
			{
				assert(NULL != p);
				prev_ = NULL;
				next_ = this;
			}

			SharedPtr(const SharedPtr<T>& rsh) :
				resource_(rsh.resource_),
				prev_(NULL),
				next_(NULL)
			{
				prev_ = rsh.next_;
				next_ = this;
				prev_->next_ = this;
			}

			~SharedPtr()
			{
				do
				{
					if (this->IsSingleNode())
					{
						this->ReleaseResource();
						break;
					}

					if (this->IsFirstNode())
					{
						next_->prev_ = NULL;
						break;
					}

					if (this->IsLastNode())
					{
						prev_->next_ = prev_;
						break;
					}

					next_->prev_ = prev_;
					prev_->next_ = next_;
					prev_ = NULL;
					next_ = NULL;
					resource_ = NULL;
				}
				while (false);
			}

			

			SharedPtr<T>& operator=(const SharedPtr<T>& rsh)
			{
			}

			const T operator*() const
			{
				return *resource_;
			}

#ifdef UNIT_TEST
		public:
#else
		private:
#endif
			bool IsSingleNode() const
			{
				return (NULL == prev_ && this == next_);
			}

			bool IsFirstNode() const
			{
				return (NULL == prev_);
			}

			bool IsLastNode() const
			{
				return (this == next_);
			}

			size_t Counter() const
			{
				return UpCounter() + DownCounter();
			}

			size_t DownCounter() const
			{
				size_t count = 1;
				if (this->IsFirstNode())
				{
					return count;
				}

				SDK::SharedPtr<T>* n = prev_;
				while (NULL != n)
				{
					++count;
					n = n->prev_;
				}

				return count;
			}

			size_t UpCounter() const
			{
				size_t count = 0;
				if (this->IsLastNode())
				{
					return count;
				}

				TNodePtr pnode = next_;
				TNodePtr plast = NULL;
				while (pnode != plast)
				{
					++count;
					plast = pnode;
					pnode = pnode->next_;
				}

				return count;
			}

		private:
			void ReleaseResource()
			{
				delete resource_;
				resource_ = NULL;
			}

		private:
			T* resource_;
			TNodePtr prev_;
			TNodePtr next_;
	};
}

#endif // SHAREDPTR_H
