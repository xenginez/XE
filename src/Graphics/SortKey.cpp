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
	return
		layer < val.layer ||
		order < val.order ||
		blend < val.blend ||
		shader < val.shader ||
		texture < val.texture ||
		(
			blend == 1 ?
			( depth > val.depth ) :
			( depth < val.depth ) );
}

bool SortKey::operator!=( const SortKey & val ) const
{
	return key != val.key;
}

bool SortKey::operator==( const SortKey & val ) const
{
	return key == val.key;
}
