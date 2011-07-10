#pragma once

#include "VariableUpdater.h"
#include <string>

namespace gb
{
	namespace base
	{
		namespace variable
		{
			
			class VariableBase
			{
			public:
				VariableBase(const std::string &name) : name(name) {}
				const std::string &getName() const {return name;}
				
			private:
				std::string name;
			};
			
			template<typename T>
			class Variable : public VariableBase
			{
			public:
				typedef unsigned long UpdateNumber;
				
				Variable(const std::string &name, VariableUpdater<T> &updater) : VariableBase(name), updater(updater)
				{
					update_number = 0;
					updater.setInitialValue(value);
				}
				
				const T& getValue()
				{
					if (updater.update(value))
						++update_number;
					
					return value;
				}
				
				UpdateNumber getUpdateNumber() const {return update_number;}
				
			private:
				T value;
				VariableUpdater<T> &updater;
				UpdateNumber update_number;
			};

		}
	}
}
