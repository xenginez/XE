/*!
 * \file	HBoxLayout.h
 *
 * \author	ZhengYuanQing
 * \date	2019/12/06
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef HBOXLAYOUT_H__25901A54_98A9_4E2F_AB3D_47AC86ECDFA1
#define HBOXLAYOUT_H__25901A54_98A9_4E2F_AB3D_47AC86ECDFA1

#include "Layout.h"

BEG_XE_NAMESPACE

class XE_API HBoxLayout : public XE::Layout
{
	OBJECT( HBoxLayout, Layout )

public:
	HBoxLayout();

	~HBoxLayout() override;

private:
	void OnGeometryChanged( const XE::Rect & val );

private:
	XE::Slot<const XE::Rect &> _OnGeometryChanged;
};

END_XE_NAMESPACE

#endif // HBOXLAYOUT_H__25901A54_98A9_4E2F_AB3D_47AC86ECDFA1
