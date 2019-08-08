#include "XSMetaClass.h"

USING_XE

XE::XSMetaClass::XSMetaClass( const String & Name, XE::uint64 Size, IMetaClassPtr Super, IMetaInfoPtr Owner, const String & ModuleName )
	:IMetaClass( Name, Size, false, false, Super, Owner, ModuleName )
{

}

XE::XSMetaClass::~XSMetaClass()
{

}

XE::Variant XE::XSMetaClass::Construct() const
{
	return nullptr;
}

XE::Variant XE::XSMetaClass::ConstructPtr() const
{
	return nullptr;
}

void XE::XSMetaClass::Destruct( Variant & val ) const
{

}

void XE::XSMetaClass::Serialize( Archive * arc, Variant & val ) const
{

}
