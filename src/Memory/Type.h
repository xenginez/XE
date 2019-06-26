/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__6AF9B68A_CAEE_4C9A_88C7_E1903198CC04
#define __TYPE_H__6AF9B68A_CAEE_4C9A_88C7_E1903198CC04

#include "Global.h"

BEG_XE_NAMESPACE

template <class _Elem> struct memory_traits
{
	using element_type  = _Elem;
	using int_type   = int;
	using pos_type   = std::streampos;
	using off_type   = std::streamoff;
	using state_type = _Mbstatet;

	static constexpr int compare( const _Elem * _First1, const _Elem * _First2, size_t _Count ) noexcept
	{
		for( ; 0 < _Count; --_Count, ++_First1, ++_First2 )
		{
			if( *_First1 != *_First2 )
			{
				return *_First1 < *_First2 ? -1 : +1;
			}
		}

		return 0;
	}

	static constexpr size_t length( const _Elem * _First ) noexcept
	{
		size_t _Count = 0;
		while( *_First != _Elem() )
		{
			++_Count;
			++_First;
		}

		return _Count;
	}

	static _Elem * copy( _Elem * const _First1, const _Elem * _First2, size_t _Count ) noexcept
	{
		return static_cast<_Elem *>( std::memcpy( _First1, _First2, _Count * sizeof( _Elem ) ) );
	}

	static _Elem * _Copy_s( _Elem * const _First1, const size_t _Dest_size, const _Elem * const _First2, const size_t _Count )  noexcept
	{
		ASSERT( _Count <= _Dest_size && "invalid argument" );
		return copy( _First1, _First2, _Count );
	}

	static constexpr const _Elem * find( const _Elem * _First, size_t _Count, const _Elem & _Ch ) noexcept
	{
		for( ; 0 < _Count; --_Count, ++_First )
		{
			if( *_First == _Ch )
			{
				return _First;
			}
		}

		return nullptr;
	}

	static _Elem * move( _Elem * const _First1, const _Elem * _First2, size_t _Count ) noexcept
	{
		return static_cast<_Elem *>( std::memmove( _First1, _First2, _Count * sizeof( _Elem ) ) );
	}

	static _Elem * assign( _Elem * const _First, size_t _Count, const _Elem _Ch ) noexcept
	{
		_Elem * _Next = _First;
		for( ; 0 < _Count; --_Count, ++_Next )
		{
			*_Next = _Ch;
		}

		return _First;
	}

	static constexpr void assign( _Elem & _Left, const _Elem & _Right ) noexcept
	{
		_Left = _Right;
	}

	static constexpr bool eq( const _Elem & _Left, const _Elem & _Right ) noexcept
	{
		return _Left == _Right;
	}

	static constexpr bool lt( const _Elem & _Left, const _Elem & _Right ) noexcept
	{
		return _Left < _Right;
	}

	static constexpr _Elem to_char_type( const int_type & _Meta ) noexcept
	{
		return static_cast<_Elem>( _Meta );
	}

	static constexpr int_type to_int_type( const _Elem & _Ch ) noexcept
	{
		return static_cast<int_type>( _Ch );
	}

	static constexpr bool eq_int_type( const int_type & _Left, const int_type & _Right ) noexcept
	{
		return _Left == _Right;
	}

	static constexpr int_type not_eof( const int_type & _Meta ) noexcept
	{
		return _Meta != eof() ? _Meta : !eof();
	}

	static constexpr int_type eof() noexcept
	{
		return static_cast<int_type>( EOF );
	}
};

END_XE_NAMESPACE

#endif // __TYPE_H__6AF9B68A_CAEE_4C9A_88C7_E1903198CC04
