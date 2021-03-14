#include "UserInterface.h"

#include "Widget.h"

BEG_META( GUI::UserInterface )
END_META()

GUI::UserInterface::UserInterface()
{

}

GUI::UserInterface::~UserInterface()
{

}

GUI::WidgetPtr GUI::UserInterface::GetWidget( GUI::WidgetHandle val ) const
{
	return _Widgets.at( val.GetValue() );
}

GUI::WidgetHandle GUI::UserInterface::AddWidget( const XE::IMetaClassPtr & val )
{
	if (val )
	{
		if( auto widget = val->ConstructPtr().Value<GUI::WidgetPtr>() )
		{
			_Widgets.push_back( widget );

			return XE::HandleCast< GUI::Widget >( _Widgets.size() - 1 );
		}
	}

	return WidgetHandle::Invalid;
}

void GUI::UserInterface::RemoveWidget( GUI::WidgetHandle val )
{
	if( _Widgets.at( val.GetValue() ) != nullptr )
	{
		_Widgets[val.GetValue()]->OnRemove();

		_Widgets[val.GetValue()] = nullptr;
	}
}
