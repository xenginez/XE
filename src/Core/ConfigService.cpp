#include "ConfigService.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

USING_XE

BEG_META( ConfigService )
END_META()

struct ConfigService::Private
{
	Map < String, String > Values;
};

XE::ConfigService::ConfigService()
	:_p( new Private )
{

}

XE::ConfigService::~ConfigService()
{
	delete _p;
}

void XE::ConfigService::Prepare()
{
	Reload();
}

bool XE::ConfigService::Startup()
{
	return true;
}

void XE::ConfigService::Update()
{

}

void nest_json( rapidjson::Value & parent, std::vector<std::string>::const_iterator beg, std::vector<std::string>::const_iterator end, const std::string & str, rapidjson::MemoryPoolAllocator<> & allocator )
{
	if( beg != end )
	{
		auto it = parent.FindMember( beg->c_str() );
		if (it == parent.MemberEnd())
		{
			parent.AddMember(
				rapidjson::Value().SetString( beg->c_str(), allocator ).Move(),
				rapidjson::Value( rapidjson::kObjectType ).Move(),
				allocator
			);

			it = parent.FindMember( beg->c_str() );
		}

		nest_json( it->value, beg + 1, end, str, allocator );
	}
	else
	{
		parent.AddMember(
			rapidjson::Value().SetString( beg->c_str(), allocator ).Move(),
			rapidjson::Value().SetString( str.c_str(), allocator ).Move(),
			allocator
		);
	}
}

void XE::ConfigService::Clearup()
{
	Save();

	_p->Values.clear();
}

void ConfigService::Save()
{
	auto path = GetFramework()->GetUserDataPath() / "config.json";

	Save( path, _p->Values );
}

void ConfigService::Save( const std::filesystem::path & path, const Map < String, String > & values ) const
{
	rapidjson::Document doc;
	auto & allocator = doc.GetAllocator();
	doc.SetObject();

	for( const auto & it : values )
	{
		auto list = StringUtils::Split( it.first, "/" );

		auto json_it = doc.FindMember( list.front().c_str() );
		if( json_it == doc.MemberEnd() )
		{
			doc.AddMember(
				rapidjson::Value().SetString( list.front().c_str(), allocator ).Move(),
				rapidjson::Value( rapidjson::kObjectType ).Move(),
				allocator );
			json_it = doc.FindMember( list.front().c_str() );
		}

		nest_json( json_it->value, list.begin() + 1, list.end() - 1, it.second, allocator );
	}

	std::ofstream ofs( path.string(), std::ios::out );
	if( ofs.is_open() )
	{
		rapidjson::OStreamWrapper wrapper( ofs );
		rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer( wrapper );
		doc.Accept( writer );
	}
	ofs.close();
}

void ConfigService::Reload()
{
	_p->Values.clear();

	auto path = GetFramework()->GetUserDataPath() / "config.json";

	Reload( path, _p->Values );
}

void ConfigService::Reload( const std::filesystem::path & path, Map < String, String > & values ) const
{
	std::ifstream ifs( path.string() );
	if( ifs.is_open() )
	{
		rapidjson::Document doc;
		rapidjson::IStreamWrapper wrapper( ifs );
		doc.ParseStream( wrapper );
		if( !doc.HasParseError() )
		{
			Stack<Pair<std::string, rapidjson::Value::ConstMemberIterator>> stack;

			for( rapidjson::Value::ConstMemberIterator iter = doc.MemberBegin(); iter != doc.MemberEnd(); ++iter )
			{
				stack.push( { iter->name.GetString(), iter } );
			}

			while( !stack.empty() )
			{
				Pair<std::string, rapidjson::Value::ConstMemberIterator> pair = stack.top();
				stack.pop();

				if( !pair.second->value.IsObject() )
				{
					values.insert( { pair.first, pair.second->value.GetString() } );
				}
				else
				{
					for( rapidjson::Value::ConstMemberIterator it = pair.second->value.MemberBegin(); it != pair.second->value.MemberEnd(); ++it )
					{
						stack.push( { pair.first + "/" + it->name.GetString(), it } );
					}
				}
			}
		}
	}
	ifs.close();
}

String XE::ConfigService::GetValue( const String & key )
{
	auto it = _p->Values.find( key );

	if( it != _p->Values.end() )
	{
		return it->second;
	}
	else
	{
		_p->Values.insert({key, ""});
	}

	return "";
}

void XE::ConfigService::SetValue( const String & key, const String & val )
{
	_p->Values[key] = val;
}
