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

#include "Math/Math.h"

#include "Component.h"

BEG_XE_NAMESPACE

class XE_API SceneComponent : public Component
{
	OBJECT( SceneComponent, Component )

public:
	friend class GameObject;

public:
	SceneComponent();

	~SceneComponent();

public:
	SceneComponentPtr GetRoot();

	SceneComponentPtr GetParent() const;

	const Array< SceneComponentPtr > & GetChildren() const;

public:
	template< typename T > XE::SharedPtr<T> GetRootT()
	{
		return DP_CAST<T>( GetRoot() );
	}

	template< typename T > XE::SharedPtr<T> GetParentT() const
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
	template< typename T > XE::SharedPtr<T> FindChildT() const
	{
		return SP_CAST<T>( FindChild( ClassID<T>::Get() ) );
	}

	template< typename T > XE::SharedPtr<T> FindChildT( const String& val ) const
	{
		return DP_CAST<T>( FindChild( val ) );
	}

	template< typename T > XE::SharedPtr<T> FindChildT( ComponentHandle val ) const
	{
		return DP_CAST<T>( FindChild( val ) );
	}

	template< typename T > XE::SharedPtr<T> FindChildFromTreeT() const
	{
		return SP_CAST<T>( FindChildFromTree( ClassID<T>::Get() ) );
	}

	template< typename T > XE::SharedPtr<T> FindChildFromTreeT( const String& val ) const
	{
		return DP_CAST<T>( FindChildFromTree( val ) );
	}

	template< typename T > XE::SharedPtr<T> FindChildFromTreeT( ComponentHandle val ) const
	{
		return DP_CAST<T>( FindChildFromTree( val ) );
	}

private:
	void Startup() override;

	void Update( XE::float32 dt ) override;

	void LateUpdate( XE::float32 dt ) override;

	void Clearup() override;

public:
	XE::AABB GetBoundingBox();

	XE::Transform & GetTransform();

private:
	XE::Transform _Transform;

	XE::SceneComponentWPtr _Parent;
	XE::Array< SceneComponentPtr > _Children;
};

END_XE_NAMESPACE

#endif // __SCENETREECOMPONENT_H__D96EDC7D_216F_47EE_ACC2_31541C5B31C7
