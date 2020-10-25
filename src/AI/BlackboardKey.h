/*!
 * \file	BlackboardKey.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/25
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BLACKBOARDKEY_H__039DE917_DC54_42D8_9A9D_0F3B8F39069A
#define BLACKBOARDKEY_H__039DE917_DC54_42D8_9A9D_0F3B8F39069A

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API BlackboardKey : public XE::Object
{
	OBJECT( BlackboardKey, Object )

public:
	BlackboardKey();

	BlackboardKey( const BlackboardKey & val );

	BlackboardKey( const XE::String & val );

	~BlackboardKey() override;

public:
	bool operator<( const BlackboardKey & val ) const;

	bool operator>( const BlackboardKey & val ) const;

	bool operator<=( const BlackboardKey & val ) const;

	bool operator>=( const BlackboardKey & val ) const;

	bool operator==( const BlackboardKey & val ) const;

	bool operator!=( const BlackboardKey & val ) const;

public:
	const XE::String & GetKey() const;

	void SetKey( const XE::String & val );

private:
	XE::String _Key;
};

END_XE_NAMESPACE

#endif // BLACKBOARDKEY_H__039DE917_DC54_42D8_9A9D_0F3B8F39069A
