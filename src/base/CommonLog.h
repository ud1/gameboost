#pragma once

#include <cstdio>

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

class CommonLog
{
public:
	CommonLog();
	CommonLog(bool timerecord);

	~CommonLog();

	virtual void print(const char *message, ...);
	virtual void print(LevelLog level, const char *message, ...);
	virtual void info(const char *message, ...);
	virtual void warning(const char *message, ...);
	virtual void error(const char *message, ...);

	virtual void SetTimeRecord(bool trec){_trec = trec;}

protected:
	bool _trec;
	virtual void init();
};

}
}