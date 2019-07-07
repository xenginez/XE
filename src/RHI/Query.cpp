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

void XE::Query::Begin( XE::uint32 val )
{
	_Device->BeginQuery( _Handle, val );
}

void XE::Query::End( XE::uint32 val )
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

XE::float64 XE::TimerQuery::TimeElapsed() const
{
	return ReadBack().Value<XE::float64>();
}

BEG_META( OcclusionQuery )
END_META()

XE::OcclusionQuery::OcclusionQuery()
{

}

XE::OcclusionQuery::~OcclusionQuery()
{

}

XE::uint64 XE::OcclusionQuery::SamplesPassed() const
{
	return ReadBack().Value<XE::uint64>();
}

BEG_META( ConditionQuery )
END_META()

XE::ConditionQuery::ConditionQuery()
{

}

XE::ConditionQuery::~ConditionQuery()
{

}

bool XE::ConditionQuery::SamplesPassed() const
{
	return ReadBack().Value<bool>();
}

BEG_META( SOStatisticsQuery )
END_META()

XE::SOStatisticsQuery::SOStatisticsQuery()
{

}

XE::SOStatisticsQuery::~SOStatisticsQuery()
{

}

XE::uint64 XE::SOStatisticsQuery::WritePrimitivesCount() const
{
	return ReadBack().Value<XE::uint64>();
}
