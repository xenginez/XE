#include "ILoggerService.h"

USING_XE

BEG_META( ILoggerService )
type->Method( "Log", &ILoggerService::Log );
END_META()

XE::ILoggerService::ILoggerService()
{

}

XE::ILoggerService::~ILoggerService()
{

}
