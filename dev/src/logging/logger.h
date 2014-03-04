#ifndef LOGGER_H_
#define LOGGER_H_

#include "log.h"

class Logger
{
	private:
		Logger() {}
		Logger(const Logger&);
		Logger& operator=(const Logger&);

	public:
		~Logger() {}

	public:
		static void SetOutputFile(FILE*& file);
		static void SetLogLevel(TLogLevel level);
		static void Init();
		static void Release();
};

#endif // LOGGER_H_
