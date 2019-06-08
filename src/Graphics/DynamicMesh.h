/*!
 * \file    DynamicMesh.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-31
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __DYNAMICMESH_H__56D3F777_E426_498D_9E35_2E50CB890A55
#define __DYNAMICMESH_H__56D3F777_E426_498D_9E35_2E50CB890A55

#include "Mesh.h"

BEG_XE_NAMESPACE

class GRAPHICS_API DynamicMesh : public Mesh
{
	OBJECT(DynamicMesh, Mesh)
	
public:
	DynamicMesh();
	
	~DynamicMesh() override;
};

END_XE_NAMESPACE

#endif //__DYNAMICMESH_H__56D3F777_E426_498D_9E35_2E50CB890A55
