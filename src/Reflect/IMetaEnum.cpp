#include "IMetaEnum.h"

USING_XE

XE::IMetaEnum::IMetaEnum( const String& Name, XE::uint64 Size, IMetaInfoPtr Owner )
	:IMetaType( Name, MetaType::ENUM, Size, Owner )
{

}

XE::IMetaEnum::~IMetaEnum()
{

}

XE::uint64 XE::IMetaEnum::GetEnumCount() const
{
	return _Values.size();
}

XE::String XE::IMetaEnum::FindName( int64 val ) const
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

XE::int64 XE::IMetaEnum::FindValue( const String& val ) const
{
	for ( auto var : _Values )
	{
		if ( var.first == val )
		{
			return var.second;
		}
	}

	return std::numeric_limits<int64>::max();
}

void XE::IMetaEnum::Visit( std::function<void( String, int64 )> val ) const
{
	for ( auto var : _Values )
	{
		val( var.first, var.second );
	}
}

void XE::IMetaEnum::_RegisterValue( const String& Name, int64 Val )
{
	_Values.push_back( std::make_pair( Name, Val ) );
}
