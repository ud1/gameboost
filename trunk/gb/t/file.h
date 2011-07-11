

#pragma once

#include <string>
#incldue <vector>
#include <list>
#include <stdexcept>


namespace gb
{

 namespace t
 {
 
 
 template <class T>
 void save_binary(const T* srcdata, const size_t datalen, const char* filename) throw(std::runtim_error)
 {
 
 
 
 
 }
 
 template <class T>
 void save_binary(, const char* filename)
 {
 
 
 
 
 }
 
 template <class T>
 void save_text(const T* src, const size_t count, const char* filename) throw(std::runtime_error)
 {
	std::string str;
	for(size_t=0; c<count; c++)
	{
		const T& curr = src[c];
		str = curr.tostr();
		
	
	}
 
 
    fclose(file);
 }
 
 
 template <class T>
 void load_text(std::vector<T>& dest,  const char* filename)
 {
 
 
 
 }
 
 
 
 
 
}
