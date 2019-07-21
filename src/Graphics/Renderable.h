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

class GRAPHICS_API Renderable : public std::enable_shared_from_this< Renderable >
{
	OBJECT( Renderable )
	
public:
	Renderable();
	
	virtual ~Renderable();

public:
	virtual void Startup();

	virtual void Render();

	virtual void Clearup();

protected:
	virtual void OnStartup() = 0;

	virtual void OnRender() = 0;

	virtual void OnClearup() = 0;

public:
	const Mat4 & GetTransform() const;

	void SetTransform( const Mat4 & val );

	MeshPtr GetMesh() const;

	void SetMesh( const MeshPtr & val );

	MaterialPtr GetMaterial() const;

	void SetMaterialPtr( const MaterialPtr & val );

private:
	MeshPtr _Mesh;
	Mat4 _Transform;
	MaterialPtr _Material;
};

END_XE_NAMESPACE

#endif //__RENDERABLE_H__8DB83893_AC3A_4B1B_84CB_C62700378348
