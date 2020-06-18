#include "XSMetaProperty.h"



XE::XSMetaProperty::XSMetaProperty( const String & Name, XE::uint8 Flag, IMetaInfoPtr Value, IMetaClassPtr Owner, const String & ModuleName )
	:IMetaProperty( Name, Flag, false, false, true, false, false, false, Value, Owner, ModuleName )
{

}

XE::XSMetaProperty::~XSMetaProperty()
{

}

XE::Variant XE::XSMetaProperty::Get( const Variant & obj ) const
{
	return *( (Variant * )( ( ( XE::uint8 * )obj.ToPointer() ) + _Address ) );
}

void XE::XSMetaProperty::Set( const Variant & obj, const Variant & val ) const
{
	( *( (Variant * )( ( ( XE::uint8 * )obj.ToPointer() ) + _Address ) ) ) = val;
}
