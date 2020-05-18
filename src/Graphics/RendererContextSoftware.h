#ifndef RENDERERCONTEXTSOFTWARE_H__3145856F_D79A_440A_90B3_558891CD1D3A
#define RENDERERCONTEXTSOFTWARE_H__3145856F_D79A_440A_90B3_558891CD1D3A

#include "RendererContext.h"

BEG_XE_NAMESPACE

class RendererContextSoftware : public XE::RendererContext
{
public:
	RendererContextSoftware();

	~RendererContextSoftware();

protected:
	void OnStartup() override;

	void OnRender( XE::Frame* val ) override;

	void OnClearup() override;

private:

};

XE::RendererContext * CreateRendererContextSoftware();

END_XE_NAMESPACE

#endif // RENDERERCONTEXTSOFTWARE_H__3145856F_D79A_440A_90B3_558891CD1D3A
