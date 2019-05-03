#include "Type.h"

#include "IMetaInfo.h"

#include "Reflection.h"

USING_XE

XE::MetaException::MetaException( IMetaInfoCPtr Meta, const String& Msg )
	:_Meta( Meta ), _Msg( Msg )
{

}

XE::MetaException::~MetaException()
{

}

char const* XE::MetaException::What() const
{
	return ( "MetaException: " + _Meta->GetFullName() + " " + _Msg ).ToCString();
}

XE::IMetaInfoCPtr XE::MetaException::GetMetaInfo() const
{
	return _Meta;
}

IMetaTypePtr REFLECT_API XE::GetReclectionType( const String& val )
{
	if ( auto e = Reflection::FindEnum( val ) )
	{
		return SP_CAST<IMetaType>( e );
	}

	return SP_CAST<IMetaType>( Reflection::FindClass( val ) );
}
