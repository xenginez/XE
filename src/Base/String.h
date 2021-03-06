/*!
* \file	String.hpp
*
* \author	ZhengYuanQing
* \date	2021/02/19
* \email	zhengyuanqing.95@gmail.com
*
*/
#ifndef STRING_HPP__2D116B84_5AD0_4FFF_A245_8EC14E092378
#define STRING_HPP__2D116B84_5AD0_4FFF_A245_8EC14E092378

#include <regex>
#include <vector>
#include <string>

#include "Type.h"

BEG_XE_NAMESPACE

class code_point;
class ansi_encode;
class wide_encode;
class utf8_encode;
class code_point_arrow;
class code_point_convert;
template < typename String > class basic_string_view;
template < typename Encode, typename Alloc > class basic_string;
template < typename Encode, typename Alloc > class string_iterator;
template < typename StringIterator > class string_reverse_iterator;
template< typename FromEncode, typename ToEncode > class string_convert;


class XE_API code_point
{
public:
	code_point();

	code_point( char c );

	code_point( wchar_t c );

	code_point( char16_t c );

	code_point( char32_t c );

	code_point( const code_point & other );

public:
	code_point & operator=( const code_point & c );

public:
	bool operator!=( const code_point & other ) const;

	bool operator==( const code_point & other ) const;

	bool operator<( const code_point & other ) const;

	bool operator<=( const code_point & other ) const;

	bool operator>( const code_point & other ) const;

	bool operator>=( const code_point & other ) const;

public:
	uint32_t unicode() const;

private:
	union
	{
		char c;
		wchar_t wc;
		char16_t c16;
		char32_t c32;
		uint32_t _unicode;
	};
};

class XE_API ansi_encode
{
public:
	using size_type = std::ptrdiff_t;
	using storage_unit = char;

public:
	template <typename Iterator>
	static Iterator advance( Iterator iter_begin, Iterator iter_end, size_type count )
	{
		auto iter = iter_begin;
		storage_unit value = 0;

		while( iter != iter_end && count != 0 )
		{
			value = *iter;
			if( value >= 0x80 && value <= 0xFF )
			{
				++iter;
			}

			++iter;
			--count;
		}

		return iter;
	}

	template <typename Iterator>
	static size_type distance( Iterator iter_begin, Iterator iter_end )
	{
		size_type retval = 0;

		for( auto iter = iter_begin; iter != iter_end; )
		{
			storage_unit value = *iter;

			if( value >= 0x80 && value <= 0xFF )
			{
				++iter;
			}

			++iter;
			++retval;
		}

		return retval;
	}

	template <typename Container>
	static typename Container::const_iterator insert( Container & str1, typename Container::const_iterator iter, code_point c, size_type count = 1 )
	{
		uint32_t value = c.unicode();

		for( size_type x = 0; x < count; ++x )
		{
			if( value <= 0x7F )
			{
				iter = str1.insert( iter, value );
			}
			else
			{
				iter = str1.insert( iter, value & 0xFF );
				iter = str1.insert( iter, ( value >> 8 ) & 0xFF );
			}
		}

		return iter;
	}

	template< typename storage_iterator >
	static size_type walk( size_type len, storage_iterator iter )
	{
		size_type retval = 0;
		size_type count = 0;

		if( len >= 0 )
		{
			for( size_type x = 0; x < len; ++x )
			{
				storage_unit value = *iter;

				count = num_of_bytes( value );
				iter += count;

				retval += count;
			}
		}
		else
		{
			for( size_type x = 0; x > len; --x )
			{
				uint16_t value = *iter;

				if( value >= 0x80 && value <= 0xFF )
				{
					--iter;
					--retval;
				}

				--iter;
				--retval;
			}
		}

		return retval;
	}

	static code_point get_code_point( const storage_unit * iter );

	static size_type num_of_bytes( storage_unit value );
};

class XE_API wide_encode
{
public:
	using size_type = std::ptrdiff_t;
	using storage_unit = wchar_t;

public:
	template <typename Iterator>
	static Iterator advance( Iterator iter_begin, Iterator iter_end, size_type count )
	{
		auto iter = iter_begin;
		storage_unit value = 0;

		while( iter != iter_end && count != 0 )
		{
			--count;
			++iter;
		}

		return iter;
	}

	template <typename Iterator>
	static size_type distance( Iterator iter_begin, Iterator iter_end )
	{
		return iter_end - iter_begin;
	}

	template <typename Container>
	static typename Container::const_iterator insert( Container & str1, typename Container::const_iterator iter, code_point c, size_type count = 1 )
	{
		uint32_t value = c.unicode();

		for( size_type x = 0; x < count; ++x )
		{
			iter = str1.insert( iter, value );
		}

		return iter;
	}

	template< typename storage_iterator >
	static size_type walk( size_type len, storage_iterator iter )
	{
		iter += len;

		return len;
	}

	static code_point get_code_point( const storage_unit * iter );

	static size_type num_of_bytes( storage_unit value );
};

class XE_API utf8_encode
{
public:
	using size_type = std::ptrdiff_t;
	using storage_unit = char;

public:
	template <typename Iterator>
	static Iterator advance( Iterator iter_begin, Iterator iter_end, size_type count )
	{
		auto iter = iter_begin;
		unsigned char value = 0;

		while( iter != iter_end && count != 0 )
		{
			value = static_cast< unsigned char >( *iter );
			if( value < 0x80 || value > 0xBf )
			{
				--count;
			}

			++iter;
		}

		if( value >= 0xBF )
		{
			while( iter != iter_end && *iter >= 0x80 && *iter <= 0xBF )
			{
				++iter;
			}
		}

		return iter;
	}

	template <typename Iterator>
	static size_type distance( Iterator iter_begin, Iterator iter_end )
	{
		size_type retval = 0;

		for( auto iter = iter_begin; iter != iter_end; ++iter )
		{
			unsigned char value = static_cast< unsigned char >( *iter );

			if( value < 0x80 || value > 0xBF )
			{
				++retval;
			}
		}

		return retval;
	}

	template <typename Container>
	static typename Container::const_iterator insert( Container & str1, typename Container::const_iterator iter, code_point c, size_type count = 1 )
	{
		uint32_t value = c.unicode();

		for( size_type x = 0; x < count; ++x )
		{
			if( value <= 0x007F )
			{
				iter = str1.insert( iter, value );
			}
			else if( value <= 0x07FF )
			{
				iter = str1.insert( iter, ( ( value ) & 0x3F ) | 0x80 );
				iter = str1.insert( iter, ( ( value >> 6 ) & 0x1F ) | 0xC0 );
			}
			else if( value <= 0xFFFF )
			{
				iter = str1.insert( iter, ( ( value ) & 0x3F ) | 0x80 );
				iter = str1.insert( iter, ( ( value >> 6 ) & 0x3F ) | 0x80 );
				iter = str1.insert( iter, ( ( value >> 12 ) & 0x0F ) | 0xE0 );
			}
			else
			{
				iter = str1.insert( iter, ( ( value ) & 0x3F ) | 0x80 );
				iter = str1.insert( iter, ( ( value >> 6 ) & 0x3F ) | 0x80 );
				iter = str1.insert( iter, ( ( value >> 12 ) & 0x3F ) | 0x80 );
				iter = str1.insert( iter, ( ( value >> 18 ) & 0x07 ) | 0xF0 );
			}
		}

		return iter;
	}

	template< typename storage_iterator >
	static size_type walk( size_type len, storage_iterator iter )
	{
		size_type retval = 0;
		size_type count = 0;

		if( len >= 0 )
		{
			for( size_type x = 0; x < len; ++x )
			{
				unsigned char value = static_cast< unsigned char >( *iter );

				count = num_of_bytes( value );
				iter += count;

				retval += count;
			}
		}
		else
		{
			for( size_type x = 0; x > len; --x )
			{
				while( true )
				{
					--iter;
					--retval;

					unsigned char value = static_cast< unsigned char >( *iter );

					if( ( value & 0xC0 ) != 0x80 )
					{
						break;
					}
				}
			}
		}

		return retval;
	}

	static code_point get_code_point( const storage_unit * iter );

	static size_type num_of_bytes( storage_unit value );
};

class XE_API code_point_arrow
{
public:
	code_point_arrow( code_point c );

public:
	const code_point * operator->() const;

private:
	code_point _data;
};

class XE_API code_point_convert
{
public:
	// local multi byte code point to local wide char code point
	static std::wstring ansi_2_wide( const std::string & str );

	// local wide char code point to local multi byte code point
	static std::string wide_2_ansi( const std::wstring & str );

	// local multi byte code point to unicode utf-8
	static std::string ansi_2_utf8( const std::string & str );

	// unicode utf-8 to local multi byte code point
	static std::string utf8_2_ansi( const std::string & str );

	// local wide char code point to unicode utf-8
	static std::string wide_2_utf8( const std::wstring & str );

	// unicode utf-8 code point to local wide char
	static std::wstring utf8_2_wide( const std::string & str );
};

template<> class string_convert< ansi_encode, ansi_encode >
{
public:
	static std::basic_string< typename ansi_encode::storage_unit > convert( const std::basic_string< typename ansi_encode::storage_unit > & str )
	{
		return str;
	}
};

template<> class string_convert< ansi_encode, wide_encode >
{
public:
	static std::basic_string< typename wide_encode::storage_unit > convert( const std::basic_string< typename ansi_encode::storage_unit > & str )
	{
		return code_point_convert::ansi_2_wide( str );
	}
};

template<> class string_convert< ansi_encode, utf8_encode >
{
public:
	static std::basic_string< typename utf8_encode::storage_unit > convert( const std::basic_string< typename ansi_encode::storage_unit > & str )
	{
		return code_point_convert::ansi_2_utf8( str );
	}
};

template<> class string_convert< wide_encode, ansi_encode >
{
public:
	static std::basic_string< typename ansi_encode::storage_unit > convert( const std::basic_string< typename wide_encode::storage_unit > & str )
	{
		return code_point_convert::wide_2_ansi( str );
	}
};

template<> class string_convert< wide_encode, wide_encode >
{
public:
	static std::basic_string< typename wide_encode::storage_unit > convert( const std::basic_string< typename wide_encode::storage_unit > & str )
	{
		return str;
	}
};

template<> class string_convert< wide_encode, utf8_encode >
{
public:
	static std::basic_string< typename utf8_encode::storage_unit > convert( const std::basic_string< typename wide_encode::storage_unit > & str )
	{
		return code_point_convert::wide_2_utf8( str );
	}
};

template<> class string_convert< utf8_encode, ansi_encode >
{
public:
	static std::basic_string< typename ansi_encode::storage_unit > convert( const std::basic_string< typename utf8_encode::storage_unit > & str )
	{
		return code_point_convert::utf8_2_ansi( str );
	}
};

template<> class string_convert< utf8_encode, wide_encode >
{
public:
	static std::basic_string< typename wide_encode::storage_unit > convert( const std::basic_string< typename utf8_encode::storage_unit > & str )
	{
		return code_point_convert::utf8_2_wide( str );
	}
};

template<> class string_convert< utf8_encode, utf8_encode >
{
public:
	static std::basic_string< typename utf8_encode::storage_unit > convert( const std::basic_string< typename utf8_encode::storage_unit > & str )
	{
		return str;
	}
};

template < typename Encode, typename Alloc >
class string_iterator
{
private:
	friend class basic_string<Encode, Alloc>;

	using v_iter = typename std::basic_string< typename Encode::storage_unit, std::char_traits< typename Encode::storage_unit >, Alloc >::const_iterator;

public:
	using difference_type = std::ptrdiff_t;
	using pointer = code_point *;
	using reference = code_point;
	using size_type = std::ptrdiff_t;
	using value_type = code_point;
	using iterator_category = std::random_access_iterator_tag;

public:
	string_iterator() = default;

public:
	code_point operator*() const
	{
		return code_point( *_iter );
	}

	code_point_arrow operator->() const
	{
		return code_point( _iter );
	}

public:
	code_point operator[]( size_type n ) const
	{
		return *( *this + n );
	}

public:
	bool operator!=( const string_iterator & other ) const
	{
		return _iter != other._iter;
	}

	bool operator==( const string_iterator & other ) const
	{
		return _iter == other._iter;
	}

	bool operator<( const string_iterator & other ) const
	{
		return _iter < other._iter;
	}

	bool operator<=( const string_iterator & other ) const
	{
		return _iter <= other._iter;
	}

	bool operator>( const string_iterator & other ) const
	{
		return _iter > other._iter;
	}

	bool operator>=( const string_iterator & other ) const
	{
		return _iter >= other._iter;
	}

public:
	string_iterator & operator+=( size_type n )
	{
		_iter += Encode::walk( n, _iter );
		return *this;
	}

	string_iterator & operator-=( size_type n )
	{
		_iter += Encode::walk( -n, _iter );
		return *this;
	}

	string_iterator operator+( size_type n ) const
	{
		auto iter = _iter + Encode::walk( n, _iter );
		return string_iterator( iter );
	}

	string_iterator & operator++()
	{
		_iter += Encode::walk( 1, _iter );
		return *this;
	}

	string_iterator operator++( int )
	{
		string_iterator retval = *this;
		_iter += Encode::walk( 1, _iter );

		return retval;
	}

	string_iterator operator-( size_type n ) const
	{
		auto iter = _iter + Encode::walk( -n, _iter );
		return string_iterator( iter );
	}

	size_type operator-( string_iterator other ) const
	{
		string_iterator a = *this;
		string_iterator b = other;

		if( a < b )
		{
			return 0 - Encode::distance( a._iter, b._iter );
		}
		else
		{
			return Encode::distance( b._iter, a._iter );
		}
	}

	string_iterator & operator--()
	{
		_iter += Encode::walk( -1, _iter );
		return *this;
	}

	string_iterator operator--( int )
	{
		string_iterator retval = *this;
		_iter += Encode::walk( -1, _iter );

		return retval;
	}

public:
	std::pair<v_iter, v_iter> code_point_range() const
	{
		return { _iter, _iter + Encode::walk( 1, _iter ) };
	}

	v_iter code_point_begin() const
	{
		return _iter;
	}

	v_iter code_point_end() const
	{
		return _iter + Encode::walk( 1, _iter );
	}

private:
	explicit string_iterator( v_iter data )
	{
		_iter = data;
	}

	v_iter _iter;
};

template < typename StringIterator >
class string_reverse_iterator : public std::reverse_iterator<StringIterator>
{
public:
	string_reverse_iterator() = default;

	string_reverse_iterator( StringIterator iter )
		: std::reverse_iterator<StringIterator>( iter )
	{
	}

	template <typename U>
	string_reverse_iterator( string_reverse_iterator<U> iter )
		: std::reverse_iterator<StringIterator>( iter.base() )
	{
	}

public:
	decltype( std::declval<StringIterator>().operator*() )  operator*() const
	{
		auto tmp = this->base();
		return ( --tmp ).operator*();
	}

	decltype( std::declval<StringIterator>().operator->() ) operator->() const
	{
		auto tmp = this->base();
		return ( --tmp ).operator->();
	}
};

template < typename Encode, typename Alloc = std::allocator< typename Encode::storage_unit > >
class basic_string
{
public:
	using encode_type = Encode;
	using allocator_type = Alloc;
	using difference_type = std::ptrdiff_t;
	using size_type = std::ptrdiff_t;
	using value_type = code_point;
	using storage_unit = typename Encode::storage_unit;

	using iterator = string_iterator<Encode, Alloc>;
	using const_iterator = string_iterator<Encode, Alloc>;
	using reverse_iterator = string_reverse_iterator<iterator>;
	using const_reverse_iterator = string_reverse_iterator<const_iterator>;

	using storage_type = std::basic_string< typename Encode::storage_unit, std::char_traits< typename Encode::storage_unit >, Alloc >;
	using storage_iterator = typename std::basic_string< typename Encode::storage_unit, std::char_traits< typename Encode::storage_unit >, Alloc >::iterator;
	using storage_const_iterator = typename std::basic_string< typename Encode::storage_unit, std::char_traits< typename Encode::storage_unit >, Alloc >::const_iterator;
	using storage_reverse_iterator = typename std::basic_string< typename Encode::storage_unit, std::char_traits< typename Encode::storage_unit >, Alloc >::reverse_iterator;
	using storage_const_reverse_iterator = typename std::basic_string< typename Encode::storage_unit, std::char_traits< typename Encode::storage_unit >, Alloc >::const_reverse_iterator;

public:
	static constexpr const size_type npos = -1;

public:
	basic_string()
	{
	}

	basic_string( const Alloc & a )
		: _string( a )
	{
	}

	basic_string( code_point code, const Alloc & a = Alloc() )
		: _string( a )
	{
		Encode::insert( _string, _string.end(), code );
	}

	basic_string( const basic_string & str, const Alloc & a = Alloc() )
		: _string( str._string, a )
	{
	}

	basic_string( basic_string && str, const Alloc & a = Alloc() )
		: _string( std::move( str._string ), a )
	{
	}

	basic_string( const storage_unit * str, const Alloc & a = Alloc() )
		: _string( 1, 0, a )
	{
		if( str == nullptr )
		{
			return;
		}

		const storage_unit * c = str;

		while( *c != 0 )
		{
			
			Encode::insert( _string, _string.end(), Encode::get_code_point( c ) );
			c += Encode::num_of_bytes( *c );
		}
	}

	template <int N>
	basic_string( const storage_unit( &str )[N], const Alloc & a = Alloc() )
		: _string( a )
	{
		const storage_unit * c = str;

		while( *c != 0 )
		{
			 
			Encode::insert( _string, _string.end(), *c );
			++c;
		}
	}

	basic_string( basic_string_view< basic_string > str, const Alloc & a = Alloc() )
		: basic_string( str.begin(), str.end(), a )
	{
	}

	basic_string( const_iterator begin, const_iterator end, const Alloc & a = Alloc() )
		: _string( a )
	{
		for( Iterator item = begin; item != end; ++item )
		{
			Encode::insert( _string, _string.end(), *item );
		}
	}

	basic_string( const std::basic_string< typename Encode::storage_unit > & str, const Alloc & a = Alloc() )
		: _string( str.begin(), str.end(), a )
	{
	}

public:
	basic_string & operator=( code_point c )
	{
		_string.clear();

		append( c );
		return *this;
	}

	basic_string & operator=( basic_string && str ) = default;

	basic_string & operator=( const basic_string & str ) = default;

	basic_string & operator=( const storage_unit * str )
	{
		_string.clear();

		append( str );
		return *this;
	}

	basic_string & operator=( basic_string_view< basic_string > str )
	{
		_string.clear();

		append( str );
		return *this;
	}

	basic_string & operator=( const std::basic_string< typename Encode::storage_unit > & str )
	{
		_string.clear();
		_string.insert(_string.end(), str.begin(), str.end() );

		return *this;
	}

public:
	basic_string & operator+=( code_point c )
	{
		append( c );
		return *this;
	}

	basic_string & operator+=( const basic_string & str )
	{
		append( str );
		return *this;
	}

	basic_string & operator+=( const storage_unit * str )
	{
		append( str );
		return *this;;
	}

	basic_string & operator+=( basic_string_view< basic_string > str )
	{
		append( str );
		return *this;
	}

	basic_string & operator+=( const std::basic_string< typename Encode::storage_unit > & str )
	{
		append( str );
		return *this;
	}

public:
	Alloc get_allocator() const
	{
		return _string.get_allocator();
	}

public:
	code_point operator[]( size_type index ) const
	{
		const_iterator iter = begin();
		std::advance( iter, index );

		return *iter;
	}

	code_point at( size_type index ) const
	{
		const_iterator iter = begin();
		std::advance( iter, index );

		return *iter;
	}

public:
	iterator advance( iterator begin, size_type count )
	{
		return iterator( Encode::advance( begin.code_point_begin(), end().code_point_begin(), count ) );
	}

	const_iterator advance( const_iterator begin, size_type count ) const
	{
		return const_iterator( Encode::advance( begin.code_point_begin(), end().code_point_begin(), count ) );
	}

public:
	basic_string & append( code_point c )
	{
		Encode::insert( _string, _string.end(), c );
		return *this;
	}

	basic_string & append( size_type size, code_point c )
	{
		Encode::insert( _string, _string.end(), c, size );
		return *this;
	}

	basic_string & append( const basic_string & str )
	{
		insert( end(), str );
		return *this;
	}

	basic_string & append( const_iterator begin, const_iterator end )
	{
		for( const_iterator item = begin; item != end; ++item )
		{
			Encode::insert( _string, _string.end(), *item );
		}

		return *this;
	}

	basic_string & append( const storage_unit * str )
	{
		if( str == nullptr )
		{
			return *this;
		}

		this->append( str, std::strlen( str ) );

		return *this;
	}

	template <int N>
	basic_string & append( const storage_unit * ( &str )[N] )
	{
		this->append( str, N - 1 );

		return *this;
	}

	basic_string & append( basic_string_view< basic_string > str )
	{
		append( str.begin(), str.end() );
		return *this;
	}

	basic_string & append( const std::basic_string< typename Encode::storage_unit > & str )
	{
		_string.insert( _string.end(), str.begin(), str.end() );

		return *this;
	}

public:
	basic_string & assign( size_type count, code_point c )
	{
		clear();
		append( count, c );

		return *this;
	}

	basic_string & assign( basic_string && str )
	{
		clear();
		append( std::move( str ) );

		return *this;
	}

	basic_string & assign( const basic_string & str )
	{
		clear();
		append( str );

		return *this;
	}

	basic_string & assign( const storage_unit * str )
	{
		clear();
		append( str, std::strlen( str ) );

		return *this;
	}

	template <int N>
	basic_string & assign( const storage_unit * ( &str )[N] )
	{
		clear();
		append( str, N );

		return *this;
	}

	basic_string & assign( const_iterator begin, const_iterator end )
	{
		clear();
		append( begin, end );

		return *this;
	}

	basic_string & assign( basic_string_view< basic_string > str )
	{
		clear();
		append( str.begin(), str.end() );

		return *this;
	}

	basic_string & assign( const std::basic_string< typename Encode::storage_unit > & str )
	{
		clear();
		append( str );

		return *this;
	}

public:
	void clear()
	{
		_string.clear();
		_string.push_back( 0 );
	}

	bool empty() const
	{
		return _string.empty();
	}

	int strcmp( const basic_string & str ) const
	{
		if( str.size() == size() )
		{
			auto it1 = begin();
			auto it2 = str.begin();
			auto it1end = end();
			auto it2end = str.end();

			for( ; it1 != it1end && it2 != it2end; ++it1, ++it2 )
			{
				if( *it1 < *it2 )
				{
					return -1;
				}
				else if( *it1 > *it2 )
				{
					return 1;
				}
			}

			return 0;
		}

		return size() > str.size() ? 1 : -1;
	}

public:
	iterator erase( const_iterator iter_begin, const_iterator iter_end )
	{
		auto retval = _string.erase( iter_begin.code_point_begin(), iter_end.code_point_begin() );
		return const_iterator( retval );
	}

	basic_string & erase( size_type indexStart = 0, size_type size = npos )
	{
		const_iterator iter_begin = begin() + indexStart;
		const_iterator iter_end;

		if( iter_begin == end() )
		{
			return *this;
		}

		if( size >= 0 )
		{
			iter_end = iter_begin;

			for( size_type i = 0; i < size && iter_end != end(); ++i )
			{
				++iter_end;
			}
		}
		else
		{
			iter_end = end();
		}

		erase( iter_begin, iter_end );

		return *this;
	}

public:
	const_iterator find_fast( const basic_string & str ) const
	{
		return find_fast( str, begin() );
	}

	const_iterator find_fast( const basic_string & str, const_iterator iter_begin ) const
	{
		const_iterator iter_end = end();

		if( iter_begin == iter_end )
		{
			return iter_end;
		}

		if( str.empty() )
		{
			return iter_begin;
		}

		auto iter = iter_begin;
		auto ch = str[0];

		while( iter != iter_end )
		{
			if( *iter == ch )
			{
				auto text_iter = iter + 1;
				auto pattern_iter = str.begin() + 1;

				while( text_iter != iter_end && pattern_iter != str.end() )
				{

					if( *text_iter == *pattern_iter )
					{
						++text_iter;
						++pattern_iter;
					}
					else
					{
						break;
					}
				}

				if( pattern_iter == str.end() )
				{
					return iter;
				}
			}

			++iter;
		}

		return iter_end;
	}

public:
	const_iterator rfind_fast( const basic_string & str ) const
	{
		return rfind_fast( str, end() );
	}

	const_iterator rfind_fast( const basic_string & str, const_iterator iter_end ) const
	{
		const_iterator iter_begin = begin();

		if( iter_begin == iter_end )
		{
			return end();
		}

		if( str.empty() )
		{
			return iter_end;
		}

		auto iter = iter_end;
		auto str_end = str.end();
		auto ch = str[0];

		while( iter != begin() )
		{
			--iter;

			if( *iter == ch )
			{
				auto text_iter = iter + 1;
				auto pattern_iter = str.begin() + 1;

				while( text_iter != end() && pattern_iter != str_end )
				{
					if( *text_iter == *pattern_iter )
					{
						++text_iter;
						++pattern_iter;
					}
					else
					{
						break;
					}
				}

				if( pattern_iter == str_end )
				{
					return iter;
				}
			}

		}

		return end();
	}

public:
	size_type find( code_point c, size_type indexStart = 0 ) const
	{
		const_iterator iter_begin = begin();

		for( size_type i = 0; i < indexStart && iter_begin != end(); ++i )
		{
			++iter_begin;
		}

		if( iter_begin == end() )
		{
			return -1;
		}

		size_type retval = indexStart;

		while( iter_begin != end() )
		{
			if( *iter_begin == c )
			{
				return retval;
			}

			++iter_begin;
			++retval;
		}

		return -1;
	}

	size_type find( const basic_string & str, size_type indexStart = 0 ) const
	{
		size_type stringLen = this->size();

		if( str.empty() )
		{
			if( indexStart > stringLen )
			{
				return -1;
			}
			else
			{
				return indexStart;
			}
		}

		if( indexStart >= stringLen )
		{
			return -1;
		}

		size_type retval = indexStart;
		auto iter = begin() + indexStart;
		auto ch = str[0];

		while( iter != end() )
		{
			if( *iter == ch )
			{
				auto text_iter = iter + 1;
				auto pattern_iter = str.begin() + 1;

				while( text_iter != end() && pattern_iter != str.end() )
				{
					if( *text_iter == *pattern_iter )
					{
						++text_iter;
						++pattern_iter;
					}
					else
					{
						break;
					}
				}

				if( pattern_iter == str.end() )
				{
					return retval;
				}
			}

			++iter;
			++retval;
		}

		return -1;
	}

public:
	size_type rfind( code_point c, size_type indexStart = npos ) const
	{
		size_type stringLen = this->size();

		size_type retval;
		const_iterator iter;

		if( indexStart >= 0 && indexStart < stringLen )
		{
			retval = indexStart + 1;
			iter = begin() + indexStart + 1;
		}
		else
		{
			retval = stringLen;
			iter = end();
		}

		while( iter != begin() )
		{
			--iter;
			--retval;

			if( *iter == c )
			{
				return retval;
			}
		}

		return -1;
	}

	size_type rfind( const basic_string & str, size_type indexStart = npos ) const
	{
		size_type stringLen = this->size();

		if( str.empty() )
		{
			if( indexStart > stringLen || indexStart == -1 )
			{
				return stringLen;
			}
			else
			{
				return indexStart;
			}
		}

		size_type retval;
		const_iterator iter;

		if( indexStart >= 0 && indexStart < stringLen )
		{
			retval = indexStart + 1;
			iter = begin() + indexStart + 1;
		}
		else
		{
			retval = stringLen;
			iter = end();
		}

		const_iterator str_end = str.end();
		auto ch = str[0];

		while( iter != begin() )
		{
			--iter;
			--retval;

			if( *iter == ch )
			{
				auto text_iter = iter + 1;
				auto pattern_iter = str.begin() + 1;

				while( text_iter != end() && pattern_iter != str_end )
				{
					if( *text_iter == *pattern_iter )
					{
						++text_iter;
						++pattern_iter;
					}
					else
					{
						break;
					}
				}

				if( pattern_iter == str_end )
				{
					return retval;
				}
			}

		}

		return -1;
	}

public:
	size_type find_first_of( code_point c, size_type indexStart = 0 ) const
	{
		return find( c, indexStart );
	}

	size_type find_first_of( const basic_string & str, size_type indexStart = 0 ) const
	{
		if( str.empty() || indexStart >= this->size() )
		{
			return -1;
		}

		size_type retval = indexStart;
		auto iter = begin() + indexStart;

		while( iter != end() )
		{
			for( auto c : str )
			{
				if( *iter == c )
				{
					return retval;
				}
			}

			++iter;
			++retval;
		}

		return -1;
	}

public:
	size_type find_last_of( code_point c, size_type indexStart = npos ) const
	{
		return rfind( c, indexStart );
	}

	size_type find_last_of( const basic_string & str, size_type indexStart = npos ) const
	{
		size_type stringLen = this->size();

		if( str.empty() || indexStart >= stringLen )
		{
			return -1;
		}

		size_type retval;
		const_iterator iter;

		if( indexStart >= 0 && indexStart < stringLen )
		{
			retval = indexStart + 1;
			iter = begin() + indexStart + 1;
		}
		else
		{
			retval = stringLen;
			iter = end();
		}

		while( iter != begin() )
		{
			--iter;
			--retval;

			for( code_point c : str )
			{
				if( *iter == c )
				{
					return retval;
				}
			}
		}

		return -1;
	}

public:
	size_type find_first_not_of( code_point c, size_type indexStart = 0 ) const
	{
		if( indexStart >= this->size() )
		{
			return -1;
		}

		size_type retval = indexStart;
		auto iter = begin() + indexStart;

		while( iter != end() )
		{
			if( *iter != c )
			{
				return retval;
			}

			++iter;
			++retval;
		}

		return -1;
	}

	size_type find_first_not_of( const basic_string & str, size_type indexStart = 0 ) const
	{
		size_type stringLen = this->size();

		if( str.empty() )
		{
			if( indexStart >= stringLen )
			{
				return -1;
			}
			else
			{
				return indexStart;
			}
		}

		if( indexStart >= stringLen )
		{
			return -1;
		}

		size_type retval = indexStart;
		auto iter = begin() + indexStart;

		auto str_end = str.end();

		while( iter != end() )
		{
			const_iterator pattern_iter = str.begin();

			while( pattern_iter != str_end )
			{
				if( *iter == *pattern_iter )
				{
					break;
				}

				++pattern_iter;
			}

			if( pattern_iter == str_end )
			{
				return retval;
			}

			++iter;
			++retval;
		}

		return -1;
	}

public:
	size_type find_last_not_of( code_point c, size_type indexStart = npos ) const
	{
		size_type stringLen = this->size();

		if( indexStart >= stringLen )
		{
			return -1;
		}

		size_type retval;
		const_iterator iter;

		if( indexStart >= 0 && indexStart < stringLen )
		{
			retval = indexStart + 1;
			iter = begin() + indexStart + 1;
		}
		else
		{
			retval = stringLen;
			iter = end();
		}

		while( iter != begin() )
		{
			--iter;
			--retval;

			if( *iter != c )
			{
				return retval;
			}
		}

		return -1;
	}

	size_type find_last_not_of( const basic_string & str, size_type indexStart = npos ) const
	{
		size_type stringLen = this->size();

		if( str.empty() )
		{
			if( indexStart > stringLen || indexStart == -1 )
			{
				return stringLen - 1;
			}
			else
			{
				return indexStart;
			}
		}

		size_type retval;
		const_iterator iter;

		if( indexStart >= 0 && indexStart < stringLen )
		{
			retval = indexStart + 1;
			iter = begin() + indexStart + 1;
		}
		else
		{
			retval = stringLen;
			iter = end();
		}

		const_iterator str_end = str.end();

		while( iter != begin() )
		{
			--iter;
			--retval;

			const_iterator pattern_iter = str.begin();

			while( pattern_iter != str_end )
			{
				if( *iter == *pattern_iter )
				{
					break;
				}

				++pattern_iter;
			}

			if( pattern_iter == str_end )
			{
				return retval;
			}
		}

		return -1;
	}

public:
	code_point front() const
	{
		return *begin();
	}

	code_point back() const
	{
		return *( --end() );
	}

public:
	void pop_back()
	{
		if( empty() )
		{
			return;
		}

		const_iterator iter = --end();
		erase( iter );
	}

	void push_back( code_point c )
	{
		append( c );
	}

public:
	basic_string & insert( size_type indexStart, code_point c )
	{
		const_iterator iter_begin = begin() + indexStart;

		Encode::insert( _string, iter_begin.code_point_begin(), c );

		return *this;
	}

	basic_string & insert( size_type indexStart, const basic_string & str )
	{
		const_iterator iter_begin = begin() + indexStart;
		
		for( code_point c : str )
		{
			storage_const_iterator iter_tmp = Encode::insert( _string, iter_begin.code_point_begin(), c );

			iter_begin = const_iterator( iter_tmp );
		}

		return *this;
	}

	iterator insert( const_iterator posStart, code_point c )
	{
		storage_const_iterator iter_tmp = Encode::insert( _string, posStart.code_point_begin(), c );
		return string_iterator<Encode, Alloc>( iter_tmp );
	}

	iterator insert( const_iterator posStart, const basic_string & str )
	{
		const_iterator iter = posStart;

		for( auto c : str )
		{
			storage_const_iterator iter_tmp = Encode::insert( _string, iter.code_point_begin(), c );

			iter = const_iterator( iter_tmp );
		}

		return ( iter );
	}

	iterator insert( const_iterator posStart, const_iterator begin, const_iterator end )
	{
		const_iterator iter = posStart;

		for( auto item = begin; item != end; item++ )
		{
			code_point c = Encode::get_code_point( &(  ) );

			storage_const_iterator iter_tmp = Encode::insert( _string, iter.code_point_begin(), *item );

			iter = const_iterator( iter_tmp );
		}

		return ( iter );
	}

public:
	basic_string & replace( size_type indexStart, size_type size, const basic_string & str )
	{
		const_iterator iter_begin = begin() + indexStart;
		const_iterator iter_end;

		if( size >= 0 )
		{
			iter_end = iter_begin;

			for( size_type j = 0; j < size && iter_end != end(); ++j )
			{
				++iter_end;
			}
		}
		else
		{
			iter_end = end();
		}

		auto iter = erase( iter_begin, iter_end );
		insert( iter, str );

		return *this;
	}

	basic_string & replace( size_type indexStart, size_type size, const storage_unit * str )
	{
		auto iter = erase( begin() + indexStart, begin() + indexStart + size );
		insert( iter, str );

		return *this;
	}

	template <int N>
	basic_string & replace( size_type indexStart, size_type size, const storage_unit( &str )[N] )
	{
		auto iter = erase( begin() + indexStart, begin() + indexStart + size );
		insert( iter, str );

		return *this;
	}

	basic_string & replace( size_type indexStart, size_type size, size_type count, code_point c )
	{
		const_iterator iter_begin = begin() + indexStart;
		const_iterator iter_end;

		if( size >= 0 )
		{
			iter_end = iter_begin;

			for( size_type j = 0; j < size && iter_end != end(); ++j )
			{
				++iter_end;
			}
		}
		else
		{
			iter_end = end();
		}

		auto iter = erase( iter_begin, iter_end );
		insert( iter, count, c );

		return *this;
	}

	basic_string & replace( const_iterator first, const_iterator last, const basic_string & str )
	{
		auto iter = erase( first, last );
		insert( iter, str );

		return *this;
	}

	basic_string & replace( const_iterator first, const_iterator last, const storage_unit * str )
	{
		auto iter = erase( first, last );
		insert( iter, str );

		return *this;
	}

	template <int N>
	basic_string & replace( const_iterator first, const_iterator last, const storage_unit( &str )[N] )
	{
		auto iter = erase( first, last );
		insert( iter, str );

		return *this;
	}

	basic_string & replace( const_iterator first, const_iterator last, size_type count, code_point c )
	{
		auto iter = erase( first, last );
		insert( iter, count, c );

		return *this;
	}

	basic_string & replace( const_iterator first1, const_iterator last1, const_iterator first2, const_iterator last2 )
	{
		auto iter = erase( first1, last1 );
		insert( iter, first2, last2 );

		return *this;
	}

public:
	void resize( size_type size )
	{
		if( size < 0 )
		{
			size = 0;
		}

		size_type stringLen = this->size();
		size_type count = size - stringLen;

		code_point c;

		if( count > 0 )
		{
			append( count, c );
		}
		else if( count < 0 )
		{
			auto end = this->end();
			auto begin = end + count;

			erase( begin, end );
		}
	}

	void resize( size_type size, code_point c )
	{
		if( size < 0 )
		{
			size = 0;
		}

		size_type stringLen = this->size();
		size_type count = size - stringLen;

		if( count > 0 )
		{
			append( count, c );
		}
		else if( count < 0 )
		{
			erase( size, -count );
		}
	}

	void reserve( size_type size )
	{
		code_point c;
		append( size, c );
	}

public:
	void shrink_to_fit()
	{
		_string.shrink_to_fit();
	}

public:
	size_type size() const
	{
		return _string.size();
	}

	size_type length() const
	{
		return Encode::distance( _string.begin(), _string.end() );
	}

public:
	basic_string substr( size_type indexStart = 0, size_type size = npos ) const
	{
		const_iterator iter_begin = begin();
		const_iterator iter_end;

		for( size_type i = 0; i < indexStart && iter_begin != end(); ++i )
		{
			++iter_begin;
		}

		if( iter_begin == end() )
		{
			return basic_string();
		}

		if( size >= 0 )
		{
			iter_end = iter_begin;

			for( size_type i = 0; i < size && iter_end != end(); ++i )
			{
				++iter_end;
			}
		}
		else
		{
			iter_end = end();
		}

		return basic_string( iter_begin, iter_end );
	}

public:
	void swap( basic_string & str )
	{
		_string.swap( str._string );
	}

public:
	const_iterator begin() const
	{
		return string_iterator<Encode, Alloc>( _string.begin() );
	}

	const_iterator end() const
	{

		return string_iterator<Encode, Alloc>( _string.end() );
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator( end() );
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator( begin() );
	}

	storage_const_iterator storage_begin() const
	{
		return _string.begin();
	}

	storage_const_iterator storage_end() const
	{
		return _string.end();
	}

	storage_const_reverse_iterator storage_rbegin() const
	{
		return _string.crbegin() + 1;
	}

	storage_const_reverse_iterator storage_rend() const
	{
		return _string.crend();
	}

public:
	typename Encode::storage_unit * data()
	{
		return _string.data();
	}

	const typename Encode::storage_unit * c_str() const
	{
		return _string.c_str();
	}

	std::basic_string< typename Encode::storage_unit > std_str() const
	{
		return { _string.begin(), _string.end() };
	}

	std::vector< basic_string > split( const basic_string & sep ) const
	{
		using string_type = std::basic_string< typename Encode::storage_unit >;

		std::basic_regex< typename Encode::storage_unit > re{ sep.c_str() };

		return { std::regex_token_iterator< typename string_type::const_pointer >( _string.data(),_string.data() + _string.size(), re, -1 ), std::regex_token_iterator< typename string_type::const_pointer >() };
	}

public:
	basic_string & replace( const basic_string & sep, const basic_string & str )
	{
		std::basic_regex< typename Encode::storage_unit > re{ sep.c_str() };

		( *this ) = std::regex_replace( c_str(), re, str.c_str() );

		return *this;
	}

public:
	operator const typename Encode::storage_unit * ( ) const
	{
		return c_str();
	}

	operator const storage_type & () const
	{
		return std_str();
	}

private:
	storage_type _string;
};

template < typename String >
class basic_string_view
{
public:
	using difference_type = typename String::difference_type;
	using size_type = typename String::difference_type;
	using value_type = typename String::value_type;

	using const_iterator = typename String::const_iterator;
	using iterator = typename String::const_iterator;
	using const_reverse_iterator = typename String::const_reverse_iterator;
	using reverse_iterator = typename String::const_reverse_iterator;

public:
	static constexpr const size_type npos = -1;

private:
	basic_string_view( String && str ) = delete;

public:
	basic_string_view() = default;

	basic_string_view( const basic_string_view & str ) = default;

	basic_string_view( basic_string_view && str ) = default;

	basic_string_view( const String & str )
		: _begin( str.begin() ), _end( str.end() )
	{
	}

	basic_string_view( const_iterator begin, const_iterator end )
		: _begin( begin ), _end( end )
	{
	}

public:
	basic_string_view<String> & operator=( const basic_string_view & str ) = default;

	basic_string_view<String> & operator=( basic_string_view && str ) = default;

public:
	value_type operator[]( size_type index ) const
	{
		const_iterator iter = begin();
		std::advance( iter, index );

		return *iter;
	}

	value_type at( size_type index ) const
	{
		const_iterator iter = begin();
		std::advance( iter, index );

		return *iter;
	}

public:
	int compare( basic_string_view str ) const
	{
		auto iter_a = begin();
		auto iter_b = str.begin();

		while( iter_a != end() && iter_b != str.end() )
		{
			auto value_a = *iter_a;
			auto value_b = *iter_b;

			if( value_a < value_b )
			{
				return -1;
			}
			else if( value_a > value_b )
			{
				return 1;
			}

			++iter_a;
			++iter_b;
		}

		if( iter_b != str.end() )
		{
			return -1;
		}
		else if( iter_a != end() )
		{
			return 1;
		}

		return 0;
	}

public:
	bool empty() const
	{
		return ( _begin == _end );
	}

public:
	const_iterator find_fast( value_type c ) const
	{
		return find_fast( c, begin() );
	}

	const_iterator find_fast( value_type c, const_iterator iter_begin ) const
	{
		const_iterator iter_end = end();

		if( iter_begin == iter_end )
		{
			return iter_end;
		}

		auto iter = iter_begin;

		while( iter != iter_end )
		{
			if( *iter == c )
			{
				return iter;
			}

			++iter;
		}

		return iter_end;
	}

	const_iterator find_fast( basic_string_view str ) const
	{
		return find_fast( str, begin() );
	}

	const_iterator find_fast( basic_string_view str, const_iterator iter_begin ) const
	{
		const_iterator iter_end = end();

		if( iter_begin == iter_end )
		{
			return iter_end;
		}

		if( str.empty() )
		{
			return iter_begin;
		}

		auto iter = iter_begin;

		while( iter != iter_end )
		{
			if( *iter == str[0] )
			{
				auto text_iter = iter + 1;
				auto pattern_iter = str.begin() + 1;

				while( text_iter != iter_end && pattern_iter != str.end() )
				{
					if( *text_iter == *pattern_iter )
					{
						++text_iter;
						++pattern_iter;
					}
					else
					{
						break;
					}
				}

				if( pattern_iter == str.end() )
				{
					return iter;
				}
			}

			++iter;
		}

		return iter_end;
	}

	template <typename T, typename = typename std::enable_if<std::is_same<T, const char *>::value || std::is_same<T, char *>::value>::type>
	const_iterator find_fast( const T & str, const_iterator iter_begin, size_type size ) const
	{
		const_iterator iter_end = end();

		if( iter_begin == iter_end )
		{
			return iter_end;
		}

		if( str == nullptr || str[0] == 0 )
		{
			return iter_begin;
		}

		auto iter = iter_begin;

		while( iter != iter_end )
		{
			if( *iter == str[0] )
			{
				auto text_iter = iter + 1;
				auto pattern_iter = str + 1;

				int count = 0;

				while( text_iter != iter_end && *pattern_iter != 0 && count < size )
				{
					if( *text_iter == *pattern_iter )
					{
						++text_iter;
						++pattern_iter;

						++count;
					}
					else
					{
						break;
					}
				}

				if( *pattern_iter == 0 )
				{
					return iter;
				}
			}

			++iter;
		}

		return iter_end;
	}

	template <int N>
	const_iterator find_fast( const char( &str )[N], const_iterator iter_begin, size_type size ) const
	{
		return find_fast( String::fromUtf8( str, size ), iter_begin );
	}

	template <typename T, typename = typename std::enable_if<std::is_same<T, const char *>::value || std::is_same<T, char *>::value>::type>
	const_iterator find_fast( const T & str ) const
	{
		return find_fast( str, begin() );
	}

	template <typename T, typename = typename std::enable_if<std::is_same<T, const char *>::value || std::is_same<T, char *>::value>::type>
	const_iterator find_fast( const T & str, const_iterator iter_begin ) const
	{
		const_iterator iter_end = end();

		if( iter_begin == iter_end )
		{
			return iter_end;
		}

		if( str == nullptr || str[0] == 0 )
		{
			return iter_begin;
		}

		auto iter = iter_begin;

		while( iter != iter_end )
		{
			if( *iter == str[0] )
			{
				auto text_iter = iter + 1;
				auto pattern_iter = str + 1;

				while( text_iter != iter_end && *pattern_iter != 0 )
				{
					if( *text_iter == *pattern_iter )
					{
						++text_iter;
						++pattern_iter;
					}
					else
					{
						break;
					}
				}

				if( *pattern_iter == 0 )
				{
					return iter;
				}
			}

			++iter;
		}

		return iter_end;
	}

	template <int N>
	const_iterator find_fast( const char( &str )[N] ) const
	{
		return find_fast( str, begin() );
	}

	template <int N>
	const_iterator find_fast( const char( &str )[N], const_iterator iter_begin ) const
	{
		return find_fast( String::fromUtf8( str, N - 1 ), iter_begin );
	}

public:
	const_iterator rfind_fast( value_type c ) const
	{
		return rfind_fast( c, end() );
	}

	const_iterator rfind_fast( value_type c, const_iterator iter_end ) const
	{
		const_iterator iter_begin = begin();

		if( iter_begin == iter_end )
		{
			return end();
		}

		auto iter = iter_end;

		while( iter != begin() )
		{
			--iter;

			if( *iter == c )
			{
				return iter;
			}
		}

		return end();
	}

	const_iterator rfind_fast( basic_string_view str ) const
	{
		return rfind_fast( str, end() );
	}

	const_iterator rfind_fast( basic_string_view str, const_iterator iter_end ) const
	{
		const_iterator iter_begin = begin();

		if( iter_begin == iter_end )
		{
			return end();
		}

		if( str.empty() )
		{
			return iter_end;
		}

		auto iter = iter_end;
		auto str_end = str.end();

		while( iter != begin() )
		{
			--iter;

			if( *iter == str[0] )
			{
				auto text_iter = iter + 1;
				auto pattern_iter = str.begin() + 1;

				while( text_iter != end() && pattern_iter != str_end )
				{
					if( *text_iter == *pattern_iter )
					{
						++text_iter;
						++pattern_iter;
					}
					else
					{
						break;
					}
				}

				if( pattern_iter == str_end )
				{
					return iter;
				}
			}
		}

		return end();
	}

public:
	value_type front() const
	{
		return *begin();
	}

	value_type back() const
	{
		return *( --end() );
	}

public:
	size_type length()  const
	{
		return size();
	}

	size_type size() const
	{
		size_type retval = 0;

		for( auto item = begin(); item != end(); ++item )
		{
			++retval;
		}

		return retval;
	}

public:
	bool starts_with( basic_string_view str ) const
	{
		if( str.empty() )
		{
			return true;
		}
		else if( empty() )
		{
			return false;
		}

		auto iter = begin();

		for( auto uc : str )
		{
			if( iter == end() )
			{
				return false;
			}

			if( *iter != uc )
			{
				return false;
			}

			++iter;
		}

		return true;
	}

	bool ends_with( basic_string_view str ) const
	{
		if( str.empty() )
		{
			return true;
		}
		else if( empty() )
		{
			return false;
		}

		auto iter = crbegin();

		for( auto iter_other = str.crbegin(); iter_other != str.crend(); ++iter_other )
		{
			if( iter == crend() )
			{
				return false;
			}

			if( *iter != *iter_other )
			{
				return false;
			}

			++iter;
		}

		return true;
	}

public:
	basic_string_view<String> remove_prefix( size_type size ) const
	{
		const_iterator iter_begin = begin();

		for( size_type i = 0; i < size && iter_begin != end(); ++i )
		{
			++iter_begin;
		}

		if( iter_begin == end() )
		{
			return basic_string_view();
		}

		return basic_string_view( iter_begin, end() );
	}

	basic_string_view<String> remove_suffix( size_type size ) const
	{
		const_iterator iter_end = end();

		for( size_type i = 0; i < size && iter_end != begin(); ++i )
		{
			--iter_end;
		}

		return basic_string_view( begin(), iter_end );
	}

public:
	basic_string_view<String> substr( size_type indexStart = 0, size_type size = npos ) const
	{
		const_iterator iter_begin = begin();
		const_iterator iter_end;

		for( size_type i = 0; i < indexStart && iter_begin != end(); ++i )
		{
			++iter_begin;
		}

		if( iter_begin == end() )
		{
			return basic_string_view();
		}

		if( size >= 0 )
		{
			iter_end = iter_begin;

			for( size_type i = 0; i < size && iter_end != end(); ++i )
			{
				++iter_end;
			}
		}
		else
		{
			iter_end = end();
		}

		return basic_string_view( iter_begin, iter_end );
	}

public:
	void swap( basic_string_view & str )
	{
		swap( _begin, str._begin );
		swap( _end, str._end );
	}

public:
	iterator begin()
	{
		return _begin;
	}

	const_iterator begin() const
	{
		return _begin;
	}

	iterator end()
	{
		return _end;
	}

	const_iterator end() const
	{
		return _end;
	}

	reverse_iterator rbegin()
	{
		return _end;
	}

	const_reverse_iterator rbegin() const
	{
		return _end;
	}

	reverse_iterator rend()
	{
		return _begin;
	}

	const_reverse_iterator rend() const
	{
		return _begin;
	}

	const_reverse_iterator crbegin() const
	{
		return _end;
	}

	const_reverse_iterator crend() const
	{
		return _begin;
	}

public:
	std::basic_string< typename String::encode_type::storage_unit > std_str() const
	{
		return { _begin.code_point_begin(), _end.code_point_begin() };
	}

	operator std::basic_string< typename String::encode_type::storage_unit >() const
	{
		return std_str();
	}

private:
	const_iterator _begin;
	const_iterator _end;
};


XE_INLINE std::string ToString( bool _Val )
{
	return _Val ? "true" : "false";
}

XE_INLINE std::string ToString( char _Val )
{
	return { 1, _Val };
}

XE_INLINE std::string ToString( uint8 _Val )
{
	return std::to_string( ( int32 )_Val );
}

XE_INLINE std::string ToString( int16 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( uint16 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( int32 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( uint32 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( int64 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( uint64 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( float32 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( float64 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( char * _Val )
{
	return _Val;
}

XE_INLINE std::string ToString( const char * _Val )
{
	return _Val;
}

XE_INLINE std::string ToString( const std::string & _Val )
{
	return _Val;
}

XE_INLINE std::string ToString( const std::filesystem::path & _Val )
{
	return _Val.u8string();
}

XE_INLINE std::string ToString( const std::chrono::system_clock::time_point & _Val )
{
	std::tm _tm;
	std::ostringstream _oss;
	const time_t _tt = std::chrono::system_clock::to_time_t( _Val );

#if PLATFORM_OS == OS_WINDOWS
	localtime_s( &_tm, &_tt );
#else
	localtime_r( &_tt, &_tm );
#endif

	_oss << std::put_time( &_tm, "%Y-%m-%d %X" );

	return _oss.str();
}

template <typename Encode, typename Alloc> XE_INLINE std::basic_string< typename Encode::storage_unit > ToString( const XE::basic_string< Encode, Alloc > & _Val )
{
	return _Val.std_str();
}


XE_INLINE bool FromString( const std::string & _Str, bool & _Val )
{
	if( _Str == "true" || _Str == "false" )
	{
		_Val = _Str == "true";
		return true;
	}

	return false;
}

XE_INLINE bool FromString( const std::string & _Str, XE::int8 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::int16 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::int32 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::int64 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::uint8 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::uint16 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::uint32 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::uint64 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::float32 & _Val )
{
	size_t size = 0;

	_Val = std::stof( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::float64 & _Val )
{
	size_t size = 0;

	_Val = std::stod( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, std::string & _Val )
{
	_Val = _Str;

	return true;
}

XE_INLINE bool FromString( const std::string & _Str, std::filesystem::path & _Val )
{
	_Val = _Str;

	return true;
}

XE_INLINE bool FromString( const std::string & _Str, std::chrono::system_clock::time_point & _Val )
{
	if( _Str.size() == 18 )
	{
		std::tm _tm;

		_tm.tm_year = std::stoi( _Str.substr( 0, 4 ) ) - 1900;
		_tm.tm_mon = std::stoi( _Str.substr( 5, 2 ) ) - 1;
		_tm.tm_mday = std::stoi( _Str.substr( 8, 2 ) );
		_tm.tm_hour = std::stoi( _Str.substr( 11, 2 ) );
		_tm.tm_min = std::stoi( _Str.substr( 14, 2 ) );
		_tm.tm_sec = std::stoi( _Str.substr( 17, 2 ) );

		_Val = std::chrono::system_clock::from_time_t( std::mktime( &_tm ) );

		return true;
	}

	return false;
}

template <typename Encode, typename Alloc>XE_INLINE bool FromString( const std::basic_string< typename Encode::storage_unit > & _Str, XE::basic_string< Encode, Alloc > & _Val )
{
	_Val.assign( _Str );

	return true;
}

END_XE_NAMESPACE

template <typename Encode, typename Alloc>
XE_INLINE bool operator==( const XE::basic_string<Encode, Alloc> & str1, const XE::basic_string<Encode, Alloc> & str2 )
{
	return str1.strcmp( str2 ) == 0;
}

template <typename Encode, typename Alloc>
XE_INLINE bool operator!=( const XE::basic_string<Encode, Alloc> & str1, const XE::basic_string<Encode, Alloc> & str2 )
{
	return !( str1 == str2 );
}

template <typename Encode, typename Alloc>
XE_INLINE bool operator<( const XE::basic_string<Encode, Alloc> & str1, const XE::basic_string<Encode, Alloc> & str2 )
{
	return str1.strcmp( str2 ) < 0;
}

template <typename Encode, typename Alloc>
XE_INLINE bool operator<=( const XE::basic_string<Encode, Alloc> & str1, const XE::basic_string<Encode, Alloc> & str2 )
{
	int cmp = str1.strcmp( str2 );
	return cmp <= 0;
}

template <typename Encode, typename Alloc>
XE_INLINE bool operator>( const XE::basic_string<Encode, Alloc> & str1, const XE::basic_string<Encode, Alloc> & str2 )
{
	return str1.strcmp( str2 ) > 0;
}

template <typename Encode, typename Alloc>
XE_INLINE bool operator>=( const XE::basic_string<Encode, Alloc> & str1, const XE::basic_string<Encode, Alloc> & str2 )
{
	int cmp = str1.strcmp( str2 );
	return cmp >= 0;
}

template <typename Encode, typename Alloc>
XE_INLINE XE::basic_string<Encode, Alloc> operator+( const XE::basic_string<Encode, Alloc> & str1, const XE::basic_string<Encode, Alloc> & str2 )
{
	XE::basic_string<Encode, Alloc> retval = str1;
	retval.append( str2 );

	return retval;
}

template <typename Encode, typename Alloc>
XE_INLINE XE::basic_string<Encode, Alloc> operator+( const XE::basic_string<Encode, Alloc> & str1, const std::basic_string<typename Encode::storage_unit> & str2 )
{
	XE::basic_string<Encode, Alloc> retval = str1;
	retval.append( str2 );

	return retval;
}

template <typename Encode, typename Alloc>
XE_INLINE XE::basic_string<Encode, Alloc> operator+( const std::basic_string<typename Encode::storage_unit> & str1, const XE::basic_string<Encode, Alloc> & str2 )
{
	XE::basic_string<Encode, Alloc> retval = str1;
	retval.append( str2 );

	return retval;
}


template <typename String>
XE_INLINE bool operator==( XE::basic_string_view<String> & str1, XE::basic_string_view<String> & str2 )
{
	return str1.compare( str2 ) == 0;
}

template <typename String>
XE_INLINE bool operator!=( XE::basic_string_view<String> & str1, XE::basic_string_view<String> & str2 )
{
	return str1.compare( str2 ) != 0;
}

template <typename String>
XE_INLINE bool operator<( XE::basic_string_view<String> & str1, XE::basic_string_view<String> & str2 )
{
	return str1.compare( str2 ) < 0;
}

template <typename String>
XE_INLINE bool operator>( XE::basic_string_view<String> & str1, XE::basic_string_view<String> & str2 )
{
	return str1.compare( str2 ) > 0;
}

template <typename String>
XE_INLINE bool operator<=( XE::basic_string_view<String> & str1, XE::basic_string_view<String> & str2 )
{
	return str1.compare( str2 ) <= 0;
}

template <typename String>
XE_INLINE bool operator>=( XE::basic_string_view<String> & str1, XE::basic_string_view<String> & str2 )
{
	return str1.compare( str2 ) >= 0;
}


template <typename Encode, typename Alloc>
void swap( XE::basic_string<Encode, Alloc> & str1, XE::basic_string<Encode, Alloc> & str2 )
{
	str1.swap( str2 );
}


namespace std
{
	template <typename Encode, typename Alloc> struct equal_to< XE::basic_string<Encode, Alloc> >
	{
		typedef XE::basic_string<Encode, Alloc> first_argument_type;
		typedef XE::basic_string<Encode, Alloc> second_argument_type;
		typedef bool result_type;

		bool operator()( const XE::basic_string<Encode, Alloc> & _Left, const XE::basic_string<Encode, Alloc> & _Right ) const
		{
			return ( _Left == _Right );
		}
	};

	template <typename Encode, typename Alloc> struct hash< XE::basic_string<Encode, Alloc> >
	{
		typedef XE::basic_string<Encode, Alloc> argument_type;
		typedef uint64_t result_type;

		uint64_t operator()( const XE::basic_string<Encode, Alloc> & _Keyval ) const noexcept
		{
			return std::hash<const typename Encode::storage_unit *>()( _Keyval.c_str() );
		}
	};
}

template < typename String >
struct StringHashCompare
{
	static size_t hash( const String & a )
	{
		return std::hash< String >()( a );
	}
	static bool equal( const String & a, const String & b )
	{
		return std::equal_to< String >()( a, b );
	}
};

#endif // STRING_HPP__2D116B84_5AD0_4FFF_A245_8EC14E092378
