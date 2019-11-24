#include "Condition.h"

USING_XE

BEG_META( Condition )
END_META()

XE::Condition::Condition()
	:_AIModule( nullptr )
{

}

XE::Condition::~Condition()
{

}

bool XE::Condition::Judgment() const
{
	return false;
}

const XE::AIModulePtr & XE::Condition::GetAIModule() const
{
	return _AIModule;
}

void XE::Condition::SetAIModule( const AIModulePtr & val )
{
	_AIModule = val;
}
