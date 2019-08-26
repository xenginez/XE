/*!
 * \file	Model.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/20
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef MODEL_H__BBFE02D5_5563_4B37_8050_C93989C9F86E
#define MODEL_H__BBFE02D5_5563_4B37_8050_C93989C9F86E

#include "Type.h"

BEG_XE_NAMESPACE

class RENDER_API Model : public Renderable
{
	OBJECT( Model, Renderable )

public:
	Model();

	virtual ~Model();

protected:
	void OnStartup( RenderContextPtr & context ) override;

	void OnRender( RenderContextPtr & context, RenderQueuePtr & queue ) override;

	void OnClearup( RenderContextPtr & context ) override;

public:
	MeshPtr GetMesh() const;

	void SetMesh( const MeshPtr & val );

	MaterialPtr GetMaterial() const;

	void SetMaterial( const MaterialPtr & val );

private:
	MeshPtr _Mesh;
	MaterialPtr _Material;
};

END_XE_NAMESPACE

#endif // MODEL_H__BBFE02D5_5563_4B37_8050_C93989C9F86E