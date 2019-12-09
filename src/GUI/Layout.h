/*!
 * \file	Layout.h
 *
 * \author	ZhengYuanQing
 * \date	2019/12/06
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef LAYOUT_H__4E6AD426_FBC0_48A4_81AB_7031D1DD7C8A
#define LAYOUT_H__4E6AD426_FBC0_48A4_81AB_7031D1DD7C8A

#include "Widget.h"

BEG_XE_NAMESPACE

class XE_API Layout : public XE::Widget
{
	OBJECT( Layout, Widget )

public:
	Layout();

	~Layout() override;

public:
	XE::real GetLeftMargin() const;

	void SetLeftMargin( XE::real val );

	XE::real GetTopMargin() const;

	void SetTopMargin( XE::real val );

	XE::real GetBottomMargin() const;

	void SetBottomMargin( XE::real val );

	XE::real GetRightMargin() const;

	void SetRightMargin( XE::real val );

	XE::real GetWidgetSpacing() const;

	void SetWidgetSpacing( XE::real val );

	SizeConstraint GetSizeConstraint() const;

	void SetSizeConstraint( SizeConstraint val );

public:
	XE::uint8 GetStretch( XE::uint64 val ) const;

	void SetStretch( XE::uint64 index, XE::uint8 val );

public:
	XE::Rect GetContentsRect() const;

public:
	XE::uint64 ChildCount() const;

	void AddChild( WidgetHandle val );

	void RemoveChild( WidgetHandle val );

	WidgetPtr GetChild( XE::uint64 val ) const;

	WidgetHandle GetChildHandle( XE::uint64 val ) const;

public:
	WidgetPtr GetWidget( WidgetHandle val ) const;

public:
	void Render() override;

protected:
	virtual void OnRender();

private:
	XE::real _LeftMargin;
	XE::real _TopMargin;
	XE::real _BottomMargin;
	XE::real _RightMargin;
	XE::real _WidgetSpacing;
	SizeConstraint _SizeConstraint;
	XE::Array< XE::Pair< WidgetHandle, XE::uint8> > _Children;
};

END_XE_NAMESPACE

#endif // LAYOUT_H__4E6AD426_FBC0_48A4_81AB_7031D1DD7C8A

