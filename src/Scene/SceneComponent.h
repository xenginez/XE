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
	virtual void Startup() override;

	virtual void Update( XE::float32 dt ) override;

	virtual void Clearup() override;

public:
	const AABB & GetBoundingBox();

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

protected:
	virtual void UpdateTransform();

private:
	bool _Dirty;

	XE::Vec3f _WorldScale;
	XE::Vec3f _WorldPosition;
	XE::Quat _WorldRotation;
	XE::Vec3f _RelativeScale;
	XE::Vec3f _RelativePosition;
	XE::Quat _RelativeRotation;

	XE::Mat4f _WorldTransform;
	XE::Mat4f _RelativeTransform;

	XE::AABB _BoundingBox;
	XE::SceneComponentWPtr _Parent;
	XE::Array< SceneComponentPtr > _Children;
};

END_XE_NAMESPACE

#endif // __SCENETREECOMPONENT_H__D96EDC7D_216F_47EE_ACC2_31541C5B31C7
