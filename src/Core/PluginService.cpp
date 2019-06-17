#include "PluginService.h"
#include "PluginService.h"


USING_XE

BEG_META( PluginService )
END_META()

struct XEPPluginInfo
{
	typedef IPlugin * ( *RegisterInvoke )( IFrameworkPtr );

	typedef void( *UnregisterInvoke )( IPlugin * );

	XE::uint64 LibHandle;

	IPlugin * Plugin;
	std::filesystem::path Path;

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
	}

	_p->_Plugins.clear();
}

void XE::PluginService::RegisterPlugin( const String & name )
{
	if( _p->_Plugins.find( name ) != _p->_Plugins.end() )
	{
		return;
	}

	XE::uint64 handle = LoadPlugin( name );
	if( handle == 0 )
	{
		XE_LOG( LoggerLevel::Error, "%1 plugin load error!", name );
		return;
	}

	XEPPluginInfo info{};
	info.LibHandle = handle;
	info.Register = Library::SymbolT < XEPPluginInfo::RegisterInvoke >( handle, "RegisterPlugin" );
	info.Unregister = Library::SymbolT < XEPPluginInfo::UnregisterInvoke >( handle, "UnregisterPlugin" );
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
		Library::Close( it->second.LibHandle );

		_p->_Plugins.erase( it );
	}
}

XE::uint64 XE::PluginService::LoadPlugin( const String & name )
{
	auto path = GetFramework()->GetPluginPath();

	for( std::filesystem::recursive_directory_iterator it( path ), end; it != end; ++it )
	{
		if( !std::filesystem::is_directory( *it ) )
		{
			if( it->path().stem().string() == name.ToStdString() )
			{
				return Library::Open( it->path().string() );
			}
		}
	}

	return 0;
}
