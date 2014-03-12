#ifndef TESTTIMERCONTROLLER_H_
#define TESTTIMERCONTROLLER_H_

#include "TimerController.h"
#include "mockcondvar.h"
#include "lock.h"

namespace SDK
{
	namespace TEST
	{
		class TimerController : public SDK::TimerController
		{
			protected:
				TimerController(Lock* l, TEST::CondVar* c);
				~TimerController() {}


			private:
				virtual bool Run();

			public:
				static TimerController* GetTestInstance();
				static void ReleaseTestInstance(TimerController*& p);

				const SDK::TimerController::TQueue& TimerQueue();
				bool RunEventLoop();

			public:
				TEST::CondVar& GetCondVar()
				{
					return *cond_;
				}

			private:
				TEST::CondVar* cond_;
		};
	}
}

#endif // TESTTIMERCONTROLLER_H_
