#include "IPluginService.h"

USING_XE

XE::IPlugin::IPlugin( IFrameworkPtr framework )
	: _Framework( framework )
{

}

XE::IPlugin::~IPlugin()
{

}

XE::IFrameworkPtr XE::IPlugin::GetFramework() const
{
	return _Framework;
}

BEGIN_META( IPluginService )
END_META()

XE::IPluginService::IPluginService()
{

}

XE::IPluginService::~IPluginService()
{

}
