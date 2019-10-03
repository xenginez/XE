#include "Order.h"

#include "CRC32.h"

USING_XE

struct OrderInfo
{
	XE::uint64 id;
	String name;
	String desc;
	IMetaInfoPtr info;
};

struct Order::Private
{
	std::hash<XE::String> Hash;
	XE::Array< XE::Map<XE::uint64, OrderInfo> > Groups;
};

Order::Order()
	:_p( new Private )
{
}

Order::~Order()
{
	delete _p;
}

XE::String XE::Order::FindOrderName( XE::uint64 id )
{
	XE::uint64 group = id >> 56;

	auto it = Instance()->_p->Groups[group].find( id );
	if ( it != Instance()->_p->Groups[group].end() )
	{
		return it->second.name;
	}

	return String();
}

XE::String XE::Order::FindOrderDesc( XE::uint64 id )
{
	XE::uint64 group = id >> 56;

	auto it = Instance()->_p->Groups[group].find( id );
	if ( it != Instance()->_p->Groups[group].end() )
	{
		return it->second.desc;
	}

	return String();
}

XE::IMetaInfoPtr XE::Order::FindOrderPatameter( XE::uint64 id )
{
	XE::uint64 group = id >> 56;

	auto it = Instance()->_p->Groups[group].find( id );
	if ( it != Instance()->_p->Groups[group].end() )
	{
		return it->second.info;
	}

	return nullptr;
}

XE::uint64 XE::Order::RegisterOrder_P( XE::uint8 group, const String& name, const String& desc, const IMetaInfoPtr & parameter )
{
	if ( group >= Instance()->_p->Groups.size() )
	{
		Instance()->_p->Groups.resize( group + 1 );
	}

	XE::uint64 crc = ( XE::uint64( group ) << 48 ) | Instance()->_p->Hash(name);
	
	auto it = Instance()->_p->Groups[group].find( crc );
	if ( it != Instance()->_p->Groups[group].end() )
	{
		if ( it->second.name == name )
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

XE::uint64 XE::Order::FindOrderID_P( XE::uint8 group, const String& name )
{
	XE::uint64 crc = ( XE::uint64( group ) << 48 ) | Instance()->_p->Hash(name);

	auto it = Instance()->_p->Groups[group].find( crc );
	if ( it != Instance()->_p->Groups[group].end() )
	{
		if ( it->second.name == name )
		{
			return crc;
		}
	}

	return Invalid;
}

void XE::Order::VisitOrder_P( XE::uint8 group, std::function< void( XE::uint64, String, String, const IMetaInfoPtr & ) > val )
{
	for ( const auto & it : Instance()->_p->Groups[group] )
	{
		val( it.second.id, it.second.name, it.second.desc, it.second.info );
	}
}
