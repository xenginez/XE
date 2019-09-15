#include "SkeletonAnimation.h"

USING_XE

BEG_META( SkeletonAnimationItem )
type->Property( "Position", &SkeletonAnimationItem::GetPosition, &SkeletonAnimationItem::SetPosition );
type->Property( "Rotation", &SkeletonAnimationItem::GetRotation, &SkeletonAnimationItem::SetRotation );
type->Property( "Scale", &SkeletonAnimationItem::GetScale, &SkeletonAnimationItem::SetScale );
END_META()

XE::SkeletonAnimationItem::SkeletonAnimationItem()
{

}

XE::SkeletonAnimationItem::~SkeletonAnimationItem()
{

}

const XE::Vec3 & XE::SkeletonAnimationItem::GetPosition() const
{
	return _Position;
}

void XE::SkeletonAnimationItem::SetPosition( const XE::Vec3 & val )
{
	_Position = val;
}

const XE::Quat & XE::SkeletonAnimationItem::GetRotation() const
{
	return _Rotation;
}

void XE::SkeletonAnimationItem::SetRotation( const XE::Quat & val )
{
	_Rotation = val;
}

const XE::Vec3 & XE::SkeletonAnimationItem::GetScale() const
{
	return _Scale;
}

void XE::SkeletonAnimationItem::SetScale( const XE::Vec3 & val )
{
	_Scale = val;
}

BEG_META( SkeletonAnimationKey )
type->Property( "Time", &SkeletonAnimationKey::GetTime, &SkeletonAnimationKey::SetTime );
type->Property( "Items", &SkeletonAnimationKey::GetSkeletonItems, &SkeletonAnimationKey::SetSkeletonItems );
END_META()

XE::SkeletonAnimationKey::SkeletonAnimationKey()
	:_Time( 0.0f )
{

}

XE::SkeletonAnimationKey::~SkeletonAnimationKey()
{

}

XE::float32 XE::SkeletonAnimationKey::GetTime() const
{
	return _Time;
}

void XE::SkeletonAnimationKey::SetTime( XE::float32 val )
{
	_Time = val;
}

const XE::Map< XE::uint32, SkeletonAnimationItem > & XE::SkeletonAnimationKey::GetSkeletonItems() const
{
	return _Items;
}

void XE::SkeletonAnimationKey::SetSkeletonItems( const XE::Map< XE::uint32, SkeletonAnimationItem > & val )
{
	_Items = val;
}


BEG_META( SkeletonAnimation )
type->Property( "Name", &SkeletonAnimation::_Name );
type->Property( "Skeleton", &SkeletonAnimation::_Skeleton );
type->Property( "MaxTime", &SkeletonAnimation::_MaxTime );
type->Property( "Keys", &SkeletonAnimation::_Keys );
END_META()

XE::SkeletonAnimation::SkeletonAnimation()
	:_MaxTime( 0.0f )
{

}

XE::SkeletonAnimation::~SkeletonAnimation()
{

}

XE::float32 XE::SkeletonAnimation::GetMaxTime() const
{
	return _MaxTime;
}

void XE::SkeletonAnimation::SetMaxTime( XE::float32 val )
{
	_MaxTime = val;
}

const XE::String & XE::SkeletonAnimation::GetName() const
{
	return _Name;
}

void XE::SkeletonAnimation::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::String & XE::SkeletonAnimation::GetSkeleton() const
{
	return _Skeleton;
}

void XE::SkeletonAnimation::SetSkeleton( const XE::String & val )
{
	_Skeleton = val;
}

const XE::Array< XE::SkeletonAnimationKey > & XE::SkeletonAnimation::GetSkeletonKeys() const
{
	return _Keys;
}

void XE::SkeletonAnimation::SetSkeletonKeys( const Array< SkeletonAnimationKey > & val )
{
	_Keys = val;
}

bool XE::SkeletonAnimation::CalcBoneJointPosition( XE::uint32 bone, XE::float32 time, XE::Vec3 & pos ) const
{
	XE::Quat rot;
	XE::Vec3 scale;

	return CalcBoneJointTransform( bone, time, pos, rot, scale );
}

bool XE::SkeletonAnimation::CalcBoneJointRotation( XE::uint32 bone, XE::float32 time, XE::Quat & rot ) const
{
	XE::Vec3 pos;
	XE::Vec3 scale;

	return CalcBoneJointTransform( bone, time, pos, rot, scale );
}

bool XE::SkeletonAnimation::CalcBoneJointScale( XE::uint32 bone, XE::float32 time, XE::Vec3 & scale ) const
{
	XE::Vec3 pos;
	XE::Quat rot;

	return CalcBoneJointTransform( bone, time, pos, rot, scale );
}

bool XE::SkeletonAnimation::CalcBoneJointTransform( XE::uint32 bone, XE::float32 time, XE::Vec3 & pos, XE::Quat & rot, XE::Vec3 & scale ) const
{
	for( auto it = _Keys.begin(); it != _Keys.end(); ++it )
	{
		if( it->GetTime() < time )
		{
			XE::Vec3 pos1, pos2;
			XE::Quat rot1, rot2;
			auto it1 = ( it - 1 )->GetSkeletonItems().find( bone );
			auto it2 = it->GetSkeletonItems().find( bone );

			if( it1 != ( it - 1 )->GetSkeletonItems().end() )
			{
				pos1 = it1->second.GetPosition();
				rot1 = it1->second.GetRotation();

				if( it2 != it->GetSkeletonItems().end() )
				{
					pos2 = it2->second.GetPosition();
					rot2 = it2->second.GetRotation();

					XE::float32 t = ( time - ( it - 1 )->GetTime() ) / ( it->GetTime() - ( it - 1 )->GetTime() );

					auto mat = Mathf::TRS( Mathf::Lerp( pos1, pos2, t ), Mathf::Slerp( rot1, rot2, t ), XE::Vec3::One );

					Mathf::TRS( mat, pos, rot, scale );

					return true;
				}
			}
		}
	}

	return false;
}
