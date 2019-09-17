#include "AnimationController.h"

#include "Animator.h"

USING_XE

BEG_META( AnimationController )
type->Property( "Animators", &AnimationController::_Animators );
type->Property( "Parameters", &AnimationController::_Parameters );
END_META()

XE::AnimationController::AnimationController()
{

}

XE::AnimationController::~AnimationController()
{

}

void XE::AnimationController::Activate()
{
	for( auto & anim : _Animators )
	{
		anim->Activate();
	}
}

void XE::AnimationController::Activate( XE::uint32 val )
{
	_Animators[val]->Activate();
}

void XE::AnimationController::Activate( const XE::String & val )
{
	auto it = _AnimatorMaps.find( val );
	if( it != _AnimatorMaps.end() )
	{
		_Animators[it->second]->Activate();
	}
}

void XE::AnimationController::Deactivate()
{
	for( auto & anim : _Animators )
	{
		anim->Deactivate();
	}
}

void XE::AnimationController::Deactivate( XE::uint32 val )
{
	_Animators[val]->Deactivate();
}

void XE::AnimationController::Deactivate( const XE::String & val )
{
	auto it = _AnimatorMaps.find( val );
	if( it != _AnimatorMaps.end() )
	{
		_Animators[it->second]->Deactivate();
	}
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
	for( auto & anim : _Animators )
	{
		if( anim->IsEnable() )
		{
			anim->Update( val );
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

XE::Variant AnimationController::GetParameter( const XE::String & val ) const
{
	auto it = _Parameters.find( val );
	if( it != _Parameters.end() )
	{
		return it->second;
	}

	return Variant();
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

void AnimationController::SetParameter( const XE::String & name, const XE::Variant & val )
{
	_Parameters[name] = val;
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
