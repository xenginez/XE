#include "GameEntity.h"

BEG_META( XE::GameEntity )
type->Property( "Name", &XE::GameEntity::_Name );
type->Property( "Enable", &XE::GameEntity::_Enable );
type->Property( "Handle", &XE::GameEntity::_Handle );
END_META()

XE::GameEntity::GameEntity()
	:_Enable( true )
{

}

XE::GameEntity::~GameEntity()
{

}

bool XE::GameEntity::GetEnable() const
{
	return _Enable;
}

void XE::GameEntity::SetEnable( bool val )
{
	if( _Enable != val )
	{
		_Enable = val;

		if( _Enable )
		{
			OnEnable();
		}
		else
		{
			OnDisable();
		}
	}
}

const XE::String & XE::GameEntity::GetName() const
{
	return _Name;
}

void XE::GameEntity::SetName( const String & val )
{
	_Name = val;
}

XE::GameEntityHandle XE::GameEntity::GetHandle() const
{
	return _Handle;
}
