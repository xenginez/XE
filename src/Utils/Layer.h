/*!
 * \file   Layer.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/11
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __LAYER_H__9354CE9B_22E2_468A_94EB_2511A6F08E22
#define __LAYER_H__9354CE9B_22E2_468A_94EB_2511A6F08E22

#include "Type.h"

BEG_XE_NAMESPACE

class UTILS_API Layer
{
public:
	static constexpr uint64 Default = 1;

public:
	Layer();

	Layer( uint64 val );

	Layer( const Layer& val );

	~Layer();

public:
	Layer& operator=( uint64 val );

	Layer& operator |=( uint64 val );

	Layer& operator &=( uint64 val );

	Layer& operator=( const Layer& val );

	Layer& operator |=( const Layer& val );

	Layer& operator &=( const Layer& val );

public:
	bool operator ||( uint64 val ) const;

	bool operator &&( uint64 val ) const;

	bool operator ==( uint64 val ) const;

	bool operator !=( uint64 val ) const;

	bool operator ||( const Layer& val ) const;

	bool operator &&( const Layer& val ) const;

	bool operator ==( const Layer& val ) const;

	bool operator !=( const Layer& val ) const;

public:
	uint64 Value;
};
DECL_META_CLASS( UTILS_API, Layer );

END_XE_NAMESPACE


bool operator ||( XE::uint64 val1, const XE::Layer& val2 );

bool operator &&( XE::uint64 val1, const XE::Layer& val2 );

bool operator ==( XE::uint64 val1, const XE::Layer& val2 );

bool operator !=( XE::uint64 val1, const XE::Layer& val2 );


#endif // __LAYER_H__9354CE9B_22E2_468A_94EB_2511A6F08E22
