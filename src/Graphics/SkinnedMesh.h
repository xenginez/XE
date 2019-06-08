/*!
 * \file    SkinnedMesh.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-31
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SKINNEDMESH_H__5E8D3F1A_5765_42C1_9164_F9AA6CCFC9CB
#define __SKINNEDMESH_H__5E8D3F1A_5765_42C1_9164_F9AA6CCFC9CB

#include "Mesh.h"

BEG_XE_NAMESPACE

class GRAPHICS_API SkinnedMesh : public Mesh
{
	OBJECT(SkinnedMesh, Mesh)
	
public:
	SkinnedMesh();
	
	~SkinnedMesh() override;
};

END_XE_NAMESPACE

#endif //__SKINNEDMESH_H__5E8D3F1A_5765_42C1_9164_F9AA6CCFC9CB
