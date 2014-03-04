#include "posixthread.h"

namespace SDK
{
	PosixThread::PosixThread(Thread& tr) : IThread(tr) 
	{}

	PosixThread::~PosixThread()
	{}

	bool PosixThread::Start()
	{
		int res = pthread_create(&tid_, NULL, IThread::ThreadStart, static_cast<void*>(this));
		return (0 == res);
	}

	void PosixThread::Stop()
	{
		pthread_cancel(tid_);
	}

	bool PosixThread::Join()
	{
		int res = pthread_join(tid_, NULL);
		return (0 == res);
	}
}
