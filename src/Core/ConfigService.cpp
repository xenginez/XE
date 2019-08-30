#include "ConfigService.h"

#include <rapidjson/writer.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

USING_XE

BEG_META(ConfigService)
END_META()

struct ConfigService::Private
{
	Map < String, String > Values;
};

XE::ConfigService::ConfigService()
		:_p(new Private)
{
	
}

XE::ConfigService::~ConfigService()
{
	delete _p;
}

void XE::ConfigService::Prepare()
{
	auto path = GetFramework()->GetUserDataPath() / "config.json";

	std::ifstream ifs( path.string() );
	if( ifs.is_open() )
	{
		rapidjson::Document doc;
		rapidjson::IStreamWrapper wrapper( ifs );
		doc.ParseStream( wrapper );
		if( !doc.HasParseError() )
		{
			for( rapidjson::Value::ConstMemberIterator iter = doc.MemberBegin(); iter != doc.MemberEnd(); ++iter )
			{
				for( rapidjson::Value::ConstMemberIterator it = iter->value.MemberBegin(); it != iter->value.MemberEnd(); ++it )
				{
					Load( it, iter->name.GetString() );
				}
			}
		}
	}
	ifs.close();
}

bool XE::ConfigService::Startup()
{
	return true;
}

void XE::ConfigService::Update()
{
	
}

void XE::ConfigService::Clearup()
{
	auto path = GetFramework()->GetUserDataPath() / "config.json";
	
	rapidjson::Document doc;
	doc.Parse( "{}" );

	for( const auto & it : _p->Values )
	{
		auto list = StringUtils::Split( it.first, "\\." );

		rapidjson::Value * value = &doc;

		for( XE::uint64 i = 0; i < list.size() - 1; ++i )
		{
			value = &( value->AddMember( rapidjson::StringRef( list[i].c_str() ), rapidjson::Value().SetObject().Move(), doc.GetAllocator() ) );
		}

		value->AddMember( rapidjson::StringRef( list.back().c_str() ), rapidjson::StringRef( it.second.ToCString() ), doc.GetAllocator() );
	}

	std::ofstream ofs( path.string() );
	if( ofs.is_open() )
	{
		rapidjson::OStreamWrapper wrapper( ofs );
		rapidjson::Writer<rapidjson::OStreamWrapper> writer( wrapper );
		doc.Accept( writer );
	}
	ofs.close();

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

void XE::ConfigService::Load( const rapidjson::Value::ConstMemberIterator & parent, const std::string & parent_name )
{
	std::string this_name = parent_name + "." + parent->name.GetString();

	if( parent->value.IsObject() )
	{
		for( rapidjson::Value::ConstMemberIterator it = parent->value.MemberBegin(); it != parent->value.MemberEnd(); ++it )
		{
			Load( it, this_name );
		}
	}
	else
	{
		_p->Values.insert( { this_name, parent->value.GetString() } );
	}
}
