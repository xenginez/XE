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

class XE_API Buffer : public XE::Array<char>
{
public:
	Buffer();

	template <class _Iter>
	Buffer( _Iter _First, _Iter _Last )
		:XE::Array<char>( _First, _Last )
	{
	}

	Buffer( Buffer && _Right )
		: XE::Array<char>( std::move( _Right ) )
	{
	}

	Buffer( const Buffer & _Right )
		:XE::Array<char>( _Right )
	{
	}

	Buffer( XE::memory_view _Right )
		:XE::Array<char>( _Right.data(), _Right.data() + _Right.size() )
	{

	}

public:
	Buffer & operator=( Buffer && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			XE::Array<char>::operator=( std::move( _Right ) );
		}

		return *this;
	}

	Buffer & operator=( const Buffer & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			assign( _Right.begin(), _Right.end() );
		}

		return *this;
	}

public:
	~Buffer();

public:
	void push_back( bool val );

	void push_back( XE::int8 val );

	void push_back( XE::int16 val );

	void push_back( XE::int32 val );

	void push_back( XE::int64 val );

	void push_back( XE::uint8 val );

	void push_back( XE::uint16 val );

	void push_back( XE::uint32 val );

	void push_back( XE::uint64 val );

	void push_back( XE::float32 val );

	void push_back( XE::float64 val );

public:
	XE::memory_view GetView() const;

};
DECL_META_CLASS( XE_API, Buffer );

END_XE_NAMESPACE

template<> struct XE::Serializable<XE::Buffer>
{
public:
	static void Serialize( Archive & arc, XE::Buffer * val )
	{
		if( arc.GetType() == ArchiveType::LOAD )
		{
			std::string str;

			arc & Archive::NVP( "data", str );

			val->resize( BASE64::DecodedLength( str ) );

			BASE64::Decode( str, (char * )val->data(), val->size() );
		}
		else
		{
			std::string str;

			BASE64::Encode( (const char * )val->data(), val->size(), &str );

			arc & Archive::NVP( "data", str );
		}
	}
};

#endif // BUFFER_H__E817FF86_E6FC_4F72_B38E_70A67AFE6BF9
