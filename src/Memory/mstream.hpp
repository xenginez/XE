/*!
 * \file   mstream.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/06/26
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MSTREAM_HPP__6426E8EE_6AF1_4B69_9CB9_F9569C80C447
#define __MSTREAM_HPP__6426E8EE_6AF1_4B69_9CB9_F9569C80C447

#include "Allocator.hpp"

BEG_XE_NAMESPACE

template <class _Elem, class _Traits> class basic_memory_view;

template <class _Traits>
class _Memory_view_iterator
{ // iterator for character buffer wrapper
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type        = typename _Traits::char_type;
	using difference_type   = ptrdiff_t;
	using pointer           = const value_type *;
	using reference         = const value_type &;

	constexpr _Memory_view_iterator() noexcept
	#ifdef DEBUG
		: _Mydata(), _Mysize( 0 ), _Myoff( 0 )
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		: _Myptr()
	#endif 
	{ // default-initialize a basic_string_view::const_iterator
	}

private:
	friend basic_memory_view<value_type, _Traits>;

#ifdef DEBUG
	constexpr _Memory_view_iterator( const pointer _Data, const size_t _Size, const size_t _Off ) noexcept
		: _Mydata( _Data ), _Mysize( _Size ), _Myoff( _Off )
	{ // initialize a basic_string_view::const_iterator
	}
#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
	constexpr explicit _Memory_view_iterator( const pointer _Ptr ) noexcept
		: _Myptr( _Ptr )
	{ // initialize a basic_string_view::const_iterator
	}
#endif 

public:
	constexpr reference operator*() const noexcept
	{ // return designated object
	#ifdef DEBUG
		_STL_VERIFY( _Mydata, "cannot dereference value-initialized string_view iterator" );
		_STL_VERIFY( _Myoff < _Mysize, "cannot dereference end string_view iterator" );
		return _Mydata[_Myoff];
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		return *_Myptr;
	#endif 
	}

	constexpr pointer operator->() const noexcept
	{ // return pointer to class object
	#ifdef DEBUG
		_STL_VERIFY( _Mydata, "cannot dereference value-initialized string_view iterator" );
		_STL_VERIFY( _Myoff < _Mysize, "cannot dereference end string_view iterator" );
		return _Mydata + _Myoff;
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		return _Myptr;
	#endif 
	}

	constexpr _Memory_view_iterator & operator++() noexcept
	{ // preincrement
	#ifdef DEBUG
		_STL_VERIFY( _Mydata, "cannot increment value-initialized string_view iterator" );
		_STL_VERIFY( _Myoff < _Mysize, "cannot increment string_view iterator past end" );
		++_Myoff;
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		++_Myptr;
	#endif 
		return *this;
	}

	constexpr _Memory_view_iterator operator++( int ) noexcept
	{ // postincrement
		_Memory_view_iterator _Tmp{ *this };
		++ * this;
		return _Tmp;
	}

	constexpr _Memory_view_iterator & operator--() noexcept
	{ // predecrement
	#ifdef DEBUG
		_STL_VERIFY( _Mydata, "cannot decrement value-initialized string_view iterator" );
		_STL_VERIFY( _Myoff != 0, "cannot decrement string_view iterator before begin" );
		--_Myoff;
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		--_Myptr;
	#endif 
		return *this;
	}

	constexpr _Memory_view_iterator operator--( int ) noexcept
	{ // postdecrement
		_Memory_view_iterator _Tmp{ *this };
		-- * this;
		return _Tmp;
	}

	constexpr _Memory_view_iterator & operator+=( const difference_type _Off ) noexcept
	{ // increment by integer
	#ifdef DEBUG
		_Verify_offset( _Off );
		_Myoff += _Off;
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
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
	#ifdef DEBUG
		if( _Off != 0 )
		{
			_STL_VERIFY( _Mydata, "cannot seek value-initialized string_view iterator" );
		}

		if( _Off > 0 )
		{
			_STL_VERIFY( _Myoff >= static_cast<size_t>( _Off ), "cannot seek string_view iterator before begin" );
		}

		if( _Off < 0 )
		{
		#pragma warning(suppress : 4146) // unary minus operator applied to unsigned type, result still unsigned
			_STL_VERIFY( _Mysize - _Myoff >= -static_cast<size_t>( _Off ), "cannot seek string_view iterator after end" );
		}

		_Myoff -= _Off;
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
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
	{ // return difference of iterators
	#ifdef DEBUG
		_STL_VERIFY( _Mydata == _Right._Mydata && _Mysize == _Right._Mysize,
					 "cannot subtract incompatible string_view iterators" );
		return static_cast<difference_type>( _Myoff - _Right._Myoff );
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		return _Myptr - _Right._Myptr;
	#endif 
	}

	constexpr reference operator[]( const difference_type _Off ) const noexcept
	{ // subscript
		return *( *this + _Off );
	}

	constexpr bool operator==( const _Memory_view_iterator & _Right ) const
		noexcept
	{ // test for iterator equality
	#ifdef DEBUG
		_STL_VERIFY( _Mydata == _Right._Mydata && _Mysize == _Right._Mysize,
					 "cannot compare incompatible string_view iterators for equality" );
		return _Myoff == _Right._Myoff;
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		return _Myptr == _Right._Myptr;
	#endif 
	}

	constexpr bool operator!=( const _Memory_view_iterator & _Right ) const
		noexcept
	{ // test for iterator inequality
		return !( *this == _Right );
	}

	constexpr bool operator<( const _Memory_view_iterator & _Right ) const noexcept
	{ // test if this < _Right
	#ifdef DEBUG
		_STL_VERIFY( _Mydata == _Right._Mydata && _Mysize == _Right._Mysize,
					 "cannot compare incompatible string_view iterators" );
		return _Myoff < _Right._Myoff;
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		return _Myptr < _Right._Myptr;
	#endif 
	}

	constexpr bool operator>( const _Memory_view_iterator & _Right ) const noexcept
	{ // test if this > _Right
		return _Right < *this;
	}

	constexpr bool operator<=( const _Memory_view_iterator & _Right ) const noexcept
	{ // test if this <= _Right
		return !( _Right < *this );
	}

	constexpr bool operator>=( const _Memory_view_iterator & _Right ) const noexcept
	{ // test if this >= _Right
		return !( *this < _Right );
	}

#ifdef DEBUG
private:
	constexpr void _Verify_offset( const difference_type _Off ) const noexcept
	{
	#ifdef DEBUG
		if( _Off != 0 )
		{
			_STL_VERIFY( _Mydata, "cannot seek value-initialized string_view iterator" );
		}

		if( _Off < 0 )
		{
		#pragma warning(suppress : 4146) // unary minus operator applied to unsigned type, result still unsigned
			_STL_VERIFY( _Myoff >= -static_cast<size_t>( _Off ), "cannot seek string_view iterator before begin" );
		}

		if( _Off > 0 )
		{
			_STL_VERIFY( _Mysize - _Myoff >= static_cast<size_t>( _Off ), "cannot seek string_view iterator after end" );
		}
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		( void) _Off;
	#endif  >= 1
	}
#endif

private:
#ifdef DEBUG
	pointer _Mydata;
	size_t _Mysize;
	size_t _Myoff;
#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
	pointer _Myptr;
#endif 
};


template <class _Elem, class _Traits> class basic_memory_view
{ // wrapper for any kind of contiguous character buffer
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


	static constexpr auto npos{ static_cast<size_type>( -1 ) };

	constexpr basic_memory_view() noexcept : _Mydata(), _Mysize( 0 )
	{ // construct empty basic_string_view
	}

	constexpr basic_memory_view( const basic_memory_view & ) noexcept = default;
	constexpr basic_memory_view & operator=( const basic_memory_view & ) noexcept = default;

	constexpr basic_memory_view( const const_pointer _Cts, const size_type _Count ) noexcept // strengthened
		: _Mydata( _Cts ), _Mysize( _Count )
	{
	}

	constexpr const_iterator begin() const noexcept
	{ // get the beginning of the range
	#ifdef DEBUG
		return const_iterator( _Mydata, _Mysize, 0 );
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		return const_iterator( _Mydata );
	#endif 
	}

	constexpr const_iterator end() const noexcept
	{ // get the end of the range
	#ifdef DEBUG
		return const_iterator( _Mydata, _Mysize, _Mysize );
	#else // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
		return const_iterator( _Mydata + _Mysize );
	#endif 
	}

	constexpr const_iterator cbegin() const noexcept
	{ // get the beginning of the range
		return begin();
	}

	constexpr const_iterator cend() const noexcept
	{ // get the end of the range
		return end();
	}

	constexpr const_reverse_iterator rbegin() const noexcept
	{ // get the beginning of the reversed range
		return const_reverse_iterator{ end() };
	}

	constexpr const_reverse_iterator rend() const noexcept
	{ // get the end of the reversed range
		return const_reverse_iterator{ begin() };
	}

	constexpr const_reverse_iterator crbegin() const noexcept
	{ // get the beginning of the reversed range
		return rbegin();
	}

	constexpr const_reverse_iterator crend() const noexcept
	{ // get the end of the reversed range
		return rend();
	}

	constexpr size_type size() const noexcept
	{ // get the size of this basic_string_view
		return _Mysize;
	}

	constexpr size_type length() const noexcept
	{ // get the size of this basic_string_view
		return _Mysize;
	}

	constexpr bool empty() const noexcept
	{ // check whether this basic_string_view is empty
		return _Mysize == 0;
	}

	constexpr const_pointer data() const noexcept
	{ // get the base pointer of this basic_string_view
		return _Mydata;
	}

	constexpr size_type max_size() const
		noexcept
	{ // get the maximum possible size
	 // bound to PTRDIFF_MAX to make end() - begin() well defined (also makes room for npos)
	 // bound to static_cast<size_t>(-1) / sizeof(_Elem) by address space limits
		return _Min_value( static_cast<size_t>( PTRDIFF_MAX ), static_cast<size_t>( -1 ) / sizeof( _Elem ) );
	}

	constexpr const_reference operator[]( const size_type _Off ) const noexcept
	{ // strengthened
// get character at offset; assume offset is in range
	#ifdef DEBUG
		_STL_VERIFY( _Off < _Mysize, "string_view subscript out of range" );
	#endif  >= 1
		return _Mydata[_Off];
	}

	constexpr const_reference at( const size_type _Off ) const
	{ // get the character at _Off or throw if that is out of range
		_Check_offset_exclusive( _Off );
		return _Mydata[_Off];
	}

	constexpr const_reference front() const noexcept
	{ // strengthened
// returns a reference to the first character in *this
	#ifdef DEBUG
		_STL_VERIFY( _Mysize != 0, "cannot call front on empty string_view" );
	#endif  >= 1
		return _Mydata[0];
	}

	constexpr const_reference back() const noexcept
	{ // strengthened
// returns a reference to the last character in *this
	#ifdef DEBUG
		_STL_VERIFY( _Mysize != 0, "cannot call back on empty string_view" );
	#endif  >= 1
		return _Mydata[_Mysize - 1];
	}

	constexpr void remove_prefix( const size_type _Count ) noexcept
	{ // strengthened
// chop off the beginning
	#ifdef DEBUG
		_STL_VERIFY( _Mysize >= _Count, "cannot remove prefix longer than total size" );
	#endif  >= 1
		_Mydata += _Count;
		_Mysize -= _Count;
	}

	constexpr void remove_suffix( const size_type _Count ) noexcept
	{ // strengthened
// chop off the end
	#ifdef DEBUG
		_STL_VERIFY( _Mysize >= _Count, "cannot remove suffix longer than total size" );
	#endif  >= 1
		_Mysize -= _Count;
	}

	constexpr void swap( basic_memory_view & _Other ) noexcept
	{ // swap contents
		const basic_memory_view _Tmp{ _Other }; // note: std::swap is not constexpr
		_Other = *this;
		*this = _Tmp;
	}

	constexpr size_type copy( _Elem * const _Ptr, size_type _Count, const size_type _Off = 0 ) const
	{ // copy [_Off, _Off + Count) to [_Ptr, _Ptr + _Count)
		_Check_offset( _Off );
		_Count = _Clamp_suffix_size( _Off, _Count );
		_Traits::copy( _Ptr, _Mydata + _Off, _Count );
		return _Count;
	}

	constexpr basic_memory_view substr( const size_type _Off = 0, size_type _Count = npos ) const
	{ // return a new basic_string_view moved forward by _Off and trimmed to _Count elements
		_Check_offset( _Off );
		_Count = _Clamp_suffix_size( _Off, _Count );
		return basic_memory_view( _Mydata + _Off, _Count );
	}

private:
	constexpr void _Check_offset( const size_type _Off ) const
	{ // checks whether _Off is in the bounds of [0, size()]
		if( _Mysize < _Off )
		{
			_Xran();
		}
	}

	constexpr void _Check_offset_exclusive( const size_type _Off ) const
	{ // checks whether _Off is in the bounds of [0, size())
		if( _Mysize <= _Off )
		{
			_Xran();
		}
	}

	constexpr size_type _Clamp_suffix_size( const size_type _Off, const size_type _Size ) const noexcept
	{ // trims _Size to the longest it can be assuming a string at/after _Off
		return _Min_value( _Size, _Mysize - _Off );
	}

	static void _Xran()
	{ // report an out_of_range error
		ASSERT( false && "invalid memory_view position" );
	}

	const_pointer _Mydata;
	size_type _Mysize;
};

using memory_view = basic_memory_view<XE::uint8, memory_traits<XE::uint8>>;

template <class _Elem, class _Traits, class _Alloc>
class basic_memorybuf : public std::basic_streambuf<_Elem, _Traits>
{
public:
	using allocator_type = _Alloc;
	using _Mysb          = std::basic_streambuf<_Elem, _Traits>;
	using _Myview         = memory_view;
	using _Mysize_type   = typename _Myview::size_type;

	explicit basic_memorybuf( std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Seekhigh( nullptr ), _Mystate( _Getstate( _Mode ) ), _Al()
	{
	}

	explicit basic_memorybuf( const _Myview & _Str, std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Al( _Str.get_allocator() )
	{
		_Init( _Str.data(), _Str.size(), _Getstate( _Mode ) );
	}

	basic_memorybuf( basic_memorybuf && _Right )
	{
		_Assign_rv( std::move( _Right ) );
	}

	basic_memorybuf & operator=( basic_memorybuf && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( basic_memorybuf && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Tidy();
			this->swap( _Right );
		}
	}

	void swap( basic_memorybuf & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mysb::swap( _Right );
			std::swap( _Seekhigh, _Right._Seekhigh );
			std::swap( _Mystate, _Right._Mystate );
			_Swap_adl( _Al, _Right._Al );
		}
	}

	basic_memorybuf( const basic_memorybuf & ) = delete;
	basic_memorybuf & operator=( const basic_memorybuf & ) = delete;

	virtual ~basic_memorybuf() noexcept
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
			return _Myview( _Base, static_cast<_Mysize_type>( _Max_value( _Mysb::pptr(), _Seekhigh ) - _Base ) );
		}
		else if( !( _Mystate & _Noread ) && _Mysb::gptr() != nullptr )
		{
			const auto _Base = _Mysb::eback();
			return _Myview( _Base, static_cast<_Mysize_type>( _Mysb::egptr() - _Base ) );
		}

		return _Myview();
	}

	void view( const _Myview & _Newstr )
	{
		_Tidy();
		_Init( _Newstr.data(), _Newstr.size(), _Mystate );
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
			_Oldsize = static_cast<size_t>( _Epptr - _Oldptr );
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

		const auto _Newptr = _Unfancy( _Al.allocate( _Newsize ) );
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

		const auto _Local_highwater = _Max_value( _Seekhigh, _Pptr );
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

		if( static_cast<unsigned long long>( _Off ) + _Newoff > static_cast<unsigned long long>( _Seekdist ) )
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
		const auto _Off = static_cast<streamoff>( _Pos );
		const auto _Gptr_old = _Mysb::gptr();
		const auto _Pptr_old = _Mysb::pptr();
		if( _Pptr_old != nullptr && _Seekhigh < _Pptr_old )
		{
			_Seekhigh = _Pptr_old;
		}

		const auto _Seeklow = _Mysb::eback();
		const auto _Seekdist = _Seekhigh - _Seeklow;
		if( static_cast<unsigned long long>( _Off ) > static_cast<unsigned long long>( _Seekdist ) )
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
		if( _Count > INT_MAX )
		{
			_Xbad_alloc();
		}

		if( _Count != 0
			&& ( _State & ( _Noread | _Constant ) )
			!= ( _Noread | _Constant ) )
		{
			const auto _Pnew = _Unfancy( _Al.allocate( _Count ) );
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
							static_cast<typename allocator_traits<allocator_type>::size_type>(
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

template <class _Elem, class _Traits, class _Alloc>
inline void swap( basic_memorybuf<_Elem, _Traits, _Alloc> & _Left, basic_memorybuf<_Elem, _Traits, _Alloc> & _Right )
{
	_Left.swap( _Right );
}

template <class _Elem, class _Traits, class _Alloc>
class basic_imemorystream : public std::basic_istream<_Elem, _Traits>
{
public:
	using _Mybase        = std::basic_istream<_Elem, _Traits>;
	using allocator_type = _Alloc;
	using _Mysb          = basic_memorybuf<_Elem, _Traits, _Alloc>;
	using _Myview         = memory_view;

	explicit basic_imemorystream( std::ios_base::openmode _Mode = std::ios_base::in )
		: _Mybase( &_Memorybuffer ), _Memorybuffer( _Mode | std::ios_base::in )
	{
	}

	explicit basic_imemorystream( const _Myview & _Str, std::ios_base::openmode _Mode = std::ios_base::in )
		: _Mybase( &_Memorybuffer ),
		_Memorybuffer( _Str, _Mode | std::ios_base::in )
	{
	}

	basic_imemorystream( basic_imemorystream && _Right )
		: _Mybase( &_Memorybuffer )
	{
		_Assign_rv( std::move( _Right ) );
	}

	basic_imemorystream & operator=( basic_imemorystream && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( basic_imemorystream && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Memorybuffer.view( _Myview() );
			this->swap( _Right );
		}
	}

	void swap( basic_imemorystream & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mybase::swap( _Right );
			_Memorybuffer.swap( _Right._Memorybuffer );
		}
	}

	basic_imemorystream( const basic_imemorystream & ) = delete;
	basic_imemorystream & operator=( const basic_imemorystream & ) = delete;

	virtual ~basic_imemorystream() noexcept
	{
	}

	_Mysb * rdbuf() const
	{
		return ( _Mysb *) & _Memorybuffer;
	}

	_Myview view() const
	{
		return _Memorybuffer.view();
	}

	void view( const _Myview & _Newstr )
	{
		_Memorybuffer.view( _Newstr );
	}

private:
	_Mysb _Memorybuffer;
};

template <class _Elem, class _Traits, class _Alloc>
inline void swap( basic_imemorystream<_Elem, _Traits, _Alloc> & _Left, basic_imemorystream<_Elem, _Traits, _Alloc> & _Right )
{
	_Left.swap( _Right );
}

template <class _Elem, class _Traits, class _Alloc>
class basic_omemorystream : public std::basic_ostream<_Elem, _Traits>
{
public:
	using _Mybase        = std::basic_ostream<_Elem, _Traits>;
	using allocator_type = _Alloc;
	using _Mysb          = basic_memorybuf<_Elem, _Traits, _Alloc>;
	using _Myview         = memory_view;

	explicit basic_omemorystream( std::ios_base::openmode _Mode = std::ios_base::out )
		: _Mybase( &_Memorybuffer ), _Memorybuffer( _Mode | std::ios_base::out )
	{
	}

	explicit basic_omemorystream( const _Myview & _Str, std::ios_base::openmode _Mode = std::ios_base::out )
		: _Mybase( &_Memorybuffer ),
		_Memorybuffer( _Str, _Mode | std::ios_base::out )
	{
	}

	basic_omemorystream( basic_omemorystream && _Right )
		: _Mybase( &_Memorybuffer )
	{
		_Assign_rv( std::move( _Right ) );
	}

	basic_omemorystream & operator=( basic_omemorystream && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( basic_omemorystream && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Memorybuffer.view( _Myview() );
			this->swap( _Right );
		}
	}

	void swap( basic_omemorystream & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mybase::swap( _Right );
			_Memorybuffer.swap( _Right._Memorybuffer );
		}
	}

	basic_omemorystream( const basic_omemorystream & ) = delete;
	basic_omemorystream & operator=( const basic_omemorystream & ) = delete;

	virtual ~basic_omemorystream() noexcept
	{
	}

	_Mysb * rdbuf() const
	{
		return ( _Mysb *) & _Memorybuffer;
	}

	_Myview view() const
	{
		return _Memorybuffer.view();
	}

	void view( const _Myview & _Newstr )
	{
		_Memorybuffer.view( _Newstr );
	}

private:
	_Mysb _Memorybuffer;
};

template <class _Elem, class _Traits, class _Alloc>
inline void swap( basic_omemorystream<_Elem, _Traits, _Alloc> & _Left,
				  basic_omemorystream<_Elem, _Traits, _Alloc> & _Right )
{
	_Left.swap( _Right );
}

template <class _Elem, class _Traits, class _Alloc>
class basic_memorystream : public std::basic_iostream<_Elem, _Traits>
{
public:
	using _Mybase        = std::basic_iostream<_Elem, _Traits>;
	using char_type      = _Elem;
	using traits_type    = _Traits;
	using allocator_type = _Alloc;
	using int_type       = typename _Traits::int_type;
	using pos_type       = typename _Traits::pos_type;
	using off_type       = typename _Traits::off_type;
	using _Mysb          = basic_memorybuf<_Elem, _Traits, _Alloc>;
	using _Myview         = memory_view;

	explicit basic_memorystream( std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Mybase( &_Stringbuffer ), _Stringbuffer( _Mode )
	{
	}

	explicit basic_memorystream( const _Myview & _Str, std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Mybase( &_Stringbuffer ), _Stringbuffer( _Str, _Mode )
	{
	}

	basic_memorystream( basic_memorystream && _Right ) : _Mybase( &_Stringbuffer )
	{
		_Assign_rv( std::move( _Right ) );
	}

	basic_memorystream & operator=( basic_memorystream && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( basic_memorystream && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Stringbuffer.view( _Myview() );
			this->swap( _Right );
		}
	}

	void swap( basic_memorystream & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mybase::swap( _Right );
			_Stringbuffer.swap( _Right._Stringbuffer );
		}
	}

	basic_memorystream( const basic_memorystream & ) = delete;
	basic_memorystream & operator=( const basic_memorystream & ) = delete;

	virtual ~basic_memorystream() noexcept
	{
	}

	_Mysb * rdbuf() const
	{
		return ( _Mysb *) & _Stringbuffer;
	}

	_Myview view() const
	{
		return _Stringbuffer.view();
	}

	void view( const _Myview & _Newstr )
	{
		_Stringbuffer.view( _Newstr );
	}

private:
	_Mysb _Stringbuffer;
};

template <class _Elem, class _Traits, class _Alloc>
inline void swap( basic_memorystream<_Elem, _Traits, _Alloc> & _Left, basic_memorystream<_Elem, _Traits, _Alloc> & _Right )
{
	_Left.swap( _Right );
}

using imemorystream = basic_imemorystream<XE::uint8, memory_traits<XE::uint8>, XE::Allocator<XE::uint8>>;
using omemorystream = basic_omemorystream<XE::uint8, memory_traits<XE::uint8>, XE::Allocator<XE::uint8>>;
using memorystream = basic_memorystream<XE::uint8, memory_traits<XE::uint8>, XE::Allocator<XE::uint8>>;

END_XE_NAMESPACE

#endif // __MSTREAM_HPP__6426E8EE_6AF1_4B69_9CB9_F9569C80C447
