#include "Blueprint.h"

#include "AIElement.h"

BEG_META( XE::Blueprint )
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

		if( element->GetType() == XE::AIElementType::SUB_ELEMENET )
		{
			_Subs.push_back( static_cast< XE::SubElement * >( element.get() ) );
		}
		else if( element->GetType() == XE::AIElementType::EVENT_ELEMENET )
		{
			auto event = static_cast< XE::EventElement * >( element.get() );
			
			if( event->GetListenerEvent() == EVENT_UPDATE )
			{
				_Updates.push_back( event );
			}

			_Events.push_back( event );
		}
	}

	for( auto sub : _Subs )
	{
		sub->Startup();
	}

	for( auto event : _Events )
	{
		if( event->GetListenerEvent() == EVENT_START )
		{
			event->Execute();
		}
	}
}

void XE::Blueprint::Enter()
{
	Super::Enter();

	for( auto sub : _Subs )
	{
		sub->Enter();
	}

	for( auto event : _Events )
	{
		if( event->GetListenerEvent() == EVENT_ENTER )
		{
			event->Execute();
		}
	}
}

void XE::Blueprint::Update( XE::float32 dt )
{
	Super::Update( dt );

	for( auto event : _Updates )
	{
		event->SetValue( dt );

		event->Execute();
	}
}

void XE::Blueprint::Quit()
{
	for( auto sub : _Subs )
	{
		sub->Quit();
	}

	for( auto event : _Events )
	{
		if( event->GetListenerEvent() == EVENT_QUIT )
		{
			event->Execute();
		}
	}

	Super::Quit();
}

void XE::Blueprint::Clearup()
{
	for( auto sub : _Subs )
	{
		sub->Clearup();
	}
	for( auto event : _Events )
	{
		if( event->GetListenerEvent() == EVENT_CLEAR )
		{
			event->Execute();
		}
	}
	for( auto element : _Elements )
	{
		element->SetBlueprint( nullptr );
	}

	_Subs.clear();
	_Events.clear();
	_Updates.clear();

	Super::Clearup();
}

bool XE::Blueprint::IsStopped() const
{
	return _Events.size() == 0;
}

void XE::Blueprint::AssetLoad()
{
	Super::AssetLoad();

	for( auto & element : _Elements )
	{
		element->AssetLoad();
	}
}

void XE::Blueprint::ProcessEvent( const EventPtr & val )
{
	if( val && !val->accept )
	{
		for( auto event : _Events )
		{
			if( event->GetListenerEvent() == val->handle )
			{
				event->SetValue( val->parameter );

				event->Execute();
			}
		}

		if( !val->accept )
		{
			Super::ProcessEvent( val );
		}
	}
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
