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

#define STARTUP_SERVICE(SERVICE) if( !SERVICE->Startup() ) { XE_LOG( LoggerLevel::Error, "startup %1 error!", SERVICE->GetMetaClass()->GetFullName() ); _p->_Exit = true; return; }

USING_XE

BEG_META( CoreFramework )
END_META()

struct XE::CoreFramework::Private
{
	std::atomic_bool _Exit = false;

	IServicePtr _GUIService;
	IServicePtr _WorldService;
	IServicePtr _TimerService;
	IServicePtr _EventService;
	IServicePtr _AudioService;
	IServicePtr _InputService;
	IServicePtr _ConfigService;
	IServicePtr _LoggerService;
	IServicePtr _ThreadService;
	IServicePtr _RenderService;
	IServicePtr _AssetsService;
	IServicePtr _PhysicsService;
	IServicePtr _ProfilerService;
	IServicePtr _NavigationService;
	IServicePtr _LocalizationService;

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

	Update();

	Clearup();

	return 0;
}

XE::IGUIServicePtr XE::CoreFramework::GetGUIService() const
{
	return SP_CAST < IGUIService >( _p->_GUIService );
}

XE::ITimerServicePtr XE::CoreFramework::GetTimerService() const
{
	return SP_CAST < ITimerService >( _p->_TimerService );
}

XE::IEventServicePtr XE::CoreFramework::GetEventService() const
{
	return SP_CAST < IEventService >( _p->_EventService );
}

XE::IInputServicePtr XE::CoreFramework::GetInputService() const
{
	return SP_CAST < IInputService >( _p->_InputService );
}

XE::IAudioServicePtr XE::CoreFramework::GetAudioService() const
{
	return SP_CAST < IAudioService >( _p->_AudioService );
}

XE::IWorldServicePtr XE::CoreFramework::GetWorldService() const
{
	return SP_CAST < IWorldService >( _p->_WorldService );
}

XE::IThreadServicePtr XE::CoreFramework::GetThreadService() const
{
	return SP_CAST < IThreadService >( _p->_ThreadService );
}

XE::IAssetsServicePtr XE::CoreFramework::GetAssetsService() const
{
	return SP_CAST < IAssetsService >( _p->_AssetsService );
}

XE::IConfigServicePtr XE::CoreFramework::GetConfigService() const
{
	return SP_CAST < IConfigService >( _p->_ConfigService );
}

XE::ILoggerServicePtr XE::CoreFramework::GetLoggerService() const
{
	return SP_CAST < ILoggerService >( _p->_LoggerService );
}

XE::IRenderServicePtr XE::CoreFramework::GetRenderService() const
{
	return SP_CAST < IRenderService >( _p->_RenderService );
}

XE::IPhysicsServicePtr XE::CoreFramework::GetPhysicsService() const
{
	return SP_CAST < IPhysicsService >( _p->_PhysicsService );
}

XE::IProfilerServicePtr XE::CoreFramework::GetProfilerService() const
{
	return SP_CAST < IProfilerService >( _p->_ProfilerService );
}

XE::ILocalizationServicePtr XE::CoreFramework::GetLocalizationService() const
{
	return SP_CAST < ILocalizationService >( _p->_LocalizationService );
}

XE::IServicePtr XE::CoreFramework::GetService( const IMetaClassPtr & val ) const
{
	if( GetGUIService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetGUIService();
	}
	else if( GetTimerService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetTimerService();
	}
	else if( GetEventService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetEventService();
	}
	else if( GetInputService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetInputService();
	}
	else if( GetAudioService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetAudioService();
	}
	else if( GetWorldService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetWorldService();
	}
	else if( GetThreadService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetThreadService();
	}
	else if( GetAssetsService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetAssetsService();
	}
	else if( GetConfigService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetConfigService();
	}
	else if( GetLoggerService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetLoggerService();
	}
	else if( GetRenderService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetRenderService();
	}
	else if( GetPhysicsService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetPhysicsService();
	}
	else if( GetProfilerService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetProfilerService();
	}
	else if( GetLocalizationService()->GetMetaClass()->CanConvert( val ) )
	{
		return GetLocalizationService();
	}

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
	CHECK_THREAD( ThreadType::GAME );

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
	_p->_GUIService = XE::make_shared < GUIService >();
	_p->_WorldService = XE::make_shared < WorldService >();
	_p->_TimerService = XE::make_shared < TimerService >();
	_p->_EventService = XE::make_shared < EventService >();
	_p->_AudioService = XE::make_shared < AudioService >();
	_p->_InputService = XE::make_shared < InputService >();
	_p->_ConfigService = XE::make_shared < ConfigService >();
	_p->_LoggerService = XE::make_shared < LoggerService >();
	_p->_ThreadService = XE::make_shared < ThreadService >();
	_p->_AssetsService = XE::make_shared < AssetsService >();
	_p->_RenderService = XE::make_shared < RenderService >();
	_p->_PhysicsService = XE::make_shared < PhysicsService >();
	_p->_ProfilerService = XE::make_shared < ProfilerService >();
	_p->_NavigationService = XE::make_shared < NavigationService >();
	_p->_LocalizationService = XE::make_shared < LocalizationService >();

	_p->_ConfigService->SetFramework( this );
	_p->_ConfigService->Prepare();
	_p->_LoggerService->SetFramework( this );
	_p->_LoggerService->Prepare();
	_p->_TimerService->SetFramework( this );
	_p->_TimerService->Prepare();
	_p->_ThreadService->SetFramework( this );
	_p->_ThreadService->Prepare();
	_p->_EventService->SetFramework( this );
	_p->_EventService->Prepare();
	_p->_ProfilerService->SetFramework( this );
	_p->_ProfilerService->Prepare();
	_p->_LocalizationService->SetFramework( this );
	_p->_LocalizationService->Prepare();
	_p->_InputService->SetFramework( this );
	_p->_InputService->Prepare();
	_p->_AudioService->SetFramework( this );
	_p->_AudioService->Prepare();
	_p->_AssetsService->SetFramework( this );
	_p->_AssetsService->Prepare();
	_p->_RenderService->SetFramework( this );
	_p->_RenderService->Prepare();
	_p->_PhysicsService->SetFramework( this );
	_p->_PhysicsService->Prepare();
	_p->_NavigationService->SetFramework( this );
	_p->_NavigationService->Prepare();
	_p->_GUIService->SetFramework( this );
	_p->_GUIService->Prepare();
	_p->_WorldService->SetFramework( this );
	_p->_WorldService->Prepare();

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

	STARTUP_SERVICE( _p->_ConfigService );
	STARTUP_SERVICE( _p->_LoggerService );
	STARTUP_SERVICE( _p->_TimerService );
	STARTUP_SERVICE( _p->_ThreadService );
	STARTUP_SERVICE( _p->_EventService );
	STARTUP_SERVICE( _p->_ProfilerService );
	STARTUP_SERVICE( _p->_LocalizationService );
	STARTUP_SERVICE( _p->_InputService );
	STARTUP_SERVICE( _p->_AudioService );
	STARTUP_SERVICE( _p->_AssetsService );
	STARTUP_SERVICE( _p->_RenderService );
	STARTUP_SERVICE( _p->_PhysicsService );
	STARTUP_SERVICE( _p->_NavigationService );
	STARTUP_SERVICE( _p->_GUIService );
	STARTUP_SERVICE( _p->_WorldService );

	for( auto & service : _p->_Services )
	{
		STARTUP_SERVICE( service );
	}
}

void XE::CoreFramework::Update()
{
	while( !_p->_Exit )
	{
		if( _p->_SysEventLoop )
		{
			_p->_SysEventLoop();
		}

		FrameAlloc::Reset();

//		_p->_ConfigService->Update();
//		_p->_LoggerService->Update();
//		_p->_ProfilerService->Update();
//		_p->_LocalizationService->Update();

		_p->_TimerService->Update();
		_p->_InputService->Update();
		_p->_EventService->Update();
		_p->_ThreadService->Update();
		_p->_PhysicsService->Update();
		_p->_NavigationService->Update();
		_p->_RenderService->Update();
		_p->_GUIService->Update();
		_p->_WorldService->Update();
		_p->_AudioService->Update();
		_p->_AssetsService->Update();

		for( auto & service : _p->_Services )
		{
			if( service != nullptr )
			{
				service->Update();
			}
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

	_p->_WorldService->Clearup();
	_p->_GUIService->Clearup();
	_p->_NavigationService->Clearup();
	_p->_PhysicsService->Clearup();
	_p->_RenderService->Clearup();
	_p->_AssetsService->Clearup();
	_p->_AudioService->Clearup();
	_p->_InputService->Clearup();
	_p->_LocalizationService->Clearup();
	_p->_ProfilerService->Clearup();
	_p->_EventService->Clearup();
	_p->_ThreadService->Clearup();
	_p->_TimerService->Clearup();
	_p->_LoggerService->Clearup();
	_p->_ConfigService->Clearup();
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
