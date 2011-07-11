/** \file
 \brief boost::any wrapper


*/

#pragma once

#include <gb/base/Types.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <boost/any.hpp>



#pragma warning(push)
#pragma warning(disable : 4290)


namespace gb
{

	namespace t
	{




//#define throw_cast  throw(std::runtime_error&)

class Any 
{
private:

	boost::any m_any;
	size_t m_element_size;
	size_t m_num_elements;

public:
 

	//! value is empty ?
	bool empty() const 
	{
		return m_any.empty();
	}

	//! return true if holde vector
	bool is_array() const throw(std::runtime_error&)
	{
		if(m_num_elements == 0)
		{
			throw std::runtime_error("empty");
		}
		return num_elements() > 1;
	}

	//! return sizeof current element
	size_t element_size() const
	{
	   return m_element_size;
	}

	//! name of current type
	const char*  type_name() const 
	{
		return m_any.type().name();
	}

	//! num elements
	size_t num_elements() const
	{
		return m_num_elements;
	}
 
	// constructor
	Any() 
	{
		m_element_size = 0;
		m_num_elements = 0;
	}

	template <typename T>
	Any(const T& value)
	{
		T _local = value;
		*this = _local;
	}

	~Any() {}

	template <typename T>
	void operator = (const T value)
	{
		m_any = value;
		m_element_size = sizeof(T);
		m_num_elements = 1;
	}

	template <typename T>
	operator T() const throw (std::runtime_error)
	{
		T value;

		try 
		{
		 value = m_any;
		}
		catch(boost::bad_any_cast)
		{
			throw std::runtime_error("cast error");
		}

		return value;
	}


	void operator = (const char* pStr)
	{
	    std::string str(pStr);
		*this =  str;
	}

	void operator = (const wchar_t* pStr)
	{
		std::wstring str(pStr);
		*this =  str;
	}

	template<typename T>
	//! assign array
	void operator = (const std::vector<T>& values)
	{
		m_any = values;
		m_element_size = sizeof(T);
		m_num_elements = values.size();
	}

 

	template<typename T>
	//! cast to array
	operator std::vector<T>() throw(std::runtime_error)
	{
		  std::vector<T> res;
		  try
		  {
			res =  boost::any_cast< std::vector<T> >(m_any);
		  }
		  catch ( boost::bad_any_cast )
		  {
			  throw std::runtime_error ("cast error"); 
		  }

	  return res;
	}

	 

};

#pragma warning(pop)

	}
	// end namespace

}
// end namespace

// end file