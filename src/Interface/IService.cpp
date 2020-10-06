#include "IService.h"

BEG_META( XE::IService )
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

void XE::IService::SetFramework( XE::IFrameworkPtr val )
{
	_Framework = val;
}
