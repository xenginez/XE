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

BEG_GUI_NAMESPACE

class GUI_API HBoxLayout : public GUI::Layout
{
	OBJECT( HBoxLayout, Layout )

public:
	HBoxLayout();

	~HBoxLayout() override;

private:
	void OnGeometryChanged( const XE::Recti & val ) override;

};

END_GUI_NAMESPACE

#endif // HBOXLAYOUT_H__25901A54_98A9_4E2F_AB3D_47AC86ECDFA1
