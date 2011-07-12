#pragma once

#include "VariableUpdater.h"
#include <gb/base/OnDeleteSignalingObject.h>
#include <gb/base/nullptr.h>
#include <gb/math/typeTraits.h>

#include <string>

namespace gb
{
	namespace base
	{
		namespace variable
		{
			
			class VariableBase : public OnDeleteSignalingObject
			{
			public:
				VariableBase(const std::string &name) : name(name) {}
				const std::string &getName() const {return name;}
				
				virtual const float *getFloats() const {return nullptr;}
				virtual int getRowsNumber() const {return 0;}
				virtual int getColumnsNumber() const {return 0;}
				virtual bool isFloatingPointType() const {return false;}
				
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
				
				const T& getValue() const
				{
					if (updater.update(value))
						++update_number;
					
					return value;
				}
				
				virtual const float *getFloats() const
				{
					return (const float *) &getValue();
				}
				
				virtual int getRowsNumber() const
				{
					return math::rows_number<T>::value;
				}
				
				virtual int getColumnsNumber() const
				{
					return math::columns_number<T>::value;
				}
				
				virtual bool isFloatingPointType() const
				{
					return math::is_floating_point_type<T>::value;
				}
				
				UpdateNumber getUpdateNumber() const {return update_number;}
				
			private:
				mutable T value;
				VariableUpdater<T> &updater;
				mutable UpdateNumber update_number;
			};

		}
	}
}
