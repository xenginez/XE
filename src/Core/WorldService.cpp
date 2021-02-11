#include "WorldService.h"

#include "Scene/World.h"
#include "Utils/Logger.h"

BEG_META( XE::WorldService )
END_META()

struct XE::WorldService::Private
{
	XE::WorldPtr _World;
};

XE::WorldService::WorldService()
	:_p( new Private )
{

}

XE::WorldService::~WorldService()
{
	delete _p;
}

void XE::WorldService::Prepare()
{

}

bool XE::WorldService::Startup()
{
	auto path = GetFramework()->GetString( "System/StartWorld" );

	if( path != "" )
	{
		_p->_World = DP_CAST< XE::World >( GetFramework()->GetServiceT<XE::IAssetsService>()->LoadObject( path.ToStdString() ) );
	}

	if( _p->_World )
	{
		_p->_World->Startup();
	}

	return true;
}

void XE::WorldService::Update()
{
	if( _p->_World )
	{
		_p->_World->Update( GetFramework()->GetServiceT<XE::ITimerService>()->GetDeltaTime() );
	}
}

void XE::WorldService::Clearup()
{
	if( _p->_World )
	{
		_p->_World->Clearup();
	}
}

XE::WorldPtr XE::WorldService::GetWorld() const
{
	return _p->_World;
}

void XE::WorldService::ActiveWorld( const XE::WorldPtr & val )
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
