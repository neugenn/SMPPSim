#ifndef MOCKCONDVAR_H_
#define MOCKCONDVAR_H_

#include "condvar.h"

namespace SDK
{
	namespace TEST
	{ 
		class CondVar : public SDK::CondVar
		{
			public:
				CondVar(
					Lock& l,
					bool waitResp = false,
					bool tmoResp = false
					) :
				       	SDK::CondVar(l),
		       			waitResponse_(waitResp),
					tmoResponse_(tmoResp)
					{}

				~CondVar() {}

			public:
				virtual bool Wait() 
				{
				       	return waitResponse_; 
				}

				virtual bool Wait(unsigned int sec, bool* timedOut = NULL)
				{
					if (NULL != timedOut)
					{
						*timedOut = tmoResponse_;
					}
					return waitResponse_;
				}

				virtual bool Signal()
				{
					return true;
				}

				void SetWaitResponse(bool r)
				{
					waitResponse_ = r;
				}

				void SetTmoResponse(bool r)
				{
					tmoResponse_ = r;
				}

			private:
				bool waitResponse_;
				bool tmoResponse_;

		};
	}
}

#endif //MOCKCONDVAR_H_
