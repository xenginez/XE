/*!
 * \file   SceneComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/09
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SCENETREECOMPONENT_H__D96EDC7D_216F_47EE_ACC2_31541C5B31C7
#define __SCENETREECOMPONENT_H__D96EDC7D_216F_47EE_ACC2_31541C5B31C7

#include "Component.h"
#include "Transform.h"

BEG_XE_NAMESPACE

class WORLD_API SceneComponent : public Component
{
	OBJECT( SceneComponent, Component )

public:
	SceneComponent();

	~SceneComponent();

public:
	Transform * GetTransform();

public:
	SceneComponentPtr GetRoot();

	SceneComponentPtr GetParent() const;

	Array< SceneComponentPtr > GetChildren() const;

	void AttachToParent( SceneComponentPtr val );

public:
	template< typename T > std::shared_ptr<T> GetRootT()
	{
		return DP_CAST<T>( GetRoot() );
	}

	template< typename T > std::shared_ptr<T> GetParentT()
	{
		return DP_CAST<T>( GetParent() );
	}

public:
	SceneComponentPtr FindChild( const String& val ) const;

	SceneComponentPtr FindChild( IMetaClassPtr val ) const;

	SceneComponentPtr FindChild( ComponentHandle val ) const;

	SceneComponentPtr FindChildFromTree( const String& val ) const;

	SceneComponentPtr FindChildFromTree( IMetaClassPtr val ) const;

	SceneComponentPtr FindChildFromTree( ComponentHandle val ) const;

public:
	template< typename T > std::shared_ptr<T> FindChildT() const
	{
		return SP_CAST<T>( FindChild( ClassID<T>::Get() ) );
	}

	template< typename T > std::shared_ptr<T> FindChildT( const String& val ) const
	{
		return DP_CAST<T>( FindChild( val ) );
	}

	template< typename T > std::shared_ptr<T> FindChildT( ComponentHandle val ) const
	{
		return DP_CAST<T>( FindChild( val ) );
	}

	template< typename T > std::shared_ptr<T> FindChildFromTreeT() const
	{
		return SP_CAST<T>( FindChildFromTree( ClassID<T>::Get() ) );
	}

	template< typename T > std::shared_ptr<T> FindChildFromTreeT( const String& val ) const
	{
		return DP_CAST<T>( FindChildFromTree( val ) );
	}

	template< typename T > std::shared_ptr<T> FindChildFromTreeT( ComponentHandle val ) const
	{
		return DP_CAST<T>( FindChildFromTree( val ) );
	}

private:
	virtual void Startup() override;

	virtual void Update( XE::float32 dt ) override;

	virtual void Clearup() override;

private:
	Transform _Transform;
	ComponentHandle _ParentHandle;
	Array< ComponentHandle > _ChildrenHandle;
};

END_XE_NAMESAPCE

#endif // __SCENETREECOMPONENT_H__D96EDC7D_216F_47EE_ACC2_31541C5B31C7
