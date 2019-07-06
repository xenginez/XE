#include "Query.h"

#include "Device.h"

USING_XE

BEG_META( Query )
END_META()

XE::Query::Query()
{

}

XE::Query::~Query()
{

}

void XE::Query::BeginQuery( XE::uint32 val )
{
	_Device->BeginQuery( _Handle, val );
}

void XE::Query::EndQuery( XE::uint32 val )
{
	_Device->EndQuery( _Handle, val );
}

XE::Variant XE::Query::ReadBack() const
{
	return _Device->ReadBack( _Handle );
}

XE::QueryHandle XE::Query::GetHandle() const
{
	return _Handle;
}

BEG_META( TimerQuery )
END_META()

XE::TimerQuery::TimerQuery()
{

}

XE::TimerQuery::~TimerQuery()
{

}

BEG_META( OcclusionQuery )
END_META()

XE::OcclusionQuery::OcclusionQuery()
{

}

XE::OcclusionQuery::~OcclusionQuery()
{

}
