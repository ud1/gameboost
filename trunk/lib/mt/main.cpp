// Надо бы что-нибудь поинтереснее написать будет
#include "gb/Config.h"

#include <gb/mt/JobScheduler.h>
#include <gb/base/Timer.h>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <gb/base/Logger.h>

#include <iostream>

using namespace gb::mt;
using namespace gb::base;

IJobScheduler *scheduler;
Timer timer;

void printTime(JobTask::Action a)
{
	if (a == JobTask::DO_JOB)
		std::cout << "time " << timer.timeElapsed() << " " << boost::this_thread::get_id() << std::endl;
	else std::cout << "Canceled\n";
}

int main()
{
	DEBUG_LOG("Hello " << 123 << " world");
	
	scheduler = createJobScheduler();
	scheduler->startThreads(3, IO_THREAD_GROUP);

	timer.startTiming();
	
	Timer::sleep(5000);
	
	JobTask task;
	task.policy = getIOThreadPolicy();

	for (int i = 0; i < 6; ++i)
	{
		task.run = &printTime;
		scheduler->scheduleJob0(i*5000, task);
	}
	
	task.run = &printTime;
	scheduler->scheduleJob0(5000, task);
	scheduler->scheduleJob0(4000, task);
	Job *job1 = scheduler->scheduleJob(3000, task);
	Job *job2 = scheduler->scheduleJob(2000, task);
	
	job1->cancel();
	
	for (int i = 5; i --> 0;)
	{
		task.run = &printTime;
		scheduler->scheduleJob0(i*5000, task);
	}
	
	job2->cancel();
	
	Timer::sleep(60000);
}