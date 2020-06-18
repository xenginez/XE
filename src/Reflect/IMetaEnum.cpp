#include "IMetaEnum.h"



XE::IMetaEnum::IMetaEnum( const String & Name, XE::uint64 Size, IMetaInfoPtr Owner, const String & ModuleName /*= "XE" */ )
	:IMetaType( Name, MetaType::ENUM, Size, Owner, ModuleName )
{

}

XE::IMetaEnum::~IMetaEnum()
{

}

XE::uint64 XE::IMetaEnum::GetEnumCount() const
{
	return _Values.size();
}

XE::String XE::IMetaEnum::FindName( XE::Variant val ) const
{
	for ( auto var : _Values )
	{
		if ( var.second == val )
		{
			return var.first;
		}
	}

	return "";
}

XE::Variant XE::IMetaEnum::FindValue( const String& val ) const
{
	for ( auto var : _Values )
	{
		if ( var.first == val )
		{
			return var.second;
		}
	}

	return XE::Variant();
}

void XE::IMetaEnum::Visit( const std::function<void( String, XE::Variant )> & val ) const
{
	for ( auto var : _Values )
	{
		val( var.first, var.second );
	}
}

void XE::IMetaEnum::_RegisterValue( const String& Name, XE::Variant Val )
{
	_Values.push_back( std::make_pair( Name, Val ) );
}
