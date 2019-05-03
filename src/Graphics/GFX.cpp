#include "GFX.h"

#include "VertexDecl.h"

USING_XE

void XE::GFX::SetPlatformData( const PlatformData &_data )
{
	bgfx::setPlatformData( _data );
}

bool XE::GFX::Init( InitType init_data )
{
	return bgfx::init( init_data );
}

void XE::GFX::Shutdown()
{
	bgfx::shutdown();
}

void XE::GFX::Reset( uint32 _width, uint32 _height, uint32 _flags /*= BGFX_RESET_NONE */ )
{
	bgfx::reset( _width, _height, _flags );
}

void XE::GFX::VertexPack( const float * _input, bool _inputNormalized, Attribute _attr, const VertexLayout &_decl, void * _data, uint32 _index /*= 0 */ )
{
	bgfx::vertexPack( _input, _inputNormalized, _attr, _decl, _data, _index );
}

void XE::GFX::VertexUnpack( float * _output, Attribute _attr, const VertexLayout &_decl, const void * _data, uint32 _index /*= 0 */ )
{
	bgfx::vertexUnpack( _output, _attr, _decl, _data, _index );
}

void XE::GFX::VertexConvert( const VertexLayout &_destDecl, void * _destData, const VertexLayout &_srcDecl, const void * _srcData, uint32 _num /*= 1 */ )
{
	bgfx::vertexConvert( _destDecl, _destData, _srcDecl, _srcData, _num );
}

XE::uint16 XE::GFX::WeldVertices( uint16 * _output, const VertexLayout &_decl, const void * _data, uint16 _num, float _epsilon /*= 0.001f */ )
{
	return bgfx::weldVertices( _output, _decl, _data, _num, _epsilon );
}

XE::uint32 XE::GFX::TopologyConvert( TopologyConversion _conversion, void * _dst, uint32 _dstSize, const void * _indices, uint32 _numIndices, bool _index32 )
{
	return bgfx::topologyConvert( _conversion, _dst, _dstSize, _indices, _numIndices, _index32 );
}

void XE::GFX::TopologySortTriList( TopologySort _sort, void * _dst, uint32 _dstSize, const float * _dir, const float * _pos, const void * _vertices, uint32 _stride, const void * _indices, uint32 _numIndices, bool _index32 )
{
	bgfx::topologySortTriList( _sort, _dst, _dstSize, _dir, _pos, _vertices, _stride, _indices, _numIndices, _index32 );
}

XE::uint8 XE::GFX::GetSupportedRenderers( uint8 _max /*= 0*/, RendererType * _enum /*= nullptr */ )
{
	return bgfx::getSupportedRenderers( _max, _enum );
}

XE::ShaderHandle XE::GFX::CreateEmbeddedShader( const EmbeddedShader * _es, RendererType _type, const XE::String &_name )
{
	return bgfx::createEmbeddedShader( _es, _type, _name.ToCString() );
}

XE::String XE::GFX::GetRendererName( RendererType _type )
{
	return bgfx::getRendererName( _type );
}

XE::Encoder* XE::GFX::Begin()
{
	return bgfx::begin();
}

void XE::GFX::End( Encoder * _encoder )
{
	bgfx::end( _encoder );
}

XE::uint32 XE::GFX::Frame( bool _capture /*= true */ )
{
	return bgfx::frame( _capture );
}

XE::RendererType XE::GFX::GetRendererType()
{
	return bgfx::getRendererType();
}

const XE::Caps* XE::GFX::GetCaps()
{
	return bgfx::getCaps();
}

const XE::Stats* XE::GFX::GetStats()
{
	return bgfx::getStats();
}

const XE::MemoryView * XE::GFX::Alloc( uint32 _size )
{
	return bgfx::alloc( _size );
}

const XE::MemoryView * XE::GFX::Copy( const void * _data, uint32 _size )
{
	return bgfx::copy( _data, _size );
}

const XE::MemoryView * XE::GFX::MakeRef( const void * _data, uint32 _size, void( * _releaseFn )( void * _ptr, void * _userData ) /*= nullptr*/, void * _userData /*= nullptr */ )
{
	return bgfx::makeRef( _data, _size, _releaseFn, _userData );
}

void XE::GFX::SetDebug( uint32 _debug )
{
	bgfx::setDebug( _debug );
}

void XE::GFX::DbgTextClear( uint8 _attr /*= 0*/, bool _small /*= false */ )
{
	bgfx::dbgTextClear( _attr, _small );
}

void XE::GFX::DbgTextPrintf( uint16 _x, uint16 _y, uint8 _attr, const String &_text )
{
	bgfx::dbgTextPrintf( _x, _y, _attr, _text.ToCString() );
}

void XE::GFX::DbgTextImage( uint16 _x, uint16 _y, uint16 _width, uint16 _height, const void * _data, uint16 _pitch )
{
	bgfx::dbgTextImage( _x, _y, _width, _height, _data, _pitch );
}

XE::IndexBufferHandle XE::GFX::CreateIndexBuffer( const MemoryView * _mem, uint16 _flags /*= BGFX_BUFFER_NONE */ )
{
	return bgfx::createIndexBuffer( _mem, _flags );
}

void XE::GFX::Destroy( IndexBufferHandle _handle )
{
	bgfx::destroy( _handle );
}

void XE::GFX::Destroy( VertexBufferHandle _handle )
{
	bgfx::destroy( _handle );
}

void XE::GFX::Destroy( DynamicIndexBufferHandle _handle )
{
	bgfx::destroy( _handle );
}

void XE::GFX::Destroy( DynamicVertexBufferHandle _handle )
{
	bgfx::destroy( _handle );
}

void XE::GFX::Destroy( IndirectBufferHandle _handle )
{
	bgfx::destroy( _handle );
}

void XE::GFX::Destroy( ShaderHandle _handle )
{
	bgfx::destroy( _handle );
}

void XE::GFX::Destroy( ProgramHandle _handle )
{
	bgfx::destroy( _handle );
}

void XE::GFX::Destroy( TextureHandle _handle )
{
	bgfx::destroy( _handle );
}

void XE::GFX::Destroy( FrameBufferHandle _handle )
{
	bgfx::destroy( _handle );
}

void XE::GFX::Destroy( UniformHandle _handle )
{
	bgfx::destroy( _handle );
}

void XE::GFX::Destroy( OcclusionQueryHandle _handle )
{
	bgfx::destroy( _handle );
}

XE::VertexBufferHandle XE::GFX::CreateVertexBuffer( const MemoryView * _mem, const VertexLayout &_decl, uint16 _flags /*= BGFX_BUFFER_NONE */ )
{
	return bgfx::createVertexBuffer( _mem, _decl, _flags );
}

XE::DynamicIndexBufferHandle XE::GFX::CreateDynamicIndexBuffer( uint32 _num, uint16 _flags /*= BGFX_BUFFER_NONE */ )
{
	return bgfx::createDynamicIndexBuffer( _num, _flags );
}

XE::DynamicIndexBufferHandle XE::GFX::CreateDynamicIndexBuffer( const MemoryView * _mem, uint16 _flags /*= BGFX_BUFFER_NONE */ )
{
	return bgfx::createDynamicIndexBuffer( _mem, _flags );
}

void XE::GFX::Update( DynamicIndexBufferHandle _handle, uint32 _startIndex, const MemoryView * _mem )
{
	bgfx::update( _handle, _startIndex, _mem );
}

void XE::GFX::Update( DynamicVertexBufferHandle _handle, uint32 _startVertex, const MemoryView * _mem )
{
	bgfx::update( _handle, _startVertex, _mem );
}

XE::DynamicVertexBufferHandle XE::GFX::CreateDynamicVertexBuffer( uint32 _num, const VertexLayout &_decl, uint16 _flags /*= BGFX_BUFFER_NONE */ )
{
	return bgfx::createDynamicVertexBuffer( _num, _decl, _flags );
}

XE::DynamicVertexBufferHandle XE::GFX::CreateDynamicVertexBuffer( const MemoryView * _mem, const VertexLayout &_decl, uint16 _flags /*= BGFX_BUFFER_NONE */ )
{
	return bgfx::createDynamicVertexBuffer( _mem, _decl, _flags );
}

XE::uint32 XE::GFX::GetAvailTransientIndexBuffer( uint32 _num )
{
	return bgfx::getAvailTransientIndexBuffer( _num );
}

XE::uint32 XE::GFX::GetAvailTransientVertexBuffer( uint32 _num, const VertexLayout &_decl )
{
	return bgfx::getAvailTransientVertexBuffer( _num, _decl );
}

XE::uint32 XE::GFX::GetAvailInstanceDataBuffer( uint32 _num, uint16 _stride )
{
	return bgfx::getAvailInstanceDataBuffer( _num, _stride );
}

void XE::GFX::AllocTransientIndexBuffer( TransientIndexBuffer * _tib, uint32 _num )
{
	bgfx::allocTransientIndexBuffer( _tib, _num );
}

void XE::GFX::AllocTransientVertexBuffer( TransientVertexBuffer * _tvb, uint32 _num, const VertexLayout &_decl )
{
	bgfx::allocTransientVertexBuffer( _tvb, _num, _decl );
}

bool XE::GFX::AllocTransientBuffers( TransientVertexBuffer * _tvb, const VertexLayout &_decl, uint32 _numVertices, TransientIndexBuffer * _tib, uint32 _numIndices )
{
	return bgfx::allocTransientBuffers( _tvb, _decl, _numVertices, _tib, _numIndices );
}

void XE::GFX::AllocInstanceDataBuffer( InstanceDataBuffer * _idb, uint32 _num, uint16 _stride )
{
	bgfx::allocInstanceDataBuffer( _idb, _num, _stride );
}

XE::IndirectBufferHandle XE::GFX::CreateIndirectBuffer( uint32 _num )
{
	return bgfx::createIndirectBuffer( _num );
}

XE::ShaderHandle XE::GFX::CreateShader( const MemoryView * _mem )
{
	return bgfx::createShader( _mem );
}

XE::uint16 XE::GFX::GetShaderUniforms( ShaderHandle _handle, UniformHandle * _uniforms /*= nullptr*/, uint16 _max /*= 0 */ )
{
	return bgfx::getShaderUniforms( _handle, _uniforms, _max );
}

void XE::GFX::GetUniformInfo( UniformHandle _handle, UniformInfo &_info )
{
	bgfx::getUniformInfo( _handle, _info );
}

void XE::GFX::SetName( ShaderHandle _handle, const String &_name )
{
	bgfx::setName( _handle, _name.ToCString() );
}

void XE::GFX::SetName( TextureHandle _handle, const String &_name )
{
	bgfx::setName( _handle, _name.ToCString() );
}

XE::ProgramHandle XE::GFX::CreateProgram( ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders /*= false */ )
{
	return bgfx::createProgram( _vsh, _fsh, _destroyShaders );
}

XE::ProgramHandle XE::GFX::CreateProgram( ShaderHandle _csh, bool _destroyShaders /*= false */ )
{
	return bgfx::createProgram( _csh, _destroyShaders );
}

bool XE::GFX::IsTextureValid( uint16 _depth, bool _cubeMap, uint16 _numLayers, TextureFormat _format, uint64 _flags )
{
	return bgfx::isTextureValid( _depth, _cubeMap, _numLayers, _format, (uint32)_flags );
}

void XE::GFX::CalcTextureSize( TextureInfo &_info, uint16 _width, uint16 _height, uint16 _depth, bool _cubeMap, bool _hasMips, uint16 _numLayers, TextureFormat _format )
{
	bgfx::calcTextureSize( _info, _width, _height, _depth, _cubeMap, _hasMips, _numLayers, _format );
}

XE::TextureHandle XE::GFX::CreateTexture( const MemoryView * _mem, uint64 _flags /*= BGFX_TEXTURE_NONE*/, uint8 _skip /*= 0*/, TextureInfo * _info /*= nullptr */ )
{
	return bgfx::createTexture( _mem, (uint32)_flags, _skip, _info );
}

XE::TextureHandle XE::GFX::CreateTexture2D( uint16 _width, uint16 _height, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags /*= BGFX_TEXTURE_NONE*/, const MemoryView * _mem /*= nullptr */ )
{
	return bgfx::createTexture2D( _width, _height, _hasMips, _numLayers, _format, (uint32)_flags, _mem );
}

XE::TextureHandle XE::GFX::CreateTexture2D( BackbufferRatio _ratio, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags /*= BGFX_TEXTURE_NONE */ )
{
	return bgfx::createTexture2D( _ratio, _hasMips, _hasMips, _numLayers, _format, (uint32)_flags );
}

XE::TextureHandle XE::GFX::CreateTexture3D( uint16 _width, uint16 _height, uint16 _depth, bool _hasMips, TextureFormat _format, uint64 _flags /*= BGFX_TEXTURE_NONE*/, const MemoryView * _mem /*= nullptr */ )
{
	return bgfx::createTexture3D( _width, _height, _depth, _hasMips, _format, (uint32)_flags, _mem );
}

XE::TextureHandle XE::GFX::CreateTextureCube( uint16 _size, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags /*= BGFX_TEXTURE_NONE*/, const MemoryView * _mem /*= nullptr */ )
{
	return bgfx::createTextureCube( _size, _hasMips, _numLayers, _format, (uint32)_flags, _mem );
}

void XE::GFX::UpdateTexture2D( TextureHandle _handle, uint16 _layer, uint8 _mip, uint16 _x, uint16 _y, uint16 _width, uint16 _height, const MemoryView * _mem, uint16 _pitch /*= UINT16_MAX */ )
{
	bgfx::updateTexture2D( _handle, _layer, _mip, _x, _y, _width, _height, _mem, _pitch );
}

void XE::GFX::UpdateTexture3D( TextureHandle _handle, uint8 _mip, uint16 _x, uint16 _y, uint16 _z, uint16 _width, uint16 _height, uint16 _depth, const MemoryView * _mem )
{
	bgfx::updateTexture3D( _handle, _mip, _x, _y, _z, _width, _height, _depth, _mem );
}

void XE::GFX::UpdateTextureCube( TextureHandle _handle, uint16 _layer, uint8 _side, uint8 _mip, uint16 _x, uint16 _y, uint16 _width, uint16 _height, const MemoryView * _mem, uint16 _pitch /*= UINT16_MAX */ )
{
	bgfx::updateTextureCube( _handle, _layer, _side, _mip, _x, _y, _width, _height, _mem, _pitch );
}

XE::uint32 XE::GFX::ReadTexture( TextureHandle _handle, void * _data, uint8 _mip /*= 0 */ )
{
	return bgfx::readTexture( _handle, _data, _mip );
}

XE::FrameBufferHandle XE::GFX::CreateFrameBuffer( uint16 _width, uint16 _height, TextureFormat _format, uint64 _textureFlags /*= BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP */ )
{
	return bgfx::createFrameBuffer( _width, _height, _format, (uint32)_textureFlags );
}

XE::FrameBufferHandle XE::GFX::CreateFrameBuffer( BackbufferRatio _ratio, TextureFormat _format, uint64 _textureFlags /*= BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP */ )
{
	return bgfx::createFrameBuffer( _ratio, _format, (uint32)_textureFlags );
}

XE::FrameBufferHandle XE::GFX::CreateFrameBuffer( uint8 _num, const TextureHandle * _handles, bool _destroyTextures /*= false */ )
{
	return bgfx::createFrameBuffer( _num, _handles, _destroyTextures );
}

XE::FrameBufferHandle XE::GFX::CreateFrameBuffer( uint8 _num, const Attachment * _attachment, bool _destroyTextures /*= false */ )
{
	return bgfx::createFrameBuffer( _num, _attachment, _destroyTextures );
}

XE::FrameBufferHandle XE::GFX::CreateFrameBuffer( void * _nwh, uint16 _width, uint16 _height, TextureFormat _format /*= TextureFormat::Count*/, TextureFormat _depthFormat /*= TextureFormat::Count */ )
{
	return bgfx::createFrameBuffer( _nwh, _width, _height, _depthFormat );
}

XE::TextureHandle XE::GFX::GetTexture( FrameBufferHandle _handle, uint8 _attachment /*= 0 */ )
{
	return bgfx::getTexture( _handle, _attachment );
}

XE::UniformHandle XE::GFX::CreateUniform( const String &_name, UniformType _type, uint16 _num /*= 1 */ )
{
	return bgfx::createUniform( _name.ToCString(), _type, _num );
}

XE::OcclusionQueryHandle XE::GFX::CreateOcclusionQuery()
{
	return bgfx::createOcclusionQuery();
}

XE::OcclusionQueryResult XE::GFX::GetResult( OcclusionQueryHandle _handle, int32 * _result /*= nullptr */ )
{
	return bgfx::getResult( _handle, _result );
}

void XE::GFX::SetPaletteColor( uint8 _index, uint32 _rgba )
{
	bgfx::setPaletteColor( _index, _rgba );
}

void XE::GFX::SetPaletteColor( uint8 _index, const float * _rgba )
{
	bgfx::setPaletteColor( _index, _rgba );
}

void XE::GFX::SetPaletteColor( uint8 _index, float _r, float _g, float _b, float _a )
{
	bgfx::setPaletteColor( _index, _r, _g, _b, _a );
}

void XE::GFX::SetViewName( ViewHandle _id, const String &_name )
{
	bgfx::setViewName( _id, _name.ToCString() );
}

void XE::GFX::SetViewRect( ViewHandle _id, uint16 _x, uint16 _y, uint16 _width, uint16 _height )
{
	bgfx::setViewRect( _id, _x, _y, _width, _height );
}

void XE::GFX::SetViewRect( ViewHandle _id, uint16 _x, uint16 _y, BackbufferRatio _ratio )
{
	bgfx::setViewRect( _id, _x, _y, _ratio );
}

void XE::GFX::SetViewScissor( ViewHandle _id, uint16 _x /*= 0*/, uint16 _y /*= 0*/, uint16 _width /*= 0*/, uint16 _height /*= 0 */ )
{
	bgfx::setViewScissor( _id, _x, _y, _width, _height );
}

void XE::GFX::SetViewClear( ViewHandle _id, uint16 _flags, uint32 _rgba /*= 0x000000ff*/, float _depth /*= 1.0f*/, uint8 _stencil /*= 0 */ )
{
	bgfx::setViewClear( _id, _flags, _rgba, _depth, _stencil );
}

void XE::GFX::SetViewClear( ViewHandle _id, uint16 _flags, float _depth, uint8 _stencil, uint8 _0 /*= UINT8_MAX*/, uint8 _1 /*= UINT8_MAX*/, uint8 _2 /*= UINT8_MAX*/, uint8 _3 /*= UINT8_MAX*/, uint8 _4 /*= UINT8_MAX*/, uint8 _5 /*= UINT8_MAX*/, uint8 _6 /*= UINT8_MAX*/, uint8 _7 /*= UINT8_MAX */ )
{
	bgfx::setViewClear( _id, _flags, _depth, _stencil, _0, _1, _2, _3, _4, _5, _6, _7 );
}

void XE::GFX::SetViewMode( ViewHandle _id, ViewMode _mode /*= ViewMode::Default */ )
{
	bgfx::setViewMode( _id, _mode );
}

void XE::GFX::SetViewFrameBuffer( ViewHandle _id, FrameBufferHandle _handle )
{
	bgfx::setViewFrameBuffer( _id, _handle );
}

void XE::GFX::SetViewTransform( ViewHandle _id, const void * _view, const void * _proj )
{
	bgfx::setViewTransform( _id, _view, _proj );
}

void XE::GFX::SetViewOrder( ViewHandle _id /*= 0*/, uint16 _num /*= UINT16_MAX*/, const ViewHandle * _order /*= nullptr */ )
{
	bgfx::setViewOrder( _id, _num, _order );
}

void XE::GFX::ResetView( ViewHandle _id )
{
	bgfx::resetView( _id );
}

void XE::GFX::SetMarker( const String &_marker )
{
	bgfx::setMarker( _marker.ToCString() );
}

void XE::GFX::SetState( uint64 _state, uint32 _rgba /*= 0 */ )
{
	bgfx::setState( _state, _rgba );
}

void XE::GFX::SetCondition( OcclusionQueryHandle _handle, bool _visible )
{
	bgfx::setCondition( _handle, _visible );
}

void XE::GFX::SetStencil( uint32 _fstencil, uint32 _bstencil /*= BGFX_STENCIL_NONE */ )
{
	bgfx::setStencil( _fstencil, _bstencil );
}

XE::uint16 XE::GFX::SetScissor( uint16 _x, uint16 _y, uint16 _width, uint16 _height )
{
	return bgfx::setScissor( _x, _y, _width, _height );
}

void XE::GFX::SetScissord( uint16 _cache /*= UINT16_MAX */ )
{
	bgfx::setScissor( _cache );
}

XE::uint32 XE::GFX::SetTransform( const TransformData * _mtx, uint16 _num /*= 1 */ )
{
	return bgfx::setTransform( _mtx, _num );
}

void XE::GFX::SetTransform( uint32 _cache, uint16 _num /*= 1 */ )
{
	bgfx::setTransform( _cache, _num );
}

XE::uint32 XE::GFX::AllocTransform( TransformData * _transform, uint16 _num )
{
	return bgfx::allocTransform( _transform, _num );
}

void XE::GFX::SetUniform( UniformHandle _handle, const void * _value, uint16 _num /*= 1 */ )
{
	bgfx::setUniform( _handle, _value, _num );
}

void XE::GFX::SetIndexBuffer( IndexBufferHandle _handle, uint32 _firstIndex, uint32 _numIndices )
{
	bgfx::setIndexBuffer( _handle, _firstIndex, _numIndices );
}

void XE::GFX::SetIndexBuffer( DynamicIndexBufferHandle _handle, uint32 _firstIndex, uint32 _numIndices )
{
	bgfx::setIndexBuffer( _handle, _firstIndex, _numIndices );
}

void XE::GFX::SetIndexBuffer( const TransientIndexBuffer * _tib, uint32 _firstIndex, uint32 _numIndices )
{
	bgfx::setIndexBuffer( _tib, _firstIndex, _numIndices );
}

void XE::GFX::SetVertexBuffer( uint8 _stream, VertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices )
{
	bgfx::setVertexBuffer( _stream, _handle, _startVertex, _numVertices );
}

void XE::GFX::SetVertexBuffer( uint8 _stream, DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices )
{
	bgfx::setVertexBuffer( _stream, _handle, _startVertex, _numVertices );
}

void XE::GFX::SetVertexBuffer( uint8 _stream, const TransientVertexBuffer * _tvb, uint32 _startVertex, uint32 _numVertices )
{
	bgfx::setVertexBuffer( _stream, _tvb, _startVertex, _numVertices );
}

void XE::GFX::SetInstanceDataBuffer( const InstanceDataBuffer * _idb, uint32 _start, uint32 _num )
{
	bgfx::setInstanceDataBuffer( _idb, _start, _num );
}

void XE::GFX::SetInstanceDataBuffer( VertexBufferHandle _handle, uint32 _startVertex, uint32 _num )
{
	bgfx::setInstanceDataBuffer( _handle, _startVertex, _num );
}

void XE::GFX::SetInstanceDataBuffer( DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _num )
{
	bgfx::setInstanceDataBuffer( _handle, _startVertex, _num );
}

void XE::GFX::SetTexture( uint8 _stage, UniformHandle _sampler, TextureHandle _handle, uint32 _flags /*= UINT32_MAX */ )
{
	bgfx::setTexture( _stage, _sampler, _handle, _flags );
}

void XE::GFX::Touch( ViewHandle _id )
{
	bgfx::touch( _id );
}

void XE::GFX::Submit( ViewHandle _id, ProgramHandle _handle, int32 _depth /*= 0*/, bool _preserveState /*= false */ )
{
	bgfx::submit( _id, _handle, _depth, _preserveState );
}

void XE::GFX::Submit( ViewHandle _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, int32 _depth /*= 0*/, bool _preserveState /*= false */ )
{
	bgfx::submit( _id, _program, _occlusionQuery, _depth, _preserveState );
}

void XE::GFX::Submit( ViewHandle _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16 _start /*= 0*/, uint16 _num /*= 1*/, int32 _depth /*= 0*/, bool _preserveState /*= false */ )
{
	bgfx::submit( _id, _handle, _indirectHandle, _start, _num, _depth, _preserveState );
}

void XE::GFX::SetImage( uint8 _stage, TextureHandle _handle, uint8 _mip, Access _access, TextureFormat _format /*= TextureFormat::Count */ )
{
	bgfx::setImage( _stage, _handle, _mip, _access, _format );
}

void XE::GFX::SetBuffer( uint8 _stage, IndexBufferHandle _handle, Access _access )
{
	bgfx::setBuffer( _stage, _handle, _access );
}

void XE::GFX::SetBuffer( uint8 _stage, VertexBufferHandle _handle, Access _access )
{
	bgfx::setBuffer( _stage, _handle, _access );
}

void XE::GFX::SetBuffer( uint8 _stage, DynamicIndexBufferHandle _handle, Access _access )
{
	bgfx::setBuffer( _stage, _handle, _access );
}

void XE::GFX::SetBuffer( uint8 _stage, DynamicVertexBufferHandle _handle, Access _access )
{
	bgfx::setBuffer( _stage, _handle, _access );
}

void XE::GFX::SetBuffer( uint8 _stage, IndirectBufferHandle _handle, Access _access )
{
	bgfx::setBuffer( _stage, _handle, _access );
}

void XE::GFX::Dispatch( ViewHandle _id, ProgramHandle _handle, uint32 _numX /*= 1*/, uint32 _numY /*= 1*/, uint32 _numZ /*= 1 */ )
{
	bgfx::dispatch( _id, _handle, _numX, _numY, _numZ );
}

void XE::GFX::Dispatch( ViewHandle _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16 _start /*= 0*/, uint16 _num /*= 1 */ )
{
	bgfx::dispatch( _id, _handle, _indirectHandle, _start, _num );
}

void XE::GFX::Discard()
{
	bgfx::discard();
}

void XE::GFX::Blit( ViewHandle _id, TextureHandle _dst, uint16 _dstX, uint16 _dstY, TextureHandle _src, uint16 _srcX /*= 0*/, uint16 _srcY /*= 0*/, uint16 _width /*= UINT16_MAX*/, uint16 _height /*= UINT16_MAX */ )
{
	bgfx::blit( _id, _dst, _dstX, _dstY, _src, _srcX, _srcY, _width, _height );
}

void XE::GFX::Blit( ViewHandle _id, TextureHandle _dst, uint8 _dstMip, uint16 _dstX, uint16 _dstY, uint16 _dstZ, TextureHandle _src, uint8 _srcMip /*= 0*/, uint16 _srcX /*= 0*/, uint16 _srcY /*= 0*/, uint16 _srcZ /*= 0*/, uint16 _width /*= UINT16_MAX*/, uint16 _height /*= UINT16_MAX*/, uint16 _depth /*= UINT16_MAX */ )
{
	bgfx::blit( _id, _dst, _dstMip, _dstX, _dstY, _srcZ, _src, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth );
}

void XE::GFX::RequestScreenShot( FrameBufferHandle _handle, const std::filesystem::path &_filePath )
{
	bgfx::requestScreenShot( _handle, _filePath.string().c_str() );
}

void XE::GFX::Flush()
{
	bgfx::frame();
	bgfx::frame();
}

bool XE::GFX::IsOriginBottomLeft()
{
	return bgfx::getCaps()->originBottomLeft;
}

bool XE::GFX::IsHomogeneousDepth()
{
	return bgfx::getCaps()->homogeneousDepth;
}

float XE::GFX::GetHalfTexel()
{
	return RendererType::Direct3D9 == bgfx::getRendererType() ? 0.5f : 0.0f;
}

XE::uint32 XE::GFX::GetMaxBlendTransforms()
{
	return 128;
}

XE::uint64 XE::GFX::ScreenQuad( float dest_width, float dest_height, float depth /*= 0.0f*/, float width /*= 1.0f*/, float height /*= 1.0f */ )
{
	float texture_half = GetHalfTexel();
	bool origin_bottom_left = IsOriginBottomLeft();

	if ( 3 == bgfx::getAvailTransientVertexBuffer( 3, PosTexcoord0Vertex::GetLayout() ) )
	{
		TransientVertexBuffer vb;
		AllocTransientVertexBuffer(&vb, 3, PosTexcoord0Vertex::GetLayout());
		auto vertex = reinterpret_cast<PosTexcoord0Vertex*>( vb.data );

		const float minx = -width;
		const float maxx = width;
		const float miny = 0.0f;
		const float maxy = height * 2.0f;

		const float texel_half_w = texture_half / dest_width;
		const float texel_half_h = texture_half / dest_height;
		const float minu = -1.0f + texel_half_w;
		const float maxu = 1.0f + texel_half_h;

		const float zz = depth;

		float minv = texel_half_h;
		float maxv = 2.0f + texel_half_h;

		if ( origin_bottom_left )
		{
			float temp = minv;
			minv = maxv;
			maxv = temp;

			minv -= 1.0f;
			maxv -= 1.0f;
		}

		vertex[0].x = minx;
		vertex[0].y = miny;
		vertex[0].z = zz;
		vertex[0].u = minu;
		vertex[0].v = minv;

		vertex[1].x = maxx;
		vertex[1].y = miny;
		vertex[1].z = zz;
		vertex[1].u = maxu;
		vertex[1].v = minv;

		vertex[2].x = maxx;
		vertex[2].y = maxy;
		vertex[2].z = zz;
		vertex[2].u = maxu;
		vertex[2].v = maxv;

		bgfx::setVertexBuffer( 0, &vb );
	}

	return 0;
}

XE::uint64 XE::GFX::ClipQuad( float depth /*= 0.0f*/, float width /*= 1.0f*/, float height /*= 1.0f */ )
{
	bool origin_bottom_left = IsOriginBottomLeft();

	if ( 4 == bgfx::getAvailTransientVertexBuffer( 4, PosTexcoord0Vertex::GetLayout() ) )
	{
		TransientVertexBuffer vb;
		AllocTransientVertexBuffer(&vb, 4, PosTexcoord0Vertex::GetLayout());
		auto vertex = reinterpret_cast<PosTexcoord0Vertex*>( vb.data );

		const float minx = -width;
		const float maxx = width;
		const float miny = -height;
		const float maxy = height;

		const float minu = 0.0f;
		const float maxu = 1.0f;

		const float zz = depth;

		float minv = 1.0f;
		float maxv = 0.0f;

		if ( origin_bottom_left )
		{
			minv = 1.0f - minv;
			maxv = 1.0f - maxv;
		}

		vertex[0].x = minx;
		vertex[0].y = maxy;
		vertex[0].z = zz;
		vertex[0].u = minu;
		vertex[0].v = maxv;

		vertex[1].x = maxx;
		vertex[1].y = maxy;
		vertex[1].z = zz;
		vertex[1].u = maxu;
		vertex[1].v = maxv;

		vertex[2].x = minx;
		vertex[2].y = miny;
		vertex[2].z = zz;
		vertex[2].u = minu;
		vertex[2].v = minv;

		vertex[3].x = maxx;
		vertex[3].y = miny;
		vertex[3].z = zz;
		vertex[3].u = maxu;
		vertex[3].v = minv;

		bgfx::setVertexBuffer( 0, &vb );
	}

	return BGFX_STATE_PT_TRISTRIP;
}

void XE::GFX::GetSizeFromRatio( BackbufferRatio _ratio, uint16 &_width, uint16 &_height )
{
	auto stats = bgfx::getStats();
	_width = stats->width;
	_height = stats->height;
	switch ( _ratio )
	{
	case BackbufferRatio::Half:
		_width /= 2;
		_height /= 2;
		break;
	case BackbufferRatio::Quarter:
		_width /= 4;
		_height /= 4;
		break;
	case BackbufferRatio::Eighth:
		_width /= 8;
		_height /= 8;
		break;
	case BackbufferRatio::Sixteenth:
		_width /= 16;
		_height /= 16;
		break;
	case BackbufferRatio::Double:
		_width *= 2;
		_height *= 2;
		break;

	default:
		break;
	}

	_width = std::max<std::uint16_t>( 1, _width );
	_height = std::max<std::uint16_t>( 1, _height );
}

const XE::String& XE::GFX::GetRendererFilenameExtension()
{
	static const std::map<RendererType, XE::String> types =
	{
		{ RendererType::Direct3D9, ".dx9" },
		{ RendererType::Direct3D11, ".dx11" },
		{ RendererType::Direct3D12, ".dx12" },
		{ RendererType::Gnm, ".gnm" },
		{ RendererType::Metal, ".metal" },
		{ RendererType::OpenGL, ".gl" },
		{ RendererType::OpenGLES, ".gles" },
		{ RendererType::Noop, ".noop" }
	};

	const auto it = types.find( bgfx::getRendererType() );
	if ( it != types.cend() )
	{
		return it->second;
	}
	static XE::String unknown = ".unknown";
	return unknown;
}

bool XE::GFX::IsSupported( uint64 flag )
{
	const auto caps = GetCaps();
	bool supported = 0 != ( caps->supported & flag );
	return supported;
}

bool XE::GFX::IsFormatSupported( uint16 flags, TextureFormat format )
{
	const uint32 formatCaps = bgfx::getCaps()->formats[format];
	return 0 != ( formatCaps & flags );
}

XE::TextureFormat XE::GFX::GetBestFormat( uint16 type_flags, uint32 search_flags )
{
	bool is_depth = ( ( search_flags & (uint32)FormatSearchFlags::REQUIRES_DEPTH ) != 0 );

	if ( !is_depth )
	{
		if ( ( ( search_flags & (uint32)FormatSearchFlags::PREFER_COMPRESSED ) != 0u ) &&
			( ( search_flags & (uint32)FormatSearchFlags::FOUR_CHANNELS ) != 0u ) &&
			 ( ( search_flags & (uint32)FormatSearchFlags::FLOATING_POINT ) == 0u ) )
		{
			if ( ( search_flags & (uint32)FormatSearchFlags::REQUIRES_ALPHA ) != 0u )
			{
				if ( IsFormatSupported(type_flags, TextureFormat::BC2) )
				{
					return TextureFormat::BC2;
				}
				if ( IsFormatSupported(type_flags, TextureFormat::BC3) )
				{
					return TextureFormat::BC3;
				}
			}
			else
			{
				if ( IsFormatSupported(type_flags, TextureFormat::BC1) )
				{
					return TextureFormat::BC1;
				}
			}
		}

		bool accept_padding = ( ( search_flags & (uint32)FormatSearchFlags::ALLOW_PADDING_CHANNELS ) != 0 );
		bool requires_alpha = ( ( search_flags & (uint32)FormatSearchFlags::REQUIRES_ALPHA ) != 0 );
		if ( ( search_flags & (uint32)FormatSearchFlags::FLOATING_POINT ) != 0u )
		{
			bool accept_half = ( ( search_flags & (uint32)FormatSearchFlags::HALF_PRECISION_FLOAT ) != 0 );
			bool accept_full = ( ( search_flags & (uint32)FormatSearchFlags::FULL_PRECISION_FLOAT ) != 0 );

			if ( ( search_flags & (uint32)FormatSearchFlags::FOUR_CHANNELS ) != 0u )
			{
				if ( accept_full && IsFormatSupported(type_flags, TextureFormat::RGBA32F) )
				{
					return TextureFormat::RGBA32F;
				}
				else if ( accept_half && IsFormatSupported(type_flags, TextureFormat::RGBA16F) )
				{
					return TextureFormat::RGBA16F;
				}
			}
			else if ( ( search_flags & (uint32)FormatSearchFlags::TWO_CHANNELS ) != 0u )
			{
				if ( !requires_alpha )
				{
					if ( accept_full && IsFormatSupported(type_flags, TextureFormat::RG32F) )
					{
						return TextureFormat::RG32F;
					}
					else if ( accept_half && IsFormatSupported(type_flags, TextureFormat::RG16F) )
					{
						return TextureFormat::RG16F;
					}
					else if ( accept_padding && accept_half && IsFormatSupported(type_flags, TextureFormat::RGBA16F) )
					{
						return TextureFormat::RGBA16F;
					}
					else if ( accept_padding && accept_full && IsFormatSupported(type_flags, TextureFormat::RGBA32F) )
					{
						return TextureFormat::RGBA32F;
					}
				}
				else
				{
					if ( accept_padding && accept_half && IsFormatSupported(type_flags, TextureFormat::RGBA16F) )
					{
						return TextureFormat::RGBA16F;
					}
					else if ( accept_padding && accept_full && IsFormatSupported(type_flags, TextureFormat::RGBA32F) )
					{
						return TextureFormat::RGBA32F;
					}
				}
			}
			else if ( ( search_flags & (uint32)FormatSearchFlags::ONE_CHANNEL ) != 0u )
			{
				if ( !requires_alpha )
				{
					if ( accept_full && IsFormatSupported(type_flags, TextureFormat::R32F) )
					{
						return TextureFormat::R32F;
					}
					else if ( accept_half && IsFormatSupported(type_flags, TextureFormat::R16F) )
					{
						return TextureFormat::R16F;
					}
					else if ( accept_padding && accept_half && IsFormatSupported(type_flags, TextureFormat::RG16F) )
					{
						return TextureFormat::RG16F;
					}
					else if ( accept_padding && accept_full && IsFormatSupported(type_flags, TextureFormat::RG32F) )
					{
						return TextureFormat::RG32F;
					}
					else if ( accept_padding && accept_half && IsFormatSupported(type_flags, TextureFormat::RGBA16F) )
					{
						return TextureFormat::RGBA16F;
					}
					else if ( accept_padding && accept_full && IsFormatSupported(type_flags, TextureFormat::RGBA32F) )
					{
						return TextureFormat::RGBA32F;
					}
				}
				else
				{
					if ( accept_padding && accept_half && IsFormatSupported(type_flags, TextureFormat::RGBA16F) )
					{
						return TextureFormat::RGBA16F;
					}
					else if ( accept_padding && accept_full && IsFormatSupported(type_flags, TextureFormat::RGBA32F) )
					{
						return TextureFormat::RGBA32F;
					}
				}
			}
		}
		else
		{
			if ( ( search_flags & (uint32)FormatSearchFlags::FOUR_CHANNELS ) != 0u )
			{
				if ( !requires_alpha )
				{
					if ( IsFormatSupported(type_flags, TextureFormat::RGBA8) )
					{
						return TextureFormat::RGBA8;
					}
					else if ( IsFormatSupported(type_flags, TextureFormat::BGRA8) )
					{
						return TextureFormat::BGRA8;
					}
					else if ( IsFormatSupported(type_flags, TextureFormat::RGB10A2) )
					{
						return TextureFormat::RGB10A2;
					}
					else if ( IsFormatSupported(type_flags, TextureFormat::RGBA16) )
					{
						return TextureFormat::RGBA16;
					}
					else if ( IsFormatSupported(type_flags, TextureFormat::R5G6B5) )
					{
						return TextureFormat::R5G6B5;
					}
					else if ( IsFormatSupported(type_flags, TextureFormat::RGB5A1) )
					{
						return TextureFormat::RGB5A1;
					}
				}
				else
				{
					if ( IsFormatSupported(type_flags, TextureFormat::RGBA8) )
					{
						return TextureFormat::RGBA8;
					}
					else if ( IsFormatSupported(type_flags, TextureFormat::RGBA16) )
					{
						return TextureFormat::RGBA16;
					}
					else if ( IsFormatSupported(type_flags, TextureFormat::RGB10A2) )
					{
						return TextureFormat::RGB10A2;
					}
					else if ( IsFormatSupported(type_flags, TextureFormat::RGB5A1) )
					{
						return TextureFormat::RGB5A1;
					}
				}
			}
			else if ( ( search_flags & (uint32)FormatSearchFlags::TWO_CHANNELS ) != 0u )
			{
				if ( !requires_alpha )
				{
					if ( IsFormatSupported(type_flags, TextureFormat::RG16) )
					{
						return TextureFormat::RG16;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGB8) )
					{
						return TextureFormat::RGB8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::BGRA8) )
					{
						return TextureFormat::BGRA8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGBA8) )
					{
						return TextureFormat::RGBA8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGB10A2) )
					{
						return TextureFormat::RGB10A2;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGBA16) )
					{
						return TextureFormat::RGBA16;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::R5G6B5) )
					{
						return TextureFormat::R5G6B5;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGB5A1) )
					{
						return TextureFormat::RGB5A1;
					}
				}
				else
				{
					if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::BGRA8) )
					{
						return TextureFormat::BGRA8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGBA8) )
					{
						return TextureFormat::RGBA8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGBA16) )
					{
						return TextureFormat::RGBA16;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGB10A2) )
					{
						return TextureFormat::RGB10A2;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGB5A1) )
					{
						return TextureFormat::RGB5A1;
					}
				}
			}
			else if ( ( search_flags & (uint32)FormatSearchFlags::ONE_CHANNEL ) != 0u )
			{
				if ( !requires_alpha )
				{
					if ( IsFormatSupported(type_flags, TextureFormat::R8) )
					{
						return TextureFormat::R8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RG16) )
					{
						return TextureFormat::RG16;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGB8) )
					{
						return TextureFormat::RGB8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::BGRA8) )
					{
						return TextureFormat::BGRA8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGBA8) )
					{
						return TextureFormat::RGBA8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGB10A2) )
					{
						return TextureFormat::RGB10A2;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGBA16) )
					{
						return TextureFormat::RGBA16;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::R5G6B5) )
					{
						return TextureFormat::R5G6B5;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGB5A1) )
					{
						return TextureFormat::RGB5A1;
					}
				}
				else
				{
					if ( IsFormatSupported(type_flags, TextureFormat::A8) )
					{
						return TextureFormat::A8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::BGRA8) )
					{
						return TextureFormat::BGRA8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGBA8) )
					{
						return TextureFormat::RGBA8;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGBA16) )
					{
						return TextureFormat::RGBA16;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGB10A2) )
					{
						return TextureFormat::RGB10A2;
					}
					else if ( accept_padding && IsFormatSupported(type_flags, TextureFormat::RGB5A1) )
					{
						return TextureFormat::RGB5A1;
					}
				}
			}
		}
	}
	else
	{
		bool requires_stencil = ( ( search_flags & (uint32)FormatSearchFlags::REQUIRES_STENCIL ) != 0 );
		if ( ( search_flags & (uint32)FormatSearchFlags::FLOATING_POINT ) != 0u )
		{
			bool accept_full = ( ( search_flags & (uint32)FormatSearchFlags::FULL_PRECISION_FLOAT ) != 0 );
			if ( !requires_stencil )
			{
				if ( accept_full && IsFormatSupported(type_flags, TextureFormat::D32F) )
				{
					return TextureFormat::D32F;
				}
				else if ( accept_full && IsFormatSupported(type_flags, TextureFormat::D24F) )
				{
					return TextureFormat::D24F;
				}
			}
			else
			{
				// no floating point that supports stencil
				// if (accept_full && is_format_supported(type_flags,
				// TextureFormat::D24S8))
				//	return TextureFormat::D24S8;

			}

		}
		else
		{
			if ( !requires_stencil )
			{
				if ( IsFormatSupported(type_flags, TextureFormat::D32) )
				{
					return TextureFormat::D32;
				}
				else if ( IsFormatSupported(type_flags, TextureFormat::D24) )
				{
					return TextureFormat::D24;
				}
				else if ( IsFormatSupported(type_flags, TextureFormat::D16) )
				{
					return TextureFormat::D16;
				}
			}
			else
			{
				if ( IsFormatSupported(type_flags, TextureFormat::D24S8) )
				{
					return TextureFormat::D24S8;
				}

			}
		}
	}

	return TextureFormat::Unknown;
}

XE::uint64 XE::GFX::GetDefaultRtSamplerFlags()
{
	static uint64 sampler_flags = 0 | BGFX_TEXTURE_RT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP;

	return sampler_flags;
}
