/** \file
 \brief Самые базовые абстрактные интерфейсы


  \todo все реализации перенести в другой заголовок, тут оставить только абстрактники

  
*/


#pragma once
#include "Types.h"
#include <string>

// temp !!!!!
#pragma warning (push)
#pragma warning (disable : 4996)

namespace gb
{

namespace base 
{
//---------------------------------------------------------------


//! \brief  Для объектов, которые могут быть удаленыпо деструктору.
class IDestructed {
public:

  virtual ~IDestructed() {}
};

//! \brief  Абстрактный объект.
class IObject {
protected:
   virtual ~IObject() {}
};

//! \brief  абстрактные опции , например ini или прочее подобное.
class IOptions {
public:

	virtual const char* getValue( const char* strSection, const char* strkey, const char* default="" ) const =0;
	virtual void        setValue( const char* strSection, const char* strkey, const char* strValue ) =0;

};


//! \brief Для объектов имеющих уникальный целый идентификатор.
class IUuidHas {
public:

   //! \brief   Получить целочисленый идентификатор .
   virtual uint32_t  uuid() const  =0;
};


//! \brief  Для объектов имеющих уникальный целый идентификатор
class UuidHas : public IUuidHas {
public:
   UuidHas(const uint32_t _uuid) :m_uuid(_uuid)  {}
   //! \brief   Получить целочисленый идентификатор .
   virtual uint32_t  uuid() const { return m_uuid; }

private:
  uint32_t m_uuid;
};


//! \brief  Для объектов имеющих уникальный идентификатор типа
class ITipeIdHas {
public:

   //! \brief  Получить уникальный идентификатор типа.
   virtual uint32_t typeId() const =0;
};


//! \brief  Для объектов имеющих имя  в виде строкового буфера.
class INamed {
public:
	  //! \brief  Получить имя объекта в виде c-строки .
      virtual const char* name() const =0;
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


//! \brief  Для объектов имеющих имя типа  в виде строкового буфера.
class ITypeNamed {
public:
	  //! \brief  Получить имя объекта в виде c-строки .
      virtual const char* type_name() const =0;
};


//!   \brief   для объектов имеющих имя в виде std::string .
class INamed_s {
public:

	  virtual const std::string name() const =0;
};


//! для объектов имеющих имя в виде std::string
class Named_s : public INamed_s {
public:
      Named_s(const std::string name) : m_strName_s(name)  {}

	  virtual const std::string name() const { return m_strName_s; }

private:
   std::string   m_strName_s;
};



//---------------------------------------------------------------
}
}

#pragma warning (pop)

// end file