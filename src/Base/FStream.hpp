#ifndef FSTREAM_H__D5AC1F9D_7B65_44E8_8271_4C1C463616A4
#define FSTREAM_H__D5AC1F9D_7B65_44E8_8271_4C1C463616A4

#include "FileSystem.h"
#include <fstream>

BEG_XE_NAMESPACE

FileSystem::File * _Fiopen( const char *, std::ios_base::openmode, int );

template <class _Elem>
bool _Fgetc( _Elem & _Ch, FileSystem::File * _File )
{ 
	return FileSystem::read( &_Ch, sizeof( _Elem ), 1, _File ) == 1;
}

template <class _Elem>
bool _Fputc( _Elem _Ch, FileSystem::File * _File )
{ 
	return FileSystem::write( &_Ch, 1, sizeof( _Elem ), _File ) == sizeof( _Elem );
}

template <class _Elem>
bool _Ungetc( const _Elem &, FileSystem::File * )
{ 
	return false;
}

template <class _Elem, class _Traits = std::char_traits<_Elem>>
class BasicFileBuf : public std::basic_streambuf<_Elem, _Traits>
{ 
public:
	using _Mysb = std::basic_streambuf<_Elem, _Traits>;
	using _Cvt = std::codecvt<_Elem, char, typename _Traits::state_type>;

	BasicFileBuf() : _Mysb()
	{
		_Init( nullptr, _Newfl );
	}

	explicit BasicFileBuf( FileSystem::File * const _File ) : _Mysb()
	{ 
		_Init( _File, _Newfl );
	}

	virtual ~BasicFileBuf() noexcept
	{
		if( _Myfile )
		{
			_Reset_back(); 
		}

		if( _Closef )
		{
			close();
		}
	}

	using int_type = typename _Traits::int_type;
	using pos_type = typename _Traits::pos_type;
	using off_type = typename _Traits::off_type;

	BasicFileBuf( _Uninitialized ) : _Mysb( _Noinit )
	{
	}

	BasicFileBuf( BasicFileBuf && _Right )
	{
		_Init( _Right._Myfile, _Newfl ); 
		_Init( static_cast< FileSystem::File * >( nullptr ), _Closefl ); 
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
			close();
			this->swap( _Right );
		}
	}

	void swap( BasicFileBuf & _Right )
	{
		if( this != std::addressof( _Right ) )
		{
			FileSystem::File * _Myfile_sav = _Myfile;
			const _Cvt * _Pcvt_sav = _Pcvt;
			typename _Traits::state_type _State_sav = _State;
			bool _Wrotesome_sav = _Wrotesome;
			bool _Closef_sav = _Closef;
			bool _Set_eback_sav = _Mysb::eback() == &_Mychar;
			bool _Set_eback_live = _Mysb::gptr() == &_Mychar;

			_Elem * _Pfirst0 = _Mysb::pbase();
			_Elem * _Pnext0 = _Mysb::pptr();
			_Elem * _Pend = _Mysb::epptr();
			_Elem * _Gfirst0 = _Mysb::eback();
			_Elem * _Gnext0 = _Mysb::gptr();
			_Elem * _Gend = _Mysb::egptr();

			
			_Init( _Right._Myfile, _Right._Myfile ? _Openfl : _Newfl );
			_Mysb::setp( _Right.pbase(), _Right.pptr(), _Right.epptr() );
			if( _Right.eback() != &_Right._Mychar )
			{
				_Mysb::setg( _Right.eback(), _Right.gptr(), _Right.egptr() );
			}
			else if( _Right.gptr() != &_Right._Mychar )
			{
				_Mysb::setg( &_Mychar, &_Mychar + 1, &_Mychar + 1 );
			}
			else
			{
				_Mysb::setg( &_Mychar, &_Mychar, &_Mychar + 1 );
			}

			_Pcvt = _Right._Pcvt;
			_State = _Right._State;
			_Wrotesome = _Right._Wrotesome;
			_Closef = _Right._Closef;

			
			_Right._Init( _Myfile_sav, _Myfile_sav ? _Openfl : _Newfl );
			_Right.setp( _Pfirst0, _Pnext0, _Pend );
			if( !_Set_eback_sav )
			{
				_Right.setg( _Gfirst0, _Gnext0, _Gend );
			}
			else if( !_Set_eback_live )
			{
				_Right.setg( &_Right._Mychar, &_Right._Mychar + 1, &_Right._Mychar + 1 );
			}
			else
			{
				_Right.setg( &_Right._Mychar, &_Right._Mychar, &_Right._Mychar + 1 );
			}

			_Right._Pcvt = _Pcvt_sav;
			_Right._State = _State_sav;
			_Right._Wrotesome = _Wrotesome_sav;
			_Right._Closef = _Closef_sav;

			
			std::swap( _Set_eback, _Right._Set_eback );
			std::swap( _Set_egptr, _Right._Set_egptr );

			std::swap( _Mychar, _Right._Mychar );
			std::swap( _Mysb::_Plocale, _Right._Plocale );
		}
	}

	BasicFileBuf( const BasicFileBuf & ) = delete;
	BasicFileBuf & operator=( const BasicFileBuf & ) = delete;

	enum _Initfl
	{ 
		_Newfl,
		_Openfl,
		_Closefl
	};

	bool is_open() const
	{
		return static_cast< bool >( _Myfile );
	}

	BasicFileBuf * open( const char * _Filename, std::ios_base::openmode _Mode, int _Prot = std::ios_base::_Default_open_prot )
	{
		
		if( _Myfile )
		{
			return nullptr;
		}

		const auto _File = _Fiopen( _Filename, _Mode, _Prot );
		if( !_File )
		{
			return nullptr; 
		}

		_Init( _File, _Openfl );
		_Initcvt( std::use_facet<_Cvt>( _Mysb::getloc() ) );
		return this; 
	}

	BasicFileBuf * open( const string & _Str, std::ios_base::openmode _Mode, int _Prot = std::ios_base::_Default_open_prot )
	{
		
		return open( _Str.c_str(), _Mode, _Prot );
	}

	BasicFileBuf * close()
	{
		BasicFileBuf * _Ans;
		if( _Myfile )
		{ 
			_Ans = this;
			if( !_Endwrite() )
			{
				_Ans = nullptr;
			}

			if( FileSystem::close( _Myfile ) != 0 )
			{
				_Ans = nullptr;
			}
		}
		else
		{
			_Ans = nullptr;
		}

		_Init( nullptr, _Closefl );
		return _Ans;
	}

	virtual void _Lock() override
	{ 
		if( _Myfile )
		{
			FileSystem::lock( _Myfile );
		}
	}

	virtual void _Unlock() override
	{ 
		if( _Myfile )
		{
			FileSystem::unlock( _Myfile );
		}
	}

protected:
	virtual int_type overflow( int_type _Meta = _Traits::eof() ) override
	{ 
		if( _Traits::eq_int_type( _Traits::eof(), _Meta ) )
		{
			return _Traits::not_eof( _Meta ); 
		}

		if( _Mysb::pptr() && _Mysb::pptr() < _Mysb::epptr() )
		{ 
			*_Mysb::_Pninc() = _Traits::to_char_type( _Meta );
			return _Meta;
		}

		if( !_Myfile )
		{
			return _Traits::eof(); 
		}

		_Reset_back(); 
		if( !_Pcvt )
		{ 
			return _Fputc( _Traits::to_char_type( _Meta ), _Myfile ) ? _Meta : _Traits::eof();
		}

		
		constexpr std::size_t _Codecvt_temp_buf = 32;
		char _Str[_Codecvt_temp_buf];
		const _Elem _Ch = _Traits::to_char_type( _Meta );
		const _Elem * _Src;
		char * _Dest;
		switch( _Pcvt->out( _State, &_Ch, &_Ch + 1, _Src, _Str, _Str + _Codecvt_temp_buf,
							_Dest ) )
		{ 
		case std::codecvt_base::partial:
		case std::codecvt_base::ok:
		{ 
			const auto _Count = static_cast< std::size_t >( _Dest - _Str );
			if( 0 < _Count && _Count != static_cast< std::size_t >( FileSystem::write( _Str, 1, _Count, _Myfile ) ) )
			{
				return _Traits::eof(); 
			}

			_Wrotesome = true; 
			if( _Src != &_Ch )
			{
				return _Meta; 
			}

			return _Traits::eof(); 
		}

		case std::std::codecvt_base::noconv:
			
			return _Fputc( _Ch, _Myfile ) ? _Meta : _Traits::eof();

		default:
			return _Traits::eof(); 
		}
	}

	virtual int_type pbackfail( int_type _Meta = _Traits::eof() ) override
	{
		
		if( _Mysb::gptr() && _Mysb::eback() < _Mysb::gptr()
			&& ( _Traits::eq_int_type( _Traits::eof(), _Meta )
				 || _Traits::eq_int_type( _Traits::to_int_type( _Mysb::gptr()[-1] ),
										  _Meta ) ) )
		{ 
			_Mysb::_Gndec();
			return _Traits::not_eof( _Meta );
		}
		else if( !_Myfile || _Traits::eq_int_type( _Traits::eof(), _Meta ) )
		{
			return _Traits::eof(); 
		}
		else if( !_Pcvt && _Ungetc( _Traits::to_char_type( _Meta ), _Myfile ) )
		{
			return _Meta; 
		}
		else if( _Mysb::gptr() != &_Mychar )
		{ 
			_Mychar = _Traits::to_char_type( _Meta );
			_Set_back(); 
			return _Meta;
		}
		else
		{
			return _Traits::eof(); 
		}
	}

	virtual int_type underflow() override
	{ 
		int_type _Meta;
		if( _Mysb::gptr() && _Mysb::gptr() < _Mysb::egptr() )
		{
			return _Traits::to_int_type( *_Mysb::gptr() ); 
		}
		else if( _Traits::eq_int_type( _Traits::eof(), _Meta = uflow() ) )
		{
			return _Meta; 
		}
		else
		{ 
			pbackfail( _Meta );
			return _Meta;
		}
	}

	virtual int_type uflow() override
	{ 
		if( _Mysb::gptr() && _Mysb::gptr() < _Mysb::egptr() )
		{
			return _Traits::to_int_type( *_Mysb::_Gninc() ); 
		}

		if( !_Myfile )
		{
			return _Traits::eof(); 
		}

		_Reset_back(); 
		if( !_Pcvt )
		{ 
			_Elem _Ch;
			return _Fgetc( _Ch, _Myfile ) ? _Traits::to_int_type( _Ch ) : _Traits::eof();
		}

		
		string _Str;

		for( ;;)
		{ 
			const char * _Src;
			int _Meta = FileSystem::getc( _Myfile );

			if( _Meta == EOF )
			{
				return _Traits::eof(); 
			}

			_Str.push_back( static_cast< char >( _Meta ) ); 

			_Elem _Ch;
			_Elem * _Dest;
			switch( _Pcvt->in( _State, _Str.data(), _Str.data() + _Str.size(), _Src, &_Ch, &_Ch + 1,
							   _Dest ) )
			{ 
			case std::codecvt_base::partial:
			case std::codecvt_base::ok:
				if( _Dest != &_Ch )
				{ 
					auto _Nleft = _Str.data() + _Str.size() - _Src;
					while( 0 < _Nleft )
					{
						FileSystem::ungetc( _Src[--_Nleft], _Myfile );
					}

					return _Traits::to_int_type( _Ch );
				}

				_Str.erase( 0, static_cast< std::size_t >( _Src - _Str.data() ) ); 
				break;

			case std::codecvt_base::noconv:
				
				return static_cast< int_type >( _Str.front() );

			default:
				return _Traits::eof(); 
			}
		}
	}

	virtual std::streamsize xsgetn( _Elem * _Ptr, std::streamsize _Count ) override
	{
		
		if constexpr( sizeof( _Elem ) == 1 )
		{
			if( _Count <= 0 )
			{
				return 0;
			}

			if( _Pcvt )
			{ 
				return _Mysb::xsgetn( _Ptr, _Count );
			}

			
			auto _Count_s = static_cast< std::size_t >( _Count );
			const auto _Start_count = _Count;
			const auto _Available = static_cast< std::size_t >( _Mysb::_Gnavail() );
			if( 0 < _Available )
			{ 
				const auto _Read_size = _Min_value( _Count_s, _Available );
				_Traits::copy( _Ptr, _Mysb::gptr(), _Read_size );
				_Ptr += _Read_size;
				_Count_s -= _Read_size;
				_Mysb::gbump( static_cast< int >( _Read_size ) );
			}

			if( _Myfile )
			{ 
				_Reset_back(); 
				
				
				constexpr std::size_t _Read_size = 4095; 
				while( _Read_size < _Count_s )
				{
					const auto _Actual_read = FileSystem::read( _Ptr, sizeof( _Elem ), _Read_size, _Myfile );
					_Ptr += _Actual_read;
					_Count_s -= _Actual_read;
					if( _Actual_read != _Read_size )
					{
						return static_cast< std::streamsize >( _Start_count - _Count_s );
					}
				}

				if( 0 < _Count_s )
				{
					_Count_s -= FileSystem::read( _Ptr, sizeof( _Elem ), _Count_s, _Myfile );
				}
			}

			return static_cast< std::streamsize >( _Start_count - _Count_s );
		}
		else
		{ 
			return _Mysb::xsgetn( _Ptr, _Count );
		}
	}

	virtual std::streamsize xsputn( const _Elem * _Ptr, std::streamsize _Count ) override
	{
		
		if
			constexpr( sizeof( _Elem ) == 1 )
		{
			if( _Pcvt )
			{ 
				return _Mysb::xsputn( _Ptr, _Count );
			}

			const std::streamsize _Start_count = _Count;
			std::streamsize _Size = _Mysb::_Pnavail();
			if( 0 < _Count && 0 < _Size )
			{ 
				if( _Count < _Size )
				{
					_Size = _Count;
				}

				_Traits::copy( _Mysb::pptr(), _Ptr, static_cast< std::size_t >( _Size ) );
				_Ptr += _Size;
				_Count -= _Size;
				_Mysb::pbump( static_cast< int >( _Size ) );
			}

			if( 0 < _Count && _Myfile )
			{ 
				_Count -= FileSystem::write( _Ptr, sizeof( _Elem ), static_cast< std::size_t >( _Count ), _Myfile );
			}

			return _Start_count - _Count;
		}
		else
		{ 
			return _Mysb::xsputn( _Ptr, _Count );
		}
	}

	virtual pos_type seekoff( off_type _Off, std::ios_base::seekdir _Way,
												 std::ios_base::openmode = std::ios_base::in | std::ios_base::out ) override
	{ 
		fpos_t _Fileposition;

		if( _Mysb::gptr() == &_Mychar 
			&& _Way == std::ios_base::cur 
			&& !_Pcvt )
		{ 
			_Off -= static_cast< off_type >( sizeof( _Elem ) ); 
		}

		if( !_Myfile || !_Endwrite()
			|| ( ( _Off != 0 || _Way != std::ios_base::cur ) && FileSystem::seek( _Myfile, _Off, _Way ) != 0 )
			|| FileSystem::getpos( _Myfile, &_Fileposition ) != 0 )
		{
			return pos_type( -1 ); 
		}

		_Reset_back(); 
		return pos_type( _State, _Fileposition ); 
	}

	virtual pos_type seekpos(
		pos_type _Pos, std::ios_base::openmode = std::ios_base::in | std::ios_base::out ) override
	{
		
		off_type _Off = static_cast< off_type >( _Pos );

		if( !_Myfile || !_Endwrite() || FileSystem::setpos( _Myfile, &_Off ) != 0 )
		{
			return pos_type( -1 ); 
		}

		_State = _Pos.state();
		_Reset_back(); 
		return pos_type( _State, _Off ); 
	}

	virtual _Mysb * setbuf( _Elem * _Buffer, std::streamsize _Count ) override
	{ 
		int _Mode;
		if( !_Buffer && _Count == 0 )
		{
			_Mode = _IONBF;
		}
		else
		{
			_Mode = _IOFBF;
		}

		const std::size_t _Size = static_cast< std::size_t >( _Count ) * sizeof( _Elem );

		if( !_Myfile || FileSystem::setvbuf( _Myfile, reinterpret_cast< char * >( _Buffer ), _Mode, _Size ) != 0 )
		{
			return nullptr; 
		}

		
		_Init( _Myfile, _Openfl );
		return this;
	}

	virtual int sync() override
	{ 
		if( !_Myfile || _Traits::eq_int_type( _Traits::eof(), overflow() ) || 0 <= FileSystem::flush( _Myfile ) )
		{
			return 0;
		}

		return -1;
	}

	virtual void imbue( const locale & _Loc ) override
	{
		
		_Initcvt( std::use_facet<_Cvt>( _Loc ) );
	}

	void _Init( FileSystem::File * _File, _Initfl _Which )
	{ 
		using _State_type = typename _Traits::state_type;

		static _State_type _Stinit; 

		_Closef = _Which == _Openfl;
		_Wrotesome = false;

		_Mysb::_Init(); 

		if( _File && sizeof( _Elem ) == 1 )
		{ 
			_Elem ** _Pb = nullptr;
			_Elem ** _Pn = nullptr;
			int * _Nr = nullptr;

			::_get_stream_buffer_pointers(
				_File, reinterpret_cast< char *** >( &_Pb ), reinterpret_cast< char *** >( &_Pn ), &_Nr );
			int * _Nw = _Nr;

			_Mysb::_Init( _Pb, _Pn, _Nr, _Pb, _Pn, _Nw );
		}

		_Myfile = _File;
		_State = _Stinit;
		_Pcvt = nullptr; 
	}

	bool _Endwrite()
	{ 
		if( !_Pcvt || !_Wrotesome )
		{
			return true;
		}

		
		if( _Traits::eq_int_type( _Traits::eof(), overflow() ) )
		{
			return false;
		}

		constexpr std::size_t _Codecvt_temp_buf = 32;
		char _Str[_Codecvt_temp_buf];
		char * _Dest;
		switch( _Pcvt->unshift( _State, _Str, _Str + _Codecvt_temp_buf, _Dest ) )
		{ 
		case std::codecvt_base::ok:
			_Wrotesome = false; 

		case std::codecvt_base::partial: 
		{ 
			const auto _Count = static_cast< std::size_t >( _Dest - _Str );
			if( 0 < _Count && _Count != static_cast< std::size_t >( FileSystem::write( _Str, 1, _Count, _Myfile ) ) )
			{
				return false; 
			}

			return !_Wrotesome;
		}

		case std::codecvt_base::noconv:
			_Wrotesome = false; 
			return true; 

		default:
			return false; 
		}
	}

	void _Initcvt( const _Cvt & _Newcvt )
	{ 
		if( _Newcvt.always_noconv() )
		{
			_Pcvt = nullptr; 
		}
		else
		{ 
			_Pcvt = std::addressof( _Newcvt );
			_Mysb::_Init(); 
		}
	}

private:
	const _Cvt * _Pcvt; 
	_Elem _Mychar; 
	bool _Wrotesome; 
	typename _Traits::state_type _State; 
	bool _Closef; 
	FileSystem::File * _Myfile; 

	void _Reset_back()
	{ 
		if( _Mysb::eback() == &_Mychar )
		{
			_Mysb::setg( _Set_eback, _Set_eback, _Set_egptr );
		}
	}

	void _Set_back()
	{ 
		if( _Mysb::eback() != &_Mychar )
		{ 
			_Set_eback = _Mysb::eback();
			_Set_egptr = _Mysb::egptr();
		}
		_Mysb::setg( &_Mychar, &_Mychar, &_Mychar + 1 );
	}

	_Elem * _Set_eback; 
	_Elem * _Set_egptr; 
};

template <class _Elem, class _Traits = std::char_traits<_Elem>>
class BasicIFileStream : public std::basic_istream<_Elem, _Traits>
{
public:
	using _Mybase = std::basic_istream<_Elem, _Traits>;
	using _Mysb = BasicFileBuf<_Elem, _Traits>;

	explicit BasicIFileStream( std::std::ios_base::openmode _Mode = std::std::ios_base::in )
		: _Mybase( &_Filebuffer ), _Filebuffer( _Mode | std::std::ios_base::in )
	{
	}

	explicit BasicIFileStream( const std::string & _File, std::std::ios_base::openmode _Mode = std::std::ios_base::in )
		: _Mybase( &_Filebuffer ), _Filebuffer( _File, _Mode | std::std::ios_base::in )
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

template <class _Elem, class _Traits = std::char_traits<_Elem>>
class BasicOFileStream : public std::basic_ostream<_Elem, _Traits>
{
public:
	using _Mybase = std::basic_ostream<_Elem, _Traits>;
	using _Mysb = BasicFileBuf<_Elem, _Traits>;

	explicit BasicOFileStream( std::std::ios_base::openmode _Mode = std::std::ios_base::out )
		: _Mybase( &_Filebuffer ), _Filebuffer( _Mode | std::std::ios_base::out )
	{
	}

	explicit BasicOFileStream( const std::string & _File, std::std::ios_base::openmode _Mode = std::std::ios_base::out )
		: _Mybase( &_Filebuffer ),
		_Filebuffer( _File, _Mode | std::std::ios_base::out )
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

template <class _Elem, class _Traits = std::char_traits<_Elem>>
class BasicFileStream : public std::basic_iostream<_Elem, _Traits>
{
public:
	using _Mybase = std::basic_iostream<_Elem, _Traits>;
	using char_type = _Elem;
	using traits_type = _Traits;
	using int_type = typename _Traits::int_type;
	using pos_type = typename _Traits::pos_type;
	using off_type = typename _Traits::off_type;
	using _Mysb = BasicFileBuf<_Elem, _Traits>;

	explicit BasicFileStream( std::std::ios_base::openmode _Mode = std::std::ios_base::in | std::std::ios_base::out )
		: _Mybase( &_Filebuffer ), _Filebuffer( _Mode )
	{
	}

	explicit BasicFileStream( const std::string & _File, std::std::ios_base::openmode _Mode = std::std::ios_base::in | std::std::ios_base::out )
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
	template <class _Elem, class _Traits = std::char_traits<_Elem>>
	inline void swap( XE::BasicFileBuf<_Elem, _Traits> & _Left,
					  XE::BasicFileBuf<_Elem, _Traits> & _Right )
	{
		_Left.swap( _Right );
	}

	template <class _Elem, class _Traits = std::char_traits<_Elem>>
	inline void swap( XE::BasicIFileStream<_Elem, _Traits> & _Left,
					  XE::BasicIFileStream<_Elem, _Traits> & _Right )
	{
		_Left.swap( _Right );
	}

	template <class _Elem, class _Traits = std::char_traits<_Elem>>
	inline void swap( XE::BasicOFileStream<_Elem, _Traits> & _Left,
					  XE::BasicOFileStream<_Elem, _Traits> & _Right )
	{
		_Left.swap( _Right );
	}

	template <class _Elem, class _Traits = std::char_traits<_Elem>>
	inline void swap( XE::BasicFileStream<_Elem, _Traits> & _Left,
					  XE::BasicFileStream<_Elem, _Traits> & _Right )
	{
		_Left.swap( _Right );
	}
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, bool & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, XE::int8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, XE::int16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, XE::int32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, XE::int64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, XE::uint8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, XE::uint16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, XE::uint32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, XE::uint64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, XE::float32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, XE::float64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicIFileStream<_Elem, _Traits> & operator >>( XE::BasicIFileStream<_Elem, _Traits> & _Left, std::string & _Right )
{
	std::string::std::size_type size;

	_Left >> size;

	_Right.resize( size );

	_Left.read( reinterpret_cast< _Elem * >( _Right.data() ), size / sizeof( _Elem ) );

	return _Left;
}


template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const bool & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const XE::int8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const XE::int16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const XE::int32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const XE::int64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const XE::uint8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const XE::uint16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const XE::uint32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const XE::uint64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const XE::float32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const XE::float64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicOFileStream<_Elem, _Traits> & operator <<( XE::BasicOFileStream<_Elem, _Traits> & _Left, const std::string & _Right )
{
	_Left << _Right.size();

	_Left.write( reinterpret_cast< const _Elem * >( _Right.c_str() ), _Right.size() / sizeof( _Elem ) );

	return _Left;
}


template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, bool & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, XE::int8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, XE::int16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, XE::int32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, XE::int64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, XE::uint8 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, XE::uint16 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, XE::uint32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, XE::uint64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, XE::float32 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, XE::float64 & _Right )
{
	_Left.read( reinterpret_cast< _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator >>( XE::BasicFileStream<_Elem, _Traits> & _Left, std::string & _Right )
{
	std::string::std::size_type size;

	_Left >> size;

	_Right.resize( size );

	_Left.read( reinterpret_cast< _Elem * >( _Right.data() ), size / sizeof( _Elem ) );

	return _Left;
}


template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const bool & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( bool ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const XE::int8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int8 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const XE::int16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int16 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const XE::int32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const XE::int64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::int64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const XE::uint8 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint8 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const XE::uint16 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint16 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const XE::uint32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const XE::uint64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::uint64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const XE::float32 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float32 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const XE::float64 & _Right )
{
	_Left.write( reinterpret_cast< const _Elem * >( &_Right ), sizeof( XE::float64 ) );

	return _Left;
}

template <class _Elem, class _Traits>
XE::BasicFileStream<_Elem, _Traits> & operator <<( XE::BasicFileStream<_Elem, _Traits> & _Left, const std::string & _Right )
{
	_Left << _Right.size();

	_Left.write( reinterpret_cast< const _Elem * >( _Right.c_str() ), _Right.size() / sizeof( _Elem ) );

	return _Left;
}

#endif 
