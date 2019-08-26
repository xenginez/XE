#include "FrameAlloc.h"

USING_XE

struct XE::FrameAlloc::Private
{
	Private()
		:Mask( 1 ), Count( 0xFE )
	{
	}

	~Private()
	{

	}

	void * allocate( XE::uint64 size )
	{
		Count |= 1;

		std::list<Data> * data_list = nullptr;

		if( Mask == 1 )
		{
			data_list = &Data1;
		}
		else
		{
			data_list = &Data2;
		}

		for( auto & data : *data_list )
		{
			if( XE::uint64( data._end - data._cur ) >= size )
			{
				void * p = data._cur;
				data._cur += size;
				return p;
			}
		}

		capacity( size );

		void * p = data_list->back()._cur;
		data_list->back()._cur += size;
		return p;
	}

	void capacity( XE::uint64 size )
	{
		size = std::max( size, ( XE::uint64 )MBYTE( 1 ) );

		Mask == 1 ? Data1.emplace_back( Data( size ) ) : Data2.emplace_back( Data( size ) );
	}

	void reset()
	{
		if( ( Count & 1 ) == 0 )
		{
			Count <<= 1;
		}

		if( Count == 0 )
		{
			Count = 0xFE;
			Data1.resize( 1 );
			Data2.resize( 1 );
		}

		Mask = ( Mask == 1 ? 2 : 1 );

		if( Mask == 1 )
		{
			for( auto & data : Data1 )
			{
				data._cur = data._beg;
			}
		}
		else
		{
			for( auto & data : Data2 )
			{
				data._cur = data._beg;
			}
		}
	}

	struct Data
	{
		Data()
		{
			_beg = nullptr;
			_cur = nullptr;
			_end = nullptr;
		}

		Data( XE::uint64 size )
		{
			_beg = ( XE::uint8 * )Alloc::Allocate( size );
			_cur = _beg;
			_end = _beg + ( size );
		}

		~Data()
		{
			if( _beg )
			{
				Alloc::Deallocate( _beg );
			}
		}

		XE::uint8 * _beg;
		XE::uint8 * _cur;
		XE::uint8 * _end;
	};

	XE::uint8 Mask;
	XE::uint8 Count;
	std::list<Data> Data1;
	std::list<Data> Data2;
};

XE::FrameAlloc::FrameAlloc()
{
}

XE::FrameAlloc::~FrameAlloc()
{
}

void * XE::FrameAlloc::Allocate( const XE::uint64 _Count )
{
	return GetPrivate()->allocate( _Count );
}

void XE::FrameAlloc::Reset()
{
	GetPrivate()->reset();
}

XE::FrameAlloc::Private * XE::FrameAlloc::GetPrivate()
{
	thread_local XE::FrameAlloc::Private data;
	return &data;
}
