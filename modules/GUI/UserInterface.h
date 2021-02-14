/*!
 * \file	UserInterface.h
 *
 * \author	ZhengYuanQing
 * \date	2019/12/09
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef USERINTERFACE_H__3FB036E9_A433_47B5_ACE1_58CC58FE6680
#define USERINTERFACE_H__3FB036E9_A433_47B5_ACE1_58CC58FE6680

#include "Type.h"

BEG_GUI_NAMESPACE

class GUI_API UserInterface : public XE::Object
{
	OBJECT( UserInterface, Object )

public:
	UserInterface();

	~UserInterface() override;

public:
	WidgetPtr GetWidget( WidgetHandle val ) const;

	WidgetHandle AddWidget( const XE::IMetaClassPtr & val );

	void RemoveWidget( WidgetHandle val );

public:
	template< typename T > WidgetHandle AddWidgetT()
	{
		return AddWidget( XE_ClassID<T>::Get() );
	}

	template< typename T > XE::SharedPtr<T> GetWidgetT() const
	{
		return SP_CAST<T>( GetWidget( XE_ClassID<T>::Get() ) );
	}

private:
	XE::Array<WidgetPtr> _Widgets;
};

END_GUI_NAMESPACE

#endif // USERINTERFACE_H__3FB036E9_A433_47B5_ACE1_58CC58FE6680
