/*!
 * \file   Model.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/17
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MODEL_H__07BBEC42_C159_4E55_9B72_CE48DEB0589F
#define __MODEL_H__07BBEC42_C159_4E55_9B72_CE48DEB0589F

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Model : public Object
{
	OBJECT( Model, Object )

public:
	Model();

	~Model() override;

public:
	const Mat4& GetWorldTransform() const;
	
	void SetWorldTransform( const Mat4& val );
	
public:
	const LOD& GetLOD() const;
	
	void SetLOD( const LOD& val );
	
	MeshPtr GetMesh( XE::uint64 lod ) const;

	void SetMesh( MeshPtr val, XE::uint64 lod );

	MaterialPtr GetMaterial() const;

	void SetMaterial( MaterialPtr val );

private:
	LOD _LOD;
	Mat4 _Transform;
	Array<MeshPtr> _Mesh;
	MaterialPtr _Material;
};

END_XE_NAMESAPCE

#endif // __MODEL_H__07BBEC42_C159_4E55_9B72_CE48DEB0589F
