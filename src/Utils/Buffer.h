/*!
 * \file	Buffer.h
 *
 * \author	ZhengYuanQing
 * \date	2019/12/26
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BUFFER_H__E817FF86_E6FC_4F72_B38E_70A67AFE6BF9
#define BUFFER_H__E817FF86_E6FC_4F72_B38E_70A67AFE6BF9

#include "BASE64.h"

BEG_XE_NAMESPACE

class XE_API Buffer
{
public:
	static constexpr XE::uint64 beg = 0;
	static constexpr XE::uint64 end = std::numeric_limits<XE::uint64>::max();

public:
	Buffer();

	Buffer( Buffer && _Right );

	Buffer( const Buffer & _Right );

	Buffer( XE::memory_view _Right );

public:
	~Buffer();

public:
	Buffer & operator=( Buffer && _Right );

	Buffer & operator=( const Buffer & _Right );

public:
	XE::uint64 pos() const;

	void seek( XE::uint64 val );

	void resize( XE::uint64 val );

public:
	void read( std::string & val );

	void wirte( const std::string & val );

public:
	void read( char * ptr, XE::uint64 size );

	void wirte( const char * ptr, XE::uint64 size );

public:
	template< typename T > void read( T & val )
	{
		read( &val, sizeof( T ) );
	}

	template< typename T > void wirte( const T & val )
	{
		wirte( &val, sizeof( T ) );
	}

public:
	XE::memory_view view() const;

private:
	XE::uint64 _pos; 
	XE::Array<char> _data;
};
DECL_META_CLASS( XE_API, Buffer );

END_XE_NAMESPACE

template<> struct XE::Serializable<XE::Buffer>
{
public:
	static void Serialize( Archive & arc, XE::Buffer * val )
	{
		std::string code;
		auto view = val->view();
		BASE64::Encode( (const char * )view.data(), view.size(), &code );

		auto nvp = XE::Archive::NVP( "data", code );
		arc & nvp;

		val->resize( BASE64::DecodedLength( code ) );
		auto view = val->view();
		BASE64::Decode( code, (char * )view.data(), view.size() );
	}
};

#endif // BUFFER_H__E817FF86_E6FC_4F72_B38E_70A67AFE6BF9
