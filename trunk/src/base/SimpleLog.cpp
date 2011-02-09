﻿#include "SimpleLog.h"
#include <ctime>
#include <cstdarg>
#include <clocale>

using namespace gb;
using namespace log;

SimpleLog::SimpleLog()
{
	init("log.txt");
}

SimpleLog::SimpleLog(bool timerecord)
{
	init("log.txt");
	SetTimeRecord(timerecord);
}

SimpleLog::SimpleLog(char *name)
{
	init(name);
}

SimpleLog::SimpleLog(char *name, bool timerecord)
{
	init(name);
	SetTimeRecord(timerecord);
}

SimpleLog::~SimpleLog()
{
	char timer[9];
	_strtime(timer);
	char date[9];
	_strdate(date);
	fprintf(_file, "\n---------------------------------------\n");
	fprintf(_file, "Конец лога: %s %s.", date, timer);
	fclose(_file);
}

void SimpleLog::init(char *name)
{
	_name = name;
	SetTimeRecord(false);
	setlocale(LC_ALL, "rus");	

	if( (_file = fopen(_name,"w")) == NULL )
	{
		printf("Error creating file...\n");
		return;
	}
	else
	{
		char timer[9];
		_strtime(timer);
		char date[9];
		_strdate(date);
		fprintf(_file, "Лог создан: %s %s.\n", date, timer);
		fprintf(_file, "---------------------------------------\n\n");
	}
}

void SimpleLog::print(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	print(NORMAL, (char*)buffer);
	va_end(args);
}

void SimpleLog::print(LevelLog level, const char *message, ...)
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

		fprintf(_file, "%s::%d: ", timer, cl);
		printf("%s::%d: ", timer, cl); 
	}
	fprintf(_file, "%s%s\n", strlev, buffer);
	printf("%s%s\n", strlev, buffer); 
	va_end(args);
}

void SimpleLog::info(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	print(INFO, (char*)buffer);
	va_end(args);
}

void SimpleLog::warning(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	print(WARNING, (char*)buffer);
	va_end(args);
}

void SimpleLog::error(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);
	print(ERROR, (char*)buffer);
	va_end(args);
}
