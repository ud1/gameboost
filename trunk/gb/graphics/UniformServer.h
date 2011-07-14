#pragma once
#include <gb/base/Variable.h>
#include <gb/base/nullptr.h>
#include <gb/base/VariableContainer.h>
#include <gb/base/TailedType.h>
#include "Uniform.h"

#include <boost/bimap.hpp>
#include <map>

namespace gb
{
	namespace graphics
	{
		
		class UniformGroup
		{
		public:
			void updateUniforms();
			
		private:
			friend class UniformServer;
			
			void bind(Uniform &uniform, base::variable::VariableBase &varriable);
			void onDeleteVariableCallback(base::variable::VariableBase *variable);
			void onDeleteUniformCallback(Uniform *uniform);
			
			
			typedef base::TailedType<Uniform *, Uniform::SignalId > UniformRef;
			typedef base::TailedType<base::variable::VariableBase *, base::variable::VariableBase::SignalId > VariableRef;
			typedef boost::bimap<UniformRef, VariableRef> Bindings;
			Bindings bindings;
		};
		
		class UniformServer : public base::variable::VariableContainer
		{
		public:
			bool registerVariableOverride(base::variable::VariableBase *var);
			bool bindUniform(UniformGroup &group, Uniform &uniform, const char *variable_name = nullptr);
			
		private:
			void onDeleteVariableCallback(const std::string &variable_name);
			
			typedef std::map<std::string, base::variable::VariableRef *> Variables;
			Variables variables;
		};
		
	}
}
