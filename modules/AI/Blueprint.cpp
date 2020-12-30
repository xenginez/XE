#include "Blueprint.h"

#include "Element.h"

BEG_META( AI::Blueprint )
type->Property( "Elements", &AI::Blueprint::_Elements, XE::IMetaProperty::NoDesign );
END_META()

AI::Blueprint::Blueprint()
{

}

AI::Blueprint::~Blueprint()
{

}

void AI::Blueprint::Startup()
{
	Super::Startup();

	for( auto element : _Elements )
	{
		element->SetBlueprint( XE_THIS( Blueprint ) );

		element->Startup();

		if( element->GetType() == AI::AIElementType::EVENT_ELEMENET )
		{
			auto event = static_cast< AI::EventElement * >( element.get() );
			
			if( event->GetListenerEvent() == EVENT_UPDATE )
			{
				_Updates.push_back( event );
			}

			_Events.push_back( event );
		}
	}

	for( auto event : _Events )
	{
		if( event->GetListenerEvent() == EVENT_START )
		{
			event->Execute();
		}
	}
}

void AI::Blueprint::Enter()
{
	Super::Enter();

	for( auto event : _Events )
	{
		if( event->GetListenerEvent() == EVENT_ENTER )
		{
			event->Execute();
		}
	}
}

void AI::Blueprint::Update( XE::float32 dt )
{
	Super::Update( dt );

	for( auto event : _Updates )
	{
		SP_CAST<AI::VariantOutputPort>( event->GetOutputPort() )->Result = dt;

		event->Execute();
	}
}

void AI::Blueprint::Quit()
{
	for( auto event : _Events )
	{
		if( event->GetListenerEvent() == EVENT_QUIT )
		{
			event->Execute();
		}
	}

	Super::Quit();
}

void AI::Blueprint::Clearup()
{
	for( auto event : _Events )
	{
		if( event->GetListenerEvent() == EVENT_CLEAR )
		{
			event->Execute();
		}
	}

	for( auto element : _Elements )
	{
		element->Clearup();

		element->SetBlueprint( nullptr );
	}

	_Events.clear();
	_Updates.clear();

	Super::Clearup();
}

bool AI::Blueprint::IsStopped() const
{
	return _Events.size() == 0;
}

void AI::Blueprint::AssetLoad()
{
	Super::AssetLoad();

	for( auto & element : _Elements )
	{
		element->AssetLoad();
	}
}

void AI::Blueprint::ProcessEvent( const XE::EventPtr & val )
{
	if( val && !val->accept )
	{
		for( auto event : _Events )
		{
			if( event->GetListenerEvent() == val->handle )
			{
				SP_CAST<AI::VariantOutputPort>( event->GetOutputPort() )->Result = val->parameter;

				event->Execute();
			}
		}

		if( !val->accept )
		{
			Super::ProcessEvent( val );
		}
	}
}

const XE::Array< AI::ElementPtr > & AI::Blueprint::GetElements() const
{
	return _Elements;
}

void AI::Blueprint::SetElements( const XE::Array< AI::ElementPtr > & val )
{
	_Elements = val;
}

AI::ElementPtr AI::Blueprint::GetElement( AI::ElementHandle val ) const
{
	XE_ASSERT( val.GetValue() <= _Elements.size() );

	return _Elements[val.GetValue()];
}
