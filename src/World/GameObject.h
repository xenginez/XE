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

#include "Transform.h"

BEG_XE_NAMESPACE

class WORLD_API GameObject : public XE::Object
{
	OBJECT( GameObject, Object )

	friend class WorldObject;

public:
	GameObject();

	~GameObject();

public:
	const String& GetName() const;

	WorldObjectPtr GetWorld() const;

	GameObjectHandle GetHandle() const;

public:
	IFrameworkPtr GetFramework() const;

	void SetFramework( IFrameworkPtr val );

public:
	Transform * GetTransform();

	SceneComponentPtr GetSceneComponent() const;

public:
	bool GetEnabled() const;

	void SetEnabled( bool val );

	bool GetDestroy() const;

	void SetDestroy( bool val );

	GameObjectType GetType() const;

	void SetType( GameObjectType val );

public:
	ComponentPtr AddComponent( IMetaClassPtr val );

	ComponentPtr FindComponent( const String& val ) const;

	ComponentPtr FindComponent( IMetaClassPtr val ) const;

	ComponentPtr FindComponent( ComponentHandle val ) const;

	const std::vector< ComponentPtr >& GetAllComponents() const;

public:
	template< typename T > std::shared_ptr<T> AddComponentT()
	{
		return SP_CAST<T>( AddComponent( ClassID<T>::Get() ) );
	}

	template< typename T > std::shared_ptr<T> FindComponentT() const
	{
		return SP_CAST<T>( FindComponent( ClassID<T>::Get() ) );
	}

	template< typename T > std::shared_ptr<T> FindComponentT( const String& val ) const
	{
		return DP_CAST<T>( FindComponent( val ) );
	}

	template< typename T > std::shared_ptr<T> FindComponentT( ComponentHandle val ) const
	{
		return DP_CAST<T>( FindComponent( val ) );
	}

protected:
	void Startup();

	void Update( XE::real dt );

	void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnUpdate( XE::real dt );

	virtual void OnClearup();

private:
	String _Name;
	bool _Enabled;
	bool _Destroy;
	GameObjectType _Type;
	WorldObjectWPtr _World;
	GameObjectHandle _Handle;
	IFrameworkPtr _Framework;
	SceneComponentPtr _SceneComponent;
	std::vector< ComponentPtr > _Components;
};

END_XE_NAMESPACE

#endif // __GAMEOBJECT_H__ECCC67A6_5AD3_4306_8C14_915D53744BBA
