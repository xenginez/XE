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

class XE_API Layer
{
public:
	static constexpr XE::uint64 Default = std::numeric_limits<XE::uint64>::max();

public:
	Layer();

	Layer( XE::uint64 val );

	Layer( const Layer& val );

	~Layer();

public:
	operator XE::uint64() const;

public:
	Layer& operator=( XE::uint64 val );

	Layer& operator |=( XE::uint64 val );

	Layer& operator &=( XE::uint64 val );

	Layer& operator=( const Layer& val );

	Layer& operator |=( const Layer& val );

	Layer& operator &=( const Layer& val );

public:
	bool operator ||( XE::uint64 val ) const;

	bool operator &&( XE::uint64 val ) const;

	bool operator ==( XE::uint64 val ) const;

	bool operator !=( XE::uint64 val ) const;

	bool operator ||( const Layer& val ) const;

	bool operator &&( const Layer& val ) const;

	bool operator ==( const Layer& val ) const;

	bool operator !=( const Layer& val ) const;

public:
	Layer operator |( XE::uint64 val ) const;
	
	Layer operator &( XE::uint64 val ) const;
	
	Layer operator ^( XE::uint64 val ) const;
	
	Layer operator |( const Layer& val ) const;
	
	Layer operator &( const Layer& val ) const;
	
	Layer operator ^( const Layer& val ) const;


public:
	XE::uint64 GetValue() const;

	void SetValue( XE::uint64 val );

private:
	XE::uint64 _Value;
};
DECL_META_CLASS( XE_API, Layer );

END_XE_NAMESPACE


bool operator ||( XE::uint64 val1, const XE::Layer& val2 );

bool operator &&( XE::uint64 val1, const XE::Layer& val2 );

bool operator ==( XE::uint64 val1, const XE::Layer& val2 );

bool operator !=( XE::uint64 val1, const XE::Layer& val2 );

XE::Layer operator |( XE::uint64 val1, const XE::Layer& val2 );

XE::Layer operator &( XE::uint64 val1, const XE::Layer& val2 );

XE::Layer operator ^( XE::uint64 val1, const XE::Layer& val2 );


#endif // __LAYER_H__9354CE9B_22E2_468A_94EB_2511A6F08E22
