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
	String paths = GetFramework()->GetConfigService()->GetString( "plugins" );

	std::vector<std::string> path_list = StringUtils::Split( paths, ",|, " );

	Array < std::filesystem::path > list;
	IteratorDirectory( list, GetFramework()->GetPluginPath() );

	for( const auto & p : list )
	{
		auto it = std::find( path_list.begin(), path_list.end(), p.string() );

		if( it != path_list.end() )
		{
			RegisterPlugin( p );
		}
	}

	return true;
}

void XE::PluginService::Update()
{
	for( auto & p : _p->_Plugins )
	{
		p.second.Plugin->Update();
	}
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

void XE::PluginService::RegisterPlugin( const std::filesystem::path & val )
{
	XE::uint64 handle = Library::Open( val.string() );
	if( handle == 0 )
	{
		XE_LOG( LoggerLevel::Error, "{%0} Plugin Load Error!", val );
		return;
	}

	XEPPluginInfo info{};
	info.LibHandle = handle;
	info.Register = Library::SymbolT < XEPPluginInfo::RegisterInvoke >( handle, "RegisterPlugin" );
	info.Unregister = Library::SymbolT < XEPPluginInfo::UnregisterInvoke >( handle, "UnregisterPlugin" );
	info.Plugin = info.Register( GetFramework() );

	info.Plugin->Startup();

	_p->_Plugins.insert( std::make_pair( info.Plugin->GetName(), info ) );
}

void XE::PluginService::UnregisterPlugin( const String & val )
{
	auto it = _p->_Plugins.find( val );

	if( it != _p->_Plugins.end() )
	{
		it->second.Plugin->Clearup();
		it->second.Unregister( it->second.Plugin );
		_p->_Plugins.erase( it );
	}
}

void XE::PluginService::IteratorDirectory( Array < std::filesystem::path > & list, const std::filesystem::path & val ) const
{
	if( std::filesystem::exists( val ) )
	{
		std::filesystem::directory_iterator item_begin( val );
		std::filesystem::directory_iterator item_end;
		for( ; item_begin != item_end; item_begin++ )
		{
			if( std::filesystem::is_directory( *item_begin ) )
			{
				IteratorDirectory( list, item_begin->path() );
			}
			else
			{
				list.push_back( item_begin->path() );
			}
		}
	}
}
