#include "ConfigService.h"

#include <pugixml.hpp>

USING_XE

BEGIN_META(ConfigService)
END_META()

struct ConfigService::Private
{
	std::map < std::string, std::string > Values;
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
		auto node = doc.select_node("items");
		auto set = node.node().select_nodes("item");
		for( auto it : set )
		{
			std::string key = it.node().attribute("name").value();
			std::string val = it.node().attribute("value").value();
			
			_p->Values.insert({ key, val });
		}
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
	
	auto node = doc.append_child("items");
	for( const auto &it : _p->Values )
	{
		auto item = node.append_child("item");
		
		item.append_attribute("name").set_value(it.first.c_str());
		item.append_attribute("value").set_value(it.first.c_str());
	}
	
	doc.save_file(path.string().c_str());
}

std::string XE::ConfigService::GetValue( const std::string &key ) const
{
	auto it = _p->Values.find(key);
	
	if( it != _p->Values.end())
	{
		return it->second;
	}
	
	return "";
}

void XE::ConfigService::SetValue( const std::string &key, const std::string &val ) const
{
	_p->Values[key] = val;
}
