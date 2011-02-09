#include "CommonLog.h"
#include <ctime>
#include <cstdarg>
#include <clocale>

using namespace gb;
using namespace log;

CommonLog::CommonLog()
{
	init();
}

CommonLog::CommonLog(bool timerecord)
{
	init();
	SetTimeRecord(timerecord);
}

CommonLog::~CommonLog()
{
}

void CommonLog::init()
{
	SetTimeRecord(false);
	setlocale(LC_ALL, "rus");
}

void CommonLog::print(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	print(NORMAL, (char*)buffer);
	va_end(args);
}

void CommonLog::print(LevelLog level, const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];

	char *strlev;
	switch (level)
	{
	case NORMAL:
		strlev = "";
		break;
	case INFO:
		strlev = "*INFO: ";
		break;
	case WARNING:
		strlev = "*WARNING: ";
		break;
	case ERROR:
		strlev = "*ERROR: ";
		break;
	default:
		strlev = "";
		break;
	}

	vsprintf(buffer, message, args);
	if (_trec == true)
	{
		char timer[9];
		_strtime(timer);
		clock_t cl = clock();
		printf("%s::%d: ", timer, cl); 
	}
	printf("%s%s\n", strlev, buffer); 
	va_end(args);
}

void CommonLog::info(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	print(INFO, (char*)buffer);
	va_end(args);
}

void CommonLog::warning(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	print(WARNING, (char*)buffer);
	va_end(args);
}

void CommonLog::error(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	print(ERROR, (char*)buffer);
	va_end(args);
}
