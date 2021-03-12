#include "SceneService.h"

#include "Scene/World.h"
#include "Utils/Logger.h"

BEG_META( XE::SceneService )
END_META()

struct XE::SceneService::Private
{
	XE::WorldPtr _World;
};

XE::SceneService::SceneService()
	:_p( new Private )
{

}

XE::SceneService::~SceneService()
{
	delete _p;
}

void XE::SceneService::Prepare()
{

}

bool XE::SceneService::Startup()
{
	auto path = GetFramework()->GetString( "System/StartWorld" );

	if( path != "" )
	{
		_p->_World = DP_CAST< XE::World >( GetFramework()->GetServiceT<XE::IAssetsService>()->LoadObject( path.std_str() ) );
	}

	if( _p->_World )
	{
		_p->_World->Startup();
	}

	return true;
}

void XE::SceneService::Update()
{
	if( _p->_World )
	{
		_p->_World->Update( GetFramework()->GetServiceT<XE::ITimerService>()->GetDeltaTime() );
	}
}

void XE::SceneService::Clearup()
{
	if( _p->_World )
	{
		_p->_World->Clearup();
	}
}

XE::WorldPtr XE::SceneService::GetWorld() const
{
	return _p->_World;
}

void XE::SceneService::ActiveWorld( const XE::WorldPtr & val )
{
	GetFramework()->GetServiceT< XE::IThreadService >()->PostTask( ThreadType::GAME, [this, val]()
																   {
																	   if( _p->_World )
																	   {
																		   _p->_World->Clearup();
																	   }

																	   _p->_World = val;

																	   if( _p->_World )
																	   {
																		   _p->_World->Startup();
																	   }
																   } );
}
