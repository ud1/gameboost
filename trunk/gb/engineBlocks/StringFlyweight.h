/**
 * StringFlyweight представляет собой класс строк, при этом
 * одинаковым строкам соотвествует один экземпляр StringFlyweight.
 * Таким образом для сравнения StringFlyweight на равенство достаточно
 * сравнить их указатели. Для создания StringFlyweight объектов
 * следует использовать StringFlyweightFactory::create()
 */

#pragma once

#include <gb/base/IRefCountable.h>
#include "CacheNoGarbage.h"
#include <string>
#include <boost/thread.hpp>

#include <iostream>

namespace gb
{
	namespace engine_blocks
	{
		
		class StringFlyweight : public std::string, public base::IRefCountable
		{
		public:
			typedef std::string Request;
			
			bool operator < (const StringFlyweight &o) const
			{
				return this < &o;
			}
			
			bool operator == (const StringFlyweight &o) const
			{
				return this == &o;
			}
			
			bool operator != (const StringFlyweight &o) const
			{
				return this != &o;
			}
			
		protected:
			StringFlyweight() {}
		private:
			void operator = (const StringFlyweight &){}
		};
		
		typedef base::RefCntHolder<const StringFlyweight> PStringFlyweight;
		
		class StringFlyweightLoader
		{
		public:
			bool checkRequest(const std::string &)
			{
				return true;
			}
			
			void load(const std::string &req, StringFlyweight &res)
			{
				(std::string &) res = req;
			}
			
			void update(const std::string &req, StringFlyweight &res) {}
		};
		
		class StringFlyweightFactory : private CacheNoGarbage<StringFlyweight, boost::mutex, StringFlyweightLoader>
		{
		public:
			const StringFlyweight *create(const std::string &v)
			{
				return get(v);
			}
		};
	}
}
