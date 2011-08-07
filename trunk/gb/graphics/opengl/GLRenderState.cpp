#include "GLRenderState.h"

#include <gb/logging/Logger.h>

#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>

#include "GLDevice.h"

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			
			bool GLRenderState::setSource(const char *code)
			{
				stateFunctions.clear();
				std::stringstream stream(code);
				int lineN = 0;
				for (std::string line; std::getline(stream, line); ++lineN)
				{
					boost::tokenizer<> tok(line);
					boost::tokenizer<>::iterator it = tok.begin();
					if (it != tok.end())
					{
						if (*it == "DepthTest")
						{
							if (++it == tok.end())
							{
								ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
								return false;
							}
							
							if (*it == "enable")
							{
								stateFunctions.push_back(boost::bind<void>(glEnable, GL_DEPTH_TEST));
							}
							else if (*it == "disable")
							{
								stateFunctions.push_back(boost::bind<void>(glDisable, GL_DEPTH_TEST));
							}
							else
							{
								ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
								return false;
							}
							continue;
						}
						else if (*it == "ScissorTest")
						{
							if (++it == tok.end())
							{
								ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
								return false;
							}
							if (*it == "enable")
							{
								stateFunctions.push_back(boost::bind<void>(glEnable, GL_SCISSOR_TEST));
							}
							else if (*it == "disable")
							{
								stateFunctions.push_back(boost::bind<void>(glDisable, GL_SCISSOR_TEST));
							}
							else
							{
								ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
								return false;
							}
							continue;
						}
						else if (*it == "Wireframe")
						{
							if (++it == tok.end())
							{
								ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
								return false;
							}
							if (*it == "enable")
							{
								stateFunctions.push_back(boost::bind<void>(glPolygonMode, GL_FRONT_AND_BACK, GL_LINE));
							}
							else if (*it == "disable")
							{
								stateFunctions.push_back(boost::bind<void>(glPolygonMode, GL_FRONT_AND_BACK, GL_FILL));
							}
							else
							{
								ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
								return false;
							}
							continue;
						}
					}
					return true;
				}
			}
			
			void GLRenderState::apply()
			{
				for (std::vector<stateFunc>::iterator it = stateFunctions.begin(); it != stateFunctions.end(); ++it)
					(*it)();
			}

		}
	}
}
