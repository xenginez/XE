/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
#define __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848

#include "Global.h"

#include <bgfx/bgfx.h>
#include <bgfx/defines.h>
#include <bgfx/platform.h>
#include <bgfx/embedded_shader.h>

BEG_XE_NAMESPACE

using Attribute = bgfx::Attrib::Enum;
using AttributeType = bgfx::AttribType::Enum;
using TextureFormat = bgfx::TextureFormat::Enum;
using RendererType = bgfx::RendererType::Enum;
using BackbufferRatio = bgfx::BackbufferRatio::Enum;
using UniformType = bgfx::UniformType::Enum;
using Access = bgfx::Access::Enum;
using ViewMode = bgfx::ViewMode::Enum;
using OcclusionQueryResult = bgfx::OcclusionQueryResult::Enum;
using TopologyConversion = bgfx::TopologyConvert::Enum;
using TopologySort = bgfx::TopologySort::Enum;
using Topology = bgfx::Topology::Enum;

using InitType = bgfx::Init;
using VertexLayout = bgfx::VertexDecl;
using Encoder = bgfx::Encoder;
using MemoryView = bgfx::Memory;
using TextureInfo = bgfx::TextureInfo;
using UniformInfo = bgfx::UniformInfo;
using Attachment = bgfx::Attachment;
using PlatformData = bgfx::PlatformData;
using TransformData = bgfx::Transform;
using Caps = bgfx::Caps;
using Stats = bgfx::Stats;
using EmbeddedShader = bgfx::EmbeddedShader;
using TransientVertexBuffer = bgfx::TransientVertexBuffer;
using TransientIndexBuffer = bgfx::TransientIndexBuffer;
using InstanceDataBuffer = bgfx::InstanceDataBuffer;

using ViewHandle = bgfx::ViewId;
using DynamicIndexBufferHandle = bgfx::DynamicIndexBufferHandle;
using DynamicVertexBufferHandle = bgfx::DynamicVertexBufferHandle;
using FrameBufferHandle = bgfx::FrameBufferHandle;
using IndexBufferHandle = bgfx::IndexBufferHandle;
using IndirectBufferHandle = bgfx::IndirectBufferHandle;
using OcclusionQueryHandle = bgfx::OcclusionQueryHandle;
using ProgramHandle = bgfx::ProgramHandle;
using ShaderHandle = bgfx::ShaderHandle;
using TextureHandle = bgfx::TextureHandle;
using UniformHandle = bgfx::UniformHandle;
using VertexBufferHandle = bgfx::VertexBufferHandle;
using VertexDeclHandle = bgfx::VertexDeclHandle;

DECL_PTR(Shader);

DECL_PTR(Program);

DECL_PTR(Uniform);

DECL_PTR(Texture);

DECL_PTR(RenderView);

DECL_PTR(RenderPass);

DECL_PTR(IndexBuffer);

DECL_PTR(FrameBuffer);

DECL_PTR(VertexBuffer);

DECL_PTR(GPUProgram);

DECL_PTR(Mesh);

DECL_PTR(StaticMesh);

DECL_PTR(DynamicMesh);

DECL_PTR(SkeletonMesh);

DECL_PTR(Model);

DECL_PTR(Material);

DECL_PTR(Bone);

DECL_PTR(Skeleton);


enum class FormatSearchFlags
{
	ONE_CHANNEL = 0x1,
	TWO_CHANNELS = 0x2,
	FOUR_CHANNELS = 0x8,
	REQUIRES_ALPHA = 0x10,
	REQUIRES_STENCIL = 0x20,
	PREFER_COMPRESSED = 0x40,
	
	ALLOW_PADDING_CHANNELS = 0x100,
	REQUIRES_DEPTH = 0x200,
	
	HALF_PRECISION_FLOAT = 0x1000,
	FULL_PRECISION_FLOAT = 0x2000,
	FLOATING_POINT = 0xF000,
};

enum class ProjectionMode
{
	PERSPECTIVE, ORTHOGRAPHIC,
};

enum class CullType
{
	NONE, CLOCKWISE, COUNTER_CLOCKWISE,
};

enum class TriangleFlags
{
	NONE, DEGENERATE,
};

enum class MeshStatus
{
	NOT_PREPARED, PREPARING, PREPARED
};

enum class MeshCreateOrigin
{
	BOTTOM, CENTER, TOP
};


// DECL_HANDLE( RENDER_API, View );
// DECL_HANDLE( RENDER_API, DynamicIndexBuffer );
// DECL_HANDLE( RENDER_API, DynamicVertexBuffer );
// DECL_HANDLE( RENDER_API, FrameBuffer );
// DECL_HANDLE( RENDER_API, IndexBuffer );
// DECL_HANDLE( RENDER_API, IndirectBuffer );
// DECL_HANDLE( RENDER_API, OcclusionQuery );
// DECL_HANDLE( RENDER_API, Program );
// DECL_HANDLE( RENDER_API, Shader );
// DECL_HANDLE( RENDER_API, Texture );
// DECL_HANDLE( RENDER_API, Uniform );
// DECL_HANDLE( RENDER_API, VertexBuffer );
// DECL_HANDLE( RENDER_API, VertexDecl );

END_XE_NAMESAPCE

#endif // __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
