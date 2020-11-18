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
	XE::float32 GetLeftMargin() const;

	void SetLeftMargin( XE::float32 val );

	XE::float32 GetTopMargin() const;

	void SetTopMargin( XE::float32 val );

	XE::float32 GetBottomMargin() const;

	void SetBottomMargin( XE::float32 val );

	XE::float32 GetRightMargin() const;

	void SetRightMargin( XE::float32 val );

	XE::float32 GetWidgetSpacing() const;

	void SetWidgetSpacing( XE::float32 val );

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
	virtual void OnGeometryChanged( const XE::Rectf & val ) = 0;

private:
	XE::float32 _LeftMargin;
	XE::float32 _TopMargin;
	XE::float32 _BottomMargin;
	XE::float32 _RightMargin;
	XE::float32 _WidgetSpacing;
	SizeConstraint _SizeConstraint;
	XE::Slot<const XE::Rectf &> _OnGeometryChanged;
	XE::Array< XE::Pair< WidgetHandle, XE::uint8> > _Children;
};

END_XE_NAMESPACE

#endif // LAYOUT_H__4E6AD426_FBC0_48A4_81AB_7031D1DD7C8A

