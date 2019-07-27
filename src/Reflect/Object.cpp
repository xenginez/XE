#include "Object.h"

#include "Reflection.h"

USING_XE

template<> struct XE::MetaDataCollector< Object >
{
	typedef Object ThisType;
	MetaDataCollector()
	{
		auto type = std::conditional_t<std::is_enum<ThisType>::value, Reflection::Enum<ThisType>, Reflection::Class<ThisType>>::Get();

		Reflection::RegisterMetaInfo( type );
	}
	static void Use()
	{
		ActiveSingleton< MetaDataCollector<ThisType> >::Register();
	}
};

XE::Object::Object()
{
}

XE::Object::~Object()
{
}

const XE::IMetaClassPtr XE::Object::GetMetaClassStatic()
{
	static auto p = XE::make_shared< CXXMetaClass<Object> >( "Object", nullptr, nullptr );
	return p;
}

const XE::IMetaClassPtr XE::Object::GetMetaClass() const
{
	return GetMetaClassStatic();
}

XE::Variant XE::Object::GetProperty( const String &name )
{
	return GetMetaClass()->FindProperty(name)->Get(this);
}

void XE::Object::SetProperty( const String &name, const Variant &val )
{
	GetMetaClass()->FindProperty(name)->Set(this, val);
}

XE::ObjectPtr XE::Object::Clone() const
{
	ObjectPtr ret = SP_CAST < Object >(GetMetaClass()->ConstructPtr());
	
	GetMetaClass()->VisitProperty([&]( IMetaPropertyPtr prop )
								  {
									  if( !( prop->GetFlag() & IMetaProperty::NoClone ) && !prop->IsStatic())
									  {
										  prop->Set(ret, prop->Get(this));
									  }
								  });
	
	return ret;
}

void XE::Object::Serialize( Archive &val )
{
	XE::Variant v(this);
	GetMetaClass()->Serialize(&val, v);
}
