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
	message_log("", (char*)buffer);
	va_end(args);
}

void CommonLog::info(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	message_log("*INFO: ", (char*)buffer);
	va_end(args);
}

void CommonLog::warning(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	message_log("*WARNING: ", (char*)buffer);
	va_end(args);
}

void CommonLog::error(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	message_log("*ERROR: ", (char*)buffer);
	va_end(args);
}

void CommonLog::message_log(char *levtext, char *text)
{
	if (_trec == true)
	{
		char timer[9];
		_strtime(timer);
		clock_t cl = clock();
		printf("%s::%d: ", timer, cl); 
	}
	printf("%s%s\n", levtext, text); 
}