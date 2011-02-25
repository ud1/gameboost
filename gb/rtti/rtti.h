// examle of using http://pushkoff.blogspot.com/2010/08/dynamiccast-rtti.html

namespace gb
{
namespace rtti
{

class Type
{
  const Type*  mSuper;
  const char*    mName;
public:
  Type( const Type* parent, const char* name ): mSuper(parent), mName(name) {}
 
  inline bool Is( const Type* objtype ) const
  {
    while( objtype && objtype != this )
    {
      objtype = objtype->mSuper;
    }
    return objtype == this;
  }
 
  inline const char* GetName() const { return mName; }
};
 
#define DECLARE_GET_TYPE(cls)      \
    typedef cls  Self;    \
    virtual const gb::rtti::Type*  GetType() const { return &Type(); }
 
#define DECLARE_OBJECT(cls)    \
    typedef Self  Super;    \
    static inline const gb::rtti::Type&  Type() { static const gb::rtti::Type my_type( &cls::Super::Type(), #cls ); return my_type; }  \
    DECLARE_GET_TYPE(cls)
         
#define DECLARE_ROOT_OBJECT(cls)            \
    static inline const gb::rtti::Type&  Type() { static const gb::rtti::Type my_type( 0, #cls ); return my_type; } \
    DECLARE_GET_TYPE(cls)             \
    template <class T> static inline T* Cast( cls * obj )      \
    {                \
      return GET_CLASS_TYPE(T)->Is( GET_OBJECT_TYPE(obj) ) ? (T*)obj : NULL;  \
    }                \
    \
    template <class T> static inline const T* Cast( const cls * obj )  \
    {                \
      return GET_CLASS_TYPE(T)->Is( GET_OBJECT_TYPE(obj) ) ? (T*)obj : NULL;  \
    }
 
/////////////////////////////////////////////////////////////////////////////////
#define GET_CLASS_TYPE(cls) (&cls::Type())
#define GET_CLASS_TYPE_NAME(cls) (GET_CLASS_TYPE(cls)->GetName())
 
#define GET_OBJECT_TYPE(obj) (obj->GetType())
#define GET_OBJECT_TYPE_NAME(obj) (GET_OBJECT_TYPE(obj)->GetName())
/////////////////////////////////////////////////////////////////////////////////

	}
};