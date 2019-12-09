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

BEG_XE_NAMESPACE

class XE_API SpacerItem : public XE::Widget
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

	const XE::Vec2 & GetSizeHint() const;

	void SetSizeHint( const XE::Vec2 & val );

public:
	XE::Vec2 SizeHint() const override;

private:
	XE::Vec2 _SizeHint;
	SizePolicy _SizePolicy;
	Orientation _Orientation;
};

END_XE_NAMESPACE

#endif // SPACERITEM_H__E3894CC6_BA88_46EF_B7B8_A6AA26FF5207
