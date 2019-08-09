#include "XSMetaEnum.h"

USING_XE

XE::XSMetaEnum::XSMetaEnum( const String & Name, IMetaInfoPtr Owner, const String & ModuleName )
	:IMetaEnum( Name, sizeof( XE::int64 ), Owner, ModuleName )
{

}

XE::XSMetaEnum::~XSMetaEnum()
{

}

void XE::XSMetaEnum::Value( const std::string & name, XE::int64 val )
{
	_RegisterValue( name, val );
}
