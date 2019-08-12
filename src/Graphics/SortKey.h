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

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API SortKey
{
public:
	union
	{
		XE::uint64 key;
		struct
		{
			XE::uint64 layer : 4;
			XE::uint64 order : 12;
			XE::uint64 blend : 1;
			XE::uint64 shader : 11;
			XE::uint64 texture : 12;
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

template< typename T > XE_INLINE SortKey MakeSortKey( const T & val )
{
	return SortKey();
}

END_XE_NAMESPACE

#endif // SORTKEY_H__4EBCA720_61A2_4DB5_8EF8_0A6508E209F6
