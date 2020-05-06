/*!
 * \file	RendererContextVulkan.h
 *
 * \author	ZhengYuanQing
 * \date	2020/05/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTVULKAN_H__9B474D4E_3242_4EE9_87DC_ABE7A51DAE85
#define RENDERERCONTEXTVULKAN_H__9B474D4E_3242_4EE9_87DC_ABE7A51DAE85

#if PLATFORM_OS & OS_WINDOWS

#include "RendererContext.h"

BEG_XE_NAMESPACE

class RendererContextVulkan : public XE::RendererContext
{
public:
	RendererContextVulkan();

	~RendererContextVulkan() override;

public:
	void Init( const InitInfo & val ) override;

	void Shutdown() override;

private:

};

END_XE_NAMESPACE

XE::RendererContext * CreateRendererContextVulkan()
{
	return new XE::RendererContextVulkan();
}
#else
XE::RendererContext * CreateRendererContextVulkan()
{
	return nullptr;
}
#endif

#endif // RENDERERCONTEXTVULKAN_H__9B474D4E_3242_4EE9_87DC_ABE7A51DAE85
