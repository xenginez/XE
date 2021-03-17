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

#include "SceneObject.h"

BEG_XE_NAMESPACE

class XE_API GameObject final : public XE::SceneObject
{
	OBJECT( GameObject, SceneObject )

public:
	GameObject();

	~GameObject();

public:
	XE::AABB GetBoundingBox() const;

public:
	XE::GameObjectType GetType() const;

	void SetType( XE::GameObjectType val );

public:
	XE::SceneComponentPtr AddSceneComponent( XE::IMetaClassPtr val, const XE::SceneComponentPtr & parent );

	XE::BehaviorComponentPtr AddBehaviorComponent( XE::IMetaClassPtr val );

	bool RemoveSceneComponent( const XE::SceneComponentPtr & val );

	bool RemoveBehaviorComponet( const XE::BehaviorComponentPtr & val );

public:
	XE::BehaviorComponentPtr FindBehaviorComponent( const XE::String & val ) const;

	XE::BehaviorComponentPtr FindBehaviorComponent( XE::IMetaClassPtr val ) const;

	XE::BehaviorComponentPtr FindBehaviorComponent( XE::ComponentHandle val ) const;

	template< typename T > XE::SharedPtr< T > FindBehaviorComponentT() const
	{
		return SP_CAST< T >( FindBehaviorComponent( ClassID< T >::Get() ) );
	}

	template< typename T > XE::SharedPtr< T > FindBehaviorComponentT( const XE::String & val ) const
	{
		return DP_CAST< T >( FindBehaviorComponent( val ) );
	}

	template< typename T > XE::SharedPtr< T > FindBehaviorComponentT( XE::ComponentHandle val ) const
	{
		return DP_CAST< T >( FindBehaviorComponent( val ) );
	}

public:
	XE::SceneComponentPtr FindSceneComponent( XE::IMetaClassPtr val ) const;

	XE::SceneComponentPtr FindSceneComponent( const XE::String & val ) const;

	XE::SceneComponentPtr FindSceneComponent( XE::ComponentHandle val ) const;

	template< typename T > XE::SharedPtr< T > FindSceneComponentT() const
	{
		return DP_CAST< T >( FindSceneComponent( XE_ClassID< T >::Get() ) );
	}

	template< typename T > XE::SharedPtr< T > FindSceneComponentT( const XE::String & val ) const
	{
		return DP_CAST< T >( FindSceneComponent( val ) );
	}

	template< typename T > XE::SharedPtr< T > FindSceneComponentT( XE::ComponentHandle val ) const
	{
		return DP_CAST< T >( FindSceneComponent( val ) );
	}

public:
	XE::SceneComponentPtr GetRootSceneComponents() const;

	const XE::Array< XE::BehaviorComponentPtr > & GetBehaviorComponents() const;

public:
	void ProcessEvent( const XE::EventPtr & val ) override;

protected:
	void Startup() override;

	void Update( XE::float32 dt ) override;

	void LateUpdate( XE::float32 dt ) override;

	void Clearup() override;

protected:
	void OnEnable() override;

	void OnDisable() override;

private:
	XE::GameObjectType _Type;
	XE::SceneComponentPtr _SceneComponent;
	XE::ComponentHandleAllocator _HandleTable;
	XE::Array< XE::BehaviorComponentPtr > _BehaviorComponents;
};

template<> class MakeAABB< XE::GameObjectPtr >
{
public:
	XE::AABB operator()( const XE::GameObjectPtr & val ) const
	{
		return val->GetBoundingBox();
	}
};

template<> class MakeRect< XE::GameObjectPtr >
{
public:
	XE::Rectf operator()( const XE::GameObjectPtr & val ) const
	{
		XE::AABB box = val->GetBoundingBox();
		auto center = box.GetCenter();
		auto size = box.GetSize();

		return XE::Rectf( center.x, center.y, size.x, size.y );
	}
};

END_XE_NAMESPACE

#endif // __GAMEOBJECT_H__ECCC67A6_5AD3_4306_8C14_915D53744BBA
