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

BEG_GUI_NAMESPACE

class GUI_API Layout : public GUI::Widget
{
	OBJECT( Layout, Widget )

public:
	Layout();

	~Layout() override;

public:
	XE::uint32 GetLeftMargin() const;

	void SetLeftMargin( XE::uint32 val );

	XE::uint32 GetTopMargin() const;

	void SetTopMargin( XE::uint32 val );

	XE::uint32 GetBottomMargin() const;

	void SetBottomMargin( XE::uint32 val );

	XE::uint32 GetRightMargin() const;

	void SetRightMargin( XE::uint32 val );

	XE::uint32 GetWidgetSpacing() const;

	void SetWidgetSpacing( XE::uint32 val );

	SizeConstraint GetSizeConstraint() const;

	void SetSizeConstraint( SizeConstraint val );

public:
	XE::uint8 GetStretch( XE::uint64 val ) const;

	void SetStretch( XE::uint64 index, XE::uint8 val );

public:
	XE::Rectf GetContentsRect() const;

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

private:
	virtual void OnGeometryChanged( const XE::Recti & val ) = 0;

private:
	XE::uint32 _LeftMargin;
	XE::uint32 _TopMargin;
	XE::uint32 _BottomMargin;
	XE::uint32 _RightMargin;
	XE::uint32 _WidgetSpacing;
	SizeConstraint _SizeConstraint;
	XE::Slot< const XE::Recti & > _OnGeometryChanged;
	XE::Array< XE::Pair< WidgetHandle, XE::uint8> > _Children;
};

END_GUI_NAMESPACE

#endif // LAYOUT_H__4E6AD426_FBC0_48A4_81AB_7031D1DD7C8A

