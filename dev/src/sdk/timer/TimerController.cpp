#include "TimerController.h"
#include "timerimpl.h"
#include "thread.h"
#include <pthread.h>
#include <iostream>
#include <cassert>

namespace SDK
{
	TimerController* TimerController::TheInstance = NULL;

	TimerController& TimerController::GetInstance()
	{
		if (NULL == TimerController::TheInstance)
		{
			TimerController::TheInstance = new TimerController;
			TimerController::TheInstance->Start();
		}

		return *TimerController::TheInstance;
	}

	TimerController::TimerController() :
			timers_(),
			queueLock_(),
			queueReady_(queueLock_)
	{}

	TimerController::~TimerController()
	{
		this->Stop();
	}

	void TimerController::Add(SharedPtr<TimerImpl>& t)
	{
		assert(t->IsActive());

		LockGuard l(queueLock_);
		timers_.push(t);
		queueReady_.Signal();
	}

	bool TimerController::Run()
	{
		for(;;)
		{
			queueLock_.Acquire();

			while (timers_.empty())
			{
				queueReady_.Wait();
			}

			SharedPtr<TimerImpl> p = timers_.top();
			timers_.pop();

			do
			{
				if (p->IsDefunct())
				{
				}

				if (!p->IsActive())
				{
					break;
				}

				bool tmo = false;
				queueReady_.Wait(p->SecUntilElapse(), &tmo);

				if (!tmo)
				{
					timers_.push(p);
					break;
				}

				if (p->IsActive())
				{
					TimerCallback* pcbk = p->GetCallback();
					if (NULL != pcbk)
					{
						pcbk->Elapsed();
						pcbk = NULL;
					}

					if (!p->IsSingleShot())
					{
						p->Reset();
						timers_.push(p);
					}
					else
					{
						p->SetInactive();
					}
				}
			}
			while (false);

			queueLock_.Release();
		}

		return true;
	}
}
