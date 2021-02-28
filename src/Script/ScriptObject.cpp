#include "ScriptObject.h"

BEG_META( XE::ScriptObject )
END_META()

XE::ScriptObject::ScriptObject()
{

}

XE::ScriptObject::~ScriptObject()
{

}

XE::IMetaClassPtr XE::ScriptObject::GetMetaClassStatic()
{
	static auto p = XE::MakeShared< XE::CXXMetaClass<XE::ScriptObject> >( "ScriptObject", ::XE_ClassID<XE::Object>::Get(), nullptr, GetModule() );
	return p;
}

XE::IMetaClassPtr XE::ScriptObject::GetMetaClass() const
{
	return _MetaClass ? _MetaClass : GetMetaClassStatic();
}

XE::ScriptGCMarker XE::ScriptObject::GetMarker() const
{
	return _Marker;
}

void XE::ScriptObject::SetMarker( XE::ScriptGCMarker val )
{
	_Marker = val;
}

void XE::ScriptObject::SetMetaClass( const XE::IMetaClassPtr & val )
{
	_MetaClass = val;
}

XE::ScriptObject::FinalizeCallbackType XE::ScriptObject::GetFinalizeCallback() const
{
	return _Finalize;
}

void XE::ScriptObject::SetFinalizeCallback( XE::ScriptObject::FinalizeCallbackType val )
{
	_Finalize = val;
}
