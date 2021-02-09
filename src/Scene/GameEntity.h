/*!
 * \file	GameEntity.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ENTITY_H__C84CE01E_E4FF_4530_B337_D1B9F4DBEF7A
#define ENTITY_H__C84CE01E_E4FF_4530_B337_D1B9F4DBEF7A

#include "Math/Math.h"
#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API GameEntity : public XE::Object
{
	OBJECT( GameEntity, Object )

private:
	friend class World;
	friend class GameZone;

public:
	GameEntity();

	~GameEntity();

public:
	XE::WorldPtr GetWorld() const;

public:
	bool GetEnable() const;

	void SetEnable( bool val );

	const String & GetName() const;

	void SetName( const String & val );

	XE::GameEntityHandle GetGameZone() const;

	void SetGameZone( const XE::GameEntityHandle & val );

protected:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

protected:
	virtual void OnEnable() = 0;

	virtual void OnDisable() = 0;

public:
	XE::Transform & GetTransform();

	XE::GameEntityHandle GetHandle() const;

	XE::GameZonePtr GetGameZonePtr() const;

private:
	bool _Enable;
	XE::String _Name;
	XE::WorldWPtr _World;
	XE::Transform _Transform;
	XE::GameEntityHandle _Handle;

	XE::GameEntityHandle _Zone;

	XE::Vec3f _WorldScale;
	XE::Vec3f _WorldPosition;
	XE::Quat _WorldRotation;
	XE::Mat4x4f _WorldTransform;
};

END_XE_NAMESPACE

#endif // ENTITY_H__C84CE01E_E4FF_4530_B337_D1B9F4DBEF7A
