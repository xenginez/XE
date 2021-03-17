#include "GraphicsContextMetal.h"

#if PLATFORM_OS & ( OS_MAC | OS_IOS )

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <QuartzCore/CAMetalLayer.h>

#ifdef PLATFORM_OS == OS_IOS
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

#import <Foundation/Foundation.h>

BEG_XE_NAMESPACE

namespace MTL
{
	class BlitCommandEncoder
	{
	};
	class Buffer
	{
	};
	class CommandBuffer
	{
	};
	class CommandQueue
	{
	};
	class ComputeCommandEncoder
	{
	};
	class Device
	{
	};
	class Function
	{
	};
	class Library
	{
	};
	class RenderCommandEncoder
	{
	};
	class Texture
	{
	};
	class RenderContext
	{
	};

	XE::MTL::RenderContext * _RTX = nullptr;

}

END_XE_NAMESPACE

XE::GraphicsContextMetal::GraphicsContextMetal()
{

}

XE::GraphicsContextMetal::~GraphicsContextMetal()
{

}

void XE::GraphicsContextMetal::OnRender( XE::Frame * val )
{

}

#endif