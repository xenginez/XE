#include "CoreFramework.h"

#include <mutex>
#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

#include "Utils/Logger.h"
#include "Utils/Library.h"

void nest_json( rapidjson::Value & parent, std::vector<std::string>::const_iterator beg, std::vector<std::string>::const_iterator end, const std::string & str, rapidjson::MemoryPoolAllocator<> & allocator )
{
	if( beg != end )
	{
		auto it = parent.FindMember( beg->c_str() );
		if( it == parent.MemberEnd() )
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

BEG_META( XE::CoreFramework )
END_META()

struct XE::CoreFramework::Private
{
	int _Argc = 0;
	char ** _Argv = nullptr;
	std::atomic_bool _Exit = false;
	std::mutex _ExitMutex;
	Map < String, String > Values;
	Array < IServicePtr > _Services;
	std::function<void()> _SysEventLoop;

	XE::Array< XE::uint64 > _StartServices, _UpdateServices, _ClearupServices;
};

XE::CoreFramework::CoreFramework()
	:_p( new Private )
{

}

XE::CoreFramework::~CoreFramework()
{
	delete _p;
}

int XE::CoreFramework::Exec( int argc, char ** argv, std::function<void()> msgloop )
{
	std::unique_lock< std::mutex > lock( _p->_ExitMutex );

	_p->_Argc = argc;
	_p->_Argv = argv;
	_p->_SysEventLoop = msgloop;

	Prepare();

	Startup();

	while( !_p->_Exit )
	{
		Update();
	}

	Clearup();

	return 0;
}

XE::IServicePtr XE::CoreFramework::GetService( const XE::IMetaClassPtr & val ) const
{
	for( auto service : _p->_Services )
	{
		if( service->GetMetaClass()->CanConvert( val ) )
		{
			return service;
		}
	}

	return nullptr;
}

bool XE::CoreFramework::RegisterService( const XE::IMetaClassPtr & val )
{
	if( GetService( val ) == nullptr )
	{
		if( IServicePtr service = val->ConstructPtr().Value< IServicePtr >() )
		{
			service->SetFramework( this );

			service->Prepare();

			if( !service->Startup() )
			{
				XE_LOG( LoggerLevel::Error, "startup %1 error!", service->GetMetaClass()->GetFullName() );
				return false;
			}

			_p->_Services.push_back( service );

			return true;
		}
	}

	return false;
}

void XE::CoreFramework::UnregisterService( const XE::IMetaClassPtr & val )
{
	auto it = std::find_if( _p->_Services.begin(), _p->_Services.end(), [val]( const IServicePtr & srv )
							{
								return srv->GetMetaClass()->CanConvert( val );
							} );

	if( it != _p->_Services.end() )
	{
		( *it )->Clearup();
		( *it ) = nullptr;
	}
}

void XE::CoreFramework::Exit()
{
	_p->_Exit = true;
}

void XE::CoreFramework::WaitExit()
{
	Exit();

	std::unique_lock< std::mutex > lock( _p->_ExitMutex );
}

bool XE::CoreFramework::IsExit() const
{
	return _p->_Exit;
}

XE::Language XE::CoreFramework::GetSystemLanguage() const
{
	return Platform::GetDefaultLanguage();
}

std::filesystem::path XE::CoreFramework::GetModulePath() const
{
	return GetApplicationPath() / MODULES_DIRECTORY;
}

std::filesystem::path XE::CoreFramework::GetAssetsPath() const
{
	return GetApplicationPath().parent_path() / ASSETS_DIRECTORY;
}

std::filesystem::path XE::CoreFramework::GetUserDataPath() const
{
	return GetApplicationPath().parent_path() / USERDATAS_DIRECTORY;
}

std::filesystem::path XE::CoreFramework::GetApplicationPath() const
{
	return std::filesystem::absolute( std::filesystem::current_path() );
}

void XE::CoreFramework::Prepare()
{
	Library::RegisterEnvPath( GetModulePath() );

	Reload();

	LoadModules();

	LoadServices();

	for( auto service : _p->_Services )
	{
		service->SetFramework( this );
		service->Prepare();
	}
}

void XE::CoreFramework::Startup()
{
	_p->_Exit = false;

	for( auto i : _p->_StartServices )
	{
		if (i != std::numeric_limits< XE::uint64 >::max() )
		{
			if( !_p->_Services[i]->Startup() )
			{
				XE_LOG( LoggerLevel::Error, "startup %1 error!", _p->_Services[i]->GetMetaClass()->GetFullName() );
				_p->_Exit = true;
				return;
			}
		}
	}
}

void XE::CoreFramework::Update()
{
	if( _p->_SysEventLoop )
	{
		_p->_SysEventLoop();
	}

	for( auto i : _p->_UpdateServices )
	{
		if( i != std::numeric_limits< XE::uint64 >::max() )
		{
			_p->_Services[i]->Update();
		}
	}
}

void XE::CoreFramework::Clearup()
{
	for( auto i : _p->_ClearupServices )
	{
		if( i != std::numeric_limits< XE::uint64 >::max() )
		{
			_p->_Services[i]->Clearup();
		}
	}

	_p->_Services.clear();

	_p->_StartServices.clear();
	_p->_UpdateServices.clear();
	_p->_ClearupServices.clear();

	_p->Values.clear();
}

void XE::CoreFramework::LoadModules()
{
	auto path = GetModulePath();

	std::filesystem::directory_iterator end;
	for( std::filesystem::directory_iterator iter( path ); iter != end; ++iter )
	{
		if( std::filesystem::is_directory( *iter ) )
		{
			auto module = ( *iter ).path() / ( ( *iter ).path().stem().u8string() + DLL_EXT_NAME );
			if( Library::Open( module.u8string() ) == LibraryHandle::Invalid )
			{
				std::cout << "load module \"" << module.u8string() << "\" fail" << std::endl;
			}
		}
	}
}

void XE::CoreFramework::LoadServices()
{
	XE::Set< XE::String > Services;
	XE::Array< XE::String > StartupServices, UpdateServices, ClearupServices;

	StartupServices = GetStringArray( "System/SortStartupServices" );
	UpdateServices = GetStringArray( "System/SortUpdateServices" );
	ClearupServices = GetStringArray( "System/SortClearupServices" );

	for( const auto & i : StartupServices )
	{
		Services.insert( i );
	}
	for( const auto & i : UpdateServices )
	{
		Services.insert( i );
	}
	for( const auto & i : ClearupServices )
	{
		Services.insert( i );
	}

	for( auto service : Services )
	{
		if( auto meta = Reflection::FindClass( service ) )
		{
			if( auto ser = meta->ConstructPtr().Value<IServicePtr>() )
			{
				_p->_Services.push_back( ser );
			}
		}
	}

	for( const auto & i : StartupServices )
	{
		auto it = std::find_if( _p->_Services.begin(), _p->_Services.end(), [i](const XE::IServicePtr & service )
								{
									return service->GetMetaClass()->GetFullName() == i;
								} );

		if( it != _p->_Services.end() )
		{
			_p->_StartServices.push_back( it - _p->_Services.begin() );
		}
		else
		{
			_p->_StartServices.push_back( std::numeric_limits< XE::uint64 >::max() );
		}
	}
	for( const auto & i : UpdateServices )
	{
		auto it = std::find_if( _p->_Services.begin(), _p->_Services.end(), [i]( const XE::IServicePtr & service )
								{
									return service->GetMetaClass()->GetFullName() == i;
								} );

		if( it != _p->_Services.end() )
		{
			_p->_UpdateServices.push_back( it - _p->_Services.begin() );
		}
		else
		{
			_p->_UpdateServices.push_back( std::numeric_limits< XE::uint64 >::max() );
		}
	}
	for( const auto & i : ClearupServices )
	{
		auto it = std::find_if( _p->_Services.begin(), _p->_Services.end(), [i]( const XE::IServicePtr & service )
								{
									return service->GetMetaClass()->GetFullName() == i;
								} );

		if( it != _p->_Services.end() )
		{
			_p->_ClearupServices.push_back( it - _p->_Services.begin() );
		}
		else
		{
			_p->_ClearupServices.push_back( std::numeric_limits< XE::uint64 >::max() );
		}
	}
}

void XE::CoreFramework::Save()
{
	auto path = GetUserDataPath() / CONFIG_FILE_NAME;

	Save( path, _p->Values );
}

void XE::CoreFramework::Save( const std::filesystem::path & path, const XE::Map < XE::String, XE::String > & values ) const
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

void XE::CoreFramework::Reload()
{
	_p->Values.clear();

	auto path = GetUserDataPath() / CONFIG_FILE_NAME;

	Reload( path, _p->Values );
}

void XE::CoreFramework::Reload( const std::filesystem::path & path, XE::Map < XE::String, XE::String > & values ) const
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

XE::String XE::CoreFramework::GetValue( const XE::String & key )
{
	auto it = _p->Values.find( key );

	if( it != _p->Values.end() )
	{
		return it->second;
	}
	else
	{
		_p->Values.insert( { key, "" } );
	}

	return "";
}

void XE::CoreFramework::SetValue( const XE::String & key, const XE::String & val )
{
	_p->Values[key] = val;
}

int XE::CoreFramework::GetArgc() const
{
	return _p->_Argc;
}

char ** XE::CoreFramework::GetArgv() const
{
	return _p->_Argv;
}
