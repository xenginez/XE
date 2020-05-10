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

template< typename T > struct BufferReadable;

class XE_API Buffer
{
public:
	static constexpr XE::uint64 BEG = 0;
	static constexpr XE::uint64 END = std::numeric_limits<XE::uint64>::max();

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
	XE::uint64 ReadPos() const;

	XE::uint64 WirtePos() const;

	void Seek( XE::uint64 val );

	void Resize( XE::uint64 val );

public:
	void Read( char * ptr, XE::uint64 size );

	void Wirte( const char * ptr, XE::uint64 size );

public:
	template< typename T > void Read( T & val )
	{
		BufferReadable<T>::Read( *this, val );
	}

	template< typename T > void Wirte( const T & val )
	{
		BufferWirteable<T>::Wirte( *this, val );
	}

public:
	void Reset();

public:
	XE::memory_view View() const;

private:
	XE::uint64 _ReadPos;
	XE::uint64 _WirtePos;
	XE::Array<char> _Data;
};
DECL_META_CLASS( XE_API, Buffer );

template< typename T > struct BufferReadable
{
	static void Read( Buffer & buf, T & val )
	{
		buf.Read( ( char * )&val, sizeof( T ) );
	}
};

template< typename T > struct BufferWirteable
{
	static void Wirte( Buffer & buf, const T & val )
	{
		buf.Wirte( ( const char * )&val, sizeof( T ) );
	}
};

template< typename T > struct BufferReadable< T * >
{
	static void Read( Buffer & buf, T * val )
	{
		buf.Read( ( char * )val, sizeof( T ) );
	}
};

template< typename T > struct BufferWirteable< T * >
{
	static void Wirte( Buffer & buf, const T * val )
	{
		buf.Wirte( ( const char * )val, sizeof( T ) );
	}
};

END_XE_NAMESPACE

template<> struct XE::Serializable<XE::Buffer>
{
public:
	static void Serialize( Archive & arc, XE::Buffer * val )
	{
		std::string code;
		auto view = val->View();
		BASE64::Encode( (const char * )view.data(), view.size(), &code );

		auto nvp = XE::Archive::NVP( "data", code );
		arc & nvp;

		val->Resize( BASE64::DecodedLength( code ) );
		view = val->View();
		BASE64::Decode( code, (char * )view.data(), view.size() );
	}
};

#endif // BUFFER_H__E817FF86_E6FC_4F72_B38E_70A67AFE6BF9
