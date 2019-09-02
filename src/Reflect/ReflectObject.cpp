#include "ReflectObject.h"

#include "Reflection.h"

USING_XE

template<> struct XE::MetaDataCollector< ReflectObject >
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

const XE::IMetaClassPtr XE::ReflectObject::GetMetaClassStatic()
{
	static auto p = XE::make_shared< CXXMetaClass<ReflectObject> >( "Object", nullptr, nullptr );
	return p;
}

const XE::IMetaClassPtr XE::ReflectObject::GetMetaClass() const
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

XE::ReflectObjectPtr XE::ReflectObject::Clone() const
{
	auto ret = GetMetaClass()->ConstructPtr().Value<ReflectObjectPtr>();

	GetMetaClass()->VisitProperty( [&]( IMetaPropertyPtr prop )
								   {
									   if( !( prop->GetFlag() & IMetaProperty::NoClone ) && !prop->IsStatic() )
									   {
										   prop->Set( ret, prop->Get( this ) );
									   }
								   } );

	return ret;
}
