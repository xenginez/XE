#include "UserInterface.h"

#include "Widget.h"

USING_XE

BEG_META( UserInterface )
END_META()

UserInterface::UserInterface()
{

}

UserInterface::~UserInterface()
{

}

WidgetPtr UserInterface::GetWidget( WidgetHandle val ) const
{
	return _Widgets.at( val.GetValue() );
}

WidgetHandle UserInterface::AddWidget( const IMetaClassPtr & val )
{
	if (val )
	{
		if( auto widget = val->ConstructPtr().Value<WidgetPtr>() )
		{
			_Widgets.push_back( widget );

			return { _Widgets.size() - 1 };
		}
	}

	return WidgetHandle::Invalid;
}

void UserInterface::RemoveWidget( WidgetHandle val )
{
	if( _Widgets.at( val.GetValue() ) != nullptr )
	{
		_Widgets[val.GetValue()]->OnRemove();

		_Widgets[val.GetValue()] = nullptr;
	}
}
