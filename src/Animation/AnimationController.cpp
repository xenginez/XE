#include "AnimationController.h"

#include "Animator.h"

USING_XE

BEG_META( AnimationController )
type->Property( "Enable", &AnimationController::_Enable );
type->Property( "Animators", &AnimationController::_Animators );
type->Property( "Parameters", &AnimationController::_Parameters );
END_META()

XE::AnimationController::AnimationController()
	:_Enable( true )
{

}

XE::AnimationController::~AnimationController()
{

}

void XE::AnimationController::Startup()
{
	for( XE::uint32 i = 0; i < _Animators.size(); i++ )
	{
		_AnimatorMaps[_Animators[i]->GetName()] = i;

		_Animators[i]->SetAnimationController( XE_THIS( AnimationController ) );

		_Animators[i]->Startup();
	}
}

void XE::AnimationController::Update( XE::float32 val )
{
	if( _Enable )
	{
		for( auto & anim : _Animators )
		{
			if( anim->GetEnable() )
			{
				anim->Update( val );
			}
		}
	}
}

void XE::AnimationController::Clearup()
{
	for( auto & anim : _Animators )
	{
		anim->Clearup();
	}

	_Animators.clear();
	_AnimatorMaps.clear();
}

XE::SkeletonPtr AnimationController::GetSkeleton() const
{
	return _Skeleton;
}

void AnimationController::SetSkeleton( const XE::SkeletonPtr & val )
{
	_Skeleton = val;
}

bool XE::AnimationController::GetEnable()
{
	return _Enable;
}

bool XE::AnimationController::GetEnable( XE::uint32 layer )
{
	return _Animators[layer]->GetEnable();
}

bool XE::AnimationController::GetEnable( const XE::String & layer )
{
	auto it = _AnimatorMaps.find( layer );

	if( it != _AnimatorMaps.end() )
	{
		_Animators[it->second]->GetEnable();
	}

	return false;
}

void XE::AnimationController::SetEnable( bool val )
{
	if( _Enable != val )
	{
		for( auto & anim : _Animators )
		{
			anim->SetEnable( val );
		}
	}
}

void XE::AnimationController::SetEnable( XE::uint32 layer, bool val )
{
	_Animators[layer]->SetEnable( val );
}

void XE::AnimationController::SetEnable( const XE::String & layer, bool val )
{
	auto it = _AnimatorMaps.find( layer );

	if( it != _AnimatorMaps.end() )
	{
		_Animators[it->second]->SetEnable( val );
	}
}

bool AnimationController::GetParameterBool( const XE::String & val ) const
{
	return GetParameter( val ).Value<bool>();
}

XE::int32 AnimationController::GetParameterInt( const XE::String & val ) const
{
	return GetParameter( val ).Value<XE::int32>();
}

XE::float32 AnimationController::GetParameterFloat( const XE::String & val ) const
{
	return GetParameter( val ).Value<XE::float32>();
}

XE::String AnimationController::GetParameterString( const XE::String & val ) const
{
	return GetParameter( val ).Value<XE::String>();
}

void AnimationController::SetParameterBool( const XE::String & name, bool val )
{
	SetParameter( name, val );
}

void AnimationController::SetParameterInt( const XE::String & name, XE::int32 val )
{
	SetParameter( name, val );
}

void AnimationController::SetParameterFloat( const XE::String & name, XE::float32 val )
{
	SetParameter( name, val );
}

void AnimationController::SetParameterString( const XE::String & name, XE::String val )
{
	SetParameter( name, val );
}

XE::Variant AnimationController::GetParameter( const XE::String & val ) const
{
	auto it = _Parameters.find( val );
	if( it != _Parameters.end() )
	{
		return it->second;
	}

	return Variant();
}

void AnimationController::SetParameter( const XE::String & name, const XE::Variant & val )
{
	_Parameters[name] = val;
}
