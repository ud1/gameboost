#pragma once
#include "Variable.h"

namespace gb
{
	namespace base
	{
		namespace variable
		{
			
			template<typename T>
			class VariableUpdater
			{
			public:
				virtual void setInitialValue(T &value) = 0;
				virtual bool update(T &value) = 0;
			};
			
			template<typename T>
			class Identity : public VariableUpdater<T>
			{
			public:
				Identity(T &value) : value(value) {}
				
				virtual void setInitialValue(T &value)
				{
					value = this->value;
				}
				
				virtual bool update(T &value)
				{
					value = this->value;
					return true;
				}
				
			private:
				T &value;
			};
			
			template<typename T>
			class IdentityWithChangeChecking : public VariableUpdater<T>
			{
			public:
				IdentityWithChangeChecking(T &value) : value(value) {}
				
				virtual void setInitialValue(T &value)
				{
					value = this->value;
				}
				
				virtual bool update(T &value)
				{
					if (value != this->value)
					{
						value = this->value;
						return true;
					}
					return false;
				}
				
			private:
				T &value;
			};
			
			template<typename T>
			class Variable;
			
			template<typename Func, typename T = typename Func::result_type, typename U = typename Func::argument_type>
			class Function : public VariableUpdater<T>
			{
			public:
				Function(Func func, Variable<U> &parameter) : func(func), parameter(parameter)
				{
					update_number = parameter.getUpdateNumber();
				}
				
				virtual void setInitialValue(T &value)
				{
					value = func(parameter.getValue());
					update_number = parameter.getUpdateNumber();
				}
				
				virtual bool update(T &value)
				{
					const U &prameter_value = parameter.getValue();
					if (parameter.getUpdateNumber() != update_number)
					{
						update_number = parameter.getUpdateNumber();
						value = func(prameter_value);
						return true;
					}
					return false;
				}
				
			private:
				Func func;
				Variable<U> &parameter;
				typename Variable<U>::UpdateNumber update_number;
			};
		
		}
	}
}
