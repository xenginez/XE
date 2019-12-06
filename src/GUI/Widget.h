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

	const WidgetPtr & GetParent() const;

	void SetParent( const WidgetPtr & val );

	const XE::Vec2 & GetMinimumSize() const;

	void SetMinimunSize( const XE::Vec2 & val );

	const XE::Vec2 & GetMaximumSize() const;

	void SetMaximunSize( const XE::Vec2 & val );

	const XE::Rect & GetBoundingRect() const;

	void SetBoundingRect( const XE::Rect & val );

public:
	virtual void Update();

	virtual void Render();

private:
	bool _Enable;
	XE::String _Name;
	WidgetPtr _Parent;
	XE::Vec2 _MinSize;
	XE::Vec2 _MaxSize;
	XE::Rect _BoundingRect;
};

END_XE_NAMESPACE

#endif // WIDGET_H__481BAA7C_32B3_4B89_9156_D53C896040D7