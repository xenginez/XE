#include "SkeletonAnimation.h"

USING_XE

BEG_META( SkeletonAnimationKey )
type->Property( "Time", &SkeletonAnimationKey::GetTime, &SkeletonAnimationKey::SetTime );
type->Property( "Position", &SkeletonAnimationKey::GetPosition, &SkeletonAnimationKey::SetPosition );
type->Property( "Rotation", &SkeletonAnimationKey::GetRotation, &SkeletonAnimationKey::SetRotation );
type->Property( "Scale", &SkeletonAnimationKey::GetScale, &SkeletonAnimationKey::SetScale );
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

const XE::Vec3 & SkeletonAnimationKey::GetScale() const
{
	return _Scale;
}

void SkeletonAnimationKey::SetScale( const XE::Vec3 & val )
{
	_Scale = val;
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

const XE::Array< XE::SkeletonAnimationTrack > & XE::SkeletonAnimation::GetSkeletonAnimationTracks() const
{
	return _Tracks;
}

void XE::SkeletonAnimation::SetSkeletonAnimationTracks( const XE::Array< SkeletonAnimationTrack > & val )
{
	_Tracks = val;
}

bool SkeletonAnimation::Sample( XE::uint32 bone, XE::float32 time, XE::Vec3 & position, XE::Quat & rotation, XE::Vec3 & scale ) const
{
	const auto & tracks_iter = _Tracks[bone];

	if( tracks_iter._Keys.size() )
	{
		if( time < Mathf::Epsilon )
		{
			position = tracks_iter._Keys.front()._Position;
			rotation = tracks_iter._Keys.front()._Rotation;
			scale = tracks_iter._Keys.front()._Scale;

			return true;
		}
		else if( time <= tracks_iter._MaxTime )
		{
			auto key_iter = std::find_if( tracks_iter._Keys.begin(), tracks_iter._Keys.end(), [time]( const SkeletonAnimationKey & key )
										  {
											  return key._Time >= time;
										  } );

			if( key_iter != tracks_iter._Keys.end() )
			{
				XE::float32 t = ( time - ( key_iter - 1 )->_Time ) / ( key_iter->_Time - ( key_iter - 1 )->_Time );

				position = Mathf::Lerp( ( key_iter - 1 )->_Position, key_iter->_Position, t );
				rotation = Mathf::Slerp( ( key_iter - 1 )->_Rotation, key_iter->_Rotation, t );
				scale = Mathf::Lerp( ( key_iter - 1 )->_Scale, key_iter->_Scale, t );

				return true;
			}
		}
	}

	return false;
}
