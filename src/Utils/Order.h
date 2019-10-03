/*!
 * \file   Order.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ORDER_H__F15EE138_6173_4905_9684_08685B5F706A
#define __ORDER_H__F15EE138_6173_4905_9684_08685B5F706A

#include "Type.h"

BEG_XE_NAMESPACE

template< XE::uint64 T > class OrderGroup;

class XE_API Order : public Singleton< Order >
{
	friend Singleton< Order >;

private:
	struct Private;

public:
	static const XE::uint64 Invalid = std::numeric_limits<XE::uint64>::max();

private:
	Order();

	~Order();

public:
	template< typename T > static XE::uint64 RegisterOrder( const String& name, const String& desc, const IMetaInfoPtr & parameter )
	{
		return RegisterOrder_P( T::group_value, name, desc, parameter );
	}

	template< typename T > static XE::uint64 FindOrderID( const String& name )
	{
		return FindOrderID_P( T::group_value, name );
	}

	template< typename T > static void VisitOrder( std::function< void( XE::uint64, String, String, const IMetaInfoPtr & ) > val )
	{
		VisitOrder_P( T::group_value, val );
	}

public:
	static String FindOrderName( XE::uint64 id );

	static String FindOrderDesc( XE::uint64 id );

	static IMetaInfoPtr FindOrderPatameter( XE::uint64 id );

private:
	static XE::uint64 RegisterOrder_P( XE::uint8 group, const String& name, const String& desc, const IMetaInfoPtr & parameter );

	static XE::uint64 FindOrderID_P( XE::uint8 group, const String& name );

	static void VisitOrder_P( XE::uint8 group, std::function< void( XE::uint64, String, String, const IMetaInfoPtr & ) > val );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __ORDER_H__F15EE138_6173_4905_9684_08685B5F706A
