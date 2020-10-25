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

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Condition : public XE::Object
{
	OBJECT( Condition, Object )

public:
	Condition();

	~Condition() override;

public:
	virtual bool Judgment() const;

public:
	const AIModulePtr & GetAIModule() const;

	void SetAIModule( const AIModulePtr & val );

	XE::AIStateHandle GetNextStateHandle() const;

	void SetNextStateHandle( XE::AIStateHandle val );

private:
	AIModulePtr _AIModule;
	XE::AIStateHandle _NextState;
};

END_XE_NAMESPACE

#endif // __CONDITION_H__5371FF72_A78F_49E3_9389_F802BE687E57
