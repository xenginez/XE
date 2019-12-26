#include "Buffer.h"

USING_XE

IMPLEMENT_META( Buffer )

Buffer::Buffer()
{

}

Buffer::~Buffer()
{

}

void Buffer::push_back( std::byte val )
{
	XE::Array<std::byte>::push_back( val );
}

void Buffer::push_back( XE::int8 val )
{
	XE::Array<std::byte>::push_back( ( std::byte )val );
}

void Buffer::push_back( XE::int16 val )
{
	union _union
	{
		struct
		{
			std::byte x1;
			std::byte x2;
		};

		XE::int16 x;
	};

	_union un;

	un.x = val;

	XE::Array<std::byte>::push_back( un.x1 );
	XE::Array<std::byte>::push_back( un.x2 );
}

void Buffer::push_back( XE::int32 val )
{
	union _union
	{
		struct
		{
			std::byte x1;
			std::byte x2;
			std::byte x3;
			std::byte x4;
		};

		XE::int32 x;
	};

	_union un;

	un.x = val;

	XE::Array<std::byte>::push_back( un.x1 );
	XE::Array<std::byte>::push_back( un.x2 );
	XE::Array<std::byte>::push_back( un.x3 );
	XE::Array<std::byte>::push_back( un.x4 );
}

void Buffer::push_back( XE::int64 val )
{
	union _union
	{
		struct
		{
			std::byte x1;
			std::byte x2;
			std::byte x3;
			std::byte x4;
			std::byte x5;
			std::byte x6;
			std::byte x7;
			std::byte x8;
		};

		XE::int64 x;
	};

	_union un;

	un.x = val;

	XE::Array<std::byte>::push_back( un.x1 );
	XE::Array<std::byte>::push_back( un.x2 );
	XE::Array<std::byte>::push_back( un.x3 );
	XE::Array<std::byte>::push_back( un.x4 );
	XE::Array<std::byte>::push_back( un.x5 );
	XE::Array<std::byte>::push_back( un.x6 );
	XE::Array<std::byte>::push_back( un.x7 );
	XE::Array<std::byte>::push_back( un.x8 );
}

void Buffer::push_back( XE::uint8 val )
{
	XE::Array<std::byte>::push_back( ( std::byte )val );
}

void Buffer::push_back( XE::uint16 val )
{
	union _union
	{
		struct
		{
			std::byte x1;
			std::byte x2;
		};

		XE::uint16 x;
	};

	_union un;

	un.x = val;

	XE::Array<std::byte>::push_back( un.x1 );
	XE::Array<std::byte>::push_back( un.x2 );
}

void Buffer::push_back( XE::uint32 val )
{
	union _union
	{
		struct
		{
			std::byte x1;
			std::byte x2;
			std::byte x3;
			std::byte x4;
		};

		XE::uint32 x;
	};

	_union un;

	un.x = val;

	XE::Array<std::byte>::push_back( un.x1 );
	XE::Array<std::byte>::push_back( un.x2 );
	XE::Array<std::byte>::push_back( un.x3 );
	XE::Array<std::byte>::push_back( un.x4 );
}

void Buffer::push_back( XE::uint64 val )
{
	union _union
	{
		struct
		{
			std::byte x1;
			std::byte x2;
			std::byte x3;
			std::byte x4;
			std::byte x5;
			std::byte x6;
			std::byte x7;
			std::byte x8;
		};

		XE::uint64 x;
	};

	_union un;

	un.x = val;

	XE::Array<std::byte>::push_back( un.x1 );
	XE::Array<std::byte>::push_back( un.x2 );
	XE::Array<std::byte>::push_back( un.x3 );
	XE::Array<std::byte>::push_back( un.x4 );
	XE::Array<std::byte>::push_back( un.x5 );
	XE::Array<std::byte>::push_back( un.x6 );
	XE::Array<std::byte>::push_back( un.x7 );
	XE::Array<std::byte>::push_back( un.x8 );
}

void Buffer::push_back( XE::float32 val )
{
	union _union
	{
		struct
		{
			std::byte x1;
			std::byte x2;
			std::byte x3;
			std::byte x4;
		};

		XE::float32 x;
	};

	_union un;

	un.x = val;

	XE::Array<std::byte>::push_back( un.x1 );
	XE::Array<std::byte>::push_back( un.x2 );
	XE::Array<std::byte>::push_back( un.x3 );
	XE::Array<std::byte>::push_back( un.x4 );
}

void Buffer::push_back( XE::float64 val )
{
	union _union
	{
		struct
		{
			std::byte x1;
			std::byte x2;
			std::byte x3;
			std::byte x4;
			std::byte x5;
			std::byte x6;
			std::byte x7;
			std::byte x8;
		};

		XE::float64 x;
	};

	_union un;

	un.x = val;

	XE::Array<std::byte>::push_back( un.x1 );
	XE::Array<std::byte>::push_back( un.x2 );
	XE::Array<std::byte>::push_back( un.x3 );
	XE::Array<std::byte>::push_back( un.x4 );
	XE::Array<std::byte>::push_back( un.x5 );
	XE::Array<std::byte>::push_back( un.x6 );
	XE::Array<std::byte>::push_back( un.x7 );
	XE::Array<std::byte>::push_back( un.x8 );
}
