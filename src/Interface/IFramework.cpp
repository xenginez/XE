#include "IFramework.h"

XE::IFrameworkPtr XE::IFramework::_CurrentFramework = nullptr;

USING_XE

BEG_META( IFramework )
END_META()

IFramework::IFramework()
{
	XE_ASSERT( _CurrentFramework == nullptr && "framework is not unique!" );

	_CurrentFramework = this;
}

IFramework::~IFramework()
{
	_CurrentFramework = nullptr;
}

XE::IFrameworkPtr XE::IFramework::GetCurrentFramework()
{
	return _CurrentFramework;
}
