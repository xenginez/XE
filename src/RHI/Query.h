/*!
 * \file	Query.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/06
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef QUERY_H__77E38073_417C_4F36_8B10_D72574F5383B
#define QUERY_H__77E38073_417C_4F36_8B10_D72574F5383B

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Query : std::enable_shared_from_this< Query >
{
	OBJECT( Query )

public:
	Query();

	virtual ~Query();

public:
	void Begin( XE::uint32 val );

	void End( XE::uint32 val );

public:
	QueryHandle GetHandle() const;

protected:
	Variant ReadBack() const;

private:
	ContextPtr _Device;
	QueryHandle _Handle;
};

class RHI_API TimerQuery : public Query
{
	OBJECT( TimerQuery, Query )

public:
	TimerQuery();

	~TimerQuery() override;

public:
	XE::float64 TimeElapsed() const;
};

class RHI_API OcclusionQuery : public Query
{
	OBJECT( OcclusionQuery, Query )

public:
	OcclusionQuery();

	~OcclusionQuery() override;

public:
	XE::uint64 SamplesPassed() const;
};

class RHI_API ConditionQuery : public Query
{
	OBJECT( ConditionQuery, Query )

public:
	ConditionQuery();

	~ConditionQuery() override;

public:
	bool SamplesPassed() const;
};

class RHI_API SOStatisticsQuery : public Query
{
	OBJECT( SOStatisticsQuery, Query )

public:
	SOStatisticsQuery();

	~SOStatisticsQuery() override;

public:
	XE::uint64 WritePrimitivesCount() const;
};

END_XE_NAMESPACE

#endif // QUERY_H__77E38073_417C_4F36_8B10_D72574F5383B
