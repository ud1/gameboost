#pragma once

#include <string>
#include <vector>

#include <gb/fs/FileSystem.h>

namespace gb
{
	namespace shaders
	{
		class ShaderPreprocessor
		{
		public:
			ShaderPreprocessor(fs::FileSystem *fs);
			~ShaderPreprocessor();
			
			bool load(const std::string &path, const std::vector<std::string> &macro_definitions, std::string &shader_out);
			
		private:
			class ShaderPreprocessorImpl;
			ShaderPreprocessorImpl *pimpl;
		};
	}
}
