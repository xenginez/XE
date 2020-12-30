#include "Module.h"

BEG_META( AI::Module )
type->Property( "Name", &AI::Module::_Name );
type->Property( "Keys", &AI::Module::_Keys );
END_META()

AI::Module::Module()
{

}

AI::Module::~Module()
{

}

void AI::Module::Startup()
{

}

void AI::Module::Enter()
{

}

void AI::Module::Update( XE::float32 dt )
{

}

void AI::Module::Quit()
{

}

void AI::Module::Clearup()
{
	_ProcessEventCallback = nullptr;
}

bool AI::Module::IsStopped() const
{
	return false;
}

const XE::String & AI::Module::GetName() const
{
	return _Name;
}

void AI::Module::SetName( const XE::String & val )
{
	_Name = val;
}

XE::Variant AI::Module::GetKey( const AI::BlackboardKey & val ) const
{
	auto it = _Keys.find( val.GetKey() );
	if( it != _Keys.end() )
	{
		return it->second;
	}
	return {};
}

void AI::Module::SetKey( const AI::BlackboardKey & key, const XE::Variant & val )
{
	_Keys[key.GetKey()] = val;
}

const XE::Map<XE::String, XE::Variant> & AI::Module::GetKeys() const
{
	return _Keys;
}

void AI::Module::SetKeys( const XE::Map<XE::String, XE::Variant> & val )
{
	_Keys = val;
}

void AI::Module::AssetLoad()
{
	Super::AssetLoad();

	auto cls = XE_ClassID<XE::Asset>::Get();
	for( auto & key : _Keys )
	{
		if( key.second.GetType() == cls )
		{
			if( XE::ObjectPtr obj = key.second.Value<XE::ObjectPtr>() )
			{
				obj->AssetLoad();
			}
		}
	}
}

void AI::Module::PostEvent( const XE::EventPtr & val )
{
	if( _ProcessEventCallback )
	{
		_ProcessEventCallback( std::ref( val ) );
	}
	else
	{
		ProcessEvent( val );
	}
}

void AI::Module::SetProcessEventCallback( const ProcessEventCallback & val )
{
	_ProcessEventCallback = val;
}
