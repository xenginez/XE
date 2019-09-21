/*!
 * \file   Condition.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/14
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CONDITION_H__5371FF72_A78F_49E3_9389_F802BE687E57
#define __CONDITION_H__5371FF72_A78F_49E3_9389_F802BE687E57

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Condition
{
	OBJECT( Condition )

public:
	Condition();

	~Condition();

public:
	virtual bool Judgment() const;

public:
	AIModule * GetAIModule() const;

	void SetAIModule( AIModule * val );

private:
	AIModule * _AIModule;
};

END_XE_NAMESPACE

#endif // __CONDITION_H__5371FF72_A78F_49E3_9389_F802BE687E57
