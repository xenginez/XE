#include "SortKey.h"

USING_XE

SortKey::SortKey()
	:key( 0 )
{

}

SortKey::SortKey( XE::uint64 val )
	: key( val )
{

}

bool SortKey::operator<( const SortKey & val ) const
{
	if( layer == RenderLayer::TRANSPARENT )
	{
		return
			layer < val.layer ||
			order < val.order ||
			depth > val.depth ||
			state < val.state;
	}

	return
		layer < val.layer ||
		order < val.order ||
		state < val.state ||
		depth < val.depth;
}

bool SortKey::operator!=( const SortKey & val ) const
{
	return key != val.key;
}

bool SortKey::operator==( const SortKey & val ) const
{
	return key == val.key;
}
