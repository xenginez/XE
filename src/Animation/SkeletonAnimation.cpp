#include "SkeletonAnimation.h"

USING_XE

BEG_META( SkeletonAnimationKey )
type->Property( "Time", &SkeletonAnimationKey::GetTime, &SkeletonAnimationKey::SetTime );
type->Property( "Position", &SkeletonAnimationKey::GetPosition, &SkeletonAnimationKey::SetPosition );
type->Property( "Rotation", &SkeletonAnimationKey::GetRotation, &SkeletonAnimationKey::SetRotation );
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

const XE::Vec3 & XE::SkeletonAnimationKey::GetPosition() const
{
	return _Position;
}

void XE::SkeletonAnimationKey::SetPosition( const XE::Vec3 & val )
{
	_Position = val;
}

const XE::Quat & XE::SkeletonAnimationKey::GetRotation() const
{
	return _Rotation;
}

void XE::SkeletonAnimationKey::SetRotation( const XE::Quat & val )
{
	_Rotation = val;
}

BEG_META( SkeletonAnimationTrack )
type->Property( "MaxTime", &SkeletonAnimationTrack::GetMaxTime, &SkeletonAnimationTrack::SetMaxTime );
type->Property( "SkeletonAnimationKeys", &SkeletonAnimationTrack::GetSkeletonAnimationKeys, &SkeletonAnimationTrack::SetSkeletonAnimationKeys );
END_META()

XE::SkeletonAnimationTrack::SkeletonAnimationTrack()
	:_MaxTime( 0.0f )
{

}

XE::SkeletonAnimationTrack::~SkeletonAnimationTrack()
{

}

XE::float32 XE::SkeletonAnimationTrack::GetMaxTime() const
{
	return _MaxTime;
}

void XE::SkeletonAnimationTrack::SetMaxTime( XE::float32 val )
{
	_MaxTime = val;
}

const XE::Array< SkeletonAnimationKey > & XE::SkeletonAnimationTrack::GetSkeletonAnimationKeys() const
{
	return _Keys;
}

void XE::SkeletonAnimationTrack::SetSkeletonAnimationKeys( const XE::Array< SkeletonAnimationKey > & val )
{
	_Keys = val;
}

BEG_META( SkeletonAnimation )
type->Property( "Name", &SkeletonAnimation::GetName, &SkeletonAnimation::SetName );
type->Property( "MaxTime", &SkeletonAnimation::GetMaxTime, &SkeletonAnimation::SetMaxTime );
type->Property( "Skeleton", &SkeletonAnimation::GetSkeleton, &SkeletonAnimation::SetSkeleton );
type->Property( "SkeletonAnimationTracks", &SkeletonAnimation::GetSkeletonAnimationTracks, &SkeletonAnimation::SetSkeletonAnimationTracks );
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

const XE::Map< XE::uint32, XE::SkeletonAnimationTrack > & XE::SkeletonAnimation::GetSkeletonAnimationTracks() const
{
	return _Tracks;
}

void XE::SkeletonAnimation::SetSkeletonAnimationTracks( const Map< XE::uint32, SkeletonAnimationTrack > & val )
{
	_Tracks = val;
}

/*
bool XE::SkeletonAnimation::CalcBoneJointTransform( XE::uint32 bone, XE::float32 time, XE::Mat4 & trans ) const
{
	auto tracks_iter = _Tracks.find( bone );
	if( tracks_iter != _Tracks.end() )
	{
		if( time < Mathf::Epsilon )
		{
			mat = Mathf::TRS(
				tracks_iter->second._Keys.front()._Position,
				tracks_iter->second._Keys.front()._Rotation,
				Vec3::One );

			return true;
		}
		else if( time <= tracks_iter->second._MaxTime )
		{
			auto key_iter = std::find_if( tracks_iter->second._Keys.begin(), tracks_iter->second._Keys.end(), [time]( const SkeletonAnimationKey & key )
										  {
											  return key._Time >= time;
										  } );

			if( key_iter != tracks_iter->second._Keys.end() )
			{
				XE::float32 t = ( time - ( key_iter - 1 )->_Time ) / ( key_iter->_Time - ( key_iter - 1 )->_Time );

				mat = Mathf::TRS(
					Mathf::Lerp( ( key_iter - 1 )->_Position, key_iter->_Position, t ),
					Mathf::Slerp( ( key_iter - 1 )->_Rotation, key_iter->_Rotation, t ),
					Vec3::One );

				return true;
			}
		}
	}

	return false;
}
*/