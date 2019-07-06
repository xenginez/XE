#include "Query.h"

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

}

void XE::Query::EndQuery( XE::uint32 val )
{

}

XE::Variant XE::Query::ReadBack() const
{
	return nullptr;
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
