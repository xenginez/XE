#include "UserInterface.h"

#include "Widget.h"



BEG_META( XE::UserInterface )
END_META()

XE::UserInterface::UserInterface()
{

}

XE::UserInterface::~UserInterface()
{

}

XE::WidgetPtr XE::UserInterface::GetWidget( XE::WidgetHandle val ) const
{
	return _Widgets.at( val.GetValue() );
}

XE::WidgetHandle XE::UserInterface::AddWidget( const XE::IMetaClassPtr & val )
{
	if (val )
	{
		if( auto widget = val->ConstructPtr().Value<XE::WidgetPtr>() )
		{
			_Widgets.push_back( widget );

			return { _Widgets.size() - 1 };
		}
	}

	return WidgetHandle::Invalid;
}

void XE::UserInterface::RemoveWidget( XE::WidgetHandle val )
{
	if( _Widgets.at( val.GetValue() ) != nullptr )
	{
		_Widgets[val.GetValue()]->OnRemove();

		_Widgets[val.GetValue()] = nullptr;
	}
}
