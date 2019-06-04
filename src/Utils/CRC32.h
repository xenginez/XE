/*!
 * \file   CRC32.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CRC32_H__77E17FE6_6F43_4C9A_9985_D9E1478BD18B
#define __CRC32_H__77E17FE6_6F43_4C9A_9985_D9E1478BD18B

#include "Global.h"

BEG_XE_NAMESPACE

class UTILS_API CRC32
{
public:
	static uint32 GetCRC32( const uint8 * src, XE::uint64 size );

	static uint32 GetCRC32( uint32 salt, const uint8 * src, XE::uint64 size );
};
DECL_META_CLASS( UTILS_API, CRC32 );

END_XE_NAMESPACE

#endif // __CRC32_H__77E17FE6_6F43_4C9A_9985_D9E1478BD18B
