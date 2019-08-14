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

class GRAPHICS_API Technique : public XE::Object
{
	OBJECT( Technique, Object )

public:
	Technique();

	~Technique() override;

public:
	void Startup( RenderContextPtr & context );

	void Render( RenderContextPtr & context );

	void Clearup( RenderContextPtr & context );

protected:
	virtual void OnStartup( RenderContextPtr & context ) = 0;

	virtual void OnRender( RenderContextPtr & context ) = 0;

	virtual void OnClearup( RenderContextPtr & context ) = 0;

private:
	Array<RenderPassPtr> _Passes;
};

END_XE_NAMESPACE

#endif // TECHNIQUE_H__B017FCDC_2462_4404_A798_ECC98DAB2131
