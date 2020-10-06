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

protected:
	virtual void UpdateTransform();

private:
	bool _Dirty;

	XE::Vec3 _WorldScale;
	XE::Vec3 _WorldPosition;
	XE::Quat _WorldRotation;
	XE::Vec3 _RelativeScale;
	XE::Vec3 _RelativePosition;
	XE::Quat _RelativeRotation;

	XE::Mat4 _WorldTransform;
	XE::Mat4 _RelativeTransform;

	XE::AABB _BoundingBox;
	XE::SceneComponentWPtr _Parent;
	XE::Array< SceneComponentPtr > _Children;
};

END_XE_NAMESPACE

#endif // __SCENETREECOMPONENT_H__D96EDC7D_216F_47EE_ACC2_31541C5B31C7
