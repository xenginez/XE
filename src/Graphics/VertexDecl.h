/*!
 * \file   VertexDecl.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __VERTEXDECL_H__2D221F64_1658_4CB8_8DD1_D2287FA5EF4D
#define __VERTEXDECL_H__2D221F64_1658_4CB8_8DD1_D2287FA5EF4D

#include "Type.h"

BEG_XE_NAMESPACE

template <typename T> struct GRAPHICS_API Vertex
{
	static const VertexLayout& GetLayout()
	{
		static VertexLayout s_decl = [] ()
		{
			VertexLayout decl;
			T::Init( decl );
			return decl;
		}( );
		return s_decl;
	}
};

struct GRAPHICS_API PosTexcoord0Vertex : Vertex<PosTexcoord0Vertex>
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	float u = 0.0f;
	float v = 0.0f;

	static void Init( VertexLayout& decl );
};

struct GRAPHICS_API MeshVertex : Vertex<MeshVertex>
{
	static void Init( VertexLayout& decl );
};

struct GRAPHICS_API PosTexcoord0Color0Vertex : Vertex<PosTexcoord0Color0Vertex>
{
	static void Init( VertexLayout& decl );
};

END_XE_NAMESAPCE

#endif // __VERTEXDECL_H__2D221F64_1658_4CB8_8DD1_D2287FA5EF4D
