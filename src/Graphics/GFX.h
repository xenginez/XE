/*!
 * \file   GFX.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GFX_H__32D726E0_F382_416D_AE96_FF42FA7A2D89
#define __GFX_H__32D726E0_F382_416D_AE96_FF42FA7A2D89

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API GFX
{
public:
	static void SetPlatformData( const XE::PlatformData &_data );

	static bool Init( InitType init_data );

	static void Shutdown();

	static void Reset( uint32 _width, uint32 _height, uint32 _flags = BGFX_RESET_NONE);

	static void VertexPack( const float * _input, bool _inputNormalized, Attribute _attr, const VertexLayout &_decl, void * _data, uint32 _index = 0 );

	static void VertexUnpack( float * _output, Attribute _attr, const VertexLayout &_decl, const void * _data, uint32 _index = 0 );

	static void VertexConvert( const VertexLayout &_destDecl, void * _destData, const VertexLayout &_srcDecl, const void * _srcData, uint32 _num = 1 );

	static uint16 WeldVertices( uint16 * _output, const VertexLayout &_decl, const void * _data, uint16 _num, float _epsilon = 0.001f );

	static uint32 TopologyConvert( TopologyConversion _conversion, void * _dst, uint32 _dstSize, const void * _indices, uint32 _numIndices, bool _index32 );

	static void TopologySortTriList( TopologySort _sort, void * _dst, uint32 _dstSize, const float * _dir, const float * _pos, const void * _vertices, uint32 _stride, const void * _indices, uint32 _numIndices, bool _index32 );

	static ShaderHandle CreateEmbeddedShader( const EmbeddedShader * _es, RendererType _type, const String &_name );

	static uint8 GetSupportedRenderers( uint8 _max = 0, RendererType * _enum = nullptr );

	static String GetRendererName( RendererType _type );

	static Encoder* Begin();

	static void End( Encoder * _encoder );

	static uint32 Frame( bool _capture = true );

	static RendererType GetRendererType();

	static const Caps* GetCaps();

	static const Stats* GetStats();

	static const MemoryView* Alloc( uint32 _size );

	static const MemoryView* Copy( const void * _data, uint32 _size );

	static const MemoryView* MakeRef( const void * _data, uint32 _size, void( * _releaseFn )( void * _ptr, void * _userData ) = nullptr, void * _userData = nullptr );

	static void SetDebug( uint32 _debug );

	static void DbgTextClear( uint8 _attr = 0, bool _small = false );

	static 	void DbgTextPrintf( uint16 _x, uint16 _y, uint8 _attr, const String &_text );

	static void DbgTextImage( uint16 _x, uint16 _y, uint16 _width, uint16 _height, const void * _data, uint16 _pitch );

	static IndexBufferHandle CreateIndexBuffer( const MemoryView * _mem, uint16 _flags = BGFX_BUFFER_NONE);

	static void Destroy( IndexBufferHandle _handle );

	static VertexBufferHandle CreateVertexBuffer( const MemoryView * _mem, const VertexLayout &_decl, uint16 _flags = BGFX_BUFFER_NONE);

	static void Destroy( VertexBufferHandle _handle );

	static DynamicIndexBufferHandle CreateDynamicIndexBuffer( uint32 _num, uint16 _flags = BGFX_BUFFER_NONE);

	static DynamicIndexBufferHandle CreateDynamicIndexBuffer( const MemoryView * _mem, uint16 _flags = BGFX_BUFFER_NONE);

	static void Update( DynamicIndexBufferHandle _handle, uint32 _startIndex, const MemoryView * _mem );

	static void Destroy( DynamicIndexBufferHandle _handle );

	static DynamicVertexBufferHandle CreateDynamicVertexBuffer( uint32 _num, const VertexLayout &_decl, uint16 _flags = BGFX_BUFFER_NONE);

	static DynamicVertexBufferHandle CreateDynamicVertexBuffer( const MemoryView * _mem, const VertexLayout &_decl, uint16 _flags = BGFX_BUFFER_NONE);

	static void Update( DynamicVertexBufferHandle _handle, uint32 _startVertex, const MemoryView * _mem );

	static void Destroy( DynamicVertexBufferHandle _handle );

	static uint32 GetAvailTransientIndexBuffer( uint32 _num );

	static uint32 GetAvailTransientVertexBuffer( uint32 _num, const VertexLayout &_decl );

	static uint32 GetAvailInstanceDataBuffer( uint32 _num, uint16 _stride );

	static void AllocTransientIndexBuffer( TransientIndexBuffer * _tib, uint32 _num );

	static void AllocTransientVertexBuffer( TransientVertexBuffer * _tvb, uint32 _num, const VertexLayout &_decl );

	static bool AllocTransientBuffers( TransientVertexBuffer * _tvb, const VertexLayout &_decl, uint32 _numVertices, TransientIndexBuffer * _tib, uint32 _numIndices );

	static void AllocInstanceDataBuffer( InstanceDataBuffer * _idb, uint32 _num, uint16 _stride );

	static IndirectBufferHandle CreateIndirectBuffer( uint32 _num );

	static void Destroy( IndirectBufferHandle _handle );

	static ShaderHandle CreateShader( const MemoryView * _mem );

	static uint16 GetShaderUniforms( ShaderHandle _handle, UniformHandle * _uniforms = nullptr, uint16 _max = 0 );

	static void GetUniformInfo( UniformHandle _handle, UniformInfo &_info );

	static void SetName( ShaderHandle _handle, const String &_name );

	static void Destroy( ShaderHandle _handle );

	static ProgramHandle CreateProgram( ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders = false );

	static ProgramHandle CreateProgram( ShaderHandle _csh, bool _destroyShaders = false );

	static void Destroy( ProgramHandle _handle );

	static bool IsTextureValid( uint16 _depth, bool _cubeMap, uint16 _numLayers, TextureFormat _format, uint64 _flags );

	static void CalcTextureSize( TextureInfo &_info, uint16 _width, uint16 _height, uint16 _depth, bool _cubeMap, bool _hasMips, uint16 _numLayers, TextureFormat _format );

	static TextureHandle CreateTexture( const MemoryView * _mem, uint64 _flags = BGFX_TEXTURE_NONE, uint8 _skip = 0, TextureInfo * _info = nullptr );

	static TextureHandle CreateTexture2D( uint16 _width, uint16 _height, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags = BGFX_TEXTURE_NONE, const MemoryView * _mem = nullptr );

	static TextureHandle CreateTexture2D( BackbufferRatio _ratio, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags = BGFX_TEXTURE_NONE);

	static TextureHandle CreateTexture3D( uint16 _width, uint16 _height, uint16 _depth, bool _hasMips, TextureFormat _format, uint64 _flags = BGFX_TEXTURE_NONE, const MemoryView * _mem = nullptr );

	static TextureHandle CreateTextureCube( uint16 _size, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags = BGFX_TEXTURE_NONE, const MemoryView * _mem = nullptr );

	static void UpdateTexture2D( TextureHandle _handle, uint16 _layer, uint8 _mip, uint16 _x, uint16 _y, uint16 _width, uint16 _height, const MemoryView * _mem, uint16 _pitch = UINT16_MAX );

	static void UpdateTexture3D( TextureHandle _handle, uint8 _mip, uint16 _x, uint16 _y, uint16 _z, uint16 _width, uint16 _height, uint16 _depth, const MemoryView * _mem );

	static void UpdateTextureCube( TextureHandle _handle, uint16 _layer, uint8 _side, uint8 _mip, uint16 _x, uint16 _y, uint16 _width, uint16 _height, const MemoryView * _mem, uint16 _pitch = UINT16_MAX );

	static uint32 ReadTexture( TextureHandle _handle, void * _data, uint8 _mip = 0 );

	static void SetName( TextureHandle _handle, const String &_name );

	static void Destroy( TextureHandle _handle );

	static FrameBufferHandle CreateFrameBuffer( uint16 _width, uint16 _height, TextureFormat _format, uint64 _textureFlags =
	BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);

	static FrameBufferHandle CreateFrameBuffer( BackbufferRatio _ratio, TextureFormat _format, uint64 _textureFlags =
	BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);

	static FrameBufferHandle CreateFrameBuffer( uint8 _num, const TextureHandle * _handles, bool _destroyTextures = false );

	static FrameBufferHandle CreateFrameBuffer( uint8 _num, const Attachment * _attachment, bool _destroyTextures = false );

	static FrameBufferHandle CreateFrameBuffer( void * _nwh, uint16 _width, uint16 _height, TextureFormat _format = TextureFormat::Count, TextureFormat _depthFormat = TextureFormat::Count );

	static TextureHandle GetTexture( FrameBufferHandle _handle, uint8 _attachment = 0 );

	static void Destroy( FrameBufferHandle _handle );

	static UniformHandle CreateUniform( const String &_name, UniformType _type, uint16 _num = 1 );

	static void Destroy( UniformHandle _handle );

	static OcclusionQueryHandle CreateOcclusionQuery();

	static OcclusionQueryResult GetResult( OcclusionQueryHandle _handle, int32 * _result = nullptr );

	static void Destroy( OcclusionQueryHandle _handle );

	static void SetPaletteColor( uint8 _index, uint32 _rgba );

	static void SetPaletteColor( uint8 _index, const float * _rgba );

	static void SetPaletteColor( uint8 _index, float _r, float _g, float _b, float _a );

	static void SetViewName( ViewHandle _id, const String &_name );

	static void SetViewRect( ViewHandle _id, uint16 _x, uint16 _y, uint16 _width, uint16 _height );

	static void SetViewRect( ViewHandle _id, uint16 _x, uint16 _y, BackbufferRatio _ratio );

	static void SetViewScissor( ViewHandle _id, uint16 _x = 0, uint16 _y = 0, uint16 _width = 0, uint16 _height = 0 );

	static void SetViewClear( ViewHandle _id, uint16 _flags, uint32 _rgba = 0x000000ff, float _depth = 1.0f, uint8 _stencil = 0 );

	static void SetViewClear( ViewHandle _id, uint16 _flags, float _depth, uint8 _stencil, uint8 _0 = UINT8_MAX, uint8 _1 = UINT8_MAX, uint8 _2 = UINT8_MAX, uint8 _3 = UINT8_MAX, uint8 _4 = UINT8_MAX, uint8 _5 = UINT8_MAX, uint8 _6 = UINT8_MAX, uint8 _7 = UINT8_MAX );

	static void SetViewMode( ViewHandle _id, ViewMode _mode = ViewMode::Default );

	static void SetViewFrameBuffer( ViewHandle _id, FrameBufferHandle _handle );

	static void SetViewTransform( ViewHandle _id, const void * _view, const void * _proj );

	static void SetViewOrder( ViewHandle _id = 0, uint16 _num = UINT16_MAX, const ViewHandle * _order = nullptr );

	static void ResetView( ViewHandle _id );

	static void SetMarker( const String &_marker );

	static void SetState( uint64 _state, uint32 _rgba = 0 );

	static void SetCondition( OcclusionQueryHandle _handle, bool _visible );

	static void SetStencil( uint32 _fstencil, uint32 _bstencil = BGFX_STENCIL_NONE);

	static uint16 SetScissor( uint16 _x, uint16 _y, uint16 _width, uint16 _height );

	static void SetScissord( uint16 _cache = UINT16_MAX );

	static uint32 SetTransform( const TransformData * _mtx, uint16 _num = 1 );

	static uint32 AllocTransform( TransformData * _transform, uint16 _num );

	static void SetTransform( uint32 _cache, uint16 _num = 1 );

	static void SetUniform( UniformHandle _handle, const void * _value, uint16 _num = 1 );

	static void SetIndexBuffer( IndexBufferHandle _handle, uint32 _firstIndex, uint32 _numIndices );

	static void SetIndexBuffer( DynamicIndexBufferHandle _handle, uint32 _firstIndex, uint32 _numIndices );

	static void SetIndexBuffer( const TransientIndexBuffer * _tib, uint32 _firstIndex, uint32 _numIndices );

	static void SetVertexBuffer( uint8 _stream, VertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices );

	static void SetVertexBuffer( uint8 _stream, DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices );

	static void SetVertexBuffer( uint8 _stream, const TransientVertexBuffer * _tvb, uint32 _startVertex, uint32 _numVertices );

	static void SetInstanceDataBuffer( const InstanceDataBuffer * _idb, uint32 _start, uint32 _num );

	static void SetInstanceDataBuffer( VertexBufferHandle _handle, uint32 _startVertex, uint32 _num );

	static void SetInstanceDataBuffer( DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _num );

	static void SetTexture( uint8 _stage, UniformHandle _sampler, TextureHandle _handle, uint32 _flags = UINT32_MAX );

	static void Touch( ViewHandle _id );

	static void Submit( ViewHandle _id, ProgramHandle _handle, int32 _depth = 0, bool _preserveState = false );

	static void Submit( ViewHandle _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, int32 _depth = 0, bool _preserveState = false );

	static void Submit( ViewHandle _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16 _start = 0, uint16 _num = 1, int32 _depth = 0, bool _preserveState = false );

	static void SetImage( uint8 _stage, TextureHandle _handle, uint8 _mip, Access _access, TextureFormat _format = TextureFormat::Count );

	static void SetBuffer( uint8 _stage, IndexBufferHandle _handle, Access _access );

	static void SetBuffer( uint8 _stage, VertexBufferHandle _handle, Access _access );

	static void SetBuffer( uint8 _stage, DynamicIndexBufferHandle _handle, Access _access );

	static void SetBuffer( uint8 _stage, DynamicVertexBufferHandle _handle, Access _access );

	static void SetBuffer( uint8 _stage, IndirectBufferHandle _handle, Access _access );

	static void Dispatch( ViewHandle _id, ProgramHandle _handle, uint32 _numX = 1, uint32 _numY = 1, uint32 _numZ = 1 );

	static void Dispatch( ViewHandle _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16 _start = 0, uint16 _num = 1 );

	static void Discard();

	static void Blit( ViewHandle _id, TextureHandle _dst, uint16 _dstX, uint16 _dstY, TextureHandle _src, uint16 _srcX = 0, uint16 _srcY = 0, uint16 _width = UINT16_MAX, uint16 _height = UINT16_MAX );

	static void Blit( ViewHandle _id, TextureHandle _dst, uint8 _dstMip, uint16 _dstX, uint16 _dstY, uint16 _dstZ, TextureHandle _src, uint8 _srcMip = 0, uint16 _srcX = 0, uint16 _srcY = 0, uint16 _srcZ = 0, uint16 _width = UINT16_MAX, uint16 _height = UINT16_MAX, uint16 _depth = UINT16_MAX );

	static void RequestScreenShot( FrameBufferHandle _handle, const std::filesystem::path &_filePath );

public:
	static void Flush();

	static bool IsOriginBottomLeft();

	static bool IsHomogeneousDepth();

	static float GetHalfTexel();

	static uint32 GetMaxBlendTransforms();

	static uint64 ScreenQuad( float dest_width, float dest_height, float depth = 0.0f, float width = 1.0f, float height = 1.0f );

	static uint64 ClipQuad( float depth = 0.0f, float width = 1.0f, float height = 1.0f );

	static void GetSizeFromRatio( BackbufferRatio _ratio, uint16 &_width, uint16 &_height );

	static const String& GetRendererFilenameExtension();

	static bool IsSupported( uint64 flag );

public:
	static bool IsFormatSupported( uint16 flags, TextureFormat format );

	static TextureFormat GetBestFormat( uint16 type_flags, uint32 search_flags );

	static uint64 GetDefaultRtSamplerFlags();
};

END_XE_NAMESAPCE

#endif // __GFX_H__32D726E0_F382_416D_AE96_FF42FA7A2D89
