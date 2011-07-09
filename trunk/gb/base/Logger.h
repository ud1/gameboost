/*! \file  Logger.h
 * \brief Логгер
 * \author ud1 (ud1@mail.ru)
 * @ingroup base_group
 * 
 * Здесь определен набор макросов типа DEBUG_LOG, ERROR_LOG, и их надо использовать везде, где надо выводить что-то в лог. 
 * Использование очень простое:
 * @code
 * DEBUG_LOG("Render time " << delta << " ms");
 * @endcode
 * 
 * Везде следует использовать именно эти макросы, так как:
 * <ol>
 * <li> Вывод обернут мьютеком, иначе одновременный вывод из нескольких потоков мог привести к смешиванию букв;
 * <li> Использование макросов позволяет при желании полностью сменить реализацию логера без необходимости переписывая другого кода;
 * <li> В его устройстве заранее заложена потенциальная возможность в будущем выводить скажем одновременно в файл, в консоль, в игровую консоль с раскраской, или еще куда;
 * <li> Есть два уровня логирования, один задаваемый в рантайме, другой во время компиляции, задав GB_LOG_LEVEL в настройках можно полностью убрать из компиляции
 * 		некоторый вывод в лог, и соответсвенно возможное проседание производительности на создание и форматирование строк для него.
 * </ol>
 */

#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include "gb/mt/syncPrimitives.h"
#include "gb/Config.h"

namespace gb
{
	namespace base
	{
		namespace eLogType
		{
			enum LogType
			{
				LT_DEBUG = 0,
				LT_MESSAGE,
				LT_WARNING,
				LT_ERROR,
				LT_CRITICAL,
				
				LT_COUNT
			};
		}
		
		class ConsoleOutputer
		{
		public:
			void print(eLogType::LogType type, const std::string &message)
			{
				static const char *log_type_desc[] = {
					"[DEBUG] ",
					"[MESSAGE] ",
					"[WARNING] ",
					"[ERROR] ",
					"[CRITICAL] "
				};
				
				const char *format = "%c";
				const size_t TIME_STR_LEN = 128;
				
				char time_str[TIME_STR_LEN];
				time_t rawtime;
				time (&rawtime);
				strftime(time_str, TIME_STR_LEN, format, localtime ( &rawtime ));
				
				guard.lock();
				std::cout << time_str << " " << log_type_desc[type] << message;
				guard.unlock();
			}
			
		private:
			mt::Mutex guard;
		};
		
		template <typename Outputer>
		class LoggerStream
		{
		public:
			LoggerStream(Outputer *outputer, eLogType::LogType type)
			{
				this->outputer = outputer;
				this->type = type;
			}
			
			LoggerStream(const LoggerStream &o)
			{
				outputer = o.outputer;
				type = o.type;
			}
			
			LoggerStream &operator = (const LoggerStream &o)
			{
				outputer = o.outputer;
				type = o.type;
				return *this;
			}
			
			~LoggerStream()
			{
				flush();
			}
			
			template <typename T>
			LoggerStream &operator << (const T &t)
			{
				if (outputer)
					str << t;
				return *this;
			}
			
			void flush() {
				if (outputer && str.str().size())
				{
					outputer->print(type, str.str());
					str.str("");
				}
			}
		private:
			Outputer *outputer;
			eLogType::LogType type;
			std::ostringstream str;
		};
		
		template <typename Outputer>
		class Logger
		{
		public:
			Logger()
			{
				log_level = eLogType::LT_DEBUG;
			}

			void setLogLevel(eLogType::LogType level)
			{
				log_level = level;
			}

			eLogType::LogType getLogLevel() const
			{
				return log_level;
			}

			LoggerStream<Outputer> operator() (eLogType::LogType level)
			{
				if (level < log_level)
				{
					return LoggerStream<Outputer>(NULL, level);
				}
				else
				{
					return LoggerStream<Outputer>(&outputer, level);
				}
			}

		private:
			Outputer outputer;
			eLogType::LogType log_level;
		};
		
		template <typename Logger>
		Logger &getLogger();
		
		class ConsoleLogger : public Logger<ConsoleOutputer> {};
		
#if GB_LOG_LEVEL <= 0
	#define DEBUG_LOG(x) (gb::base::getLogger<GB_LOGGER_TYPE>()(gb::base::eLogType::LT_DEBUG) << x << "\n").flush()
#else
	#define DEBUG_LOG(x)
#endif

#if GB_LOG_LEVEL <= 1
	#define MESSAGE_LOG(x) (gb::base::getLogger<GB_LOGGER_TYPE>()(gb::base::eLogType::LT_MESSAGE) << x << "\n").flush()
#else
	#define MESSAGE_LOG(x)
#endif

#if GB_LOG_LEVEL <= 2
#		define WARNING_LOG(x) (gb::base::getLogger<GB_LOGGER_TYPE>()(gb::base::eLogType::LT_WARNING) << x << "\n").flush()
#else
#		define WARNING_LOG(x)
#endif
		
#if GB_LOG_LEVEL <= 3
#		define ERROR_LOG(x) (gb::base::getLogger<GB_LOGGER_TYPE>()(gb::base::eLogType::LT_ERROR) << x << "\n").flush()
#else
#		define ERROR_LOG(x)
#endif
		
#if GB_LOG_LEVEL <= 4
#		define CRITICAL_LOG(x) (gb::base::getLogger<GB_LOGGER_TYPE>()(gb::base::eLogType::LT_CRITICAL) << x << "\n").flush()
#else
#		define CRITICAL_LOG(x)
#endif
		
	}
}

