#include "TimerController.h"
#include "timerimpl.h"
#include "thread.h"
#include <pthread.h>
#include <iostream>

namespace SDK
{
	/*
	*/

	TimerController* TimerController::TheInstance = NULL;

	TimerController::TimerController() : timers_(), lock_()
	{}

	TimerController::~TimerController()
	{}

	bool TimerController::Add(TimerImpl* t)
	{
		if (NULL == t)
		{
			return false;
		}

		if (this->Manages(t->GetID()))
		{
			return false;
		}

		//[TODO]: synchronize
		LockGuard l(lock_);
		timers_.push_back(t);
		return true;
	}

	void TimerController::Remove(const TimerImpl* t)
	{
		if (NULL == t)
		{
			return;
		}

		//[TODO]: synchronize
		LockGuard l(lock_);
		std::vector<TimerImpl*>::iterator it = timers_.begin();
		std::vector<TimerImpl*>::iterator itEnd = timers_.end();
		for (; it != itEnd; ++it)
		{
			const TimerImpl* pi = *it;
			if (pi->GetID() == t->GetID())
			{
				timers_.erase(it);
				break;
			}
		}
	}

	bool TimerController::Manages(timer_id_t id)
	{
		bool r = false;
		//[TODO]: synchronize
		LockGuard l(lock_);
		for (size_t i = 0; i < timers_.size(); ++i)
		{
			if (timers_[i]->GetID() == id)
			{
				r  = true;
				break;
			}
		}
		return r;
	}

	bool TimerController::Run()
	{
		for(;;)
		{
			LockGuard l(lock_);
			std::vector<TimerImpl*>::iterator it = timers_.begin();
			std::vector<TimerImpl*>::iterator itEnd = timers_.end();

			for (; it != itEnd; ++it)
			{
				TimerImpl* pi = *it;
				if (pi->Elapsed())
				{
					std::cout << "Timer" << " " << pi->GetID() << " elapsed !" << std::endl;
					pi->Reset();
				}
			}
		}

		return true;
	}

	class TestTimerController : public TimerController
	{
		public:
			TestTimerController() : TimerController() {}
			~TestTimerController() {}

		private:
			virtual bool Run() 
			{
				return true;
			}
			
	};

	TimerController& TimerController::GetInstance()
	{
		if (NULL == TimerController::TheInstance)
		{
		#ifdef UNIT_TEST
		TheInstance = new TestTimerController();
		#else
		TheInstance = new TimerController();
		#endif
		TheInstance->Start();
		}

		return *TheInstance;
	}
}
