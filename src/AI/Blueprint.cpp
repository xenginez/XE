#include "Blueprint.h"

#include "AIElement.h"

BEG_META( XE::Blueprint )
type->Property( "Root", &Blueprint::_Root, IMetaProperty::NoDesign );
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
}

void XE::Blueprint::Update( XE::float32 dt )
{
	Super::Update( dt );

	auto handle = _Root;
	while( handle )
	{
		_Elements[handle]->Execute();

		handle = _Elements[handle]->GetNextHandle();
	}
}

void XE::Blueprint::Clearup()
{
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

XE::AIElementHandle XE::Blueprint::GetRoot() const
{
	return _StartupRoot;
}

void XE::Blueprint::SetRoot( XE::AIElementHandle val )
{
	_StartupRoot = val;
}

XE::AIElementHandle XE::Blueprint::GetUpdateRoot() const
{
	return _Root;
}

void XE::Blueprint::SetUpdateRoot( XE::AIElementHandle val )
{
	_Root = val;
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
