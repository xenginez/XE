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
		if( anim->IsEnable() && anim->IsPlaying() )
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

void XE::AnimationController::Play()
{
	for( auto & anim : _Animators )
	{
		anim->Play();
	}
}

void XE::AnimationController::Play( XE::uint32 val )
{
	_Animators[val]->Play();
}

void XE::AnimationController::Play( const XE::String & val )
{
	auto it = _AnimatorMaps.find( val );
	if( it != _AnimatorMaps.end() )
	{
		_Animators[it->second]->Play();
	}
}

void XE::AnimationController::Stop()
{
	for( auto & anim : _Animators )
	{
		anim->Stop();
	}
}

void XE::AnimationController::Stop( XE::uint32 val )
{
	_Animators[val]->Stop();
}

void XE::AnimationController::Stop( const XE::String & val )
{
	auto it = _AnimatorMaps.find( val );
	if( it != _AnimatorMaps.end() )
	{
		_Animators[it->second]->Stop();
	}
}

bool XE::AnimationController::IsPlaying() const
{
	for( auto & anim : _Animators )
	{
		if( !anim->IsPlaying() )
		{
			return false;
		}
	}

	return true;
}

bool XE::AnimationController::IsPlaying( XE::uint32 val ) const
{
	return _Animators[val]->IsPlaying();
}

bool XE::AnimationController::IsPlaying( const XE::String & val ) const
{
	auto it = _AnimatorMaps.find( val );
	if( it != _AnimatorMaps.end() )
	{
		return _Animators[it->second]->IsPlaying();
	}

	return false;
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
