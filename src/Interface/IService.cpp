#include "IService.h"

USING_XE

BEG_META( IService )
END_META()

XE::IService::IService()
{

}

XE::IService::~IService()
{

}

XE::IFrameworkPtr XE::IService::GetFramework() const
{
	return _Framework;
}

void XE::IService::SetFramework( IFrameworkPtr val )
{
	_Framework = val;
}
