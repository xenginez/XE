#include "ConfigService.h"

#include <pugixml/pugixml.hpp>

USING_XE

BEG_META(ConfigService)
END_META()

struct ConfigService::Private
{
	std::map < String, String > Values;
};

XE::ConfigService::ConfigService()
		:_p(new Private)
{
	
}

XE::ConfigService::~ConfigService()
{
	delete _p;
}

bool XE::ConfigService::Startup()
{
	auto path = GetFramework()->GetUserDataPath() / "config.xml";

	pugi::xml_document doc;
	if( doc.load_file(path.string().c_str()).status == pugi::status_ok )
	{
		for( auto it = doc.begin(); it != doc.end(); ++it )
		{
			for( auto it2 = it->begin(); it2 != it->end(); ++it2 )
			{
				Load( it2, it->name() );
			}
		}

		return true;
	}
	
	return false;
}

void XE::ConfigService::Update()
{
	
}

void XE::ConfigService::Clearup()
{
	auto path = GetFramework()->GetUserDataPath() / "config.xml";
	
	pugi::xml_document doc;
	
	for( const auto &it : _p->Values )
	{
		std::vector<std::string> path_list = StringUtils::Split( it.first, "." );

		if( !path_list.empty() )
		{
			pugi::xml_node node = doc.child( path_list[0].c_str() );
			for( int i = 1; i < path_list.size(); ++i )
			{
				node = node.child( path_list[i].c_str() );
			}

			node.append_attribute( "value" ).set_value( it.second.ToCString() );
		}
	}
	
	doc.save_file(path.string().c_str());

	_p->Values.clear();
}

String XE::ConfigService::GetValue( const String &key ) const
{
	auto it = _p->Values.find(key);
	
	if( it != _p->Values.end())
	{
		return it->second;
	}
	
	return "";
}

void XE::ConfigService::SetValue( const String &key, const String &val ) const
{
	_p->Values[key] = val;
}

void XE::ConfigService::Load( const pugi::xml_node_iterator & parent, const std::string & parent_name )
{
	std::string this_name = parent_name + "." + parent->name();

	auto attr = parent->attribute( "value" );
	if( !attr.empty() )
	{
		_p->Values.insert( { this_name, attr.value() } );
	}

	for( auto it = parent->begin(); it != parent->end(); ++it )
	{
		Load( it, this_name );
	}
}
