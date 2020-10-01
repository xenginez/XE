#ifndef FSTREAM_H__D5AC1F9D_7B65_44E8_8271_4C1C463616A4
#define FSTREAM_H__D5AC1F9D_7B65_44E8_8271_4C1C463616A4

#include "FileSystem.h"

BEG_XE_NAMESPACE

template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
class BasicFileBuf : public std::basic_streambuf<_Elem, _Traits>
{
public:
	using allocator_type = _Alloc;
	using _Mysb = std::basic_streambuf<_Elem, _Traits>;
	using _Mysize_type = std::size_type;

public:
	explicit BasicFileBuf( std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Seekhigh( nullptr ), _Mystate( _Getstate( _Mode ) ), _Al()
	{
	}

	explicit BasicFileBuf( const std::string & _Str, std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Al()
	{
		_Init( _Str, _Str.size(), _Getstate( _Mode ) );
	}

	BasicFileBuf( BasicFileBuf && _Right )
	{
		_Assign_rv( std::move( _Right ) );
	}

	BasicFileBuf & operator=( BasicFileBuf && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( BasicFileBuf && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Tidy();
			this->swap( _Right );
		}
	}

	void swap( BasicFileBuf & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mysb::swap( _Right );
			std::swap( _Seekhigh, _Right._Seekhigh );
			std::swap( _Mystate, _Right._Mystate );
			_Swap_adl( _Al, _Right._Al );
		}
	}

	BasicFileBuf( const BasicFileBuf & ) = delete;
	BasicFileBuf & operator=( const BasicFileBuf & ) = delete;

	virtual ~BasicFileBuf() noexcept
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

	void _Init( const std::string & _Ptr, _Mysize_type _Count, int _State )
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
class BasicIFileStream : public std::basic_istream<_Elem, _Traits>
{
public:
	using _Mybase = std::basic_istream<_Elem, _Traits>;
	using allocator_type = _Alloc;
	using _Mysb = BasicFileBuf<_Elem, _Traits, _Alloc>;

	explicit BasicIFileStream( std::ios_base::openmode _Mode = std::ios_base::in )
		: _Mybase( &_Filebuffer ), _Filebuffer( _Mode | std::ios_base::in )
	{
	}

	explicit BasicIFileStream( const std::string & _File, std::ios_base::openmode _Mode = std::ios_base::in )
		: _Mybase( &_Filebuffer ), _Filebuffer( _File, _Mode | std::ios_base::in )
	{
	}

	BasicIFileStream( BasicIFileStream && _Right )
		: _Mybase( &_Filebuffer )
	{
		_Assign_rv( std::move( _Right ) );
	}

	BasicIFileStream & operator=( BasicIFileStream && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( BasicIFileStream && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			this->swap( _Right );
		}
	}

	void swap( BasicIFileStream & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mybase::swap( _Right );
			_Filebuffer.swap( _Right._Filebuffer );
		}
	}

	BasicIFileStream( const BasicIFileStream & ) = delete;
	BasicIFileStream & operator=( const BasicIFileStream & ) = delete;

	virtual ~BasicIFileStream() noexcept
	{
	}

	_Mysb * rdbuf() const
	{
		return ( _Mysb * ) &_Filebuffer;
	}

private:
	_Mysb _Filebuffer;
};

template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
class BasicOFileStream : public std::basic_ostream<_Elem, _Traits>
{
public:
	using _Mybase = std::basic_ostream<_Elem, _Traits>;
	using allocator_type = _Alloc;
	using _Mysb = BasicFileBuf<_Elem, _Traits, _Alloc>;

	explicit BasicOFileStream( std::ios_base::openmode _Mode = std::ios_base::out )
		: _Mybase( &_Filebuffer ), _Filebuffer( _Mode | std::ios_base::out )
	{
	}

	explicit BasicOFileStream( const std::string & _File, std::ios_base::openmode _Mode = std::ios_base::out )
		: _Mybase( &_Filebuffer ),
		_Filebuffer( _File, _Mode | std::ios_base::out )
	{
	}

	BasicOFileStream( BasicOFileStream && _Right )
		: _Mybase( &_Filebuffer )
	{
		_Assign_rv( std::move( _Right ) );
	}

	BasicOFileStream & operator=( BasicOFileStream && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( BasicOFileStream && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			this->swap( _Right );
		}
	}

	void swap( BasicOFileStream & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mybase::swap( _Right );
			_Filebuffer.swap( _Right._Filebuffer );
		}
	}

	BasicOFileStream( const BasicOFileStream & ) = delete;
	BasicOFileStream & operator=( const BasicOFileStream & ) = delete;

	virtual ~BasicOFileStream() noexcept
	{
	}

	_Mysb * rdbuf() const
	{
		return ( _Mysb * ) &_Filebuffer;
	}

private:
	_Mysb _Filebuffer;
};

template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
class BasicFileStream : public std::basic_iostream<_Elem, _Traits>
{
public:
	using _Mybase = std::basic_iostream<_Elem, _Traits>;
	using char_type = _Elem;
	using traits_type = _Traits;
	using allocator_type = _Alloc;
	using int_type = typename _Traits::int_type;
	using pos_type = typename _Traits::pos_type;
	using off_type = typename _Traits::off_type;
	using _Mysb = BasicFileBuf<_Elem, _Traits, _Alloc>;

	explicit BasicFileStream( std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Mybase( &_Filebuffer ), _Filebuffer( _Mode )
	{
	}

	explicit BasicFileStream( const std::string & _File, std::ios_base::openmode _Mode = std::ios_base::in | std::ios_base::out )
		: _Mybase( &_Filebuffer ), _Filebuffer( _File, _Mode )
	{
	}

	BasicFileStream( BasicFileStream && _Right ) : _Mybase( &_Filebuffer )
	{
		_Assign_rv( std::move( _Right ) );
	}

	BasicFileStream & operator=( BasicFileStream && _Right )
	{
		_Assign_rv( std::move( _Right ) );
		return *this;
	}

	void _Assign_rv( BasicFileStream && _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			this->swap( _Right );
		}
	}

	void swap( BasicFileStream & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			_Mybase::swap( _Right );
			_Filebuffer.swap( _Right._Filebuffer );
		}
	}

	BasicFileStream( const BasicFileStream & ) = delete;
	BasicFileStream & operator=( const BasicFileStream & ) = delete;

	virtual ~BasicFileStream() noexcept
	{
	}

	_Mysb * rdbuf() const
	{
		return ( _Mysb * ) &_Filebuffer;
	}

private:
	_Mysb _Filebuffer;
};

using FileStream = XE::BasicFileStream<char>;
using IFileStream = XE::BasicIFileStream<char>;
using OFileStream = XE::BasicOFileStream<char>;

END_XE_NAMESPACE

namespace std
{
	template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
	inline void swap( XE::BasicFileBuf<_Elem, _Traits, _Alloc> & _Left,
					  XE::BasicFileBuf<_Elem, _Traits, _Alloc> & _Right )
	{
		_Left.swap( _Right );
	}

	template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
	inline void swap( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left,
					  XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Right )
	{
		_Left.swap( _Right );
	}

	template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
	inline void swap( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left,
					  XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Right )
	{
		_Left.swap( _Right );
	}

	template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
	inline void swap( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left,
					  XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Right )
	{
		_Left.swap( _Right );
	}
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, bool & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, XE::int8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, XE::int16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, XE::int32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, XE::int64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, XE::uint8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, XE::uint16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, XE::uint32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, XE::uint64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, XE::float32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, XE::float64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicIFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicIFileStream<_Elem, _Traits, _Alloc> & _Left, std::string & _Right )
{
	std::string::size_type size;

	_Left >> size;

	_Right.resize( size );

	_Left.read( reinterpret_cast< _Elem * >( _Right.data() ), size / sizeof( _Elem ) );

	return _Left;
}


template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const bool & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::int8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::int16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::int32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::int64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::float32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::float64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicOFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicOFileStream<_Elem, _Traits, _Alloc> & _Left, const std::string & _Right )
{
	_Left << _Right.size();

	_Left.write( reinterpret_cast< const _Elem * >( _Right.c_str() ), _Right.size() / sizeof( _Elem ) );

	return _Left;
}


template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, bool & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, XE::int8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, XE::int16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, XE::int32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, XE::int64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, XE::uint8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, XE::uint16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, XE::uint32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, XE::uint64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, XE::float32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, XE::float64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator >>( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, std::string & _Right )
{
	std::string::size_type size;

	_Left >> size;

	_Right.resize( size );

	_Left.read( reinterpret_cast< _Elem * >( _Right.data() ), size / sizeof( _Elem ) );

	return _Left;
}


template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const bool & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::int8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::int16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::int32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::int64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::uint64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::float32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const XE::float64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits, class _Alloc>
XE::BasicFileStream<_Elem, _Traits, _Alloc> & operator <<( XE::BasicFileStream<_Elem, _Traits, _Alloc> & _Left, const std::string & _Right )
{
	_Left << _Right.size();

	_Left.write( reinterpret_cast< const _Elem * >( _Right.c_str() ), _Right.size() / sizeof( _Elem ) );

	return _Left;
}

#endif // FSTREAM_H__D5AC1F9D_7B65_44E8_8271_4C1C463616A4
