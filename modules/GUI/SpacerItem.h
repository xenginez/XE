/*!
 * \file	SpacerItem.h
 *
 * \author	ZhengYuanQing
 * \date	2019/12/09
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SPACERITEM_H__E3894CC6_BA88_46EF_B7B8_A6AA26FF5207
#define SPACERITEM_H__E3894CC6_BA88_46EF_B7B8_A6AA26FF5207

#include "Widget.h"

BEG_GUI_NAMESPACE

class GUI_API SpacerItem : public GUI::Widget
{
	OBJECT( SpacerItem, Widget )

public:
	SpacerItem();

	~SpacerItem() override;

public:
	SizePolicy GetSizePolicy() const;

	void SetSizePolicy( SizePolicy val );

	Orientation GetOrientation() const;

	void SetOrientation( Orientation val );

	const XE::Vec2i & GetSizeHint() const;

	void SetSizeHint( const XE::Vec2i & val );

public:
	XE::Vec2i SizeHint() const override;

private:
	XE::Vec2i _SizeHint;
	SizePolicy _SizePolicy;
	Orientation _Orientation;
};

END_GUI_NAMESPACE

#endif // SPACERITEM_H__E3894CC6_BA88_46EF_B7B8_A6AA26FF5207
