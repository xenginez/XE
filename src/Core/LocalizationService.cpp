#include "LocalizationService.h"

#include <fstream>

BEG_META( XE::LocalizationService )
END_META()

struct XE::LocalizationService::Private
{
	XE::Language _Language;
	XE::UnorderedMap<XE::String, XE::String> _Maps;
};

XE::LocalizationService::LocalizationService()
	:_p( new Private )
{

}

XE::LocalizationService::~LocalizationService()
{
	delete _p;
}

bool XE::LocalizationService::Startup()
{
	String LanguageName = GetFramework()->GetString( "System/Language" );

	if ( LanguageName == "" )
	{
		_p->_Language = GetFramework()->GetSystemLanguage();
	}
	else
	{
		_p->_Language = (Language)( EnumID<Language>::Get()->FindValue( LanguageName ).Value<Language>() );
	}

	UpdateLocalized();

	return true;
}

void XE::LocalizationService::Update()
{

}

void XE::LocalizationService::Clearup()
{
	_p->_Maps.clear();
}

XE::Language XE::LocalizationService::GetCurrentLanguage() const
{
	return _p->_Language;
}

void XE::LocalizationService::SetCurrentLanguage( XE::Language val )
{
	_p->_Language = val;

	GetFramework()->SetString( "System/Language", EnumID<Language>::Get()->FindName( (XE::int64)_p->_Language ) );

	UpdateLocalized();
}

const XE::String & XE::LocalizationService::LocalizedString( const XE::String & key, const XE::String& val ) const
{
	auto it = _p->_Maps.find( key );

	if ( it != _p->_Maps.end() && it->second != "" )
	{
		return it->second;
	}

	return val;
}

void XE::LocalizationService::Prepare()
{

}

void XE::LocalizationService::UpdateLocalized()
{
	std::string path = (GetFramework()->GetUserDataPath() / "language.csv").string();

	std::ifstream ifs( path );

	std::string buf( 2048, 0 );

	if ( ifs.is_open() )
	{
		ifs.getline( buf.data(), 2048 );

		while ( ifs.eof() )
		{
			ifs.getline( buf.data(), 2048 );

			std::vector<std::string> list = StringUtils::Split( buf, "," );

			_p->_Maps.insert( std::make_pair( list[0], list[( (XE::int64)_p->_Language ) + 1] ) );
		}
	}
}
