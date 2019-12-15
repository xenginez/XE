/*!
 * \file	MD5.h
 *
 * \author	ZhengYuanQing
 * \date	2019/12/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef MD5_H__EF0EE087_0F95_41D9_956F_532BA1F954FA
#define MD5_H__EF0EE087_0F95_41D9_956F_532BA1F954FA

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API MD5
{
public:
	MD5();

	MD5( XE::memory_view val );

public:
	MD5 & operator =( const MD5 & val );

	MD5 & operator =( XE::memory_view val );

public:
	std::string To16String() const;

	std::string To32String() const;

private:
	void Hash( XE::memory_view val );

private:
	char _Hash[33];
};
DECL_META_CLASS( XE_API, MD5 );

END_XE_NAMESPACE

namespace std
{
	inline std::string to_string( const XE::MD5 & _Val )
	{
		return _Val.To32String();
	}
}

#endif // MD5_H__EF0EE087_0F95_41D9_956F_532BA1F954FA
