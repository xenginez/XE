#include "Type.h"

USING_XE
/*
BEG_META( StateWrite )
type->Value( "R", StateWrite::R );
type->Value( "G", StateWrite::G );
type->Value( "B", StateWrite::B );
type->Value( "A", StateWrite::A );
type->Value( "Z", StateWrite::Z );
type->Value( "RGB", StateWrite::RGB );
END_META()

BEG_META( StateDepthTest )
type->Value( "LESS", StateDepthTest::LESS );
type->Value( "LEQUAL", StateDepthTest::LEQUAL );
type->Value( "EQUAL", StateDepthTest::EQUAL );
type->Value( "GEQUAL", StateDepthTest::GEQUAL );
type->Value( "GREATER", StateDepthTest::GREATER );
type->Value( "NOTEQUAL", StateDepthTest::NOTEQUAL );
type->Value( "NEVER", StateDepthTest::NEVER );
type->Value( "ALWAYS", StateDepthTest::ALWAYS );
END_META()

BEG_META( StateBlendFunc )
type->Value( "ZERO", StateBlendFunc::ZERO );
type->Value( "ONE", StateBlendFunc::ONE );
type->Value( "SRC_COLOR", StateBlendFunc::SRC_COLOR );
type->Value( "INV_SRC_COLOR", StateBlendFunc::INV_SRC_COLOR );
type->Value( "SRC_ALPHA", StateBlendFunc::SRC_ALPHA );
type->Value( "INV_SRC_ALPHA", StateBlendFunc::INV_SRC_ALPHA );
type->Value( "DST_ALPHA", StateBlendFunc::DST_ALPHA );
type->Value( "INV_DST_ALPHA", StateBlendFunc::INV_DST_ALPHA );
type->Value( "DST_COLOR", StateBlendFunc::DST_COLOR );
type->Value( "INV_DST_COLOR", StateBlendFunc::INV_DST_COLOR );
type->Value( "SRC_ALPHA_SAT", StateBlendFunc::SRC_ALPHA_SAT );
type->Value( "FACTOR", StateBlendFunc::FACTOR );
type->Value( "INV_FACTOR", StateBlendFunc::INV_FACTOR );
END_META()

BEG_META( StateBlendEquation )
type->Value( "ADD", StateBlendEquation::ADD );
type->Value( "SUB", StateBlendEquation::SUB );
type->Value( "REVSUB", StateBlendEquation::REVSUB );
type->Value( "MIN", StateBlendEquation::MIN );
type->Value( "MAX", StateBlendEquation::MAX );
END_META()

BEG_META( StateCull )
type->Value( "CW", StateCull::CW );
type->Value( "CCW", StateCull::CCW );
END_META()

BEG_META( StateTopologyType )
type->Value( "TRISTRIP", StateTopologyType::TRISTRIP );
type->Value( "LINES", StateTopologyType::LINES );
type->Value( "LINESTRIP", StateTopologyType::LINESTRIP );
type->Value( "POINTS", StateTopologyType::POINTS );
END_META()

BEG_META( StateMSAA )
type->Value( "MSAA ", StateMSAA::MSAA );
type->Value( "LINEAA", StateMSAA::LINEAA );
type->Value( "CONSERVATIVE_RASTER", StateMSAA::CONSERVATIVE_RASTER );
type->Value( "NONE ", StateMSAA::NONE );
type->Value( "BLEND_INDEPENDENT", StateMSAA::BLEND_INDEPENDENT );
type->Value( "BLEND_ALPHA_TO_COVERAGE", StateMSAA::BLEND_ALPHA_TO_COVERAGE );
END_META()

BEG_META( StencilFlags )
type->Value( "NONE", StencilFlags::NONE );
type->Value( "TEST_LESS", StencilFlags::TEST_LESS );
type->Value( "TEST_LEQUAL", StencilFlags::TEST_LEQUAL );
type->Value( "TEST_EQUAL", StencilFlags::TEST_EQUAL );
type->Value( "TEST_GEQUAL", StencilFlags::TEST_GEQUAL );
type->Value( "TEST_GREATER", StencilFlags::TEST_GREATER );
type->Value( "TEST_NOTEQUAL", StencilFlags::TEST_NOTEQUAL );
type->Value( "TEST_NEVER", StencilFlags::TEST_NEVER );
type->Value( "TEST_ALWAYS", StencilFlags::TEST_ALWAYS );
type->Value( "FAIL_S_ZERO", StencilFlags::FAIL_S_ZERO );
type->Value( "FAIL_S_KEEP", StencilFlags::FAIL_S_KEEP );
type->Value( "FAIL_S_REPLACE", StencilFlags::FAIL_S_REPLACE );
type->Value( "FAIL_S_INCR", StencilFlags::FAIL_S_INCR );
type->Value( "FAIL_S_INCRSAT", StencilFlags::FAIL_S_INCRSAT );
type->Value( "FAIL_S_DECR", StencilFlags::FAIL_S_DECR );
type->Value( "FAIL_S_DECRSAT", StencilFlags::FAIL_S_DECRSAT );
type->Value( "FAIL_S_INVERT", StencilFlags::FAIL_S_INVERT );
type->Value( "FAIL_Z_ZERO", StencilFlags::FAIL_Z_ZERO );
type->Value( "FAIL_Z_KEEP", StencilFlags::FAIL_Z_KEEP );
type->Value( "FAIL_Z_REPLACE", StencilFlags::FAIL_Z_REPLACE );
type->Value( "FAIL_Z_INCR", StencilFlags::FAIL_Z_INCR );
type->Value( "FAIL_Z_INCRSAT", StencilFlags::FAIL_Z_INCRSAT );
type->Value( "FAIL_Z_DECR", StencilFlags::FAIL_Z_DECR );
type->Value( "FAIL_Z_DECRSAT", StencilFlags::FAIL_Z_DECRSAT );
type->Value( "FAIL_Z_INVERT", StencilFlags::FAIL_Z_INVERT );
type->Value( "PASS_Z_ZERO", StencilFlags::PASS_Z_ZERO );
type->Value( "PASS_Z_KEEP", StencilFlags::PASS_Z_KEEP );
type->Value( "PASS_Z_REPLACE", StencilFlags::PASS_Z_REPLACE );
type->Value( "PASS_Z_INCR", StencilFlags::PASS_Z_INCR );
type->Value( "PASS_Z_INCRSAT", StencilFlags::PASS_Z_INCRSAT );
type->Value( "PASS_Z_DECR", StencilFlags::PASS_Z_DECR );
type->Value( "PASS_Z_DECRSAT", StencilFlags::PASS_Z_DECRSAT );
type->Value( "PASS_Z_INVERT", StencilFlags::PASS_Z_INVERT );
END_META()

BEG_META( ClearFlags )
type->Value( "NONE", ClearFlags::NONE );
type->Value( "COLOR", ClearFlags::COLOR );
type->Value( "DEPTH", ClearFlags::DEPTH );
type->Value( "STENCIL", ClearFlags::STENCIL );
type->Value( "COLOR_DEPTH", ClearFlags::COLOR_DEPTH );
type->Value( "DEPTH_STENCIL", ClearFlags::DEPTH_STENCIL );
type->Value( "COLOR_STENCIL", ClearFlags::COLOR_STENCIL );
type->Value( "COLOR_DEPTH_STENCIL", ClearFlags::COLOR_DEPTH_STENCIL );
type->Value( "DISCARD_COLOR_0", ClearFlags::DISCARD_COLOR_0 );
type->Value( "DISCARD_COLOR_1", ClearFlags::DISCARD_COLOR_1 );
type->Value( "DISCARD_COLOR_2", ClearFlags::DISCARD_COLOR_2 );
type->Value( "DISCARD_COLOR_3", ClearFlags::DISCARD_COLOR_3 );
type->Value( "DISCARD_COLOR_4", ClearFlags::DISCARD_COLOR_4 );
type->Value( "DISCARD_COLOR_5", ClearFlags::DISCARD_COLOR_5 );
type->Value( "DISCARD_COLOR_6", ClearFlags::DISCARD_COLOR_6 );
type->Value( "DISCARD_COLOR_7", ClearFlags::DISCARD_COLOR_7 );
type->Value( "DISCARD_DEPTH", ClearFlags::DISCARD_DEPTH );
type->Value( "DISCARD_STENCIL", ClearFlags::DISCARD_STENCIL );
END_META()

BEG_META( DebugFlags )
type->Value( "NONE", DebugFlags::NONE );
type->Value( "WIREFRAME", DebugFlags::WIREFRAME );
type->Value( "IFH", DebugFlags::IFH );
type->Value( "STATS", DebugFlags::STATS );
type->Value( "TEXT", DebugFlags::TEXT );
type->Value( "PROFILER ", DebugFlags::PROFILER );
END_META()

BEG_META( ComputeFormat )
type->Value( "I8X1", ComputeFormat::I8X1 );
type->Value( "I8X2", ComputeFormat::I8X2 );
type->Value( "I8X4", ComputeFormat::I8X4 );
type->Value( "I16X1", ComputeFormat::I16X1 );
type->Value( "I16X2", ComputeFormat::I16X2 );
type->Value( "I16X4", ComputeFormat::I16X4 );
type->Value( "I32X1", ComputeFormat::I32X1 );
type->Value( "I32X2", ComputeFormat::I32X2 );
type->Value( "I32X4", ComputeFormat::I32X4 );
type->Value( "U8X1", ComputeFormat::U8X1 );
type->Value( "U8X2", ComputeFormat::U8X2 );
type->Value( "U8X4", ComputeFormat::U8X4 );
type->Value( "U16X1", ComputeFormat::U16X1 );
type->Value( "U16X2", ComputeFormat::U16X2 );
type->Value( "U16X4", ComputeFormat::U16X4 );
type->Value( "U32X1", ComputeFormat::U32X1 );
type->Value( "U32X2", ComputeFormat::U32X2 );
type->Value( "U32X4", ComputeFormat::U32X4 );
type->Value( "F8X1", ComputeFormat::F8X1 );
type->Value( "F8X2", ComputeFormat::F8X2 );
type->Value( "F8X4", ComputeFormat::F8X4 );
type->Value( "F16X1", ComputeFormat::F16X1 );
type->Value( "F16X2", ComputeFormat::F16X2 );
type->Value( "F16X4", ComputeFormat::F16X4 );
type->Value( "F32X1", ComputeFormat::F32X1 );
type->Value( "F32X2", ComputeFormat::F32X2 );
type->Value( "F32X4", ComputeFormat::F32X4 );
END_META()

BEG_META( BufferUsage )
type->Value( "NONE", BufferUsage::NONE );
type->Value( "COMPUTE_READ ", BufferUsage::COMPUTE_READ );
type->Value( "COMPUTE_WRITE", BufferUsage::COMPUTE_WRITE );
type->Value( "DRAW_INDIRECT", BufferUsage::DRAW_INDIRECT );
type->Value( "ALLOW_RESIZE ", BufferUsage::ALLOW_RESIZE );
type->Value( "INDEX32", BufferUsage::INDEX32 );
type->Value( "COMPUTE_READ_WRITE", BufferUsage::COMPUTE_READ_WRITE );
END_META()

BEG_META( TextureUsage )
type->Value( "NONE", TextureUsage::NONE );
type->Value( "MSAA_SAMPLE", TextureUsage::MSAA_SAMPLE );
type->Value( "RT", TextureUsage::RT );
type->Value( "COMPUTE_WRITE", TextureUsage::COMPUTE_WRITE );
type->Value( "SRGB", TextureUsage::SRGB );
type->Value( "BLIT_DST", TextureUsage::BLIT_DST );
type->Value( "READ_BACK", TextureUsage::READ_BACK );
END_META()

BEG_META( RenderTargetMSAA )
type->Value( "X2", RenderTargetMSAA::X2 );
type->Value( "X4", RenderTargetMSAA::X4 );
type->Value( "X8", RenderTargetMSAA::X8 );
type->Value( "X16", RenderTargetMSAA::X16 );
type->Value( "WRITE_ONLY", RenderTargetMSAA::WRITE_ONLY );
END_META()

BEG_META( SampleFlags )
type->Value( "U_MIRROR", SampleFlags::U_MIRROR );
type->Value( "U_CLAMP", SampleFlags::U_CLAMP );
type->Value( "U_BORDER", SampleFlags::U_BORDER );
type->Value( "V_MIRROR", SampleFlags::V_MIRROR );
type->Value( "V_CLAMP ", SampleFlags::V_CLAMP );
type->Value( "V_BORDER", SampleFlags::V_BORDER );
type->Value( "W_MIRROR", SampleFlags::W_MIRROR );
type->Value( "W_CLAMP", SampleFlags::W_CLAMP );
type->Value( "W_BORDER", SampleFlags::W_BORDER );
type->Value( "MIN_POINT", SampleFlags::MIN_POINT );
type->Value( "MIN_ANISOT", SampleFlags::MIN_ANISOTROPIC );
type->Value( "MAG_POINT", SampleFlags::MAG_POINT );
type->Value( "MAG_ANISOT", SampleFlags::MAG_ANISOTROPIC );
type->Value( "MIP_POINT", SampleFlags::MIP_POINT );
type->Value( "POINTS", SampleFlags::POINTS );
type->Value( "UV_MIRROR", SampleFlags::UV_MIRROR );
type->Value( "UV_CLAMP", SampleFlags::UV_CLAMP );
type->Value( "UV_BORDER", SampleFlags::UV_BORDER );
type->Value( "UVW_MIRROR", SampleFlags::UVW_MIRROR );
type->Value( "UVW_CLAMP", SampleFlags::UVW_CLAMP );
type->Value( "UVW_BORDER", SampleFlags::UVW_BORDER );
type->Value( "LESS", SampleFlags::LESS );
type->Value( "LEQUAL", SampleFlags::LEQUAL );
type->Value( "EQUAL", SampleFlags::EQUAL );
type->Value( "GEQUAL", SampleFlags::GEQUAL );
type->Value( "GREATER", SampleFlags::GREATER );
type->Value( "NOTEQUAL", SampleFlags::NOTEQUAL );
type->Value( "NEVER", SampleFlags::NEVER );
type->Value( "ALWAYS", SampleFlags::ALWAYS );
END_META()

BEG_META( ResetFlags )
type->Value( "MSAAX2", ResetFlags::MSAAX2 );
type->Value( "MSAAX4", ResetFlags::MSAAX4 );
type->Value( "MSAAX8", ResetFlags::MSAAX8 );
type->Value( "MSAAX16", ResetFlags::MSAAX16 );
type->Value( "NONE ", ResetFlags::NONE );
type->Value( "FULLSCREEN", ResetFlags::FULLSCREEN );
type->Value( "VSYNC", ResetFlags::VSYNC );
type->Value( "MAXANISOTROPY", ResetFlags::MAXANISOTROPY );
type->Value( "CAPTURE", ResetFlags::CAPTURE );
type->Value( "FLUSH_AFTER_RENDER", ResetFlags::FLUSH_AFTER_RENDER );
type->Value( "FLIP_AFTER_RENDER", ResetFlags::FLIP_AFTER_RENDER );
type->Value( "SRGB_BACKBUFFER", ResetFlags::SRGB_BACKBUFFER );
type->Value( "HDR10", ResetFlags::HDR10 );
type->Value( "HIDPI", ResetFlags::HIDPI );
type->Value( "DEPTH_CLAMP", ResetFlags::DEPTH_CLAMP );
type->Value( "SUSPEND", ResetFlags::SUSPEND );
END_META()

BEG_META( CapsFlags )
type->Value( "ALPHA_TO_COVERAGE", CapsFlags::ALPHA_TO_COVERAGE );
type->Value( "BLEND_INDEPENDENT", CapsFlags::BLEND_INDEPENDENT );
type->Value( "COMPUTE", CapsFlags::COMPUTE );
type->Value( "CONSERVATIVE_RASTER", CapsFlags::CONSERVATIVE_RASTER );
type->Value( "DRAW_INDIRECT", CapsFlags::DRAW_INDIRECT );
type->Value( "FRAGMENT_DEPTH", CapsFlags::FRAGMENT_DEPTH );
type->Value( "FRAGMENT_ORDERING", CapsFlags::FRAGMENT_ORDERING );
type->Value( "FRAMEBUFFER_RW", CapsFlags::FRAMEBUFFER_RW );
type->Value( "GRAPHICS_DEBUGGER", CapsFlags::GRAPHICS_DEBUGGER );
type->Value( "RESERVED", CapsFlags::RESERVED );
type->Value( "HDR10", CapsFlags::HDR10 );
type->Value( "HIDPI", CapsFlags::HIDPI );
type->Value( "INDEX32", CapsFlags::INDEX32 );
type->Value( "INSTANCING", CapsFlags::INSTANCING );
type->Value( "OCCLUSION_QUERY", CapsFlags::OCCLUSION_QUERY );
type->Value( "RENDERER_MULTITHREADED", CapsFlags::RENDERER_MULTITHREADED );
type->Value( "SWAP_CHAIN", CapsFlags::SWAP_CHAIN );
type->Value( "TEXTURE_2D_ARRAY", CapsFlags::TEXTURE_2D_ARRAY );
type->Value( "TEXTURE_3D", CapsFlags::TEXTURE_3D );
type->Value( "TEXTURE_BLIT", CapsFlags::TEXTURE_BLIT );
type->Value( "TEXTURE_COMPARE_RESERVED", CapsFlags::TEXTURE_COMPARE_RESERVED );
type->Value( "TEXTURE_COMPARE_LEQUAL", CapsFlags::TEXTURE_COMPARE_LEQUAL );
type->Value( "TEXTURE_CUBE_ARRAY", CapsFlags::TEXTURE_CUBE_ARRAY );
type->Value( "TEXTURE_DIRECT_ACCESS", CapsFlags::TEXTURE_DIRECT_ACCESS );
type->Value( "TEXTURE_READ_BACK", CapsFlags::TEXTURE_READ_BACK );
type->Value( "VERTEX_ATTRIB_HALF", CapsFlags::VERTEX_ATTRIB_HALF );
type->Value( "VERTEX_ATTRIB_UINT10", CapsFlags::VERTEX_ATTRIB_UINT10 );
type->Value( "VERTEX_ID", CapsFlags::VERTEX_ID );
type->Value( "TEXTURE_COMPARE_ALL", CapsFlags::TEXTURE_COMPARE_ALL );
END_META()

BEG_META( CapsFormat )
type->Value( "TEXTURE_NONE", CapsFormat::TEXTURE_NONE );
type->Value( "TEXTURE_2D", CapsFormat::TEXTURE_2D );
type->Value( "TEXTURE_2D_SRGB", CapsFormat::TEXTURE_2D_SRGB );
type->Value( "TEXTURE_2D_EMULATED", CapsFormat::TEXTURE_2D_EMULATED );
type->Value( "TEXTURE_3D", CapsFormat::TEXTURE_3D );
type->Value( "TEXTURE_3D_SRGB", CapsFormat::TEXTURE_3D_SRGB );
type->Value( "TEXTURE_3D_EMULATED", CapsFormat::TEXTURE_3D_EMULATED );
type->Value( "TEXTURE_CUBE", CapsFormat::TEXTURE_CUBE );
type->Value( "TEXTURE_CUBE_SRGB", CapsFormat::TEXTURE_CUBE_SRGB );
type->Value( "TEXTURE_CUBE_EMULATE", CapsFormat::TEXTURE_CUBE_EMULATED );
type->Value( "TEXTURE_VERTEX", CapsFormat::TEXTURE_VERTEX );
type->Value( "TEXTURE_IMAGE", CapsFormat::TEXTURE_IMAGE );
type->Value( "TEXTURE_FRAMEBUFFER ", CapsFormat::TEXTURE_FRAMEBUFFER );
type->Value( "TEXTURE_FRAMEBUFFER_MSAA", CapsFormat::TEXTURE_FRAMEBUFFER_MSAA );
type->Value( "TEXTURE_MSAA", CapsFormat::TEXTURE_MSAA );
type->Value( "TEXTURE_MIP_AUTOGEN", CapsFormat::TEXTURE_MIP_AUTOGEN );
END_META()

BEG_META( PCIType )
type->Value( "NONE", PCIType::NONE );
type->Value( "SOFTWARE", PCIType::SOFTWARE );
type->Value( "AMD", PCIType::AMD );
type->Value( "INTEL", PCIType::INTEL );
type->Value( "NVIDIA", PCIType::NVIDIA );
END_META()

BEG_META( CubeMap )
type->Value( "POSITIVE_X", CubeMap::POSITIVE_X );
type->Value( "NEGATIVE_X", CubeMap::NEGATIVE_X );
type->Value( "POSITIVE_Y", CubeMap::POSITIVE_Y );
type->Value( "NEGATIVE_Y", CubeMap::NEGATIVE_Y );
type->Value( "POSITIVE_Z", CubeMap::POSITIVE_Z );
type->Value( "NEGATIVE_Z", CubeMap::NEGATIVE_Z );
END_META()

BEG_META( Fatal )
type->Value( "DEBUG_CHECK", Fatal::DEBUG_CHECK );
type->Value( "INVALID_SHADER", Fatal::INVALID_SHADER );
type->Value( "UNABLE_TO_INITIALIZE", Fatal::UNABLE_TO_INITIALIZE );
type->Value( "UNABLE_TO_CREATE_TEXTURE", Fatal::UNABLE_TO_CREATE_TEXTURE );
type->Value( "DEVICE_LOST", Fatal::DEVICE_LOST );
END_META()

BEG_META( RendererType )
type->Value( "NOOP", RendererType::NOOP );
type->Value( "DIRECT3D9", RendererType::DIRECT3D9 );
type->Value( "DIRECT3D11", RendererType::DIRECT3D11 );
type->Value( "DIRECT3D12", RendererType::DIRECT3D12 );
type->Value( "GNM", RendererType::GNM );
type->Value( "METAL", RendererType::METAL );
type->Value( "NVN", RendererType::NVN );
type->Value( "OPENGLES", RendererType::OPENGLES );
type->Value( "OPENGL", RendererType::OPENGL );
type->Value( "VULKAN", RendererType::VULKAN );
END_META()

BEG_META( Access )
type->Value( "READ", Access::READ );
type->Value( "WRITE", Access::WRITE );
type->Value( "READ_WRITE", Access::READ_WRITE );
END_META()

BEG_META( Attrib )
type->Value( "POSITION", Attrib::POSITION );
type->Value( "NORMAL", Attrib::NORMAL );
type->Value( "TANGENT", Attrib::TANGENT );
type->Value( "BITANGENT", Attrib::BITANGENT );
type->Value( "COLOR0", Attrib::COLOR0 );
type->Value( "COLOR1", Attrib::COLOR1 );
type->Value( "COLOR2", Attrib::COLOR2 );
type->Value( "COLOR3", Attrib::COLOR3 );
type->Value( "INDICES", Attrib::INDICES );
type->Value( "WEIGHT", Attrib::WEIGHT );
type->Value( "TEXCOORD0", Attrib::TEXCOORD0 );
type->Value( "TEXCOORD1", Attrib::TEXCOORD1 );
type->Value( "TEXCOORD2", Attrib::TEXCOORD2 );
type->Value( "TEXCOORD3", Attrib::TEXCOORD3 );
type->Value( "TEXCOORD4", Attrib::TEXCOORD4 );
type->Value( "TEXCOORD5", Attrib::TEXCOORD5 );
type->Value( "TEXCOORD6", Attrib::TEXCOORD6 );
type->Value( "TEXCOORD7", Attrib::TEXCOORD7 );
END_META()

BEG_META( AttribType )
type->Value( "UINT8", AttribType::UINT8 );
type->Value( "UINT10", AttribType::UINT10 );
type->Value( "INT16", AttribType::INT16 );
type->Value( "HALF", AttribType::HALF );
type->Value( "FLOAT", AttribType::FLOAT );
END_META()

BEG_META( TextureType )
type->Value( "TEXTURE2D", TextureType::TEXTURE2D );
type->Value( "TEXTURE3D", TextureType::TEXTURE3D );
type->Value( "TEXTURECUBE", TextureType::TEXTURECUBE );
type->Value( "TEXTUREARRAY", TextureType::TEXTUREARRAY );
END_META()

BEG_META( TextureFormat )
type->Value( "BC1", TextureFormat::BC1 );
type->Value( "BC2", TextureFormat::BC2 );
type->Value( "BC3", TextureFormat::BC3 );
type->Value( "BC4", TextureFormat::BC4 );
type->Value( "BC5", TextureFormat::BC5 );
type->Value( "BC6H", TextureFormat::BC6H );
type->Value( "BC7", TextureFormat::BC7);
type->Value( "ETC1", TextureFormat::ETC1 );
type->Value( "ETC2", TextureFormat::ETC2 );
type->Value( "ETC2A", TextureFormat::ETC2A);
type->Value( "ETC2A1", TextureFormat::ETC2A1 );
type->Value( "PTC12", TextureFormat::PTC12 );
type->Value( "PTC14", TextureFormat::PTC14 );
type->Value( "PTC12A", TextureFormat::PTC12A );
type->Value( "PTC14A", TextureFormat::PTC14A );
type->Value( "PTC22", TextureFormat::PTC22 );
type->Value( "PTC24", TextureFormat::PTC24 );
type->Value( "ATC", TextureFormat::ATC );
type->Value( "ATCE", TextureFormat::ATCE );
type->Value( "ATCI", TextureFormat::ATCI );
type->Value( "ASTC4X4", TextureFormat::ASTC4X4 );
type->Value( "ASTC5X5", TextureFormat::ASTC5X5 );
type->Value( "ASTC6X6", TextureFormat::ASTC6X6 );
type->Value( "ASTC8X5", TextureFormat::ASTC8X5 );
type->Value( "ASTC8X6", TextureFormat::ASTC8X6 );
type->Value( "ASTC10X5", TextureFormat::ASTC10X5 );
type->Value( "UNKNOWN", TextureFormat::UNKNOWN );
type->Value( "R1", TextureFormat::R1 );
type->Value( "A8", TextureFormat::A8 );
type->Value( "R8", TextureFormat::R8 );
type->Value( "R8I", TextureFormat::R8I );
type->Value( "R8U", TextureFormat::R8U );
type->Value( "R8S", TextureFormat::R8S );
type->Value( "R16", TextureFormat::R16 );
type->Value( "R16I", TextureFormat::R16I );
type->Value( "R16U", TextureFormat::R16U );
type->Value( "R16F", TextureFormat::R16F );
type->Value( "R16S", TextureFormat::R16S );
type->Value( "R32I", TextureFormat::R32I );
type->Value( "R32U", TextureFormat::R32U );
type->Value( "R32F", TextureFormat::R32F );
type->Value( "RG8", TextureFormat::RG8 );
type->Value( "RG8I", TextureFormat::RG8I);
type->Value( "RG8U", TextureFormat::RG8U);
type->Value( "RG8S", TextureFormat::RG8S);
type->Value( "RG16", TextureFormat::RG16);
type->Value( "RG16I", TextureFormat::RG16I );
type->Value( "RG16U", TextureFormat::RG16U );
type->Value( "RG16F", TextureFormat::RG16F );
type->Value( "RG16S", TextureFormat::RG16S );
type->Value( "RG32I", TextureFormat::RG32I );
type->Value( "RG32U", TextureFormat::RG32U );
type->Value( "RG32F", TextureFormat::RG32F );
type->Value( "RGB8", TextureFormat::RGB8 );
type->Value( "RGB8I", TextureFormat::RGB8I );
type->Value( "RGB8U", TextureFormat::RGB8U );
type->Value( "RGB8S", TextureFormat::RGB8S );
type->Value( "RGB9E5F", TextureFormat::RGB9E5F );
type->Value( "BGRA8", TextureFormat::BGRA8 );
type->Value( "RGBA8", TextureFormat::RGBA8 );
type->Value( "RGBA8I", TextureFormat::RGBA8I );
type->Value( "RGBA8U", TextureFormat::RGBA8U );
type->Value( "RGBA8S", TextureFormat::RGBA8S );
type->Value( "RGBA16", TextureFormat::RGBA16 );
type->Value( "RGBA16I", TextureFormat::RGBA16I );
type->Value( "RGBA16U", TextureFormat::RGBA16U );
type->Value( "RGBA16F", TextureFormat::RGBA16F );
type->Value( "RGBA16S", TextureFormat::RGBA16S );
type->Value( "RGBA32I", TextureFormat::RGBA32I );
type->Value( "RGBA32U", TextureFormat::RGBA32U );
type->Value( "RGBA32F", TextureFormat::RGBA32F );
type->Value( "R5G6B5", TextureFormat::R5G6B5 );
type->Value( "RGBA4", TextureFormat::RGBA4 );
type->Value( "RGB5A1", TextureFormat::RGB5A1 );
type->Value( "RGB10A2", TextureFormat::RGB10A2 );
type->Value( "RG11B10F", TextureFormat::RG11B10F );
type->Value( "UNKNOWNDEPTH", TextureFormat::UNKNOWNDEPTH );
type->Value( "D16", TextureFormat::D16 );
type->Value( "D24", TextureFormat::D24 );
type->Value( "D24S8", TextureFormat::D24S8 );
type->Value( "D32", TextureFormat::D32 );
type->Value( "D16F", TextureFormat::D16F );
type->Value( "D24F", TextureFormat::D24F );
type->Value( "D32F", TextureFormat::D32F );
type->Value( "D0S8", TextureFormat::D0S8 );
type->Value( "DEFAULT", TextureFormat::DEFAULT );
END_META()

BEG_META( UniformType )
type->Value( "SAMPLER", UniformType::SAMPLER );
type->Value( "END", UniformType::END );
type->Value( "VEC4", UniformType::VEC4 );
type->Value( "MAT3", UniformType::MAT3 );
type->Value( "MAT4", UniformType::MAT4 );
END_META()

BEG_META( BackbufferRatio )
type->Value( "EQUAL", BackbufferRatio::EQUAL );
type->Value( "HALF", BackbufferRatio::HALF );
type->Value( "QUARTER", BackbufferRatio::QUARTER );
type->Value( "EIGHTH", BackbufferRatio::EIGHTH );
type->Value( "SIXTEENTH", BackbufferRatio::SIXTEENTH );
type->Value( "DOUBLE", BackbufferRatio::DOUBLE );
END_META()

BEG_META( OcclusionQueryResult )
type->Value( "INVISIBLE", OcclusionQueryResult::INVISIBLE );
type->Value( "VISIBLE", OcclusionQueryResult::VISIBLE );
type->Value( "NORESULT", OcclusionQueryResult::NORESULT );
END_META()

BEG_META( Topology )
type->Value( "TRILIST", Topology::TRILIST);
type->Value( "TRISTRIP", Topology::TRISTRIP );
type->Value( "LINELIST", Topology::LINELIST );
type->Value( "LINESTRIP", Topology::LINESTRIP );
type->Value( "POINTLIST", Topology::POINTLIST );
END_META()

BEG_META( TopologyConvert )
type->Value( "TRILIST_FLIP_WINDING", TopologyConvert::TRILIST_FLIP_WINDING );
type->Value( "TRISTRIP_FLIP_WINDING", TopologyConvert::TRISTRIP_FLIP_WINDING );
type->Value( "TRILIST_TO_LINELIST", TopologyConvert::TRILIST_TO_LINELIST );
type->Value( "TRISTRIP_TO_TRILIST", TopologyConvert::TRISTRIP_TO_TRILIST );
type->Value( "LINESTRIP_TO_LINELIST", TopologyConvert::LINESTRIP_TO_LINELIST );
END_META()

BEG_META( TopologySort )
type->Value( "DIRECTIONFRONT_TO_BACKMIN", TopologySort::DIRECTIONFRONT_TO_BACKMIN );
type->Value( "DIRECTIONFRONT_TO_BACKAVG", TopologySort::DIRECTIONFRONT_TO_BACKAVG );
type->Value( "DIRECTIONFRONT_TO_BACKMAX", TopologySort::DIRECTIONFRONT_TO_BACKMAX );
type->Value( "DIRECTIONBACK_TO_FRONTMIN", TopologySort::DIRECTIONBACK_TO_FRONTMIN );
type->Value( "DIRECTIONBACK_TO_FRONTAVG", TopologySort::DIRECTIONBACK_TO_FRONTAVG );
type->Value( "DIRECTIONBACK_TO_FRONTMAX", TopologySort::DIRECTIONBACK_TO_FRONTMAX );
type->Value( "DISTANCEFRONT_TO_BACKMIN", TopologySort::DISTANCEFRONT_TO_BACKMIN );
type->Value( "DISTANCEFRONT_TO_BACKAVG", TopologySort::DISTANCEFRONT_TO_BACKAVG );
type->Value( "DISTANCEFRONT_TO_BACKMAX", TopologySort::DISTANCEFRONT_TO_BACKMAX );
type->Value( "DISTANCEBACK_TO_FRONTMIN", TopologySort::DISTANCEBACK_TO_FRONTMIN );
type->Value( "DISTANCEBACK_TO_FRONTAVG", TopologySort::DISTANCEBACK_TO_FRONTAVG );
type->Value( "DISTANCEBACK_TO_FRONTMAX", TopologySort::DISTANCEBACK_TO_FRONTMAX );
END_META()

BEG_META( ViewMode )
type->Value( "DEFAULT", ViewMode::DEFAULT );
type->Value( "SEQUENTIAL", ViewMode::SEQUENTIAL );
type->Value( "DEPTHASCENDING", ViewMode::DEPTHASCENDING );
type->Value( "DEPTHDESCENDING", ViewMode::DEPTHDESCENDING );
END_META()


XE::uint64 XE::StateDefault()
{
	return BGFX_STATE_DEFAULT;
}

XE::uint64 XE::StateAlphaRef( uint64 val )
{
	return BGFX_STATE_ALPHA_REF( val );
}

XE::uint64 XE::StatePointSize( uint64 val )
{
	return BGFX_STATE_POINT_SIZE( val );
}

XE::uint64 XE::StateStencilFuncRef( uint64 val )
{
	return BGFX_STENCIL_FUNC_REF( val );
}

XE::uint64 XE::StateStencilFuncRMask( uint64 val )
{
	return BGFX_STENCIL_FUNC_RMASK( val );
}

XE::uint64 XE::SamplerBorderColor( uint64 val )
{
	return BGFX_SAMPLER_BORDER_COLOR( val );
}

XE::uint64 XE::BlendFunctionSeparate( StateBlendFunc srcRGB, StateBlendFunc dstRGB, StateBlendFunc srcA, StateBlendFunc dstA )
{
	return BGFX_STATE_BLEND_FUNC_SEPARATE( ( XE::uint64 )srcRGB, ( XE::uint64 )dstRGB, ( XE::uint64 )srcA, ( XE::uint64 )dstA );
}

XE::uint64 XE::BlendEquationSeparate( StateBlendEquation rgb, StateBlendEquation a )
{
	return BGFX_STATE_BLEND_EQUATION_SEPARATE( ( XE::uint64 )rgb, ( XE::uint64 )a );
}

XE::uint64 XE::BlendAdditive()
{
	return BGFX_STATE_BLEND_ADD;
}

XE::uint64 XE::BlendAlpha()
{
	return BGFX_STATE_BLEND_ALPHA;
}

XE::uint64 XE::BlendDarken()
{
	return BGFX_STATE_BLEND_DARKEN;
}

XE::uint64 XE::BlendLighten()
{
	return BGFX_STATE_BLEND_LIGHTEN;
}

XE::uint64 XE::BlendMultiply()
{
	return BGFX_STATE_BLEND_MULTIPLY;
}

XE::uint64 XE::BlendNormal()
{
	return BGFX_STATE_BLEND_NORMAL;
}

XE::uint64 XE::BlendScreen()
{
	return BGFX_STATE_BLEND_SCREEN;
}

XE::uint64 XE::BlendLinearBurn()
{
	return BGFX_STATE_BLEND_LINEAR_BURN;
}

XE::uint64 XE::BlendFuncRT1( StateBlendFunc src, StateBlendFunc dst )
{
	return BGFX_STATE_BLEND_FUNC_RT_1( ( XE::uint64 )src, ( XE::uint64 )dst );
}

XE::uint64 XE::BlendFuncRT2( StateBlendFunc src, StateBlendFunc dst )
{
	return BGFX_STATE_BLEND_FUNC_RT_1( ( XE::uint64 )src, ( XE::uint64 )dst );
}

XE::uint64 XE::BlendFuncRT3( StateBlendFunc src, StateBlendFunc dst )
{
	return BGFX_STATE_BLEND_FUNC_RT_2( ( XE::uint64 )src, ( XE::uint64 )dst );
}

XE::uint64 XE::BlendFuncRT1E( StateBlendFunc src, StateBlendFunc dst, StateBlendEquation equation )
{
	return BGFX_STATE_BLEND_FUNC_RT_1E( ( XE::uint64 )src, ( XE::uint64 )dst, ( XE::uint64 )equation );
}

XE::uint64 XE::BlendFuncRT2E( StateBlendFunc src, StateBlendFunc dst, StateBlendEquation equation )
{
	return BGFX_STATE_BLEND_FUNC_RT_2E( ( XE::uint64 )src, ( XE::uint64 )dst, ( XE::uint64 )equation );
}

XE::uint64 XE::BlendFuncRT3E( StateBlendFunc src, StateBlendFunc dst, StateBlendEquation equation )
{
	return BGFX_STATE_BLEND_FUNC_RT_3E( ( XE::uint64 )src, ( XE::uint64 )dst, ( XE::uint64 )equation );
}
*/