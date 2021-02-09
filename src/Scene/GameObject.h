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
	XE::AABB GetBoundingBox() const;

public:
	GameObjectType GetType() const;

	void SetType( GameObjectType val );

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
	SceneComponentPtr GetSceneComponent() const;

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
	SceneComponentPtr _SceneComponent;
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
	XE::Rectf operator()( const GameObjectPtr & val ) const
	{
		AABB box = val->GetBoundingBox();
		auto center = box.GetCenter();
		auto size = box.GetSize();

		return Rectf( center.x, center.y, size.x, size.y );
	}
};

END_XE_NAMESPACE

#endif // __GAMEOBJECT_H__ECCC67A6_5AD3_4306_8C14_915D53744BBA
