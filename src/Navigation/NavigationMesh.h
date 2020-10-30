/*!
 * \file	NavigationMesh.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef NAVIGATIONMESH_H__8525A1B1_097F_44D5_8165_B30558A04235
#define NAVIGATIONMESH_H__8525A1B1_097F_44D5_8165_B30558A04235

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API NavigationMesh : public XE::Object
{
	OBJECT( NavigationMesh, Object )

public:
	NavigationMesh();

	~NavigationMesh() override;

public:
	XE::NavigationMeshHandle GetHandle() const;

public:
	void AssetLoad() override;

private:
	XE::NavigationMeshHandle _Handle;
};

END_XE_NAMESPACE

#endif // NAVIGATIONMESH_H__8525A1B1_097F_44D5_8165_B30558A04235
