/*!
 * \file	Widget.h
 *
 * \author	ZhengYuanQing
 * \date	2019/06/14
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef WIDGET_H__481BAA7C_32B3_4B89_9156_D53C896040D7
#define WIDGET_H__481BAA7C_32B3_4B89_9156_D53C896040D7

#include "Math/Mathf.h"
#include "Utils/Object.h"
#include "Utils/Signals.hpp"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Widget : public XE::Object
{
	OBJECT( Widget, Object )

public:
	Widget();

	~Widget() override;

public:
	bool GetEnable() const;

	void SetEnable( bool val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	WidgetHandle GetHandle() const;

	void SetHandle( WidgetHandle val );

	WidgetHandle GetParentHandle() const;

	void SetParentHandle( WidgetHandle val );

	const UserInterfacePtr & GetUserInterface() const;

	void SetUserInterface( const UserInterfacePtr & val );

public:
	XE::Vec2 GetSize() const;

	void SetSize( const XE::Vec2 & val );

	XE::Vec2 GetPosition() const;

	void SetPosition( const XE::Vec2 & val );

	const XE::Rect & GetGeometry() const;

	void SetGeometry( const XE::Rect & val );

	const XE::Vec2 & GetMinimumSize() const;

	void SetMinimunSize( const XE::Vec2 & val );

	const XE::Vec2 & GetMaximumSize() const;

	void SetMaximunSize( const XE::Vec2 & val );

public:
	virtual void Render();

public:
	virtual void OnRemove();

public:
	virtual XE::Vec2 SizeHint() const;

public:
	XE::Signal<const XE::Rect&> GeometryChanged;

private:
	bool _Enable;
	XE::String _Name;
	WidgetHandle _Handle;
	WidgetHandle _ParentHandle;
	XE::Vec2 _MinSize;
	XE::Vec2 _MaxSize;
	XE::Rect _Geometry;
	UserInterfacePtr _UI;
};

END_XE_NAMESPACE

#endif // WIDGET_H__481BAA7C_32B3_4B89_9156_D53C896040D7