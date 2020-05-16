/*!
 * \file   IWorldService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IWORLDSERVICE_H__1CE0128D_8AE2_434B_BF15_97B410BA145D
#define __IWORLDSERVICE_H__1CE0128D_8AE2_434B_BF15_97B410BA145D

#include "IService.h"

BEG_XE_NAMESPACE

class XE_API IWorldService : public IService
{
	OBJECT( IWorldService, IService )

public:
	IWorldService();

	~IWorldService() override;

public:
	virtual void LoadWorld( const XE::String & val ) = 0;

public:
	bool AddGameObject( const GameObjectPtr & val );

	bool RemoveGameObject( const GameObjectPtr & val );

	GameObjectPtr FindGameObject( const String & val ) const;

	GameObjectPtr FindGameObject( GameObjectHandle val ) const;

	const Array< GameObjectPtr > & GetGameObjects() const;

public:
	GameObjectPtr Intersect( const Array<GameObjectPtr> exclude, const Ray & val ) const;

	GameObjectPtr Intersect( const Array<GameObjectPtr> exclude, const AABB & val ) const;

	GameObjectPtr Intersect( const Array<GameObjectPtr> exclude, const Line & val ) const;

	GameObjectPtr Intersect( const Array<GameObjectPtr> exclude, const Plane & val ) const;

	GameObjectPtr Intersect( const Array<GameObjectPtr> exclude, const Sphere & val ) const;

	GameObjectPtr Intersect( const Array<GameObjectPtr> exclude, const Frustum & val ) const;

public:
	Array<GameObjectPtr> Intersects( const Ray & val ) const;

	Array<GameObjectPtr> Intersects( const AABB & val ) const;

	Array<GameObjectPtr> Intersects( const Line & val ) const;

	Array<GameObjectPtr> Intersects( const Plane & val ) const;

	Array<GameObjectPtr> Intersects( const Sphere & val ) const;

	Array<GameObjectPtr> Intersects( const Frustum & val ) const;

protected:
	virtual XE::WorldPtr GetCurrentWorld() const = 0;
};

END_XE_NAMESPACE

#endif // __IWORLDSERVICE_H__1CE0128D_8AE2_434B_BF15_97B410BA145D
