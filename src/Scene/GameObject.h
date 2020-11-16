/*!
 * \file   GameObject.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GAMEOBJECT_H__ECCC67A6_5AD3_4306_8C14_915D53744BBA
#define __GAMEOBJECT_H__ECCC67A6_5AD3_4306_8C14_915D53744BBA

#include "GameEntity.h"

BEG_XE_NAMESPACE

class XE_API GameObject final : public XE::GameEntity
{
	OBJECT( GameObject, GameEntity )

public:
	GameObject();

	~GameObject();

public:
	const XE::AABB & GetBoundingBox() const;

public:
	GameObjectType GetType() const;

	void SetType( GameObjectType val );

public:
	Vec3f GetWorldUp();

	Vec3f GetWorldRight();

	Vec3f GetWorldForward();

	Vec3f GetRelativeUp() const;

	Vec3f GetRelativeRight() const;

	Vec3f GetRelativeForward() const;

public:
	const Vec3f & GetWorldScale();

	void SetWorldScale( const Vec3f & val );

	const Vec3f & GetWorldPosition();

	void SetWorldPosition( const Vec3f & val );

	const Quat & GetWorldRotation();

	void SetWorldRotation( const Quat & val );

public:
	const Vec3f & GetRelativeScale() const;

	void SetRelativeScale( const Vec3f & val );

	const Vec3f & GetRelativePosition() const;

	void SetRelativePosition( const Vec3f & val );

	const Quat & GetRelativeRotation() const;

	void SetRelativeRotation( const Quat & val );

public:
	const Mat4f & GetWorldTransform() const;

	void SetWorldTransform( const Mat4f & val );

	const Mat4f & GetRelativeTransform() const;

	void SetRelativeTransform( const Mat4f & val );

public:
	SceneComponentPtr AddSceneComponent( IMetaClassPtr val, const SceneComponentPtr& parent );

	BehaviorComponentPtr AddBehaviorComponent( IMetaClassPtr val );

	bool RemoveSceneComponent( const XE::SceneComponentPtr & val );

	bool RemoveBehaviorComponet( const BehaviorComponentPtr & val );

public:
	BehaviorComponentPtr FindBehaviorComponent( const String& val ) const;

	BehaviorComponentPtr FindBehaviorComponent( IMetaClassPtr val ) const;

	BehaviorComponentPtr FindBehaviorComponent( ComponentHandle val ) const;

	template< typename T > XE::SharedPtr<T> FindBehaviorComponentT() const
	{
		return SP_CAST<T>( FindBehaviorComponent( ClassID<T>::Get() ) );
	}

	template< typename T > XE::SharedPtr<T> FindBehaviorComponentT( const String& val ) const
	{
		return DP_CAST<T>( FindBehaviorComponent( val ) );
	}

	template< typename T > XE::SharedPtr<T> FindBehaviorComponentT( ComponentHandle val ) const
	{
		return DP_CAST<T>( FindBehaviorComponent( val ) );
	}

public:
	SceneComponentPtr GetRootSceneComponent() const;

	const XE::Array<BehaviorComponentPtr>& GetBehaviorComponents() const;

public:
	void ProcessEvent( const EventPtr & val ) override;

protected:
	void Startup() override;

	void Update( XE::float32 dt ) override;

	void Clearup() override;

protected:
	void OnEnable() override;

	void OnDisable() override;

private:
	GameObjectType _Type;
	SceneComponentPtr _RootSceneComponent;
	XE::ComponentHandleAllocator _HandleTable;
	XE::Array< BehaviorComponentPtr > _BehaviorComponents;
};

template<> class MakeAABB< GameObjectPtr >
{
public:
	XE::AABB operator()( const GameObjectPtr & val ) const
	{
		return val->GetBoundingBox();
	}
};

template<> class MakeRect< GameObjectPtr >
{
public:
	XE::Rect operator()( const GameObjectPtr & val ) const
	{
		AABB box = val->GetBoundingBox();
		auto center = box.GetCenter();
		auto size = box.GetSize();

		return Rect( center.x, center.y, size.x, size.y );
	}
};

END_XE_NAMESPACE

#endif // __GAMEOBJECT_H__ECCC67A6_5AD3_4306_8C14_915D53744BBA
