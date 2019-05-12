#include "Object.h"

#include "IFramework.h"
#include "ILocalizationService.h"

USING_XE

BEGIN_META(Object)
END_META()

XE::Object::Object()
{
}

XE::Object::~Object()
{
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

void XE::Object::Load( Archive &val )
{
	XE::Variant v(this);
	GetMetaClass()->Serialize(&val, v);
}

void XE::Object::Save( Archive &val ) const
{
	XE::Variant v(this);
	GetMetaClass()->Serialize(&val, v);
}

XE::String XE::Object::tr( const XE::String &val ) const
{
	return _Framework->GetLocalizationService()->LocalizedString(val);
}
