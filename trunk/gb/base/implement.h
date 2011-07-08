#pragma once

#include "abstract.h"

namespace gb
{

 namespace base 
 {



//! \brief  Для объектов имеющих уникальный целый идентификатор
class UuidHas : public IUuidHas {
public:
   UuidHas(const uint32_t _uuid) :m_uuid(_uuid)  {}
   //! \brief   Получить целочисленый идентификатор .
   virtual uint32_t  uuid() const { return m_uuid; }

private:
  uint32_t m_uuid;
};



//! для объектов имеющих имя в виде буфера строки (32 байта)
class Named {
public:

  Named(const char* strName)
  {
    strncpy(m_strName, strName, 31);
  }  
  
  virtual const char* name() const { return m_strName; }
  
private:
  char m_strName[32];
};




//! для объектов имеющих имя в виде std::string
class Named_s : public INamed_s {
public:
      Named_s(const std::string name) : m_strName_s(name)  {}

	  virtual const std::string name() const { return m_strName_s; }

private:
   std::string   m_strName_s;
};



//! \brief  Для объектов имеющих информацию о версии  создания
class Versioned : public IVersioned {
public: 
	 
 
	Versioned( const VERSION& v) : m_version(v)
  {
     assert(false);
  }

 

   virtual VERSION  version() const { return m_version; }

private:
   VERSION  m_version;
};



 }
}

// end file