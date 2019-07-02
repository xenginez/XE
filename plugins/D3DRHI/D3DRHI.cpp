#include "D3DRHI.h"

USING_XE

XE::D3DRHI::D3DRHI( IFrameworkPtr framework )
	:IPlugin( framework )
{

}

XE::D3DRHI::~D3DRHI()
{

}

String XE::D3DRHI::GetName() const
{
	return "D3DRHI";
}

void XE::D3DRHI::Startup()
{

}

void XE::D3DRHI::Clearup()
{

}

REGISTER_PLUGIN( D3DRHI );