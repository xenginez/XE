#include "Order.h"

#include "CRC32.h"

USING_XE

struct OrderInfo
{
	XE::uint64 id;
	String name;
	String desc;
	const IMetaInfo * info;
};

struct Order::Private
{
	std::vector< std::map<XE::uint64, OrderInfo> > Groups;
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
	XE::uint64 group = id >> 32;

	auto it = This()->_p->Groups[group].find( id );
	if ( it != This()->_p->Groups[group].end() )
	{
		return it->second.name;
	}

	return String();
}

XE::String XE::Order::FindOrderDesc( XE::uint64 id )
{
	XE::uint64 group = id >> 32;

	auto it = This()->_p->Groups[group].find( id );
	if ( it != This()->_p->Groups[group].end() )
	{
		return it->second.desc;
	}

	return String();
}

const XE::IMetaInfo * XE::Order::FindOrderPatameter( XE::uint64 id )
{
	XE::uint64 group = id >> 32;

	auto it = This()->_p->Groups[group].find( id );
	if ( it != This()->_p->Groups[group].end() )
	{
		return it->second.info;
	}

	return nullptr;
}

XE::uint64 XE::Order::RegisterOrder_P( XE::uint64 group, const String& name, const String& desc, const IMetaInfo * parameter )
{
	if ( group >= This()->_p->Groups.size() )
	{
		This()->_p->Groups.resize( group + 1 );
	}

	XE::uint64 crc = ( group << 32 ) + CRC32::GetCRC32( (XE::uint32)group, (const XE::uint8 *)name.ToCString(), name.Size() );

	auto it = This()->_p->Groups[group].find( crc );
	if ( it != This()->_p->Groups[group].end() )
	{
		if ( it->second.name == name )
		{
			return crc;
		}

		return invalid;
	}

	OrderInfo info;

	info.id = crc;
	info.name = name;
	info.desc = desc;
	info.info = parameter;

	This()->_p->Groups[group].insert( std::make_pair( crc, info ) );

	return crc;
}

XE::uint64 XE::Order::FindOrderID_P( XE::uint64 group, const String& name )
{
	XE::uint64 crc = ( group << 32 ) + CRC32::GetCRC32( (XE::uint32)group, (const XE::uint8 *)name.ToCString(), name.Size() );

	auto it = This()->_p->Groups[group].find( crc );
	if ( it != This()->_p->Groups[group].end() )
	{
		if ( it->second.name == name )
		{
			return crc;
		}
	}

	return invalid;
}

void XE::Order::VisitOrder_P( XE::uint64 group, std::function< void( XE::uint64, String, String, const IMetaInfo * ) > val )
{
	for ( auto it : This()->_p->Groups[group] )
	{
		val( it.second.id, it.second.name, it.second.desc, it.second.info );
	}
}
