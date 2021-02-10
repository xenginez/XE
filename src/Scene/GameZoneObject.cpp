#include "GameZoneObject.h"

#include "World.h"

BEG_META( XE::GameZoneObject )
type->Property( "Children", &XE::GameZoneObject::_Children );
type->Property( "ChildrenEnable", &XE::GameZoneObject::_ChildrenEnable,  XE::IMetaProperty::NoDesign );
END_META()

XE::GameZoneObject::GameZoneObject()
{

}

XE::GameZoneObject::~GameZoneObject()
{

}

void XE::GameZoneObject::OnEnable()
{
	auto world = GetWorld();
	for( int i = 0;i < _Children.size(); ++i )
	{
		world->FindObject( _Children[i] )->SetEnable( _ChildrenEnable[i] );
	}
}

void XE::GameZoneObject::OnDisable()
{
	auto world = GetWorld();
	for( int i = 0;i < _Children.size(); ++i )
	{
		auto child = world->FindObject( _Children[i] );

		_ChildrenEnable[i] = child->GetEnable();
		child->SetEnable( false );
	}
}

void XE::GameZoneObject::InsertEntity( const XE::SceneObjectHandle & val )
{
	_Children.push_back( val );

	_ChildrenEnable.push_back( GetWorld()->FindObject( val )->GetEnable() );
}

void XE::GameZoneObject::RemoveEntity( const XE::SceneObjectHandle & val )
{
	auto it = std::find( _Children.begin(), _Children.end(), val );
	if( it != _Children.end() )
	{
		_ChildrenEnable.erase( _ChildrenEnable.begin() + ( it - _Children.begin() ) );
		_Children.erase( it );
	}
}

const XE::Array< XE::SceneObjectHandle > & XE::GameZoneObject::GetChildren() const
{
	return _Children;
}
