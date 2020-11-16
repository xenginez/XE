#include "IAudioService.h"

BEG_META( XE::IAudioService )
END_META()

struct XE::IAudioService::Private
{
	XE::Vec3f _Position = {};
	XE::Vec3f _Velocity = {};
	XE::Vec3f _Orientation = {};
};

XE::IAudioService::IAudioService()
	:_p( new Private )
{

}

XE::IAudioService::~IAudioService()
{
	delete _p;
}

const XE::Vec3f & XE::IAudioService::GetListenerPosition() const
{
	return _p->_Position;
}

void XE::IAudioService::SetListenerPosition( const XE::Vec3f & val )
{
	_p->_Position = val;
}

const XE::Vec3f & XE::IAudioService::GetListenerVelocity() const
{
	return _p->_Velocity;
}

void XE::IAudioService::SetListenerVelocity( const XE::Vec3f & val )
{
	_p->_Velocity = val;
}

const XE::Vec3f & XE::IAudioService::GetListenerOrientation() const
{
	return _p->_Orientation;
}

void XE::IAudioService::SetListenerOrientation( const XE::Vec3f & val )
{
	_p->_Orientation = val;
}
