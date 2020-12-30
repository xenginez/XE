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

#include "Type.h"

BEG_GUI_NAMESPACE

class GUI_API Widget : public XE::Object
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

	GUI::WidgetHandle GetHandle() const;

	void SetHandle( GUI::WidgetHandle val );

	GUI::WidgetHandle GetParentHandle() const;

	void SetParentHandle( GUI::WidgetHandle val );

	const GUI::UserInterfacePtr & GetUserInterface() const;

	void SetUserInterface( const GUI::UserInterfacePtr & val );

public:
	XE::Vec2i GetSize() const;

	void SetSize( const XE::Vec2i & val );

	XE::Vec2i GetPosition() const;

	void SetPosition( const XE::Vec2i & val );

	const XE::Recti & GetGeometry() const;

	void SetGeometry( const XE::Recti & val );

	const XE::Vec2i & GetMinimumSize() const;

	void SetMinimunSize( const XE::Vec2i & val );

	const XE::Vec2i & GetMaximumSize() const;

	void SetMaximunSize( const XE::Vec2i & val );

public:
	virtual void Render();

public:
	virtual void OnRemove();

public:
	virtual XE::Vec2i SizeHint() const;

public:
	XE::Signal< const XE::Recti & > GeometryChanged;

private:
	bool _Enable;
	XE::String _Name;
	WidgetHandle _Handle;
	WidgetHandle _ParentHandle;
	XE::Vec2i _MinSize;
	XE::Vec2i _MaxSize;
	XE::Recti _Geometry;
	UserInterfacePtr _UI;
};

END_GUI_NAMESPACE

#endif // WIDGET_H__481BAA7C_32B3_4B89_9156_D53C896040D7