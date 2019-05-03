#include "AIModule.h"

USING_XE

BEGIN_META( AIModule )
END_META()

XE::AIModule::AIModule()
{

}

XE::AIModule::~AIModule()
{

}

XE::GameObjectPtr XE::AIModule::GetGameObject() const
{
	return _GameObject.lock();
}

void XE::AIModule::SetGameObject( GameObjectPtr val )
{
	_GameObject = val;
}
