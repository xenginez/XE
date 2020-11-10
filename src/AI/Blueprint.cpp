#include "Blueprint.h"

#include "AIElement.h"

BEG_META( XE::Blueprint )
type->Property( "Startup", &Blueprint::_StartupRoot, IMetaProperty::NoDesign );
type->Property( "Update", &Blueprint::_UpdateRoot, IMetaProperty::NoDesign );
type->Property( "Clearup", &Blueprint::_ClearupRoot, IMetaProperty::NoDesign );
type->Property( "Elements", &Blueprint::_Elements, IMetaProperty::NoDesign );
END_META()

XE::Blueprint::Blueprint()
{

}

XE::Blueprint::~Blueprint()
{

}

void XE::Blueprint::Startup()
{
	Super::Startup();

	for( auto element : _Elements )
	{
		element->SetBlueprint( XE_THIS( Blueprint ) );
	}

	auto handle = _StartupRoot;
	while( handle )
	{
		_Elements[handle]->Execute();

		handle = _Elements[handle]->GetNextHandle();
	}
}

void XE::Blueprint::Update( XE::float32 dt )
{
	Super::Update( dt );

	auto handle = _UpdateRoot;
	while( handle )
	{
		_Elements[handle]->Execute();

		handle = _Elements[handle]->GetNextHandle();
	}
}

void XE::Blueprint::Clearup()
{
	auto handle = _ClearupRoot;
	while( handle )
	{
		_Elements[handle]->Execute();

		handle = _Elements[handle]->GetNextHandle();
	}

	for( auto element : _Elements )
	{
		element->SetBlueprint( nullptr );
	}

	Super::Clearup();
}

void XE::Blueprint::AssetLoad()
{
	Super::AssetLoad();

	for( auto & element : _Elements )
	{
		element->AssetLoad();
	}
}

XE::AIElementHandle XE::Blueprint::GetStartupRoot() const
{
	return _StartupRoot;
}

void XE::Blueprint::SetStartupRoot( XE::AIElementHandle val )
{
	_StartupRoot = val;
}

XE::AIElementHandle XE::Blueprint::GetUpdateRoot() const
{
	return _UpdateRoot;
}

void XE::Blueprint::SetUpdateRoot( XE::AIElementHandle val )
{
	_UpdateRoot = val;
}

XE::AIElementHandle XE::Blueprint::GetClearupRoot() const
{
	return _ClearupRoot;
}

void XE::Blueprint::SetClearupRoot( XE::AIElementHandle val )
{
	_ClearupRoot = val;
}

const XE::Array< XE::AIElementPtr > & XE::Blueprint::GetElements() const
{
	return _Elements;
}

void XE::Blueprint::SetElements( const XE::Array< XE::AIElementPtr > & val )
{
	_Elements = val;
}

XE::AIElementPtr XE::Blueprint::GetElement( XE::AIElementHandle val ) const
{
	XE_ASSERT( val.GetValue() <= _Elements.size() );

	return _Elements[val.GetValue()];
}
