/*!
 * \file   MStream.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/06/26
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MSTREAM_HPP__6426E8EE_6AF1_4B69_9CB9_F9569C80C447
#define __MSTREAM_HPP__6426E8EE_6AF1_4B69_9CB9_F9569C80C447

#include "Type.h"

BEG_XE_NAMESPACE

template <class _Elem, class _Traits>
class BasicMemoryView;

template <class _Traits> 
class _Memory_view_iterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type        = typename _Traits::char_type;
	using difference_type   = ptrdiff_t;
	using pointer           = const value_type *;
	using reference         = const value_type &;

	constexpr _Memory_view_iterator() noexcept
	#ifdef XE_DEBUG
		: _Mydata(), _Mysize( 0 ), _Myoff( 0 )
	#else
		: _Myptr()
	#endif 
	{
	}

private:
	friend BasicMemoryView<value_type, _Traits>;

#ifdef XE_DEBUG
	constexpr _Memory_view_iterator( const pointer _Data, const size_t _Size, const size_t _Off ) noexcept
		: _Mydata( _Data ), _Mysize( _Size ), _Myoff( _Off )
	{
	}
#else
	constexpr explicit _Memory_view_iterator( const pointer _Ptr ) noexcept
		: _Myptr( _Ptr )
	{
	}
#endif 

public:
	constexpr reference operator*() const noexcept
	{
		XE_ASSERT( _Mydata && "cannot dereference value-initialized basic_memory_view<char> iterator" );
		XE_ASSERT( _Myoff < _Mysize && "cannot dereference end basic_memory_view<char> iterator" );
	#ifdef XE_DEBUG
		return _Mydata[_Myoff];
	#else
		return *_Myptr;
	#endif 
	}

	constexpr pointer operator->() const noexcept
	{
		XE_ASSERT( _Mydata && "cannot dereference value-initialized basic_memory_view<char> iterator" );
		XE_ASSERT( _Myoff < _Mysize && "cannot dereference end basic_memory_view<char> iterator" );
	#ifdef XE_DEBUG
		return _Mydata + _Myoff;
	#else 
		return _Myptr;
	#endif 
	}

	constexpr _Memory_view_iterator & operator++() noexcept
	{
		XE_ASSERT( _Mydata && "cannot increment value-initialized basic_memory_view<char> iterator" );
		XE_ASSERT( _Myoff < _Mysize && "cannot increment basic_memory_view<char> iterator past end" );
	#ifdef XE_DEBUG
		++_Myoff;
	#else 
		++_Myptr;
	#endif 
		return *this;
	}

	constexpr _Memory_view_iterator operator++( int ) noexcept
	{
		_Memory_view_iterator _Tmp{ *this };
		++ * this;
		return _Tmp;
	}

	constexpr _Memory_view_iterator & operator--() noexcept
	{
		XE_ASSERT( _Mydata && "cannot decrement value-initialized basic_memory_view<char> iterator" );
		XE_ASSERT( _Myoff != 0 && "cannot decrement basic_memory_view<char> iterator before begin" );
	#ifdef XE_DEBUG
		--_Myoff;
	#else 
		--_Myptr;
	#endif 
		return *this;
	}

	constexpr _Memory_view_iterator operator--( int ) noexcept
	{
		_Memory_view_iterator _Tmp{ *this };
		-- * this;
		return _Tmp;
	}

	constexpr _Memory_view_iterator & operator+=( const difference_type _Off ) noexcept
	{
	#ifdef XE_DEBUG
		_Verify_offset( _Off );
		_Myoff += _Off;
	#else 
		_Myptr += _Off;
	#endif 

		return *this;
	}

	constexpr _Memory_view_iterator operator+( const difference_type _Off ) const
		noexcept
	{ // return this + integer
		_Memory_view_iterator _Tmp{ *this };
		_Tmp += _Off;
		return _Tmp;
	}

	constexpr _Memory_view_iterator & operator-=( const difference_type _Off ) noexcept
	{ // decrement by integer
	#ifdef XE_DEBUG
		if( _Off != 0 )
		{
			XE_ASSERT( _Mydata && "cannot seek value-initialized basic_memory_view<char> iterator" );
		}

		if( _Off > 0 )
		{
			XE_ASSERT( _Myoff >= static_cast< size_t >( _Off ) && "cannot seek basic_memory_view<char> iterator before begin" );
		}

		if( _Off < 0 )
		{
		#pragma warning(suppress : 4146)
			XE_ASSERT( _Mysize - _Myoff >= -static_cast< size_t >( _Off ) && "cannot seek basic_memory_view<char> iterator after end" );
		}

		_Myoff -= _Off;
	#else 
		_Myptr -= _Off;
	#endif 

		return *this;
	}

	constexpr _Memory_view_iterator operator-( const difference_type _Off ) const
		noexcept
	{ // return this - integer
		_Memory_view_iterator _Tmp{ *this };
		_Tmp -= _Off;
		return _Tmp;
	}

	constexpr difference_type operator-( const _Memory_view_iterator & _Right ) const
		noexcept
	{
		XE_ASSERT( _Mydata == _Right._Mydata && _Mysize == _Right._Mysize && "cannot subtract incompatible basic_memory_view<char> iterators" );
	#ifdef XE_DEBUG
		return static_cast< difference_type >( _Myoff - _Right._Myoff );
	#else 
		return _Myptr - _Right._Myptr;
	#endif 
	}

	constexpr reference operator[]( const difference_type _Off ) const noexcept
	{
		return *( *this + _Off );
	}

	constexpr bool operator==( const _Memory_view_iterator & _Right ) const
		noexcept
	{
		XE_ASSERT( _Mydata == _Right._Mydata && _Mysize == _Right._Mysize && "cannot compare incompatible basic_memory_view<char> iterators for equality" );
	#ifdef XE_DEBUG
		return _Myoff == _Right._Myoff;
	#else 
		return _Myptr == _Right._Myptr;
	#endif 
	}

	constexpr bool operator!=( const _Memory_view_iterator & _Right ) const
		noexcept
	{
		return !( *this == _Right );
	}

	constexpr bool operator<( const _Memory_view_iterator & _Right ) const noexcept
	{
		XE_ASSERT( _Mydata == _Right._Mydata && _Mysize == _Right._Mysize && "cannot compare incompatible basic_memory_view<char> iterators" );
	#ifdef XE_DEBUG
		return _Myoff < _Right._Myoff;
	#else 
		return _Myptr < _Right._Myptr;
	#endif 
	}

	constexpr bool operator>( const _Memory_view_iterator & _Right ) const noexcept
	{
		return _Right < *this;
	}

	constexpr bool operator<=( const _Memory_view_iterator & _Right ) const noexcept
	{
		return !( _Right < *this );
	}

	constexpr bool operator>=( const _Memory_view_iterator & _Right ) const noexcept
	{
		return !( *this < _Right );
	}

#ifdef XE_DEBUG
private:
	constexpr void _Verify_offset( const difference_type _Off ) const noexcept
	{
		if( _Off != 0 )
		{
			XE_ASSERT( _Mydata && "cannot seek value-initialized basic_memory_view<char> iterator" );
		}

		if( _Off < 0 )
		{
		#pragma warning(suppress : 4146)
			XE_ASSERT( _Myoff >= -static_cast< size_t >( _Off ) && "cannot seek basic_memory_view<char> iterator before begin" );
		}

		if( _Off > 0 )
		{
			XE_ASSERT( _Mysize - _Myoff >= static_cast< size_t >( _Off ) && "cannot seek basic_memory_view<char> iterator after end" );
		}
	}
#endif

private:
#ifdef XE_DEBUG
	pointer _Mydata;
	size_t _Mysize;
	size_t _Myoff;
#else 
	pointer _Myptr;
#endif 
};

template <class _Elem, class _Traits = std::char_traits<_Elem>> 
class BasicMemoryView
{
public:
	using traits_type            = _Traits;
	using value_type             = _Elem;
	using pointer                = _Elem *;
	using const_pointer          = const _Elem *;
	using reference              = _Elem &;
	using const_reference        = const _Elem &;
	using const_iterator         = _Memory_view_iterator<_Traits>;
	using iterator               = const_iterator;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using reverse_iterator       = const_reverse_iterator;
	using size_type              = size_t;
	using difference_type        = ptrdiff_t;

public:
	static constexpr auto npos{ static_cast< size_type >( -1 ) };

public:
	constexpr BasicMemoryView() noexcept
		: _Mydata( nullptr ), _Mysize( 0 )
	{
	}
	
	constexpr BasicMemoryView( std::nullptr_t ) noexcept
		: _Mydata( nullptr ), _Mysize( 0 )
	{
	}

	constexpr BasicMemoryView( const BasicMemoryView & ) noexcept = default;
	
	constexpr BasicMemoryView & operator=( const BasicMemoryView & ) noexcept = default;

	constexpr BasicMemoryView( const_pointer _Cts, size_type _Count ) noexcept
		: _Mydata( _Cts ), _Mysize( _Count )
	{
	}

public:
	constexpr const_iterator begin() const noexcept
	{
	#ifdef XE_DEBUG
		return const_iterator( _Mydata, _Mysize, 0 );
	#else 
		return const_iterator( _Mydata );
	#endif 
	}

	constexpr const_iterator end() const noexcept
	{
	#ifdef XE_DEBUG
		return const_iterator( _Mydata, _Mysize, _Mysize );
	#else 
		return const_iterator( _Mydata + _Mysize );
	#endif 
	}

	constexpr const_iterator cbegin() const noexcept
	{
		return begin();
	}

	constexpr const_iterator cend() const noexcept
	{
		return end();
	}

	constexpr const_reverse_iterator rbegin() const noexcept
	{
		return const_reverse_iterator{ end() };
	}

	constexpr const_reverse_iterator rend() const noexcept
	{
		return const_reverse_iterator{ begin() };
	}

	constexpr const_reverse_iterator crbegin() const noexcept
	{
		return rbegin();
	}

	constexpr const_reverse_iterator crend() const noexcept
	{
		return rend();
	}

public:
	constexpr size_type size() const noexcept
	{
		return _Mysize;
	}

	constexpr size_type length() const noexcept
	{
		return _Mysize;
	}

	constexpr bool empty() const noexcept
	{
		return _Mysize == 0;
	}

public:
	constexpr const_pointer data() const noexcept
	{
		return _Mydata;
	}

	constexpr size_type max_size() const noexcept
	{
		return _Min_value( static_cast< size_t >( PTRDIFF_MAX ), static_cast< size_t >( -1 ) / sizeof( _Elem ) );
	}

public:
	constexpr operator bool() const noexcept
	{
		return _Mydata != nullptr;
	}

	constexpr const_reference operator[]( const size_type _Off ) const noexcept
	{
		XE_ASSERT( _Off < _Mysize && "basic_memory_view<char> subscript out of range" );

		return _Mydata[_Off];
	}

	constexpr const_reference at( const size_type _Off ) const
	{
		_Check_offset_exclusive( _Off );
		return _Mydata[_Off];
	}

	constexpr const_reference front() const noexcept
	{
		XE_ASSERT( _Mysize != 0 && "cannot call front on empty basic_memory_view<char>" );

		return _Mydata[0];
	}

	constexpr const_reference back() const noexcept
	{
		XE_ASSERT( _Mysize != 0 && "cannot call back on empty basic_memory_view<char>" );

		return _Mydata[_Mysize - 1];
	}

public:
	constexpr void remove_prefix( const size_type _Count ) noexcept
	{
		XE_ASSERT( _Mysize >= _Count && "cannot remove prefix longer than total size" );

		_Mydata += _Count;
		_Mysize -= _Count;
	}

	constexpr void remove_suffix( const size_type _Count ) noexcept
	{
		XE_ASSERT( _Mysize >= _Count && "cannot remove suffix longer than total size" );

		_Mysize -= _Count;
	}

public:
	constexpr void swap( BasicMemoryView & _Other ) noexcept
	{
		const BasicMemoryView _Tmp{ _Other };
		_Other = *this;
		*this = _Tmp;
	}

	constexpr size_type copy( _Elem * const _Ptr, size_type _Count, const size_type _Off = 0 ) const
	{
		_Check_offset( _Off );
		_Count = _Clamp_suffix_size( _Off, _Count );
		_Traits::copy( _Ptr, _Mydata + _Off, _Count );
		return _Count;
	}

	constexpr BasicMemoryView subview( const size_type _Off = 0, size_type _Count = npos ) const
	{
		_Check_offset( _Off );
		_Count = _Clamp_suffix_size( _Off, _Count );
		return BasicMemoryView( _Mydata + _Off, _Count );
	}

private:
	constexpr void _Check_offset( const size_type _Off ) const
	{
		if( _Mysize < _Off )
		{
			_Xran();
		}
	}

	constexpr void _Check_offset_exclusive( const size_type _Off ) const
	{
		if( _Mysize <= _Off )
		{
			_Xran();
		}
	}

	constexpr size_type _Clamp_suffix_size( const size_type _Off, const size_type _Size ) const noexcept
	{
		return _Min_value( _Size, _Mysize - _Off );
	}

	static void _Xran()
	{
		XE_ASSERT( false && "invalid basic_memory_view<char> position" );
	}

	const_pointer _Mydata;
	size_type _Mysize;
};

template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
class BasicMemoryBuf : public std::basic_streambuf<_Elem, _Traits>
{
public:
	using allocator_type = _Alloc;
	using _Mysb          = std::basic_streambuf<_Elem, _Traits>;
	using _Myview         = BasicMemoryView<_Elem, _Traits>;
	using _Mysize_type   = typename _Myview::size_type;

	explicit BasicMemoryBuf( std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Seekhigh( nullptr ), _Mystate( _Getstate( _Mode ) ), _Al()
	{
	}

	explicit BasicMemoryBuf( const _Myview & _Str, std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Al()
	{
		_Init( _Str.data(), _Str.size(), _Getstate( _Mode ) );
	}

	BasicMemoryBuf( BasicMemoryBuf && _Right )
	{
		_Assign_rv( std::move( _Right ) );
	}

	BasicMemoryBuf & operator=( BasicMemoryBuf && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( BasicMemoryBuf && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Tidy();
			this->swap( _Right );
		}
	}

	void swap( BasicMemoryBuf & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mysb::swap( _Right );
			std::swap( _Seekhigh, _Right._Seekhigh );
			std::swap( _Mystate, _Right._Mystate );
			_Swap_adl( _Al, _Right._Al );
		}
	}

	BasicMemoryBuf( const BasicMemoryBuf & ) = delete;
	BasicMemoryBuf & operator=( const BasicMemoryBuf & ) = delete;

	virtual ~BasicMemoryBuf() noexcept
	{
		_Tidy();
	}

	enum
	{
		_Allocated = 1,
		_Constant = 2,
		_Noread = 4,
		_Append = 8,
		_Atend = 16
	};

	using int_type = typename _Traits::int_type;
	using pos_type = typename _Traits::pos_type;
	using off_type = typename _Traits::off_type;

	_Myview view() const
	{
		if( !( _Mystate & _Constant ) && _Mysb::pptr() != nullptr )
		{
			const auto _Base = _Mysb::pbase();
			return _Myview( _Base, static_cast< _Mysize_type >( std::max( _Mysb::pptr(), _Seekhigh ) - _Base ) );
		}
		else if( !( _Mystate & _Noread ) && _Mysb::gptr() != nullptr )
		{
			const auto _Base = _Mysb::eback();
			return _Myview( _Base, static_cast< _Mysize_type >( _Mysb::egptr() - _Base ) );
		}

		return _Myview();
	}

	void view( const _Myview & _Newview )
	{
		_Tidy();
		_Init( _Newview.data(), _Newview.size(), _Mystate );
	}

protected:
	virtual int_type overflow( int_type _Meta = _Traits::eof() )
	{
		if( _Mystate & _Constant )
		{
			return _Traits::eof();
		}

		if( _Traits::eq_int_type( _Traits::eof(), _Meta ) )
		{
			return _Traits::not_eof( _Meta );
		}

		const auto _Pptr = _Mysb::pptr();
		const auto _Epptr = _Mysb::epptr();
		if( _Pptr != nullptr && _Pptr < _Epptr )
		{
			*_Mysb::_Pninc() = _Traits::to_char_type( _Meta );
			_Seekhigh = _Pptr + 1;
			return _Meta;
		}

		size_t _Oldsize = 0;
		const auto _Oldptr = _Mysb::eback();
		if( _Pptr != nullptr )
		{
			_Oldsize = static_cast< size_t >( _Epptr - _Oldptr );
		}

		size_t _Newsize;
		if( _Oldsize < _MINSIZE )
		{
			_Newsize = _MINSIZE;
		}
		else if( _Oldsize < INT_MAX / 2 )
		{
			_Newsize = _Oldsize << 1;
		}
		else if( _Oldsize < INT_MAX )
		{
			_Newsize = INT_MAX;
		}
		else
		{
			return _Traits::eof();
		}

		const auto _Newptr = _Al.allocate( _Newsize );
		_Traits::copy( _Newptr, _Oldptr, _Oldsize );

		const auto _New_pnext = _Newptr + _Oldsize;
		_Seekhigh = _New_pnext + 1;

		_Mysb::setp( _Newptr, _New_pnext, _Newptr + _Newsize );
		if( _Mystate & _Noread )
		{
			_Mysb::setg( _Newptr, nullptr, _Newptr );
		}
		else
		{
			_Mysb::setg( _Newptr, _Newptr + ( _Mysb::gptr() - _Oldptr ), _Seekhigh );
		}

		if( _Mystate & _Allocated )
		{
			_Al.deallocate( _Ptr_traits::pointer_to( *_Oldptr ), _Oldsize );
		}

		_Mystate |= _Allocated;
		*_Mysb::_Pninc() = _Traits::to_char_type( _Meta );
		return _Meta;
	}

	virtual int_type pbackfail( int_type _Meta = _Traits::eof() )
	{
		const auto _Gptr = _Mysb::gptr();
		if( _Gptr == nullptr || _Gptr <= _Mysb::eback()
			|| ( !_Traits::eq_int_type( _Traits::eof(), _Meta ) && !_Traits::eq( _Traits::to_char_type( _Meta ), _Gptr[-1] )
				 && ( _Mystate & _Constant ) ) )
		{
			return _Traits::eof();
		}

		_Mysb::gbump( -1 );
		if( !_Traits::eq_int_type( _Traits::eof(), _Meta ) )
		{
			*_Mysb::gptr() = _Traits::to_char_type( _Meta );
		}

		return _Traits::not_eof( _Meta );
	}

	virtual int_type underflow()
	{
		const auto _Gptr = _Mysb::gptr();
		if( _Gptr == nullptr )
		{
			return _Traits::eof();
		}

		if( _Gptr < _Mysb::egptr() )
		{
			return _Traits::to_int_type( *_Gptr );
		}

		const auto _Pptr = _Mysb::pptr();
		if( !_Pptr || ( _Mystate & _Noread ) )
		{
			return _Traits::eof();
		}

		const auto _Local_highwater = std::max( _Seekhigh, _Pptr );
		if( _Local_highwater <= _Gptr )
		{
			return _Traits::eof();
		}

		_Seekhigh = _Local_highwater;
		_Mysb::setg( _Mysb::eback(), _Mysb::gptr(), _Local_highwater );
		return _Traits::to_int_type( *_Mysb::gptr() );
	}

	virtual pos_type seekoff( off_type _Off, std::ios_base::seekdir _Way, std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
	{
		const auto _Gptr_old = _Mysb::gptr();
		const auto _Pptr_old = _Mysb::pptr();
		if( _Pptr_old != nullptr && _Seekhigh < _Pptr_old )
		{
			_Seekhigh = _Pptr_old;
		}

		const auto _Seeklow = _Mysb::eback();
		const auto _Seekdist = _Seekhigh - _Seeklow;
		off_type _Newoff;
		switch( _Way )
		{
		case std::ios_base::beg:
			_Newoff = 0;
			break;
		case std::ios_base::end:
			_Newoff = _Seekdist;
			break;
		case std::ios_base::cur:
		{
			constexpr auto _Both = std::ios_base::in | std::ios_base::out;
			if( ( _Mode & _Both ) != _Both )
			{
				if( _Mode & std::ios_base::in )
				{
					if( _Gptr_old != nullptr || _Seeklow == nullptr )
					{
						_Newoff = _Gptr_old - _Seeklow;
						break;
					}
				}
				else if( ( _Mode & std::ios_base::out ) && ( _Pptr_old != nullptr || _Seeklow == nullptr ) )
				{
					_Newoff = _Pptr_old - _Seeklow;
					break;
				}
			}
		}

		default:
			return pos_type( off_type( -1 ) );
		}

		if( static_cast< unsigned long long >( _Off ) + _Newoff > static_cast< unsigned long long >( _Seekdist ) )
		{
			return pos_type( off_type( -1 ) );
		}

		_Off += _Newoff;
		if( _Off != 0
			&& ( ( ( _Mode & std::ios_base::in ) && _Gptr_old == nullptr )
				 || ( ( _Mode & std::ios_base::out ) && _Pptr_old == nullptr ) ) )
		{
			return pos_type( off_type( -1 ) );
		}

		const auto _Newptr = _Seeklow + _Off;
		if( ( _Mode & std::ios_base::in ) && _Gptr_old != nullptr )
		{
			_Mysb::setg( _Seeklow, _Newptr, _Seekhigh );
		}

		if( ( _Mode & std::ios_base::out ) && _Pptr_old != nullptr )
		{
			_Mysb::setp( _Seeklow, _Newptr, _Mysb::epptr() );
		}

		return pos_type( _Off );
	}

	virtual pos_type seekpos( pos_type _Pos, std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
	{
		const auto _Off = static_cast< std::streamoff >( _Pos );
		const auto _Gptr_old = _Mysb::gptr();
		const auto _Pptr_old = _Mysb::pptr();
		if( _Pptr_old != nullptr && _Seekhigh < _Pptr_old )
		{
			_Seekhigh = _Pptr_old;
		}

		const auto _Seeklow = _Mysb::eback();
		const auto _Seekdist = _Seekhigh - _Seeklow;
		if( static_cast< unsigned long long >( _Off ) > static_cast< unsigned long long >( _Seekdist ) )
		{
			return pos_type( off_type( -1 ) );
		}

		if( _Off != 0
			&& ( ( ( _Mode & std::ios_base::in ) && _Gptr_old == nullptr )
				 || ( ( _Mode & std::ios_base::out ) && _Pptr_old == nullptr ) ) )
		{
			return pos_type( off_type( -1 ) );
		}

		const auto _Newptr = _Seeklow + _Off;
		if( ( _Mode & std::ios_base::in ) && _Gptr_old != nullptr )
		{
			_Mysb::setg( _Seeklow, _Newptr, _Seekhigh );
		}

		if( ( _Mode & std::ios_base::out ) && _Pptr_old != nullptr )
		{
			_Mysb::setp( _Seeklow, _Newptr, _Mysb::epptr() );
		}

		return pos_type( _Off );
	}

	void _Init( const _Elem * _Ptr, _Mysize_type _Count, int _State )
	{
		XE_ASSERT( _Count > INT_MAX );

		if( _Count != 0
			&& ( _State & ( _Noread | _Constant ) )
			!= ( _Noread | _Constant ) )
		{
			const auto _Pnew = _Al.allocate( _Count );
			_Traits::copy( _Pnew, _Ptr, _Count );
			_Seekhigh = _Pnew + _Count;

			if( !( _State & _Noread ) )
			{
				_Mysb::setg( _Pnew, _Pnew, _Seekhigh );
			}

			if( !( _State & _Constant ) )
			{
				_Mysb::setp( _Pnew, ( _State & ( _Atend | _Append ) ) ? _Seekhigh : _Pnew, _Seekhigh );

				if( _State & _Noread )
				{
					_Mysb::setg( _Pnew, nullptr, _Pnew );
				}
			}

			_State |= _Allocated;
		}
		else
		{
			_Seekhigh = nullptr;
		}

		_Mystate = _State;
	}

	void _Tidy() noexcept
	{
		if( _Mystate & _Allocated )
		{
			_Al.deallocate( _Ptr_traits::pointer_to( *_Mysb::eback() ),
							static_cast< typename std::allocator_traits<allocator_type>::size_type >(
							( _Mysb::pptr() != nullptr ? _Mysb::epptr() : _Mysb::egptr() ) - _Mysb::eback() ) );
		}

		_Mysb::setg( nullptr, nullptr, nullptr );
		_Mysb::setp( nullptr, nullptr );
		_Seekhigh = nullptr;
		_Mystate &= ~_Allocated;
	}

private:
	using _Ptr_traits = std::pointer_traits<typename std::allocator_traits<allocator_type>::pointer>;

	enum
	{
		_MINSIZE = 32
	};

	static int _Getstate( std::ios_base::openmode _Mode )
	{
		int _State = 0;
		if( !( _Mode & std::ios_base::in ) )
		{
			_State |= _Noread;
		}

		if( !( _Mode & std::ios_base::out ) )
		{
			_State |= _Constant;
		}

		if( _Mode & std::ios_base::app )
		{
			_State |= _Append;
		}

		if( _Mode & std::ios_base::ate )
		{
			_State |= _Atend;
		}

		return _State;
	}

	_Elem * _Seekhigh;
	int _Mystate;
	allocator_type _Al;
};

template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
class BasicIMemoryStream : public std::basic_istream<_Elem, _Traits>
{
public:
	using _Mybase        = std::basic_istream<_Elem, _Traits>;
	using allocator_type = _Alloc;
	using _Mysb          = BasicMemoryBuf<_Elem, _Traits, _Alloc>;
	using _Myview         = BasicMemoryView<_Elem, _Traits>;

	explicit BasicIMemoryStream( std::ios_base::openmode _Mode = std::ios_base::in )
		: _Mybase( &_Memorybuffer ), _Memorybuffer( _Mode | std::ios_base::in )
	{
	}

	explicit BasicIMemoryStream( const _Myview & _View, std::ios_base::openmode _Mode = std::ios_base::in )
		: _Mybase( &_Memorybuffer ), _Memorybuffer( _View, _Mode | std::ios_base::in )
	{
	}

	BasicIMemoryStream( BasicIMemoryStream && _Right )
		: _Mybase( &_Memorybuffer )
	{
		_Assign_rv( std::move( _Right ) );
	}

	BasicIMemoryStream & operator=( BasicIMemoryStream && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( BasicIMemoryStream && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Memorybuffer.view( _Myview() );
			this->swap( _Right );
		}
	}

	void swap( BasicIMemoryStream & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mybase::swap( _Right );
			_Memorybuffer.swap( _Right._Memorybuffer );
		}
	}

	BasicIMemoryStream( const BasicIMemoryStream & ) = delete;
	BasicIMemoryStream & operator=( const BasicIMemoryStream & ) = delete;

	virtual ~BasicIMemoryStream() noexcept
	{
	}

	_Mysb * rdbuf() const
	{
		return (_Mysb * )& _Memorybuffer;
	}

	_Myview view() const
	{
		return _Memorybuffer.view();
	}

	void view( const _Myview & _Newview )
	{
		_Memorybuffer.view( _Newview );
	}

private:
	_Mysb _Memorybuffer;
};

template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
class BasicOMemoryStream : public std::basic_ostream<_Elem, _Traits>
{
public:
	using _Mybase        = std::basic_ostream<_Elem, _Traits>;
	using allocator_type = _Alloc;
	using _Mysb          = BasicMemoryBuf<_Elem, _Traits, _Alloc>;
	using _Myview         = BasicMemoryView<_Elem, _Traits>;

	explicit BasicOMemoryStream( std::ios_base::openmode _Mode = std::ios_base::out )
		: _Mybase( &_Memorybuffer ), _Memorybuffer( _Mode | std::ios_base::out )
	{
	}

	explicit BasicOMemoryStream( const _Myview & _View, std::ios_base::openmode _Mode = std::ios_base::out )
		: _Mybase( &_Memorybuffer ),
		_Memorybuffer( _View, _Mode | std::ios_base::out )
	{
	}

	BasicOMemoryStream( BasicOMemoryStream && _Right )
		: _Mybase( &_Memorybuffer )
	{
		_Assign_rv( std::move( _Right ) );
	}

	BasicOMemoryStream & operator=( BasicOMemoryStream && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( BasicOMemoryStream && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Memorybuffer.view( _Myview() );
			this->swap( _Right );
		}
	}

	void swap( BasicOMemoryStream & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mybase::swap( _Right );
			_Memorybuffer.swap( _Right._Memorybuffer );
		}
	}

	BasicOMemoryStream( const BasicOMemoryStream & ) = delete;
	BasicOMemoryStream & operator=( const BasicOMemoryStream & ) = delete;

	virtual ~BasicOMemoryStream() noexcept
	{
	}

	_Mysb * rdbuf() const
	{
		return (_Mysb * )& _Memorybuffer;
	}

	_Myview view() const
	{
		return _Memorybuffer.view();
	}

	void view( const _Myview & _Newview )
	{
		_Memorybuffer.view( _Newview );
	}

private:
	_Mysb _Memorybuffer;
};

template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
class BasicMemoryStream : public std::basic_iostream<_Elem, _Traits>
{
public:
	using _Mybase        = std::basic_iostream<_Elem, _Traits>;
	using char_type      = _Elem;
	using traits_type    = _Traits;
	using allocator_type = _Alloc;
	using int_type       = typename _Traits::int_type;
	using pos_type       = typename _Traits::pos_type;
	using off_type       = typename _Traits::off_type;
	using _Mysb          = BasicMemoryBuf<_Elem, _Traits, _Alloc>;
	using _Myview         = BasicMemoryView<_Elem, _Traits>;

	BasicMemoryStream( std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Mybase( &_Stringbuffer ), _Stringbuffer( _Mode )
	{
	}

	BasicMemoryStream( const _Myview & _View, std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Mybase( &_Stringbuffer ), _Stringbuffer( _View, _Mode )
	{
	}

	BasicMemoryStream( BasicMemoryStream && _Right ) : _Mybase( &_Stringbuffer )
	{
		_Assign_rv( std::move( _Right ) );
	}

	BasicMemoryStream( const BasicMemoryStream & _Right ) : _Mybase( &_Stringbuffer ), _Stringbuffer( _Right._Stringbuffer.view(), std::ios_base::in | std::ios_base::out )
	{

	}

	BasicMemoryStream & operator=( BasicMemoryStream && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( BasicMemoryStream && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Stringbuffer.view( _Myview() );
			this->swap( _Right );
		}
	}

	void swap( BasicMemoryStream & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mybase::swap( _Right );
			_Stringbuffer.swap( _Right._Stringbuffer );
		}
	}

	BasicMemoryStream & operator=( const BasicMemoryStream & ) = delete;

	virtual ~BasicMemoryStream() noexcept
	{
	}

	_Mysb * rdbuf() const
	{
		return (_Mysb * )& _Stringbuffer;
	}

	_Myview view() const
	{
		return _Stringbuffer.view();
	}

	void view( const _Myview & _Newview )
	{
		_Stringbuffer.view( _Newview );
	}

private:
	_Mysb _Stringbuffer;
};

using MemoryView = XE::BasicMemoryView<char>;
using MemoryStream = XE::BasicMemoryStream<char>;
using IMemoryStream = XE::BasicIMemoryStream<char>;
using OMemoryStream = XE::BasicOMemoryStream<char>;

END_XE_NAMESPACE

namespace std
{
	template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
	inline void swap( XE::BasicMemoryBuf<_Elem, _Traits, _Alloc> & _Left,
					  XE::BasicMemoryBuf<_Elem, _Traits, _Alloc> & _Right )
	{
		_Left.swap( _Right );
	}

	template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
	inline void swap( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left,
					  XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Right )
	{
		_Left.swap( _Right );
	}

	template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
	inline void swap( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left,
					  XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Right )
	{
		_Left.swap( _Right );
	}

	template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
	inline void swap( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left,
					  XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Right )
	{
		_Left.swap( _Right );
	}
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, bool & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::int8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::int16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::int32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::int64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::uint8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::uint16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::uint32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::uint64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::float32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::float64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIMemoryStream<_Elem, _Traits, _Alloc> & _Left, std::string & _Right )
{
	std::string::size_type size;

	_Left >> size;

	_Right.resize( size );

	_Left.read( reinterpret_cast< _Elem * >( _Right.data() ), size / sizeof( _Elem ) );

	return _Left;
}


template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const bool & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::int8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::int16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::int32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::int64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::float32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::float64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOMemoryStream<_Elem, _Traits, _Alloc> & _Left, const std::string & _Right )
{
	_Left << _Right.size();

	_Left.write( reinterpret_cast< const _Elem * >( _Right.c_str() ), _Right.size() / sizeof( _Elem ) );

	return _Left;
}


template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, bool & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::int8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::int16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::int32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::int64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::uint8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::uint16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::uint32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::uint64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::float32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, XE::float64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, std::string & _Right )
{
	std::string::size_type size;

	_Left >> size;

	_Right.resize( size );

	_Left.read( reinterpret_cast< _Elem * >( _Right.data() ), size / sizeof( _Elem ) );

	return _Left;
}


template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const bool & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::int8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::int16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::int32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::int64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::float32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const XE::float64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicMemoryStream<_Elem, _Traits, _Alloc> & _Left, const std::string & _Right )
{
	_Left << _Right.size();

	_Left.write( reinterpret_cast< const _Elem * >( _Right.c_str() ), _Right.size() / sizeof( _Elem ) );

	return _Left;
}

#endif // __MSTREAM_HPP__6426E8EE_6AF1_4B69_9CB9_F9569C80C447
