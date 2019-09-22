#include "Gfx.h"

#include <bgfx/bgfx.h>

USING_XE

template<typename To, typename Form> To HandleCast( XE::Handle<Form> handle )
{
	To to;

	if( handle )
	{
		to.idx = ( XE::uint16 )handle.GetValue();
	}
	else
	{
		to.idx = bgfx::kInvalidHandle;
	}

	return to;
}

template<typename To, typename Form> To HandleCast( Form handle )
{
	if( handle.idx == bgfx::kInvalidHandle )
	{
		return To();
	}

	return ( XE::uint64 )handle.idx;
}

XE::VertexLayout::VertexLayout()
	: m_stride( 0 )
{
}

XE::VertexLayout & XE::VertexLayout::begin( RendererType _renderer /*= RendererType::NOOP */ )
{
	( ( bgfx::VertexLayout * )( this ) )->begin( ( bgfx::RendererType::Enum )_renderer );

	return *this;
}

void XE::VertexLayout::end()
{
	( ( bgfx::VertexLayout * )( this ) )->end();
}

XE::VertexLayout & XE::VertexLayout::add( Attrib _attrib, XE::uint8 _num, AttribType _type, bool _normalized /*= false */, bool _asInt /*= false */ )
{
	( ( bgfx::VertexLayout * )( this ) )->add( ( bgfx::Attrib::Enum )_attrib, _num, ( bgfx::AttribType::Enum )_type, _normalized, _asInt );

	return *this;
}

XE::VertexLayout & XE::VertexLayout::skip( XE::uint8 _num )
{
	( ( bgfx::VertexLayout * )( this ) )->skip( _num );

	return *this;
}

void XE::VertexLayout::decode( Attrib _attrib, XE::uint8 & _num, AttribType & _type, bool & _normalized, bool & _asInt ) const
{
	( ( bgfx::VertexLayout * )( this ) )->decode( ( bgfx::Attrib::Enum )_attrib, _num, ( bgfx::AttribType::Enum & )_type, _normalized, _asInt );
}

bool XE::VertexLayout::has( Attrib _attrib ) const
{
	return ( ( bgfx::VertexLayout * )( this ) )->has( ( bgfx::Attrib::Enum )_attrib );
}

XE::uint16 XE::VertexLayout::getOffset( Attrib _attrib ) const
{
	return ( ( bgfx::VertexLayout * )( this ) )->getOffset( ( bgfx::Attrib::Enum )_attrib );
}

XE::uint16 XE::VertexLayout::getStride() const
{
	return ( ( bgfx::VertexLayout * )( this ) )->getStride();
}

XE::uint32 XE::VertexLayout::getSize( XE::uint32 _num ) const
{
	return ( ( bgfx::VertexLayout * )( this ) )->getSize( _num );
}

XE::Encoder::Encoder()
	:_encoder( nullptr )
{

}

XE::Encoder::Encoder( Encoder && val )
	: _encoder( val._encoder )
{

}

XE::Encoder & XE::Encoder::operator=( Encoder && val )
{
	std::swap( _encoder, val._encoder );

	return *this;
}

#define _p (( bgfx::Encoder * )( _encoder ))

void XE::Encoder::setMarker( const XE::String & _marker )
{
	_p->setMarker( _marker.ToCString() );
}

void XE::Encoder::setState( XE::uint64 _state, XE::uint32 _rgba /*= 0 */ )
{
	_p->setState( _state, _rgba );
}

void XE::Encoder::setCondition( OcclusionQueryHandle _handle, bool _visible )
{
	_p->setCondition( HandleCast<bgfx::OcclusionQueryHandle>( _handle ), _visible );
}

void XE::Encoder::setStencil( XE::uint32 _fstencil, StencilFlags _bstencil /*= StencilFlags::NONE /* , XE::uint32 _bstencil = BGFX_STENCIL_NONE */ )
{
	_p->setStencil( _fstencil, ( XE::uint32 )_bstencil );
}

XE::uint16 XE::Encoder::setScissor( XE::uint16 _x, XE::uint16 _y, XE::uint16 _width, XE::uint16 _height )
{
	return _p->setScissor( _x, _y, _width, _height );
}

void XE::Encoder::setScissor( XE::uint16 _cache /*= UINT16_MAX */ )
{
	_p->setScissor( _cache );
}

XE::uint32 XE::Encoder::setTransform( XE::basic_memory_view<Mat4> _transform /* const void * _mtx */ /* , XE::uint16 _num = 1 */ )
{
	return _p->setTransform( _transform.data(), _transform.size() );
}

void XE::Encoder::setTransform( XE::uint32 _cache, XE::uint16 _num /*= 1 */ )
{
	_p->setTransform( _cache, _num );
}

XE::uint32 XE::Encoder::allocTransform( XE::basic_memory_view<Mat4> _transform /* Transform * _transform */ /* , XE::uint16 _num */ )
{
	return _p->allocTransform( ( bgfx::Transform * )_transform.data(), _transform.size() );
}

void XE::Encoder::setUniform( UniformHandle _handle, XE::memory_view _value /* , const void * _value */ /* , XE::uint16 _num = 1 */ )
{
	_p->setUniform( HandleCast<bgfx::UniformHandle>( _handle ), _value.data(), _value.size() );
}

void XE::Encoder::setIndexBuffer( IndexBufferHandle _handle )
{
	_p->setIndexBuffer( HandleCast<bgfx::IndexBufferHandle>( _handle ) );
}

void XE::Encoder::setIndexBuffer( IndexBufferHandle _handle, XE::uint32 _firstIndex, XE::uint32 _numIndices )
{
	_p->setIndexBuffer( HandleCast<bgfx::IndexBufferHandle>( _handle ), _firstIndex, _numIndices );
}

void XE::Encoder::setIndexBuffer( DynamicIndexBufferHandle _handle )
{
	_p->setIndexBuffer( HandleCast<bgfx::DynamicIndexBufferHandle>( _handle ) );
}

void XE::Encoder::setIndexBuffer( DynamicIndexBufferHandle _handle, XE::uint32 _firstIndex, XE::uint32 _numIndices )
{
	_p->setIndexBuffer( HandleCast<bgfx::DynamicIndexBufferHandle>( _handle ), _firstIndex, _numIndices );
}

void XE::Encoder::setIndexBuffer( const TransientIndexBuffer * _tib )
{
	_p->setIndexBuffer( ( bgfx::TransientIndexBuffer * )_tib );
}

void XE::Encoder::setIndexBuffer( const TransientIndexBuffer * _tib, XE::uint32 _firstIndex, XE::uint32 _numIndices )
{
	_p->setIndexBuffer( ( bgfx::TransientIndexBuffer * )_tib, _firstIndex, _numIndices );
}

void XE::Encoder::setVertexBuffer( XE::uint8 _stream, VertexBufferHandle _handle )
{
	_p->setVertexBuffer( _stream, HandleCast<bgfx::VertexBufferHandle>( _handle ) );
}

void XE::Encoder::setVertexBuffer( uint8 _stream, VertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle /*= VertexLayoutHandle() */ )
{
	_p->setVertexBuffer( _stream, HandleCast<bgfx::VertexBufferHandle>( _handle ), _startVertex, _numVertices, HandleCast<bgfx::VertexLayoutHandle>( _layoutHandle ) );
}

void XE::Encoder::setVertexBuffer( XE::uint8 _stream, DynamicVertexBufferHandle _handle )
{
	_p->setVertexBuffer( _stream, HandleCast<bgfx::DynamicVertexBufferHandle>( _handle ) );
}

void XE::Encoder::setVertexBuffer( uint8 _stream, DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle /*= VertexLayoutHandle() */ )
{
	_p->setVertexBuffer( _stream, HandleCast<bgfx::DynamicVertexBufferHandle>( _handle ), _startVertex, _numVertices, HandleCast<bgfx::VertexLayoutHandle>( _layoutHandle ) );
}

void XE::Encoder::setVertexBuffer( XE::uint8 _stream, const TransientVertexBuffer * _tvb )
{
	_p->setVertexBuffer( _stream, ( const bgfx::TransientVertexBuffer * )_tvb );
}

void XE::Encoder::setVertexBuffer( uint8 _stream, const TransientVertexBuffer * _tvb, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle /*= VertexLayoutHandle() */ )
{
	_p->setVertexBuffer( _stream, ( const bgfx::TransientVertexBuffer * )_tvb, _startVertex, _numVertices, HandleCast<bgfx::VertexLayoutHandle>( _layoutHandle ) );
}

void XE::Encoder::setVertexCount( XE::uint32 _numVertices )
{
	_p->setVertexCount( _numVertices );
}

void XE::Encoder::setInstanceDataBuffer( const InstanceDataBuffer * _idb )
{
	_p->setInstanceDataBuffer( ( const bgfx::InstanceDataBuffer * )_idb );
}

void XE::Encoder::setInstanceDataBuffer( const InstanceDataBuffer * _idb, XE::uint32 _start, XE::uint32 _num )
{
	_p->setInstanceDataBuffer( ( const bgfx::InstanceDataBuffer * )_idb, _start, _num );
}

void XE::Encoder::setInstanceDataBuffer( VertexBufferHandle _handle, XE::uint32 _start, XE::uint32 _num )
{
	_p->setInstanceDataBuffer( HandleCast<bgfx::VertexBufferHandle>( _handle ), _start, _num );
}

void XE::Encoder::setInstanceDataBuffer( DynamicVertexBufferHandle _handle, XE::uint32 _start, XE::uint32 _num )
{
	_p->setInstanceDataBuffer( HandleCast<bgfx::DynamicVertexBufferHandle>( _handle ), _start, _num );
}

void XE::Encoder::setInstanceCount( XE::uint32 _numInstances )
{
	_p->setInstanceCount( _numInstances );
}

void XE::Encoder::setTexture( XE::uint8 _stage, UniformHandle _sampler, TextureHandle _handle, XE::uint32 _flags /*= UINT32_MAX */ )
{
	_p->setTexture( _stage, HandleCast<bgfx::UniformHandle>( _sampler ), HandleCast<bgfx::TextureHandle>( _sampler ), _flags );
}

void XE::Encoder::touch( ViewHandle _view )
{
	_p->touch( ( XE::uint16 )_view.GetValue() );
}

void XE::Encoder::submit( ViewHandle _view, ProgramHandle _program, XE::uint32 _depth /*= 0 */, bool _preserveState /*= false */ )
{
	_p->submit( ( XE::uint16 )_view.GetValue(), HandleCast<bgfx::ProgramHandle>( _program ), _depth, _preserveState );
}

void XE::Encoder::submit( ViewHandle _view, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, XE::uint32 _depth /*= 0 */, bool _preserveState /*= false */ )
{
	_p->submit( ( XE::uint16 )_view.GetValue(), HandleCast<bgfx::ProgramHandle>( _program ), HandleCast<bgfx::OcclusionQueryHandle>( _occlusionQuery ), _depth, _preserveState );
}

void XE::Encoder::submit( ViewHandle _view, ProgramHandle _program, IndirectBufferHandle _indirectHandle, XE::uint16 _start /*= 0 */, XE::uint16 _num /*= 1 */, XE::uint32 _depth /*= 0 */, bool _preserveState /*= false */ )
{
	_p->submit( ( XE::uint16 )_view.GetValue(), HandleCast<bgfx::ProgramHandle>( _program ), HandleCast<bgfx::IndirectBufferHandle>( _indirectHandle ), _start, _num, _depth, _preserveState );
}

void XE::Encoder::setBuffer( XE::uint8 _stage, IndexBufferHandle _handle, Access _access )
{
	_p->setBuffer( _stage, HandleCast<bgfx::IndexBufferHandle>( _handle ), ( bgfx::Access::Enum )_access );
}

void XE::Encoder::setBuffer( XE::uint8 _stage, VertexBufferHandle _handle, Access _access )
{
	_p->setBuffer( _stage, HandleCast<bgfx::VertexBufferHandle>( _handle ), ( bgfx::Access::Enum )_access );
}

void XE::Encoder::setBuffer( XE::uint8 _stage, DynamicIndexBufferHandle _handle, Access _access )
{
	_p->setBuffer( _stage, HandleCast<bgfx::DynamicIndexBufferHandle>( _handle ), ( bgfx::Access::Enum )_access );
}

void XE::Encoder::setBuffer( XE::uint8 _stage, DynamicVertexBufferHandle _handle, Access _access )
{
	_p->setBuffer( _stage, HandleCast<bgfx::DynamicVertexBufferHandle>( _handle ), ( bgfx::Access::Enum )_access );
}

void XE::Encoder::setBuffer( XE::uint8 _stage, IndirectBufferHandle _handle, Access _access )
{
	_p->setBuffer( _stage, HandleCast<bgfx::IndirectBufferHandle>( _handle ), ( bgfx::Access::Enum )_access );
}

void XE::Encoder::setImage( XE::uint8 _stage, TextureHandle _handle, XE::uint8 _mip, Access _access, TextureFormat _format /*= TextureFormat::UNKNOWN */ )
{
	_p->setImage( _stage, HandleCast<bgfx::TextureHandle>( _handle ), _mip, ( bgfx::Access::Enum )_access, ( bgfx::TextureFormat::Enum )_format );
}

void XE::Encoder::dispatch( ViewHandle _view, ProgramHandle _handle, XE::uint32 _numX /*= 1 */, XE::uint32 _numY /*= 1 */, XE::uint32 _numZ /*= 1 */ )
{
	_p->dispatch( ( XE::uint16 )_view.GetValue(), HandleCast<bgfx::ProgramHandle>( _handle ), _numX, _numY, _numZ );
}

void XE::Encoder::dispatch( ViewHandle _view, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, XE::uint16 _start /*= 0 */, XE::uint16 _num /*= 1 */ )
{
	_p->dispatch( ( XE::uint16 )_view.GetValue(), HandleCast<bgfx::ProgramHandle>( _handle ), HandleCast<bgfx::IndirectBufferHandle>( _indirectHandle ), _start, _num );
}

void XE::Encoder::discard()
{
	_p->discard();
}

void XE::Encoder::blit( ViewHandle _view, TextureHandle _dst, XE::uint16 _dstX, XE::uint16 _dstY, TextureHandle _src, XE::uint16 _srcX /*= 0 */, XE::uint16 _srcY /*= 0 */, XE::uint16 _width /*= UINT16_MAX */, XE::uint16 _height /*= UINT16_MAX */ )
{
	_p->blit( ( XE::uint16 )_view.GetValue(), HandleCast<bgfx::TextureHandle>( _dst ), _dstX, _dstY, HandleCast<bgfx::TextureHandle>( _src ), _srcX, _srcY, _width, _height );
}

void XE::Encoder::blit( ViewHandle _view, TextureHandle _dst, XE::uint8 _dstMip, XE::uint16 _dstX, XE::uint16 _dstY, XE::uint16 _dstZ, TextureHandle _src, XE::uint8 _srcMip /*= 0 */, XE::uint16 _srcX /*= 0 */, XE::uint16 _srcY /*= 0 */, XE::uint16 _srcZ /*= 0 */, XE::uint16 _width /*= UINT16_MAX */, XE::uint16 _height /*= UINT16_MAX */, XE::uint16 _depth /*= UINT16_MAX */ )
{
	_p->blit( ( XE::uint16 )_view.GetValue(), HandleCast<bgfx::TextureHandle>( _dst ), _dstMip, _dstX, _dstY, _dstZ, HandleCast<bgfx::TextureHandle>( _src ), _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth );
}

void XE::Gfx::vertexPack( const XE::Vec4 & _input, bool _inputNormalized, Attrib _attr, const VertexLayout & _layout, XE::memory_view _data /* , void * _data */ /* , XE::uint32 _index = 0 */ )
{
	bgfx::vertexPack( _input.d, _inputNormalized, ( bgfx::Attrib::Enum )_attr, ( const bgfx::VertexLayout & )_layout, (void * )_data.data(), _data.size() );
}

void XE::Gfx::vertexUnpack( XE::Vec4 & _output, Attrib _attr, const VertexLayout & _layout, XE::memory_view _data /* , const void * _data */ /* , XE::uint32 _index = 0 */ )
{
	bgfx::vertexUnpack( _output.d, ( bgfx::Attrib::Enum )_attr, ( const bgfx::VertexLayout & )_layout, (void * )_data.data(), _data.size() );
}

void XE::Gfx::vertexConvert( const VertexLayout & _destLayout, XE::memory_view _destData /* , void * _destData */, const VertexLayout & _srcLayout, XE::memory_view _srcData /* , const void * _srcData */ /* , XE::uint32 _num = 1 */ )
{
	bgfx::vertexConvert( ( const bgfx::VertexLayout & )_destLayout, (void * )_destData.data(), ( const bgfx::VertexLayout & )_srcLayout, (void * )_srcData.data(), _srcData.size() );
}

XE::uint16 XE::Gfx::weldVertices( XE::uint16 * _output, const VertexLayout & _layout, XE::memory_view _data /* , const void * _data */ /* , XE::uint16 _num */, float _epsilon /*= 0.001f */ )
{
	return bgfx::weldVertices( _output, ( const bgfx::VertexLayout & )_layout, _data.data(), _data.size(), _epsilon );
}

XE::uint32 XE::Gfx::topologyConvert( TopologyConvert _conversion, XE::memory_view _dst /* , void * _dst */ /* , XE::uint32 _dstSize */, XE::memory_view _indices /* , const void * _indices */ /* , XE::uint32 _numIndices */, bool _index32 )
{
	return bgfx::topologyConvert( ( bgfx::TopologyConvert::Enum )_conversion, (void * )_dst.data(), _dst.size(), _indices.data(), _indices.size(), _index32 );
}

void XE::Gfx::topologySortTriList( TopologySort _sort, XE::memory_view _dst /* , void * _dst */ /* , XE::uint32 _dstSize */, const XE::Vec3 & _dir, const XE::Vec3 & _pos, XE::memory_view _vertices /* , const void * _vertices */ /* , XE::uint32 _stride */, XE::memory_view _indices /* , const void * _indices */ /* , XE::uint32 _numIndices */, bool _index32 )
{
	bgfx::topologySortTriList( ( bgfx::TopologySort::Enum ) _sort, (void * )_dst.data(), _dst.size(), _dir.d, _pos.d, _vertices.data(), _vertices.size(), _indices.data(), _indices.size(), _index32 );
}

XE::uint8 XE::Gfx::getSupportedRenderers( XE::uint8 _max /*= 0 */, RendererType * _enum /*= NULL */ )
{
	return bgfx::getSupportedRenderers( _max, ( bgfx::RendererType::Enum * )_enum );
}

void XE::Gfx::reset( XE::uint32 _width, XE::uint32 _height, ResetFlags _flags /*= ResetFlags::NONE */, TextureFormat _format /*= TextureFormat::UNKNOWN */ )
{
	bgfx::reset( _width, _height, ( XE::uint32 )_flags, ( bgfx::TextureFormat::Enum )_format );
}

XE::Encoder XE::Gfx::begin( bool _forThread /*= false */ )
{
	XE::Encoder encoder;
	encoder._encoder = bgfx::begin( _forThread );
	return encoder;
}

void XE::Gfx::end( Encoder _encoder )
{
	bgfx::end( ( bgfx::Encoder * ) _encoder._encoder );
}

XE::uint32 XE::Gfx::frame( bool _capture /*= false */ )
{
	return bgfx::frame( _capture );
}

XE::RendererType XE::Gfx::getRendererType()
{
	return ( XE::RendererType )bgfx::getRendererType();
}

const XE::memory_view XE::Gfx::alloc( XE::uint32 _size )
{
	auto mem = bgfx::alloc( _size );
	return { ( std::byte * )mem->data, mem->size };
}

const XE::memory_view XE::Gfx::copy( const void * _data, XE::uint32 _size )
{
	auto mem = bgfx::copy( _data, _size );
	return { ( std::byte * )mem->data, mem->size };
}

const XE::memory_view XE::Gfx::makeRef( XE::memory_view _data /* const void * _data */ /* , XE::uint32 _size */ /* , ReleaseFn _releaseFn = NULL */ )
{
	auto mem = bgfx::makeRef( _data.data(), _data.size() );
	return { ( std::byte * )mem->data, mem->size };
}

void XE::Gfx::setDebug( XE::uint32 _debug )
{
	bgfx::setDebug( _debug );
}

void XE::Gfx::dbgTextClear( XE::uint8 _attr /*= 0 */, bool _small /*= false */ )
{
	bgfx::dbgTextClear( _attr, _small );
}

void XE::Gfx::dbgTextPrintf( XE::uint16 _x, XE::uint16 _y, XE::uint8 _attr, const XE::String & _text )
{
	bgfx::dbgTextPrintf( _x, _y, _attr, _text.ToCString() );
}

void XE::Gfx::dbgTextImage( XE::uint16 _x, XE::uint16 _y, XE::uint16 _width, XE::uint16 _height, XE::memory_view _data /* , const void * _data */, XE::uint16 _pitch )
{
	bgfx::dbgTextImage( _x, _y, _width, _height, _data.data(), _pitch );
}

XE::IndexBufferHandle XE::Gfx::createIndexBuffer( const XE::memory_view _mem, BufferUsage _flags /*= BufferUsage::NONE */ )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	return bgfx::createIndexBuffer( &mem, ( XE::uint16 )_flags ).idx;
}

void XE::Gfx::setName( IndexBufferHandle _handle, const XE::String & _name )
{
	bgfx::setName( HandleCast<bgfx::IndexBufferHandle>( _handle ), _name.ToCString(), _name.Size() );
}

void XE::Gfx::setName( VertexBufferHandle _handle, const XE::String & _name )
{
	bgfx::setName( HandleCast<bgfx::VertexBufferHandle>( _handle ), _name.ToCString(), _name.Size() );
}

void XE::Gfx::setName( ShaderHandle _handle, const XE::String & _name )
{
	bgfx::setName( HandleCast<bgfx::ShaderHandle>( _handle ), _name.ToCString(), _name.Size() );
}

void XE::Gfx::setName( TextureHandle _handle, const XE::String & _name )
{
	bgfx::setName( HandleCast<bgfx::TextureHandle>( _handle ), _name.ToCString(), _name.Size() );
}

void XE::Gfx::setName( FrameBufferHandle _handle, const XE::String & _name )
{
	bgfx::setName( HandleCast<bgfx::FrameBufferHandle>( _handle ), _name.ToCString(), _name.Size() );
}

void XE::Gfx::destroy( IndexBufferHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::IndexBufferHandle>( _handle ) );
}

void XE::Gfx::destroy( VertexLayoutHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::VertexLayoutHandle>( _handle ) );
}

void XE::Gfx::destroy( VertexBufferHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::VertexBufferHandle>( _handle ) );
}

void XE::Gfx::destroy( DynamicIndexBufferHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::DynamicIndexBufferHandle>( _handle ) );
}

void XE::Gfx::destroy( DynamicVertexBufferHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::DynamicVertexBufferHandle>( _handle ) );
}

void XE::Gfx::destroy( IndirectBufferHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::IndirectBufferHandle>( _handle ) );
}

void XE::Gfx::destroy( ShaderHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::ShaderHandle>( _handle ) );
}

void XE::Gfx::destroy( ProgramHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::ProgramHandle>( _handle ) );
}

void XE::Gfx::destroy( TextureHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::TextureHandle>( _handle ) );
}

void XE::Gfx::destroy( FrameBufferHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::FrameBufferHandle>( _handle ) );
}

void XE::Gfx::destroy( UniformHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::UniformHandle>( _handle ) );
}

void XE::Gfx::destroy( OcclusionQueryHandle _handle )
{
	bgfx::destroy( HandleCast<bgfx::OcclusionQueryHandle>( _handle ) );
}

XE::VertexLayoutHandle XE::Gfx::createVertexLayout( const VertexLayout & _layout )
{
	return bgfx::createVertexLayout( ( const bgfx::VertexLayout & )_layout ).idx;
}

XE::VertexBufferHandle XE::Gfx::createVertexBuffer( const XE::memory_view _mem, const VertexLayout & _layout, BufferUsage _flags /*= BufferUsage::NONE */ )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	return bgfx::createVertexBuffer( &mem, ( const bgfx::VertexLayout & )_layout, ( XE::uint16 )_flags ).idx;
}

XE::DynamicIndexBufferHandle XE::Gfx::createDynamicIndexBuffer( XE::uint32 _num, BufferUsage _flags /*= BufferUsage::NONE */ )
{
	return bgfx::createDynamicIndexBuffer( _num, ( XE::uint16 )_flags ).idx;
}

XE::DynamicIndexBufferHandle XE::Gfx::createDynamicIndexBuffer( const XE::memory_view _mem, BufferUsage _flags /*= BufferUsage::NONE */ )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	return bgfx::createDynamicIndexBuffer( &mem, ( XE::uint16 )_flags ).idx;
}

void XE::Gfx::update( DynamicIndexBufferHandle _handle, XE::uint32 _startIndex, const XE::memory_view _mem )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	bgfx::update( HandleCast<bgfx::DynamicIndexBufferHandle>( _handle ), _startIndex, &mem );
}

void XE::Gfx::update( DynamicVertexBufferHandle _handle, XE::uint32 _startVertex, const XE::memory_view _mem )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	bgfx::update( HandleCast<bgfx::DynamicVertexBufferHandle>( _handle ), _startVertex, &mem );
}

XE::DynamicVertexBufferHandle XE::Gfx::createDynamicVertexBuffer( XE::uint32 _num, const VertexLayout & _layout, BufferUsage _flags /*= BufferUsage::NONE */ )
{
	return bgfx::createDynamicVertexBuffer( _num, ( const bgfx::VertexLayout & )_layout, ( XE::uint16 )_flags ).idx;
}

XE::DynamicVertexBufferHandle XE::Gfx::createDynamicVertexBuffer( const XE::memory_view _mem, const VertexLayout & _layout, BufferUsage _flags /*= BufferUsage::NONE */ )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	return bgfx::createDynamicVertexBuffer( &mem, ( const bgfx::VertexLayout & )_layout, ( XE::uint16 )_flags ).idx;
}

XE::uint32 XE::Gfx::getAvailTransientIndexBuffer( XE::uint32 _num )
{
	return bgfx::getAvailTransientIndexBuffer( _num );
}

XE::uint32 XE::Gfx::getAvailTransientVertexBuffer( XE::uint32 _num, const VertexLayout & _layout )
{
	return bgfx::getAvailTransientVertexBuffer( _num, ( const bgfx::VertexLayout & )_layout );
}

XE::uint32 XE::Gfx::getAvailInstanceDataBuffer( XE::uint32 _num, XE::uint16 _stride )
{
	return bgfx::getAvailInstanceDataBuffer( _num, _stride );
}

void XE::Gfx::allocTransientIndexBuffer( TransientIndexBuffer * _tib, XE::uint32 _num )
{
	bgfx::allocTransientIndexBuffer( ( bgfx::TransientIndexBuffer * )_tib, _num );
}

void XE::Gfx::allocTransientVertexBuffer( TransientVertexBuffer * _tvb, XE::uint32 _num, const VertexLayout & _layout )
{
	bgfx::allocTransientVertexBuffer( ( bgfx::TransientVertexBuffer * )_tvb, _num, ( const bgfx::VertexLayout & )_layout );
}

bool XE::Gfx::allocTransientBuffers( TransientVertexBuffer * _tvb, const VertexLayout & _layout, XE::uint32 _numVertices, TransientIndexBuffer * _tib, XE::uint32 _numIndices )
{
	return bgfx::allocTransientBuffers( ( bgfx::TransientVertexBuffer * )_tvb, ( const bgfx::VertexLayout & )_layout, _numVertices, ( bgfx::TransientIndexBuffer * )_tib, _numIndices );
}

void XE::Gfx::allocInstanceDataBuffer( InstanceDataBuffer * _idb, XE::uint32 _num, XE::uint16 _stride )
{
	bgfx::allocInstanceDataBuffer( ( bgfx::InstanceDataBuffer * )_idb, _num, _stride );
}

XE::IndirectBufferHandle XE::Gfx::createIndirectBuffer( XE::uint32 _num )
{
	return bgfx::createIndirectBuffer( _num ).idx;
}

XE::ShaderHandle XE::Gfx::createShader( const XE::memory_view _mem )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	return bgfx::createShader( &mem ).idx;
}

XE::uint16 XE::Gfx::getShaderUniforms( ShaderHandle _handle, UniformHandle * _uniforms /*= NULL */, XE::uint16 _max /*= 0 */ )
{
	bgfx::UniformHandle h;
	auto ret = bgfx::getShaderUniforms( HandleCast<bgfx::ShaderHandle>( _handle ), &h, _max );
	( *_uniforms ) = h.idx;
	return ret;
}

XE::ProgramHandle XE::Gfx::createProgram( ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders /*= false */ )
{
	return bgfx::createProgram( HandleCast<bgfx::ShaderHandle>( _vsh ), HandleCast<bgfx::ShaderHandle>( _fsh ), _destroyShaders ).idx;
}

XE::ProgramHandle XE::Gfx::createProgram( ShaderHandle _csh, bool _destroyShader /*= false */ )
{
	return bgfx::createProgram( HandleCast<bgfx::ShaderHandle>( _csh ), _destroyShader ).idx;
}

bool XE::Gfx::isTextureValid( XE::uint16 _depth, bool _cubeMap, XE::uint16 _numLayers, TextureFormat _format, XE::uint64 _flags )
{
	return bgfx::isTextureValid( _depth, _cubeMap, _numLayers, ( bgfx::TextureFormat::Enum )_format, _flags );
}

void XE::Gfx::calcTextureSize( TextureInfo & _info, XE::uint16 _width, XE::uint16 _height, XE::uint16 _depth, bool _cubeMap, bool _hasMips, XE::uint16 _numLayers, TextureFormat _format )
{
	bgfx::calcTextureSize( ( bgfx::TextureInfo & )_info, _width, _height, _depth, _cubeMap, _hasMips, _numLayers, ( bgfx::TextureFormat::Enum )_format );
}

XE::TextureHandle XE::Gfx::createTexture( const XE::memory_view _mem, TextureUsage _tflags, SamlerFlags _sflags /* , XE::uint64 _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE */, XE::uint8 _skip /*= 0 */, TextureInfo * _info /*= NULL */ )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	return bgfx::createTexture( &mem, ( XE::uint64 )_tflags | ( XE::uint64 )_sflags, _skip, ( bgfx::TextureInfo * ) _info ).idx;
}

XE::TextureHandle XE::Gfx::createTexture2D( XE::uint16 _width, XE::uint16 _height, bool _hasMips, XE::uint16 _numLayers, TextureFormat _format, TextureUsage _tflags, SamlerFlags _sflags /* , XE::uint64 _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE */, const XE::memory_view _mem /*= NULL */ )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	return bgfx::createTexture2D( _width, _height, _hasMips, _numLayers, ( bgfx::TextureFormat::Enum )_format, ( XE::uint64 )_tflags | ( XE::uint64 )_sflags, &mem ).idx;
}

XE::TextureHandle XE::Gfx::createTexture2D( BackbufferRatio _ratio, bool _hasMips, XE::uint16 _numLayers, TextureFormat _format, TextureUsage _tflags, SamlerFlags _sflags /* , XE::uint64 _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE */ )
{
	return bgfx::createTexture2D( ( bgfx::BackbufferRatio::Enum )_ratio, _hasMips, _numLayers, ( bgfx::TextureFormat::Enum )_format, ( XE::uint64 )_tflags | ( XE::uint64 )_sflags ).idx;
}

XE::TextureHandle XE::Gfx::createTexture3D( XE::uint16 _width, XE::uint16 _height, XE::uint16 _depth, bool _hasMips, TextureFormat _format, TextureUsage _tflags, SamlerFlags _sflags /* , XE::uint64 _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE */, const XE::memory_view _mem /*= NULL */ )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	return bgfx::createTexture3D( _width, _height, _depth, _hasMips, ( bgfx::TextureFormat::Enum )_format, ( XE::uint64 )_tflags | ( XE::uint64 )_sflags, &mem ).idx;
}

XE::TextureHandle XE::Gfx::createTextureCube( XE::uint16 _size, bool _hasMips, XE::uint16 _numLayers, TextureFormat _format, TextureUsage _tflags, SamlerFlags _sflags /* , XE::uint64 _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE */, const XE::memory_view _mem /*= NULL */ )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	return bgfx::createTextureCube( _size, _hasMips, _numLayers, ( bgfx::TextureFormat::Enum )_format, ( XE::uint64 )_tflags | ( XE::uint64 )_sflags, &mem ).idx;
}

void XE::Gfx::updateTexture2D( TextureHandle _handle, XE::uint16 _layer, XE::uint8 _mip, XE::uint16 _x, XE::uint16 _y, XE::uint16 _width, XE::uint16 _height, const XE::memory_view _mem, XE::uint16 _pitch /*= UINT16_MAX */ )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	bgfx::updateTexture2D( HandleCast<bgfx::TextureHandle>( _handle ), _layer, _mip, _x, _y, _width, _height, &mem );
}

void XE::Gfx::updateTexture3D( TextureHandle _handle, XE::uint8 _mip, XE::uint16 _x, XE::uint16 _y, XE::uint16 _z, XE::uint16 _width, XE::uint16 _height, XE::uint16 _depth, const XE::memory_view _mem )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	bgfx::updateTexture3D( HandleCast<bgfx::TextureHandle>( _handle ), _mip, _x, _y, _z, _width, _height, _depth, &mem );
}

void XE::Gfx::updateTextureCube( TextureHandle _handle, XE::uint16 _layer, XE::uint8 _side, XE::uint8 _mip, XE::uint16 _x, XE::uint16 _y, XE::uint16 _width, XE::uint16 _height, const XE::memory_view _mem, XE::uint16 _pitch /*= UINT16_MAX */ )
{
	bgfx::Memory mem = { ( XE::uint8 * )_mem.data(), ( XE::uint32 )_mem.size() };
	bgfx::updateTextureCube( HandleCast<bgfx::TextureHandle>( _handle ), _layer, _side, _mip, _x, _y, _width, _height, &mem, _pitch );
}

XE::uint32 XE::Gfx::readTexture( TextureHandle _handle, XE::memory_view _data /* , void * _data */, XE::uint8 _mip /*= 0 */ )
{
	return bgfx::readTexture( HandleCast<bgfx::TextureHandle>( _handle ), (void * )_data.data(), _data.size() );
}

void * XE::Gfx::getDirectAccessPtr( TextureHandle _handle )
{
	return bgfx::getDirectAccessPtr( HandleCast<bgfx::TextureHandle>( _handle ) );
}

XE::FrameBufferHandle XE::Gfx::createFrameBuffer( XE::uint16 _width, XE::uint16 _height, TextureFormat _format, SamlerFlags _textureFlags /*= ( SamlerFlags )( SamlerFlags::U_CLAMP | SamlerFlags::V_CLAMP ) /* , XE::uint64 _textureFlags = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP */ )
{
	return bgfx::createFrameBuffer( _width, _height, ( bgfx::TextureFormat::Enum )_format, ( XE::uint64 )_textureFlags ).idx;
}

XE::FrameBufferHandle XE::Gfx::createFrameBuffer( BackbufferRatio _ratio, TextureFormat _format, SamlerFlags _textureFlags /*= (SamlerFlags )( SamlerFlags::U_CLAMP | SamlerFlags::V_CLAMP ) /* , XE::uint64 _textureFlags = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP */ )
{
	return bgfx::createFrameBuffer( ( bgfx::BackbufferRatio::Enum )_ratio, ( bgfx::TextureFormat::Enum )_format, ( XE::uint64 )_textureFlags ).idx;
}

XE::FrameBufferHandle XE::Gfx::createFrameBuffer( XE::uint8 _num, const TextureHandle * _handles, bool _destroyTextures /*= false */ )
{
	bgfx::TextureHandle h[8];
	for( XE::uint64 i = 0; i < 8; ++i )
	{
		h[i].idx = _handles[i].GetValue();
	}
	return bgfx::createFrameBuffer( _num, h, _destroyTextures ).idx;
}

XE::FrameBufferHandle XE::Gfx::createFrameBuffer( XE::uint8 _num, const Attachment * _attachment, bool _destroyTextures /*= false */ )
{
	return bgfx::createFrameBuffer( _num, ( const bgfx::Attachment * )_attachment, _destroyTextures ).idx;
}

XE::FrameBufferHandle XE::Gfx::createFrameBuffer( WindowHandle _nwh, XE::uint16 _width, XE::uint16 _height, TextureFormat _format /*= TextureFormat::UNKNOWN */, TextureFormat _depthFormat /*= TextureFormat::UNKNOWN */ )
{
	return bgfx::createFrameBuffer( (void * )_nwh.GetValue(), _width, _height, ( bgfx::TextureFormat::Enum )_format, ( bgfx::TextureFormat::Enum )_depthFormat ).idx;
}

XE::TextureHandle XE::Gfx::getTexture( FrameBufferHandle _handle, XE::uint8 _attachment /*= 0 */ )
{
	return bgfx::getTexture( HandleCast<bgfx::FrameBufferHandle>( _handle ), _attachment ).idx;
}

XE::UniformHandle XE::Gfx::createUniform( const XE::String & _name, UniformType _type, XE::uint16 _num /*= 1 */ )
{
	return bgfx::createUniform( _name.ToCString(), ( bgfx::UniformType::Enum ) _type, _num ).idx;
}

void XE::Gfx::getUniformInfo( UniformHandle _handle, UniformInfo & _info )
{
	bgfx::getUniformInfo( HandleCast<bgfx::UniformHandle>( _handle ), ( bgfx::UniformInfo & )_info );
}

XE::OcclusionQueryHandle XE::Gfx::createOcclusionQuery()
{
	return bgfx::createOcclusionQuery().idx;
}

XE::OcclusionQueryResult XE::Gfx::getResult( OcclusionQueryHandle _handle, XE::int32 * _result /*= nullptr */ )
{
	return (OcclusionQueryResult )bgfx::getResult( HandleCast<bgfx::OcclusionQueryHandle>( _handle ), _result );
}

void XE::Gfx::setPaletteColor( XE::uint8 _index, XE::uint32 _rgba )
{
	bgfx::setPaletteColor( _index, _rgba );
}

void XE::Gfx::setPaletteColor( XE::uint8 _index, float _r, float _g, float _b, float _a )
{
	bgfx::setPaletteColor( _index, _r, _g, _b, _a );
}

void XE::Gfx::setPaletteColor( XE::uint8 _index, const XE::FColor & _rgba )
{
	bgfx::setPaletteColor( _index, _rgba.d );
}

void XE::Gfx::setViewName( ViewHandle _view, const XE::String & _name )
{
	bgfx::setViewName( _view.GetValue(), _name.ToCString() );
}

void XE::Gfx::setViewRect( ViewHandle _view, XE::uint16 _x, XE::uint16 _y, XE::uint16 _width, XE::uint16 _height )
{
	bgfx::setViewRect( _view.GetValue(), _x, _y, _width, _height );
}

void XE::Gfx::setViewRect( ViewHandle _view, XE::uint16 _x, XE::uint16 _y, BackbufferRatio _ratio )
{
	bgfx::setViewRect( _view.GetValue(), _x, _y, ( bgfx::BackbufferRatio::Enum )_ratio );
}

void XE::Gfx::setViewScissor( ViewHandle _view, XE::uint16 _x /*= 0 */, XE::uint16 _y /*= 0 */, XE::uint16 _width /*= 0 */, XE::uint16 _height /*= 0 */ )
{
	bgfx::setViewScissor( _view.GetValue(), _x, _y, _width, _height );
}

void XE::Gfx::setViewClear( ViewHandle _view, ClearFlags _falgs /* , XE::uint16 _flags */, XE::uint32 _rgba /*= 0x000000ff */, float _depth /*= 1.0f */, XE::uint8 _stencil /*= 0 */ )
{
	bgfx::setViewClear( _view.GetValue(), ( XE::uint16 )_falgs, _rgba, _depth, _stencil );
}

void XE::Gfx::setViewClear( ViewHandle _view, ClearFlags _falgs /* , XE::uint16 _flags */, float _depth, XE::uint8 _stencil, XE::uint8 _0 /*= UINT8_MAX */, XE::uint8 _1 /*= UINT8_MAX */, XE::uint8 _2 /*= UINT8_MAX */, XE::uint8 _3 /*= UINT8_MAX */, XE::uint8 _4 /*= UINT8_MAX */, XE::uint8 _5 /*= UINT8_MAX */, XE::uint8 _6 /*= UINT8_MAX */, XE::uint8 _7 /*= UINT8_MAX */ )
{
	bgfx::setViewClear( _view.GetValue(), ( XE::uint16 )_falgs, _depth, _stencil, _0, _1, _2, _3, _4, _5, _6, _7 );
}

void XE::Gfx::setViewMode( ViewHandle _view, ViewMode _mode /*= ViewMode::DEFAULT */ )
{
	bgfx::setViewMode( _view.GetValue(), ( bgfx::ViewMode::Enum )_mode );
}

void XE::Gfx::setViewFrameBuffer( ViewHandle _view, FrameBufferHandle _handle )
{
	bgfx::setViewFrameBuffer( _view.GetValue(), HandleCast<bgfx::FrameBufferHandle>( _handle ) );
}

void XE::Gfx::setViewTransform( ViewHandle _handle, const Mat4 & _view, const Mat4 & _proj /* , const void * _view */ /* , const void * _proj */ )
{
	bgfx::setViewTransform( _handle.GetValue(), _view.d, _proj.d );
}

void XE::Gfx::setViewOrder( ViewHandle _view, XE::basic_memory_view<ViewHandle> _remap /* , XE::uint16 _num = UINT16_MAX */ /* , const ViewId * _remap = NULL */ )
{
	bgfx::setViewOrder( _view.GetValue(), _remap.size(), ( const bgfx::ViewId * )_remap.data() );
}

void XE::Gfx::resetView( ViewHandle _view )
{
	bgfx::resetView( _view.GetValue() );
}

void XE::Gfx::setMarker( const XE::String & _marker )
{
	bgfx::setMarker( _marker.ToCString() );
}

void XE::Gfx::setState( XE::uint64 _state, XE::uint32 _rgba /*= 0 */ )
{
	bgfx::setState( _state, _rgba );
}

void XE::Gfx::setCondition( OcclusionQueryHandle _handle, bool _visible )
{
	bgfx::setCondition( HandleCast<bgfx::OcclusionQueryHandle>( _handle ), _visible );
}

void XE::Gfx::setStencil( XE::uint32 _fstencil, StencilFlags _bstencil /*= StencilFlags::NONE */ )
{
	bgfx::setStencil( _fstencil, ( XE::uint32 )_bstencil );
}

XE::uint16 XE::Gfx::setScissor( XE::uint16 _x, XE::uint16 _y, XE::uint16 _width, XE::uint16 _height )
{
	return bgfx::setScissor( _x, _y, _width, _height );
}

void XE::Gfx::setScissor( XE::uint16 _cache /*= UINT16_MAX */ )
{
	bgfx::setScissor( _cache );
}

XE::uint32 XE::Gfx::setTransform( XE::basic_memory_view<Mat4> _mtx /* const void * _mtx */ /* , XE::uint16 _num = 1 */ )
{
	return bgfx::setTransform( _mtx.data(), _mtx.size() );
}

void XE::Gfx::setTransform( XE::uint32 _cache, XE::uint16 _num /*= 1 */ )
{
	bgfx::setTransform( _cache, _num );
}

XE::uint32 XE::Gfx::allocTransform( XE::basic_memory_view<Mat4> _transform /* Transform * _transform */ /* , XE::uint16 _num */ )
{
	return bgfx::allocTransform( ( bgfx::Transform * )_transform.data(), _transform.size() );
}

void XE::Gfx::setUniform( UniformHandle _handle, XE::memory_view _value /* , const void * _value */ /* , XE::uint16 _num = 1 */ )
{
	bgfx::setUniform( HandleCast<bgfx::UniformHandle>( _handle ), _value.data(), _value.size() );
}

void XE::Gfx::setIndexBuffer( IndexBufferHandle _handle )
{
	bgfx::setIndexBuffer( HandleCast<bgfx::IndexBufferHandle>( _handle ) );
}

void XE::Gfx::setIndexBuffer( IndexBufferHandle _handle, XE::uint32 _firstIndex, XE::uint32 _numIndices )
{
	bgfx::setIndexBuffer( HandleCast<bgfx::IndexBufferHandle>( _handle ), _firstIndex, _numIndices );
}

void XE::Gfx::setIndexBuffer( DynamicIndexBufferHandle _handle )
{
	bgfx::setIndexBuffer( HandleCast<bgfx::DynamicIndexBufferHandle>( _handle ) );
}

void XE::Gfx::setIndexBuffer( DynamicIndexBufferHandle _handle, XE::uint32 _firstIndex, XE::uint32 _numIndices )
{
	bgfx::setIndexBuffer( HandleCast<bgfx::DynamicIndexBufferHandle>( _handle ), _firstIndex, _numIndices );
}

void XE::Gfx::setIndexBuffer( const TransientIndexBuffer * _tib )
{
	bgfx::setIndexBuffer( ( const bgfx::TransientIndexBuffer * )_tib );
}

void XE::Gfx::setIndexBuffer( const TransientIndexBuffer * _tib, XE::uint32 _firstIndex, XE::uint32 _numIndices )
{
	bgfx::setIndexBuffer( ( const bgfx::TransientIndexBuffer * )_tib, _firstIndex, _numIndices );
}

void XE::Gfx::setVertexBuffer( XE::uint8 _stream, VertexBufferHandle _handle )
{
	bgfx::setVertexBuffer( _stream, HandleCast<bgfx::VertexBufferHandle>( _handle ) );
}

void XE::Gfx::setVertexBuffer( uint8 _stream, VertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle /*= VertexLayoutHandle() */ )
{
	bgfx::setVertexBuffer( _stream, HandleCast<bgfx::VertexBufferHandle>( _handle ), _startVertex, _numVertices, HandleCast<bgfx::VertexLayoutHandle>( _layoutHandle ) );
}

void XE::Gfx::setVertexBuffer( XE::uint8 _stream, DynamicVertexBufferHandle _handle )
{
	bgfx::setVertexBuffer( _stream, HandleCast<bgfx::DynamicVertexBufferHandle>( _handle ) );
}

void XE::Gfx::setVertexBuffer( uint8 _stream, DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle /*= VertexLayoutHandle() */ )
{
	bgfx::setVertexBuffer( _stream, HandleCast<bgfx::DynamicVertexBufferHandle>( _handle ), _startVertex, _numVertices, HandleCast<bgfx::VertexLayoutHandle>( _layoutHandle ) );
}

void XE::Gfx::setVertexBuffer( XE::uint8 _stream, const TransientVertexBuffer * _tvb )
{
	bgfx::setVertexBuffer( _stream, ( const bgfx::TransientVertexBuffer * )_tvb );
}

void XE::Gfx::setVertexBuffer( uint8 _stream, const TransientVertexBuffer * _tvb, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle /*= VertexLayoutHandle() */ )
{
	bgfx::setVertexBuffer( _stream, ( const bgfx::TransientVertexBuffer * )_tvb, _startVertex, _numVertices, HandleCast<bgfx::VertexLayoutHandle>( _layoutHandle ) );
}

void XE::Gfx::setVertexCount( XE::uint32 _numVertices )
{
	bgfx::setVertexCount( _numVertices );
}

void XE::Gfx::setInstanceDataBuffer( const InstanceDataBuffer * _idb )
{
	bgfx::setInstanceDataBuffer( ( const bgfx::InstanceDataBuffer * )_idb );
}

void XE::Gfx::setInstanceDataBuffer( const InstanceDataBuffer * _idb, XE::uint32 _start, XE::uint32 _num )
{
	bgfx::setInstanceDataBuffer( ( const bgfx::InstanceDataBuffer * )_idb, _start, _num );
}

void XE::Gfx::setInstanceDataBuffer( VertexBufferHandle _handle, XE::uint32 _start, XE::uint32 _num )
{
	bgfx::setInstanceDataBuffer( HandleCast<bgfx::VertexBufferHandle>( _handle ), _start, _num );
}

void XE::Gfx::setInstanceDataBuffer( DynamicVertexBufferHandle _handle, XE::uint32 _start, XE::uint32 _num )
{
	bgfx::setInstanceDataBuffer( HandleCast<bgfx::DynamicVertexBufferHandle>( _handle ), _start, _num );
}

void XE::Gfx::setInstanceCount( XE::uint32 _numInstances )
{
	bgfx::setInstanceCount( _numInstances );
}

void XE::Gfx::setTexture( XE::uint8 _stage, UniformHandle _sampler, TextureHandle _handle, XE::uint32 _flags /*= UINT32_MAX */ )
{
	bgfx::setTexture( _stage, HandleCast<bgfx::UniformHandle>( _sampler ), HandleCast<bgfx::TextureHandle>( _handle ), _flags );
}

void XE::Gfx::touch( ViewHandle _view )
{
	bgfx::touch( _view.GetValue() );
}

void XE::Gfx::submit( ViewHandle _view, ProgramHandle _program, XE::uint32 _depth /*= 0 */, bool _preserveState /*= false */ )
{
	bgfx::submit( _view.GetValue(), HandleCast<bgfx::ProgramHandle>( _program ), _depth, _preserveState );
}

void XE::Gfx::submit( ViewHandle _view, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, XE::uint32 _depth /*= 0 */, bool _preserveState /*= false */ )
{
	bgfx::submit( _view.GetValue(), HandleCast<bgfx::ProgramHandle>( _program ), HandleCast<bgfx::OcclusionQueryHandle>( _occlusionQuery ), _depth, _preserveState );
}

void XE::Gfx::submit( ViewHandle _view, ProgramHandle _program, IndirectBufferHandle _indirectHandle, XE::uint16 _start /*= 0 */, XE::uint16 _num /*= 1 */, XE::uint32 _depth /*= 0 */, bool _preserveState /*= false */ )
{
	bgfx::submit( _view.GetValue(), HandleCast<bgfx::ProgramHandle>( _program ), HandleCast<bgfx::IndirectBufferHandle>( _indirectHandle ), _start, _num, _depth, _preserveState );
}

void XE::Gfx::setBuffer( XE::uint8 _stage, IndexBufferHandle _handle, Access _access )
{
	bgfx::setBuffer( _stage, HandleCast<bgfx::IndexBufferHandle>( _handle ), ( bgfx::Access::Enum )_access );
}

void XE::Gfx::setBuffer( XE::uint8 _stage, VertexBufferHandle _handle, Access _access )
{
	bgfx::setBuffer( _stage, HandleCast<bgfx::VertexBufferHandle>( _handle ), ( bgfx::Access::Enum )_access );
}

void XE::Gfx::setBuffer( XE::uint8 _stage, DynamicIndexBufferHandle _handle, Access _access )
{
	bgfx::setBuffer( _stage, HandleCast<bgfx::DynamicIndexBufferHandle>( _handle ), ( bgfx::Access::Enum )_access );
}

void XE::Gfx::setBuffer( XE::uint8 _stage, DynamicVertexBufferHandle _handle, Access _access )
{
	bgfx::setBuffer( _stage, HandleCast<bgfx::DynamicVertexBufferHandle>( _handle ), ( bgfx::Access::Enum )_access );
}

void XE::Gfx::setBuffer( XE::uint8 _stage, IndirectBufferHandle _handle, Access _access )
{
	bgfx::setBuffer( _stage, HandleCast<bgfx::IndirectBufferHandle>( _handle ), ( bgfx::Access::Enum )_access );
}

void XE::Gfx::setImage( XE::uint8 _stage, TextureHandle _handle, XE::uint8 _mip, Access _access, TextureFormat _format /*= TextureFormat::UNKNOWN */ )
{
	bgfx::setImage( _stage, HandleCast<bgfx::TextureHandle>( _handle ), _mip, ( bgfx::Access::Enum )_access, ( bgfx::TextureFormat::Enum )_format );
}

void XE::Gfx::dispatch( ViewHandle _view, ProgramHandle _handle, XE::uint32 _numX /*= 1 */, XE::uint32 _numY /*= 1 */, XE::uint32 _numZ /*= 1 */ )
{
	bgfx::dispatch( _view.GetValue(), HandleCast<bgfx::ProgramHandle>( _handle ), _numX, _numY, _numZ );
}

void XE::Gfx::dispatch( ViewHandle _view, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, XE::uint16 _start /*= 0 */, XE::uint16 _num /*= 1 */ )
{
	bgfx::dispatch( _view.GetValue(), HandleCast<bgfx::ProgramHandle>( _handle ), HandleCast<bgfx::IndirectBufferHandle>( _indirectHandle ), _start, _num );
}

void XE::Gfx::discard()
{
	bgfx::discard();
}

void XE::Gfx::blit( ViewHandle _view, TextureHandle _dst, XE::uint16 _dstX, XE::uint16 _dstY, TextureHandle _src, XE::uint16 _srcX /*= 0 */, XE::uint16 _srcY /*= 0 */, XE::uint16 _width /*= UINT16_MAX */, XE::uint16 _height /*= UINT16_MAX */ )
{
	bgfx::blit( _view.GetValue(), HandleCast<bgfx::TextureHandle>( _dst ), _dstX, _dstY, HandleCast<bgfx::TextureHandle>( _src ), _srcX, _srcY, _width, _height );
}

void XE::Gfx::blit( ViewHandle _view, TextureHandle _dst, XE::uint8 _dstMip, XE::uint16 _dstX, XE::uint16 _dstY, XE::uint16 _dstZ, TextureHandle _src, XE::uint8 _srcMip /*= 0 */, XE::uint16 _srcX /*= 0 */, XE::uint16 _srcY /*= 0 */, XE::uint16 _srcZ /*= 0 */, XE::uint16 _width /*= UINT16_MAX */, XE::uint16 _height /*= UINT16_MAX */, XE::uint16 _depth /*= UINT16_MAX */ )
{
	bgfx::blit( _view.GetValue(), HandleCast<bgfx::TextureHandle>( _dst ), _dstMip, _dstX, _dstY, _dstZ, HandleCast<bgfx::TextureHandle>( _src ), _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth );
}

void XE::Gfx::requestScreenShot( FrameBufferHandle _handle, const XE::String & _filePath )
{
	bgfx::requestScreenShot( HandleCast<bgfx::FrameBufferHandle>( _handle ), _filePath.ToCString() );
}
