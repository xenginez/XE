/*!
 * \file   D3DRHI.h
 *
 * \author ZhengYuanQing
 * \date   2019/07/02
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __D3DRHI_H__7A52B7D1_A459_455A_B8B8_825CE7AE9948
#define __D3DRHI_H__7A52B7D1_A459_455A_B8B8_825CE7AE9948

#include "Type.h"

BEG_XE_NAMESPACE

class D3DRHI : public XE::IPlugin
{
public:
	D3DRHI( IFrameworkPtr framework );

	virtual ~D3DRHI();

public:
	String GetName() const override;

public:
	void Startup() override;

	void Clearup() override;

};

END_XE_NAMESPACE

#endif // __D3DRHI_H__7A52B7D1_A459_455A_B8B8_825CE7AE9948
