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
	void BeginQuery( XE::uint32 val );

	void EndQuery( XE::uint32 val );

public:
	Variant ReadBack() const;

	QueryHandle GetHandle() const;

private:
	DevicePtr _Device;
	QueryHandle _Handle;
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

END_XE_NAMESPACE

#endif // QUERY_H__77E38073_417C_4F36_8B10_D72574F5383B
