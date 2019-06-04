/*!
 * \file   BASE64.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BASE64_H__42CDEC97_29D9_428E_94CF_C482E8BA58C4
#define __BASE64_H__42CDEC97_29D9_428E_94CF_C482E8BA58C4

#include "Global.h"

BEG_XE_NAMESPACE

class UTILS_API BASE64
{
public:
	static std::string Encode( const uint8 * src, XE::uint64 size );

	static XE::uint64 Encode( const uint8 * src, XE::uint64 size, uint8 * out );

	static XE::uint64 Decode( const std::string& str, char * out );

	static XE::uint64 Decode( const uint8* src, XE::uint64 size, char * out );

private:
	static const char _base64_encode_table[65];
	static const char _base64_decode_table[256];
};
DECL_META_CLASS( UTILS_API, BASE64 );

END_XE_NAMESPACE

#endif // __BASE64_H__42CDEC97_29D9_428E_94CF_C482E8BA58C4
