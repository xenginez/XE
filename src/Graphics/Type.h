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

DECL_PTR(SkinnedMesh);

DECL_PTR(Model);

DECL_PTR(Material);


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



class GRAPHICS_API VertexInfluence
{
public:
	float Weight;
	uint32 VertexIndex;
};

class GRAPHICS_API BoneInfluence
{
public:
	String Name;
	Mat4 Transform;
	Array < VertexInfluence > Influences;
};

class GRAPHICS_API VertexData
{
public:
	uint32 Origin;
	int32 Palette;
	Array < float > Weights;
	Array < uint32 > Influences;
};

class GRAPHICS_API SkinBindData
{
public:
	SkinBindData();
	
	~SkinBindData();

public:
	void AddBone( const BoneInfluence &bone );
	
	void RemoveEmptyBones();
	
	void
	BuildVertexTable( std::uint32_t vertex_count, const std::vector < std::uint32_t > &vertex_remap, Array < VertexData > &table );
	
	void RemapVertices( const std::vector < std::uint32_t > &remap );
	
	const Array < BoneInfluence > &GetBones() const;
	
	Array < BoneInfluence > &GetBones();
	
	bool HasBones() const;
	
	const BoneInfluence * FindBoneById( const String &id ) const;
	
	void ClearVertexInfluences();
	
	void Clear();

private:
	Array < BoneInfluence > _Bones;
};

class GRAPHICS_API BonePalette
{
public:
	using BoneIndexMap = Map < XE::uint32, XE::uint32 >;

public:
	BonePalette();
	
	BonePalette( XE::uint32 val );
	
	BonePalette( const BonePalette &val );
	
	~BonePalette();

public:
	Array < XE::Mat4 >
	GetSkinningMatrices( const Array < Mat4 > &node_transforms, const SkinBindData &bind_data, bool compute_inverse_transpose ) const;
	
	void
	ComputePaletteFit( BoneIndexMap &input, XE::int32 &current_space, XE::int32 &common_bones, XE::int32 &additional_bones );
	
	void AssignBones( BoneIndexMap &bones, Array < XE::uint32 > &faces );
	
	void AssignBones( const Array < XE::uint32 > &bones );
	
	XE::uint32 TranslateBoneToPalette( XE::uint32 bone_index ) const;
	
	XE::int32 GetMaximumBlendIndex() const;
	
	XE::uint32 GetMaximumSize() const;
	
	XE::uint32 GetDataGroup() const;
	
	Array < XE::uint32 > &GetInfluencedFaces();
	
	const Array < XE::uint32 > &GetBones() const;
	
	void SetMaximumBlendIndex( int index );
	
	void SetDataGroup( XE::uint32 group );
	
	void ClearInfluencedFaces();

private:
	XE::uint32 _MaxSize;
	BoneIndexMap _BonesLut;
	XE::uint32 _DataGroupID;
	XE::int32 _MaxBlendIndex;
	Array < XE::uint32 > _Bones;
	Array < XE::uint32 > _Faces;
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
