/*!
 * \file   SceneObject.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef SCENEOBJECT_H__F888E5FC_E0D1_4D0D_9B2B_D42241EDFFBE
#define SCENEOBJECT_H__F888E5FC_E0D1_4D0D_9B2B_D42241EDFFBE

#include "Math/Math.h"
#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API SceneObject : public XE::Object
{
	OBJECT( SceneObject, Object )

private:
	friend class World;
	friend class GameZone;

public:
	SceneObject();

	~SceneObject();

public:
	XE::WorldPtr GetWorld() const;

public:
	bool GetEnable() const;

	void SetEnable( bool val );

	const String & GetName() const;

	void SetName( const String & val );

	XE::SceneObjectHandle GetGameZone() const;

	void SetGameZone( const XE::SceneObjectHandle & val );

protected:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

protected:
	virtual void OnEnable() = 0;

	virtual void OnDisable() = 0;

public:
	XE::Transform & GetTransform();

	XE::SceneObjectHandle GetHandle() const;

	XE::GameZoneObjectPtr GetGameZoneObjectPtr() const;

private:
	bool _Enable;
	XE::String _Name;
	XE::WorldWPtr _World;
	XE::Transform _Transform;
	XE::SceneObjectHandle _Handle;

	XE::SceneObjectHandle _Zone;

	XE::Vec3f _WorldScale;
	XE::Vec3f _WorldPosition;
	XE::Quat _WorldRotation;
	XE::Mat4x4f _WorldTransform;
};

END_XE_NAMESPACE

#endif // SCENEOBJECT_H__F888E5FC_E0D1_4D0D_9B2B_D42241EDFFBE
