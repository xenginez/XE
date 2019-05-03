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

template< uint64 T > class OrderGroup;

class UTILS_API Order : public Singleton< Order >
{
	friend Singleton< Order >;

private:
	struct Private;

public:
	static const uint64 invalid = 0;

private:
	Order();

	~Order();

public:
	template< typename T > static uint64 RegisterOrder( const String& name, const String& desc, const IMetaInfo * parameter )
	{
		return RegisterOrder_P( T::group_value, name, desc, parameter );
	}

	template< typename T > static uint64 FindOrderID( const String& name )
	{
		return FindOrderID_P( T::group_value, name );
	}

	template< typename T > static void VisitOrder( std::function< void( uint64, String, String, const IMetaInfo * ) > val )
	{
		VisitOrder_P( T::group_value, val );
	}

public:
	static String FindOrderName( uint64 id );

	static String FindOrderDesc( uint64 id );

	static const IMetaInfo * FindOrderPatameter( uint64 id );

private:
	static uint64 RegisterOrder_P( uint64 group, const String& name, const String& desc, const IMetaInfo * parameter );

	static uint64 FindOrderID_P( uint64 group, const String& name );

	static void VisitOrder_P( uint64 group, std::function< void( uint64, String, String, const IMetaInfo * ) > val );

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __ORDER_H__F15EE138_6173_4905_9684_08685B5F706A
