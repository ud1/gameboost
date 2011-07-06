

#pragma once

// сервер значений , которые обсуждали по асе

class UfServer {
public:
	UfServer();
	~UfServer() { m_values.clear(); }

	// зарегистрировать переменную по иvенам names(имена должны быть разделены запятыми и без пробелов),
	//  которая будет получена обратным вызовом func. 
	size_t register_value(const ctd::string& names, TFuncGetValue func, void* pUserPtr);

	//  поиск переменной по имени, если не найдена то вернёт минус один.
	size_t search_value(const std::string& name) const ;

	// получить переменную
	const float* get_value(const size_t index) const ;


	typedef const float* (__cdecl *TFuncGetValue) (void* );
  
  
	private:
	
		struct value_info 
		{
			std::vector<std::string> names;
			TFuncGetValue func;
			void* pUserPtr;

			value_info()
			{
				func = NULL;
				pUserPtr = NULL;
			}
		};

	std::vector<value_type> m_values;
};

//=========================================================================

UfServer::UfServer()
{
     m_values.reserve(64); // <-  хз скока перем.. будет .  64  должно хватить.
}

size_t UfServer::register_value(const std::string& names, TFuncGetValue func, void* pUserPtr) throw()
{
 //  do parse names
 std::vector<std::string> names;
 
 .....
 
	// check params
	if(!func)
	{
		throw std::runtime_error("bad parameter"); 
	}
 

	// add to vector

	value_info vi;
	vi.names = names;
	vi.func = func;
	vi.pUserPtr = pUserPtr;
	m_values.push_back(vt);
	return m_values.size()-1; // last
}

size_t UfServer::search_value(const std::string& name_arg ) const
{
	// make upper
	std::string name =  boost::toupper_copy(name_arg);
	......
	
	for( size_t c=0; c<m_values.size(); c++ )
	{
	const value_info& vi = m_values[c];
		for(size_t j=0; j<vi.names.size(); j++)
		{
			if( name == vi.names[c] )
			{
			// found !
			return c;
			}
		}

	}

	// not found 
	return -1;
}

const float* UfServer::get_value(const size_t index) const throw(std::runtime_error)
{
  if(index > m_values.size()-1)
  {
  throw std::runtime_error("bad index");
  }
  
  const value_info& vi = m_values.at(index);

  const float* res =  vi.func(vi.pUserParam);
  return res;
}

 

// end file