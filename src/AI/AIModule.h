/*!
 * \file   AIModule.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/14
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __AIMODULE_H__A590ED03_BAEC_4291_90B5_DBFC9EB9A475
#define __AIMODULE_H__A590ED03_BAEC_4291_90B5_DBFC9EB9A475

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AIModule : public XE::Object
{
	OBJECT( AIModule, Object )

public:
	AIModule();

	~AIModule();

public:
	virtual void Startup() = 0;

	virtual void Update( XE::float32 dt ) = 0;

	virtual void Clearup() = 0;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

private:
	XE::String _Name;
};

END_XE_NAMESPACE

#endif // __AIMODULE_H__A590ED03_BAEC_4291_90B5_DBFC9EB9A475
