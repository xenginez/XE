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

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API GameObject : public XE::Object
{
	OBJECT( GameObject, Object )

	friend class World;

public:
	GameObject();

	~GameObject();

public:
	GameObjectHandle GetHandle() const;

public:
	const XE::AABB & GetBoundingBox() const;

public:
	Vec3 GetWorldUp();

	Vec3 GetWorldRight();

	Vec3 GetWorldForward();

	Vec3 GetRelativeUp() const;

	Vec3 GetRelativeRight() const;

	Vec3 GetRelativeForward() const;

public:
	const Vec3 & GetWorldScale();

	void SetWorldScale( const Vec3 & val );

	const Vec3 & GetWorldPosition();

	void SetWorldPosition( const Vec3 & val );

	const Quat & GetWorldRotation();

	void SetWorldRotation( const Quat & val );

public:
	const Vec3 & GetRelativeScale() const;

	void SetRelativeScale( const Vec3 & val );

	const Vec3 & GetRelativePosition() const;

	void SetRelativePosition( const Vec3 & val );

	const Quat & GetRelativeRotation() const;

	void SetRelativeRotation( const Quat & val );

public:
	const Mat4 & GetWorldTransform() const;

	void SetWorldTransform( const Mat4 & val );

	const Mat4 & GetRelativeTransform() const;

	void SetRelativeTransform( const Mat4 & val );

public:
	bool GetEnabled() const;

	void SetEnabled( bool val );

	bool GetDestroy() const;

	void SetDestroy( bool val );

	GameObjectType GetType() const;

	void SetType( GameObjectType val );

	const String & GetName() const;

	void SetName( const String & val );

public:
	ComponentPtr AddComponent( IMetaClassPtr val );

	ComponentPtr FindComponent( const String& val ) const;

	ComponentPtr FindComponent( IMetaClassPtr val ) const;

	ComponentPtr FindComponent( ComponentHandle val ) const;

	const XE::Array< ComponentPtr >& GetComponents() const;

public:
	SceneComponentPtr GetRootSceneComponent() const;

	XE::Array<SceneComponentPtr> GetSceneComponets() const;

	XE::Array<BehaviorComponentPtr> GetBehaviorComponents() const;

public:
	template< typename T > XE::SharedPtr<T> AddComponentT()
	{
		return SP_CAST<T>( AddComponent( ClassID<T>::Get() ) );
	}

	template< typename T > XE::SharedPtr<T> FindComponentT() const
	{
		return SP_CAST<T>( FindComponent( ClassID<T>::Get() ) );
	}

	template< typename T > XE::SharedPtr<T> FindComponentT( const String& val ) const
	{
		return DP_CAST<T>( FindComponent( val ) );
	}

	template< typename T > XE::SharedPtr<T> FindComponentT( ComponentHandle val ) const
	{
		return DP_CAST<T>( FindComponent( val ) );
	}

public:
	void ProcessEvent( EventPtr & val ) override;

protected:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnUpdate( XE::float32 dt );

	virtual void OnClearup();

private:
	String _Name;
	bool _Enabled;
	bool _Destroy;
	GameObjectType _Type;
	GameObjectHandle _Handle;
	SceneComponentPtr _SceneComponent;
	XE::Array< ComponentPtr > _Components;
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
