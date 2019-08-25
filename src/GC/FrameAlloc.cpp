#include "FrameAlloc.h"

USING_XE

struct XE::FrameAlloc::Private
{
	std::list< std::pair<std::thread::id, LocalThreadData * > > _Data;
};

struct XE::FrameAlloc::LocalThreadData
{
	LocalThreadData()
	{
		FrameAlloc::RegisterLocalThreadData( this );
	}

	~LocalThreadData()
	{
		clear();
		FrameAlloc::UnregisterLocalThreadData( this );
	}

	void * allocate( XE::uint64 size )
	{
		for( auto & data : Datas )
		{
			if( XE::uint64( data._end - data._cur ) >= size )
			{
				void * p = data._cur;
				data._cur += size;
				return p;
			}
		}

		capacity( size );

		void * p = Datas.back()._cur;
		Datas.back()._cur += size;
		return p;
	}

	void capacity( XE::uint64 size )
	{
		size = std::max( size, ( XE::uint64 )MBYTE( 2 ) );

		Datas.emplace_back( Data( size ) );
	}

	void reset()
	{
		Datas.resize( 1 );
		Datas.front()._cur = Datas.front()._beg;
	}

	void clear()
	{
		Datas.clear();
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

	std::list<Data> Datas;
};

XE::FrameAlloc::FrameAlloc()
	:_p( new Private )
{

}

XE::FrameAlloc::~FrameAlloc()
{
	delete _p;
}

void * XE::FrameAlloc::Allocate( const XE::uint64 _Count )
{
	return GetLocalThreadData()->allocate( _Count );
}

void XE::FrameAlloc::Reset()
{
	GetLocalThreadData()->reset();
}

XE::FrameAlloc::LocalThreadData * XE::FrameAlloc::GetLocalThreadData()
{
	thread_local XE::FrameAlloc::LocalThreadData data;
	return &data;
}

void XE::FrameAlloc::Clear()
{
	_P();

	for( auto data : _p->_Data )
	{
		data.second->clear();
	}
}

void XE::FrameAlloc::RegisterLocalThreadData( XE::FrameAlloc::LocalThreadData * val )
{
	_P();

	_p->_Data.push_back( { std::this_thread::get_id(), val } );
}

void XE::FrameAlloc::UnregisterLocalThreadData( XE::FrameAlloc::LocalThreadData * val )
{
	_P();

	for( auto it = _p->_Data.begin(); it != _p->_Data.end(); ++it )
	{
		if( it->second == val )
		{
			_p->_Data.erase( it );
			return;
		}
	}
}
