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
			class TypedVariable : public VariableBase
			{
			public:
				typedef unsigned long UpdateNumber;
				
				TypedVariable(const std::string &name) : VariableBase(name)
				{
					update_number = 0;
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
				
			protected:
				mutable UpdateNumber update_number;
			};
			
			template<typename T>
			class Variable : public TypedVariable<T>
			{
			public:
				typedef unsigned long UpdateNumber;
				typedef TypedVariable<T> Base;
				
				Variable(const std::string &name, VariableUpdater<T> *updater) : TypedVariable<T>(name), updater(updater)
				{
					Base::update_number = 0;
					
					if (updater)
						updater->setInitialValue(value);
				}
				
				const T& getValue() const
				{
					if (updater && updater->update(value))
						++Base::update_number;
					
					return value;
				}
				
				virtual const float *getFloats() const
				{
					return math::value_ptr(getValue());
				}
				
			protected:
				mutable T value;
				VariableUpdater<T> *updater;
			};
			
			template<typename T>
			class AutonomousVariable : public Variable<T>
			{
			public:
				typedef Variable<T> Base;
				AutonomousVariable(const std::string &name) : Base(name, nullptr) {}
				
				void updateValue(const T &new_value)
				{
					Base::value = new_value;
					++Base::update_number;
				}
			};

			class VariableRef : public VariableBase
			{
			public:
				VariableBase *referencedVariable;
				
				VariableRef(const std::string &name) : VariableBase(name) {}
				
				virtual const float *getFloats() const {return referencedVariable->getFloats();}
				virtual int getRowsNumber() const {return referencedVariable->getRowsNumber();}
				virtual int getColumnsNumber() const {return referencedVariable->getColumnsNumber();}
				virtual bool isFloatingPointType() const {return referencedVariable->isFloatingPointType();}
			};
		}
	}
}
