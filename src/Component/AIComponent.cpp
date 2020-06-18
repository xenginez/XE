#include "AIComponent.h"



BEG_META( XE::AIComponent )
type->Property( "AIModules", &AIComponent::_AIModules );
END_META()

XE::AIComponent::AIComponent()
{

}

XE::AIComponent::~AIComponent()
{

}

void XE::AIComponent::OnStartup()
{
	Super::OnStartup();

	for ( auto ai : _AIModules )
	{
		ai->Startup();
	}
}

void XE::AIComponent::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	for ( auto ai : _AIModules )
	{
		ai->Update( dt );
	}
}

void XE::AIComponent::OnClearup()
{
	for ( auto ai : _AIModules )
	{
		ai->Clearup();
	}

	Super::OnClearup();
}
