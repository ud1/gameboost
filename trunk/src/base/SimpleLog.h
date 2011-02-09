﻿#pragma once

#include "CommonLog.h"

namespace gb
{
namespace log
{

class SimpleLog : public CommonLog
{
public:
	SimpleLog();
	SimpleLog(bool timerecord);
	SimpleLog(char *name);
	SimpleLog(char *name, bool timerecord);

	~SimpleLog();

	virtual void print(const char *message, ...);
	virtual void print(LevelLog level, const char *message, ...);
	virtual void info(const char *message, ...);
	virtual void warning(const char *message, ...);
	virtual void error(const char *message, ...);

	virtual void SetTimeRecord(bool trec){_trec = trec;}



private:
	FILE *_file;	// файл лога
	char *_name;	// имя файла

	virtual void init(char *name);


};

}
}