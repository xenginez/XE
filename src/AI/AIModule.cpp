#include "AIModule.h"

#include "BlackBoard.h"

USING_XE

BEG_META( AIModule )
type->Property( "Name", &AIModule::_Name );
type->Property( "Blackboard", &AIModule::_Blackboard );
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

XE::BlackBoardPtr XE::AIModule::GetBlackBoard() const
{
	return _Blackboard;
}
