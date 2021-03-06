#include "StringUtils.h"

std::vector<std::string> XE::StringUtils::Split( const std::string & src, const std::string & sep )
{
	std::regex re{ sep };
	return { std::sregex_token_iterator( src.begin(), src.end(), re, -1 ), std::sregex_token_iterator() };
}

std::string XE::StringUtils::Replace( const std::string & src, const std::string & sep, const std::string & dst )
{
	std::regex regex( sep );

	return std::regex_replace( src, regex, dst );
}
