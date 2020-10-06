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

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API UserInterface : public XE::Object
{
	OBJECT( UserInterface, Object )

public:
	UserInterface();

	~UserInterface() override;

public:
	WidgetPtr GetWidget( WidgetHandle val ) const;

	WidgetHandle AddWidget( const IMetaClassPtr & val );

	void RemoveWidget( WidgetHandle val );

public:
	template< typename T > WidgetHandle AddWidgetT()
	{
		return AddWidget( ClassID<T>::Get() );
	}

	template< typename T > XE::SharedPtr<T> GetWidgetT() const
	{
		return SP_CAST<T>( GetWidget( ClassID<T>::Get() ) );
	}

private:
	XE::Array<WidgetPtr> _Widgets;
};

END_XE_NAMESPACE

#endif // USERINTERFACE_H__3FB036E9_A433_47B5_ACE1_58CC58FE6680
