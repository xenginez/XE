#include "StringUtils.h"

USING_XE

std::vector<std::string> XE::StringUtils::Split( const std::string& src, const std::string& sep )
{
	std::vector<std::string> ret;

	std::regex regex( src );
	std::sregex_token_iterator p( sep.cbegin(), sep.cend(), regex, -1 );
	std::sregex_token_iterator end;

	for ( ; p != end; ++p )
	{
		ret.push_back( p->str() );
	}

	return ret;
}
