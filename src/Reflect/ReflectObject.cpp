#include "ReflectObject.h"

#include "Reflection.h"



template<> struct XE::MetaDataCollector< XE::ReflectObject >
{
	typedef ReflectObject ThisType;
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

XE::ReflectObject::ReflectObject()
{
}

XE::ReflectObject::~ReflectObject()
{
}

XE::IMetaClassPtr XE::ReflectObject::GetMetaClassStatic()
{
	static auto p = XE::MakeShared< CXXMetaClass<ReflectObject> >( "Object", nullptr, nullptr );
	return p;
}

XE::IMetaClassPtr XE::ReflectObject::GetMetaClass() const
{
	return GetMetaClassStatic();
}

XE::Variant XE::ReflectObject::GetProperty( const String &name )
{
	return GetMetaClass()->FindProperty(name)->Get(this);
}

void XE::ReflectObject::SetProperty( const String &name, const Variant &val )
{
	GetMetaClass()->FindProperty(name)->Set(this, val);
}

void XE::ReflectObject::Serialize( Archive &val )
{
	XE::Variant v(this);
	GetMetaClass()->Serialize(&val, v);
}
