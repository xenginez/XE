#include "Condition.h"



BEG_META( XE::Condition )
type->Property( "NextState", &Condition::_NextState );
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

void XE::Condition::SetAIModule( const XE::AIModulePtr & val )
{
	_AIModule = val;
}

XE::StateHandle XE::Condition::GetNextStateHandle() const
{
	return _NextState;
}

void XE::Condition::SetNextStateHandle( XE::StateHandle val )
{
	_NextState = val;
}
