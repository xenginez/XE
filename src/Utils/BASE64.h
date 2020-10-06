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

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API BASE64
{
public:
	static bool Encode( const std::string & in, std::string * out );

	static bool Encode( const char * input, size_t input_length, std::string * out );

	static bool Encode( const char * input, size_t input_length, char * out, size_t out_length );

	static bool Decode( const std::string & in, std::string * out );

	static bool Decode( const std::string & in, char * out, size_t out_length );

	static bool Decode( const char * input, size_t input_length, char * out, size_t out_length );

	static int DecodedLength( const std::string & in );

	static int DecodedLength( const char * in, size_t in_length );

	static int EncodedLength( size_t length );

	static int EncodedLength( const std::string & in );

	static void StripPadding( std::string * in );

};
DECL_META_CLASS( XE_API, BASE64 );

END_XE_NAMESPACE

#endif // __BASE64_H__42CDEC97_29D9_428E_94CF_C482E8BA58C4
