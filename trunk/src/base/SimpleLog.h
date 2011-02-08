#pragma once

#include <cstdio>
#include <string>

namespace gb
{
namespace log
{

typedef enum
{
	NORMAL,
	INFO,
	WARNING,
	ERROR
} LevelLog;

class SimpleLog
{
public:
	SimpleLog();
	SimpleLog(bool timerecord);
	SimpleLog(char *name);
	SimpleLog(char *name, bool timerecord);

	~SimpleLog();

	void print(const char *message, ...);
	void print(LevelLog level, const char *message, ...);
	void info(const char *message, ...);
	void warning(const char *message, ...);
	void error(const char *message, ...);

	void set_time_record(bool trec){_trec = trec;}



private:
	FILE *_file;	// файл лога
	char *_name;	// имя файла
	bool _trec;

	void init(char *name);
};

} // namespace
} // namespace
