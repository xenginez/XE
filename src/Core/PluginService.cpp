#include "PluginService.h"

#include <pugixml/pugixml.hpp>

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

	if( Desc.Library == 0 )
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
		auto plugin_path = path / "plugin.xml";

		pugi::xml_document doc;
		if( doc.load_file( plugin_path.string().c_str() ).status == pugi::status_ok )
		{
			auto plugin = doc.select_node( "Plugin" );

			Desc.Name = plugin.node().select_node( "Name" ).node().value();
			Desc.Description = plugin.node().select_node( "Description" ).node().value();
			std::string lib_name = plugin.node().select_node( "Library" ).node().value();
			lib_name += DLL_EXT_NAME;
			Desc.Library = Library::Open( ( path / lib_name ).string() );
		}
	}

	return Desc;
}

void XE::PluginService::Prepare()
{

}
