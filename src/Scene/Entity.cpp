#include "Entity.h"

BEG_META( XE::Entity )
type->Property( "Name", &XE::Entity::_Name );
type->Property( "Enable", &XE::Entity::_Enable );
type->Property( "Handle", &XE::Entity::_Handle );
END_META()

XE::Entity::Entity()
	:_Enable( true )
{

}

XE::Entity::~Entity()
{

}

bool XE::Entity::GetEnable() const
{
	return _Enable;
}

void XE::Entity::SetEnable( bool val )
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

const XE::String & XE::Entity::GetName() const
{
	return _Name;
}

void XE::Entity::SetName( const String & val )
{
	_Name = val;
}

XE::EntityHandle XE::Entity::GetHandle() const
{
	return _Handle;
}
