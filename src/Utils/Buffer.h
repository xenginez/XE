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

class XE_API Buffer : public XE::Array<std::byte>
{
public:
	Buffer();

	template <class _Iter>
	Buffer( _Iter _First, _Iter _Last )
		:XE::Array<std::byte>( _First, _Last )
	{
	}

	Buffer( Buffer && _Right )
		: XE::Array<std::byte>( std::move( _Right ) )
	{
	}

	Buffer( const Buffer & _Right )
		:XE::Array<std::byte>( _Right )
	{
	}

	Buffer( XE::memory_view _Right )
		:XE::Array<std::byte>( _Right.data(), _Right.data() + _Right.size() )
	{

	}

public:
	Buffer & operator=( Buffer && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			XE::Array<std::byte>::operator=( std::move( _Right ) );
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
			XE::uint64 size;
			std::string str;
			arc & Archive::NVP( "size", size );
			arc & Archive::NVP( "data", str );

			val->resize( size );

			BASE64::Decode( str, ( XE::uint8 * )val->data() );
		}
		else
		{
			XE::uint64 size = val->size();
			std::string str = BASE64::Encode( ( XE::uint8 * )val->data(), val->size() );

			arc & Archive::NVP( "size", size );
			arc & Archive::NVP( "data", str );
		}
	}
};

#endif // BUFFER_H__E817FF86_E6FC_4F72_B38E_70A67AFE6BF9
