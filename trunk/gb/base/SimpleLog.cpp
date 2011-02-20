

#include <gb/base/SimpleLog.h>

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

void SimpleLog::message_log(char *levtext, char *text)
{
	if (_trec == true)
	{
		char timer[9];
		_strtime(timer);
		clock_t cl = clock();
		printf("%s::%d: ", timer, cl); 
		fprintf(_file, "%s::%d: ", timer, cl);
	}
	printf("%s%s\n", levtext, text); 
	fprintf(_file, "%s%s\n", levtext, text);
}
