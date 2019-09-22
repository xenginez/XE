/*!
 * \file	Gfx.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GFX_H__12636FE6_A92D_467B_909E_9892450A6029
#define GFX_H__12636FE6_A92D_467B_909E_9892450A6029

#include "Type.h"

BEG_XE_NAMESPACE

class Gfx;

class XE_API Attachment
{
public:
	Access  access;
	TextureHandle handle;
	XE::uint16 mip;
	XE::uint16 layer;
	XE::uint8  resolve;
};

class XE_API UniformInfo
{
public:
	XE::String name;
	UniformType type;
	XE::uint16 num;
};

class XE_API TextureInfo
{
public:
	TextureFormat format;
	XE::uint32 storageSize;
	XE::uint16 width;
	XE::uint16 height;
	XE::uint16 depth;
	XE::uint16 numLayers;
	XE::uint8 numMips;
	XE::uint8 bitsPerPixel;
	bool    cubeMap;
};

class XE_API InstanceDataBuffer
{
public:
	XE::memory_view data;
	XE::uint32 offset;
	XE::uint32 num;
	XE::uint16 stride;
	VertexBufferHandle handle;
};

class XE_API TransientIndexBuffer
{
public:
	XE::memory_view data;
	XE::uint32 startIndex;
	IndexBufferHandle handle;
};

class XE_API TransientVertexBuffer
{
public:
	XE::memory_view data;
	XE::uint32 startVertex;
	XE::uint16 stride;
	VertexBufferHandle handle;
	VertexLayoutHandle layoutHandle;
};

class XE_API VertexLayout
{
public:
	VertexLayout();

	VertexLayout & begin( RendererType _renderer = RendererType::NOOP );

	void end();

	VertexLayout & add(
		Attrib _attrib
		, XE::uint8 _num
		, AttribType _type
		, bool _normalized = false
		, bool _asInt = false
	);

	VertexLayout & skip( XE::uint8 _num );

	void decode(
		Attrib _attrib
		, XE::uint8 & _num
		, AttribType & _type
		, bool & _normalized
		, bool & _asInt
	) const;

	bool has( Attrib _attrib ) const;

	XE::uint16 getOffset( Attrib _attrib ) const;

	XE::uint16 getStride() const;

	XE::uint32 getSize( XE::uint32 _num ) const;

	XE::uint32 m_hash;
	XE::uint16 m_stride;
	XE::uint16 m_offset[18];
	XE::uint16 m_attributes[18];
};

class XE_API Encoder
{
	friend class Gfx;

public:
	Encoder();

	Encoder( Encoder && val );

	Encoder & operator=( Encoder && val );

public:
	void setMarker( const XE::String & _marker );

	void setState(
		XE::uint64 _state
		, XE::uint32 _rgba = 0
	);

	void setCondition(
		OcclusionQueryHandle _handle
		, bool _visible
	);

	void setStencil(
		XE::uint32 _fstencil
		, StencilFlags _bstencil = StencilFlags::NONE
		//		, XE::uint32 _bstencil = BGFX_STENCIL_NONE
	);

	XE::uint16 setScissor(
		XE::uint16 _x
		, XE::uint16 _y
		, XE::uint16 _width
		, XE::uint16 _height
	);

	void setScissor( XE::uint16 _cache = UINT16_MAX );

	XE::uint32 setTransform(
		XE::basic_memory_view<Mat4> _transform
		// 		const void * _mtx
		// 		, XE::uint16 _num = 1
	);

	XE::uint32 allocTransform(
		XE::basic_memory_view<Mat4> _transform
		// 		Transform * _transform
		//		, XE::uint16 _num
	);

	void setTransform(
		XE::uint32 _cache
		, XE::uint16 _num = 1
	);

	void setUniform(
		UniformHandle _handle
		, XE::memory_view _value
		// 		, const void * _value
		// 		, XE::uint16 _num = 1
	);

	void setIndexBuffer( IndexBufferHandle _handle );

	void setIndexBuffer(
		IndexBufferHandle _handle
		, XE::uint32 _firstIndex
		, XE::uint32 _numIndices
	);

	void setIndexBuffer( DynamicIndexBufferHandle _handle );

	void setIndexBuffer(
		DynamicIndexBufferHandle _handle
		, XE::uint32 _firstIndex
		, XE::uint32 _numIndices
	);

	void setIndexBuffer( const TransientIndexBuffer * _tib );

	void setIndexBuffer(
		const TransientIndexBuffer * _tib
		, XE::uint32 _firstIndex
		, XE::uint32 _numIndices
	);

	void setVertexBuffer(
		XE::uint8 _stream
		, VertexBufferHandle _handle
	);

	void setVertexBuffer(
		XE::uint8 _stream
		, VertexBufferHandle _handle
		, XE::uint32 _startVertex
		, XE::uint32 _numVertices
		, VertexLayoutHandle _layoutHandle = VertexLayoutHandle()
	);

	void setVertexBuffer(
		XE::uint8 _stream
		, DynamicVertexBufferHandle _handle
	);

	void setVertexBuffer(
		XE::uint8 _stream
		, DynamicVertexBufferHandle _handle
		, XE::uint32 _startVertex
		, XE::uint32 _numVertices
		, VertexLayoutHandle _layoutHandle = VertexLayoutHandle()
	);

	void setVertexBuffer(
		XE::uint8 _stream
		, const TransientVertexBuffer * _tvb
	);

	void setVertexBuffer(
		XE::uint8 _stream
		, const TransientVertexBuffer * _tvb
		, XE::uint32 _startVertex
		, XE::uint32 _numVertices
		, VertexLayoutHandle _layoutHandle = VertexLayoutHandle()
	);

	void setVertexCount( XE::uint32 _numVertices );

	void setInstanceDataBuffer( const InstanceDataBuffer * _idb );

	void setInstanceDataBuffer(
		const InstanceDataBuffer * _idb
		, XE::uint32 _start
		, XE::uint32 _num
	);

	void setInstanceDataBuffer(
		VertexBufferHandle _handle
		, XE::uint32 _start
		, XE::uint32 _num
	);

	void setInstanceDataBuffer(
		DynamicVertexBufferHandle _handle
		, XE::uint32 _start
		, XE::uint32 _num
	);

	void setInstanceCount( XE::uint32 _numInstances );

	void setTexture(
		XE::uint8 _stage
		, UniformHandle _sampler
		, TextureHandle _handle
		, XE::uint32 _flags = UINT32_MAX
	);

	void touch( ViewHandle _view );

	void submit(
		ViewHandle _view
		, ProgramHandle _program
		, XE::uint32 _depth = 0
		, bool _preserveState = false
	);

	void submit(
		ViewHandle _view
		, ProgramHandle _program
		, OcclusionQueryHandle _occlusionQuery
		, XE::uint32 _depth = 0
		, bool _preserveState = false
	);

	void submit(
		ViewHandle _view
		, ProgramHandle _program
		, IndirectBufferHandle _indirectHandle
		, XE::uint16 _start = 0
		, XE::uint16 _num = 1
		, XE::uint32 _depth = 0
		, bool _preserveState = false
	);

	void setBuffer(
		XE::uint8 _stage
		, IndexBufferHandle _handle
		, Access _access
	);

	void setBuffer(
		XE::uint8 _stage
		, VertexBufferHandle _handle
		, Access _access
	);

	void setBuffer(
		XE::uint8 _stage
		, DynamicIndexBufferHandle _handle
		, Access _access
	);

	void setBuffer(
		XE::uint8 _stage
		, DynamicVertexBufferHandle _handle
		, Access _access
	);

	void setBuffer(
		XE::uint8 _stage
		, IndirectBufferHandle _handle
		, Access _access
	);

	void setImage(
		XE::uint8 _stage
		, TextureHandle _handle
		, XE::uint8 _mip
		, Access _access
		, TextureFormat _format = TextureFormat::UNKNOWN
	);

	void dispatch(
		ViewHandle _view
		, ProgramHandle _handle
		, XE::uint32 _numX = 1
		, XE::uint32 _numY = 1
		, XE::uint32 _numZ = 1
	);

	void dispatch(
		ViewHandle _view
		, ProgramHandle _handle
		, IndirectBufferHandle _indirectHandle
		, XE::uint16 _start = 0
		, XE::uint16 _num = 1
	);

	void discard();

	void blit(
		ViewHandle _view
		, TextureHandle _dst
		, XE::uint16 _dstX
		, XE::uint16 _dstY
		, TextureHandle _src
		, XE::uint16 _srcX = 0
		, XE::uint16 _srcY = 0
		, XE::uint16 _width = UINT16_MAX
		, XE::uint16 _height = UINT16_MAX
	);

	void blit(
		ViewHandle _view
		, TextureHandle _dst
		, XE::uint8 _dstMip
		, XE::uint16 _dstX
		, XE::uint16 _dstY
		, XE::uint16 _dstZ
		, TextureHandle _src
		, XE::uint8 _srcMip = 0
		, XE::uint16 _srcX = 0
		, XE::uint16 _srcY = 0
		, XE::uint16 _srcZ = 0
		, XE::uint16 _width = UINT16_MAX
		, XE::uint16 _height = UINT16_MAX
		, XE::uint16 _depth = UINT16_MAX
	);

private:
	void * _encoder;
};

class XE_API Gfx
{
public:
	static void vertexPack(
		const XE::Vec4 & _input
		, bool _inputNormalized
		, Attrib _attr
		, const VertexLayout & _layout
		, XE::memory_view _data
// 		, void * _data
// 		, XE::uint32 _index = 0
	);

	static void vertexUnpack(
		XE::Vec4 & _output
		, Attrib _attr
		, const VertexLayout & _layout
		, XE::memory_view _data
// 		, const void * _data
// 		, XE::uint32 _index = 0
	);

	static void vertexConvert(
		const VertexLayout & _destLayout
		, XE::memory_view _destData
//		, void * _destData
		, const VertexLayout & _srcLayout
		, XE::memory_view _srcData
// 		, const void * _srcData
// 		, XE::uint32 _num = 1
	);

	static XE::uint16 weldVertices(
		XE::uint16 * _output
		, const VertexLayout & _layout
		, XE::memory_view _data
// 		, const void * _data
// 		, XE::uint16 _num
		, float _epsilon = 0.001f
	);

	static XE::uint32 topologyConvert(
		TopologyConvert _conversion
		, XE::memory_view _dst
// 		, void * _dst
// 		, XE::uint32 _dstSize
		, XE::memory_view _indices
// 		, const void * _indices
// 		, XE::uint32 _numIndices
		, bool _index32
	);

	static void topologySortTriList(
		TopologySort _sort
		, XE::memory_view _dst
// 		, void * _dst
// 		, XE::uint32 _dstSize
		, const XE::Vec3 & _dir
		, const XE::Vec3 & _pos
		, XE::memory_view _vertices
// 		, const void * _vertices
// 		, XE::uint32 _stride
		, XE::memory_view _indices
// 		, const void * _indices
// 		, XE::uint32 _numIndices
		, bool _index32
	);

	static XE::uint8 getSupportedRenderers(
		XE::uint8 _max = 0
		, RendererType * _enum = NULL
	);

	static void reset(
		XE::uint32 _width
		, XE::uint32 _height
		, ResetFlags _flags = ResetFlags::NONE
		, TextureFormat _format = TextureFormat::UNKNOWN
	);

	static Encoder begin( bool _forThread = false );

	static void end( Encoder _encoder );

	static XE::uint32 frame( bool _capture = false );

	static RendererType getRendererType();

	static const XE::memory_view alloc( XE::uint32 _size );

	static const XE::memory_view copy(
		const void * _data
		, XE::uint32 _size
	);

	static const XE::memory_view makeRef(
		XE::memory_view _data
// 		const void * _data
// 		, XE::uint32 _size
//		, ReleaseFn _releaseFn = NULL
	);

	static void setDebug( XE::uint32 _debug );

	static void dbgTextClear(
		XE::uint8 _attr = 0
		, bool _small = false
	);

	static void dbgTextPrintf(
		XE::uint16 _x
		, XE::uint16 _y
		, XE::uint8 _attr
		, const XE::String & _text
	);

	static void dbgTextImage(
		XE::uint16 _x
		, XE::uint16 _y
		, XE::uint16 _width
		, XE::uint16 _height
		, XE::memory_view _data
//		, const void * _data
		, XE::uint16 _pitch
	);

	static IndexBufferHandle createIndexBuffer(
		const XE::memory_view _mem
		, BufferUsage _flags = BufferUsage::NONE
	);

	static void setName(
		IndexBufferHandle _handle
		, const XE::String & _name
	);

	static void destroy( IndexBufferHandle _handle );

	static VertexLayoutHandle createVertexLayout( const VertexLayout & _layout );

	static void destroy( VertexLayoutHandle _handle );

	static VertexBufferHandle createVertexBuffer(
		const XE::memory_view _mem
		, const VertexLayout & _layout
		, BufferUsage _flags = BufferUsage::NONE
	);

	static void setName(
		VertexBufferHandle _handle
		, const XE::String & _name
	);

	static void destroy( VertexBufferHandle _handle );

	static DynamicIndexBufferHandle createDynamicIndexBuffer(
		XE::uint32 _num
		, BufferUsage _flags = BufferUsage::NONE
	);

	static DynamicIndexBufferHandle createDynamicIndexBuffer(
		const XE::memory_view _mem
		, BufferUsage _flags = BufferUsage::NONE
	);

	static void update(
		DynamicIndexBufferHandle _handle
		, XE::uint32 _startIndex
		, const XE::memory_view _mem
	);

	static void destroy( DynamicIndexBufferHandle _handle );

	static DynamicVertexBufferHandle createDynamicVertexBuffer(
		XE::uint32 _num
		, const VertexLayout & _layout
		, BufferUsage _flags = BufferUsage::NONE
	);

	static DynamicVertexBufferHandle createDynamicVertexBuffer(
		const XE::memory_view _mem
		, const VertexLayout & _layout
		, BufferUsage _flags = BufferUsage::NONE
	);

	static void update(
		DynamicVertexBufferHandle _handle
		, XE::uint32 _startVertex
		, const XE::memory_view _mem
	);

	static void destroy( DynamicVertexBufferHandle _handle );

	static XE::uint32 getAvailTransientIndexBuffer( XE::uint32 _num );

	static XE::uint32 getAvailTransientVertexBuffer(
		XE::uint32 _num
		, const VertexLayout & _layout
	);

	static XE::uint32 getAvailInstanceDataBuffer(
		XE::uint32 _num
		, XE::uint16 _stride
	);

	static void allocTransientIndexBuffer(
		TransientIndexBuffer * _tib
		, XE::uint32 _num
	);

	static void allocTransientVertexBuffer(
		TransientVertexBuffer * _tvb
		, XE::uint32 _num
		, const VertexLayout & _layout
	);

	static bool allocTransientBuffers(
		TransientVertexBuffer * _tvb
		, const VertexLayout & _layout
		, XE::uint32 _numVertices
		, TransientIndexBuffer * _tib
		, XE::uint32 _numIndices
	);

	static void allocInstanceDataBuffer(
		InstanceDataBuffer * _idb
		, XE::uint32 _num
		, XE::uint16 _stride
	);

	static IndirectBufferHandle createIndirectBuffer( XE::uint32 _num );

	static void destroy( IndirectBufferHandle _handle );

	static ShaderHandle createShader( const XE::memory_view _mem );

	static XE::uint16 getShaderUniforms(
		ShaderHandle _handle
		, UniformHandle * _uniforms = NULL
		, XE::uint16 _max = 0
	);

	static void setName(
		ShaderHandle _handle
		, const XE::String & _name
	);

	static void destroy( ShaderHandle _handle );

	static ProgramHandle createProgram(
		ShaderHandle _vsh
		, ShaderHandle _fsh
		, bool _destroyShaders = false
	);

	static ProgramHandle createProgram(
		ShaderHandle _csh
		, bool _destroyShader = false
	);

	static void destroy( ProgramHandle _handle );

	static bool isTextureValid(
		XE::uint16 _depth
		, bool _cubeMap
		, XE::uint16 _numLayers
		, TextureFormat _format
		, XE::uint64 _flags
	);

	static void calcTextureSize(
		TextureInfo & _info
		, XE::uint16 _width
		, XE::uint16 _height
		, XE::uint16 _depth
		, bool _cubeMap
		, bool _hasMips
		, XE::uint16 _numLayers
		, TextureFormat _format
	);

	static TextureHandle createTexture(
		const XE::memory_view _mem
		, TextureUsage _tflags
		, SamlerFlags _sflags
//		, XE::uint64 _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE
		, XE::uint8 _skip = 0
		, TextureInfo * _info = NULL
	);

	static TextureHandle createTexture2D(
		XE::uint16 _width
		, XE::uint16 _height
		, bool     _hasMips
		, XE::uint16 _numLayers
		, TextureFormat _format
		, TextureUsage _tflags
		, SamlerFlags _sflags
//		, XE::uint64 _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE
		, const XE::memory_view _mem = NULL
	);

	static TextureHandle createTexture2D(
		BackbufferRatio _ratio
		, bool _hasMips
		, XE::uint16 _numLayers
		, TextureFormat _format
		, TextureUsage _tflags
		, SamlerFlags _sflags
//		, XE::uint64 _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE
	);

	static TextureHandle createTexture3D(
		XE::uint16 _width
		, XE::uint16 _height
		, XE::uint16 _depth
		, bool _hasMips
		, TextureFormat _format
		, TextureUsage _tflags
		, SamlerFlags _sflags
//		, XE::uint64 _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE
		, const XE::memory_view _mem = NULL
	);

	static TextureHandle createTextureCube(
		XE::uint16 _size
		, bool _hasMips
		, XE::uint16 _numLayers
		, TextureFormat _format
		, TextureUsage _tflags
		, SamlerFlags _sflags
//		, XE::uint64 _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE
		, const XE::memory_view _mem = NULL
	);

	static void updateTexture2D(
		TextureHandle _handle
		, XE::uint16 _layer
		, XE::uint8 _mip
		, XE::uint16 _x
		, XE::uint16 _y
		, XE::uint16 _width
		, XE::uint16 _height
		, const XE::memory_view _mem
		, XE::uint16 _pitch = UINT16_MAX
	);

	static void updateTexture3D(
		TextureHandle _handle
		, XE::uint8 _mip
		, XE::uint16 _x
		, XE::uint16 _y
		, XE::uint16 _z
		, XE::uint16 _width
		, XE::uint16 _height
		, XE::uint16 _depth
		, const XE::memory_view _mem
	);

	static void updateTextureCube(
		TextureHandle _handle
		, XE::uint16 _layer
		, XE::uint8 _side
		, XE::uint8 _mip
		, XE::uint16 _x
		, XE::uint16 _y
		, XE::uint16 _width
		, XE::uint16 _height
		, const XE::memory_view _mem
		, XE::uint16 _pitch = UINT16_MAX
	);

	static XE::uint32 readTexture(
		TextureHandle _handle
		, XE::memory_view _data
		//		, void * _data
		, XE::uint8 _mip = 0
	);

	static void setName(
		TextureHandle _handle
		, const XE::String & _name
	);

	static void * getDirectAccessPtr( TextureHandle _handle );

	static void destroy( TextureHandle _handle );

	static FrameBufferHandle createFrameBuffer(
		XE::uint16 _width
		, XE::uint16 _height
		, TextureFormat _format
		, SamlerFlags _textureFlags = ( SamlerFlags )( ( XE::uint64 )SamlerFlags::U_CLAMP | ( XE::uint64 )SamlerFlags::V_CLAMP )
//		, XE::uint64 _textureFlags = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
	);

	static FrameBufferHandle createFrameBuffer(
		BackbufferRatio _ratio
		, TextureFormat _format
		, SamlerFlags _textureFlags = (SamlerFlags )( ( XE::uint64 )SamlerFlags::U_CLAMP | ( XE::uint64 )SamlerFlags::V_CLAMP )
//		, XE::uint64 _textureFlags = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
	);

	static FrameBufferHandle createFrameBuffer(
		XE::uint8 _num
		, const TextureHandle * _handles
		, bool _destroyTextures = false
	);

	static FrameBufferHandle createFrameBuffer(
		XE::uint8 _num
		, const Attachment * _attachment
		, bool _destroyTextures = false
	);

	static FrameBufferHandle createFrameBuffer(
		WindowHandle _nwh
		, XE::uint16 _width
		, XE::uint16 _height
		, TextureFormat _format = TextureFormat::UNKNOWN
		, TextureFormat _depthFormat = TextureFormat::UNKNOWN
	);

	static void setName(
		FrameBufferHandle _handle
		, const XE::String & _name
	);

	static TextureHandle getTexture(
		FrameBufferHandle _handle
		, XE::uint8 _attachment = 0
	);

	static void destroy( FrameBufferHandle _handle );

	static UniformHandle createUniform(
		const XE::String & _name
		, UniformType _type
		, XE::uint16 _num = 1
	);

	static void getUniformInfo(
		UniformHandle _handle
		, UniformInfo & _info
	);

	static void destroy( UniformHandle _handle );

	static OcclusionQueryHandle createOcclusionQuery();

	static OcclusionQueryResult getResult(
		OcclusionQueryHandle _handle
		, XE::int32 * _result = nullptr
	);

	static void destroy( OcclusionQueryHandle _handle );

	static void setPaletteColor(
		XE::uint8 _index
		, XE::uint32 _rgba
	);

	static void setPaletteColor(
		XE::uint8 _index
		, float _r
		, float _g
		, float _b
		, float _a
	);

	static void setPaletteColor(
		XE::uint8 _index
		, const XE::FColor & _rgba
	);

	static void setViewName(
		ViewHandle _view
		, const XE::String & _name
	);

	static void setViewRect(
		ViewHandle _view
		, XE::uint16 _x
		, XE::uint16 _y
		, XE::uint16 _width
		, XE::uint16 _height
	);

	static void setViewRect(
		ViewHandle _view
		, XE::uint16 _x
		, XE::uint16 _y
		, BackbufferRatio _ratio
	);

	static void setViewScissor(
		ViewHandle _view
		, XE::uint16 _x = 0
		, XE::uint16 _y = 0
		, XE::uint16 _width = 0
		, XE::uint16 _height = 0
	);

	static void setViewClear(
		ViewHandle _view
		, ClearFlags _falgs
//		, XE::uint16 _flags
		, XE::uint32 _rgba = 0x000000ff
		, float _depth = 1.0f
		, XE::uint8 _stencil = 0
	);

	static void setViewClear(
		ViewHandle _view
		, ClearFlags _falgs
//		, XE::uint16 _flags
		, float _depth
		, XE::uint8 _stencil
		, XE::uint8 _0 = UINT8_MAX
		, XE::uint8 _1 = UINT8_MAX
		, XE::uint8 _2 = UINT8_MAX
		, XE::uint8 _3 = UINT8_MAX
		, XE::uint8 _4 = UINT8_MAX
		, XE::uint8 _5 = UINT8_MAX
		, XE::uint8 _6 = UINT8_MAX
		, XE::uint8 _7 = UINT8_MAX
	);

	static void setViewMode(
		ViewHandle _view
		, ViewMode _mode = ViewMode::DEFAULT
	);

	static void setViewFrameBuffer(
		ViewHandle _view
		, FrameBufferHandle _handle
	);

	static void setViewTransform(
		ViewHandle _handle
		, const Mat4 & _view
		, const Mat4 & _proj
// 		, const void * _view
// 		, const void * _proj
	);

	static void setViewOrder(
		ViewHandle _view
		, XE::basic_memory_view<ViewHandle> _remap
// 		, XE::uint16 _num = UINT16_MAX
// 		, const ViewId * _remap = NULL
	);

	static void resetView( ViewHandle _view );

	static void setMarker( const XE::String & _marker );

	static void setState(
		XE::uint64 _state
		, XE::uint32 _rgba = 0
	);

	static void setCondition(
		OcclusionQueryHandle _handle
		, bool _visible
	);

	static void setStencil(
		XE::uint32 _fstencil
		, StencilFlags _bstencil = StencilFlags::NONE
	);

	static XE::uint16 setScissor(
		XE::uint16 _x
		, XE::uint16 _y
		, XE::uint16 _width
		, XE::uint16 _height
	);

	static void setScissor( XE::uint16 _cache = UINT16_MAX );

	static XE::uint32 setTransform(
		XE::basic_memory_view<Mat4> _mtx
// 		const void * _mtx
// 		, XE::uint16 _num = 1
	);

	static XE::uint32 allocTransform(
		XE::basic_memory_view<Mat4> _transform
// 		Transform * _transform
// 		, XE::uint16 _num
	);

	static void setTransform(
		XE::uint32 _cache
		, XE::uint16 _num = 1
	);

	static void setUniform(
		UniformHandle _handle
		, XE::memory_view _value
// 		, const void * _value
// 		, XE::uint16 _num = 1
	);

	static void setIndexBuffer( IndexBufferHandle _handle );

	static void setIndexBuffer(
		IndexBufferHandle _handle
		, XE::uint32 _firstIndex
		, XE::uint32 _numIndices
	);

	static void setIndexBuffer( DynamicIndexBufferHandle _handle );

	static void setIndexBuffer(
		DynamicIndexBufferHandle _handle
		, XE::uint32 _firstIndex
		, XE::uint32 _numIndices
	);

	static void setIndexBuffer( const TransientIndexBuffer * _tib );

	static void setIndexBuffer(
		const TransientIndexBuffer * _tib
		, XE::uint32 _firstIndex
		, XE::uint32 _numIndices
	);

	static void setVertexBuffer(
		XE::uint8 _stream
		, VertexBufferHandle _handle
	);

	static void setVertexBuffer(
		XE::uint8 _stream
		, VertexBufferHandle _handle
		, XE::uint32 _startVertex
		, XE::uint32 _numVertices
		, VertexLayoutHandle _layoutHandle = VertexLayoutHandle()
	);

	static void setVertexBuffer(
		XE::uint8 _stream
		, DynamicVertexBufferHandle _handle
	);

	static void setVertexBuffer(
		XE::uint8 _stream
		, DynamicVertexBufferHandle _handle
		, XE::uint32 _startVertex
		, XE::uint32 _numVertices
		, VertexLayoutHandle _layoutHandle = VertexLayoutHandle()
	);

	static void setVertexBuffer(
		XE::uint8 _stream
		, const TransientVertexBuffer * _tvb
	);

	static void setVertexBuffer(
		XE::uint8 _stream
		, const TransientVertexBuffer * _tvb
		, XE::uint32 _startVertex
		, XE::uint32 _numVertices
		, VertexLayoutHandle _layoutHandle = VertexLayoutHandle()
	);

	static void setVertexCount( XE::uint32 _numVertices );

	static void setInstanceDataBuffer( const InstanceDataBuffer * _idb );

	static void setInstanceDataBuffer(
		const InstanceDataBuffer * _idb
		, XE::uint32 _start
		, XE::uint32 _num
	);

	static void setInstanceDataBuffer(
		VertexBufferHandle _handle
		, XE::uint32 _start
		, XE::uint32 _num
	);

	static void setInstanceDataBuffer(
		DynamicVertexBufferHandle _handle
		, XE::uint32 _start
		, XE::uint32 _num
	);

	static void setInstanceCount( XE::uint32 _numInstances );

	static void setTexture(
		XE::uint8 _stage
		, UniformHandle _sampler
		, TextureHandle _handle
		, XE::uint32 _flags = UINT32_MAX
	);

	static void touch( ViewHandle _view );

	static void submit(
		ViewHandle _view
		, ProgramHandle _program
		, XE::uint32 _depth = 0
		, bool _preserveState = false
	);

	static void submit(
		ViewHandle _view
		, ProgramHandle _program
		, OcclusionQueryHandle _occlusionQuery
		, XE::uint32 _depth = 0
		, bool _preserveState = false
	);

	static void submit(
		ViewHandle _view
		, ProgramHandle _program
		, IndirectBufferHandle _indirectHandle
		, XE::uint16 _start = 0
		, XE::uint16 _num = 1
		, XE::uint32 _depth = 0
		, bool _preserveState = false
	);

	static void setBuffer(
		XE::uint8 _stage
		, IndexBufferHandle _handle
		, Access _access
	);

	static void setBuffer(
		XE::uint8 _stage
		, VertexBufferHandle _handle
		, Access _access
	);

	static void setBuffer(
		XE::uint8 _stage
		, DynamicIndexBufferHandle _handle
		, Access _access
	);

	static void setBuffer(
		XE::uint8 _stage
		, DynamicVertexBufferHandle _handle
		, Access _access
	);

	static void setBuffer(
		XE::uint8 _stage
		, IndirectBufferHandle _handle
		, Access _access
	);

	static void setImage(
		XE::uint8 _stage
		, TextureHandle _handle
		, XE::uint8 _mip
		, Access _access
		, TextureFormat _format = TextureFormat::UNKNOWN
	);

	static void dispatch(
		ViewHandle _view
		, ProgramHandle _handle
		, XE::uint32 _numX = 1
		, XE::uint32 _numY = 1
		, XE::uint32 _numZ = 1
	);

	static void dispatch(
		ViewHandle _view
		, ProgramHandle _handle
		, IndirectBufferHandle _indirectHandle
		, XE::uint16 _start = 0
		, XE::uint16 _num = 1
	);

	static void discard();

	static void blit(
		ViewHandle _view
		, TextureHandle _dst
		, XE::uint16 _dstX
		, XE::uint16 _dstY
		, TextureHandle _src
		, XE::uint16 _srcX = 0
		, XE::uint16 _srcY = 0
		, XE::uint16 _width = UINT16_MAX
		, XE::uint16 _height = UINT16_MAX
	);

	static void blit(
		ViewHandle _view
		, TextureHandle _dst
		, XE::uint8 _dstMip
		, XE::uint16 _dstX
		, XE::uint16 _dstY
		, XE::uint16 _dstZ
		, TextureHandle _src
		, XE::uint8 _srcMip = 0
		, XE::uint16 _srcX = 0
		, XE::uint16 _srcY = 0
		, XE::uint16 _srcZ = 0
		, XE::uint16 _width = UINT16_MAX
		, XE::uint16 _height = UINT16_MAX
		, XE::uint16 _depth = UINT16_MAX
	);

	static void requestScreenShot(
		FrameBufferHandle _handle
		, const XE::String & _filePath
	);

};

END_XE_NAMESPACE

#endif // GFX_H__12636FE6_A92D_467B_909E_9892450A6029
