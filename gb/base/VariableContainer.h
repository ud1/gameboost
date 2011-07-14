#pragma once

#include <gb/base/Variable.h>

#include <map>

namespace gb
{
	namespace base
	{
		namespace variable
		{
			
			class VariableContainer
			{
			public:
				~VariableContainer();
				
				/**
				 * \return true если переменная была перезаписана
				 */
				virtual bool registerVariableOverride(VariableBase *var);
				bool unregisterVariable(const std::string &variable_name);
				
				VariableBase *find(const std::string &variable_name) const;
				
			protected:
				virtual void onDeleteVariableCallback(const std::string &variable_name);
				
			private:
				struct VarPtr
				{
					VariableBase *variable;
					VariableBase::SignalId unregister_signal_id;
				};
				
				typedef std::map<std::string, VarPtr> Variables;
				Variables variables;
			};
		
		}
	}
}