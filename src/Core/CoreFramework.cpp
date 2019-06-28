#include "CoreFramework.h"

#include "LoggerService.h"
#include "ConfigService.h"
#include "LocalizationService.h"
#include "TimerService.h"
#include "EventService.h"
#include "AudioService.h"
#include "ThreadService.h"
#include "PluginService.h"
#include "InputService.h"

#include "AssetsService.h"

#define LOGGER_INDEX	_p->_Services.at(0)
#define CONFIG_INDEX	_p->_Services.at(1)
#define LOCAL_INDEX		_p->_Services.at(2)
#define TIMER_INDEX		_p->_Services.at(3)
#define EVENT_INDEX		_p->_Services.at(4)
#define AUDIO_INDEX		_p->_Services.at(5)
#define THREAD_INDEX	_p->_Services.at(6)
#define PLUGIN_INDEX	_p->_Services.at(7)
#define INPUT_INDEX		_p->_Services.at(8)
#define ASSETS_INDEX	_p->_Services.at(9)
#define RENDER_INDEX	_p->_Services.at(10)
#define GUI_INDEX		_p->_Services.at(11)
#define PHYSICS_INDEX	_p->_Services.at(12)
#define NAVIGAT_INDEX	_p->_Services.at(13)
#define WORLD_INDEX		_p->_Services.at(14)

USING_XE

BEG_META( CoreFramework )
END_META()

struct XE::CoreFramework::Private
{
	std::atomic_bool _Exit = false;
	Array < IServicePtr > _Services;
};

XE::CoreFramework::CoreFramework()
	:_p( new Private )
{

}

XE::CoreFramework::~CoreFramework()
{
	delete _p;
}

int XE::CoreFramework::Exec()
{
	Prepare();

	Startup();

	Update();

	Clearup();

	return 0;
}

XE::IGUIServicePtr XE::CoreFramework::GetGUIService() const
{
	return SP_CAST < IGUIService >( GUI_INDEX );
}

XE::ITimerServicePtr XE::CoreFramework::GetTimerService() const
{
	return SP_CAST < ITimerService >( TIMER_INDEX );
}

XE::IEventServicePtr XE::CoreFramework::GetEventService() const
{
	return SP_CAST < IEventService >( EVENT_INDEX );
}

XE::IInputServicePtr XE::CoreFramework::GetInputService() const
{
	return SP_CAST < IInputService >( INPUT_INDEX );
}

XE::IAudioServicePtr XE::CoreFramework::GetAudioService() const
{
	return SP_CAST < IAudioService >( AUDIO_INDEX );
}

XE::IWorldServicePtr XE::CoreFramework::GetWorldService() const
{
	return SP_CAST < IWorldService >( WORLD_INDEX );
}

XE::IPluginServicePtr XE::CoreFramework::GetPluginService() const
{
	return SP_CAST < IPluginService >( PLUGIN_INDEX );
}

XE::IThreadServicePtr XE::CoreFramework::GetThreadService() const
{
	return SP_CAST < IThreadService >( THREAD_INDEX );
}

XE::IAssetsServicePtr XE::CoreFramework::GetAssetsService() const
{
	return SP_CAST < IAssetsService >( ASSETS_INDEX );
}

XE::IConfigServicePtr XE::CoreFramework::GetConfigService() const
{
	return SP_CAST < IConfigService >( CONFIG_INDEX );
}

XE::ILoggerServicePtr XE::CoreFramework::GetLoggerService() const
{
	return SP_CAST < ILoggerService >( LOGGER_INDEX );
}

XE::IRenderServicePtr XE::CoreFramework::GetRenderService() const
{
	return SP_CAST < IRenderService >( RENDER_INDEX );
}

XE::IPhysicsServicePtr XE::CoreFramework::GetPhysicsService() const
{
	return SP_CAST < IPhysicsService >( PHYSICS_INDEX );
}

XE::ILocalizationServicePtr XE::CoreFramework::GetLocalizationService() const
{
	return SP_CAST < ILocalizationService >( LOCAL_INDEX );
}

XE::IServicePtr XE::CoreFramework::GetService( const IMetaClassPtr & val ) const
{
	for( auto it = _p->_Services.rbegin(); it != _p->_Services.rend(); ++it )
	{
		if( ( *it ) != nullptr && ( *it )->GetMetaClass()->CanConvert( val ) )
		{
			return *it;
		}
	}

	return nullptr;
}

bool XE::CoreFramework::RegisterService( const IMetaClassPtr & val )
{
	if( val->CanConvert( IService::GetMetaClassStatic() ) && !val->IsAbstract() && !val->IsSingleton() )
	{
		for( const auto & sev : _p->_Services )
		{
			if( sev->GetMetaClass()->CanConvert( val ) )
			{
				return false;
			}
		}

		if( auto p = val->ConstructPtr() )
		{
			IServicePtr service = SP_CAST < IService >( p );

			service->SetFramework( this );

			service->Prepare();

			service->Startup();

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
	return Platform::get_default_language();
}

std::filesystem::path XE::CoreFramework::GetPluginPath() const
{
	return GetApplicationPath() / "plugin";
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
	_p->_Services.push_back( make_shared < LoggerService >() );
	_p->_Services.push_back( make_shared < ConfigService >() );
	_p->_Services.push_back( make_shared < LocalizationService >() );
	_p->_Services.push_back( make_shared < TimerService >() );
	_p->_Services.push_back( make_shared < EventService >() );
	_p->_Services.push_back( make_shared < AudioService >() );
	_p->_Services.push_back( make_shared < ThreadService >() );
	_p->_Services.push_back( make_shared < PluginService >() );
	_p->_Services.push_back( make_shared < InputService >() );
	// 	_p->_Services.push_back( make_shared <RenderService>() );
	// 	_p->_Services.push_back( make_shared <GUIService>() );
	// 	_p->_Services.push_back( make_shared <PhysicsService>() );
	_p->_Services.push_back( make_shared < AssetsService >() );
	// 	_p->_Services.push_back( make_shared <NavigationService>() );
	// 	_p->_Services.push_back( make_shared <WorldService>() );

	for( auto & it : _p->_Services )
	{
		it->SetFramework( this );
		it->Prepare();
	}
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
	while( !_p->_Exit )
	{
		FrameAlloc::reset();

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
	for( auto & service : _p->_Services )
	{
		if( service != nullptr )
		{
			service->Clearup();
		}
	}

	_p->_Services.clear();

	FrameAlloc::clear();
	ObjectAlloc::clear();
}
