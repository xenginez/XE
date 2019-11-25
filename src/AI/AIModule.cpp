#include "AIModule.h"

USING_XE

BEG_META( AIModule )
END_META()

XE::AIModule::AIModule()
{

}

XE::AIModule::~AIModule()
{

}

const XE::String & AIModule::GetName() const
{
	return _Name;
}

void AIModule::SetName( const XE::String & val )
{
	_Name = val;
}
