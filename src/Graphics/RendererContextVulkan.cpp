#include "RendererContextVulkan.h"

#if PLATFORM_OS & ( OS_WINDOWS | OS_ANDROID | OS_LINUX )

#if PLATFORM_OS == OS_ANDROID
#	define VK_USE_PLATFORM_ANDROID_KHR
#	define KHR_SURFACE_EXTENSION_NAME VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_ANDROID
#elif PLATFORM_OS == OS_LINUX
//#	define VK_USE_PLATFORM_MIR_KHR
#	define VK_USE_PLATFORM_XCB_KHR
#	define VK_USE_PLATFORM_XLIB_KHR
//#	define VK_USE_PLATFORM_WAYLAND_KHR
#	define KHR_SURFACE_EXTENSION_NAME VK_KHR_XCB_SURFACE_EXTENSION_NAME
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_LINUX
#elif PLATFORM_OS == OS_WINDOWS
#	define VK_USE_PLATFORM_WIN32_KHR
#	define KHR_SURFACE_EXTENSION_NAME  VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_WINDOWS
#endif

#define VK_NO_STDDEF_H
#define VK_NO_STDINT_H
#define VK_NO_PROTOTYPES

extern "C"
{
#include <vulkan/vulkan.h>
}

BEG_XE_NAMESPACE

namespace VK
{
	class ScratchBuffer
	{
	};
	class Image
	{
	};
	class Buffer
	{
	};
	class VertexBuffer
	{
	};
	class Shader
	{
	};
	class Program
	{
	};
	class Texture
	{
	};
	class FrameBuffer
	{
	};
	class RenderContext
	{
	};

	XE::VK::RenderContext * _RTX = nullptr;

}

END_XE_NAMESPACE

XE::RendererContextVulkan::RendererContextVulkan()
{

}

XE::RendererContextVulkan::~RendererContextVulkan()
{

}

void XE::RendererContextVulkan::OnRender( XE::RenderFrame* val )
{

}

#endif