#include "CoreFramework.h"

#include "GUIService.h"
#include "TimerService.h"
#include "EventService.h"
#include "AudioService.h"
#include "InputService.h"
#include "WorldService.h"
#include "LoggerService.h"
#include "ConfigService.h"
#include "ThreadService.h"
#include "RenderService.h"
#include "AssetsService.h"
#include "PhysicsService.h"
#include "ProfilerService.h"
#include "NavigationService.h"
#include "LocalizationService.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>


USING_XE

BEG_META( CoreFramework )
END_META()

struct XE::CoreFramework::Private
{
	std::atomic_bool _Exit = false;

	Array < IServicePtr > _Services;

	std::function<void()> _SysEventLoop;
};

XE::CoreFramework::CoreFramework()
	:_p( new Private )
{

}

XE::CoreFramework::~CoreFramework()
{
	delete _p;

	Reflection::Clear();
	ObjectAlloc::Clear();
}

int XE::CoreFramework::Exec( std::function<void()> val )
{
	_p->_SysEventLoop = val;

	Prepare();

	Startup();

	while( !_p->_Exit )
	{
		Update();
	}

	Clearup();

	return 0;
}

XE::IGUIServicePtr XE::CoreFramework::GetGUIService() const
{
	return GetServiceT<IGUIService>();
}

XE::ITimerServicePtr XE::CoreFramework::GetTimerService() const
{
	return GetServiceT<ITimerService>();
}

XE::IEventServicePtr XE::CoreFramework::GetEventService() const
{
	return GetServiceT<IEventService>();
}

XE::IInputServicePtr XE::CoreFramework::GetInputService() const
{
	return GetServiceT<IInputService>();
}

XE::IAudioServicePtr XE::CoreFramework::GetAudioService() const
{
	return GetServiceT<IAudioService>();
}

XE::IWorldServicePtr XE::CoreFramework::GetWorldService() const
{
	return GetServiceT<IWorldService>();
}

XE::IThreadServicePtr XE::CoreFramework::GetThreadService() const
{
	return GetServiceT<IThreadService>();
}

XE::IAssetsServicePtr XE::CoreFramework::GetAssetsService() const
{
	return GetServiceT<IAssetsService>();
}

XE::IConfigServicePtr XE::CoreFramework::GetConfigService() const
{
	return GetServiceT<IConfigService>();
}

XE::ILoggerServicePtr XE::CoreFramework::GetLoggerService() const
{
	return GetServiceT<ILoggerService>();
}

XE::IRenderServicePtr XE::CoreFramework::GetRenderService() const
{
	return GetServiceT<IRenderService>();
}

XE::IPhysicsServicePtr XE::CoreFramework::GetPhysicsService() const
{
	return GetServiceT<IPhysicsService>();
}

XE::IProfilerServicePtr XE::CoreFramework::GetProfilerService() const
{
	return GetServiceT<IProfilerService>();
}

XE::ILocalizationServicePtr XE::CoreFramework::GetLocalizationService() const
{
	return GetServiceT<ILocalizationService>();
}

XE::IServicePtr XE::CoreFramework::GetService( const IMetaClassPtr & val ) const
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

bool XE::CoreFramework::RegisterService( const IMetaClassPtr & val )
{
	if( GetService( val ) == nullptr )
	{
		if( auto p = val->ConstructPtr().DetachPtr() )
		{
			IServicePtr service = SP_CAST < IService >( p );

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

void XE::CoreFramework::UnregisterService( const IMetaClassPtr & val )
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
	return GetApplicationPath() / "module";
}

std::filesystem::path XE::CoreFramework::GetAssetsPath() const
{
	return GetApplicationPath().parent_path() / "assets";
}

std::filesystem::path XE::CoreFramework::GetUserDataPath() const
{
	return GetApplicationPath().parent_path() / "data";
}

std::filesystem::path XE::CoreFramework::GetApplicationPath() const
{
	return std::filesystem::absolute( std::filesystem::current_path() );
}

void XE::CoreFramework::Prepare()
{
	LoadServices();

	for( auto service : _p->_Services )
	{
		service->SetFramework( this );
		service->Prepare();
	}

	LoadModules();
}

void XE::CoreFramework::Startup()
{
	_p->_Exit = false;

	for( auto & service : _p->_Services )
	{
		if( !service->Startup() ) 
		{
			XE_LOG( LoggerLevel::Error, "startup %1 error!", service->GetMetaClass()->GetFullName() );
			_p->_Exit = true; 
			return; 
		}
	}
}

void XE::CoreFramework::Update()
{
	if( _p->_SysEventLoop )
	{
		_p->_SysEventLoop();
	}

	FrameAlloc::Reset();

	for( auto & service : _p->_Services )
	{
		if( service != nullptr )
		{
			service->Update();
		}
	}
}

void XE::CoreFramework::Clearup()
{
	for( auto it = _p->_Services.rbegin(); it != _p->_Services.rend(); ++it )
	{
		if( *it != nullptr )
		{
			( *it )->Clearup();
		}
	}
	_p->_Services.clear();
}

void XE::CoreFramework::LoadModules()
{
	auto modules = StringUtils::Split( GetConfigService()->GetString( "System/Modules" ), "," );
	for( auto module : modules )
	{
		auto path = GetModulePath() / module;
		if( std::filesystem::is_directory( path ) )
		{
			path = path / ( module + DLL_EXT_NAME );
			Library::Open( path.u8string() );
		}
	}
}

void CoreFramework::LoadServices()
{
	auto path = GetUserDataPath() / "config.json";
	std::ifstream ifs( path.string() );
	if( ifs.is_open() )
	{
		rapidjson::Document doc;
		rapidjson::IStreamWrapper wrapper( ifs );
		doc.ParseStream( wrapper );
		if( !doc.HasParseError() )
		{
			auto services = StringUtils::Split( doc["System"]["Services"].GetString(), "," );
			for( auto service : services )
			{
				if( auto meta = Reflection::FindClass( service ) )
				{
					if( auto ser = meta->ConstructPtr().Value<IServicePtr>() )
					{
						_p->_Services.push_back( ser );
					}
				}
			}
		}
	}
	ifs.close();
}
