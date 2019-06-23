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

class AI_API AIModule : public XE::Object
{
	OBJECT( AIModule, Object )

public:
	AIModule();

	~AIModule();

public:
	virtual void Startup() = 0;

	virtual void Update( XE::real dt ) = 0;

	virtual void Clearup() = 0;

public:
	GameObjectPtr GetGameObject() const;

	void SetGameObject( GameObjectPtr val );

private:
	GameObjectWPtr _GameObject;
};

END_XE_NAMESPACE

#endif // __AIMODULE_H__A590ED03_BAEC_4291_90B5_DBFC9EB9A475
