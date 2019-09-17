/*!
 * \file   WorldObject.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/12
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __WORLDOBJECT_H__F419FF88_F84C_4C18_AC3A_D1660070EABD
#define __WORLDOBJECT_H__F419FF88_F84C_4C18_AC3A_D1660070EABD

#include "GameObject.h"

BEG_XE_NAMESPACE

class WORLD_API WorldObject : public XE::Object
{
	OBJECT( WorldObject, Object )

public:
	friend class WorldService;

public:
	WorldObject();

	~WorldObject();

public:
	const String& GetName() const;

	void SetName( const String& val );

public:
	bool AddGameObject( const GameObjectPtr & val );

	GameObjectPtr FindGameObject( const String& val ) const;

	GameObjectPtr FindGameObject( GameObjectHandle val ) const;

	const Array< GameObjectPtr >& GetGameObjects() const;

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

public:
	void OnMessage( MessagePtr & val ) override;

protected:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

private:
	String _Name;
	static XE::uint64 _HandleTable;
	OCTree<GameObjectPtr> _StaticTree;
	OCTree<GameObjectPtr> _DynmicTree;
	Array< GameObjectPtr > _AllGameObjects;
};

END_XE_NAMESPACE

#endif // __WORLDOBJECT_H__F419FF88_F84C_4C18_AC3A_D1660070EABD
