#include "LocalizationService.h"

#include <fstream>

BEG_META( XE::LocalizationService )
END_META()

struct XE::LocalizationService::Private
{
	XE::Language _Language;
	std::array< XE::UnorderedMap<XE::String, XE::String>, ( XE::uint64 )XE::Language::UNKNOWN > _Maps;
};

XE::LocalizationService::LocalizationService()
	:_p( new Private )
{

}

XE::LocalizationService::~LocalizationService()
{
	delete _p;
}

void XE::LocalizationService::Prepare()
{
	String LanguageName = GetFramework()->GetString( "System/Language" );

	if( LanguageName == "" )
	{
		_p->_Language = GetFramework()->GetSystemLanguage();
	}
	else
	{
		_p->_Language = ( Language ) ( XE_EnumID< Language >::Get()->FindValue( LanguageName ).Value<Language>() );
	}

	LoadLocalized();
}

bool XE::LocalizationService::Startup()
{
	return true;
}

void XE::LocalizationService::Update()
{

}

void XE::LocalizationService::Clearup()
{
	for( auto & i : _p->_Maps )
	{
		i.clear();
	}
}

XE::Language XE::LocalizationService::GetCurrentLanguage() const
{
	return _p->_Language;
}

void XE::LocalizationService::SetCurrentLanguage( XE::Language val )
{
	_p->_Language = val;

	GetFramework()->SetString( "System/Language", ::XE_EnumID<Language>::Get()->FindName( (XE::int64)_p->_Language ) );
}

const XE::String & XE::LocalizationService::LocalizedString( const XE::String & key, const XE::String& defualt /*= ""*/ ) const
{
	auto it = _p->_Maps[( XE::uint64 )_p->_Language].find( key );

	if ( it != _p->_Maps[( XE::uint64 )_p->_Language].end() && it->second != "" )
	{
		return it->second;
	}

	return defualt;
}

void XE::LocalizationService::LoadLocalized()
{
	std::string path = ( GetFramework()->GetUserDataPath() / LANGUAGE_FILE_NAME ).u8string();

	std::ifstream ifs( path );

	if ( ifs.is_open() )
	{
		std::string buf( 2048, 0 );

		ifs.getline( buf.data(), 2048 );
		
		auto title = StringUtils::Split( buf, "," );
		title.erase( title.begin() );

		XE::Array< XE::uint64 > indexs( XE::MemoryResource::GetStackMemoryResource() );
		for( const auto & i : title )
		{
			indexs.push_back( ( XE::uint64 )::XE_EnumID<Language>::Get()->FindValue( i ).Value< XE::Language >() );
		}

		while ( !ifs.eof() )
		{
			buf[0] = 0;
			ifs.getline( buf.data(), 2048 );

			std::vector<std::string> list = StringUtils::Split( buf, "," );

			for( int i = 1; i < list.size(); ++i )
			{
				_p->_Maps[indexs[i]].insert( { list[0], list[i] } );
			}
		}
	}
}
