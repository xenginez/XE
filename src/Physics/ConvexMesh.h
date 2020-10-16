/*!
 * \file	ConvexMesh.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/14
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CONVEXMESH_H__2B7F14EF_B860_4313_8897_FD3A36963ABD
#define CONVEXMESH_H__2B7F14EF_B860_4313_8897_FD3A36963ABD

#include "Math/Vec3.h"
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API ConvexMesh : public XE::Object
{
public:
	ConvexMesh();

	~ConvexMesh();

private:
	XE::Array<XE::Vec3> _Vertices;
	XE::Array<XE::uint8> _Indices;
};

END_XE_NAMESPACE

#endif // CONVEXMESH_H__2B7F14EF_B860_4313_8897_FD3A36963ABD
