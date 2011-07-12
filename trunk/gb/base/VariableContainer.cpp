#include "VariableContainer.h"

#include <boost/bind.hpp>

namespace gb
{
	namespace base
	{
		namespace variable
		{
			
			VariableContainer::~VariableContainer()
			{
				for (Variables::iterator it = variables.begin(); it != variables.end(); ++it)
					it->second.variable->removeSignal(it->second.unregister_signal_id);
			}
			
			bool VariableContainer::registerVariableOverride(VariableBase *var)
			{
				VarPtr var_ptr;
				var_ptr.variable = var;
				var_ptr.unregister_signal_id = var->addSignal(boost::bind(&VariableContainer::unregisterVariable, this, var->getName()));
				
				bool result = unregisterVariable(var->getName());
				
				variables.insert(std::make_pair(var->getName(), var_ptr));
				
				return result;
			}
			
			bool VariableContainer::unregisterVariable(const std::string &variable_name)
			{
				Variables::iterator it = variables.find(variable_name);
				
				if (it != variables.end())
				{
					VarPtr &var_ptr = it->second;
					var_ptr.variable->removeSignal(var_ptr.unregister_signal_id);
					variables.erase(it);
					return true;
				}
				
				return false;
			}
		
			VariableBase *VariableContainer::find(const std::string &variable_name) const
			{
				Variables::iterator it = variables.find(variable_name);
				
				if (it != variables.end())
					return it->second.variable;
				
				return nullptr;
			}
			
		}		
	}
}