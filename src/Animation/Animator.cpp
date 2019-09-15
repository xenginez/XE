#include "Animator.h"

USING_XE

BEG_META( AnimatorItem )
type->Property( "Position", &AnimatorItem::GetPosition, &AnimatorItem::SetPosition );
type->Property( "Rotation", &AnimatorItem::GetRotation, &AnimatorItem::SetRotation );
END_META()

XE::AnimatorItem::AnimatorItem()
{

}

XE::AnimatorItem::~AnimatorItem()
{

}

const XE::Vec3 & XE::AnimatorItem::GetPosition() const
{
	return _Position;
}

void XE::AnimatorItem::SetPosition( const XE::Vec3 & val )
{
	_Position = val;
}

const XE::Quat & XE::AnimatorItem::GetRotation() const
{
	return _Rotation;
}

void XE::AnimatorItem::SetRotation( const XE::Quat & val )
{
	_Rotation = val;
}


BEG_META( AnimatorKey )
type->Property( "Time", &AnimatorKey::GetTime, &AnimatorKey::SetTime );
type->Property( "Items", &AnimatorKey::GetSkeletonItems, &AnimatorKey::SetSkeletonItems );
END_META()

XE::AnimatorKey::AnimatorKey()
	:_Time( 0.0f )
{

}

XE::AnimatorKey::~AnimatorKey()
{

}

XE::float32 XE::AnimatorKey::GetTime() const
{
	return _Time;
}

void XE::AnimatorKey::SetTime( XE::float32 val )
{
	_Time = val;
}

const XE::Array< XE::AnimatorItem > & XE::AnimatorKey::GetSkeletonItems() const
{
	return _Items;
}

void XE::AnimatorKey::SetSkeletonItems( const Array< AnimatorItem > & val )
{
	_Items = val;
}


BEG_META( Animator )
type->Property( "Name", &Animator::_Name );
type->Property( "Skeleton", &Animator::_Skeleton );
type->Property( "MaxTime", &Animator::_MaxTime );
type->Property( "Keys", &Animator::_Keys );
END_META()

XE::Animator::Animator()
	:_MaxTime( 0.0f )
{

}

XE::Animator::~Animator()
{

}

XE::float32 XE::Animator::GetMaxTime() const
{
	return _MaxTime;
}

void XE::Animator::SetMaxTime( XE::float32 val )
{
	_MaxTime = val;
}

const XE::String & XE::Animator::GetName() const
{
	return _Name;
}

void XE::Animator::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::String & XE::Animator::GetSkeleton() const
{
	return _Skeleton;
}

void XE::Animator::SetSkeleton( const XE::String & val )
{
	_Skeleton = val;
}

const XE::Array< XE::AnimatorKey > & XE::Animator::GetSkeletonKeys() const
{
	return _Keys;
}

void XE::Animator::SetSkeletonKeys( const Array< AnimatorKey > & val )
{
	_Keys = val;
}

XE::Vec3 XE::Animator::CalcBoneJointPosition( XE::uint32 bone, XE::float32 time ) const
{
	XE::Mat4 mat = CalcBoneJointTransform( bone, time );

	XE::Vec3 pos;
	XE::Quat rot;
	XE::Vec3 scl;

	Mathf::TRS( mat, pos, rot, scl );

	return pos;
}

XE::Quat XE::Animator::CalcBoneJointRotation( XE::uint32 bone, XE::float32 time ) const
{
	XE::Mat4 mat = CalcBoneJointTransform( bone, time );

	XE::Vec3 pos;
	XE::Quat rot;
	XE::Vec3 scl;

	Mathf::TRS( mat, pos, rot, scl );

	return rot;
}

XE::Mat4 XE::Animator::CalcBoneJointTransform( XE::uint32 bone, XE::float32 time ) const
{
	for( auto it = _Keys.begin(); it != _Keys.end(); ++it )
	{
		if( it->GetTime() < time )
		{
			auto pos1 = ( it - 1 )->GetSkeletonItems()[bone].GetPosition();
			auto rot1 = ( it - 1 )->GetSkeletonItems()[bone].GetRotation();

			auto pos2 = it->GetSkeletonItems()[bone].GetPosition();
			auto rot2 = it->GetSkeletonItems()[bone].GetRotation();

			XE::float32 t = ( time - ( it - 1 )->GetTime() ) / ( it->GetTime() - ( it - 1 )->GetTime() );

			return Mathf::TRS( Mathf::Lerp( pos1, pos2, t ), Mathf::Slerp( rot1, rot2, t ), XE::Vec3::One );
		}
		else if( Mathf::Abs( it->GetTime() - time ) < Mathf::Epsilon )
		{
			return Mathf::TRS( it->GetSkeletonItems()[bone].GetPosition(), it->GetSkeletonItems()[bone].GetRotation(), XE::Vec3::One );
		}
	}

	return Mathf::TRS( _Keys.back().GetSkeletonItems()[bone].GetPosition(), _Keys.back().GetSkeletonItems()[bone].GetRotation(), XE::Vec3::One );
}
