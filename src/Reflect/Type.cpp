#include "Type.h"

#include "IMetaInfo.h"
#include "Reflection.h"



XE::MetaException::MetaException( IMetaInfoCPtr Meta, const String& Msg )
	:_Meta( Meta ), _Msg( Msg )
{

}

XE::MetaException::~MetaException()
{

}

char const* XE::MetaException::What() const
{
	return ( "MetaException: " + _Meta->GetFullName() + " " + _Msg ).c_str();
}

XE::IMetaInfoCPtr XE::MetaException::GetMetaInfo() const
{
	return _Meta;
}
