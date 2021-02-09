#include "GameZone.h"

#include "World.h"

BEG_META( XE::GameZone )
type->Property( "Children", &XE::GameZone::_Children );
type->Property( "ChildrenEnable", &XE::GameZone::_ChildrenEnable,  XE::IMetaProperty::NoDesign );
END_META()

XE::GameZone::GameZone()
{

}

XE::GameZone::~GameZone()
{

}

void XE::GameZone::OnEnable()
{
	auto world = GetWorld();
	for( int i = 0;i < _Children.size(); ++i )
	{
		world->FindEntity( _Children[i] )->SetEnable( _ChildrenEnable[i] );
	}
}

void XE::GameZone::OnDisable()
{
	auto world = GetWorld();
	for( int i = 0;i < _Children.size(); ++i )
	{
		auto child = world->FindEntity( _Children[i] );

		_ChildrenEnable[i] = child->GetEnable();
		child->SetEnable( false );
	}
}

void XE::GameZone::InsertEntity( const XE::GameEntityHandle & val )
{
	_Children.push_back( val );

	_ChildrenEnable.push_back( GetWorld()->FindEntity( val )->GetEnable() );
}

void XE::GameZone::RemoveEntity( const XE::GameEntityHandle & val )
{
	auto it = std::find( _Children.begin(), _Children.end(), val );
	if( it != _Children.end() )
	{
		_ChildrenEnable.erase( _ChildrenEnable.begin() + ( it - _Children.begin() ) );
		_Children.erase( it );
	}
}

const XE::Array< XE::GameEntityHandle > & XE::GameZone::GetChildren() const
{
	return _Children;
}
