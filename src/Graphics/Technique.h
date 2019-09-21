/*!
 * \file	Technique.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef TECHNIQUE_H__B017FCDC_2462_4404_A798_ECC98DAB2131
#define TECHNIQUE_H__B017FCDC_2462_4404_A798_ECC98DAB2131

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Technique : public XE::Object
{
	OBJECT( Technique, Object )

public:
	Technique();

	~Technique() override;

public:
	void Startup( IRenderContextPtr & context );

	void Render( IRenderContextPtr & context );

	void Clearup( IRenderContextPtr & context );

protected:
	virtual void OnStartup( IRenderContextPtr & context ) = 0;

	virtual void OnRender( IRenderContextPtr & context ) = 0;

	virtual void OnClearup( IRenderContextPtr & context ) = 0;

private:
	Array<RenderPassPtr> _Passes;
};

END_XE_NAMESPACE

#endif // TECHNIQUE_H__B017FCDC_2462_4404_A798_ECC98DAB2131
