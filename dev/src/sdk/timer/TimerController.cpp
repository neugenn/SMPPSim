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
			queueLock_(new Lock),
			queueReady_(new CondVar(*queueLock_))
	{
	}

	TimerController::TimerController(
			Lock* l,
			CondVar* c
			) :
			timers_(),
			queueLock_(l),
			queueReady_(c)
	{
	}

	TimerController::~TimerController()
	{
		this->Stop();
	}

	void TimerController::Add(SharedPtr<TimerImpl>& t)
	{
		assert(t->IsActive());

		LockGuard l(*queueLock_);
		timers_.push(t);
		queueReady_->Signal();
	}

	bool TimerController::Run()
	{
		bool r = true;
		for(;;)
		{
			r = this->RunEventLoop();
		}

		return r;
	}

	bool TimerController::RunEventLoop()
	{
		queueLock_->Acquire();

		while (timers_.empty())
		{
			queueReady_->Wait();
		}

		const SharedPtr<TimerImpl>& p = timers_.top();
		do
		{
			if (!p->IsActive())
			{
				timers_.pop();
				break;
			}

			bool tmo = false;
			queueReady_->Wait(p->SecUntilElapse(), &tmo);

			if (!tmo)
			{
				break;
			}

			if (p->IsActive())
			{
				TimerCallback* pcbk = p->GetCallback();
				if (NULL != pcbk)
				{
					pcbk->Elapsed();
				}
				pcbk = NULL;

				if (!p->IsSingleShot())
				{
					p->Reset();
				}
				else
				{
					p->SetInactive();
					timers_.pop();
				}
			}
		}
		while (false);

		queueLock_->Release();

		return true;
	}
}
