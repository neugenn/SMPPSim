#include "logger.h"
#include "lock.h"
#include <cassert>

static SDK::Lock lock;
static bool init = false;

void Logger::SetOutputFile(FILE*& file)
{
	if (NULL != file)
	{
		lock.Acquire();
		if (file != Output2FILE::Stream())
		{
			fclose(Output2FILE::Stream());
			Output2FILE::Stream() = file;
		}
		lock.Release();
	}
}

void Logger::SetLogLevel(TLogLevel level)
{
	lock.Acquire();
	Log<Output2FILE>::ReportingLevel() = level;
	lock.Release();
}

void Logger::Init()
{
	if (init)
	{
		FILE_LOG(logWARNING) << "Logging module already initialized !";
		return;
	}

	lock.Acquire();
	FILE* f = fopen("application.log", "a");
	assert(NULL != f);
	init = true;
	lock.Release();

	Logger::SetOutputFile(f);
	Logger::SetLogLevel(logDEBUG2);
	FILE_LOG(logINFO) << "Logging module initialized with reporting level " << Log<Output2FILE>::ToString(Log<Output2FILE>::ReportingLevel());
}

void Logger::Release()
{
	lock.Acquire();
	FILE_LOG(logDEBUG) << "Bye !";
	fclose(Output2FILE::Stream());
	init = false;
	lock.Release();
}
