#include "IService.h"

USING_XE

BEGIN_META( IService )
END_META()

XE::IService::IService()
{

}

XE::IService::~IService()
{

}

XE::ObjectPtr XE::IService::Clone() const
{
	return nullptr;
}

XE::IFrameworkPtr XE::IService::GetFramework() const
{
	return _Framework;
}

void XE::IService::SetFramework( IFrameworkPtr val )
{
	_Framework = val;
}
