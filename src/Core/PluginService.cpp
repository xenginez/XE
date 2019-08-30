#include "PluginService.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

USING_XE

BEG_META( PluginService )
END_META()


struct XEPPluginInfo
{
public:
	typedef IPlugin * ( *RegisterInvoke )( IFrameworkPtr );

	typedef void( *UnregisterInvoke )( IPlugin * );

public:
	PluginDesc Desc;

	IPlugin * Plugin;
	RegisterInvoke Register;
	UnregisterInvoke Unregister;
};

struct PluginService::Private
{
	std::map < String, XEPPluginInfo > _Plugins;
};

XE::PluginService::PluginService()
	:_p( new Private )
{

}

XE::PluginService::~PluginService()
{
	delete _p;
}

bool XE::PluginService::Startup()
{
	String paths = GetFramework()->GetConfigService()->GetString( "System.Plugins" );

	std::vector<std::string> plugin_names = StringUtils::Split( paths, "," );

	for( const auto & name : plugin_names )
	{
		RegisterPlugin( name );
	}

	return true;
}

void XE::PluginService::Update()
{

}

void XE::PluginService::Clearup()
{
	for( auto & p : _p->_Plugins )
	{
		p.second.Plugin->Clearup();
		p.second.Unregister( p.second.Plugin );
		Library::Close( p.second.Desc.Library );
	}

	_p->_Plugins.clear();
}

void XE::PluginService::RegisterPlugin( const String & name )
{
	if( _p->_Plugins.find( name ) != _p->_Plugins.end() )
	{
		return;
	}

	PluginDesc Desc = LoadPlugin( name );

	if( Desc.Library == LibraryHandle::Invalid )
	{
		XE_LOG( LoggerLevel::Error, "%1 plugin load error!", name );
		return;
	}

	XEPPluginInfo info{};
	info.Desc = Desc;
	info.Register = Library::SymbolT < XEPPluginInfo::RegisterInvoke >( Desc.Library, "RegisterPlugin" );
	info.Unregister = Library::SymbolT < XEPPluginInfo::UnregisterInvoke >( Desc.Library, "UnregisterPlugin" );
	info.Plugin = info.Register( GetFramework() );

	info.Plugin->Startup();

	_p->_Plugins.insert( std::make_pair( name, info ) );
}

void XE::PluginService::UnregisterPlugin( const String & name )
{
	auto it = _p->_Plugins.find( name );

	if( it != _p->_Plugins.end() )
	{
		it->second.Plugin->Clearup();
		it->second.Unregister( it->second.Plugin );
		Library::Close( it->second.Desc.Library );

		_p->_Plugins.erase( it );
	}
}

XE::PluginDesc XE::PluginService::LoadPlugin( const String & name )
{
	PluginDesc Desc;

	auto path = GetFramework()->GetPluginPath() / name.ToStdString();

	if( std::filesystem::is_directory( path ) )
	{
		auto plugin_path = path / "plugin.json";

		std::ifstream ifs( path.string() );
		if( ifs.is_open() )
		{
			rapidjson::Document doc;
			rapidjson::IStreamWrapper wrapper( ifs );
			doc.ParseStream( wrapper );
			if( !doc.HasParseError() )
			{
				Desc.Name = doc.FindMember( "Name" )->value.GetString();
				Desc.Description = doc.FindMember( "Description" )->value.GetString(); 
				std::string lib_name = doc.FindMember( "Library" )->value.GetString(); 
				lib_name += DLL_EXT_NAME;
				Desc.Library = Library::Open( ( path / lib_name ).string() );
			}
		}
		ifs.close();
	}

	return Desc;
}

void XE::PluginService::Prepare()
{

}
