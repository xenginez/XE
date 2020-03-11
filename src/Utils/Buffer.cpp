#include "Buffer.h"

USING_XE

IMPLEMENT_META( Buffer )

Buffer::Buffer()
{

}

Buffer::~Buffer()
{

}

void Buffer::push_back( bool val )
{
	XE::Array<char>::push_back( val ? 1 : 0 );
}

void Buffer::push_back( XE::int8 val )
{
	XE::Array<char>::push_back( ( char )val );
}

void Buffer::push_back( XE::int16 val )
{
	union _union
	{
		struct
		{
			char x1;
			char x2;
		};

		XE::int16 x;
	};

	_union un;

	un.x = val;

	XE::Array<char>::push_back( un.x1 );
	XE::Array<char>::push_back( un.x2 );
}

void Buffer::push_back( XE::int32 val )
{
	union _union
	{
		struct
		{
			char x1;
			char x2;
			char x3;
			char x4;
		};

		XE::int32 x;
	};

	_union un;

	un.x = val;

	XE::Array<char>::push_back( un.x1 );
	XE::Array<char>::push_back( un.x2 );
	XE::Array<char>::push_back( un.x3 );
	XE::Array<char>::push_back( un.x4 );
}

void Buffer::push_back( XE::int64 val )
{
	union _union
	{
		struct
		{
			char x1;
			char x2;
			char x3;
			char x4;
			char x5;
			char x6;
			char x7;
			char x8;
		};

		XE::int64 x;
	};

	_union un;

	un.x = val;

	XE::Array<char>::push_back( un.x1 );
	XE::Array<char>::push_back( un.x2 );
	XE::Array<char>::push_back( un.x3 );
	XE::Array<char>::push_back( un.x4 );
	XE::Array<char>::push_back( un.x5 );
	XE::Array<char>::push_back( un.x6 );
	XE::Array<char>::push_back( un.x7 );
	XE::Array<char>::push_back( un.x8 );
}

void Buffer::push_back( XE::uint8 val )
{
	XE::Array<char>::push_back( ( char )val );
}

void Buffer::push_back( XE::uint16 val )
{
	union _union
	{
		struct
		{
			char x1;
			char x2;
		};

		XE::uint16 x;
	};

	_union un;

	un.x = val;

	XE::Array<char>::push_back( un.x1 );
	XE::Array<char>::push_back( un.x2 );
}

void Buffer::push_back( XE::uint32 val )
{
	union _union
	{
		struct
		{
			char x1;
			char x2;
			char x3;
			char x4;
		};

		XE::uint32 x;
	};

	_union un;

	un.x = val;

	XE::Array<char>::push_back( un.x1 );
	XE::Array<char>::push_back( un.x2 );
	XE::Array<char>::push_back( un.x3 );
	XE::Array<char>::push_back( un.x4 );
}

void Buffer::push_back( XE::uint64 val )
{
	union _union
	{
		struct
		{
			char x1;
			char x2;
			char x3;
			char x4;
			char x5;
			char x6;
			char x7;
			char x8;
		};

		XE::uint64 x;
	};

	_union un;

	un.x = val;

	XE::Array<char>::push_back( un.x1 );
	XE::Array<char>::push_back( un.x2 );
	XE::Array<char>::push_back( un.x3 );
	XE::Array<char>::push_back( un.x4 );
	XE::Array<char>::push_back( un.x5 );
	XE::Array<char>::push_back( un.x6 );
	XE::Array<char>::push_back( un.x7 );
	XE::Array<char>::push_back( un.x8 );
}

void Buffer::push_back( XE::float32 val )
{
	union _union
	{
		struct
		{
			char x1;
			char x2;
			char x3;
			char x4;
		};

		XE::float32 x;
	};

	_union un;

	un.x = val;

	XE::Array<char>::push_back( un.x1 );
	XE::Array<char>::push_back( un.x2 );
	XE::Array<char>::push_back( un.x3 );
	XE::Array<char>::push_back( un.x4 );
}

void Buffer::push_back( XE::float64 val )
{
	union _union
	{
		struct
		{
			char x1;
			char x2;
			char x3;
			char x4;
			char x5;
			char x6;
			char x7;
			char x8;
		};

		XE::float64 x;
	};

	_union un;

	un.x = val;

	XE::Array<char>::push_back( un.x1 );
	XE::Array<char>::push_back( un.x2 );
	XE::Array<char>::push_back( un.x3 );
	XE::Array<char>::push_back( un.x4 );
	XE::Array<char>::push_back( un.x5 );
	XE::Array<char>::push_back( un.x6 );
	XE::Array<char>::push_back( un.x7 );
	XE::Array<char>::push_back( un.x8 );
}

void XE::Buffer::Wirte( const char * ptr, XE::uint64 size )
{
	XE::Array<char>::insert( end(), ptr, ptr + size );
}

XE::memory_view Buffer::GetView() const
{
	return XE::memory_view( this->data(), this->size() );
}
