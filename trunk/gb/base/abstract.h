/** \file
 \brief Самые базовые абстрактные интерфейсы


  \todo все реализации перенести в другой заголовок, тут оставить только абстрактники

  
*/


#pragma once
#include "Types.h"
#include "version.h"
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


class IVersioned {
public:

  virtual VERSION  version() const =0;
  
};





//---------------------------------------------------------------
}
}

#pragma warning (pop)

// end file