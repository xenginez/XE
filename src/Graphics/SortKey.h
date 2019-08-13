/*!
 * \file	SortKey.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/11
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SORTKEY_H__4EBCA720_61A2_4DB5_8EF8_0A6508E209F6
#define SORTKEY_H__4EBCA720_61A2_4DB5_8EF8_0A6508E209F6

#include "DrawCall.h"

BEG_XE_NAMESPACE

class GRAPHICS_API SortKey
{
public:
	union
	{
		XE::uint64 key;
		struct
		{
			XE::uint64 layer : 3;
			XE::uint64 order : 12;
			XE::uint64 blend : 1;
			XE::uint64 state : 24;
			XE::uint64 depth : 24;
		};
	};

public:
	SortKey();

	SortKey( XE::uint64 val );

public:
	bool operator <( const SortKey & val )const;

	bool operator ==( const SortKey & val )const;

	bool operator !=( const SortKey & val )const;

};

template< typename T > XE_INLINE SortKey MakeSortKey( const T & val );

XE_INLINE SortKey MakeSortKey( const RenderDrawCall & val )
{
	return SortKey();
};

XE_INLINE SortKey MakeSortKey( const IndirectDrawcall & val )
{
	return SortKey();
};

XE_INLINE SortKey MakeSortKey( const InstanceDrawcall & val )
{
	return SortKey();
};

XE_INLINE SortKey MakeSortKey( const IndexInstanceDrawcall & val )
{
	return SortKey();
};

XE_INLINE SortKey MakeSortKey( const ComputeDrawCall & val )
{
	return SortKey();
};

template< typename ... T > XE_INLINE SortKey MakeSortKey( const PacketDrawCall< T... > & val )
{
	return MakeSortKey( std::get<0>( val._DrawCalls ) );
};

END_XE_NAMESPACE

#endif // SORTKEY_H__4EBCA720_61A2_4DB5_8EF8_0A6508E209F6
