#include <gb/Config.h>
#if GB_ALLOW_BOOST_LIBRARY

#include <gb/shaders/ShaderPreprocessor.h>
#include <gb/fs/Helpers.h>
#include <gb/base/Logger.h>

#define BOOST_WAVE_PRAGMA_KEYWORD "shader"

#include <boost/wave.hpp>
#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class
#include <boost/filesystem.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <sstream>
#include <iostream>

namespace gb
{
	namespace shaders
	{
		using namespace gb::fs;
		using namespace boost::wave;
		
		class ShaderPreprocessor::ShaderPreprocessorImpl
		{
		public:
			ShaderPreprocessorImpl(FileSystem *fs)
			{
				file_system = fs;
			}
			
			bool load(const std::string &file_name, const std::vector<std::string> macro_definitions, std::string &out)
			{
				std::string instring;
				if (!readEntireFile(*file_system, file_name, instring))
					return false;

				boost::wave::util::file_position_type current_position;
				try
				{
					ShaderContext ctx(instring.begin(), instring.end(), file_name.c_str(), file_system);
					for (std::vector<std::string>::const_iterator it = macro_definitions.begin(); it != macro_definitions.end(); ++it)
					{
						ctx.add_macro_definition(*it, false);
					}

					ShaderContext::iterator_type it = ctx.begin();
					ShaderContext::iterator_type end_it = ctx.end();

					std::ostringstream oss;
					for (; it != end_it; ++it)
					{
						current_position = (*it).get_position();
						oss << (*it).get_value();
					}

					out = oss.str();
				}
				catch (boost::wave::cpp_exception &e)
				{
					// some preprocessing error
					ERROR_LOG(e.file_name() << "(" << e.line_no() << "): " << e.description());
					return false;
				}
				catch (std::exception &e)
				{
					// use last recognized token to retrieve the error position
					ERROR_LOG( 
						current_position.get_file() 
						<< "(" << current_position.get_line() << "): "
						<< "exception caught: " << e.what()
					);
					return false;
				}
				catch (...)
				{
					return false;
				}

				return true;
			}

		protected:
			FileSystem	*file_system;

			typedef boost::wave::cpplexer::lex_token<> token_type;
			typedef boost::wave::cpplexer::lex_iterator<token_type> lex_iterator_type;
			class ShaderContext;

			struct load_file_to_string
			{
				template <typename IterContextT>
				class inner
				{
				public:
					template <typename PositionT>
					static void init_iterators(IterContextT &iter_ctx, 
						PositionT const &act_pos, boost::wave::language_support language)
					{
						typedef typename IterContextT::iterator_type iterator_type;

						// read in the file
						ShaderContext &context = iter_ctx.ctx.derived();
						if (!context.readEntireFile(context.getCurrentIncludeFileName(), iter_ctx.instring))
						{ // Call ShaderContext::readEntireFile
							BOOST_WAVE_THROW_CTX(iter_ctx.ctx, preprocess_exception, 
								bad_include_file, context.getCurrentIncludeFileName().c_str(), act_pos);
							return;
						}

						iter_ctx.first = iterator_type(
							iter_ctx.instring.begin(), iter_ctx.instring.end(), 
							PositionT(iter_ctx.filename), language);
						iter_ctx.last = iterator_type();
					}
					
					private:
						std::string instring;
				};
			};

			struct PreprocessingHooks : public boost::wave::context_policies::default_preprocessing_hooks
			{
				template <typename ContextT, typename ContainerT>
				bool interpret_pragma(ContextT const &ctx, ContainerT &pending, 
					typename ContextT::token_type const &option, 
					ContainerT const &values, 
					typename ContextT::token_type const &pragma_token)
				{
					if (option.get_value() == "echo")
					{
						pending = values;
						pending.push_back(typename ContainerT::value_type(boost::wave::T_NEWLINE, "\n", values.rbegin()->get_position()));
						return true;
					}
					return false;
				}

				template <typename ContextT, typename ContainerT>
				bool 
					emit_line_directive(ContextT const& ctx, ContainerT &pending, 
					typename ContextT::token_type const& act_token)
				{
					std::ostringstream oss;
					const ShaderContext &context = ctx.derived();
					oss << "//line " << act_token.get_position().get_line() << " " << context.getCurrentFileName();
					
					typename ContextT::token_type::position_type pos;
					pos.set_line(act_token.get_position().get_line());
					pos.set_column(1);
					pos.set_file(context.getCurrentFileName().c_str());
					
					pending.push_back(ContainerT::value_type(boost::wave::T_CPPCOMMENT, oss.str().c_str(), pos));
					pos.set_column(pos.get_column() + oss.str().size());
					pending.push_back(ContainerT::value_type(boost::wave::T_GENERATEDNEWLINE, "\n", pos));
					return true;
				}

				template <typename ContextT>
				bool found_include_directive(ContextT const& ctx, std::string const& filename, 
					bool include_next) 
				{
					if (filename.size() < 3)
						return true; // incorect filename

					bool system_path;
					if (filename[0] == '<' && filename[filename.size()-1] == '>')
					{
						system_path = true;
					}
					else if (filename[0] == '\"' && filename[filename.size()-1] == '\"')
					{
						system_path = false;
					}
					else
					{
						return true; // incorect filename
					}

					ShaderContext &context = const_cast<ShaderContext &>(ctx.derived()); // stupid const here
					context.foundIncludeDirective(filename.substr(1, filename.size() - 2), system_path);
					return false;    // ok to include this file
				}

				template <typename ContextT>
				void opened_include_file(ContextT const& ctx, std::string const& relname, 
					std::string const& absname, bool is_system_include) 
				{
					ShaderContext &context = const_cast<ShaderContext &>(ctx.derived()); // stupid const here
					// using filename from previous found_include_directive call
					context.openedIncludeFile(context.getCurrentIncludeFileName());
				}

				template <typename ContextT>
				void returning_from_include_file(ContextT const& ctx) 
				{
					ShaderContext &context = const_cast<ShaderContext &>(ctx.derived()); // stupid const here
					context.returningFromIncludeFile();
				}
			};

			typedef boost::wave::context<
				std::string::iterator,
				lex_iterator_type,
				load_file_to_string,
				PreprocessingHooks,
				ShaderContext> context_type;


			class ShaderContext : public context_type
			{
			public:
				ShaderContext(
					target_iterator_type const &first_,
					target_iterator_type const &last_, 
					char const *fname,
					FileSystem *fs) : context_type(first_, last_, fname)
				{
					file_system = fs;
					file_name_stack.push_back(fname);
				}

				bool readEntireFile(const std::string &file_name, std::string &out)
				{ // Used by load_file_to_string
					return gb::fs::readEntireFile(*file_system, file_name, out);
				}

				void foundIncludeDirective(const std::string &filename, bool system_path)
				{
					found_include_file_path = file_name_stack[file_name_stack.size() - 1].parent_path() / filename;
				}

				const std::string getCurrentIncludeFileName() const
				{
					return found_include_file_path.string();
				}

				void openedIncludeFile(const std::string &filename)
				{
					file_name_stack.push_back(filename);
				}

				void returningFromIncludeFile()
				{
					file_name_stack.pop_back();
				}

				const std::string &getCurrentFileName() const
				{
					return file_name_stack[file_name_stack.size() - 1].string();
				}

			private:
				FileSystem *file_system;

				typedef boost::filesystem::path Path;
				std::vector<Path> file_name_stack;
				Path found_include_file_path;
			};
		};

		ShaderPreprocessor::ShaderPreprocessor(fs::FileSystem *fs)
		{
			pimpl = new ShaderPreprocessorImpl(fs);
		}
		
		ShaderPreprocessor::~ShaderPreprocessor()
		{
			delete pimpl;
		}
		
		bool ShaderPreprocessor::load(const std::string &path, const std::vector<std::string> &macro_definitions, std::string &shader_out)
		{
			return pimpl->load(path, macro_definitions, shader_out);
		}
	}
}

#endif // GB_ALLOW_BOOST_LIBRARY