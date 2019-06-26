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

template <class _Elem>
struct memory_traits
{ // properties of a string or stream element
	using char_type  = _Elem;
	using int_type   = int;
	using pos_type   = std::streampos;
	using off_type   = std::streamoff;
	using state_type = _Mbstatet;

	static constexpr int compare( const _Elem * _First1, const _Elem * _First2, size_t _Count ) noexcept
	{ // strengthened
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
	{ // strengthened
// find length of null-terminated sequence
		size_t _Count = 0;
		while( *_First != _Elem() )
		{
			++_Count;
			++_First;
		}

		return _Count;
	}

	static _Elem * copy( _Elem * const _First1, const _Elem * _First2,
						 size_t _Count ) noexcept
	{ // strengthened
// copy [_First2, _First2 + _Count) to [_First1, ...)
		return static_cast<_Elem *>( std::memcpy( _First1, _First2, _Count * sizeof( _Elem ) ) );
	}

	static _Elem * _Copy_s( _Elem * const _First1, const size_t _Dest_size, const _Elem * const _First2, const size_t _Count ) noexcept
	{ // copy [_First2, _First2 + _Count) to [_First1, _First1 + _Dest_size)
		_STL_VERIFY( _Count <= _Dest_size, "invalid argument" );
		return copy( _First1, _First2, _Count );
	}

	static constexpr const _Elem * find( const _Elem * _First, size_t _Count, const _Elem & _Ch ) noexcept
	{ // strengthened
// look for _Ch in [_First, _First + _Count)
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
	{ // strengthened
// copy [_First2, _First2 + _Count) to [_First1, ...), allowing overlap
		return static_cast<_Elem *>( std::memmove( _First1, _First2, _Count * sizeof( _Elem ) ) );
	}

	static _Elem * assign( _Elem * const _First, size_t _Count, const _Elem _Ch ) noexcept
	{ // strengthened
// assign _Count * _Ch to [_First, ...)
		_Elem * _Next = _First;
		for( ; 0 < _Count; --_Count, ++_Next )
		{
			*_Next = _Ch;
		}

		return _First;
	}

	static constexpr void assign( _Elem & _Left, const _Elem & _Right ) noexcept
	{ // assign an element
		_Left = _Right;
	}

	static constexpr bool eq( const _Elem & _Left, const _Elem & _Right ) noexcept
	{ // test for element equality
		return _Left == _Right;
	}

	static constexpr bool lt( const _Elem & _Left, const _Elem & _Right ) noexcept
	{ // test if _Left precedes _Right
		return _Left < _Right;
	}

	static constexpr _Elem to_char_type( const int_type & _Meta ) noexcept
	{ // convert metacharacter to character
		return static_cast<_Elem>( _Meta );
	}

	static constexpr int_type to_int_type( const _Elem & _Ch ) noexcept
	{ // convert character to metacharacter
		return static_cast<int_type>( _Ch );
	}

	static constexpr bool eq_int_type( const int_type & _Left, const int_type & _Right ) noexcept
	{ // test for metacharacter equality
		return _Left == _Right;
	}

	static constexpr int_type not_eof( const int_type & _Meta ) noexcept
	{ // return anything but EOF
		return _Meta != eof() ? _Meta : !eof();
	}

	static constexpr int_type eof() noexcept
	{ // return end-of-file metacharacter
		return static_cast<int_type>( EOF );
	}
};

END_XE_NAMESPACE

#endif // __TYPE_H__6AF9B68A_CAEE_4C9A_88C7_E1903198CC04
