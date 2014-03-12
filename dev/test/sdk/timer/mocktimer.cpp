#include "mocktimer.h"

namespace SDK
{
	namespace TEST
	{
		SharedPtr<TimerImpl>& Timer::Impl()
		{
			return impl_;
		}
	}
}
