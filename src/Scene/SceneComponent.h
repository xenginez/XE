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
	XE::SceneComponentPtr GetRoot();

	XE::SceneComponentPtr GetParent() const;

	const XE::Array< XE::SceneComponentPtr > & GetChildren() const;

public:
	template< typename T > XE::SharedPtr< T > GetRootT()
	{
		return DP_CAST< T >( GetRoot() );
	}

	template< typename T > XE::SharedPtr< T > GetParentT() const
	{
		return DP_CAST< T >( GetParent() );
	}

public:
	XE::SceneComponentPtr FindChild( const XE::String& val ) const;

	XE::SceneComponentPtr FindChild( XE::IMetaClassPtr val ) const;

	XE::SceneComponentPtr FindChild( XE::ComponentHandle val ) const;

	XE::SceneComponentPtr FindChildFromTree( const XE::String& val ) const;

	XE::SceneComponentPtr FindChildFromTree( XE::IMetaClassPtr val ) const;

	XE::SceneComponentPtr FindChildFromTree( XE::ComponentHandle val ) const;

public:
	template< typename T > XE::SharedPtr< T > FindChildT() const
	{
		return SP_CAST< T >( FindChild( ClassID< T >::Get() ) );
	}

	template< typename T > XE::SharedPtr< T > FindChildT( const XE::String& val ) const
	{
		return DP_CAST< T >( FindChild( val ) );
	}

	template< typename T > XE::SharedPtr< T > FindChildT( XE::ComponentHandle val ) const
	{
		return DP_CAST< T >( FindChild( val ) );
	}

	template< typename T > XE::SharedPtr< T > FindChildFromTreeT() const
	{
		return SP_CAST< T >( FindChildFromTree( ClassID< T >::Get() ) );
	}

	template< typename T > XE::SharedPtr< T > FindChildFromTreeT( const XE::String& val ) const
	{
		return DP_CAST< T >( FindChildFromTree( val ) );
	}

	template< typename T > XE::SharedPtr< T > FindChildFromTreeT( XE::ComponentHandle val ) const
	{
		return DP_CAST< T >( FindChildFromTree( val ) );
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
