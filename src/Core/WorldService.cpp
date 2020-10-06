#include "WorldService.h"

#include "Scene/World.h"
#include "Scene/GameObject.h"

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
		_p->_World = DP_CAST<XE::World>( GetFramework()->GetServiceT<XE::IAssetsService>()->LoadObject( path.ToStdString() ) );
	}
	else
	{
		_p->_World = XE::MakeShared<XE::World>();
	}

	_p->_World->Startup();

	return true;
}

void XE::WorldService::Update()
{
	_p->_World->Update( GetFramework()->GetServiceT<XE::ITimerService>()->GetDeltaTime() );
}

void XE::WorldService::Clearup()
{
	_p->_World->Clearup();
}

void XE::WorldService::LoadWorld( const XE::String & val )
{
	GetFramework()->GetServiceT<XE::IThreadService>()->PostTask( XE::ThreadType::GAME, [this, val]()
																		  {
																			  if( _p->_World )
																			  {
																				  _p->_World->Clearup();

																				  _p->_World = nullptr;
																			  }

																			  _p->_World = DP_CAST<XE::World>( GetFramework()->GetServiceT<XE::IAssetsService>()->LoadObject( val.ToStdString() ) );

																			  _p->_World->Startup();

																			  return false;
																		  } );
}

XE::WorldPtr XE::WorldService::GetCurrentWorld() const
{
	return _p->_World;
}
