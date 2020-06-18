#include "Order.h"

#include "CRC32.h"



struct OrderInfo
{
	XE::uint64 id;
	XE::String name;
	XE::String desc;
	XE::IMetaInfoPtr info;
};

struct XE::Order::Private
{
	std::hash<XE::String> Hash;
	XE::Array< XE::Map<XE::uint64, OrderInfo> > Groups;
};

XE::Order::Order()
	:_p( new Private )
{
}

XE::Order::~Order()
{
	delete _p;
}

XE::String XE::Order::FindOrderName( XE::uint64 id )
{
	XE::uint64 group = id >> 56;

	auto it = Instance()->_p->Groups[group].find( id );
	if( it != Instance()->_p->Groups[group].end() )
	{
		return it->second.name;
	}

	return String();
}

XE::String XE::Order::FindOrderDesc( XE::uint64 id )
{
	XE::uint64 group = id >> 56;

	auto it = Instance()->_p->Groups[group].find( id );
	if( it != Instance()->_p->Groups[group].end() )
	{
		return it->second.desc;
	}

	return XE::String();
}

XE::IMetaInfoPtr XE::Order::FindOrderPatameter( XE::uint64 id )
{
	XE::uint64 group = id >> 56;

	auto it = Instance()->_p->Groups[group].find( id );
	if( it != Instance()->_p->Groups[group].end() )
	{
		return it->second.info;
	}

	return nullptr;
}

XE::uint64 XE::Order::RegisterOrder_P( XE::uint8 group, const XE::String & name, const XE::String & desc, const XE::IMetaInfoPtr & parameter )
{
	if( group >= Instance()->_p->Groups.size() )
	{
		Instance()->_p->Groups.resize( ( XE::uint64 )group + 1 );
	}

	XE::uint64 crc = ( XE::uint64( group ) << 48 ) | Instance()->_p->Hash( name );

	auto it = Instance()->_p->Groups[group].find( crc );
	if( it != Instance()->_p->Groups[group].end() )
	{
		if( it->second.name == name )
		{
			return crc;
		}

		return Invalid;
	}

	OrderInfo info;

	info.id = crc;
	info.name = name;
	info.desc = desc;
	info.info = parameter;

	Instance()->_p->Groups[group].insert( std::make_pair( crc, info ) );

	return crc;
}

XE::uint64 XE::Order::FindOrderID_P( XE::uint8 group, const XE::String & name )
{
	XE::uint64 crc = ( XE::uint64( group ) << 48 ) | Instance()->_p->Hash( name );

	auto it = Instance()->_p->Groups[group].find( crc );
	if( it != Instance()->_p->Groups[group].end() )
	{
		if( it->second.name == name )
		{
			return crc;
		}
	}

	return Invalid;
}

void XE::Order::VisitOrder_P( XE::uint8 group, std::function< void( XE::uint64, XE::String, XE::String, const XE::IMetaInfoPtr & ) > val )
{
	for( const auto & it : Instance()->_p->Groups[group] )
	{
		val( it.second.id, it.second.name, it.second.desc, it.second.info );
	}
}
