#include "CoreFramework.h"

#include "LoggerService.h"
#include "ConfigService.h"
#include "LocalizationService.h"
#include "TimerService.h"
#include "EventService.h"
#include "AudioService.h"
#include "ThreadService.h"
#include "PluginService.h"

#include "AssetsService.h"

USING_XE

BEGIN_META(CoreFramework)
END_META()

struct XE::CoreFramework::Private
{
	bool _Exit;
	Language _Language;
	Array < IServicePtr > _Services;
};

XE::CoreFramework::CoreFramework()
		:_p(new Private)
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
	return SP_CAST < IGUIService >(_p->_Services[0]);
}

XE::ITimerServicePtr XE::CoreFramework::GetTimerService() const
{
	return SP_CAST < ITimerService >(_p->_Services[0]);
}

XE::IEventServicePtr XE::CoreFramework::GetEventService() const
{
	return SP_CAST < IEventService >(_p->_Services[0]);
}

XE::IInputServicePtr XE::CoreFramework::GetInputService() const
{
	return SP_CAST < IInputService >(_p->_Services[0]);
}

XE::IAudioServicePtr XE::CoreFramework::GetAudioService() const
{
	return SP_CAST < IAudioService >(_p->_Services[0]);
}

XE::IWorldServicePtr XE::CoreFramework::GetWorldService() const
{
	return SP_CAST < IWorldService >(_p->_Services[0]);
}

XE::IPluginServicePtr XE::CoreFramework::GetPluginService() const
{
	return SP_CAST < IPluginService >(_p->_Services[0]);
}

XE::IThreadServicePtr XE::CoreFramework::GetThreadService() const
{
	return SP_CAST < IThreadService >(_p->_Services[0]);
}

XE::IAssetsServicePtr XE::CoreFramework::GetAssetsService() const
{
	return SP_CAST < IAssetsService >(_p->_Services[0]);
}

XE::IConfigServicePtr XE::CoreFramework::GetConfigService() const
{
	return SP_CAST < IConfigService >(_p->_Services[0]);
}

XE::ILoggerServicePtr XE::CoreFramework::GetLoggerService() const
{
	return SP_CAST < ILoggerService >(_p->_Services[0]);
}

XE::IRenderServicePtr XE::CoreFramework::GetRenderService() const
{
	return SP_CAST < IRenderService >(_p->_Services[0]);
}

XE::IPhysicsServicePtr XE::CoreFramework::GetPhysicsService() const
{
	return SP_CAST < IPhysicsService >(_p->_Services[0]);
}

XE::ILocalizationServicePtr XE::CoreFramework::GetLocalizationService() const
{
	return SP_CAST < ILocalizationService >(_p->_Services[0]);
}

XE::IServicePtr XE::CoreFramework::GetService( const IMetaClassPtr val ) const
{
	for( auto it = _p->_Services.rbegin(); it != _p->_Services.rend(); ++it )
	{
		if(( *it ) != nullptr && ( *it )->GetMetaClass()->CanConvert(val))
		{
			return *it;
		}
	}
	
	return nullptr;
}

bool XE::CoreFramework::RegisterService( IMetaClassPtr val )
{
	if( val->CanConvert(IService::GetMetaClassStatic()) && !val->IsAbstract())
	{
		if( auto p = val->ConstructPtr())
		{
			IServicePtr service = SP_CAST < IService >(p);
			
			service->SetFramework(this);
			
			service->Startup();
			
			_p->_Services.push_back(service);
			
			return true;
		}
	}
	
	return false;
}

void XE::CoreFramework::UnregisterService( IMetaClassPtr val )
{
	for( XE::uint64 i = _p->_Services.size() - 1; i >= 0; --i )
	{
		if( _p->_Services[i]->GetMetaClass()->CanConvert(val))
		{
			_p->_Services[i]->Clearup();
			_p->_Services[i] = nullptr;
		}
	}
}

XE::Language XE::CoreFramework::GetSystemLanguage() const
{
	return _p->_Language;
}

std::filesystem::path XE::CoreFramework::GetPluginPath() const
{
	return GetApplicationPath() / "Plugins";
}

std::filesystem::path XE::CoreFramework::GetAssetsPath() const
{
	return GetApplicationPath() / "Assets";
}

std::filesystem::path XE::CoreFramework::GetUserDataPath() const
{
	return GetApplicationPath() / "Userdata";
}

std::filesystem::path XE::CoreFramework::GetApplicationPath() const
{
	return std::filesystem::current_path();
}

void XE::CoreFramework::Prepare()
{
	_p->_Services.push_back(make_shared < LoggerService >());
	_p->_Services.push_back(make_shared < ConfigService >());
	_p->_Services.push_back(make_shared < LocalizationService >());
	_p->_Services.push_back(make_shared < TimerService >());
	_p->_Services.push_back(make_shared < EventService >());
	_p->_Services.push_back(make_shared < AudioService >());
	_p->_Services.push_back(make_shared < ThreadService >());
	_p->_Services.push_back(make_shared < PluginService >());
// 	_p->_Services.push_back( make_shared <InputService>() );
// 	_p->_Services.push_back( make_shared <RenderService>() );
// 	_p->_Services.push_back( make_shared <GUIService>() );
// 	_p->_Services.push_back( make_shared <PhysicsService>() );
	_p->_Services.push_back(make_shared < AssetsService >());
// 	_p->_Services.push_back( make_shared <WorldService>() );
// 	_p->_Services.push_back( make_shared <NavigationService>() );
	
	for( auto it : _p->_Services )
	{
		it->SetFramework(this);
	}
}

void XE::CoreFramework::Startup()
{
	_p->_Exit = false;
	
	_p->_Language = Platform::get_default_language();
	
	for( XE::uint64 i = 0; i < _p->_Services.size(); ++i )
	{
		if( !_p->_Services[i]->Startup())
		{
			_p->_Services[i]->Clearup();
			_p->_Services[i] = nullptr;
		}
	}
}

void XE::CoreFramework::Update()
{
	while( !_p->_Exit )
	{
		for( auto service : _p->_Services )
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
		if(( *it ) != nullptr )
		{
			( *it )->Clearup();
		}
	}
	
	_p->_Services.clear();
}
