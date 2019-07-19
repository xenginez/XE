/*!
 * \file    Renderable.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-31
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERABLE_H__8DB83893_AC3A_4B1B_84CB_C62700378348
#define __RENDERABLE_H__8DB83893_AC3A_4B1B_84CB_C62700378348

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Renderable : public Object
{
	OBJECT( Renderable, Object )
	
public:
	Renderable();
	
	~Renderable() override;

public:
	MeshPtr GetMesh() const;

	void SetMesh( const MeshPtr & val );

	MaterialPtr GetMaterial() const;

	void SetMaterialPtr( const MaterialPtr & val );

public:
	const Mat4& GetTransform() const;

	void UpdateTransform( const Mat4& val );

private:
	MeshPtr _Mesh;
	Mat4 _Transform;
	MaterialPtr _Material;
};

END_XE_NAMESPACE

#endif //__RENDERABLE_H__8DB83893_AC3A_4B1B_84CB_C62700378348
