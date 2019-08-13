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

class RHI_API Query : public Resource
{
	OBJECT( Query, Resource )

public:
	Query();

	virtual ~Query();

};

class RHI_API TimerQuery : public Query
{
	OBJECT( TimerQuery, Query )

public:
	TimerQuery();

	~TimerQuery() override;

};

class RHI_API OcclusionQuery : public Query
{
	OBJECT( OcclusionQuery, Query )

public:
	OcclusionQuery();

	~OcclusionQuery() override;

};

class RHI_API ConditionQuery : public Query
{
	OBJECT( ConditionQuery, Query )

public:
	ConditionQuery();

	~ConditionQuery() override;

};

class RHI_API SOStatisticsQuery : public Query
{
	OBJECT( SOStatisticsQuery, Query )

public:
	SOStatisticsQuery();

	~SOStatisticsQuery() override;

};

END_XE_NAMESPACE

#endif // QUERY_H__77E38073_417C_4F36_8B10_D72574F5383B
