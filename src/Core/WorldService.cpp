#include "WorldService.h"

USING_XE

struct XE::WorldService::Private
{
	XE::WorldPtr _World;
};

BEG_META( WorldService )
END_META()

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
		_p->_World = DP_CAST<XE::World>( GetFramework()->GetServiceT<XE::IAssetsService>()->Load( path ) );
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

void WorldService::LoadWorld( const XE::String & val )
{
	GetFramework()->GetServiceT<XE::IThreadService>()->PostTask( [this, val]()
																 {
																	 if( _p->_World )
																	 {
																		 _p->_World->Clearup();

																		 _p->_World = nullptr;
																	 }

																	 _p->_World = SP_CAST<XE::World>( GetFramework()->GetServiceT<XE::IAssetsService>()->Load( val ) );

																	 _p->_World->Startup();

																	 return false;
																 }, XE::ThreadType::GAME, XE::ThreadPriority::MAX );


}

XE::String WorldService::GetWorldName() const
{
	return _p->_World ? _p->_World->GetName() : "";
}

XE::WorldPtr WorldService::GetCurrentWorld() const
{
	return _p->_World;
}
