#include "UniformServer.h"

#include <boost/bind.hpp>

namespace gb
{
	namespace graphics
	{
		using namespace base;
		using namespace base::variable;
		
		//----------------- UniformGroup -------------------------
		
		void UniformGroup::updateUniforms()
		{
			for (Bindings::left_iterator it = bindings.left.begin(); it != bindings.left.end(); ++it)
				it->first.head->setFloats(it->second.head->getFloats(), 1, false);
		}
		
		void UniformGroup::bind(Uniform &uniform, base::variable::VariableBase &varriable)
		{
			bindings.insert(Bindings::value_type(
				UniformRef(&uniform, uniform.addSignal(boost::bind(&UniformGroup::onDeleteUniformCallback, this, &uniform))), 
				VariableRef(&varriable, varriable.addSignal(boost::bind(&UniformGroup::onDeleteVariableCallback, this, &varriable)))
			));
		}
		
		void UniformGroup::onDeleteVariableCallback(base::variable::VariableBase *variable)
		{
			Bindings::right_iterator it = bindings.right.find(VariableRef(variable, VariableBase::SignalId()));
			if (it != bindings.right.end())
			{
				it->first.head->removeSignal(it->first.tail);
				it->second.head->removeSignal(it->second.tail);
				bindings.right.erase(it);
			}
		}
		
		void UniformGroup::onDeleteUniformCallback(Uniform *uniform)
		{
			Bindings::left_iterator it = bindings.left.find(UniformRef(uniform, Uniform::SignalId()));
			if (it != bindings.left.end())
			{
				it->first.head->removeSignal(it->first.tail);
				it->second.head->removeSignal(it->second.tail);
				bindings.left.erase(it);
			}
		}
		
		//----------------- UniformServer -------------------------
		
		bool UniformServer::registerVariableOverride(VariableBase *var)
		{
			Variables::iterator it = variables.find(var->getName());
			if (it != variables.end())
			{
				it->second->referencedVariable = var;
			}
			else
			{
				VariableRef *ref = new VariableRef(var->getName());
				ref->referencedVariable = var;
				variables.insert(std::make_pair(var->getName(), ref));
			}
			
			return VariableContainer::registerVariableOverride(var);
		}
		
		bool UniformServer::bindUniform(UniformGroup &group, Uniform &uniform, const char *variable_name)
		{
			if (!variable_name)
				variable_name = uniform.getName();
			
			Variables::iterator it = variables.find(variable_name);
			if (it == variables.end())
				return false;
			
			group.bind(uniform, *it->second);
			return true;
		}
		
		void UniformServer::onDeleteVariableCallback(const std::string &variable_name)
		{
			Variables::iterator it = variables.find(variable_name);
			delete it->second;
			variables.erase(it);
			VariableContainer::onDeleteVariableCallback(variable_name);
		}
		
	}
}